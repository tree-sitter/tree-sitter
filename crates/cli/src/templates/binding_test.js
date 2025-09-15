import assert from "node:assert";
import { test } from "node:test";
import Parser from "tree-sitter";
import language from "./index.js";

test("can load grammar", () => {
  const parser = new Parser();
  assert.doesNotThrow(() => parser.setLanguage(language));
});
