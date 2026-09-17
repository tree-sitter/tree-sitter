use super::super::*;

error_tests! { Lex {
    error_unterminated_string {
        r#"grammar { language: "test }rule program { "x" }"#,
        LexErrorKind::UnterminatedString
    }
    error_newline_in_string {
        "grammar { language: \"test\n",
        LexErrorKind::NewlineInString
    }
    error_escaped_newline_in_string {
        "grammar { language: \"test\\\n\" }",
        LexErrorKind::NewlineInString
    }
    error_unterminated_escape {
        r#"grammar { language: "test\"#,
        LexErrorKind::UnterminatedEscape
    }
    error_unterminated_raw_string {
        r#"grammar { language: r#"test } rule program { "x" }"#,
        LexErrorKind::UnterminatedRawString
    }
    error_expected_raw_string_quote {
        r#"grammar { language: r## } rule program { "x" }"#,
        LexErrorKind::ExpectedRawStringQuote
    }
    error_too_many_raw_string_hashes {
        &format!("let x = r{}\"test\"", "#".repeat(256)),
        LexErrorKind::TooManyHashes(256)
    }
    error_unexpected_char {
        r#"grammar { language: "test" } rule program { $ }"#,
        LexErrorKind::UnexpectedChar('$')
    }
    error_non_ascii_latin {
        r#"grammar { language: "test" } rule café { "x" }"#,
        LexErrorKind::UnexpectedChar('é')
    }
    error_non_ascii_emoji {
        r#"grammar { language: "test" } rule 🎉 { "x" }"#,
        LexErrorKind::UnexpectedChar('🎉')
    }
    error_non_ascii_cjk {
        r#"grammar { language: "test" } rule 名前 { "x" }"#,
        LexErrorKind::UnexpectedChar('名')
    }
    error_non_ascii_after_ident {
        r#"grammar { language: "test" } rule foo™ { "x" }"#,
        LexErrorKind::UnexpectedChar('™')
    }
}}

inherit_error_tests! { Lex {
    error_inherited_lex_error {
        r#"grammar { language: "base"#,
        LexErrorKind::UnterminatedString
    }
}}
