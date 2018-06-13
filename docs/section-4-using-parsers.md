---
title: Using Parsers
permalink: using-parsers
---

# Using Parsers

A Tree-sitter parser consists of a single C source file which exports one function with the naming scheme `tree_sitter_${LANGUAGE_NAME}`. This function returns a pointer to a `TSLanguage` struct, which can be used in conjunction with a `TSParser` to produce a syntax trees.

## The Raw C API

Here's an example of a simple C program that uses the Tree-sitter [JSON parser](https://github.com/tree-sitter/tree-sitter-json).

```c
// Filename - test-json-parser.c

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "tree_sitter/runtime.h"

TSLanguage *tree_sitter_json();

int main() {
  // Create a parser with the JSON language.
  TSParser *parser = ts_parser_new();
  ts_parser_set_language(parser, tree_sitter_json());

  // Parse some source code.
  const char *source_code = "[1, null]";
  TSTree *tree = ts_parser_parse_string(parser, NULL, source_code, strlen(source_code));

  // Find some syntax tree nodes.
  TSNode root_node = ts_tree_root_node(tree);
  TSNode array_node = ts_node_named_child(root_node, 0);
  TSNode number_node = ts_node_named_child(array_node, 0);

  // Check that the nodes have the expected types.
  assert(!strcmp(ts_node_type(root_node), "value"));
  assert(!strcmp(ts_node_type(array_node), "array"));
  assert(!strcmp(ts_node_type(number_node), "number"));

  // Check that the nodes have the expected child counts.
  assert(ts_node_child_count(root_node) == 1);
  assert(ts_node_child_count(array_node) == 4);
  assert(ts_node_named_child_count(array_node) == 2);
  assert(ts_node_child_count(number_node) == 0);

  // Print the syntax tree as an S-expression.
  char *string = ts_node_string(root_node);
  printf("Syntax tree: %s\n", string);

  // Free all of the heap allocations.
  free(string);
  ts_tree_delete(tree);
  ts_parser_delete(parser);
  return 0;
}
```

This program uses the Tree-sitter C API, which is declared in the header file `tree_sitter/runtime.h`, so we need to add the `tree_sitter/include` directory to the include path. We also need to link `libruntime.a` into the binary.

```sh
clang                                   \
  -I tree-sitter/include                \
  test-json-parser.c                    \
  tree-sitter-json/src/parser.c         \
  tree-sitter/out/Release/libruntime.a  \
  -o test-json-parser

./test-json-parser
```

### Providing the text to parse

Text input is provided to a tree-sitter parser via a `TSInput` struct, which contains function pointers for seeking to positions in the text, and for reading chunks of text. The text can be encoded in either UTF8 or UTF16. This interface allows you to efficiently parse text that is stored in your own data structure.

### Querying the syntax tree

Tree-sitter provides a DOM-style interface for inspecting syntax trees. Functions like `ts_node_child(node, index)` and `ts_node_next_sibling(node)` expose every node in the concrete syntax tree. This is useful for operations like syntax-highlighting, which operate on a token-by-token basis. You can also traverse the tree in a more abstract way by using functions like
`ts_node_named_child(node, index)` and `ts_node_next_named_sibling(node)`. These functions don't expose nodes that were specified in the grammar as anonymous tokens, like `:` and `{`. This is useful when analyzing the meaning of a document.
