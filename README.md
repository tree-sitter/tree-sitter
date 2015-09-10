# tree-sitter

[![Build Status](https://travis-ci.org/maxbrunsfeld/tree-sitter.png?branch=master)](https://travis-ci.org/maxbrunsfeld/tree-sitter)

Tree-sitter is an incremental parsing library in C and C++, intended to be used via [bindings](https://github.com/maxbrunsfeld/node-tree-sitter) to higher-level
languages. It allows documents to be efficiently re-parsed after localized
edits, making it suitable for use in performance-intensive text-editing programs.

Tree-sitter uses a sentential-form incremental [LR parsing](https://en.wikipedia.org/wiki/LR_parser)
algorithm, as described in the paper *[Efficient and Flexible Incremental Parsing](http://harmonia.cs.berkeley.edu/papers/twagner-parsing.ps.gz)*
by Tim Wagner. It handles ambiguity at compile-time via [precedence annotations](https://en.wikipedia.org/wiki/Operator-precedence_parser),
and at run-time via the [GLR algorithm](https://en.wikipedia.org/wiki/GLR_parser).
This allows it to generate a fast parser for any context-free grammar.

### Installation

```sh
script/configure.sh  # Generate a Makefile using gyp
make                 # Build static libraries for the compiler and runtime
```

### Writing a grammar

Tree-sitter's interface for creating grammars is a C++ library, `libcompiler`.
This allows grammars and rules to be defined, manipulated and
extended as simple values in high-level languages like [javascript](https://github.com/maxbrunsfeld/node-tree-sitter-compiler),
and then converted into tree-sitter's native representation and compiled to C
parsers. These parsers can then be used from any language that has a binding to
tree-sitter's runtime library, `libruntime`.

Here's a simple example that uses `libcompiler` directly:

```cpp
// arithmetic_grammar.cc

#include <assert.h>
#include <stdio.h>
#include "tree_sitter/compiler.h"

using namespace tree_sitter;

int main() {
  auto arithmetic_grammar = Grammar({

    // The first rule listed in a grammar becomes the 'start rule'.
    { "expression", choice({
      sym("sum"),
      sym("product"),
      sym("number"),
      sym("variable"),

      // Error recovery is controlled by wrapping rule subtrees with `err`.
      seq({
        str("("),
        err(sym("expression")),
        str(")") }) }) },

    // Tokens like '+' and '*' are described directly within the grammar's rules,
    // as opposed to in a seperate lexer description.
    { "sum", prec(1, seq({
      sym("expression"),
      str("+"),
      sym("expression") })) },

    // Ambiguities can be resolved at compile time by assigning precedence
    // values to rule subtrees.
    { "product", prec(2, seq({
      sym("expression"),
      str("*"),
      sym("expression") })) },

    // Tokens can be specified using ECMAScript regexps.
    { "number", pattern("\\d+") },
    { "variable", pattern("[a-zA-Z]+\\w*") },
    { "comment", pattern("//.*") },

  }).ubiquitous_tokens({

    // Things that can appear anywhere in the language are expressed as
    // 'ubiquitous tokens'.
    sym("comment"),
    pattern("\\s+")
  });

  // Generate C code for parsing this language.
  auto output = compile(arithmetic_grammar, "arithmetic");
  std::string c_code = output.first;
  const GrammarError *error = output.second;

  assert(!error);
  puts(c_code.c_str());

  return 0;
}
```

To create a parser for this language, compile and run this grammar like this:

```sh
clang++ -stdlib=libc++ -std=c++11                             \
  -I tree-sitter/include -L tree-sitter/out/Debug -l compiler \
  arithmetic_grammar.cc -o arithmetic_grammar

./arithmetic_grammar > arithmetic_parser.c

clang -I tree-sitter/include -c arithmetic_parser.c
```

### Using the parser

The `tree_sitter/runtime` C library exposes a DOM-style interface for inspecting
documents.

Functions like `ts_node_child(node, index)` and `ts_node_next_sibling(node)`
expose every node in the concrete syntax tree. This is useful for operations
like syntax-highlighting, that operate on a token-by-token basis. You can also
traverse the tree in a more abstract way by using functions like
`ts_node_named_child(node, index)` and `ts_node_next_named_sibling(node)`. These
functions don't expose nodes that were specified in the grammar as anonymous
tokens, like `(` and `+`. This is useful when analyzing the meaning of a document.

```c
#include <stdio.h>
#include "tree_sitter/runtime.h"

// Declare the language constructor that was generated from your grammar.
TSLanguage *ts_language_arithmetic();

int main() {
  TSDocument *document = ts_document_make();
  ts_document_set_language(document, ts_language_arithmetic());

  // Usually, you would use the more general `ts_document_set_input`, which
  // takes a struct with function pointers for seeking to positions in the text,
  // and reading chunks of text. This allows you to efficiently parse text
  // stored in your own data structure.
  ts_document_set_input_string(document, "a + b * 5");

  TSNode root_node = ts_document_root_node(document);
  printf(
    "Root name: %s, position: %lu, size: %lu\n",
    ts_node_name(root_node, document),
    ts_node_pos(root_node).chars,
    ts_node_size(root_node).chars
  );

  TSNode product_node = ts_node_named_child(ts_node_child(root_node, 0), 1);
  printf(
    "Child name: %s, position: %lu, size: %lu\n",
    ts_node_name(product_node, document),
    ts_node_pos(product_node).chars,
    ts_node_size(product_node).chars
  );

  ts_document_free(document);
  return 0;
}
```

To demo this parser's capabilities, compile this program like this:

```sh
clang                                                        \
  -I tree-sitter/include -L tree-sitter/out/Debug -l runtime \
  arithmetic_parser.o test_parser.c -o test_parser

./test_parser
```

### References

- [Context Aware Scanning for Parsing Extensible Languages](http://www.umsec.umn.edu/publications/Context-Aware-Scanning-Parsing-Extensible)
- [LR(1) Parser Generation System](http://arxiv.org/pdf/1010.1234.pdf)  (Error recovery scheme)
- [Efficient and Flexible Incremental Parsing](http://harmonia.cs.berkeley.edu/papers/twagner-parsing.ps.gz)
