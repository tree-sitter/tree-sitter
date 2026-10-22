use wasm_bindgen_test::wasm_bindgen_test;

use super::*;

const RUBY_GRAMMAR: &[u8] = include_bytes!(concat!(
    env!("CARGO_MANIFEST_DIR"),
    "/../target/release/tree-sitter-ruby.wasm"
));
#[wasm_bindgen_test]
async fn loads_unshared_grammar_with_real_scanner_functions() {
    let (memory, table) = host();
    let bytes = Uint8Array::from(RUBY_GRAMMAR);
    // SAFETY: the host values belong to this Wasm instance, and the fixture
    // was compiled from Tree-sitter's fetched Ruby grammar source.
    let language = unsafe { load_language(&memory, &table, &bytes, host_maximum(&memory)) }
        .await
        .expect("link Ruby grammar");
    let mut parser = crate::Parser::new();
    parser.set_language(&language).expect("set Ruby grammar");
    let tree = parser.parse("class A; end", None).expect("parse Ruby");
    assert_eq!(
        tree.root_node().to_sexp(),
        "(program (class name: (constant)))"
    );
}

#[wasm_bindgen_test]
fn loads_grammar_synchronously() {
    let (memory, table) = host();
    let bytes = Uint8Array::from(RUBY_GRAMMAR);
    // SAFETY: the host values belong to this Wasm instance, and the fixture
    // was compiled from Tree-sitter's fetched Ruby grammar source.
    let language = unsafe { load_language_sync(&memory, &table, &bytes, host_maximum(&memory)) }
        .expect("link Ruby grammar synchronously");
    let mut parser = crate::Parser::new();
    parser.set_language(&language).expect("set Ruby grammar");
    assert!(
        !parser
            .parse("class B; end", None)
            .expect("parse Ruby")
            .root_node()
            .has_error()
    );
}

#[wasm_bindgen_test]
fn failed_link_clears_new_table_entries_before_releasing_memory() {
    let (memory, table) = host();
    let bytes = Uint8Array::from(RUBY_GRAMMAR);
    let bytes = prepare_bytes(&memory, &bytes, host_maximum(&memory)).unwrap();
    let functions = host_functions(&table).unwrap();
    let old_table_length = table.length();

    // Reject the grammar only after instantiation and its data relocations.
    let result = link_grammar_module_sync(
        &bytes,
        &memory,
        &table,
        &functions,
        LANGUAGE_VERSION as u32 + 1,
        LANGUAGE_VERSION as u32 + 1,
    );
    assert!(result.is_err());
    assert!(table.length() > old_table_length);
    for index in old_table_length..table.length() {
        assert!(
            table.get_raw(index).unwrap().is_null(),
            "table entry {index}"
        );
    }

    // A failed link must not prevent another grammar from loading and parsing.
    let language = unsafe { load_language_sync(&memory, &table, &bytes, host_maximum(&memory)) }
        .expect("link Ruby grammar after failed attempt");
    let mut parser = crate::Parser::new();
    parser.set_language(&language).expect("set Ruby grammar");
    assert!(
        !parser
            .parse("class B; end", None)
            .unwrap()
            .root_node()
            .has_error()
    );
}

#[wasm_bindgen_test]
fn scanner_imports_are_callable_in_the_host_table() {
    let (_, table) = host();
    let functions = wasm_stdlib_functions();
    assert_eq!(
        functions.iter().map(|(name, _)| *name).collect::<Vec<_>>(),
        crate::wasm_stdlib_symbols().collect::<Vec<_>>()
    );
    for (name, index) in &functions {
        assert!(
            table.get_raw(*index as u32).unwrap().is_function(),
            "missing scanner import {name}"
        );
    }
    let (_, index) = functions
        .iter()
        .find(|(name, _)| *name == "iswalpha")
        .unwrap();
    let iswalpha: js_sys::Function = table.get_raw(*index as u32).unwrap().dyn_into().unwrap();
    assert_eq!(
        iswalpha
            .call1(&JsValue::NULL, &JsValue::from_f64('A' as u32 as f64))
            .unwrap()
            .as_f64(),
        Some(1.0)
    );
}

fn host() -> (WebAssembly::Memory, WebAssembly::Table) {
    let (memory, table): (WebAssembly::Memory, WebAssembly::Table) = (
        wasm_bindgen::memory()
            .dyn_into()
            .expect("test module's WebAssembly.Memory"),
        wasm_bindgen::function_table()
            .dyn_into()
            .expect("test module's WebAssembly.Table"),
    );
    assert_eq!(
        memory
            .buffer()
            .is_instance_of::<js_sys::SharedArrayBuffer>(),
        option_env!("TREE_SITTER_JS_LOADER_TEST_HOST") == Some("shared")
    );
    (memory, table)
}

fn host_maximum(memory: &WebAssembly::Memory) -> Option<u32> {
    memory
        .buffer()
        .is_instance_of::<js_sys::SharedArrayBuffer>()
        .then_some(4_096)
}
