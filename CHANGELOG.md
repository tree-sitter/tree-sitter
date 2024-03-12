# Changelog

## [0.22.1] — 2024-03-10

### Bug Fixes

- Cli build script behavior on release

## [0.22.0] — 2024-03-10

### Breaking

- Remove top-level `corpus` dir for tests
  The cli will now only look in `test/corpus` for tests
- Remove redundant escape regex & curly brace regex preprocessing (<https://github.com/tree-sitter/tree-sitter/pull/2838>)
- **bindings**: Convert node bindings to NAPI (<https://github.com/tree-sitter/tree-sitter/pull/3077>)
- **wasm**: Make `current*`, `is*`, and `has*` methods properties (<https://github.com/tree-sitter/tree-sitter/pull/3103>)
- **wasm**: Keep API in-line with upstream and start aligning with node (<https://github.com/tree-sitter/tree-sitter/pull/3149>)

### Features

- Add xtasks to assist with bumping crates (<https://github.com/tree-sitter/tree-sitter/pull/3065>)
- Improve language bindings (<https://github.com/tree-sitter/tree-sitter/pull/2438>)
- Expose the allocator and array header files for external scanners (<https://github.com/tree-sitter/tree-sitter/pull/3063>)
- Add typings for the node bindings
- Replace `nan` with `node-addon-api` and conditionally print logs
- **bindings**: Add more make targets
- **bindings**: Add peerDependencies for npm
- **bindings**: Add prebuildify to node
- **bindings**: Remove dsl types file (<https://github.com/tree-sitter/tree-sitter/pull/3126>)
- **node**: Type tag the language (<https://github.com/tree-sitter/tree-sitter/pull/3109>)
- **test**: Add attributes for corpus tests

### Bug Fixes

- Apply some `scan-build` suggestions (unused assignment/garbage access) (<https://github.com/tree-sitter/tree-sitter/pull/3056>)
- Wrap `||` comparison in parentheses when `&&` is used (<https://github.com/tree-sitter/tree-sitter/pull/3070>)
- Ignore unused variables in the array macros (<https://github.com/tree-sitter/tree-sitter/pull/3083>)
- `binding.cc` overwrite should replace `PARSER_NAME` (<https://github.com/tree-sitter/tree-sitter/pull/3116>)
- Don't use `__declspec(dllexport)` on windows (<https://github.com/tree-sitter/tree-sitter/pull/3128>)
- Parsers should export the language function on windows
- Allow the regex `v` flag (<https://github.com/tree-sitter/tree-sitter/pull/3154>)
- **assertions**: Case shouldn't matter for comment node detection
- **bindings**: Editorconfig and setup.py fixes (<https://github.com/tree-sitter/tree-sitter/pull/3082>)
- **bindings**: Insert `types` after `main` if it exists (<https://github.com/tree-sitter/tree-sitter/pull/3122>)
- **bindings**: Fix template oversights (<https://github.com/tree-sitter/tree-sitter/pull/3155>)
- **cli**: Only output the sources with `--no-bindings` (<https://github.com/tree-sitter/tree-sitter/pull/3123>)
- **generate**: Add `.npmignore`, populate Swift's exclude list (<https://github.com/tree-sitter/tree-sitter/pull/3085>)
- **generate**: Extern allocator functions for the template don't need to be "exported" (<https://github.com/tree-sitter/tree-sitter/pull/3132>)
- **generate**: Camel case name in `Cargo.toml` description (<https://github.com/tree-sitter/tree-sitter/pull/3140>)
- **lib**: Include `api.h` so `ts_set_allocator` is visible (<https://github.com/tree-sitter/tree-sitter/pull/3092>)

### Documentation

- Add GitHub user and PR info to the changelog
- Add css for inline code (<https://github.com/tree-sitter/tree-sitter/pull/2844>)
- Document test attributes
- Add `Ohm` language parser
- Remove duplicate `the`'s (<https://github.com/tree-sitter/tree-sitter/pull/3120>)
- Add discord and matrix badges (<https://github.com/tree-sitter/tree-sitter/pull/3148>)

### Refactor

- Rename TS_REUSE_ALLOCATOR flag (<https://github.com/tree-sitter/tree-sitter/pull/3088>)
- Remove extern/const where possible
- **array**: Use pragma GCC in clang too
- **bindings**: Remove npmignore (<https://github.com/tree-sitter/tree-sitter/pull/3089>)

### Testing

- Don't use TS_REUSE_ALLOCATOR on Darwin systems (<https://github.com/tree-sitter/tree-sitter/pull/3087>)
- Add test case for parse stack merging with incorrect error cost bug (<https://github.com/tree-sitter/tree-sitter/pull/3098>)

### Build System and CI

- Improve changelog settings (<https://github.com/tree-sitter/tree-sitter/pull/3064>)
- Unify crate versions via workspace (<https://github.com/tree-sitter/tree-sitter/pull/3074>)
- Update `cc` to remove annoying debug output (<https://github.com/tree-sitter/tree-sitter/pull/3075>)
- Adjust dependabot settings (<https://github.com/tree-sitter/tree-sitter/pull/3079>)
- Use c11 everywhere
- Add uninstall command
- Don't skip tests on failing lint (<https://github.com/tree-sitter/tree-sitter/pull/3102>)
- Remove unused deps, bump deps, and bump MSRV to 1.74.1 (<https://github.com/tree-sitter/tree-sitter/pull/3153>)
- **bindings**: Metadata improvements
- **bindings**: Make everything c11 (<https://github.com/tree-sitter/tree-sitter/pull/3099>)
- **dependabot**: Update weekly instead of daily (<https://github.com/tree-sitter/tree-sitter/pull/3112>)
- **deps**: Bump the cargo group with 1 update (<https://github.com/tree-sitter/tree-sitter/pull/3081>)
- **deps**: Bump the cargo group with 1 update (<https://github.com/tree-sitter/tree-sitter/pull/3097>)
- **deps**: Bump deps & lockfile (<https://github.com/tree-sitter/tree-sitter/pull/3060>)
- **deps**: Bump the cargo group with 4 updates (<https://github.com/tree-sitter/tree-sitter/pull/3134>)
- **lint**: Detect if `Cargo.lock` needs to be updated (<https://github.com/tree-sitter/tree-sitter/pull/3066>)
- **lint**: Make lockfile check quiet (<https://github.com/tree-sitter/tree-sitter/pull/3078>)
- **swift**: Move 'cLanguageStandard' behind 'targets' (<https://github.com/tree-sitter/tree-sitter/pull/3101>)

### Other

- Make Node.js language bindings context aware (<https://github.com/tree-sitter/tree-sitter/pull/2841>)
  They don't have any dynamic global data, so all it takes is just declaring them as such
- Fix crash when attempting to load ancient languages via wasm (<https://github.com/tree-sitter/tree-sitter/pull/3068>)
- Use workspace dependencies for internal crates like Tree-sitter (<https://github.com/tree-sitter/tree-sitter/pull/3076>)
- Remove vendored wasmtime headers (https://github.com/tree-sitter/tree-sitter/pull/3084)
  When building rust binding, use wasmtime headers provided via cargo
  by the wasmtime-c-api crate.
- Fix invalid parse stack recursive merging with mismatched error cost (<https://github.com/tree-sitter/tree-sitter/pull/3086>)
  Allowing this invalid merge caused an invariant to be violated
  later on during parsing, when handling a later error.
- Fix regression in `subtree_compare` (<https://github.com/tree-sitter/tree-sitter/pull/3111>)
- docs: Add `Ohm` language parser (<https://github.com/tree-sitter/tree-sitter/pull/3114>)
- Delete `binding_files.rs` (<https://github.com/tree-sitter/tree-sitter/pull/3106>)
- **bindings**: Consistent wording (<https://github.com/tree-sitter/tree-sitter/pull/3096>)
- **bindings**: Ignore more artifacts (<https://github.com/tree-sitter/tree-sitter/pull/3119>)

## [0.21.0] — 2024-02-21

### Breaking

- Remove the apply-all-captures flag, make last-wins precedence the default

  **NOTE**: This change might cause breakage in your grammar's highlight tests.
  Just flip the order around of the relevant queries, and keep in mind that the
  last query that matches will win.

### Features

- Use lockfiles to dedup recompilation
- Improve error message for files with an unknown grammar path (<https://github.com/tree-sitter/tree-sitter/pull/2475>)
- Implement first-line-regex (<https://github.com/tree-sitter/tree-sitter/pull/2479>)
- Error out if an empty string is in the `extras` array
- Allow specifying an external scanner's files (<https://github.com/tree-sitter/tree-sitter/pull/3031>)
- Better error info when a scanner is missing required symbols
- **cli**: Add an optional `grammar-path` argument for the playground (<https://github.com/tree-sitter/tree-sitter/pull/3014>)
- **cli**: Add optional `config-path` argument (<https://github.com/tree-sitter/tree-sitter/pull/3050>)
- **loader**: Add more commonly used default parser directories

### Bug Fixes

- Prettify xml output and add node position info (<https://github.com/tree-sitter/tree-sitter/pull/2970>)
- Inherited grammar generation
- Properly error out when the word property is an invalid rule
- Update schema for regex flags (<https://github.com/tree-sitter/tree-sitter/pull/3006>)
- Properly handle `Query.matches` when filtering out results (<https://github.com/tree-sitter/tree-sitter/pull/3013>)
- Sexp format edge case with quoted closed parenthesis (<https://github.com/tree-sitter/tree-sitter/pull/3016>)
- Always push the default files if there's no `externals`
- Don't log NUL characters (<https://github.com/tree-sitter/tree-sitter/pull/3037>)
- Don't throw an error if the user uses `map` in the grammar (<https://github.com/tree-sitter/tree-sitter/pull/3041>)
- Remove redundant imports (<https://github.com/tree-sitter/tree-sitter/pull/3047>)
- **cli**: Installation via a HTTP tunnel proxy (<https://github.com/tree-sitter/tree-sitter/pull/2824>)
- **cli**: Don't update tests automatically if parse errors are detected (<https://github.com/tree-sitter/tree-sitter/pull/3033>)
- **cli**: Don't use `long` for `grammar_path`
- **test**: Allow writing updates to tests without erroneous nodes instead of denying all of them if a single error is found
- **test**: Edge case when parsing `UNEXPECTED`/`MISSING` nodes with an indentation level greater than 0
- **wasm**: Remove C++ mangled symbols (<https://github.com/tree-sitter/tree-sitter/pull/2971>)

### Documentation

- Create issue template (<https://github.com/tree-sitter/tree-sitter/pull/2978>)
- Document regex limitations
- Mention that `token($.foo)` is illegal
- Explicitly mention behavior of walking outside the given "root" node for a `TSTreeCursor` (<https://github.com/tree-sitter/tree-sitter/pull/3021>)
- Small fixes (<https://github.com/tree-sitter/tree-sitter/pull/2987>)
- Add `Tact` language parser (<https://github.com/tree-sitter/tree-sitter/pull/3030>)
- **web**: Provide deno usage information (<https://github.com/tree-sitter/tree-sitter/pull/2498>)

### Refactor

- Extract regex check into a function and lower its precedence
- `&PathBuf` -> `&Path` (<https://github.com/tree-sitter/tree-sitter/pull/3035>)
- Name anonymous types in api.h (<https://github.com/tree-sitter/tree-sitter/pull/1659>)

### Testing

- Add quotes around bash variables (<https://github.com/tree-sitter/tree-sitter/pull/3023>)
- Update html tests

### Build System and CI

- Only create release for normal semver tags (<https://github.com/tree-sitter/tree-sitter/pull/2973>)
- Add useful development targets to makefile (<https://github.com/tree-sitter/tree-sitter/pull/2979>)
- Remove minimum glibc information in summary page (<https://github.com/tree-sitter/tree-sitter/pull/2988>)
- Use the native m1 mac runner (<https://github.com/tree-sitter/tree-sitter/pull/2995>)
- Add editorconfig (<https://github.com/tree-sitter/tree-sitter/pull/2998>)
- Remove symbolic links from repository (<https://github.com/tree-sitter/tree-sitter/pull/2997>)
- Move common Cargo.toml keys into the workspace and inherit them (<https://github.com/tree-sitter/tree-sitter/pull/3019>)
- Remove reviewers when drafting or closing a PR (<https://github.com/tree-sitter/tree-sitter/pull/2963>)
- Enable creating changelogs with git-cliff (<https://github.com/tree-sitter/tree-sitter/pull/3040>)
- Cache fixtures (<https://github.com/tree-sitter/tree-sitter/pull/3038>)
- Don't cancel jobs on master (<https://github.com/tree-sitter/tree-sitter/pull/3052>)
- Relax caching requirements (<https://github.com/tree-sitter/tree-sitter/pull/3051>)
- **deps**: Bump clap from 4.4.18 to 4.5.0 (<https://github.com/tree-sitter/tree-sitter/pull/3007>)
- **deps**: Bump wasmtime from v16.0.0 to v17.0.1 (<https://github.com/tree-sitter/tree-sitter/pull/3008>)
- **deps**: Bump wasmtime to v18.0.1 (<https://github.com/tree-sitter/tree-sitter/pull/3057>)
- **sanitize**: Add a timeout of 60 minutes (<https://github.com/tree-sitter/tree-sitter/pull/3017>)
- **sanitize**: Reduce timeout to 20 minutes (<https://github.com/tree-sitter/tree-sitter/pull/3054>)

### Other

- Document preferred language for scanner (<https://github.com/tree-sitter/tree-sitter/pull/2972>)
- Add java and tsx to corpus tests (<https://github.com/tree-sitter/tree-sitter/pull/2992>)
- Provide a CLI flag to open `log.html` (<https://github.com/tree-sitter/tree-sitter/pull/2996>)
- Some more clippy lints (<https://github.com/tree-sitter/tree-sitter/pull/3010>)
- Remove deprecated query parsing mechanism (<https://github.com/tree-sitter/tree-sitter/pull/3011>)
- Print out full compiler arguments ran when it fails (<https://github.com/tree-sitter/tree-sitter/pull/3018>)
- Deprecate C++ scanners (<https://github.com/tree-sitter/tree-sitter/pull/3020>)
- Add some documentation to the playground page (<https://github.com/tree-sitter/tree-sitter/pull/1495>)
- Update relevant rust tests (<https://github.com/tree-sitter/tree-sitter/pull/2947>)
- Clippy lints (<https://github.com/tree-sitter/tree-sitter/pull/3032>)
- Error out when multiple arguments are passed to `token`/`token.immediate` (<https://github.com/tree-sitter/tree-sitter/pull/3036>)
- Tidying
- Prefer turbofish syntax where possible (<https://github.com/tree-sitter/tree-sitter/pull/3048>)
- Use published wasmtime crates
- Cleaner cast
- Update `Cargo.lock`
- Get rid of `github_issue_test` file (<https://github.com/tree-sitter/tree-sitter/pull/3055>)
- **cli**: Use spawn to display `emcc`'s stdout and stderr (<https://github.com/tree-sitter/tree-sitter/pull/2494>)
- **cli**: Warn users when a query path needed for a subcommand isn't specified in a grammar's package.json
- **generate**: Dedup and warn about duplicate or invalid rules (<https://github.com/tree-sitter/tree-sitter/pull/2994>)
- **test**: Use different languages for async tests (<https://github.com/tree-sitter/tree-sitter/pull/2953>)
- **wasm**: Use `SIDE_MODULE=2` to silence warning (<https://github.com/tree-sitter/tree-sitter/pull/3003>)
