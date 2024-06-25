## Subdirectories

* [`src`](./src) - C source code for the Tree-sitter library
* [`include`](./include) - C headers for the Tree-sitter library
* [`binding_rust`](./binding_rust) - Rust bindings to the Tree-sitter library
* [`binding_web`](./binding_web) - JavaScript bindings to the Tree-sitter library, using WebAssembly

## no_std support

The tree-sitter crate has a feature named `std` that is enabled by default. In order to use tree-sitter 
in a no_std environment, this feature needs to be disabled. Modify your tree-sitter dependency in Cargo.toml
to opt out of enabled_by-default feature:

```toml
tree-sitter = { version = "^0.22.6", default-features = false}
```
