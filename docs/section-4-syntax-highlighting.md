---
title: Syntax Highlighting
permalink: syntax-highlighting
---

# Syntax Highlighting

Syntax highlighting is a very common feature in applications that deal with code. Tree-sitter has built-in support for syntax highlighting, via the [`tree-sitter-highlight`](https://github.com/tree-sitter/tree-sitter/tree/master/highlight) library. This system is currently used on GitHub.com for highlighting code written in several languages.

**Note - If you are working on syntax highlighting in the [Atom](https://atom.io/) text editor, you should consult [this page](https://flight-manual.atom.io/hacking-atom/sections/creating-a-grammar/) in the Atom Flight Manual. Atom currently uses a different syntax highlighting system that is also based on Tree-sitter, but is older than the one described in this document.**

## Overview

Tree-sitter's syntax highlighting system is based on *tree queries*, which are a general system for pattern-matching on Tree-sitter's syntax trees. See [this section](./using-parsers#pattern-matching-with-queries) of the documentation for more information about tree queries.

Syntax highlighting queries for a given language are normally included in the same git repository as the Tree-sitter grammar for that language, in a top-level directory called `queries`. For an example, see the `queries` directory in the [`tree-sitter-ruby` repository](https://github.com/tree-sitter/tree-sitter-ruby/tree/master/queries).

Highlighting is controlled by *three* different types of query files that can be included in the `queries` folder.

* The highlights query (required, with default name `highlights.scm`)
* The local variable query (optional, with default name `locals.scm`)
* The language injection query (optional, with default name `injections.scm`)

## Highlights Query

The most important query is called the highlights query. The highlights query uses *captures* to assign arbitrary *highlight names* to different nodes in the tree. Each highlight name can then be mapped to a color. Commonly used highlight names include `keyword`, `function`, `type`, `property`, and `string`. Names can also be dot-separated like `function.builtin`.

For example, consider the following Go code:

```go
func increment(a int) int {
    return a + 1
}
```

With this syntax tree:

```
(source_file
  (function_declaration
    name: (identifier)
    parameters: (parameter_list
      (parameter_declaration
        name: (identifier)
        type: (type_identifier)))
    result: (type_identifier)
    body: (block
      (return_statement
        (expression_list
          (binary_expression
            left: (identifier)
            right: (int_literal)))))))
```

Suppose we wanted to render this code with the following colors:
* keywords `func` and `return` in purple
* function `increment` in blue
* type `int` in green
* number `5` brown

We can assign each of these categories a *highlight name* using a query like this:

```
"func" @keyword
"return" @keyword

(function_declaration
  name: (identifier) @function)

(type_identifier) @type

(int_literal) @number
```

And we could map each of these highlight names to a color:

```json
{
  "theme": {
    "keyword": "purple",
    "function": "blue",
    "type": "green",
    "number": "brown"
  }
}
```

## Local Variable Query

Good syntax highlighting helps the reader to quickly distinguish between the different types of 'entities' in their code. Ideally, if a given entity appears in *multiple* places, it should be colored the same in each place. The Tree-sitter syntax highlighting system can help you to achieve this by keeping track of local scopes and variables.

The *local variables* query is different from the highlights query in that, while the highlights query uses *arbitrary* capture names which can then be mapped to colors, the locals variable query uses a fixed set of capture names, each of which has a special meaning.

The capture names are as follows:

* `@local.scope` - indicates that a syntax node introduces a new local scope.
* `@local.definition` - indicates that a syntax node contains the *name* of a definition within the current local scope.
* `@local.reference` - indicates that a syntax node contains the *name* which *may* refer to an earlier definition within some enclosing scope.

When highlighting a file, Tree-sitter will keep track of the set of scopes that contains any given position, and the set of definitions within each scope. When processing a syntax node that is captured as a `local.reference`, Tree-sitter will try to find a definition for a name that that matches the node's text. If it finds a match, Tree-sitter will ensure that the *reference* and the *definition* are colored the same.

For example, consider this Ruby code:

```
def increment_all(list)
  list.map do |item|
    item + 1
  end
end
```

## Language Injection Query
