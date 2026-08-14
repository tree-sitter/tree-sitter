# Unsupported Tree-sitter 0.26 Wasm build

Published versions of the `tree-sitter` Rust crate through 0.26 compile
`stdio.c`, `stdlib.c`, and `string.c` from the directory advertised by
`tree-sitter-language`'s `wasm-src` build-script metadata when targeting
`wasm32-unknown-unknown`.

That integration used a separate, non-thread-safe allocator and an incomplete
libc implementation. Current versions of Tree-sitter instead provide their own
Wasm libc implementation and forward C allocation functions to Rust's
application-selected global allocator.

The translation units in this directory produce an actionable compilation
error for old Tree-sitter versions. They can be removed in a breaking
`tree-sitter-language` release that those older runtimes cannot select.
