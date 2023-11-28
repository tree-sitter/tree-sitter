use crate::tests::helpers::fixtures::WASM_DIR;
use lazy_static::lazy_static;
use std::fs;
use tree_sitter::{wasmtime::Engine, Parser, WasmError, WasmErrorKind, WasmStore};

lazy_static! {
    static ref ENGINE: Engine = Engine::default();
}

#[test]
fn test_load_wasm_language() {
    let mut store = WasmStore::new(ENGINE.clone()).unwrap();
    let mut parser = Parser::new();

    let wasm_cpp = fs::read(&WASM_DIR.join(format!("tree-sitter-cpp.wasm"))).unwrap();
    let wasm_rs = fs::read(&WASM_DIR.join(format!("tree-sitter-rust.wasm"))).unwrap();
    let wasm_rb = fs::read(&WASM_DIR.join(format!("tree-sitter-ruby.wasm"))).unwrap();
    let wasm_typescript = fs::read(&WASM_DIR.join(format!("tree-sitter-typescript.wasm"))).unwrap();

    let language_rust = store.load_language("rust", &wasm_rs).unwrap();
    let language_cpp = store.load_language("cpp", &wasm_cpp).unwrap();
    let language_ruby = store.load_language("ruby", &wasm_rb).unwrap();
    let language_typescript = store.load_language("typescript", &wasm_typescript).unwrap();
    parser.set_wasm_store(store).unwrap();

    let mut parser2 = Parser::new();
    parser2
        .set_wasm_store(WasmStore::new(ENGINE.clone()).unwrap())
        .unwrap();

    for mut parser in [parser, parser2] {
        for _ in 0..2 {
            parser.set_language(language_cpp).unwrap();
            let tree = parser.parse("A<B> c = d();", None).unwrap();
            assert_eq!(
                tree.root_node().to_sexp(),
                "(translation_unit (declaration type: (template_type name: (type_identifier) arguments: (template_argument_list (type_descriptor type: (type_identifier)))) declarator: (init_declarator declarator: (identifier) value: (call_expression function: (identifier) arguments: (argument_list)))))"
            );

            parser.set_language(language_rust).unwrap();
            let tree = parser.parse("const A: B = c();", None).unwrap();
            assert_eq!(
                tree.root_node().to_sexp(),
                "(source_file (const_item name: (identifier) type: (type_identifier) value: (call_expression function: (identifier) arguments: (arguments))))"
            );

            parser.set_language(language_ruby).unwrap();
            let tree = parser.parse("class A; end", None).unwrap();
            assert_eq!(
                tree.root_node().to_sexp(),
                "(program (class name: (constant)))"
            );

            parser.set_language(language_typescript).unwrap();
            let tree = parser.parse("class A {}", None).unwrap();
            assert_eq!(
                tree.root_node().to_sexp(),
                "(program (class_declaration name: (type_identifier) body: (class_body)))"
            );
        }
    }
}

#[test]
fn test_load_wasm_errors() {
    let mut store = WasmStore::new(ENGINE.clone()).unwrap();
    let wasm = fs::read(&WASM_DIR.join(format!("tree-sitter-rust.wasm"))).unwrap();

    let bad_wasm = &wasm[1..];
    assert_eq!(
        store.load_language("rust", &bad_wasm).unwrap_err(),
        WasmError {
            kind: WasmErrorKind::Parse,
            message: "failed to parse dylink section of wasm module".into(),
        }
    );

    assert_eq!(
        store.load_language("not_rust", &wasm).unwrap_err(),
        WasmError {
            kind: WasmErrorKind::Instantiate,
            message: "module did not contain language function: tree_sitter_not_rust".into(),
        }
    );

    let mut bad_wasm = wasm.clone();
    bad_wasm[300..500].iter_mut().for_each(|b| *b = 0);
    assert_eq!(
        store.load_language("rust", &bad_wasm).unwrap_err().kind,
        WasmErrorKind::Compile,
    );
}
