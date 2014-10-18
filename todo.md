TODO
====

* Incremental parsing
  * Add randomized editing to all language tests.
    - [ ] inserts
    - [ ] deletes
    - [ ] replaces
  * Verify that tree remains the same after edit is undone.
  * Verify that the tree's total size is as expected after each edit.

* Ubiquitous token handling
  * Fix the unintuitive tree that results when ubiquitous tokens are last child
    of their parent node.

* Error handling
  * Preserve tokens within error nodes
  * Try to minimize size of error node by looking ahead a few tokens

* Grammar Features
  * Indentation tokens
  * Regexp assertions
    - [ ] '^'
    - [ ] '$'
    - [ ] '\b'
  * Composing languages
    - [ ] Rule for referencing named grammar
    - [ ] Grammar registry object in runtime
    - [ ] Parsing returns control to parent language

* Performance
  * Optimize grammar compilation

* Grammars
  * C
  * Go

* Query API
  * closest(node name)
  * find(node name)
