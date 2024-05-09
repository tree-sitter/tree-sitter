/// <reference types="tree-sitter-cli/dsl" />
// @ts-check

module.exports = grammar({
  name: "LOWER_PARSER_NAME",

  rules: {
    // TODO: add the actual grammar rules
    source_file: $ => "hello"
  }
});
