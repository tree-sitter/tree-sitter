# Vendored WASI libc sources

These files are copied from
[`WebAssembly/wasi-libc`](https://github.com/WebAssembly/wasi-libc) commit
`161b3195fc2558d2b1ba3eb9ffae3b2b47407623`, which is the `wasi-libc`
submodule revision pinned by WASI SDK 33.

The allowlist is maintained by `cargo xtask vendor-wasm-stdlib`. Run that
command after changing `crates/loader/wasi-sdk-version` or the pinned
`WASI_LIBC_REVISION` in `crates/xtask/src/build_wasm.rs`.

The files under `string/` and `ctype/`, as well as `LICENSE`, are copied
verbatim. `lib/src/wasm-stdlib/libc.c` combines the selected translation units
and renames colliding file-local table identifiers; it is maintained by
Tree-sitter.
