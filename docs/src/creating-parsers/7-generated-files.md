# Working with generated files

Tree-sitter grammars produce generated artifacts such as `src/parser.c`, `src/grammar.json`,
and `src/node-types.json`. Whether to commit these files is a project choice; both approaches
are common.

## Committing generated files

**Pros**

- Consumers can build without running `tree-sitter generate`.
- CI and editor integrations see a stable parser snapshot.

**Tips**

- Regenerate in CI when `grammar.js` changes so pull requests stay in sync.
- Use a `.gitattributes` merge driver for generated C to reduce painful merges:

  ```gitattributes
  src/parser.c merge=ours
  ```

  (Adjust the strategy to match your team's workflow.)

## Ignoring generated files

**Pros**

- Smaller diffs when the grammar changes frequently.
- No risk of committing a parser built with a mismatched CLI version.

**Tips**

- Document the required `tree-sitter` CLI version in `README.md`.
- Run `tree-sitter generate` in your build script or CI before compiling.
- Keep `grammar.json` and `node-types.json` under version control if downstream tools
  depend on them, even when `parser.c` is gitignored.

## Keeping JSON artifacts in sync

If you commit `grammar.json` or `node-types.json`, regenerate them whenever the grammar
changes. Mismatched JSON and C sources cause subtle bugs in tests, queries, and editor tooling.

## Related commands

- `tree-sitter generate` — refresh parser sources from `grammar.js`.
- `tree-sitter test` — verify corpus tests against the current parser.
- `tree-sitter init --update` — refresh scaffolding without overwriting custom files.
