# Tree-sitter tips and tricks

Language development using [Tree-Sitter](https://github.com/tree-sitter/tree-sitter) can be an arduous task. These tips are intended to help bring empiricism to the process by reducing trial and error (or at least introducing some guard rails).

### :bulb: Rely on Language Specs, but not too much.
There are language specifications (like [this one for Java](https://docs.oracle.com/javase/specs/jls/se9/html/index.html)) that comprehensively describe a language. Specs provide the lexical and syntactic structure of a language in addition to its components (ex., types, variables, declarations, etc.) and how they interconnect. This can serve as a great baseline for writing your grammar. However, mirroring the spec 100% is not always the best approach, especially when its structure does not align with the parse tree you'd like to generate using tree-sitter. In this situation, it's better to deviate from the spec and prioritize generating a good parse tree. One way to do this may be to find an LR parser for the language you're working on ([such as this one for Java](https://github.com/javaparser/javaparser)) to see how they've modeled their tree outputs. Studying tree outputs from other LR parsers can be a good way to guide your own grammar development. 

### :bulb: What does a "good" parse tree look like?

Here are some attributes of a "pretty" tree:

:white_check_mark: Not overly verbose.

:white_check_mark: Everything is outlined clearly.

:white_check_mark: Communicates good information needed further along in the pipeline.

![image](https://user-images.githubusercontent.com/875834/34972577-41bc12ac-fa37-11e7-9a12-a05d18b6f6e4.png)

_Example of a good tree (WIP -- better examples welcome!):_

```
===
module
===

module com.foo { }
open module com.foo { }

---

(program
  (module_declaration (module_identifier (identifier) (identifier)))
  (module_declaration (module_identifier (identifier) (identifier))))
```

### :bulb: Improving a parse tree by making it more compact
Here are some things that might help:

**1. Aliasing** - by aliasing different things, you can maintain compact tree structure while marking differences in your grammar. _(Need better description)_

**2. Making things hidden** - by putting an underscore before a rule (`_rule` vs `rule`), it will allow you to omit displaying it in the tree.

### :bulb: Testing in the wild to help prioritize what to support next.

Once you have developed a significant portion of the grammar, find a file from an active open source repository that follows the typical structure of the language and see how much of it can be successfully parsed by your system. Is it 40%? 60%? This can be a good way to benchmark how practical your grammar is in terms of popular usage of your language. It can also be an effective way to identify what to support and prioritize what's next.

### :bulb: Knowing when to stop development
Most languages have a long-tail of features that don't get utilized frequently. It is reasonable to prioritize developing 80% of a language and only supporting commonly used elements.

### :bulb: Handling conflicts

Conflicts may arise due to ambiguities in the grammar. This is when the parser can not decide what the next symbol in an input stream should be because there are multiple ways to parse some strings. There are three ways to handle conflict:
1. Rearrange code.
2. Specifying associativity and/or precedence.
3. Adding a conflict.

**1. Rearrange code.** There are ways to specify rules in a way that makes it easier for the lexer to digest. This can be done by using the following helper functions:

_(WIP: Explain why the following help you avoid conflicts)_

- `inline` - _(need Max's help here)_
- `commaSep` - creates a repeating sequence of 0 or more tokens separated by a comma
- `commaSep1` - creates a repeating sequence of 1 or more tokens separated by a comma
- `sep1`- creates a repeating sequence of 0 or more tokens separated by the specified delimiter

**2. Specifying associativity and/or precedence.**

Another way of resolving a conflict is through associativity and precedence. Specifying precedence allows us to prioritize productions in the grammar. If there are two or more ways to proceed, the production with the higher precedence will get preference. Left and right associativity can also be used to reflect how to proceed. For instance, a left-associative evaluation is `(a Q b) Q c` vs. a right-associative evaluation would render `a Q (b Q c)`. In this way, associativity changes the meaning of the expression.

_(WIP: Add examples)_

**3. Add a conflict.** 

Adding conflicts allows the parser to pursue two paths in parallel, and decide which one to proceed with further along the process. By specifying a conflict with one rule, you can prevent the parser from recursively descending.

Adding a conflict to your grammar should be a last resort, and it's typically best to exhaust the first two options first.

_(WIP: add example)_
