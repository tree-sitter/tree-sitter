Tree-sitter Highlighting
=========================

[![Build Status](https://travis-ci.org/tree-sitter/tree-sitter.svg?branch=master)](https://travis-ci.org/tree-sitter/tree-sitter)
[![Build status](https://ci.appveyor.com/api/projects/status/vtmbd6i92e97l55w/branch/master?svg=true)](https://ci.appveyor.com/project/maxbrunsfeld/tree-sitter/branch/master)
[![Crates.io](https://img.shields.io/crates/v/tree-sitter-highlight.svg)](https://crates.io/crates/tree-sitter-highlight)

### Usage

Compile some languages into your app, and declare them:

```rust
extern "C" tree_sitter_html();
extern "C" tree_sitter_javascript();
```

Load some *property sheets*:

```rust
use tree_sitter_highlight::load_property_sheet;

let javascript_property_sheet = load_property_sheet(
  fs::read_to_string("./tree-sitter-javascript/src/highlights.json").unwrap()
).unwrap();

let html_property_sheet = load_property_sheet(
  fs::read_to_string("./tree-sitter-html/src/highlights.json").unwrap()
).unwrap();
```

Highlight some code:

```rust
use tree_sitter_highlight::{highlight, HighlightEvent};

let highlights = highlight(
    b"const x = new Y();",
    unsafe { tree_sitter_javascript() },
    &javascript_property_sheet,
    &|_| None
).unwrap();

for event in highlights {
    match event {
        HighlightEvent::Source(s) {
            eprintln!("source: {:?}", s);
        },
        HighlightEvent::ScopeStart(s) {
            eprintln!("scope started: {:?}", s);
        },
        HighlightEvent::ScopeEnd(s) {
            eprintln!("scope ended: {:?}", s);
        },
    }
}
```

The last parameter to `highlight` is a *language injection* callback. This allows other languages to be retrieved when Tree-sitter detects an embedded document (for example, a piece of JavaScript code inside of a `script` tag within HTML).
