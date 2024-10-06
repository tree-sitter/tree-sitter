# Changelog

## [0.24.2] - 2024-10-06

### Features

- Drop legacy binding updates

### Bug Fixes

- **templates**: Properly replace author email

### Build System and CI

- **bindings**: Improve cmake file
- **cmake**: Support amalgamated build
- **cmake**: Correct library scopes
- **make**: Fix `tree-sitter.pc` generation (#3745)

### Other

- **templates**: Update npm packages

## [0.24.1] - 2024-10-04

### Bug Fixes

- **generate**: Move generated header files into the generate crate

### Other

- 0.24.1

## [0.24.0] - 2024-10-04

### Breaking

- Remove C++ support for external scanners (<https://github.com/tree-sitter/tree-sitter/pull/3602>)
- Remove `filter` flag from commands in favor of `include` and `exclude` (<https://github.com/tree-sitter/tree-sitter/pull/3604>)
- Remove the `build-wasm` subcommand (<https://github.com/tree-sitter/tree-sitter/pull/3605>)
- Move generation of grammar files to an `init` command (<https://github.com/tree-sitter/tree-sitter/pull/3694>)
- Implement `StreamingIterator` instead of `Iterator` for `QueryMatches` and `QueryCaptures` (<https://github.com/tree-sitter/tree-sitter/pull/3504>)
- **generate**: Remove unused rules (<https://github.com/tree-sitter/tree-sitter/pull/3722>)
- **lib**: Child_containing_descendant now returns direct children (<https://github.com/tree-sitter/tree-sitter/pull/3703>)
- **lib**: Treat nodes' end ranges exclusively in `goto_first_child_for_{byte,point}` (<https://github.com/tree-sitter/tree-sitter/pull/3263>)

### Features

- Add an API to time out query executions (<https://github.com/tree-sitter/tree-sitter/pull/3559>)
- Add `field_name_for_named_child` (<https://github.com/tree-sitter/tree-sitter/pull/3614>)
- Add `root` field in node-types.json (<https://github.com/tree-sitter/tree-sitter/pull/3615>)
- Add eslint configuration package (<https://github.com/tree-sitter/tree-sitter/pull/3666>)
- Provide a `rebuild` flag to force rebuild parsers (<https://github.com/tree-sitter/tree-sitter/pull/3672>)
- Add shell completions (<https://github.com/tree-sitter/tree-sitter/pull/3675>)
- Move generate logic to its own crate (<https://github.com/tree-sitter/tree-sitter/pull/3689>)
- Add `--overview-only` to `test` subcommand (<https://github.com/tree-sitter/tree-sitter/pull/3501>)
- Move tree-sitter configuration to dedicated file (#3700) (<https://github.com/tree-sitter/tree-sitter/pull/3700>)
- **api**: Expose function to check if symbol represents a supertype (<https://github.com/tree-sitter/tree-sitter/pull/3616>)
- **bindings**: Bump `go-tree-sitter` version (<https://github.com/tree-sitter/tree-sitter/pull/3564>)
- **cli**: Add a `no-ranges` flag to the parse command (<https://github.com/tree-sitter/tree-sitter/pull/3687>)
- **generate**: Bump `tree-sitter` dev dependency to `0.23` (<https://github.com/tree-sitter/tree-sitter/pull/3563>)
- **generate**: Add a no-op `--no-bindings` flag
- **init**: Add an update flag (<https://github.com/tree-sitter/tree-sitter/pull/3698>)
- **language**: Derive Clone and Copy on LanguageFn (<https://github.com/tree-sitter/tree-sitter/pull/3585>)
- **schema**: Misc improvements (<https://github.com/tree-sitter/tree-sitter/pull/3681>)
- **test**: Test all queries

### Bug Fixes

- Correct comment quote (<https://github.com/tree-sitter/tree-sitter/pull/3630>)
- Properly handle utf8 code points for highlight and tag assertions (<https://github.com/tree-sitter/tree-sitter/pull/3610>)
- Do not generate spurious files if the grammar path is not the default path (<https://github.com/tree-sitter/tree-sitter/pull/3677>)
- Disallow empty string literals in rules (<https://github.com/tree-sitter/tree-sitter/pull/3679>)
- Correct test name parsing when the prior test has equal signs (<https://github.com/tree-sitter/tree-sitter/pull/3704>)
- Handle more cases of editing subtrees that depend on column values (<https://github.com/tree-sitter/tree-sitter/pull/3257>)
- Exclude APIs that dup given file descriptors from WASI builds (<https://github.com/tree-sitter/tree-sitter/pull/3475>)
- Deprecate `child_containing_descendant` and add `child_with_descendant` instead (<https://github.com/tree-sitter/tree-sitter/pull/3708>)
- **binding_web**: Correct `edit` signature (<https://github.com/tree-sitter/tree-sitter/pull/3599>)
- **binding_web**: Remove nonexistent function definition (<https://github.com/tree-sitter/tree-sitter/pull/3612>)
- **bindings**: Use `RUST_BINDING_VERSION` in `Cargo.toml` template
- **bindings**: Lower go version to `1.22` (<https://github.com/tree-sitter/tree-sitter/pull/3711>)
- **build**: Correct wasm root path lookup (<https://github.com/tree-sitter/tree-sitter/pull/3723>)
- **build**: Force rebuild parsers when build is invoked (<https://github.com/tree-sitter/tree-sitter/pull/3729>)
- **cli**: Remove conflicting short flags in the `fuzz` subcommand (<https://github.com/tree-sitter/tree-sitter/pull/3562>)
- **cli**: Keep skipped tests unchanged in the test/corpus (<https://github.com/tree-sitter/tree-sitter/pull/3590>)
- **cli**: Remove duplicate short options from `fuzz` command (#3635) (<https://github.com/tree-sitter/tree-sitter/pull/3635>)
- **cli**: Generate the parser version from the config as well
- **docs**: Fix highlight readme example using compatible versions (<https://github.com/tree-sitter/tree-sitter/pull/3573>)
- **fuzz**: Skip tests marked with `:skip` & don't report errors on tests marked with `:error` (<https://github.com/tree-sitter/tree-sitter/pull/3640>)
- **generate**: Remove necessary files from gitignore template (<https://github.com/tree-sitter/tree-sitter/pull/3561>)
- **generate**: Disallow inline variables referencing themselves (<https://github.com/tree-sitter/tree-sitter/pull/3569>)
- **generate**: Add `tree-sitter` to the `dev-dependencies` of the Cargo.toml (<https://github.com/tree-sitter/tree-sitter/pull/3597>)
- **generate**: Do not generate large character sets for unused variables (<https://github.com/tree-sitter/tree-sitter/pull/3606>)
- **generate**: Remove excludes in `Package.swift` (<https://github.com/tree-sitter/tree-sitter/pull/3631>)
- **generate**: Add `*.scm` section to `.editorconfig` template (<https://github.com/tree-sitter/tree-sitter/pull/3724>)
- **generate**: Filter out unused rules in other spots (<https://github.com/tree-sitter/tree-sitter/pull/3726>)
- **init**: Fix some schema issues
- **init**: Don't prompt to reconfigure (<https://github.com/tree-sitter/tree-sitter/pull/3713>)
- **init**: Do not migrate `package.json` on error (<https://github.com/tree-sitter/tree-sitter/pull/3718>)
- **lib**: Correct extra node creation from non-zero root-alias cursors (<https://github.com/tree-sitter/tree-sitter/pull/3568>)
- **lib**: Backtrack to the last relevant iterator if no child was found (<https://github.com/tree-sitter/tree-sitter/pull/3570>)
- **lib**: Peek at the next sibling when iterating to find the child that contains a given descendant (<https://github.com/tree-sitter/tree-sitter/pull/3566>)
- **lib**: Correct descendant-for-range behavior with zero-width tokens (<https://github.com/tree-sitter/tree-sitter/pull/3688>)
- **lib**: Silence warnings with `-Wpedantic` (<https://github.com/tree-sitter/tree-sitter/pull/3691>)
- **lib**: Ensure an unfinished state was found before removing it (<https://github.com/tree-sitter/tree-sitter/pull/3727>)
- **rust**: Add missing TSNode functions (<https://github.com/tree-sitter/tree-sitter/pull/3571>)
- **test**: Exit with an error if a test marked with `:error` has no error
- **test**: Retain attributes when running `test -u` (<https://github.com/tree-sitter/tree-sitter/pull/3572>)
- **test**: Correctly handle assertions on empty lines (<https://github.com/tree-sitter/tree-sitter/pull/3674>)
- **wasm**: Use / paths for workdir (<https://github.com/tree-sitter/tree-sitter/pull/3658>)

### Documentation

- Add Kotlin to the playground (<https://github.com/tree-sitter/tree-sitter/pull/3560>)
- **changelog**: Add 0.23.0 release notes (<https://github.com/tree-sitter/tree-sitter/pull/3565>)

### Refactor

- Improve the grammar schema
- **cli**: Break out subcommand logic into separate functions (<https://github.com/tree-sitter/tree-sitter/pull/3676>)

### Build System and CI

- Add backport workflow (<https://github.com/tree-sitter/tree-sitter/pull/3575>)
- Bump deps (<https://github.com/tree-sitter/tree-sitter/pull/3696>)
- Bump language to `0.1.1` (<https://github.com/tree-sitter/tree-sitter/pull/3730>)
- **bindings**: Add CMakeLists.txt file (<https://github.com/tree-sitter/tree-sitter/pull/3608>)
- **cmake**: Link wasmtime dependencies (<https://github.com/tree-sitter/tree-sitter/pull/3717>)
- **deps**: Bump the cargo group across 1 directory with 11 updates (<https://github.com/tree-sitter/tree-sitter/pull/3644>)
- **deps**: Bump the cargo group with 3 updates (<https://github.com/tree-sitter/tree-sitter/pull/3671>)
- **lib**: Build using cmake (<https://github.com/tree-sitter/tree-sitter/pull/3541>)
- **make**: Support darwin cross-compile (<https://github.com/tree-sitter/tree-sitter/pull/3641>)
- **xtask**: Bump cmake version in `bump-version`
- **xtask**: Only consider major and minor versions when validating the current version
- **xtask**: Ignore the language crate

### Other

- Remove `compile_flags.txt` (<https://github.com/tree-sitter/tree-sitter/pull/3667>)
- Update generate crate paths (<https://github.com/tree-sitter/tree-sitter/pull/3697>)
- **bindings**: Update rust lib docs (<https://github.com/tree-sitter/tree-sitter/pull/3621>)
- **lib**: Add parameter names in declarations that are missing them (<https://github.com/tree-sitter/tree-sitter/pull/3692>)
- **tests**: Do not use `.as_bytes().len()` on strings (<https://github.com/tree-sitter/tree-sitter/pull/3664>)

## [0.23.2] - 2024-10-01

This release only corrected the version in a crate so publishing wouldn't fail.

## [0.23.1] - 2024-09-30

### Features

- **bindings**: Bump `go-tree-sitter` version
- **generate**: Bump `tree-sitter` dev dependency to `0.23`
- **language**: Derive Clone and Copy on LanguageFn

### Bug Fixes

- Correct comment quote
- Properly handle utf8 code points for highlight and tag assertions
- Do not generate spurious files if the grammar path is not the default path
- Disallow empty string literals in rules
- Correct test name parsing when the prior test has equal signs
- Handle more cases of editing subtrees that depend on column values
- Exclude APIs that dup given file descriptors from WASI builds
- **binding_web**: Correct `edit` signature
- **binding_web**: Remove nonexistent function definition
- **cli**: Remove conflicting short flags in the `fuzz` subcommand
- **cli**: Keep skipped tests unchanged in the test/corpus
- **cli**: Remove duplicate short options from `fuzz` command (#3635)
- **docs**: Fix highlight readme example using compatible versions
- **fuzz**: Skip tests marked with `:skip` & don't report errors on tests marked with `:error`
- **generate**: Remove necessary files from gitignore template
- **generate**: Disallow inline variables referencing themselves
- **generate**: Add `tree-sitter` to the `dev-dependencies` of the Cargo.toml
- **generate**: Do not generate large character sets for unused variables
- **generate**: Remove excludes in `Package.swift`
- **lib**: Correct extra node creation from non-zero root-alias cursors
- **lib**: Backtrack to the last relevant iterator if no child was found
- **lib**: Peek at the next sibling when iterating to find the child that contains a given descendant
- **lib**: Correct descendant-for-range behavior with zero-width tokens
- **rust**: Add missing TSNode functions
- **test**: Exit with an error if a test marked with `:error` has no error
- **test**: Retain attributes when running `test -u`
- **wasm**: Use / paths for workdir

### Build System and CI

- **deps**: Bump the cargo group across 1 directory with 11 updates
- **make**: Support darwin cross-compile

### Other

- **bindings**: Update rust lib docs

## [0.23.0] - 2024-08-26

### Breaking

- Introduce tree-sitter-language crate for grammar crates to depend on (<https://github.com/tree-sitter/tree-sitter/pull/3069>)
- Revert interning of a sequence or choice of a single rule (<https://github.com/tree-sitter/tree-sitter/pull/3548>)
- **bindings**: Use capsules in python (<https://github.com/tree-sitter/tree-sitter/pull/3384>)
- **dsl**: Support other JS runtimes (<https://github.com/tree-sitter/tree-sitter/pull/3355>)

### Features

- Add `fuzz` subcommand (<https://github.com/tree-sitter/tree-sitter/pull/3385>)
- Allow external scanners to use the logger (<https://github.com/tree-sitter/tree-sitter/pull/3204>)
- **bindings**: Add query constants to python
- **bindings**: Add node, python, swift tests (<https://github.com/tree-sitter/tree-sitter/pull/3178>)
- **bindings**: Update npm scripts (<https://github.com/tree-sitter/tree-sitter/pull/3210>)
- **cli**: Bump unicode data to v15.1.0
- **cli**: Add debug build flag (<https://github.com/tree-sitter/tree-sitter/pull/3279>)
- **cli**: Attach helpful context when `grammar.json` cannot be found (<https://github.com/tree-sitter/tree-sitter/pull/3405>)
- **cli**: Add `--show-fields` flag to `test` command (<https://github.com/tree-sitter/tree-sitter/pull/3502>)
- **lib**: Add `ts_query_end_byte_for_pattern` (<https://github.com/tree-sitter/tree-sitter/pull/3451>)
- **lib**: Support no_std
- **zig**: Update outdated path syntax (<https://github.com/tree-sitter/tree-sitter/pull/3383>)

### Bug Fixes

- Always reset to the first language when iterating over language attributes (<https://github.com/tree-sitter/tree-sitter/pull/3375>)
- Better error when a supertype rule is invalid (<https://github.com/tree-sitter/tree-sitter/pull/3400>)
- Intern a sequence or choice of a single element the same as the element itself
- Do not "absorb" rules that consist of a single terminal if the rule is hidden (<https://github.com/tree-sitter/tree-sitter/pull/2577>)
- **bindings**: Update go bindings (<https://github.com/tree-sitter/tree-sitter/pull/3544>)
- **cli**: Installation via authenticated proxy (<https://github.com/tree-sitter/tree-sitter/pull/3414>)
- **cli**: Dedup `preceding_auxiliary_symbols` (<https://github.com/tree-sitter/tree-sitter/pull/3550>)
- **dsl**: Improve error message when a rule function returns undefined (<https://github.com/tree-sitter/tree-sitter/pull/3452>)
- **generate**: Rename `cargo.toml` template (<https://github.com/tree-sitter/tree-sitter/pull/3532>)
- **go**: Update parser name in binding files, add to docs (<https://github.com/tree-sitter/tree-sitter/pull/3547>)
- **lib**: A null clock must have `tv_nsec` be 0 as well (<https://github.com/tree-sitter/tree-sitter/pull/3372>)
- **lib**: Restrict pattern_map optimization when a wildcard step has an immediate first child (<https://github.com/tree-sitter/tree-sitter/pull/3440>)
- **lib**: An empty root node should not precede an empty range (<https://github.com/tree-sitter/tree-sitter/pull/3450>)
- **lib**: Fix api header C++ interop (<https://github.com/tree-sitter/tree-sitter/pull/3534>)
- **make**: Fail properly on Windows (<https://github.com/tree-sitter/tree-sitter/pull/3418>)
- **rust**: Fetch `CARGO_MANIFEST_DIR` at runtime in build script (<https://github.com/tree-sitter/tree-sitter/pull/3352>)
- **rust**: Fix new clippy warnings (<https://github.com/tree-sitter/tree-sitter/pull/3491>)
- **test**: Multi-grammar corpus tests are now in the repo root (<https://github.com/tree-sitter/tree-sitter/pull/3342>)
- **wasm**: Update test

### Performance

- Hoist out common subexpressions in satisfies_text_predicates (<https://github.com/tree-sitter/tree-sitter/pull/3397>)

### Documentation

- Update changelog
- Remove duplicate pr # in changelog
- Add note for bullet
- Fix syntax highlighting unit testing example (<https://github.com/tree-sitter/tree-sitter/pull/3434>)
- Add tsserver annotation to example (<https://github.com/tree-sitter/tree-sitter/pull/3460>)
- Fix tree cursor documentation (<https://github.com/tree-sitter/tree-sitter/pull/3324>)
- Document rust library features (<https://github.com/tree-sitter/tree-sitter/pull/3395>)
- Clean up binding & parser lists (<https://github.com/tree-sitter/tree-sitter/pull/3443>)

### Refactor

- Remove ansi_term dependency (<https://github.com/tree-sitter/tree-sitter/pull/3387>)
- Remove difference dependency (<https://github.com/tree-sitter/tree-sitter/pull/3388>)
- **scripts**: Clean up bash scripts (<https://github.com/tree-sitter/tree-sitter/pull/3231>)

### Testing

- Modernize scanner files (<https://github.com/tree-sitter/tree-sitter/pull/3340>)

### Build System and CI

- **deps**: bump wasmtime, cc, and wasmparser (<https://github.com/tree-sitter/tree-sitter/pull/3529>
- **bindings**: Use language version in soname (<https://github.com/tree-sitter/tree-sitter/pull/3308>)
- **lib**: Include the minor in the soname
- **loader**: Make dependencies optional (<https://github.com/tree-sitter/tree-sitter/pull/1638>)
- **swift**: Declare header search path (<https://github.com/tree-sitter/tree-sitter/pull/3474>)
- **wasm**: Don't minify JS (<https://github.com/tree-sitter/tree-sitter/pull/3380>)
- **wasm**: Bump emscripten to 3.1.64 (<https://github.com/tree-sitter/tree-sitter/pull/3497>)
- **wasm**: Support big endian machines (<https://github.com/tree-sitter/tree-sitter/pull/3492>)
- **zig**: Git ignore updated Zig cache directory (<https://github.com/tree-sitter/tree-sitter/pull/3408>)

### Other

- Swap `sprintf()` for `snprintf()` (<https://github.com/tree-sitter/tree-sitter/pull/3430>)
- Add `.build` to gitignore (<https://github.com/tree-sitter/tree-sitter/pull/3498>)
- Reset language when resetting wasm store (<https://github.com/tree-sitter/tree-sitter/pull/3495>)
- Clone wasm store engine (<https://github.com/tree-sitter/tree-sitter/pull/3542>)
- **bindings**: Fix indent & line endings (<https://github.com/tree-sitter/tree-sitter/pull/3284>)

## [0.22.6] — 2024-05-05

### Features

- Improve handling of serialization buffer overflows (<https://github.com/tree-sitter/tree-sitter/pull/3318>)
- Reverse iteration through node parents (<https://github.com/tree-sitter/tree-sitter/pull/3214>)
- **cli**: Support `NO_COLOR` (<https://github.com/tree-sitter/tree-sitter/pull/3299>)
- **cli**: Add test listing and allow users to parse a specific test number (<https://github.com/tree-sitter/tree-sitter/pull/3067>)
- **grammar**: Add "inherits" field if available (<https://github.com/tree-sitter/tree-sitter/pull/3295>)

### Bug Fixes

- Correctly load field data from wasm languages
- Improve error message when the `tree-sitter` field is malformed
- Don't error out on package.json lookup errors if `--no-bindings` is passed (<https://github.com/tree-sitter/tree-sitter/pull/3323>)
- **cli**: Keep default cc flags in build
- **cli**: Properly account for multi-grammar repos when using docker to build a wasm parser (<https://github.com/tree-sitter/tree-sitter/pull/3337>)
- **generate**: Don't check arbitrarily named dirs
- **generate**: Take `AsRef<Path>` for the path parameter to avoid clones (<https://github.com/tree-sitter/tree-sitter/pull/3322>)
- **highlight**: Correct signature of `ts_highlighter_add_language`
- **lib**: Do not return field names for extras (<https://github.com/tree-sitter/tree-sitter/pull/3330>)
- **lib**: Advance the lookahead end byte by 4 when there's an invalid code point (<https://github.com/tree-sitter/tree-sitter/pull/3305>)
- **rust**: Update README example (<https://github.com/tree-sitter/tree-sitter/pull/3307>)
- **rust**: Use unix + wasi cfg instead of not windows for fd (<https://github.com/tree-sitter/tree-sitter/pull/3304>)
- **test**: Allow newlines in between test name and attribute
- **wasm**: Correct `childrenFromFieldXXX` method signatures (<https://github.com/tree-sitter/tree-sitter/pull/3301>)
- **xtask**: Always bump every crate in tandem
- **zig**: Make usable as a zig dependency (<https://github.com/tree-sitter/tree-sitter/pull/3315>)

### Documentation

- Mention build command variables
- Swap `\s` for `\\s` in query example
- **highlight**: Typo (<https://github.com/tree-sitter/tree-sitter/pull/3290>)

### Refactor

- **tests**: Migrate remaining `grammar.json` tests to `grammar.js` (<https://github.com/tree-sitter/tree-sitter/pull/3325>)

### Build System and CI

- Add nightly rustfmt to workflow for linting (<https://github.com/tree-sitter/tree-sitter/pull/3333>)
- Fix address sanitizer step (<https://github.com/tree-sitter/tree-sitter/pull/3188>)
- **deps**: Bump cc from 1.0.92 to 1.0.94 in the cargo group (<https://github.com/tree-sitter/tree-sitter/pull/3298>)
- **deps**: Bump the cargo group with 6 updates (<https://github.com/tree-sitter/tree-sitter/pull/3313>)
- **xtask**: Bump `build.zig.zon` version when bumping versions

## [0.22.5] — 2024-04-14

### Bug Fixes

- Avoid generating unused character set constants
- **cli**: Test parsing on windows (<https://github.com/tree-sitter/tree-sitter/pull/3289>)
- **rust**: Compilation on wasm32-wasi (<https://github.com/tree-sitter/tree-sitter/pull/3293>)

## [0.22.4] — 2024-04-12

### Bug Fixes

- Fix sorting of transitions within a lex state
- Include 2-character ranges in array-based state transitions

### Build System and CI

- Always bump at least the patch version in bump xtask

## [0.22.3] — 2024-04-12

### Features

- Add strncat to wasm stdlib
- Generate simpler code for matching large character sets (<https://github.com/tree-sitter/tree-sitter/pull/3234>)
- When loading languages via WASM, gracefully handle memory errors and leaks in external scanners (<https://github.com/tree-sitter/tree-sitter/pull/3181>)

### Bug Fixes

- **bindings**: Add utf-8 flag to python & node (<https://github.com/tree-sitter/tree-sitter/pull/3278>)
- **bindings**: Generate parser.c if missing (<https://github.com/tree-sitter/tree-sitter/pull/3277>)
- **bindings**: Remove required platforms for swift (<https://github.com/tree-sitter/tree-sitter/pull/3264>)
- **cli**: Fix mismatched parenthesis when accounting for `&&` (<https://github.com/tree-sitter/tree-sitter/pull/3274>)
- **lib**: Do not consider childless nodes for ts_node_parent (<https://github.com/tree-sitter/tree-sitter/pull/3191>)
- **lib**: Properly account for aliased root nodes and root nodes with
  children in `ts_subtree_string` (<https://github.com/tree-sitter/tree-sitter/pull/3191>)
- **lib**: Account for the root node of a tree cursor being an alias (<https://github.com/tree-sitter/tree-sitter/pull/3191>)
- **lib**: Use correct format specifier in log message (<https://github.com/tree-sitter/tree-sitter/pull/3255>)
- **parser**: Fix variadic macro (<https://github.com/tree-sitter/tree-sitter/pull/3229>)
- render: Proper function prototypes (<https://github.com/tree-sitter/tree-sitter/pull/3277>)
- **windows**: Add `/utf-8` flag for parsers using unicode symbols (<https://github.com/tree-sitter/tree-sitter/pull/3223>)
- Add a semicolon after SKIP macros (<https://github.com/tree-sitter/tree-sitter/pull/3264>)
- Add back `build-wasm` temporarily (<https://github.com/tree-sitter/tree-sitter/pull/3203>)
- Add lifetime to matches function (<https://github.com/tree-sitter/tree-sitter/pull/3254>)
- Default output directory for `build --wasm` should use current_dir (<https://github.com/tree-sitter/tree-sitter/pull/3203>)
- Fix sorting of wasm stdlib symbols
- Insert "tree-sitter" section in current directory's package.json if it exists (<https://github.com/tree-sitter/tree-sitter/pull/3224>)
- Tie the lifetime of the cursor to the query in `QueryCursor::captures()` (<https://github.com/tree-sitter/tree-sitter/pull/3266>)
- Wrong flag check in `build.rs`

### Performance

- **cli**: Reduced the compile time of generated parsers by generating C code with fewer conditionals (<https://github.com/tree-sitter/tree-sitter/pull/3234>)

### Documentation

- Add NGINX grammar

### Refactor

- **parser**: Make REDUCE macro non-variadic (<https://github.com/tree-sitter/tree-sitter/pull/3280>)
- **js**: Misc fixes & tidying
- **rust**: Misc fixes & tidying

### Testing

- Add regression test for node parent + string bug (<https://github.com/tree-sitter/tree-sitter/pull/3191>)
- **test**: Allow colons in test names (<https://github.com/tree-sitter/tree-sitter/pull/3264>)

### Build System and CI

- Upgrade wasmtime
- Update emscripten version (<https://github.com/tree-sitter/tree-sitter/pull/3272>)
- **dependabot**: Improve PR labels (<https://github.com/tree-sitter/tree-sitter/pull/3282>)

## [0.22.2] — 2024-03-17

### Breaking

- **cli**: Add a separate build command to compile parsers

### Features

- **bindings/rust**: Expose `Parser::included_ranges`
- Lower the lib's MSRV (<https://github.com/tree-sitter/tree-sitter/pull/3169>)
- **lib**: Implement Display for Node (<https://github.com/tree-sitter/tree-sitter/pull/3177>)

### Bug Fixes

- **bindings/wasm**: Fix `Parser.getIncludedRanges()` (<https://github.com/tree-sitter/tree-sitter/pull/3164>)
- **lib**: Makefile installation on macOS (<https://github.com/tree-sitter/tree-sitter/pull/3167>)
- **lib**: Makefile installation (<https://github.com/tree-sitter/tree-sitter/pull/3173>)
- **lib**: Avoid possible UB of calling memset on a null ptr when 0 is passed into `array_grow_by` (<https://github.com/tree-sitter/tree-sitter/pull/3176>)
- **lib**: Allow hiding symbols (<https://github.com/tree-sitter/tree-sitter/pull/3180>)

### Documentation

- Fix typo (<https://github.com/tree-sitter/tree-sitter/pull/3158>)
- **licensfe**: Update year (<https://github.com/tree-sitter/tree-sitter/pull/3183>)

### Refactor

- Remove dependency on which crate (<https://github.com/tree-sitter/tree-sitter/pull/3172>)
- Turbofish styling

### Testing

- Fix header writes (<https://github.com/tree-sitter/tree-sitter/pull/3174>)

### Build System and CI

- Simplify workflows (<https://github.com/tree-sitter/tree-sitter/pull/3002>)
- **lib**: Allow overriding CFLAGS on the commandline (<https://github.com/tree-sitter/tree-sitter/pull/3159>)

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
- Remove vendored wasmtime headers (<https://github.com/tree-sitter/tree-sitter/pull/3084>)
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
