---
title: Creating Parsers
permalink: creating-parsers
---

# Creating parsers

Developing Tree-sitter parsers can have a difficult learning curve, but once you get the hang of it, it can be fun and even zen-like. This document should help you to build an effective mental model for parser development.

## Understanding the problem

Writing a grammar requires creativity. There are an infinite number of CFGs (context-free grammars) that can be used to describe any given language. In order to produce a good Tree-sitter parser, you need to create a grammar with two important properties:

  1. **An intuitive structure** - Tree-sitter's output is a [concrete syntax tree][cst]; each node in the tree corresponds directly to a [terminal or non-terminal symbol][non-terminal] in the grammar. So in order to produce an easy-to-analyze tree, there should be a direct correspondence between the symbols in your grammar and the recognizable constructs in the language. This might seem obvious, but it is very different from the way that context-free grammars are often written in contexts like [language specifications][language-spec] or [Yacc][yacc]/[Bison][bison] parsers.

  2. **A close adherence to LR(1)** - Tree-sitter is based on the [GLR parsing][glr-parsing] algorithm. This means that while it can handle any context-free grammar, it works most efficiently with a class of context-free grammars called [LR(1) Grammars][lr-grammars]. In this respect, Tree-sitter's grammars are similar to (but less restrictive than) [Yacc][yacc] and [Bison][bison] grammars, but *different* from [ANTLR grammars][antlr], [Parsing Expression Grammars][peg], or the [ambiguous grammars][ambiguous-grammar] commonly used in language specifications.

It's unlikely that you'll be able to satisfy these two properties just by translating an existing context-free grammar directly into Tree-sitter's grammar format. There are a few kinds of adjustments that are often required. The following sections will explain these adjustments in more depth.

## Installing the tools

The best way to create a Tree-sitter parser is with the [`Tree-sitter CLI`][tree-sitter-cli], which is distributed as [a Node.js module][node-module]. To install it, first install [`node`][node.js] and its package manager [`npm`][npm] on your system. Then use `npm` to create a new node module and add `tree-sitter-cli` and [`nan`][nan] as dependencies:

```sh
mkdir tree-sitter-${YOUR_LANGUAGE_NAME}
cd tree-sitter-${YOUR_LANGUAGE_NAME}

# This will prompt you for input
npm init

npm install --save nan
npm install --save-dev tree-sitter-cli
```

This will install the CLI and its dependencies into the `node_modules` folder in your directory. An executable program called `tree-sitter` will be created at the path `./node_modules/.bin/tree-sitter`. You may want to follow the Node.js convention of adding `./node_modules/.bin` to your `PATH` so that you can easily run this program when working in this directory.

Once you have the CLI installed, create a file called `grammar.js` with the following skeleton:

```js
module.exports = grammar({
  name: 'the_language_name',

  rules: {
    // The production rules of the context-free grammar
    source_file: $ => 'hello'
  }
});
```

Then run the the following command:

```sh
tree-sitter generate
npm install
```

This will generate the C code required to parse this trivial language, as well as all of the files needed to compile and load this native parser as a Node.js module. You can test this parser by creating a source file with the contents `hello;` and parsing it:

```sh
tree-sitter parse ./the-file
```

This should print:
```
(source_file [0, 0] - [0, 5])
```

When you make changes to the grammar, you can update the parser simply by re-running `tree-sitter generate`. The best way to recompile the C-code is to run the command `node-gyp build`. You may have to install the [`node-gyp`][node-gyp] tool separately by running `npm install -g node-gyp`.

## Starting to define the grammar

It's usually a good idea to find a formal specification for the language you're trying to parse. This specification will most likely contain a context-free grammar. As you read through the rules of this CFG, you will probably discover a complex and cyclic graph of relationships. It might be unclear how you should navigate this graph as you define your grammar.

Although languages have very different constructs, their constructs can often be categorized in to similar groups like *Declarations*, *Definitions*, *Statements*, *Expressions*, *Types*, and *Patterns*. In writing your grammar, a good first step is to create just enough structure to include all of these basic *groups* of symbols. For an imaginary C-like language, this might look something like this:

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

## Writing unit tests

For each rule that you add to the grammar, you should first create a *test* that describes how the syntax trees should look when parsing that rule. These tests are written using specially-formatted text files in a `corpus` directory in your parser's root folder. Here is an example of how these tests should look:

```
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
      (return_statement (number))))
```

The name of the test is written between two lines containing only `=` characters. Then the source code is written, followed by a line containing three or more `-` characters. Then, the expected syntax tree is written as an [S-expression][s-exp]. The exact placement of whitespace in the S-expression doesn't matter, but ideally the syntax tree should be legible. Note that the S-expression does not show syntax nodes like `func`, `(` and `;`, which are expressed as strings and regexes in the grammar. It only shows the *named* nodes, as described in [the previous page](/using-parsers#named-vs-anonymous-nodes).

These tests are important. They serve as the parser's API documentation, and they can be run every time you change the grammar to verify that everything still parses correctly. You can run these tests using this command:

```sh
tree-sitter test
```

To run a particular test, you can use the the `-f` flag:

```sh
tree-sitter test -f 'Return statements'
```

The recommendation is to be comprehensive in adding tests. If it's a visible node, add it to a test file in your `/corpus/` directory. It's typically a good idea to test as many permutations of a particular language construct as possible. This increases test coverage, but doubly acquaints readers with a way to examine expected outputs and understand the "edges" of a language.


## Using the grammar DSL

The following is a complete list of built-in functions you can use to define Tree-sitter grammars. Use-cases for some of these functions will be explained in more detail in later sections.

* **Symbols (the `$` object)** - Every grammar rule is written as a JavaScript function that takes a parameter conventionally called `$`. The syntax `$.identifier` is how you refer to another grammar symbol within a rule.
* **String and Regex literals** - The terminal symbols in a grammar are described using JavaScript strings and regular expressions. Of course during parsing, Tree-sitter does not actually use JavaScript's regex engine to evaluate these regexes; it generates its own regex-matching logic as part of each parser. Regex literals are just used as a convenient way of writing regular expressions in your grammar.
* **Sequences : `seq(rule1, rule2, ...)`** - This function creates a rule that matches any number of other rules, one after another. It is analogous to simply writing multiple symbols next to each other in [EBNF notation](enbf).
* **Alternatives : `choice(rule1, rule2, ...)`** - This function creates a rule that matches *one* of a set of possible rules. The order of the arguments does not matter. This is analogous to the `|` (pipe) operator in EBNF notation.
* **Repetitions : `repeat(rule)`** - This function creates a rule that matches *zero-or-more* occurrences of a given rule. It is analogous to the `{x}` (curly brace) syntax in EBNF notation.
* **Repetitions : `repeat1(rule)`** - This function creates a rule that matches *one-or-more* occurrences of a given rule. The previous `repeat` rule is implemented in terms of `repeat1` but is included because it is very commonly used.
* **Options : `optional(rule)`** - This function creates a rule that matches *zero or one* occurrence of a given rule it is analogous to the `[x]` (square bracket) syntax in EBNF notation.
* **Precedence : `prec(number, rule)`** - This function marks the given rule with a numerical precedence which will be used to resolve [*LR(1) Conflicts*][lr-conflict] at parser-generation time. When two rules overlap in a way that represents either a true ambiguity or a *local* ambiguity given one token of lookahead, Tree-sitter will try to resolve the conflict by matching the rule with the higher precedence. The default precedence of all rules is zero. This works similarly to the [precedence directives][yacc-prec] in Yacc grammars.
* **Left Associativity : `prec.left([number], rule)`** - This function marks the given rule as left-associative (and optionally applies a numerical precedence). When an LR(1) conflict arises in which all of the rules have the same numerical precedence, Tree-sitter will consult the rules' associativity. If there is a left-associative rule, Tree-sitter will prefer matching a rule that ends *earlier*. This works similarly to [associativity directives][yacc-prec] in Yacc grammars.
* **Right Associativity : `prec.right([number], rule)`** - This function is like `prec.left`, but it instructs Tree-sitter to prefer matching a rule that ends *later*.
* **Dynamic Precedence : `prec.dynamic(number, rule)`** - This function is similar to `prec`, but the given numerical precedence is applied at *runtime* instead of at parser generation time. This is only necessary when handling a conflict dynamically using the the `conflicts` field in the grammar, and when there is a genuine *ambiguity*: multiple rules correctly match a given piece of code. In that event, Tree-sitter compares the total dynamic precedence associated with each rule, and selects the one with the highest total. This is similar to [dynamic precedence directives][bison-dprec] in Bison grammars.
* **Tokens : `token(rule)`** - This function marks the given rule as producing only a single token. Tree-sitter's default is to treat each String or RegExp literal in the grammar as a separate token. Each token is matched separately by the lexer and returned as its own leaf node in the tree. The `token` function allows you to express a complex rule using the functions described above (rather than as a single regular expression) but still have Tree-sitter treat it as a single token.
* **Aliases : `alias(rule, name)`** - This function causes the given rule to *appear* with an alternative name in the syntax tree. It is useful in cases where a language construct needs to be parsed differently in different contexts (and thus needs to be defined using multiple symbols), but should always *appear* as the same type of node.

In addition to the `name` and `rules` fields, grammars have a few other optional public fields that influence the behavior of the parser.

* `extras` - an array of tokens that may appear *anywhere* in the language. This is often used for whitespace and comments. The default for `extras` in `tree-sitter-cli` is to accept whitespace. To control whitespace explicitly, specify `extras=[]` in the grammar.
* `inline` - an array of rule names that should be automatically *removed* from the grammar by replacing all of their usages with a copy of their definition. This is useful for rules that are used in multiple places but for which you *don't* want to create syntax tree nodes at runtime.
* `conflicts` - an array of arrays of rule names. Each inner array represents a set of rules that's involved in an *LR(1) conflict* that is *intended to exist* in the grammar. When these conflicts occur at runtime, Tree-sitter will use the GLR algorithm to explore all of the possible interpretations. If *multiple* parses end up succeeding, Tree-sitter will pick the subtree rule with the highest *dynamic precedence*.
* `externals` - an array of toen names which can be returned by an *external scanner*. External scanners allow you to write custom C code which runs during the lexing process in order to handle lexical rules (e.g. Python's indentation tokens) that cannot be described by regular expressions.
* `word` - the name of a token that will match keywords for the purpose of the [keyword extraction](#keyword-extraction) optimization.

## Adjusting existing grammars

Imagine that you were just starting work on the [Tree-sitter JavaScript parser][tree-sitter-javascript]. You might try to directly mirror the structure of the [ECMAScript Language Spec][ecmascript-spec]. To illustrate the problem with this approach, consider the following line of code:

```js
return x + y;
```

According to the specification, this line is a `ReturnStatement`, the fragment `x + y` is an `AdditiveExpression`, and `x` and `y` are both `IdentifierReferences`. The relationship between these constructs is captured by a complex series of production rules:  

```
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

The language spec encodes the 20 precedence levels of JavaScript expressions using 20 different non-terminal symbols. If we were to create a concrete syntax tree representing this statement according to the language spec, it would have twenty levels of nesting and it would contain nodes with names like `BitwiseXORExpression`, which are unrelated to the actual code.

### Using precedence

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

```
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

For an expression like `-a * b`, it's not clear whether the `-` operator applies to the `a * b` or just to the `a`. This is where the `prec` function described above comes into play. By wrapping a rule with `prec`, we can indicate that certain sequence of symbols should *bind to each other more tightly* than others. For example, the `'-', $._expression` sequence in `unary_expression` should bind more tightly than the `$._expression, '+', $._expression` sequence in `binary_expression`:

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

### Using associativity

Applying a higher precedence in `unary_expression` fixes that conflict, but there is still another conflict:

```
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

### Hiding rules

You may have noticed in the above examples that some of the grammar rule name like `_expression` and `_type` began with an underscore. Starting a rule's name with an underscore causes the rule to be *hidden* in the syntax tree. This is useful for rules like `_expression` in the grammars above, which always just wrap a single child node. If these nodes were not hidden, they would add substantial depth and noise to the syntax tree without making it any easier to understand.

### Dealing with LR conflicts

...

## Lexical Analysis

Tree-sitter's parsing process is divided into two phases: parsing (which is described above) and [lexing][lexing] - the process of grouping individual characters into the language's fundamental *tokens*. There are a few important things to know about how Tree-sitter's lexing works.

### Conflicting Tokens

Grammars often contain multiple tokens that can match the same characters. For example, a grammar might contain the tokens (`"if"` and `/[a-z]+/`). Tree-sitter differentiates between these conflicting tokens in a few ways:

1. **Context-aware Lexing** - Tree-sitter performs lexing on-demand, during the parsing process. At any given position in a source document, the lexer only tries to recognize tokens that are *valid* at that position in the document.

2. **Lexical Precedence** - When the precedence functions described [above](#using-the-grammar-dsl) are used within the `token` function, the given precedence values serve as instructions to the lexer. If there are two valid tokens that match the characters at a given position in the document, Tree-sitter will select the one with the higher precedence.

3. **Match Length** - If multiple valid tokens with the same precedence match the characters at a given position in a document, Tree-sitter will select the token that matches the [longest sequence of characters][longest-match].

4. **Match Specificity** - If there are two valid tokens with the same precedence and which both match the same number of characters, Tree-sitter will prefer a token that is specified in the grammar as a `String` over a token specified as a `RegExp`.

### Keywords

If your language has keywords which are matched by a rule (typically `identifier`), you can tell Tree-sitter about it with your grammar's `word` property.

```js
grammar({
  word: $ => $.identifier,

  rules: {
    class_declaration: $ => seq(
      'class',
      $.identifier,
      $.class_body
    ),

    break_statement: $ => seq('break', ';'),

    continue_statement: $ => seq('continue', ';'),

    identifier: $ => /[a-z]+/
  }
})
```

In this case, we're specifying `identifier` as our `word`. Tree-sitter will automatically find the set of terminals which are matched by `$.identifier`, and consider them keywords. Instead of generating a parser which scans for each keyword individually, Tree-sitter will generate a parser that tries to match the word rule (in this case, `identifier`), and checks to see if the matched word is the necessary keyword.

This makes the set of parse states smaller, so the parser compiles faster.

It *also changes behavior*. Consider this grammar:

```js
grammar({
  rules: {
    import: $ => seq(
      'import',
      $.identifier,
      'as',
      $.identifier
    ),

    identifier: $ => /[a-z]+/
  }
})
```

Without the `word` directive, the grammar matches this input:

```
import foo asbar
```

Which is probably not what you want. If we add `word: $ => $.identifier`, this will no longer parse. When we try to parse `'as'`, we will parse a word — which will be the identifier ``'asbar'``—and then compare it to `'as'`, correctly generating an error.

[lexing]: https://en.wikipedia.org/wiki/Lexical_analysis
[longest-match]: https://en.wikipedia.org/wiki/Maximal_munch
[cst]: https://en.wikipedia.org/wiki/Parse_tree
[dfa]: https://en.wikipedia.org/wiki/Deterministic_finite_automaton
[non-terminal]: https://en.wikipedia.org/wiki/Terminal_and_nonterminal_symbols
[language-spec]: https://en.wikipedia.org/wiki/Programming_language_specification
[glr-parsing]: https://en.wikipedia.org/wiki/GLR_parser
[lr-grammars]: https://en.wikipedia.org/wiki/LR_parser
[yacc]: https://en.wikipedia.org/wiki/Yacc
[bison]: https://en.wikipedia.org/wiki/GNU_bison
[antlr]: http://www.antlr.org/
[peg]: https://en.wikipedia.org/wiki/Parsing_expression_grammar
[ambiguous-grammar]: https://en.wikipedia.org/wiki/Ambiguous_grammar
[tree-sitter-javascript]: https://github.com/tree-sitter/tree-sitter-javascript
[ecmascript-spec]: https://www.ecma-international.org/ecma-262/6.0
[tree-sitter-cli]: https://github.com/tree-sitter/tree-sitter-cli
[node-module]: https://www.npmjs.com/package/tree-sitter-cli
[node.js]: https://nodejs.org
[npm]: https://docs.npmjs.com
[nan]: https://github.com/nodejs/nan
[s-exp]: https://en.wikipedia.org/wiki/S-expression
[node-gyp]: https://github.com/nodejs/node-gyp
[ebnf]: https://en.wikipedia.org/wiki/Extended_Backus%E2%80%93Naur_form
[lr-conflict]: https://en.wikipedia.org/wiki/LR_parser#Conflicts_in_the_constructed_tables
[yacc-prec]: https://docs.oracle.com/cd/E19504-01/802-5880/6i9k05dh3/index.html
[bison-dprec]: https://www.gnu.org/software/bison/manual/html_node/Generalized-LR-Parsing.html
