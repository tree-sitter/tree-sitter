Tree-sitter Tags
=========================

### Usage

Compile some languages into your app, and declare them:

```rust
extern "C" tree_sitter_python();
extern "C" tree_sitter_javascript();
```

Create a tag context. You need one of these for each thread that you're using for tag computation:

```rust
use tree_sitter_tags::TagsContext;

let context = TagsContext::new();
```

Load some tagging queries from the `queries` directory of some language repositories:

```rust
use tree_sitter_highlight::TagsConfiguration;

let python_language = unsafe { tree_sitter_python() };
let javascript_language = unsafe { tree_sitter_javascript() };

let python_config = HighlightConfiguration::new(
    python_language,
    &fs::read_to_string("./tree-sitter-python/queries/tags.scm").unwrap(),
    &fs::read_to_string("./tree-sitter-python/queries/locals.scm").unwrap(),
).unwrap();

let javascript_config = HighlightConfiguration::new(
    javascript_language,
    &fs::read_to_string("./tree-sitter-javascript/queries/tags.scm").unwrap(),
    &fs::read_to_string("./tree-sitter-javascript/queries/locals.scm").unwrap(),
).unwrap();
```

Compute code navigation tags for some source code:

```rust
use tree_sitter_highlight::HighlightEvent;

let tags = context.generate_tags(
    &javascript_config,
    b"class A { getB() { return c(); } }",
    None,
    |_| None
);

for tag in tags {
    println!("kind: {:?}", tag.kind);
    println!("range: {:?}", tag.range);
    println!("name_range: {:?}", tag.name_range);
    println!("docs: {:?}", tag.docs);
}
```
