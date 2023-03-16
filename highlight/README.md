# `tree-sitter-highlight`

[![Crates.io](https://img.shields.io/crates/v/tree-sitter-highlight.svg)](https://crates.io/crates/tree-sitter-highlight)

### Usage

Add this crate, and the language-specific crates for whichever languages you want to parse, to your `Cargo.toml`:

```toml
[dependencies]
tree-sitter-highlight = "0.19"
tree-sitter-html = "0.19"
tree-sitter-javascript = "0.19"
```

Define the list of highlight names that you will recognize:

```rust
let highlight_names = &[
    "attribute",
    "constant",
    "function.builtin",
    "function",
    "keyword",
    "operator",
    "property",
    "punctuation",
    "punctuation.bracket",
    "punctuation.delimiter",
    "string",
    "string.special",
    "tag",
    "type",
    "type.builtin",
    "variable",
    "variable.builtin",
    "variable.parameter",
];
```

Create a highlighter. You need one of these for each thread that you're using for syntax highlighting:

```rust
use tree_sitter_highlight::Highlighter;

let highlighter = Highlighter::new();
```

Load some highlighting queries from the `queries` directory of some language repositories:

```rust
use tree_sitter_highlight::HighlightConfiguration;

let html_language = unsafe { tree_sitter_html() };
let javascript_language = unsafe { tree_sitter_javascript() };

let html_config = HighlightConfiguration::new(
    tree_sitter_html::language(),
    tree_sitter_html::HIGHLIGHTS_QUERY,
    tree_sitter_html::INJECTIONS_QUERY,
    "",
).unwrap();

let javascript_config = HighlightConfiguration::new(
    tree_sitter_javascript::language(),
    tree_sitter_javascript::HIGHLIGHTS_QUERY,
    tree_sitter_javascript::INJECTIONS_QUERY,
    tree_sitter_javascript::LCOALS_QUERY,
).unwrap();
```

Configure the recognized names:

```rust
javascript_config.configure(&highlight_names);
```

Highlight some code:

```rust
use tree_sitter_highlight::HighlightEvent;

let highlights = highlighter.highlight(
    &javascript_config,
    b"const x = new Y();",
    None,
    |_| None
).unwrap();

for event in highlights {
    match event.unwrap() {
        HighlightEvent::Source {start, end} => {
            eprintln!("source: {}-{}", start, end);
        },
        HighlightEvent::HighlightStart(s) => {
            eprintln!("highlight style started: {:?}", s);
        },
        HighlightEvent::HighlightEnd => {
            eprintln!("highlight style ended");
        },
    }
}
```

The last parameter to `highlight` is a *language injection* callback. This allows other languages to be retrieved when Tree-sitter detects an embedded document (for example, a piece of JavaScript code inside of a `script` tag within HTML).
