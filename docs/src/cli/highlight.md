# `tree-sitter highlight`

You can run syntax highlighting on an arbitrary file using `tree-sitter highlight`. This can either output colors directly
to your terminal using ANSI escape codes, or produce HTML (if the `--html` flag is passed). For more information, see
[the syntax highlighting page](../3-syntax-highlighting.md).

```bash
tree-sitter highlight [OPTIONS] [PATHS]... # Aliases: hi
```

## Options

### `-H/--html`

Output an HTML document with syntax highlighting.

### `--layout <LAYOUT>`

When generating HTML, the document structure to emit. One of:

- `document` (default): a complete, self-contained HTML document wrapping a plain `<div class="highlight"><pre><code>`
  block.
- `line-numbers`: a complete document with a line-number column (a `<table>` layout).
- `fragment`: only the code markup, without the surrounding `<head>`/`<style>`/`<body>` document, so it can be embedded
  in an existing page.

### `--style <STYLE>`

When generating HTML, how token colors are applied. One of:

- `classes` (default): `class="..."` spans plus a generated `<style>` block carrying the theme's colors.
- `inline`: `style="..."` spans with the colors inlined, so the markup is self-contained.
- `minimal`: `class="..."` spans with no colors emitted (supply your own stylesheet).

### `--check`

Check that the highlighting captures conform strictly to the standards.

### `--captures-path <CAPTURES_PATH>`

The path to a file with captures. These captures would be considered the "standard" captures to compare against.

### `--query-paths <QUERY_PATHS>`

The paths to query files to use for syntax highlighting. These should end in `highlights.scm`.

### `--scope <SCOPE>`

The language scope to use for syntax highlighting. This is useful when the language is ambiguous.

### `-t/--time`

Print the time taken to highlight the file.

### `-q/--quiet`

Suppress main output.

### `--paths <PATHS_FILE>`

The path to a file that contains paths to source files to highlight

### `-p/--grammar-path <PATH>`

The path to the directory containing the grammar.

### `--config-path <CONFIG_PATH>`

The path to an alternative configuration (`config.json`) file. See [the init-config command](./init-config.md) for more
information.

### `-n/--test-number <TEST_NUMBER>`

Highlight the contents of a specific test.

### `-r/--rebuild`

Force a rebuild of the parser before running the fuzzer.
