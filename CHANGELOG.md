# Changelog

## [0.21.0] — 2024-02-21

### Breaking

- Remove the apply-all-captures flag, make last-wins precedence the default for queries

  **NOTE**: This change might cause breakage in your grammar's highlight tests. Just
  flip the order around of the relevant queries, and keep in mind that the last
  query that matches will win.

### Bug Fixes

- Prettify xml output and add node position info
- Inherited grammar generation
- Properly error out when the word property is an invalid rule
- Update schema for regex flags
- Properly handle `Query.matches` when filtering out results
- Sexp format edge case with quoted closed parenthesis
- Always push the default files if there's no `externals`
- Don't log NUL characters
- Don't throw an error if the user uses `map` in the grammar
- Remove redundant imports
- **cli**: Installation via a HTTP tunnel proxy
- **cli**: Don't update tests automatically if parse errors are detected
- **cli**: Don't use `long` for `grammar_path`
- **test**: Allow writing updates to tests without erroneous nodes instead of denying
  all of them if a single error is found
- **test**: Edge case when parsing `UNEXPECTED`/`MISSING` nodes with an indentation
  level greater than 0
- **wasm**: Remove C++ mangled symbols

### Build System

- Add useful development targets to makefile
- Add editorconfig
- Remove symbolic links from repository
- Move common Cargo.toml keys into the workspace and inherit them
- Enable creating changelogs with git-cliff
- **deps**: Bump clap from 4.4.18 to 4.5.0
- **deps**: Bump wasmtime from v16.0.0 to v17.0.1
- **deps**: Bump wasmtime to v18.0.1

### Documentation

- Create issue template
- Document regex limitations
- Mention that `token($.foo)` is illegal
- Explicitly mention behavior of walking outside the given "root" node for a `TSTreeCursor`
- Small fixes
- Add `Tact` language parser
- **web**: Provide deno usage information

### Features

- Use lockfiles to dedup recompilation
- Improve error message for files with an unknown grammar path
- Implement first-line-regex
- Error out if an empty string is in the `extras` array
- Allow specifying an external scanner's files
- Better error info when a scanner is missing required symbols
- **cli**: Add an optional `grammar-path` argument for the playground
- **cli**: Add optional `config-path` argument
- **loader**: Add more commonly used default parser directories

### Miscellaneous Tasks

- Document preferred language for scanner
- Add java and tsx to corpus tests
- Provide a CLI flag to open `log.html`
- Some more clippy lints
- Remove deprecated query parsing mechanism
- Print out full compiler arguments ran when it fails
- Deprecate C++ scanners
- Update relevant rust tests
- Clippy lints
- Error out when multiple arguments are passed to `token`/`token.immediate`
- Update `Cargo.lock`
- Get rid of `github_issue_test` file
- **cli**: Use spawn to display `emcc`'s stdout and stderr
- **cli**: Warn users when a query path needed for a subcommand isn't specified
  in a grammar's package.json
- **generate**: Dedup and warn about duplicate or invalid rules
- **test**: Use different languages for async tests
- **wasm**: Use `SIDE_MODULE=2` to silence warning

### Refactor

- Extract regex check into a function and lower its precedence
- `&PathBuf` -> `&Path`
- Name anonymous types in api.h

### Testing

- Add quotes around bash variables
- Update html tests
