TODO
====

* Performance
  * Implement the remainder of the incremental parsing algorithm: re-use parse tree after the edit
  * Optimize grammar compilation

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

* Grammars
  * C
  * Go

* Query API
  * closest(node name)
  * find(node name)
