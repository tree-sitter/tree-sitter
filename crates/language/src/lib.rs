mod language;
pub use language::*;

#[cfg(all(target_arch = "wasm32", target_os = "unknown"))]
mod stdlib;
#[cfg(all(target_arch = "wasm32", target_os = "unknown"))]
pub use stdlib::*;
