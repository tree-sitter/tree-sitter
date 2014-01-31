TODO
====

## correct batch parsing
- generate correct lexers in the presence of 'overlapping' transition
  rules (e.g. transitions on 'a' and on \w).
- add comments to generated C code giving an example string for each token
- change the meaning of 'repeat' from 1-or-more to 0-or-more
- fix any memory leaks
- add special lexical behavior for indentation-aware languages

## node.js wrapper
- add simple selector engine for trees

## incremental parsing

## chores
- figure out why Symbol and Character can't have const member variables
  (unordered_map seems to require mutability of key objects)
