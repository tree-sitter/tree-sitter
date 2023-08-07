---
title: Creating Parsers
permalink: creating-parsers
---

# Creating parsers

Developing Tree-sitter grammars can have a difficult learning curve, but once you get the hang of it, it can be fun and even zen-like. This document will help you to get started and to develop a useful mental model.

## Getting Started

### Dependencies

In order to develop a Tree-sitter parser, there are two dependencies that you need to install:

* **Node.js** - Tree-sitter grammars are written in JavaScript, and Tree-sitter uses [Node.js][node.js] to interpret JavaScript files. It requires the `node` command to be in one of the directories in your [`PATH`][path-env]. You'll need Node.js version 6.0 or greater.
* **A C Compiler** - Tree-sitter creates parsers that are written in C. In order to run and test these parsers with the `tree-sitter parse` or `tree-sitter test` commands, you must have a C/C++ compiler installed. Tree-sitter will try to look for these compilers in the standard places for each platform.

### Installation

To create a Tree-sitter parser, you need to use [the `tree-sitter` CLI][tree-sitter-cli]. You can install the CLI in a few different ways:

* Build the `tree-sitter-cli` [Rust crate][crate] from source using [`cargo`][cargo], the Rust package manager. This works on any platform. See [the contributing docs](./contributing#developing-tree-sitter) for more information.
* Install the `tree-sitter-cli` [Node.js module][node-module] using [`npm`][npm], the Node package manager. This approach is fast, but is only works on certain platforms, because it relies on pre-built binaries.
* Download a binary for your platform from [the latest GitHub release][releases], and put it into a directory on your `PATH`.

### Project Setup

The preferred convention is to name the parser repository "tree-sitter-" followed by the name of the language.

```sh
mkdir tree-sitter-${YOUR_LANGUAGE_NAME}
cd tree-sitter-${YOUR_LANGUAGE_NAME}
```

You can use the `npm` command line tool to create a `package.json` file that describes your project, and allows your parser to be used from Node.js.

```sh
# This will prompt you for input
npm init

# This installs a small module that lets your parser be used from Node
npm install --save nan

# This installs the Tree-sitter CLI itself
npm install --save-dev tree-sitter-cli
```

The last command will install the CLI into the `node_modules` folder in your working directory. An executable program called `tree-sitter` will be created inside of `node_modules/.bin/`. You may want to follow the Node.js convention of adding that folder to your `PATH` so that you can easily run this program when working in this directory.

```sh
# In your shell profile script
export PATH=$PATH:./node_modules/.bin
```

Once you have the CLI installed, create a file called `grammar.js` with the following contents:

```js
module.exports = grammar({
  name: 'YOUR_LANGUAGE_NAME',

  rules: {
    // TODO: add the actual grammar rules
    source_file: $ => 'hello'
  }
});
```

Then run the following command:

```sh
tree-sitter generate
```

This will generate the C code required to parse this trivial language, as well as a few files that are needed to compile and load this native parser as a Node.js module.

You can test this parser by creating a source file with the contents "hello" and parsing it:

```sh
echo 'hello' > example-file
tree-sitter parse example-file
```

Alternatively, in Windows PowerShell:

```pwsh
"hello" | Out-File example-file -Encoding utf8
tree-sitter parse example-file
```

This should print the following:

```text
(source_file [0, 0] - [1, 0])
```

You now have a working parser.

## Tool Overview

Let's go over all of the functionality of the `tree-sitter` command line tool.

### Command: `generate`

The most important command you'll use is `tree-sitter generate`. This command reads the `grammar.js` file in your current working directory and creates a file called `src/parser.c`, which implements the parser. After making changes to your grammar, just run `tree-sitter generate` again.

The first time you run `tree-sitter generate`, it will also generate a few other files:

* `binding.gyp` - This file tells Node.js how to compile your language.
* `bindings/node/index.js` - This is the file that Node.js initially loads when using your language.
* `bindings/node/binding.cc` - This file wraps your language in a JavaScript object when used in Node.js.
* `bindings/rust/lib.rs` - This file wraps your language in a Rust crate when used in Rust.
* `bindings/rust/build.rs` - This file wraps the building process for the Rust crate.
* `src/tree_sitter/parser.h` - This file provides some basic C definitions that are used in your generated `parser.c` file.

If there is an ambiguity or *local ambiguity* in your grammar, Tree-sitter will detect it during parser generation, and it will exit with a `Unresolved conflict` error message. See below for more information on these errors.

### Command: `test`

The `tree-sitter test` command allows you to easily test that your parser is working correctly.

For each rule that you add to the grammar, you should first create a *test* that describes how the syntax trees should look when parsing that rule. These tests are written using specially-formatted text files in the `corpus/` or `test/corpus/` directories within your parser's root folder.

For example, you might have a file called `test/corpus/statements.txt` that contains a series of entries like this:

```text
==================
Return statements
==================

func x() int {
  return 1;
}

---

(source_file
  (function_definition
    (identifier)
    (parameter_list)
    (primitive_type)
    (block
      (return_statement (number)))))
```

* The **name** of each test is written between two lines containing only `=` (equal sign) characters.
* Then the **input source code** is written, followed by a line containing three or more `-` (dash) characters.
* Then, the **expected output syntax tree** is written as an [S-expression][s-exp]. The exact placement of whitespace in the S-expression doesn't matter, but ideally the syntax tree should be legible. Note that the S-expression does not show syntax nodes like `func`, `(` and `;`, which are expressed as strings and regexes in the grammar. It only shows the *named* nodes, as described in [this section][named-vs-anonymous-nodes-section] of the page on parser usage.

  The expected output section can also *optionally* show the [*field names*][field-names-section] associated with each child node. To include field names in your tests, you write a node's field name followed by a colon, before the node itself in the S-expression:

```text
(source_file
  (function_definition
    name: (identifier)
    parameters: (parameter_list)
    result: (primitive_type)
    body: (block
      (return_statement (number)))))
```

* If your language's syntax conflicts with the `===` and `---` test separators, you can optionally add an arbitrary identical suffix (in the below example, `|||`) to disambiguate them:

```text
==================|||
Basic module
==================|||

---- MODULE Test ----
increment(n) == n + 1
====

---|||

(source_file
  (module (identifier)
    (operator (identifier)
      (parameter_list (identifier))
      (plus (identifier_ref) (number)))))
```

These tests are important. They serve as the parser's API documentation, and they can be run every time you change the grammar to verify that everything still parses correctly.

By default, the `tree-sitter test` command runs all of the tests in your `corpus` or `test/corpus/` folder. To run a particular test, you can use the `-f` flag:

```sh
tree-sitter test -f 'Return statements'
```

The recommendation is to be comprehensive in adding tests. If it's a visible node, add it to a test file in your `corpus` directory. It's typically a good idea to test all of the permutations of each language construct. This increases test coverage, but doubly acquaints readers with a way to examine expected outputs and understand the "edges" of a language.

#### Automatic Compilation

You might notice that the first time you run `tree-sitter test` after regenerating your parser, it takes some extra time. This is because Tree-sitter automatically compiles your C code into a dynamically-loadable library. It recompiles your parser as-needed whenever you update it by re-running `tree-sitter generate`.

#### Syntax Highlighting Tests

The `tree-sitter test` command will *also* run any syntax highlighting tests in the `test/highlight` folder, if it exists. For more information about syntax highlighting tests, see [the syntax highlighting page][syntax-highlighting-tests].

### Command: `parse`

You can run your parser on an arbitrary file using `tree-sitter parse`. This will print the resulting the syntax tree, including nodes' ranges and field names, like this:

```text
(source_file [0, 0] - [3, 0]
  (function_declaration [0, 0] - [2, 1]
    name: (identifier [0, 5] - [0, 9])
    parameters: (parameter_list [0, 9] - [0, 11])
    result: (type_identifier [0, 12] - [0, 15])
    body: (block [0, 16] - [2, 1]
      (return_statement [1, 2] - [1, 10]
        (expression_list [1, 9] - [1, 10]
          (int_literal [1, 9] - [1, 10]))))))
```

You can pass any number of file paths and glob patterns to `tree-sitter parse`, and it will parse all of the given files. The command will exit with a non-zero status code if any parse errors occurred. You can also prevent the syntax trees from being printed using the `--quiet` flag. Additionally, the `--stat` flag prints out aggregated parse success/failure information for all processed files. This makes `tree-sitter parse` usable as a secondary testing strategy: you can check that a large number of files parse without error:

```sh
tree-sitter parse 'examples/**/*.go' --quiet --stat
```

### Command: `highlight`

You can run syntax highlighting on an arbitrary file using `tree-sitter highlight`. This can either output colors directly to your terminal using ansi escape codes, or produce HTML (if the `--html` flag is passed). For more information, see [the syntax highlighting page][syntax-highlighting].

### The Grammar DSL

The following is a complete list of built-in functions you can use in your `grammar.js` to define rules. Use-cases for some of these functions will be explained in more detail in later sections.

* **Symbols (the `$` object)** - Every grammar rule is written as a JavaScript function that takes a parameter conventionally called `$`. The syntax `$.identifier` is how you refer to another grammar symbol within a rule. Names starting with `$.MISSING` or `$.UNEXPECTED` should be avoided as they have special meaning for the `tree-sitter test` command.
* **String and Regex literals** - The terminal symbols in a grammar are described using JavaScript strings and regular expressions. Of course during parsing, Tree-sitter does not actually use JavaScript's regex engine to evaluate these regexes; it generates its own regex-matching logic as part of each parser. Regex literals are just used as a convenient way of writing regular expressions in your grammar.
* **Regex Limitations** - Currently, only a subset of the Regex engine is actually
supported. This is due to certain features like lookahead and lookaround assertions
not feasible to use in an LR(1) grammar, as well as certain flags being unnecessary
for tree-sitter. However, plenty of features are supported by default:

  * Character classes
  * Character ranges
  * Character sets
  * Quantifiers
  * Alternation
  * Grouping
  * Unicode character escapes
  * Unicode property escapes

* **Sequences : `seq(rule1, rule2, ...)`** - This function creates a rule that matches any number of other rules, one after another. It is analogous to simply writing multiple symbols next to each other in [EBNF notation][ebnf].
* **Alternatives : `choice(rule1, rule2, ...)`** - This function creates a rule that matches *one* of a set of possible rules. The order of the arguments does not matter. This is analogous to the `|` (pipe) operator in EBNF notation.
* **Repetitions : `repeat(rule)`** - This function creates a rule that matches *zero-or-more* occurrences of a given rule. It is analogous to the `{x}` (curly brace) syntax in EBNF notation.
* **Repetitions : `repeat1(rule)`** - This function creates a rule that matches *one-or-more* occurrences of a given rule. The previous `repeat` rule is implemented in terms of `repeat1` but is included because it is very commonly used.
* **Options : `optional(rule)`** - This function creates a rule that matches *zero or one* occurrence of a given rule. It is analogous to the `[x]` (square bracket) syntax in EBNF notation.
* **Precedence : `prec(number, rule)`** - This function marks the given rule with a numerical precedence which will be used to resolve [*LR(1) Conflicts*][lr-conflict] at parser-generation time. When two rules overlap in a way that represents either a true ambiguity or a *local* ambiguity given one token of lookahead, Tree-sitter will try to resolve the conflict by matching the rule with the higher precedence. The default precedence of all rules is zero. This works similarly to the [precedence directives][yacc-prec] in Yacc grammars.
* **Left Associativity : `prec.left([number], rule)`** - This function marks the given rule as left-associative (and optionally applies a numerical precedence). When an LR(1) conflict arises in which all of the rules have the same numerical precedence, Tree-sitter will consult the rules' associativity. If there is a left-associative rule, Tree-sitter will prefer matching a rule that ends *earlier*. This works similarly to [associativity directives][yacc-prec] in Yacc grammars.
* **Right Associativity : `prec.right([number], rule)`** - This function is like `prec.left`, but it instructs Tree-sitter to prefer matching a rule that ends *later*.
* **Dynamic Precedence : `prec.dynamic(number, rule)`** - This function is similar to `prec`, but the given numerical precedence is applied at *runtime* instead of at parser generation time. This is only necessary when handling a conflict dynamically using the `conflicts` field in the grammar, and when there is a genuine *ambiguity*: multiple rules correctly match a given piece of code. In that event, Tree-sitter compares the total dynamic precedence associated with each rule, and selects the one with the highest total. This is similar to [dynamic precedence directives][bison-dprec] in Bison grammars.
* **Tokens : `token(rule)`** - This function marks the given rule as producing only
a single token. Tree-sitter's default is to treat each String or RegExp literal
in the grammar as a separate token. Each token is matched separately by the lexer
and returned as its own leaf node in the tree. The `token` function allows you to
express a complex rule using the functions described above (rather than as a single
regular expression) but still have Tree-sitter treat it as a single token.
The token function will only accept terminal rules, so `token($.foo)` will not work.
You can think of it as a shortcut for squashing complex rules of strings or regexes
down to a single token.
* **Immediate Tokens : `token.immediate(rule)`** - Usually, whitespace (and any other extras, such as comments) is optional before each token. This function means that the token will only match if there is no whitespace.
* **Aliases : `alias(rule, name)`** - This function causes the given rule to *appear* with an alternative name in the syntax tree. If `name` is a *symbol*, as in `alias($.foo, $.bar)`, then the aliased rule will *appear* as a [named node][named-vs-anonymous-nodes-section] called `bar`. And if `name` is a *string literal*, as in `alias($.foo, 'bar')`, then the aliased rule will appear as an [anonymous node][named-vs-anonymous-nodes-section], as if the rule had been written as the simple string.
* **Field Names : `field(name, rule)`** - This function assigns a *field name* to the child node(s) matched by the given rule. In the resulting syntax tree, you can then use that field name to access specific children.

In addition to the `name` and `rules` fields, grammars have a few other optional public fields that influence the behavior of the parser.

* **`extras`** - an array of tokens that may appear *anywhere* in the language. This is often used for whitespace and comments. The default value of `extras` is to accept whitespace. To control whitespace explicitly, specify `extras: $ => []` in your grammar.
* **`inline`** - an array of rule names that should be automatically *removed* from the grammar by replacing all of their usages with a copy of their definition. This is useful for rules that are used in multiple places but for which you *don't* want to create syntax tree nodes at runtime.
* **`conflicts`** - an array of arrays of rule names. Each inner array represents a set of rules that's involved in an *LR(1) conflict* that is *intended to exist* in the grammar. When these conflicts occur at runtime, Tree-sitter will use the GLR algorithm to explore all of the possible interpretations. If *multiple* parses end up succeeding, Tree-sitter will pick the subtree whose corresponding rule has the highest total *dynamic precedence*.
* **`externals`** - an array of token names which can be returned by an [*external scanner*](#external-scanners). External scanners allow you to write custom C code which runs during the lexing process in order to handle lexical rules (e.g. Python's indentation tokens) that cannot be described by regular expressions.
* **`precedences`** - an array of array of strings, where each array of strings defines named precedence levels in descending order. These names can be used in the `prec` functions to define precedence relative only to other names in the array, rather than globally. Can only be used with parse precedence, not lexical precedence.
* **`word`** - the name of a token that will match keywords for the purpose of the [keyword extraction](#keyword-extraction) optimization.
* **`supertypes`** an array of hidden rule names which should be considered to be 'supertypes' in the generated [*node types* file][static-node-types].

## Writing the Grammar

Writing a grammar requires creativity. There are an infinite number of CFGs (context-free grammars) that can be used to describe any given language. In order to produce a good Tree-sitter parser, you need to create a grammar with two important properties:

1. **An intuitive structure** - Tree-sitter's output is a [concrete syntax tree][cst]; each node in the tree corresponds directly to a [terminal or non-terminal symbol][non-terminal] in the grammar. So in order to produce an easy-to-analyze tree, there should be a direct correspondence between the symbols in your grammar and the recognizable constructs in the language. This might seem obvious, but it is very different from the way that context-free grammars are often written in contexts like [language specifications][language-spec] or [Yacc][yacc]/[Bison][bison] parsers.

2. **A close adherence to LR(1)** - Tree-sitter is based on the [GLR parsing][glr-parsing] algorithm. This means that while it can handle any context-free grammar, it works most efficiently with a class of context-free grammars called [LR(1) Grammars][lr-grammars]. In this respect, Tree-sitter's grammars are similar to (but less restrictive than) [Yacc][yacc] and [Bison][bison] grammars, but *different* from [ANTLR grammars][antlr], [Parsing Expression Grammars][peg], or the [ambiguous grammars][ambiguous-grammar] commonly used in language specifications.

It's unlikely that you'll be able to satisfy these two properties just by translating an existing context-free grammar directly into Tree-sitter's grammar format. There are a few kinds of adjustments that are often required. The following sections will explain these adjustments in more depth.

### The First Few Rules

It's usually a good idea to find a formal specification for the language you're trying to parse. This specification will most likely contain a context-free grammar. As you read through the rules of this CFG, you will probably discover a complex and cyclic graph of relationships. It might be unclear how you should navigate this graph as you define your grammar.

Although languages have very different constructs, their constructs can often be categorized in to similar groups like *Declarations*, *Definitions*, *Statements*, *Expressions*, *Types*, and *Patterns*. In writing your grammar, a good first step is to create just enough structure to include all of these basic *groups* of symbols. For a language like Go, you might start with something like this:

```js
{
  // ...

  rules: {
    source_file: $ => repeat($._definition),

    _definition: $ => choice(
      $.function_definition
      // TODO: other kinds of definitions
    ),

    function_definition: $ => seq(
      'func',
      $.identifier,
      $.parameter_list,
      $._type,
      $.block
    ),

    parameter_list: $ => seq(
      '(',
       // TODO: parameters
      ')'
    ),

    _type: $ => choice(
      'bool'
      // TODO: other kinds of types
    ),

    block: $ => seq(
      '{',
      repeat($._statement),
      '}'
    ),

    _statement: $ => choice(
      $.return_statement
      // TODO: other kinds of statements
    ),

    return_statement: $ => seq(
      'return',
      $._expression,
      ';'
    ),

    _expression: $ => choice(
      $.identifier,
      $.number
      // TODO: other kinds of expressions
    ),

    identifier: $ => /[a-z]+/,

    number: $ => /\d+/
  }
}
```

Some of the details of this grammar will be explained in more depth later on, but if you focus on the `TODO` comments, you can see that the overall strategy is *breadth-first*. Notably, this initial skeleton does not need to directly match an exact subset of the context-free grammar in the language specification. It just needs to touch on the major groupings of rules in as simple and obvious a way as possible.

With this structure in place, you can now freely decide what part of the grammar to flesh out next. For example, you might decide to start with *types*. One-by-one, you could define the rules for writing basic types and composing them into more complex types:

```js
{
  // ...

  _type: $ => choice(
    $.primitive_type,
    $.array_type,
    $.pointer_type
  ),

  primitive_type: $ => choice(
    'bool',
    'int'
  ),

  array_type: $ => seq(
    '[',
    ']',
    $._type
  ),

  pointer_type: $ => seq(
    '*',
    $._type
  )
}
```

After developing the *type* sublanguage a bit further, you might decide to switch to working on *statements* or *expressions* instead. It's often useful to check your progress by trying to parse some real code using `tree-sitter parse`.

**And remember to add tests for each rule in your `corpus` folder!**

### Structuring Rules Well

Imagine that you were just starting work on the [Tree-sitter JavaScript parser][tree-sitter-javascript]. Naively, you might try to directly mirror the structure of the [ECMAScript Language Spec][ecmascript-spec]. To illustrate the problem with this approach, consider the following line of code:

```js
return x + y;
```

According to the specification, this line is a `ReturnStatement`, the fragment `x + y` is an `AdditiveExpression`, and `x` and `y` are both `IdentifierReferences`. The relationship between these constructs is captured by a complex series of production rules:

```text
ReturnStatement          ->  'return' Expression
Expression               ->  AssignmentExpression
AssignmentExpression     ->  ConditionalExpression
ConditionalExpression    ->  LogicalORExpression
LogicalORExpression      ->  LogicalANDExpression
LogicalANDExpression     ->  BitwiseORExpression
BitwiseORExpression      ->  BitwiseXORExpression
BitwiseXORExpression     ->  BitwiseANDExpression
BitwiseANDExpression     ->  EqualityExpression
EqualityExpression       ->  RelationalExpression
RelationalExpression     ->  ShiftExpression
ShiftExpression          ->  AdditiveExpression
AdditiveExpression       ->  MultiplicativeExpression
MultiplicativeExpression ->  ExponentiationExpression
ExponentiationExpression ->  UnaryExpression
UnaryExpression          ->  UpdateExpression
UpdateExpression         ->  LeftHandSideExpression
LeftHandSideExpression   ->  NewExpression
NewExpression            ->  MemberExpression
MemberExpression         ->  PrimaryExpression
PrimaryExpression        ->  IdentifierReference
```

The language spec encodes the twenty different precedence levels of JavaScript expressions using twenty levels of indirection between `IdentifierReference` and `Expression`. If we were to create a concrete syntax tree representing this statement according to the language spec, it would have twenty levels of nesting, and it would contain nodes with names like `BitwiseXORExpression`, which are unrelated to the actual code.

### Using Precedence

To produce a readable syntax tree, we'd like to model JavaScript expressions using a much flatter structure like this:

```js
{
  // ...

  _expression: $ => choice(
    $.identifier,
    $.unary_expression,
    $.binary_expression,
    // ...
  ),

  unary_expression: $ => choice(
    seq('-', $._expression),
    seq('!', $._expression),
    // ...
  ),

  binary_expression: $ => choice(
    seq($._expression, '*', $._expression),
    seq($._expression, '+', $._expression),
    // ...
  ),
}
```

Of course, this flat structure is highly ambiguous. If we try to generate a parser, Tree-sitter gives us an error message:

```text
Error: Unresolved conflict for symbol sequence:

  '-'  _expression  •  '*'  …

Possible interpretations:

  1:  '-'  (binary_expression  _expression  •  '*'  _expression)
  2:  (unary_expression  '-'  _expression)  •  '*'  …

Possible resolutions:

  1:  Specify a higher precedence in `binary_expression` than in the other rules.
  2:  Specify a higher precedence in `unary_expression` than in the other rules.
  3:  Specify a left or right associativity in `unary_expression`
  4:  Add a conflict for these rules: `binary_expression` `unary_expression`
```

For an expression like `-a * b`, it's not clear whether the `-` operator applies to the `a * b` or just to the `a`. This is where the `prec` function [described above](#the-grammar-dsl) comes into play. By wrapping a rule with `prec`, we can indicate that certain sequence of symbols should *bind to each other more tightly* than others. For example, the `'-', $._expression` sequence in `unary_expression` should bind more tightly than the `$._expression, '+', $._expression` sequence in `binary_expression`:

```js
{
  // ...

  unary_expression: $ => prec(2, choice(
    seq('-', $._expression),
    seq('!', $._expression),
    // ...
  ))
}
```

### Using Associativity

Applying a higher precedence in `unary_expression` fixes that conflict, but there is still another conflict:

```text
Error: Unresolved conflict for symbol sequence:

  _expression  '*'  _expression  •  '*'  …

Possible interpretations:

  1:  _expression  '*'  (binary_expression  _expression  •  '*'  _expression)
  2:  (binary_expression  _expression  '*'  _expression)  •  '*'  …

Possible resolutions:

  1:  Specify a left or right associativity in `binary_expression`
  2:  Add a conflict for these rules: `binary_expression`
```

For an expression like `a * b * c`, it's not clear whether we mean `a * (b * c)` or `(a * b) * c`. This is where `prec.left` and `prec.right` come into use. We want to select the second interpretation, so we use `prec.left`.

```js
{
  // ...

  binary_expression: $ => choice(
    prec.left(2, seq($._expression, '*', $._expression)),
    prec.left(1, seq($._expression, '+', $._expression)),
    // ...
  ),
}
```

### Hiding Rules

You may have noticed in the above examples that some of the grammar rule name like `_expression` and `_type` began with an underscore. Starting a rule's name with an underscore causes the rule to be *hidden* in the syntax tree. This is useful for rules like `_expression` in the grammars above, which always just wrap a single child node. If these nodes were not hidden, they would add substantial depth and noise to the syntax tree without making it any easier to understand.

### Using Fields

Often, it's easier to analyze a syntax nodes if you can refer to its children by *name* instead of by their position in an ordered list. Tree-sitter grammars support this using the `field` function. This function allows you to assign unique names to some or all of a node's children:

```js
function_definition: $ => seq(
  'func',
  field('name', $.identifier),
  field('parameters', $.parameter_list),
  field('return_type', $._type),
  field('body', $.block)
)
```

Adding fields like this allows you to retrieve nodes using the [field APIs][field-names-section].

## Lexical Analysis

Tree-sitter's parsing process is divided into two phases: parsing (which is described above) and [lexing][lexing] - the process of grouping individual characters into the language's fundamental *tokens*. There are a few important things to know about how Tree-sitter's lexing works.

### Conflicting Tokens

Grammars often contain multiple tokens that can match the same characters. For example, a grammar might contain the tokens (`"if"` and `/[a-z]+/`). Tree-sitter differentiates between these conflicting tokens in a few ways.

1. **Context-aware Lexing** - Tree-sitter performs lexing on-demand, during the parsing process. At any given position in a source document, the lexer only tries to recognize tokens that are *valid* at that position in the document.

2. **Lexical Precedence** - When the precedence functions described [above](#the-grammar-dsl) are used *within* the `token` function, the given explicit precedence values serve as instructions to the lexer. If there are two valid tokens that match the characters at a given position in the document, Tree-sitter will select the one with the higher precedence.

3. **Match Length** - If multiple valid tokens with the same precedence match the characters at a given position in a document, Tree-sitter will select the token that matches the [longest sequence of characters][longest-match].

4. **Match Specificity** - If there are two valid tokens with the same precedence and which both match the same number of characters, Tree-sitter will prefer a token that is specified in the grammar as a `String` over a token specified as a `RegExp`.

5. **Rule Order** - If none of the above criteria can be used to select one token over another, Tree-sitter will prefer the token that appears earlier in the grammar.

If there is an external scanner it may have [an additional impact](#other-external-scanner-details) over regular tokens defined in the grammar.

### Lexical Precedence vs. Parse Precedence

One common mistake involves not distinguishing *lexical precedence* from *parse precedence*. Parse precedence determines which rule is chosen to interpret a given sequence of tokens. *Lexical precedence* determines which token is chosen to interpret at a given position of text and it is a lower-level operation that is done first. The above list fully captures Tree-sitter's lexical precedence rules, and you will probably refer back to this section of the documentation more often than any other. Most of the time when you really get stuck, you're dealing with a lexical precedence problem. Pay particular attention to the difference in meaning between using `prec` inside of the `token` function versus outside of it. The *lexical precedence* syntax is `token(prec(N, ...))`.

### Keywords

Many languages have a set of *keyword* tokens (e.g. `if`, `for`, `return`), as well as a more general token (e.g. `identifier`) that matches any word, including many of the keyword strings. For example, JavaScript has a keyword `instanceof`, which is used as a binary operator, like this:

```js
if (a instanceof Something) b();
```

The following, however, is not valid JavaScript:

```js
if (a instanceofSomething) b();
```

A keyword like `instanceof` cannot be followed immediately by another letter, because then it would be tokenized as an `identifier`, **even though an identifier is not valid at that position**. Because Tree-sitter uses context-aware lexing, as described [above](#conflicting-tokens), it would not normally impose this restriction. By default, Tree-sitter would recognize `instanceofSomething` as two separate tokens: the `instanceof` keyword followed by an `identifier`.

### Keyword Extraction

Fortunately, Tree-sitter has a feature that allows you to fix this, so that you can match the behavior of other standard parsers: the `word` token. If you specify a `word` token in your grammar, Tree-sitter will find the set of *keyword* tokens that match strings also matched by the `word` token. Then, during lexing, instead of matching each of these keywords individually, Tree-sitter will match the keywords via a two-step process where it *first* matches the `word` token.

For example, suppose we added `identifier` as the `word` token in our JavaScript grammar:

```js
grammar({
  name: 'javascript',

  word: $ => $.identifier,

  rules: {
    _expression: $ => choice(
      $.identifier,
      $.unary_expression,
      $.binary_expression
      // ...
    ),

    binary_expression: $ => choice(
      prec.left(1, seq($._expression, 'instanceof', $._expression))
      // ...
    ),

    unary_expression: $ => choice(
      prec.left(2, seq('typeof', $._expression))
      // ...
    ),

    identifier: $ => /[a-z_]+/
  }
});
```

Tree-sitter would identify `typeof` and `instanceof` as keywords. Then, when parsing the invalid code above, rather than scanning for the `instanceof` token individually, it would scan for an `identifier` first, and find `instanceofSomething`. It would then correctly recognize the code as invalid.

Aside from improving error detection, keyword extraction also has performance benefits. It allows Tree-sitter to generate a smaller, simpler lexing function, which means that **the parser will compile much more quickly**.

### External Scanners

Many languages have some tokens whose structure is impossible or inconvenient to describe with a regular expression. Some examples:

* [Indent and dedent][indent-tokens] tokens in Python
* [Heredocs][heredoc] in Bash and Ruby
* [Percent strings][percent-string] in Ruby

Tree-sitter allows you to handle these kinds of tokens using *external scanners*. An external scanner is a set of C functions that you, the grammar author, can write by hand in order to add custom logic for recognizing certain tokens.

To use an external scanner, there are a few steps. First, add an `externals` section to your grammar. This section should list the names of all of your external tokens. These names can then be used elsewhere in your grammar.

```js
grammar({
  name: 'my_language',

  externals: $ => [
    $.indent,
    $.dedent,
    $.newline
  ],

  // ...
});
```

Then, add another C or C++ source file to your project. Currently, its path must be `src/scanner.c` or `src/scanner.cc` for the CLI to recognize it. Be sure to add this file to the `sources` section of your `binding.gyp` file so that it will be included when your project is compiled by Node.js and uncomment the appropriate block in your `bindings/rust/build.rs` file so that it will be included in your Rust crate.

> **Note**
> While it is possible to write an external scanner in C++, it can be difficult to get working cross-platform and introduces extra requirements; therefore it is *greatly* preferred to use C.

In this new source file, define an [`enum`][enum] type containing the names of all of your external tokens. The ordering of this enum must match the order in your grammar's `externals` array; the actual names do not matter.

```c
#include <tree_sitter/parser.h>

enum TokenType {
  INDENT,
  DEDENT,
  NEWLINE
}
```

Finally, you must define five functions with specific names, based on your language's name and five actions: *create*, *destroy*, *serialize*, *deserialize*, and *scan*. These functions must all use [C linkage][c-linkage], so if you're writing the scanner in C++, you need to declare them with the `extern "C"` qualifier.

#### Create

```c
void * tree_sitter_my_language_external_scanner_create() {
  // ...
}
```

This function should create your scanner object. It will only be called once anytime your language is set on a parser. Often, you will want to allocate memory on the heap and return a pointer to it. If your external scanner doesn't need to maintain any state, it's ok to return `NULL`.

#### Destroy

```c
void tree_sitter_my_language_external_scanner_destroy(void *payload) {
  // ...
}
```

This function should free any memory used by your scanner. It is called once when a parser is deleted or assigned a different language. It receives as an argument the same pointer that was returned from the *create* function. If your *create* function didn't allocate any memory, this function can be a noop.

#### Serialize

```c
unsigned tree_sitter_my_language_external_scanner_serialize(
  void *payload,
  char *buffer
) {
  // ...
}
```

This function should copy the complete state of your scanner into a given byte buffer, and return the number of bytes written. The function is called every time the external scanner successfully recognizes a token. It receives a pointer to your scanner and a pointer to a buffer. The maximum number of bytes that you can write is given by the `TREE_SITTER_SERIALIZATION_BUFFER_SIZE` constant, defined in the `tree_sitter/parser.h` header file.

The data that this function writes will ultimately be stored in the syntax tree so that the scanner can be restored to the right state when handling edits or ambiguities. For your parser to work correctly, the `serialize` function must store its entire state, and `deserialize` must restore the entire state. For good performance, you should design your scanner so that its state can be serialized as quickly and compactly as possible.

#### Deserialize

```c
void tree_sitter_my_language_external_scanner_deserialize(
  void *payload,
  const char *buffer,
  unsigned length
) {
  // ...
}
```

This function should *restore* the state of your scanner based the bytes that were previously written by the `serialize` function. It is called with a pointer to your scanner, a pointer to the buffer of bytes, and the number of bytes that should be read.
It is good practice to explicitly erase your scanner state variables at the start of this function, before restoring their values from the byte buffer.

#### Scan

```c
bool tree_sitter_my_language_external_scanner_scan(
  void *payload,
  TSLexer *lexer,
  const bool *valid_symbols
) {
  // ...
}
```

This function is responsible for recognizing external tokens. It should return `true` if a token was recognized, and `false` otherwise. It is called with a "lexer" struct with the following fields:

* **`int32_t lookahead`** - The current next character in the input stream, represented as a 32-bit unicode code point.
* **`TSSymbol result_symbol`** - The symbol that was recognized. Your scan function should *assign* to this field one of the values from the `TokenType` enum, described above.
* **`void (*advance)(TSLexer *, bool skip)`** - A function for advancing to the next character. If you pass `true` for the second argument, the current character will be treated as whitespace; whitespace won't be included in the text range associated with tokens emitted by the external scanner.
* **`void (*mark_end)(TSLexer *)`** - A function for marking the end of the recognized token. This allows matching tokens that require multiple characters of lookahead. By default (if you don't call `mark_end`), any character that you moved past using the `advance` function will be included in the size of the token. But once you call `mark_end`, then any later calls to `advance` will *not* increase the size of the returned token. You can call `mark_end` multiple times to increase the size of the token.
* **`uint32_t (*get_column)(TSLexer *)`** - A function for querying the current column position of the lexer. It returns the number of codepoints since the start of the current line. The codepoint position is recalculated on every call to this function by reading from the start of the line.
* **`bool (*is_at_included_range_start)(const TSLexer *)`** - A function for checking whether the parser has just skipped some characters in the document. When parsing an embedded document using the `ts_parser_set_included_ranges` function (described in the [multi-language document section][multi-language-section]), the scanner may want to apply some special behavior when moving to a disjoint part of the document. For example, in [EJS documents][ejs], the JavaScript parser uses this function to enable inserting automatic semicolon tokens in between the code directives, delimited by `<%` and `%>`.
* **`bool (*eof)(const TSLexer *)`** - A function for determining whether the lexer is at the end of the file. The value of `lookahead` will be `0` at the end of a file, but this function should be used instead of checking for that value because the `0` or "NUL" value is also a valid character that could be present in the file being parsed.

The third argument to the `scan` function is an array of booleans that indicates which of external tokens are currently expected by the parser. You should only look for a given token if it is valid according to this array. At the same time, you cannot backtrack, so you may need to combine certain pieces of logic.

```c
if (valid_symbols[INDENT] || valid_symbols[DEDENT]) {

  // ... logic that is common to both `INDENT` and `DEDENT`

  if (valid_symbols[INDENT]) {

    // ... logic that is specific to `INDENT`

    lexer->result_symbol = INDENT;
    return true;
  }
}
```

#### Other External Scanner Details

If a token in the `externals` array is valid at a given position in the parse, the external scanner will be called first before anything else is done. This means the external scanner functions as a powerful override of Tree-sitter's lexing behavior, and can be used to solve problems that can't be cracked with ordinary lexical, parse, or dynamic precedence.

If a syntax error is encountered during regular parsing, Tree-sitter's first action during error recovery will be to call the external scanner's `scan` function with all tokens marked valid. The scanner should detect this case and handle it appropriately. One simple method of detection is to add an unused token to the end of the `externals` array, for example `externals: $ => [$.token1, $.token2, $.error_sentinel]`, then check whether that token is marked valid to determine whether Tree-sitter is in error correction mode.

If you put terminal keywords in the `externals` array, for example `externals: $ => ['if', 'then', 'else']`, then any time those terminals are present in the grammar they will be tokenized by the external scanner. It is similar to writing `externals: [$.if_keyword, $.then_keyword, $.else_keyword]` then using `alias($.if_keyword, 'if')` in the grammar.

If in the `externals` array use literal keywords then lexing works in two steps, the external scanner will be called first and if it sets a resulting token and returns `true` then the token considered as recognized and Tree-sitter moves to a next token. But the external scanner may return `false` and in this case Tree-sitter fallbacks to the internal lexing mechanism.

In case of some keywords defined in the `externals` array in a rule referencing form like `$.if_keyword` and there is no additional definition of that rule in the grammar rules, e.g., `if_keyword: $ => 'if'` then fallback to the internal lexer isn't possible because Tree-sitter doesn't know the actual keyword and it's fully the external scanner resposibilty to recognize such tokens.

External scanners are a common cause of infinite loops.
Be very careful when emitting zero-width tokens from your external scanner, and if you consume characters in a loop be sure use the `eof` function to check whether you are at the end of the file.

[ambiguous-grammar]: https://en.wikipedia.org/wiki/Ambiguous_grammar
[antlr]: https://www.antlr.org
[bison-dprec]: https://www.gnu.org/software/bison/manual/html_node/Generalized-LR-Parsing.html
[bison]: https://en.wikipedia.org/wiki/GNU_bison
[c-linkage]: https://en.cppreference.com/w/cpp/language/language_linkage
[cargo]: https://doc.rust-lang.org/cargo/getting-started/installation.html
[crate]: https://crates.io/crates/tree-sitter-cli
[cst]: https://en.wikipedia.org/wiki/Parse_tree
[dfa]: https://en.wikipedia.org/wiki/Deterministic_finite_automaton
[ebnf]: https://en.wikipedia.org/wiki/Extended_Backus%E2%80%93Naur_form
[ecmascript-spec]: https://262.ecma-international.org/6.0/
[ejs]: https://ejs.co
[enum]: https://en.wikipedia.org/wiki/Enumerated_type#C
[glr-parsing]: https://en.wikipedia.org/wiki/GLR_parser
[heredoc]: https://en.wikipedia.org/wiki/Here_document
[indent-tokens]: https://en.wikipedia.org/wiki/Off-side_rule
[language-spec]: https://en.wikipedia.org/wiki/Programming_language_specification
[lexing]: https://en.wikipedia.org/wiki/Lexical_analysis
[longest-match]: https://en.wikipedia.org/wiki/Maximal_munch
[lr-conflict]: https://en.wikipedia.org/wiki/LR_parser#Conflicts_in_the_constructed_tables
[lr-grammars]: https://en.wikipedia.org/wiki/LR_parser
[multi-language-section]: ./using-parsers#multi-language-documents
[named-vs-anonymous-nodes-section]: ./using-parsers#named-vs-anonymous-nodes
[field-names-section]: ./using-parsers#node-field-names
[nan]: https://github.com/nodejs/nan
[node-module]: https://www.npmjs.com/package/tree-sitter-cli
[node.js]: https://nodejs.org
[static-node-types]: ./using-parsers#static-node-types
[non-terminal]: https://en.wikipedia.org/wiki/Terminal_and_nonterminal_symbols
[npm]: https://docs.npmjs.com
[path-env]: https://en.wikipedia.org/wiki/PATH_(variable)
[peg]: https://en.wikipedia.org/wiki/Parsing_expression_grammar
[percent-string]: https://docs.ruby-lang.org/en/2.5.0/doc/syntax/literals_rdoc.html#label-Percent+Strings
[releases]: https://github.com/tree-sitter/tree-sitter/releases/latest
[s-exp]: https://en.wikipedia.org/wiki/S-expression
[syntax-highlighting]: ./syntax-highlighting
[syntax-highlighting-tests]: ./syntax-highlighting#unit-testing
[tree-sitter-cli]: https://github.com/tree-sitter/tree-sitter/tree/master/cli
[tree-sitter-javascript]: https://github.com/tree-sitter/tree-sitter-javascript
[yacc-prec]: https://docs.oracle.com/cd/E19504-01/802-5880/6i9k05dh3/index.html
[yacc]: https://en.wikipedia.org/wiki/Yacc
