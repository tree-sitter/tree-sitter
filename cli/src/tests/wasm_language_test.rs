use crate::tests::helpers::{allocations, fixtures::WASM_DIR};
use lazy_static::lazy_static;
use std::fs;
use tree_sitter::{
    wasmtime::Engine, Parser, Query, QueryCursor, WasmError, WasmErrorKind, WasmStore,
};

lazy_static! {
    static ref ENGINE: Engine = Engine::default();
}

#[test]
fn test_wasm_stdlib_symbols() {
    let symbols = tree_sitter::wasm_stdlib_symbols().collect::<Vec<_>>();
    assert_eq!(
        symbols,
        {
            let mut symbols = symbols.clone();
            symbols.sort();
            symbols
        },
        "symbols aren't sorted"
    );

    assert!(symbols.contains(&"malloc"));
    assert!(symbols.contains(&"free"));
    assert!(symbols.contains(&"memset"));
    assert!(symbols.contains(&"memcpy"));
}

#[test]
fn test_load_wasm_language() {
    allocations::record(|| {
        let mut store = WasmStore::new(ENGINE.clone()).unwrap();
        let mut parser = Parser::new();

        let wasm_cpp = fs::read(&WASM_DIR.join(format!("tree-sitter-cpp.wasm"))).unwrap();
        let wasm_rs = fs::read(&WASM_DIR.join(format!("tree-sitter-rust.wasm"))).unwrap();
        let wasm_rb = fs::read(&WASM_DIR.join(format!("tree-sitter-ruby.wasm"))).unwrap();
        let wasm_typescript =
            fs::read(&WASM_DIR.join(format!("tree-sitter-typescript.wasm"))).unwrap();

        let language_rust = store.load_language("rust", &wasm_rs).unwrap();
        let language_cpp = store.load_language("cpp", &wasm_cpp).unwrap();
        let language_ruby = store.load_language("ruby", &wasm_rb).unwrap();
        let language_typescript = store.load_language("typescript", &wasm_typescript).unwrap();
        parser.set_wasm_store(store).unwrap();

        let mut parser2 = Parser::new();
        parser2
            .set_wasm_store(WasmStore::new(ENGINE.clone()).unwrap())
            .unwrap();
        let mut query_cursor = QueryCursor::new();

        for mut parser in [parser, parser2] {
            for _ in 0..2 {
                let query_rust = Query::new(&language_rust, "(const_item) @foo").unwrap();
                let query_typescript =
                    Query::new(&language_typescript, "(class_declaration) @foo").unwrap();

                parser.set_language(&language_cpp).unwrap();
                let tree = parser.parse("A<B> c = d();", None).unwrap();
                assert_eq!(
                    tree.root_node().to_sexp(),
                    "(translation_unit (declaration type: (template_type name: (type_identifier) arguments: (template_argument_list (type_descriptor type: (type_identifier)))) declarator: (init_declarator declarator: (identifier) value: (call_expression function: (identifier) arguments: (argument_list)))))"
                );

                parser.set_language(&language_rust).unwrap();
                let source = "const A: B = c();";
                let tree = parser.parse(source, None).unwrap();
                assert_eq!(
                    tree.root_node().to_sexp(),
                    "(source_file (const_item name: (identifier) type: (type_identifier) value: (call_expression function: (identifier) arguments: (arguments))))"
                );
                assert_eq!(
                    query_cursor
                        .matches(&query_rust, tree.root_node(), source.as_bytes())
                        .count(),
                    1
                );

                parser.set_language(&language_ruby).unwrap();
                let tree = parser.parse("class A; end", None).unwrap();
                assert_eq!(
                    tree.root_node().to_sexp(),
                    "(program (class name: (constant)))"
                );

                parser.set_language(&language_typescript).unwrap();
                let tree = parser.parse("class A {}", None).unwrap();
                assert_eq!(
                    tree.root_node().to_sexp(),
                    "(program (class_declaration name: (type_identifier) body: (class_body)))"
                );
                assert_eq!(
                    query_cursor
                        .matches(&query_typescript, tree.root_node(), source.as_bytes())
                        .count(),
                    1
                );
            }
        }
    });
}

#[test]
fn test_load_and_reload_wasm_language() {
    allocations::record(|| {
        let mut store = WasmStore::new(ENGINE.clone()).unwrap();

        let wasm_rust = fs::read(&WASM_DIR.join(format!("tree-sitter-rust.wasm"))).unwrap();
        let wasm_typescript =
            fs::read(&WASM_DIR.join(format!("tree-sitter-typescript.wasm"))).unwrap();

        let language_rust = store.load_language("rust", &wasm_rust).unwrap();
        let language_typescript = store.load_language("typescript", &wasm_typescript).unwrap();
        assert_eq!(store.language_count(), 2);

        // When a language is dropped, stores can release their instances of that language.
        drop(language_rust);
        assert_eq!(store.language_count(), 1);

        let language_rust = store.load_language("rust", &wasm_rust).unwrap();
        assert_eq!(store.language_count(), 2);

        drop(language_rust);
        drop(language_typescript);
        assert_eq!(store.language_count(), 0);
    });
}

#[test]
fn test_load_wasm_errors() {
    allocations::record(|| {
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
    });
}
