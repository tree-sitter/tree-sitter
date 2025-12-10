# `tree-sitter generate`

The most important command you'll use is `tree-sitter generate`. This command reads the `grammar.js` file in your current
working directory and creates a file called `src/parser.c`, which implements the parser. After making changes to your grammar,
just run `tree-sitter generate` again.

```bash
tree-sitter generate [OPTIONS] [GRAMMAR_PATH] # Aliases: gen, g
```

The grammar path argument allows you to specify a path to a `grammar.js` JavaScript file, or `grammar.json` JSON file.
In case your `grammar.js` file is in a non-standard path, you can specify it yourself. But, if you are using a parser
where `grammar.json` was already generated, or it was hand-written, you can tell the CLI to generate the parser *based*
on this JSON file. This avoids relying on a JavaScript file and avoids the dependency on a JavaScript runtime.

If there is an ambiguity or *local ambiguity* in your grammar, Tree-sitter will detect it during parser generation, and
it will exit with a `Unresolved conflict` error message. To learn more about conflicts and how to handle them, check out
the section on [`Structuring Rules Well`](../creating-parsers/3-writing-the-grammar.md#structuring-rules-well)
in the user guide.

## Options

### `-l/--log`

Print the log of the parser generation process. This is really only useful if you know what you're doing, or are investigating
a bug in the CLI itself. It logs info such as what tokens are included in the error recovery state,
what keywords were extracted, what states were split and why, and the entry point state.

### `--abi <VERSION>`

The ABI to use for parser generation. The default is ABI 15, with ABI 14 being a supported target.

### `--no-parser`

Only generate `grammar.json` and `node-types.json`

### `-o/--output`

The directory to place the generated parser in. The default is `src/` in the current directory.

### `--report-states-for-rule <RULE>`

Print the overview of states from the given rule. This is useful for debugging and understanding the generated parser's
item sets for all given states in a given rule. To solely view state count numbers for rules, pass in `-` for the rule argument.
To view the overview of states for every rule, pass in `*` for the rule argument.

### `--json-summary`

Report conflicts in a JSON format.

### `--js-runtime <EXECUTABLE>`

The path to the JavaScript runtime executable to use when generating the parser. The default is `node`.
Note that you can also set this with `TREE_SITTER_JS_RUNTIME`. Starting from version 0.26.0, you can
also pass in `native` to use the experimental native QuickJS runtime that comes bundled with the CLI.
This avoids the dependency on a JavaScript runtime entirely. The native QuickJS runtime is compatible
with ESM as well as with CommonJS in strict mode. If your grammar depends on `npm` to install dependencies such as base grammars, the native runtime can be used *after* running `npm install`.

### `--disable-optimization`

Disable optimizations when generating the parser. Currently, this only affects the merging of compatible parse states.
