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

The default names for the query files use the `.scm` file. We chose this extension because it commonly used for files written in [Scheme](https://en.wikipedia.org/wiki/Scheme_%28programming_language%29), a popular dialect of Lisp, and these query files use a Lisp-like syntax. But alternatively, you can think of `SCM` as an acronym for "Source Code Matching".

## Highlights Query

The most important query is called the highlights query. The highlights query uses *captures* to assign arbitrary *highlight names* to different nodes in the tree. Each highlight name can then be mapped to a color. Commonly used highlight names include `keyword`, `function`, `type`, `property`, and `string`. Names can also be dot-separated like `function.builtin`.

#### Example Input

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

#### Example Query

Suppose we wanted to render this code with the following colors:
* keywords `func` and `return` in purple
* function `increment` in blue
* type `int` in green
* number `5` brown

We can assign each of these categories a *highlight name* using a query like this:

```
; highlights.scm

"func" @keyword
"return" @keyword
(type_identifier) @type
(int_literal) @number
(function_declaration name: (identifier) @function)
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

#### Result

<pre class='highlight' style='border: 1px solid #aaa;'>
<span style='color: purple;'>func</span> <span style='color: #005fd7;'>increment</span>(<span>a</span> <span style='color: green;'>int</span>) <span style='color: green;'>int</span> {
    <span style='color: purple;'>return</span> <span>a</span> <span style='font-weight: bold;color: #4e4e4e;'>+</span> <span style='font-weight: bold;color: #875f00;'>1</span>
}
</pre>

## Local Variable Query

Good syntax highlighting helps the reader to quickly distinguish between the different types of *entities* in their code. Ideally, if a given entity appears in *multiple* places, it should be colored the same in each place. The Tree-sitter syntax highlighting system can help you to achieve this by keeping track of local scopes and variables.

The *local variables* query is different from the highlights query in that, while the highlights query uses *arbitrary* capture names which can then be mapped to colors, the locals variable query uses a fixed set of capture names, each of which has a special meaning.

The capture names are as follows:

* `@local.scope` - indicates that a syntax node introduces a new local scope.
* `@local.definition` - indicates that a syntax node contains the *name* of a definition within the current local scope.
* `@local.reference` - indicates that a syntax node contains the *name* which *may* refer to an earlier definition within some enclosing scope.

When highlighting a file, Tree-sitter will keep track of the set of scopes that contains any given position, and the set of definitions within each scope. When processing a syntax node that is captured as a `local.reference`, Tree-sitter will try to find a definition for a name that that matches the node's text. If it finds a match, Tree-sitter will ensure that the *reference* and the *definition* are colored the same.

The information produced by this query can also be *used* by the highlights query. You can *disable* a pattern for nodes which have been identified as local variables by adding the predicate `(is-not? local)` to the pattern. This is used in the example below:

#### Example Input

Consider this Ruby code:

```ruby
def process_list(list)
  context = current_context
  list.map do |item|
    process_item(item, context)
  end
end

item = 5
list = [item]
```

With this syntax tree:

```
(program
  (method
    name: (identifier)
    parameters: (method_parameters
      (identifier))
    (assignment
      left: (identifier)
      right: (identifier))
    (method_call
      method: (call
        receiver: (identifier)
        method: (identifier))
      block: (do_block
        (block_parameters
          (identifier))
        (method_call
          method: (identifier)
          arguments: (argument_list
            (identifier)
            (identifier))))))
  (assignment
    left: (identifier)
    right: (integer))
  (assignment
    left: (identifier)
    right: (array
      (identifier))))
```

There are several different types of names within this method:

* `process_list` is a method.
* Within this method, `list` is a formal parameter
* `context` is a local variable.
* `current_context` is *not* a local variable, so it must be a method.
* Within the `do` block, `item` is a formal parameter
* Later on, `item` and `list` are both local variables (not formal parameters).

#### Example Queries

Let's write some queries that let us clearly distinguish between these types of names. First, set up the highlighting query, as described in the previous section. We'll assign distinct colors to method calls, method definitions, and formal parameters:

```
; highlights.scm

(call method: (identifier) @function.method)
(method_call method: (identifier) @function.method)

(method name: (identifier) @function.method)

(method_parameters (identifier) @variable.parameter)
(block_parameters (identifier) @variable.parameter)

((identifier) @function.method
 (is-not? local))
```

Then, we'll set up a local variable query to keep track of the variables and scopes. Here, we're indicating that methods and blocks create local *scopes*, parameters and assignments create *definitions*, and other identifiers should be considered *references*:

```
; locals.scm

(method) @local.scope
(do_block) @local.scope

(method_parameters (identifier) @local.definition)
(block_parameters (identifier) @local.definition)

(assignment left:(identifier) @local.definition)

(identifier) @local.reference
```

#### Result

<pre class='highlight' style='border: 1px solid #aaa;'>
<span style='color: purple;'>def</span> <span style='color: #005fd7;'>process_list</span><span style='color: #4e4e4e;'>(</span><span style='text-decoration: underline;'>list</span><span style='color: #4e4e4e;'>)</span>
  <span>context</span> <span style='font-weight: bold;color: #4e4e4e;'>=</span> <span style='color: #005fd7;'>current_context</span>
  <span style='text-decoration: underline;'>list</span><span style='color: #4e4e4e;'>.</span><span style='color: #005fd7;'>map</span> <span style='color: purple;'>do</span> |<span style='text-decoration: underline;'>item</span>|
    <span style='color: #005fd7;'>process_item</span>(<span style='text-decoration: underline;'>item</span><span style='color: #4e4e4e;'>,</span> <span>context</span><span style='color: #4e4e4e;'>)</span>
  <span style='color: purple;'>end</span>
<span style='color: purple;'>end</span>

<span>item</span> <span style='font-weight: bold;color: #4e4e4e;'>=</span> <span style='font-weight: bold;color: #875f00;'>5</span>
<span>list</span> <span style='font-weight: bold;color: #4e4e4e;'>=</span> [<span>item</span><span style='color: #4e4e4e;'>]</span>
</pre>

## Language Injection Query

Some source files contain code written in multiple different languages. Examples include:
* HTML files, which can contain JavaScript inside of `<script>` tags and CSS inside of `<style>` tags
* [ERB](https://en.wikipedia.org/wiki/ERuby) files, which contain Ruby inside of `<% %>` tags, and HTML outside of those tags
* PHP files, which can contain  HTML between the `<php` tags
* JavaScript files, which contain regular expression syntax within regex literals
* Ruby, which can contain Bash code inside of `<<BASH` here-doc literals

All of these examples can be modeled in terms of a *parent* syntax tree and one or more *injected* syntax trees, which reside *inside* of certain nodes in the parent tree. The language injection query allows you to specify these "injections" using the following captures:

* `@injection.content` - indicates that the captured node should have its contents re-parsed using another language.
* `@injection.language` - indicates that the captured node's text may contain the *name* of a language that should be used to re-parse the `@injection.content`.

The language can also be specified by a hard-coded string using the `(set! injection.language)` predicate. The way that the

#### Examples

Consider this ruby code:

```ruby
system <<-BASH.strip!
  abc --def | ghi > jkl
BASH
```

With this syntax tree:

```
(program
  (method_call
    method: (identifier)
    arguments: (argument_list
      (call
        receiver: (heredoc_beginning)
        method: (identifier))))
  (heredoc_body
    (heredoc_end)))
```

The following query would specify that the contents of the heredoc should be parsed using a language named "BASH" (because that is the text of the `heredoc_end` node):

```
(heredoc_body
  (heredoc_end) @injection.language) @injection.content
```
