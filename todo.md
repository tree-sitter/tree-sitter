TODO
====

Backlog
-------

* Handle UTF8 strings
* Implement assertions in regexps ('^', '$', etc)
* Make parse error handling more robust
* Create C and go grammars
* Implement the remainder of the incremental parsing algorithm: reuse parse tree after the edit
* Expand the AST Node querying API (`closest(node_name)`, `find(node_name)`, etc)
* Add special lexical behavior for indentation-aware languages
* Speed up grammar compilation

Icebox
------

* Implement Pager's [Practical general method](http://link.springer.com/article/10.1007%2FBF00290336)
  for reducing the size of the LR(1) parse table
