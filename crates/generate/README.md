# Tree-sitter Generate

This helper crate implements the logic for the `tree-sitter generate` command,
and can be used by external tools to generate a parser from a grammar file.

## Testing the grammar DSLs

From the repository root:

```sh
cargo test -p tree-sitter-generate
node --test crates/generate/src/dsl.test.mjs
```

The Rust tests include embedded QuickJS loading and parser generation. The Node
tests exercise the same embedded JavaScript bootstrap with both legacy and
module grammars, including inheritance, configuration, and diagnostics.

The CLI package also tests the declarations against TypeScript's language
service, including recursive inference, go-to-definition, references, and rename:

```sh
npm ci --prefix crates/cli/npm --ignore-scripts
npm test --prefix crates/cli/npm
```

Skipping install scripts avoids downloading a released CLI binary when testing
the local declarations. The JavaScript test runners require Node 18 or newer.
