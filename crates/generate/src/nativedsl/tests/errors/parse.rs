use crate::nativedsl::EscapeErrorKind;

use super::super::*;

error_tests! { Parse {
    error_invalid_escape {
        r#"grammar { language: "test" } rule program { "x\q" }"#,
        ParseErrorKind::InvalidEscape(EscapeErrorKind::Invalid('q'))
    }
    error_non_ascii_escape {
        "grammar { language: \"test\" } rule program { \"x\\é\" }",
        ParseErrorKind::InvalidEscape(EscapeErrorKind::Invalid('é'))
    }
    error_hex_escape_too_short {
        r#"grammar { language: "test" } rule program { "x\x0" }"#,
        ParseErrorKind::InvalidEscape(EscapeErrorKind::InvalidHex)
    }
    error_hex_escape_non_hex {
        r#"grammar { language: "test" } rule program { "x\xZZ" }"#,
        ParseErrorKind::InvalidEscape(EscapeErrorKind::InvalidHex)
    }
    // A multibyte character where a hex digit is expected must not produce a
    // diagnostic span that slices through the character.
    error_hex_escape_multibyte {
        "grammar { language: \"test\" } rule program { \"x\\x)\u{3a3}\" }",
        ParseErrorKind::InvalidEscape(EscapeErrorKind::InvalidHex)
    }
    error_hex_escape_out_of_ascii_range {
        r#"grammar { language: "test" } rule program { "x\x80" }"#,
        ParseErrorKind::InvalidEscape(EscapeErrorKind::InvalidHex)
    }
    error_unicode_escape_too_short {
        r#"grammar { language: "test" } rule program { "x\u123" }"#,
        ParseErrorKind::InvalidEscape(EscapeErrorKind::InvalidUnicode)
    }
    error_unicode_escape_multibyte {
        "grammar { language: \"test\" } rule program { \"x\\u00\u{3a3}\" }",
        ParseErrorKind::InvalidEscape(EscapeErrorKind::InvalidUnicode)
    }
    error_unicode_escape_braced_empty {
        r#"grammar { language: "test" } rule program { "x\u{}" }"#,
        ParseErrorKind::InvalidEscape(EscapeErrorKind::InvalidUnicode)
    }
    error_unicode_escape_braced_unclosed {
        r#"grammar { language: "test" } rule program { "x\u{1234" }"#,
        ParseErrorKind::InvalidEscape(EscapeErrorKind::InvalidUnicode)
    }
    error_unicode_escape_surrogate {
        r#"grammar { language: "test" } rule program { "x\uD800" }"#,
        ParseErrorKind::InvalidEscape(EscapeErrorKind::InvalidUnicode)
    }
    error_unicode_escape_out_of_range {
        r#"grammar { language: "test" } rule program { "x\u{110000}" }"#,
        ParseErrorKind::InvalidEscape(EscapeErrorKind::InvalidUnicode)
    }
    error_unicode_escape_braced_too_long {
        r#"grammar { language: "test" } rule program { "x\u{1234567}" }"#,
        ParseErrorKind::InvalidEscape(EscapeErrorKind::InvalidUnicode)
    }
    error_unicode_escape_braced_surrogate {
        r#"grammar { language: "test" } rule program { "x\u{D800}" }"#,
        ParseErrorKind::InvalidEscape(EscapeErrorKind::InvalidUnicode)
    }
    error_invalid_language_name {
        r#"grammar { language: "te\nst" } rule program { "x" }"#,
        ParseErrorKind::InvalidLanguageName
    }
    error_invalid_reserved_context_name {
        r#"grammar { language: "test" } rule program { reserved("de\fault", "x") }"#,
        ParseErrorKind::InvalidReservedContextName
    }
    error_backslash_in_module_path {
        r#"let helper = import("dir\helper.tsg") grammar { language: "test" } rule program
        { "x" }"#,
        ParseErrorKind::BackslashInModulePath
    }
    error_unknown_grammar_field {
        r#"grammar { language: "test", bogus: "x" } rule program { "x" }"#,
        ParseErrorKind::UnknownGrammarField("bogus".into())
    }
    error_expected_token {
        r#"grammar { language: "test" } rule program { seq("a" "b") }"#,
        ParseErrorKind::ExpectedToken { expected: TokenKind::RParen, got: TokenKind::StringLit }
    }
    error_expected_expression {
        r#"grammar { language: "test" } rule program { seq(,) }"#,
        ParseErrorKind::ExpectedExpression
    }
    error_integer_overflow {
        r#"grammar { language: "test" } rule program { prec(9223372036854775808, "x") }"#,
        ParseErrorKind::IntegerOverflow
    }
    error_expected_item {
        r#"grammar { language: "test" } "stray_string""#,
        ParseErrorKind::ExpectedItem
    }
    error_unknown_type {
        r#"grammar { language: "test" } let x: foo = "y" rule program { "x" }"#,
        ParseErrorKind::UnknownType("foo".into())
    }
    error_spread_t_not_allowed {
        r#"grammar { language: "test" } let x: spread_t = "y" rule program { "x" }"#,
        ParseErrorKind::UnknownType("spread_t".into())
    }
    error_list_of_module_rejected {
        r#"grammar { language: "test" } let x: list_t<library_t> = [] rule program { "x" }"#,
        ParseErrorKind::ListInnerType(Ty::ANY_LIBRARY)
    }
    error_obj_of_module_rejected {
        r#"grammar { language: "test" } let x: obj_t<library_t> = { a: 1 } rule program { "x" }"#,
        ParseErrorKind::ObjectInnerType(Ty::ANY_LIBRARY)
    }
    error_list_triple_nesting_rejected {
        r#"grammar { language: "test" } let x: list_t<list_t<list_t<rule_t>>> = [] rule program { "x" }"#,
        ParseErrorKind::ListInnerType(Ty::LIST_LIST_RULE)
    }
    error_tuple_annotation_arity_too_small {
        r#"grammar { language: "test" } let x: tuple_t<rule_t> = "y" rule program { "x" }"#,
        ParseErrorKind::TupleArity(1)
    }
    error_tuple_annotation_arity_too_large {
        r#"grammar { language: "test" } let x: tuple_t<rule_t, rule_t, rule_t, rule_t, rule_t, rule_t, rule_t, rule_t, rule_t> = "y" rule program { "x" }"#,
        ParseErrorKind::TupleArity(9)
    }
    error_tuple_annotation_element_not_scalar {
        r#"grammar { language: "test" } let x: tuple_t<list_t<rule_t>, rule_t> = "y" rule program { "x" }"#,
        ParseErrorKind::TupleElementType(Ty::LIST_RULE)
    }
    error_missing_return_type {
        r#"grammar { language: "test" } macro f(x: rule_t) = x rule program { "x" }"#,
        ParseErrorKind::ExpectedType
    }
    error_multiple_grammar_blocks {
        r#"grammar { language: "first" }
        grammar { language: "second" }
        rule program { "x" }"#,
        ParseErrorKind::DuplicateGrammarBlock
    }
    error_expected_function_name {
        r#"grammar { language: "test" }
        let x = { a: 1 }
        rule program { x.a("y") }"#,
        ParseErrorKind::ExpectedMacroName
    }
    error_expected_ident {
        r#"grammar { language: "test" } rule { "x" }"#,
        ParseErrorKind::ExpectedIdent
    }
    error_expected_string {
        r#"grammar { language: 123 } rule program { "x" }"#,
        ParseErrorKind::ExpectedString
    }
    error_expected_name {
        r#"grammar { : "test" } rule program { "x" }"#,
        ParseErrorKind::ExpectedName
    }
    error_field_name_quoted {
        r#"grammar { language: "test" } rule program { field("f", "x") }"#,
        ParseErrorKind::QuotedName
    }
    error_cfg_unknown_attribute {
        r#"grammar { language: "test" } #[notcfg(X)] rule program { "x" }"#,
        ParseErrorKind::ExpectedCfgKeyword("notcfg".to_string())
    }
    error_expected_type {
        r#"grammar { language: "test" }
        let x: = "y"
        rule program { "x" }"#,
        ParseErrorKind::ExpectedType
    }
    error_truncated_rule_body {
        r#"grammar { language: "test" } rule program {"#,
        ParseErrorKind::ExpectedExpression
    }
    error_int_arith_trailing_op {
        r#"grammar { language: "test" } rule program { prec(1 +, "x") }"#,
        ParseErrorKind::ExpectedExpression
    }
    error_nesting_too_deep {
        // Constructed inline since it needs dynamic depth
        &{
            let deep = "(-".repeat(300) + "1" + &")".repeat(300);
            format!("grammar {{ language: \"test\" }} rule foo {{ {deep} }}")
        },
        ParseErrorKind::NestingTooDeep
    }
    error_nesting_too_deep_bare_unary {
        // Long unparenthesized unary `-` run; recurses via parse_postfix.
        &{
            let deep = "-".repeat(300);
            format!("grammar {{ language: \"test\" }} rule foo {{ {deep}x }}")
        },
        ParseErrorKind::NestingTooDeep
    }
    error_nesting_too_deep_bare_at {
        // Long `@` run inside a rule-set body (where `@` is allowed); SymRef
        // recurses via parse_postfix and trips the depth guard.
        &{
            let deep = "@".repeat(300);
            format!("grammar {{ language: \"test\" }} rules deep() {{ rule r {{ {deep}x }} }}")
        },
        ParseErrorKind::NestingTooDeep
    }
    error_nesting_too_deep_field_chain {
        // An iterative `.field` chain builds a left-nested FieldAccess tree the
        // entry-only depth guard once missed (parses fine, then overflows later).
        &{
            let deep = ".b".repeat(300);
            format!("grammar {{ language: \"test\" }} rule foo {{ a{deep} }}")
        },
        ParseErrorKind::NestingTooDeep
    }
    error_nesting_too_deep_qualified_chain {
        // Iterative `::member` chain in parse_ident_expr (same loop, `::` arm).
        &{
            let deep = "::b".repeat(300);
            format!("grammar {{ language: \"test\" }} rule foo {{ a{deep} }}")
        },
        ParseErrorKind::NestingTooDeep
    }
    error_nesting_too_deep_binop_chain {
        // Iterative `+`/`-` chain in parse_expr builds a left-nested BinOp tree.
        &{
            let deep = "+0".repeat(300);
            format!("grammar {{ language: \"test\" }} rule foo {{ prec(0{deep}, \"x\") }}")
        },
        ParseErrorKind::NestingTooDeep
    }
    error_computed_rule_at_top_level {
        r#"grammar { language: "test" } rule @r { "x" }"#,
        ParseErrorKind::ComputedRuleTopLevel
    }
    error_computed_ref_in_let_value {
        r#"grammar { language: "test" } let x = @r rule program { "x" }"#,
        ParseErrorKind::ComputedRuleTopLevel
    }
    error_computed_ref_in_rule_body {
        r#"grammar { language: "test" } rule program { @r }"#,
        ParseErrorKind::ComputedRuleTopLevel
    }
    error_nesting_too_deep_computed_rule_name {
        // `rule @<expr> { ... }` enters parse_postfix directly for the name.
        &{
            let deep = "-".repeat(300);
            format!("grammar {{ language: \"test\" }} rules deep() {{ rule @{deep}name {{ \"x\" }} }}")
        },
        ParseErrorKind::NestingTooDeep
    }
    error_too_many_children {
        &{
            let args = vec!["\"x\""; 65_536].join(",");
            format!("grammar {{ language: \"test\" }} rule foo {{ seq({args}) }}")
        },
        ParseErrorKind::TooManyChildren(65_536)
    }
    error_too_many_macro_params {
        &{
            let params = (0..256).map(|i| format!("p{i}: rule_t")).collect::<Vec<_>>().join(",");
            format!("grammar {{ language: \"test\" }} macro f({params}) rule_t {{ \"x\" }} rule program {{ \"y\" }}")
        },
        ParseErrorKind::TooManyBindings
    }
    error_too_many_for_bindings {
        &{
            let bs = (0..256).map(|i| format!("b{i}: rule_t")).collect::<Vec<_>>().join(",");
            format!("grammar {{ language: \"test\" }} rule program {{ for ({bs}) in [program] {{ \"x\" }} }}")
        },
        ParseErrorKind::TooManyBindings
    }
    error_grammar_config_unknown_field {
        r#"let base = inherit("inherit_base/grammar.tsg")
        grammar { language: "derived", inherits: base, extras: grammar_config(base, bogus) }"#,
        ParseErrorKind::UnknownGrammarField("bogus".into())
    }
    error_grammar_config_unreadable_field {
        r#"let base = inherit("inherit_base/grammar.tsg")
        grammar { language: "derived", inherits: base, extras: grammar_config(base, flags) }"#,
        ParseErrorKind::GrammarFieldNotReadable("flags".into())
    }
}}

#[test]
fn error_duplicate_grammar_field_has_note() {
    let e = assert_err!(
        dsl_err(
            r#"grammar { language: "test", word: foo, word: bar } rule foo { "x" } rule bar { "y" }"#,
        ),
        Parse
    );
    assert_eq!(e.kind, ParseErrorKind::DuplicateGrammarField("word".into()));
    assert!(!e.notes.is_empty());
}

#[test]
fn error_builtin_arg_count_messages() {
    macro_rules! g {
        ($expr:expr) => {
            concat!(r#"grammar { language: "test" } rule foo { "#, $expr, " }")
        };
    }
    #[rustfmt::skip]
    let cases: &[(&str, TokenKind, u8, usize)] = &[
        (g!("blank(\"a\")"), TokenKind::KwBlank, 0, 1),
        (g!("blank(\"a\",)"), TokenKind::KwBlank, 0, 1),
        (g!("blank(\"a\", \"b\")"), TokenKind::KwBlank, 0, 2),
        (g!("eof(\"a\")"), TokenKind::KwEof, 0, 1),
        (g!("repeat()"), TokenKind::KwRepeat, 1, 0),
        (g!("repeat1()"), TokenKind::KwRepeat1, 1, 0),
        (g!("optional()"), TokenKind::KwOptional, 1, 0),
        (g!("token()"), TokenKind::KwToken, 1, 0),
        (g!("token_immediate()"), TokenKind::KwTokenImmediate, 1, 0),
        (g!("inherit()"), TokenKind::KwInherit, 1, 0),
        (g!(r#"repeat("a", "b")"#), TokenKind::KwRepeat, 1, 2),
        (g!(r#"repeat1("a", "b")"#), TokenKind::KwRepeat1, 1, 2),
        (g!(r#"optional("a", "b")"#), TokenKind::KwOptional, 1, 2),
        (g!(r#"token("a", "b")"#), TokenKind::KwToken, 1, 2),
        (g!(r#"token_immediate("a", "b")"#), TokenKind::KwTokenImmediate, 1, 2),
        (g!(r#"inherit("a", "b")"#), TokenKind::KwInherit, 1, 2),
        (g!("prec()"), TokenKind::KwPrec, 2, 0),
        (g!("prec(1)"), TokenKind::KwPrec, 2, 1),
        (g!("prec_left()"), TokenKind::KwPrecLeft, 2, 0),
        (g!("prec_left(1)"), TokenKind::KwPrecLeft, 2, 1),
        (g!("prec_right()"), TokenKind::KwPrecRight, 2, 0),
        (g!("prec_right(1)"), TokenKind::KwPrecRight, 2, 1),
        (g!("prec_dynamic()"), TokenKind::KwPrecDynamic, 2, 0),
        (g!("prec_dynamic(1)"), TokenKind::KwPrecDynamic, 2, 1),
        (g!("field()"), TokenKind::KwField, 2, 0),
        (g!("field(name)"), TokenKind::KwField, 2, 1),
        (g!("alias()"), TokenKind::KwAlias, 2, 0),
        (g!(r#"alias("a")"#), TokenKind::KwAlias, 2, 1),
        (g!("append()"), TokenKind::KwAppend, 2, 0),
        (g!(r#"append("a")"#), TokenKind::KwAppend, 2, 1),
        (g!("reserved()"), TokenKind::KwReserved, 2, 0),
        (g!(r#"reserved("ctx")"#), TokenKind::KwReserved, 2, 1),
        (g!(r#"prec(1, "a", "b")"#), TokenKind::KwPrec, 2, 3),
        (g!(r#"prec_left(1, "a", "b")"#), TokenKind::KwPrecLeft, 2, 3),
        (g!(r#"prec_right(1, "a", "b")"#), TokenKind::KwPrecRight, 2, 3),
        (g!(r#"prec_dynamic(1, "a", "b")"#), TokenKind::KwPrecDynamic, 2, 3),
        (g!(r#"field(name, "a", "b")"#), TokenKind::KwField, 2, 3),
        (g!(r#"alias("a", "b", "c")"#), TokenKind::KwAlias, 2, 3),
        (g!(r#"append([1], [2], [3])"#), TokenKind::KwAppend, 2, 3),
        (g!(r#"reserved("ctx", "a", "b")"#), TokenKind::KwReserved, 2, 3),
        (g!("regexp()"), TokenKind::KwRegexp, 1, 0),
        (g!(r#"regexp("a", "b", "c")"#), TokenKind::KwRegexp, 2, 3),
        (g!("grammar_config()"), TokenKind::KwGrammarConfig, 2, 0),
        (g!("grammar_config(base)"), TokenKind::KwGrammarConfig, 2, 1),
    ];
    for &(src, name, expected, got) in cases {
        let e = assert_err!(dsl_err(src), Parse);
        assert_eq!(
            e.kind,
            ParseErrorKind::WrongArgumentCount {
                name,
                expected,
                got
            },
            "wrong error for: {src}"
        );
    }
}

#[test]
fn error_builtin_arg_count_display() {
    for (src, expected_msg) in [
        (
            r#"grammar { language: "test" } rule foo { prec(1) }"#,
            "'prec' takes 2 arguments, got 1",
        ),
        (
            r#"grammar { language: "test" } rule foo { repeat() }"#,
            "'repeat' takes 1 argument, got 0",
        ),
        (
            r#"grammar { language: "test" } rule foo { blank("x") }"#,
            "'blank' takes no arguments, got 1",
        ),
    ] {
        let e = assert_err!(dsl_err(src), Parse);
        assert_eq!(e.to_string(), expected_msg, "wrong message for: {src}");
    }
}

inherit_error_tests! { Parse {
    error_inherited_parse_error {
        "grammar { language: \"base\" }\nrule program { seq(\"a\" \"b\") }\n",
        ParseErrorKind::ExpectedToken { expected: TokenKind::RParen, got: TokenKind::StringLit }
    }
}}
