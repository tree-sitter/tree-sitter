# ABI versions

Parsers generated with tree-sitter have an associated ABI version, which establishes hard compatibility boundaries
between the generated parser and the tree-sitter library.

A given version of the tree-sitter library is only able to load parsers generated with supported ABI versions:

| tree-sitter version | Min parser ABI version | Max parser ABI version |
|---------------------|------------------------|------------------------|
| 0.14                | 9                      | 9                      |
| >=0.15.0, <=0.15.7  | 9                      | 10                     |
| >=0.15.8, <=0.16    | 9                      | 11                     |
| 0.17, 0.18          | 9                      | 12                     |
| >=0.19, <=0.20.2    | 13                     | 13                     |
| >=0.20.3, <=0.24    | 13                     | 14                     |
| >=0.25              | 13                     | 15                     |

By default, the tree-sitter CLI will generate parsers using the latest available ABI for that version, but an older ABI (supported by the CLI) can be selected by passing the [`--abi` option][abi_option] to the `generate` command.

Note that the ABI version range supported by the CLI can be smaller than for the library: When a new ABI version is released, older versions will be phased out over a deprecation period, which starts with no longer being able to generate parsers with the oldest ABI version.

[abi_option]: ../cli/generate.md#--abi-version
