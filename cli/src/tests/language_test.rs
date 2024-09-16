use std::ffi::CStr;

use tree_sitter::{
    ffi::{
        ts_language_symbol_name, ts_language_symbol_type, TSSymbol, TSSymbolTypeAnonymous,
        TSSymbolTypeAuxiliary, TSSymbolTypeRegular, TSSymbolTypeSupertype,
    },
    Parser,
};

use super::helpers::fixtures::get_language;

#[test]
fn test_lookahead_iterator() {
    let mut parser = Parser::new();
    let language = get_language("rust");
    parser.set_language(&language).unwrap();

    let tree = parser.parse("struct Stuff {}", None).unwrap();

    let mut cursor = tree.walk();

    assert!(cursor.goto_first_child()); // struct
    assert!(cursor.goto_first_child()); // struct keyword

    let next_state = cursor.node().next_parse_state();
    assert_ne!(next_state, 0);
    assert_eq!(
        next_state,
        language.next_state(cursor.node().parse_state(), cursor.node().grammar_id())
    );
    assert!((next_state as usize) < language.parse_state_count());
    assert!(cursor.goto_next_sibling()); // type_identifier
    assert_eq!(next_state, cursor.node().parse_state());
    assert_eq!(cursor.node().grammar_name(), "identifier");
    assert_ne!(cursor.node().grammar_id(), cursor.node().kind_id());

    let expected_symbols = ["//", "/*", "identifier", "line_comment", "block_comment"];
    let mut lookahead = language.lookahead_iterator(next_state).unwrap();
    assert_eq!(*lookahead.language(), language);
    assert!(lookahead.iter_names().eq(expected_symbols));

    lookahead.reset_state(next_state);
    assert!(lookahead.iter_names().eq(expected_symbols));

    lookahead.reset(&language, next_state);
    assert!(lookahead
        .map(|s| language.node_kind_for_id(s).unwrap())
        .eq(expected_symbols));
}

#[test]
fn test_lookahead_iterator_modifiable_only_by_mut() {
    let mut parser = Parser::new();
    let language = get_language("rust");
    parser.set_language(&language).unwrap();

    let tree = parser.parse("struct Stuff {}", None).unwrap();

    let mut cursor = tree.walk();

    assert!(cursor.goto_first_child()); // struct
    assert!(cursor.goto_first_child()); // struct keyword

    let next_state = cursor.node().next_parse_state();
    assert_ne!(next_state, 0);

    let mut lookahead = language.lookahead_iterator(next_state).unwrap();
    let _ = lookahead.next();

    let mut names = lookahead.iter_names();
    let _ = names.next();
}

#[test]
fn test_symbol_metadata_checks() {
    let language = get_language("rust");
    let ts_language = language.clone().into_raw();
    for i in 0..language.node_kind_count() {
        let ts_symbol: TSSymbol = i.try_into().unwrap();
        unsafe {
            let name = CStr::from_ptr(ts_language_symbol_name(ts_language, ts_symbol))
                .to_str()
                .unwrap();
            match name {
                "_type"
                | "_expression"
                | "_pattern"
                | "_literal"
                | "_literal_pattern"
                | "_declaration_statement" => {
                    assert_eq!(
                        ts_language_symbol_type(ts_language, ts_symbol),
                        TSSymbolTypeSupertype
                    );
                    assert_ne!(
                        ts_language_symbol_type(ts_language, ts_symbol),
                        TSSymbolTypeAuxiliary
                    );
                }
                "_raw_string_literal_start"
                | "_raw_string_literal_end"
                | "_line_doc_comment"
                | "_error_sentinel" => {
                    assert_eq!(
                        ts_language_symbol_type(ts_language, ts_symbol),
                        TSSymbolTypeAuxiliary
                    );
                    assert_ne!(
                        ts_language_symbol_type(ts_language, ts_symbol),
                        TSSymbolTypeSupertype
                    );
                }
                "enum_item" | "struct_item" | "type_item" => {
                    assert_ne!(
                        ts_language_symbol_type(ts_language, ts_symbol),
                        TSSymbolTypeSupertype
                    );
                    assert_eq!(
                        ts_language_symbol_type(ts_language, ts_symbol),
                        TSSymbolTypeRegular
                    );
                }
                "=>" | "[" | "]" | "(" | ")" | "{" | "}" => {
                    assert_ne!(
                        ts_language_symbol_type(ts_language, ts_symbol),
                        TSSymbolTypeSupertype
                    );
                    assert_eq!(
                        ts_language_symbol_type(ts_language, ts_symbol),
                        TSSymbolTypeAnonymous
                    );
                }
                _ => {}
            }
        }
    }
}
