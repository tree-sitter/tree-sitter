use crate::{LanguageError, Parser};

use super::ffi;
use std::{ffi::CString, os::raw::c_char};
pub use wasmtime;

#[cfg(feature = "wasm")]
pub fn test() {
    wasmtime_c_api::wasm_engine_new();
}

#[repr(C)]
#[derive(Clone)]
pub struct wasm_engine_t {
    pub(crate) engine: wasmtime::Engine,
}

pub struct WasmStore(*mut ffi::TSWasmStore);
pub struct WasmLanguage(*const ffi::TSWasmLanguage);

impl WasmStore {
    pub fn new(engine: wasmtime::Engine) -> Self {
        let mut c_engine = wasm_engine_t { engine };
        let c_engine = &mut c_engine as *mut _;
        WasmStore(unsafe { ffi::ts_wasm_store_new(c_engine as *mut _) })
    }

    pub fn load_language(&mut self, name: &str, bytes: &[u8]) -> WasmLanguage {
        let name = CString::new(name).unwrap();
        WasmLanguage(unsafe {
            ffi::ts_wasm_store_load_language(
                self.0,
                name.as_ptr(),
                bytes.as_ptr() as *const c_char,
                bytes.len() as u32,
            )
        })
    }
}

impl Parser {
    pub fn wasm_language(&self) -> Option<WasmLanguage> {
        let language = unsafe { ffi::ts_parser_wasm_language(self.0.as_ptr()) };
        if language.is_null() {
            None
        } else {
            Some(WasmLanguage(language))
        }
    }

    pub fn set_wasm_language(&mut self, language: WasmLanguage) -> Result<(), LanguageError> {
        unsafe {
            ffi::ts_parser_set_wasm_language(self.0.as_ptr(), language.0);
        }
        Ok(())
    }

    pub fn set_wasm_store(&mut self, language: WasmStore) -> Result<(), LanguageError> {
        unsafe {
            ffi::ts_parser_set_wasm_store(self.0.as_ptr(), language.0);
        }
        Ok(())
    }
}

impl Drop for WasmLanguage {
    fn drop(&mut self) {
        unsafe { ffi::ts_wasm_language_delete(self.0) };
    }
}

impl Drop for WasmStore {
    fn drop(&mut self) {
        unsafe { ffi::ts_wasm_store_delete(self.0) };
    }
}
