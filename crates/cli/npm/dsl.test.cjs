const assert = require('node:assert/strict');
const fs = require('node:fs');
const os = require('node:os');
const path = require('node:path');
const test = require('node:test');
const ts = require('typescript');

const declarations = path.join(__dirname, 'dsl.d.ts');

test('the documented type reference resolves from an ES module dependency', () => {
  const directory = fs.mkdtempSync(path.join(os.tmpdir(), 'tree-sitter-dsl-types-'));
  try {
    const dependency = path.join(directory, 'node_modules', 'tree-sitter-cli');
    fs.mkdirSync(dependency, {recursive: true});
    fs.copyFileSync(declarations, path.join(dependency, 'dsl.d.ts'));
    fs.copyFileSync(path.join(__dirname, 'package.json'), path.join(dependency, 'package.json'));
    const filename = path.join(directory, 'grammar.mjs');
    fs.writeFileSync(filename, `
      /// <reference types="tree-sitter-cli/dsl.d.ts" />
      export const label = rule(), root = rule(() => alias('x', label));
      export default { name: 'example', start: root };
    `);
    const program = ts.createProgram([filename], {
      allowJs: true, checkJs: true, strict: true, noEmit: true,
      target: ts.ScriptTarget.ESNext,
      module: ts.ModuleKind.NodeNext,
      moduleResolution: ts.ModuleResolutionKind.NodeNext,
    });
    assert.deepEqual(ts.getPreEmitDiagnostics(program).map(diagnostic =>
      ts.flattenDiagnosticMessageText(diagnostic.messageText, '\n')), []);
  } finally {
    fs.rmSync(directory, {recursive: true, force: true});
  }
});

function languageService(sources, options = {}) {
  const files = new Map(Object.entries(sources).map(([name, text]) =>
    [path.join(__dirname, name), text]));
  const readFile = filename => files.get(filename) ?? ts.sys.readFile(filename);
  return ts.createLanguageService({
    getScriptFileNames: () => [...files.keys(), declarations],
    getScriptVersion: () => '0',
    getScriptSnapshot: filename => {
      const text = readFile(filename);
      return text === undefined ? undefined : ts.ScriptSnapshot.fromString(text);
    },
    getCurrentDirectory: () => __dirname,
    getCompilationSettings: () => ({
      allowJs: true,
      checkJs: true,
      strict: true,
      noEmit: true,
      target: ts.ScriptTarget.ESNext,
      module: ts.ModuleKind.NodeNext,
      moduleResolution: ts.ModuleResolutionKind.NodeNext,
      ...options,
    }),
    getDefaultLibFileName: ts.getDefaultLibFilePath,
    fileExists: filename => files.has(filename) || ts.sys.fileExists(filename),
    readFile,
    readDirectory: ts.sys.readDirectory,
    directoryExists: ts.sys.directoryExists,
  });
}

function diagnostics(service, filename) {
  return service.getSemanticDiagnostics(filename).map(diagnostic =>
    ts.flattenDiagnosticMessageText(diagnostic.messageText, '\n'));
}

for (const dom of [false, true]) {
  test(`external() is typed with DOM libraries ${dom ? 'enabled' : 'disabled'}`, () => {
    const name = 'external-grammar.mjs';
    const source = `
      export const newline = external();
      // @ts-expect-error External handles, like rule handles, are not callable.
      newline();
    `;
    const service = languageService({[name]: source}, {
      lib: dom ? ['lib.esnext.d.ts', 'lib.dom.d.ts'] : ['lib.esnext.d.ts'],
    });
    const filename = path.join(__dirname, name);
    assert.deepEqual(diagnostics(service, filename), []);
    assert.deepEqual(diagnostics(service, declarations), []);
    const info = service.getQuickInfoAtPosition(filename, source.indexOf('newline'));
    assert.match(ts.displayPartsToString(info.displayParts), /ExternalHandle/);
    service.dispose();
  });
}

for (const extension of ['mjs', 'mts']) {
  test(`${extension}: recursive handles retain types, definitions, references and rename`, () => {
    const baseName = `navigation-base.${extension}`;
    const derivedName = `navigation-derived.${extension}`;
    const base = `
      export const
        identifier = rule(() => /[a-z]+/),
        expression = rule(() => choice(identifier, expression, parenthesized)),
        parenthesized = rule(() => seq('(', expression, ')')),
        source_file = rule(() => repeat(expression)),
        type_identifier = rule(),
        aliased = rule(() => alias(identifier, type_identifier)),
        newline = external();

      /** @satisfies {ModuleGrammar} */
      export default {
        name: 'example', start: source_file, word: identifier, externals: [newline]
      };
    `;
    const derived = `
      import * as base from './navigation-base.mjs';
      export const identifier = override(base.identifier, () => /[a-z_]+/);
      /** @satisfies {ModuleGrammar} */
      export default { name: 'derived', extends: base };
    `;
    const service = languageService({ [baseName]: base, [derivedName]: derived });
    const baseFile = path.join(__dirname, baseName);
    const derivedFile = path.join(__dirname, derivedName);
    for (const filename of [baseFile, derivedFile, declarations]) {
      assert.deepEqual(diagnostics(service, filename), []);
    }

    for (const name of ['identifier', 'expression', 'parenthesized']) {
      const declaration = base.indexOf(`${name} =`);
      const reference = base.indexOf(name, base.indexOf('choice('));
      const definitions = service.getDefinitionAtPosition(baseFile, reference);
      assert.equal(definitions.length, 1);
      assert.equal(definitions[0].fileName, baseFile);
      assert.equal(definitions[0].textSpan.start, declaration);
      const references = service.getReferencesAtPosition(baseFile, declaration);
      assert.ok(references.some(r => r.textSpan.start === reference));
      const renames = service.findRenameLocations(baseFile, declaration, false, false);
      assert.ok(renames.some(r => r.textSpan.start === reference));
      const info = service.getQuickInfoAtPosition(baseFile, reference);
      assert.match(ts.displayPartsToString(info.displayParts), /RuleHandle/);
    }

    const aliasDeclaration = base.indexOf('type_identifier =');
    const aliasReference = base.indexOf('type_identifier', base.indexOf('alias(identifier'));
    const aliasDefinitions = service.getDefinitionAtPosition(baseFile, aliasReference);
    assert.equal(aliasDefinitions[0].textSpan.start, aliasDeclaration);
    assert.ok(service.findRenameLocations(baseFile, aliasDeclaration, false, false)
      .some(r => r.textSpan.start === aliasReference));

    const inheritedReference = derived.indexOf('base.identifier') + 'base.'.length;
    const definition = service.getDefinitionAtPosition(derivedFile, inheritedReference);
    assert.equal(definition[0].fileName, baseFile);
    assert.equal(definition[0].textSpan.start, base.indexOf('identifier ='));
    assert.ok(service.findRenameLocations(baseFile, base.indexOf('identifier ='), false, false)
      .some(r => r.fileName === derivedFile && r.textSpan.start === inheritedReference));
    service.dispose();
  });
}

test('handles cannot be called or forged, and root configuration requires a start', () => {
  const name = 'invalid-handles.mts';
  const service = languageService({
    [name]: `
      const item = rule(() => 'x');
      const aliasOnly = rule();
      const aliased = rule(() => alias(item, aliasOnly));
      // @ts-expect-error Handles are not callable.
      item();
      // @ts-expect-error Handles cannot be constructed outside the DSL.
      const forged: RuleHandle = {};
      // @ts-expect-error Helpers must be called, not passed as rule references.
      choice(() => 'x');
      // @ts-expect-error Root grammars require a start rule.
      const config: ModuleGrammar = { name: 'example' };
    `,
  });
  assert.deepEqual(diagnostics(service, path.join(__dirname, name)), []);
  service.dispose();
});

test('legacy callback grammars remain type-compatible', () => {
  const name = 'legacy-grammar.mjs';
  const service = languageService({
    [name]: `
      export default grammar({
        name: 'legacy',
        rules: {
          source_file: $ => repeat($.identifier),
          identifier: $ => /[a-z]+/,
        },
      });
    `,
  });
  assert.deepEqual(diagnostics(service, path.join(__dirname, name)), []);
  service.dispose();
});
