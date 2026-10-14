//! Loads trusted grammar side modules into a Rust Wasm application's memory.
//!
//! Grammars loaded here share the caller's memory and function table. Only load
//! trusted modules: Wasm memory isolation does not apply between these modules
//! and the application. A loaded language is usable for parsing only in the
//! Wasm instance that linked it, so each worker must load its own instance.
//!
//! Enable `js-loader` on `wasm32-unknown-unknown`, then process the final
//! application binary with wasm-bindgen and initialize it through the generated
//! JavaScript glue. Merely supplying `env.memory` to `WebAssembly.instantiate`
//! does not provide the `js-sys` and loader imports these functions need.

use js_sys::{Object, Reflect, Uint8Array, WebAssembly};
use wasm_bindgen::{JsCast, JsValue, prelude::wasm_bindgen};
use wasm_bindgen_futures::JsFuture;

use crate::{
    LANGUAGE_VERSION, Language, MIN_COMPATIBLE_LANGUAGE_VERSION, ffi,
    wasm_stdlib::wasm_stdlib_functions,
};

#[wasm_bindgen(module = "/binding_rust/js_loader.js")]
unsafe extern "C" {
    #[wasm_bindgen(catch, js_name = linkGrammarModuleAsync)]
    fn link_grammar_module_async(
        bytes: &Uint8Array,
        memory: &WebAssembly::Memory,
        table: &WebAssembly::Table,
        host_functions: &Object,
        minimum_abi: u32,
        maximum_abi: u32,
    ) -> Result<js_sys::Promise, JsValue>;

    #[wasm_bindgen(catch, js_name = linkGrammarModuleSync)]
    fn link_grammar_module_sync(
        bytes: &Uint8Array,
        memory: &WebAssembly::Memory,
        table: &WebAssembly::Table,
        host_functions: &Object,
        minimum_abi: u32,
        maximum_abi: u32,
    ) -> Result<JsValue, JsValue>;
}

/// Loads one grammar into the current Wasm instance without blocking compilation.
///
/// Call this on a browser main thread. `memory_maximum_pages` must be the
/// maximum declared by `memory`, or `None` for unshared memory without one.
///
/// # Errors
///
/// Returns an error for invalid imports, grammar ABI, or failed compilation.
///
/// # Safety
///
/// `memory` and `table` must be the current Rust Wasm instance's own memory
/// and function table. The grammar executes within that memory without
/// isolation, so its code must be trusted not to corrupt the application.
pub async unsafe fn load_language(
    memory: &WebAssembly::Memory,
    table: &WebAssembly::Table,
    bytes: &Uint8Array,
    memory_maximum_pages: Option<u32>,
) -> Result<Language, JsValue> {
    let bytes = prepare_bytes(memory, bytes, memory_maximum_pages)?;
    let host_functions = host_functions(table)?;
    let address = JsFuture::from(link_grammar_module_async(
        &bytes,
        memory,
        table,
        &host_functions,
        MIN_COMPATIBLE_LANGUAGE_VERSION as u32,
        LANGUAGE_VERSION as u32,
    )?)
    .await?;
    language_from_address(memory, address)
}

/// Loads one grammar synchronously on a worker whose event loop cannot await.
///
/// Do not call this on a browser main thread with a nontrivial grammar module.
/// `memory_maximum_pages` must be the maximum declared by `memory`, or `None`
/// for unshared memory without one.
///
/// # Errors
///
/// Returns an error for invalid imports, grammar ABI, or failed compilation.
///
/// # Safety
///
/// `memory` and `table` must be the current Rust Wasm instance's own memory
/// and function table. The grammar executes within that memory without
/// isolation, so its code must be trusted not to corrupt the application.
pub unsafe fn load_language_sync(
    memory: &WebAssembly::Memory,
    table: &WebAssembly::Table,
    bytes: &Uint8Array,
    memory_maximum_pages: Option<u32>,
) -> Result<Language, JsValue> {
    let bytes = prepare_bytes(memory, bytes, memory_maximum_pages)?;
    let host_functions = host_functions(table)?;
    let address = link_grammar_module_sync(
        &bytes,
        memory,
        table,
        &host_functions,
        MIN_COMPATIBLE_LANGUAGE_VERSION as u32,
        LANGUAGE_VERSION as u32,
    )?;
    language_from_address(memory, address)
}

fn prepare_bytes(
    memory: &WebAssembly::Memory,
    bytes: &Uint8Array,
    memory_maximum_pages: Option<u32>,
) -> Result<Uint8Array, JsValue> {
    let shared = memory
        .buffer()
        .is_instance_of::<js_sys::SharedArrayBuffer>();
    let owned = bytes.to_vec();
    let adapted = crate::wasm_stdlib::memory_import::with_compatible_memory_import(
        &owned,
        memory_maximum_pages,
        shared,
    )
    .map_err(|error| js_sys::Error::new(&error.to_string()))?;
    Ok(Uint8Array::from(adapted.as_ref()))
}

fn host_functions(table: &WebAssembly::Table) -> Result<Object, JsValue> {
    let host_functions = Object::new();
    for (name, index) in wasm_stdlib_functions() {
        let index = u32::try_from(index)
            .map_err(|_| js_sys::Error::new("scanner import index exceeds the function table"))?;
        let function = table.get_raw(index)?;
        if !function.is_function() {
            return Err(js_sys::Error::new(&format!("missing scanner import {name}")).into());
        }
        Reflect::set(&host_functions, &JsValue::from_str(name), &function)?;
    }
    Ok(host_functions)
}

fn language_from_address(
    memory: &WebAssembly::Memory,
    address: JsValue,
) -> Result<Language, JsValue> {
    let pointer = address
        .as_f64()
        .ok_or_else(|| js_sys::Error::new("grammar returned a nonnumeric language address"))?;
    if pointer <= 0.0 || pointer > u32::MAX as f64 || pointer.fract() != 0.0 {
        return Err(js_sys::Error::new("grammar returned an invalid language address").into());
    }
    let pointer = pointer as u32;
    let memory_bytes = Uint8Array::new(&memory.buffer());
    let end = pointer
        .checked_add(4)
        .ok_or_else(|| js_sys::Error::new("grammar language address overflows memory"))?;
    if end > memory_bytes.length() {
        return Err(js_sys::Error::new("grammar language address lies outside memory").into());
    }
    let version_bytes = memory_bytes.subarray(pointer, end).to_vec();
    let abi_version = u32::from_le_bytes(
        version_bytes
            .try_into()
            .map_err(|_| js_sys::Error::new("missing grammar ABI version"))?,
    ) as usize;
    if !(MIN_COMPATIBLE_LANGUAGE_VERSION..=LANGUAGE_VERSION).contains(&abi_version) {
        return Err(js_sys::Error::new(&format!(
            "unsupported Tree-sitter grammar ABI {abi_version}"
        ))
        .into());
    }
    // SAFETY: the returned pointer is non-null and within the host memory.
    // The module instance and allocations remain live in `linkedGrammarModules`.
    Ok(unsafe { Language::from_raw(pointer as *const ffi::TSLanguage) })
}

#[cfg(test)]
mod tests;
