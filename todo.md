TODO
====

* Complete javascript and golang grammars
* Add `token` helper that allows user to specify structure of tokens using
  rules other than strings and patterns
* Allow language keywords to be specified inline, not as separate named rules.
* Make separator character set configurable, not hard-coded to whitespace
* Add special lexical behavior for indentation-aware languages
* Return a useful error when grammar contains invalid regex patterns
* Create working parser when grammar contains no error productions
* Create working parser when grammar contains unused symbols
* Implement Pager's [Practical general method](http://link.springer.com/article/10.1007%2FBF00290336)
  for reducing the size of the LR(1) parse table
* Speed up grammar compilation
* Implement the remainder of the incremental parsing algorithm: reuse parse
  tree after the edit
* Create easy way to publish grammars as npm packages
* Add simple selector engine for syntax trees
* Make ordering of parse and lex tables deterministic, so that generated
  code doesn't keep changing on every commit
