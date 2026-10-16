# Rust Wasm Web Test

This is a minimal example of using the `tree-sitter` Rust crate within a larger application that is compiled to WebAssembly and embedded within a JavaScript engine. It uses web workers to perform parsing on a background thread while still sharing memory with the main thread. One grammar crate is included in the main module as a Rust dependency, and two other grammar crates are dynamically loaded as separate modules.

`cargo xtask test-rust-wasm-web` also loads the unshared Ruby grammar generated
by `cargo xtask generate-fixtures --wasm` from `target/release` and runs the
`js-loader` tests with both shared and unshared Rust/Wasm hosts. That check
requires `wasm-bindgen-test-runner` matching the workspace's `wasm-bindgen`
version and a nightly toolchain with `rust-src`.
