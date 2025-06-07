# Tree-sitter Tags

[![crates.io badge]][crates.io]

[crates.io]: https://crates.io/crates/tree-sitter-tags
[crates.io badge]: https://img.shields.io/crates/v/tree-sitter-tags.svg?color=%23B48723

### Usage

Add this crate, and the language-specific crates for whichever languages you want to parse, to your `Cargo.toml`:

```toml
[dependencies]
tree-sitter-tags = "0.19"
tree-sitter-javascript = "0.19"
tree-sitter-python = "0.19"
```

Create a tag context. You need one of these for each thread that you're using for tag computation:

```rust
use tree_sitter_tags::TagsContext;

let context = TagsContext::new();
```

Load some tagging queries from the `queries` directory of some language repositories:

```rust
use tree_sitter_tags::TagsConfiguration;

let python_config = TagsConfiguration::new(
    tree_sitter_python::language(),
    tree_sitter_python::TAGGING_QUERY,
    "",
).unwrap();

let javascript_config = TagsConfiguration::new(
    tree_sitter_javascript::language(),
    tree_sitter_javascript::TAGGING_QUERY,
    tree_sitter_javascript::LOCALS_QUERY,
).unwrap();
```

Compute code navigation tags for some source code:

```rust
let tags = context.generate_tags(
    &javascript_config,
    b"class A { getB() { return c(); } }",
    None,
);

for tag in tags {
    println!("kind: {:?}", tag.kind);
    println!("range: {:?}", tag.range);
    println!("name_range: {:?}", tag.name_range);
    println!("docs: {:?}", tag.docs);
}
```
