// @ts-check

import { Project, SourceFile, ts } from "ts-morph"
import { minify } from "terser"
import path from "node:path"
import fs from "node:fs/promises"

/**
 * @param {SourceFile} sourceFile
 * @param  {...string} identifiers
 * @returns
 */
function getIdentifiers(sourceFile, ...identifiers) {
  return sourceFile
    .getDescendantsOfKind(ts.SyntaxKind.Identifier)
    .filter((i) => identifiers.includes(i.getText()))
}

/**
 *
 * @param {SourceFile} sourceFile
 * @returns
 */
function patchSource(sourceFile) {
  if (
    !sourceFile
      .getDescendantsOfKind(ts.SyntaxKind.Identifier)
      .filter((i) => i.getText() === "require").length
  ) {
    console.log("Already patched")
    return
  }

  // remove all conditions node specific conditions
  {
    getIdentifiers(sourceFile, "ENVIRONMENT_IS_NODE", "process")
      .map((i) => i.getFirstAncestorByKind(ts.SyntaxKind.IfStatement))
      .forEach(
        (i) =>
          i != null &&
          !i.wasForgotten() &&
          i.replaceWithText(i.getElseStatement()?.getFullText() ?? "")
      )
  }

  // remove all node specific variables
  {
    getIdentifiers(sourceFile, "ENVIRONMENT_IS_NODE").forEach((node) =>
      node
        .getFirstAncestorByKindOrThrow(ts.SyntaxKind.VariableDeclaration)
        .remove()
    )
  }

  // uncomment eval
  {
    getIdentifiers(sourceFile, "eval").forEach((node) => {
      node
        .getFirstAncestorByKindOrThrow(ts.SyntaxKind.ExpressionStatement)
        .replaceWithText((writer) => {
          writer.writeLine(`throw new Error("eval() is not supported")`)
        })
    })
  }

  // add import for ?module
  {
    const instantiateWasm = sourceFile
      .getDescendantsOfKind(ts.SyntaxKind.StringLiteral)
      .filter((i) => i.getText() === `"instantiateWasm"`)
      .map((i) => i.getFirstAncestorByKindOrThrow(ts.SyntaxKind.IfStatement))[0]

    // remove instantiateAsync() method call
    instantiateWasm
      .getNextSiblingIfKindOrThrow(ts.SyntaxKind.ExpressionStatement)
      .remove()

    instantiateWasm.replaceWithText((writer) => {
      writer.writeLine(
        `WebAssembly.instantiate(wasm, info).then((instance) => receiveInstance(instance, wasm))`
      )
    })

    sourceFile.insertText(0, (writer) => {
      writer.writeLine(`import wasm from "./tree-sitter.wasm?module"`)
    })
  }

  // patch Parser.Language.load to allow WebAssembly.Module as an argument
  {
    const block = sourceFile
      .getDescendantsOfKind(ts.SyntaxKind.MethodDeclaration)
      .filter((i) => i.isStatic() && i.getName() === "load")
      .at(0)

    if (block == null) throw new Error("Failed to find load function")
    const parameterName = block.getParameters().at(0)?.getName()

    const ifStmt = block.getFirstDescendantByKindOrThrow(
      ts.SyntaxKind.IfStatement
    )
    const assignVar = ifStmt
      .getThenStatement()
      .getFirstDescendantByKindOrThrow(ts.SyntaxKind.BinaryExpression)
      .getLeft()
      .asKindOrThrow(ts.SyntaxKind.Identifier)
      .getText()

    if (parameterName == null) throw new Error("Failed to find parameter name")
    ifStmt.replaceWithText(
      `if (${parameterName} instanceof WebAssembly.Module) { ${assignVar} = Promise.resolve(${parameterName}) } else ${ifStmt.getText()}`
    )
  }

  // Add a check for WebAssembly.Module imported from a different V8 context
  // (e.g. a different iframe or worker), fixing the instanceof check.
  {
    sourceFile
      .getDescendantsOfKind(ts.SyntaxKind.PropertyAccessExpression)
      .filter((i) => i.getText() === "WebAssembly.Module")
      .map((i) =>
        i.getFirstAncestorByKindOrThrow(ts.SyntaxKind.BinaryExpression)
      )
      .filter((i) => i.getOperatorToken().getText() === "instanceof")
      .forEach((expr) => {
        const text = expr.getText()
        const name = expr
          .getLeft()
          .asKindOrThrow(ts.SyntaxKind.Identifier)
          .getText()
        expr.replaceWithText(
          `${text} || ${name}.toString().includes("WebAssembly.Module")`
        )
      })
  }
}

/**
 *
 * @param {SourceFile} sourceFile
 * @returns
 */
function patchDefinition(sourceFile) {
  // make all delete() optional due to isomorphic nature of the library
  {
    getIdentifiers(sourceFile, "delete")
      .map((i) => i.getFirstAncestorByKind(ts.SyntaxKind.MethodDeclaration))
      .forEach((i) => i?.set({ hasQuestionToken: true }))

    getIdentifiers(sourceFile, "delete")
      .map((i) => i.getFirstAncestorByKind(ts.SyntaxKind.MethodSignature))
      .forEach((i) => i?.set({ hasQuestionToken: true }))
  }
}

async function main() {
  const project = new Project()
  const sourceFile = project.addSourceFileAtPath(
    path.resolve("./web-tree-sitter/tree-sitter.js")
  )

  const declarationFile = project.addSourceFileAtPath(
    path.resolve("./web-tree-sitter/tree-sitter-web.d.ts")
  )

  patchSource(sourceFile)
  patchDefinition(declarationFile)

  await fs.writeFile(
    path.resolve("./web-tree-sitter/tree-sitter.edge.js"),
    (await minify(sourceFile.getFullText())).code ?? "",
    { encoding: "utf-8" }
  )

  await fs.writeFile(
    path.resolve("./web-tree-sitter/tree-sitter.edge.d.ts"),
    declarationFile.getFullText(),
    { encoding: "utf-8" }
  )
}

main()
