# Operators

## Capturing Nodes

When matching patterns, you may want to process specific nodes within the pattern. Captures allow you to associate names
with specific nodes in a pattern, so that you can later refer to those nodes by those names. Capture names are written _after_
the nodes that they refer to, and start with an `@` character.

For example, this pattern would match any assignment of a `function` to an `identifier`, and it would associate the name
`the-function-name` with the identifier:

```query
(assignment_expression
  left: (identifier) @the-function-name
  right: (function))
```

And this pattern would match all method definitions, associating the name `the-method-name` with the method name, `the-class-name`
with the containing class name:

```query
(class_declaration
  name: (identifier) @the-class-name
  body: (class_body
    (method_definition
      name: (property_identifier) @the-method-name)))
```

## Quantification Operators

You can match a repeating sequence of sibling nodes using the postfix `+` and `*` _repetition_ operators, which work analogously
to the `+` and `*` operators [in regular expressions][regex]. The `+` operator matches _one or more_ repetitions of a pattern,
and the `*` operator matches _zero or more_.

For example, this pattern would match a sequence of one or more comments:

```query
(comment)+
```

This pattern would match a class declaration, capturing all of the decorators if any were present:

```query
(class_declaration
  (decorator)* @the-decorator
  name: (identifier) @the-name)
```

You can also mark a node as optional using the `?` operator. For example, this pattern would match all function calls, capturing
a string argument if one was present:

```query
(call_expression
  function: (identifier) @the-function
  arguments: (arguments (string)? @the-string-arg))
```

## Grouping Sibling Nodes

You can also use parentheses for grouping a sequence of _sibling_ nodes. For example, this pattern would match a comment
followed by a function declaration:

```query
(
  (comment)
  (function_declaration)
)
```

Any of the quantification operators mentioned above (`+`, `*`, and `?`) can also be applied to groups. For example, this
pattern would match a comma-separated series of numbers:

```query
(
  (number)
  ("," (number))*
)
```

## Alternations

An alternation is written as a pair of square brackets (`[]`) containing a list of alternative patterns.
This is similar to _character classes_ from regular expressions (`[abc]` matches either a, b, or c).

For example, this pattern would match a call to either a variable or an object property.
In the case of a variable, capture it as `@function`, and in the case of a property, capture it as `@method`:

```query
(call_expression
  function: [
    (identifier) @function
    (member_expression
      property: (property_identifier) @method)
  ])
```

This pattern would match a set of possible keyword tokens, capturing them as `@keyword`:

```query
[
  "break"
  "delete"
  "else"
  "for"
  "function"
  "if"
  "return"
  "try"
  "while"
] @keyword
```

Alternations can have quantified alternants, and then can have their own
quantifiers as well. See the following examples for an illustration of how these
cases work:

```query
;;; SOURCE CODE ;;;
; #include <foo>
; #include <bar>
; #include <baz>
; // comment
;;;;;;;;;;;;;;;;;;;

[
  (preproc_include)
  (comment)
]+ @capture
; ^ Produces one match with four captures:
; [
;   "#include <foo>\n",
;   "#include <bar>\n",
;   "#include <baz>\n",
;   "// comment",
; ]
;
; Regex equivalent: [ab]+

[
  (preproc_include)+
  (comment)
] @capture
; ^ Produces two matches; one with three captures, and one with one capture:
; [
;   "#include <foo>\n",
;   "#include <bar>\n",
;   "#include <baz>\n",
; ],
; [
;   "// comment",
; ]
;
; Regex equivalent: a+|b

[
  (preproc_include)
  (comment)
] @capture
; ^ Produces four matches, each with one capture:
; [
;   "#include <foo>\n",
; ],
; [
;   "#include <bar>\n",
; ],
; [
;   "#include <baz>\n",
; ],
; [
;   "// comment",
; ]
;
; Regex equivalent: [ab]
```

### Recursive Alternations

Inside an alternation, the special pattern `(^)` is a recursive back-reference to the enclosing `[...]`. It causes the query 
engine to loop back and try all alternatives again, one level deeper in the tree. This enables matching nodes at arbitrary 
nesting depth without writing out every possible depth by hand.

A recursive alternation needs at least two branches: one or more *recursive* branches that descend into a child and end with 
`(^)`, and one or more *base-case* branches that match the target node.

For example, to find every `return_statement` at any depth inside a function body:

```query
(function_definition
  body: (compound_statement
    [(_ (^)) (return_statement) @ret]))
```

The `(_ (^))` branch matches any child node and recurses. The `(return_statement) @ret` branch is the base case that captures 
the target. Together they express "descend through any number of intermediate nodes until a `return_statement` is found."

Recursive branches can be constrained to specific node types. This pattern only descends through `if_statement` consequence 
chains (with or without braces):

```query
(function_definition
  body: (compound_statement [
    (if_statement consequence: (compound_statement (^))) @if
    (if_statement consequence: (^)) @if
    (return_statement) @ret
  ]))
```

When alternations are nested, `(^^)` refers to the next outer `[...]`, `(^^^)` to the one beyond that, and so on. This allows 
inner and outer alternations to recurse independently, enabling multi-level patterns that distinguish different nesting 
depths.

#### Labeled Recursion

The anonymous `(^)` / `(^^)` references target alternations by counting nesting levels (De Bruijn indices). When patterns grow 
complex, this becomes hard to read and fragile under refactoring. **Labeled recursion** lets you name a recursion scope and 
refer to it by name.

`(^label ...)` defines a labeled scope - the body (one or more child patterns) becomes a recursion target. `(^label)` (without 
a body) is a back-reference that jumps to the most recent scope with that name.

For example, to match C pointer-declarator chains like `***x`, stripping the type and capturing each layer:

```query
(declaration
  type: (_) @type
  declarator: (^ptr (pointer_declarator
    declarator: [(^ptr) (identifier) @name]
  ) @star))
```

Here `(^ptr ...)` wraps the `pointer_declarator` node. The back-reference `(^ptr)` jumps back to the scope entry - re-entering 
at the `pointer_declarator` match, one level deeper. This cannot be expressed with anonymous `(^)`, because `(^)` can only 
target an enclosing `[...]`, and the recursion target here is the node pattern above the alternation.

Labels are scoped to their body - a `(^label)` reference is only valid inside the corresponding `(^label ...)` body. 
Referencing an undefined or out-of-scope label is a parse error.

Labeled and counted references can coexist. Inside a labeled scope that directly wraps an alternation, both `(^)` (targeting 
the alternation) and `(^label)` (targeting the labeled scope) resolve to the same point.

Note: `(^)`, `(^^)`, and `(^label)` must be the last element in their branch (tail position). They cannot be followed by 
sibling steps or have child steps of their own.

## Anchors

The anchor operator, `.`, is used to constrain the ways in which child patterns are matched. It has different behaviors
depending on where it's placed inside a query.

When `.` is placed before the _first_ child within a parent pattern, the child will only match when it is the first named
node in the parent. For example, the below pattern matches a given `array` node at most once, assigning the `@the-element`
capture to the first `identifier` node in the parent `array`:

```query
(array . (identifier) @the-element)
```

Without this anchor, the pattern would match once for every identifier in the array, with `@the-element` bound
to each matched identifier.

Similarly, an anchor placed after a pattern's _last_ child will cause that child pattern to only match nodes that are the
last named child of their parent. The below pattern matches only nodes that are the last named child within a `block`.

```query
(block (_) @last-expression .)
```

Finally, an anchor _between_ two child patterns will cause the patterns to only match nodes that are immediate siblings.
The pattern below, given a long dotted name like `a.b.c.d`, will only match pairs of consecutive identifiers:
`a, b`, `b, c`, and `c, d`.

```query
(dotted_name
  (identifier) @prev-id
  .
  (identifier) @next-id)
```

Without the anchor, non-consecutive pairs like `a, c` and `b, d` would also be matched.

The restrictions placed on a pattern by an anchor operator ignore anonymous nodes.

[regex]: https://en.wikipedia.org/wiki/Regular_expression#Basic_concepts
