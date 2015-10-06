TODO
====

### Handling ambiguity (GLR)
* Add a simple way to specify syntactic ambiguity resolutions in the Grammar (e.g. 'prefer declarations to statements' in C), similar to bison's `dprec`
construct.

### Runtime System
* Refactoring: make separate symbol for unexpected characters than for interior error nodes.

### Testing / Quality
* Start running the clang-analyzer on the codebase on Travis-CI.
* Use the Valgrind leak checker to fix the memory leaks in the runtime library.
* Randomize the editing in the language tests, using a seed that can be specified in order to reproduce failures.

### Ubiquitous token handling
* Fix the unintuitive tree that results when ubiquitous tokens are last child of their parent node.

### Error handling
* Use information about nesting depth of tokens like '(' and ')' to make error recovery more accurate.

### Grammar Features
* Regexp assertions
  - [ ] '^'
  - [ ] '$'
  - [ ] '\b'
* Composing languages
  - [ ] Rule for referencing named grammar
  - [ ] Grammar registry object in runtime
  - [ ] Parsing returns control to parent language
* Indentation tokens

