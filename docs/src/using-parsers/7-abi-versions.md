# ABI versions

Parsers generated with tree-sitter have an associated ABI version. This version specifies the shape of the C code that they contain, which they expose to applications.

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

Tree-sitter developers aim to maintain compatibility with the previous ABI version at least.

Parser authors are able to specify the ABI version they want to use by specifying it with the `--abi` option of the `tree-sitter generate` command.
