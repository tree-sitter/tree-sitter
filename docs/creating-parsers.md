# Creating parsers

Developing Tree-sitter parsers can have a difficult learning curve, but once you get the hang of it, it can fun and even zen-like. This document should help you to build an effective mental model for parser development.

## Introduction

Writing a grammar requires creativity. There are an infinite number of context-free grammars that can be used to describe any given language. In order to produce a good Tree-sitter parser, you need to create a grammar with two important properties:

  1. **An intuitive structure** - Tree-sitter's output is a [concrete syntax tree][cst]; each node in the tree corresponds directly to a [terminal or non-terminal symbol][non-terminal] in the grammar. So in order to produce an easy-to-analyze tree, there should be a direct correspondence between the symbols in your grammar and the recognizable constructs in the language. This might seem obvious, but it is very different from the way that context-free grammars are often written in contexts like [language specifications][language-spec] or [Yacc][yacc] parsers.

  2. **A close adherence to LR** - Tree-sitter is based on the [GLR parsing][glr-parsing] algorithm. This means that while it can handle any context-free grammar, it works most efficiently with a class of context-free grammars called [LR Grammars][lr-grammars]. In this respect, Tree-sitter's grammars are similar to (but less restrictive than) Yacc grammars, but very different from [ANTLR grammars][antlr], [Parsing Expression Grammars][peg], or the [ambiguous grammars][ambiguous-grammar] commonly used in language specifications.

It's unlikely that you'll be able to satisfy these two properties by translating an existing context-free grammar directly into Tree-sitter's grammar format. There are a few kinds of adjustments that are often required. The following sections will explain these adjustments in more depth.

## Producing an intuitive tree

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

### Precedence Annotations

Clearly, we need a different way of modeling JavaScript expressions.

...

## Dealing with LR conflicts

[cst]: https://en.wikipedia.org/wiki/Parse_tree
[non-terminal]: https://en.wikipedia.org/wiki/Terminal_and_nonterminal_symbols
[language-spec]: https://en.wikipedia.org/wiki/Programming_language_specification
[glr-parsing]: https://en.wikipedia.org/wiki/GLR_parser
[lr-grammars]: https://en.wikipedia.org/wiki/LR_parser
[yacc]: https://en.wikipedia.org/wiki/Yacc
[antlr]: http://www.antlr.org/
[peg]: https://en.wikipedia.org/wiki/Parsing_expression_grammar
[ambiguous-grammar]: https://en.wikipedia.org/wiki/Ambiguous_grammar
[tree-sitter-javascript]: https://github.com/tree-sitter/tree-sitter-javascript
[ecmascript-spec]: https://www.ecma-international.org/ecma-262/6.0
