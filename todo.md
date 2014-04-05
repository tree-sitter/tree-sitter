TODO
====

# flexibility of lexer
- make separator character set configurable, not hard-coded to whitespace
- add special lexical behavior for indentation-aware languages
- add helpers for constructing rules involving infix, prefix, and postfix operators

# validation / robustness of compiler
make the main `compile` function return errors when grammars are invalid
- check validity of regex patterns
- check that all rules that are referenced are also defined
- check that all rules that are defined are also referenced (except the start rule)
- don't require user to use the `err` helper
  (right now, generated code doesn't compile if there are no error productions)

# compiler optimization
- implement Pager's [Practical general method](http://link.springer.com/article/10.1007%2FBF00290336)
  for reducing the size of the LR(1) parse table
- speed up grammar compilation

# incremental parsing
- implement the remainder of the incremental parsing algorithm: reuse parse
  tree after the edit

# node.js wrapper
- create easy way to publish grammars as npm packages
- add simple selector engine for trees

# chores
- make ordering of parse and lex tables deterministic, so that generated
  code doesn't keep changing on every commit
