import { describe, it, expect, beforeAll, beforeEach, afterEach } from "vitest";
import { Language, Tree, Edit } from "../src";
import { Parser } from "../src";
import helper from "./helper";

describe("node id stability", () => {
  let parser: Parser;
  let tree: Tree | null;
  let JavaScript: Language;

  beforeAll(async () => {
    ({ JavaScript } = await helper);
  });

  beforeEach(() => {
    tree = null;
    parser = new Parser();
    parser.setLanguage(JavaScript);
  });

  afterEach(() => {
    parser.delete();
    tree!.delete();
  });

  it("node ID of existing variable_declarator is stable after inserting second declaration", () => {
    const source1 = `
      let name = "John Doe";
    `;
    tree = parser.parse(source1);

    const variableDeclaratorsBefore = tree?.rootNode.descendantsOfType(
      "variable_declarator"
    );
    const firstDeclarationIdBefore = variableDeclaratorsBefore?.[0]?.id;

    expect(firstDeclarationIdBefore).toBeTypeOf("number");

    const source2 = `
      let age = 31;
    `;

    const startIndex = 0;
    const startPosition = { row: 0, column: 0 };
    const newEndPosition = { row: 1, column: 0 };

    const edit = new Edit({
      startIndex,
      oldEndIndex: startIndex,
      newEndIndex: startIndex + source2.length,
      startPosition,
      oldEndPosition: startPosition,
      newEndPosition,
    });

    tree?.edit(edit);

    const newText = source2 + source1;
    tree = parser.parse(newText, tree);

    const variableDeclaratorsAfter = tree?.rootNode.descendantsOfType(
      "variable_declarator"
    );
    const nodeIds = variableDeclaratorsAfter?.map((n) => n.id);

    expect(nodeIds).toContain(firstDeclarationIdBefore);
  });
});
