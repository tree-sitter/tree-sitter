# ABI versions

Parsers generated with tree-sitter have an associated ABI version. This version establishes hard compatibility boundaries between the generated parser and the tree-sitter library.

A given version of tree-sitter is only able to load parsers which have certain ABI versions:

| tree-sitter version | Min parser ABI version | Max parser ABI version |
|---------------------|------------------------|------------------------|
| 0.14                | 9                      | 9                      |
| >=0.15.0, <=0.15.7  | 9                      | 10                     |
| >=0.15.8, <=0.16    | 9                      | 11                     |
| 0.17, 0.18          | 9                      | 12                     |
| >=0.19, <=0.20.2    | 13                     | 13                     |
| >=0.20.3, <=0.24    | 13                     | 14                     |
| >=0.25              | 13                     | 15                     |

By default, parsers are generated using the latest available ABI. Grammar authors can specify an older ABI via the `--abi` option to the `generate` command:
```
tree-sitter generate --abi=<DESIRED-ABI>
```
