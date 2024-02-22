# Changelog

## [0.21.0] — 2024-02-21

### Breaking

- Remove the apply-all-captures flag, make last-wins precedence the default _by_ @amaanq

  **NOTE**: This change might cause breakage in your grammar's highlight tests.
  Just flip the order around of the relevant queries, and keep in mind that the
  last query that matches will win.

### Bug Fixes

- Prettify xml output and add node position info _by_ @amaanq _in_ #2970
- Inherited grammar generation _by_ @amaanq
- Properly error out when the word property is an invalid rule _by_ @amaanq
- Update schema for regex flags _by_ @amaanq _in_ #3006
- Properly handle `Query.matches` when filtering out results _by_ @amaanq _in_ #3013
- Sexp format edge case with quoted closed parenthesis _by_ @amaanq _in_ #3016
- Always push the default files if there's no `externals` _by_ @amaanq
- Don't log NUL characters _by_ @amaanq _in_ #3037
- Don't throw an error if the user uses `map` in the grammar _by_ @amaanq _in_ #3041
- Remove redundant imports _by_ @amaanq _in_ #3047
- **cli**: Installation via a HTTP tunnel proxy _by_ @stormyyd _in_ #2824
- **cli**: Don't update tests automatically if parse errors are detected _by_ @amaanq _in_ #3033
- **cli**: Don't use `long` for `grammar_path` _by_ @amaanq
- **test**: Allow writing updates to tests without erroneous nodes instead of denying all of them if a single error is found _by_ @amaanq
- **test**: Edge case when parsing `UNEXPECTED`/`MISSING` nodes with an indentation level greater than 0 _by_ @amaanq
- **wasm**: Remove C++ mangled symbols _by_ @amaanq _in_ #2971

### Build System

- Add useful development targets to makefile _by_ @dundargoc _in_ #2979
- Add editorconfig _by_ @dundargoc _in_ #2998
- Remove symbolic links from repository _by_ @dundargoc _in_ #2997
- Move common Cargo.toml keys into the workspace and inherit them _by_ @amaanq _in_ #3019
- Enable creating changelogs with git-cliff _by_ @dundargoc _in_ #3040
- **deps**: Bump clap from 4.4.18 to 4.5.0 _by_ @dependabot[bot] _in_ #3007
- **deps**: Bump wasmtime from v16.0.0 to v17.0.1 _by_ @dependabot[bot] _in_ #3008
- **deps**: Bump wasmtime to v18.0.1 _by_ @amaanq _in_ #3057

### Documentation

- Create issue template _by_ @dundargoc _in_ #2978
- Document regex limitations _by_ @amaanq
- Mention that `token($.foo)` is illegal _by_ @amaanq
- Explicitly mention behavior of walking outside the given "root" node for a `TSTreeCursor` _by_ @amaanq _in_ #3021
- Small fixes _by_ @dundargoc _in_ #2987
- Add `Tact` language parser _by_ @novusnota _in_ #3030
- **web**: Provide deno usage information _by_ @sigmaSd _in_ #2498

### Features

- Use lockfiles to dedup recompilation _by_ @amaanq
- Improve error message for files with an unknown grammar path _by_ @amaanq _in_ #2475
- Implement first-line-regex _by_ @sigmaSd _in_ #2479
- Error out if an empty string is in the `extras` array _by_ @aminya
- Allow specifying an external scanner's files _by_ @amaanq _in_ #3031
- Better error info when a scanner is missing required symbols _by_ @amaanq
- **cli**: Add an optional `grammar-path` argument for the playground _by_ @amaanq _in_ #3014
- **cli**: Add optional `config-path` argument _by_ @WillLillis _in_ #3050
- **loader**: Add more commonly used default parser directories _by_ @amaanq

### Miscellaneous Tasks

- Document preferred language for scanner _by_ @calebdw _in_ #2972
- Add java and tsx to corpus tests _by_ @amaanq _in_ #2992
- Provide a CLI flag to open `log.html` _by_ @amaanq _in_ #2996
- Some more clippy lints _by_ @amaanq _in_ #3010
- Remove deprecated query parsing mechanism _by_ @amaanq _in_ #3011
- Print out full compiler arguments ran when it fails _by_ @amaanq _in_ #3018
- Deprecate C++ scanners _by_ @amaanq _in_ #3020
- Update relevant rust tests _by_ @amaanq _in_ #2947
- Clippy lints _by_ @amaanq _in_ #3032
- Error out when multiple arguments are passed to `token`/`token.immediate` _by_ @amaanq _in_ #3036
- Update `Cargo.lock` _by_ @amaanq
- Get rid of `github_issue_test` file _by_ @amaanq _in_ #3055
- **cli**: Use spawn to display `emcc`'s stdout and stderr _by_ @amaanq _in_ #2494
- **cli**: Warn users when a query path needed for a subcommand isn't specified in a grammar's package.json _by_ @amaanq
- **generate**: Dedup and warn about duplicate or invalid rules _by_ @amaanq _in_ #2994
- **test**: Use different languages for async tests _by_ @amaanq _in_ #2953
- **wasm**: Use `SIDE_MODULE=2` to silence warning _by_ @amaanq _in_ #3003

### Refactor

- Extract regex check into a function and lower its precedence _by_ @amaanq
- `&PathBuf` -> `&Path` _by_ @amaanq _in_ #3035
- Name anonymous types in api.h _by_ @MatthewGentoo _in_ #1659

### Testing

- Add quotes around bash variables _by_ @dundargoc _in_ #3023
- Update html tests _by_ @amaanq
