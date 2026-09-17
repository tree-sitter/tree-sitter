use super::super::*;

error_tests! { match Lower {
    // obj_t<X> carries the value type, not the key set, so a missing field on a
    // computed object can't be caught at typecheck - lower reports it with the keys.
    error_field_not_found_on_computed_object {
        r#"grammar { language: "test" }
        macro mk() obj_t<rule_t> { { a: program } }
        rule program { seq(mk().b) }"#,
        LowerErrorKind::FieldNotFound { field, available } if field == "b" && *available == ["a"]
    }
    // A str_t widened to rule_t (via let/append/mixed list) into a name-only config
    // field can't be caught at typecheck, so lower reports it instead of panicking.
    error_inline_str_list_via_let {
        r#"let names = ["a"]
        grammar { language: "test", inline: names }
        rule program { "x" }"#,
        LowerErrorKind::ExpectedRuleName
    }
    error_inline_str_list_via_append {
        r#"grammar { language: "test", inline: append(["x"], ["y"]) }
        rule program { "z" }"#,
        LowerErrorKind::ExpectedRuleName
    }
    error_conflicts_str_list_via_let {
        r#"let groups: list_t<list_t<rule_t>> = [["a", "b"], ["c"]]
        grammar { language: "test", conflicts: groups }
        rule program { "x" }"#,
        LowerErrorKind::ExpectedRuleName
    }
    error_inline_mixed_name_and_str_via_let {
        r#"let m = [program, "b"]
        grammar { language: "test", inline: m }
        rule program { "x" }"#,
        LowerErrorKind::ExpectedRuleName
    }
    error_missing_language_field {
        r#"grammar { extras: [] } rule program { "x" }"#,
        LowerErrorKind::MissingLanguageField
    }
    // A grammar that emits grammar.json must have at least one rule (matches
    // grammar.js). Config-only *bases* are allowed (checked only on the root).
    error_grammar_has_no_rules {
        r#"grammar { language: "test" }"#,
        LowerErrorKind::GrammarHasNoRules
    }
    // An external resolves rule-like but lives in external_roots, not
    // variables, so it can't be variables[0] (the start symbol).
    error_external_as_start_rule {
        r#"grammar { language: "test", externals: [tok], start: tok }
        rule program { "x" }"#,
        LowerErrorKind::ExternalCannotBeStart(name) if name == "tok"
    }
    error_multiple_inherits {
        r#"let a = inherit("inherit_base/grammar.tsg")
        let b = inherit("inherit_base/grammar.tsg")
        grammar { language: "derived", inherits: a }
        rule extra { "x" }"#,
        LowerErrorKind::MultipleInherits
    }
    error_multiple_inherits_let_and_config {
        r#"let base = inherit("inherit_base/grammar.tsg")
        grammar { language: "derived", inherits: inherit("inherit_base/grammar.tsg") }
        rule extra { "x" }"#,
        LowerErrorKind::MultipleInherits
    }
    error_override_without_target {
        r#"grammar { language: "test" } override rule foo { "bar" }"#,
        LowerErrorKind::OverrideRuleNotFound(names) if *names == ["foo"]
    }
    error_override_rule_not_found {
        r#"let base = inherit("inherit_base/grammar.tsg")
        grammar { language: "derived", inherits: base }
        override rule nonexistent { "oops" }"#,
        LowerErrorKind::OverrideRuleNotFound(names) if *names == ["nonexistent"]
    }
    error_missing_grammar_block {
        r#"rule program { "x" }"#,
        LowerErrorKind::MissingGrammarBlock
    }
    error_inherit_without_config {
        r#"let base = inherit("inherit_base/grammar.tsg")
        grammar { language: "test" }
        rule program { "x" }"#,
        LowerErrorKind::InheritWithoutConfig
    }
    error_config_field_unset {
        r#"let base = inherit("inherit_base_no_word/grammar.tsg")
        grammar { language: "test", inherits: base, word: grammar_config(base, word) }
        override rule program { "x" }"#,
        LowerErrorKind::ConfigFieldUnset
    }
    error_word_not_named_symbol {
        r#"let my_word = seq("x", "y")
        grammar { language: "test", word: my_word }
        rule program { "z" }"#,
        LowerErrorKind::ExpectedRuleName
    }
    error_int_literal_too_large_positive {
        r#"grammar { language: "test" }
        rule program { prec(3000000000, "x") }"#,
        LowerErrorKind::IntegerOverflow(3_000_000_000)
    }
    error_int_literal_too_large_negative {
        r#"grammar { language: "test" }
        rule program { prec(-3000000000, "x") }"#,
        LowerErrorKind::IntegerOverflow(-3_000_000_000)
    }
    error_double_negation_of_i32_min_overflows {
        r#"grammar { language: "test" }
        let x: int_t = -2147483648
        rule program { prec(-x, "y") }"#,
        LowerErrorKind::IntegerOverflow(2_147_483_648)
    }
    error_int_arith_add_overflow {
        r#"grammar { language: "test" }
        let x: int_t = 2000000000
        rule program { prec(x + x, "y") }"#,
        LowerErrorKind::IntegerOverflow(4_000_000_000)
    }
    error_int_arith_sub_underflow {
        r#"grammar { language: "test" }
        let x: int_t = -2000000000
        rule program { prec(x - 2000000000, "y") }"#,
        LowerErrorKind::IntegerOverflow(-4_000_000_000)
    }
    // Multiple unmatched overrides should produce a list in deterministic
    // (sorted) order so users see a stable error and tests don't flake.
    error_multiple_override_rules_not_found {
        r#"let base = inherit("inherit_base/grammar.tsg")
        grammar { language: "derived", inherits: base }
        override rule zzz { "z" }
        override rule aaa { "a" }
        override rule mmm { "m" }"#,
        LowerErrorKind::OverrideRuleNotFound(names) if *names == ["aaa", "mmm", "zzz"]
    }
    // A variable holding a non-name rule (e.g. seq) passed as alias target
    // should produce a proper error, not panic.
    error_alias_non_name_rule_via_var {
        r#"grammar { language: "test" }
        macro make_alias(target: rule_t) rule_t { alias("x", target) }
        rule a { "a" }
        rule b { "b" }
        rule program { make_alias(seq(a, b)) }"#,
        LowerErrorKind::ExpectedRuleName
    }
    // A variable holding a non-name rule in config name-lists (inline,
    // supertypes, conflicts) should produce a proper error, not panic.
    error_inline_non_name_rule_via_var {
        r#"let x = seq(a, b)
        grammar { language: "test", inline: [x] }
        rule a { "a" }
        rule b { "b" }
        rule program { a }"#,
        LowerErrorKind::ExpectedRuleName
    }
}}

error_tests! { Resolve {
    error_inherit_rule_not_found {
        r#"let base = inherit("inherit_base/grammar.tsg")
        grammar { language: "derived", inherits: base }
        rule extra { base::nonexistent_rule }"#,
        ResolveErrorKind::ImportMemberNotFound("nonexistent_rule".into())
    }
}}

#[test]
fn error_recursive_macro_combinator_product() {
    // A self-recursive macro nesting combinators deeply: the macro-recursion x
    // combinator-depth product once overflowed the stack before MAX_CALL_DEPTH.
    // The combinator nesting is now evaluated iteratively (heap work stack), so
    // it can't overflow; the genuinely unbounded axis - the macro calling itself
    // forever - is caught cleanly by the MAX_CALL_DEPTH guard instead.
    let body = format!("{}seq(x, m(x)){}", "seq(".repeat(90), ")".repeat(90));
    let src = format!(
        "grammar {{ language: \"test\" }}\nmacro m(x: rule_t) rule_t {{ {body} }}\nrule prog {{ m(\"a\") }}"
    );
    let e = assert_err!(dsl_err(&src), Lower);
    assert!(
        matches!(e.kind, LowerErrorKind::CallDepthExceeded(_)),
        "expected CallDepthExceeded, got {:?}",
        e.kind
    );
}

#[test]
fn error_inherit_bad_path() {
    let e = assert_err!(
        dsl_err(
            r#"let base = inherit("nonexistent/grammar.tsg")
        grammar { language: "derived", inherits: base }"#
        ),
        Lower
    );
    assert!(matches!(e.kind, LowerErrorKind::ModuleResolveFailed(_)));
}

#[test]
fn error_module_read_failure_renders_without_panic() {
    // The import path is a directory, so read_to_string fails before any
    // ModuleError wrapping: this is a DslError::Lower(ModuleReadFailed) directly,
    // carrying the offending path. Assert the variant + path, then check that
    // rendering does not slice OOB on the (empty) module source.
    let dir = tempfile::tempdir().unwrap();
    let subdir = dir.path().join("not_a_file");
    std::fs::create_dir(&subdir).unwrap();
    let parent_path = dir.path().join("parent.tsg");
    let parent_src = format!(
        "let h = import(\"{}\")\ngrammar {{ language: \"test\" }}\nrule program {{ \"x\" }}",
        dsl_path(&subdir)
    );
    std::fs::write(&parent_path, &parent_src).unwrap();
    let error = expect_err(parse_native_dsl(&parent_src, &parent_path));
    assert!(
        matches!(
            &error.error,
            DslError::Lower(e)
                if matches!(&e.kind, LowerErrorKind::ModuleReadFailed(io) if io.path.is_some())
        ),
        "expected ModuleReadFailed carrying a path, got {error:?}"
    );
    let _rendered = format!("{error}");
}

#[test]
fn helper_lower_error_carries_helper_source() {
    // A lower error born inside an imported helper (an integer overflow in the
    // helper's macro body) tags the diagnostic with the helper's source + path,
    // so it renders against helper.tsg, not the root that imported it.
    let err = expect_err(parse_with_module_documents(
        &[(
            "helper.tsg",
            "macro big() rule_t { prec(1000000000 + 2000000000, \"x\") }\n",
        )],
        r#"
        let h = import("helper.tsg")
        grammar { language: "test" }
        rule program { h::big() }
    "#,
    ));
    let DslError::Lower(e) = &err.error else {
        panic!("expected lower error, got {:?}", err.error)
    };
    assert_eq!(e.kind, LowerErrorKind::IntegerOverflow(3_000_000_000));
    let document = err.document(e.document);
    let src = document.text();
    let path = document.path();
    assert!(
        path.ends_with("helper.tsg"),
        "expected helper.tsg, got {path:?}"
    );
    assert!(
        src.contains("macro big"),
        "expected helper source, got {src:?}"
    );
}

inherit_error_tests! { Resolve {
    error_inherit_child_error {
        "grammar { language: \"base\" }\nrule program { bogus_ref }\n",
        ResolveErrorKind::UnknownIdentifier("bogus_ref".into())
    }
}}

inherit_error_tests! { match Lower {
    error_inherited_missing_language {
        "grammar { extras: [] }\nrule program { \"x\" }\n",
        LowerErrorKind::MissingLanguageField
    }
}}

#[test]
fn error_inherit_cycle() {
    let dir = tempfile::tempdir().unwrap();
    let a_path = dir.path().join("a.tsg");
    let b_path = dir.path().join("b.tsg");
    std::fs::write(
        &a_path,
        format!(
            "let base = inherit(\"{}\")\ngrammar {{ language: \"a\", inherits: base }}",
            dsl_path(&b_path)
        ),
    )
    .unwrap();
    std::fs::write(
        &b_path,
        format!(
            "let base = inherit(\"{}\")\ngrammar {{ language: \"b\", inherits: base }}",
            dsl_path(&a_path)
        ),
    )
    .unwrap();
    let source = std::fs::read_to_string(&a_path).unwrap();
    let err = expect_err(parse_native_dsl(&source, &a_path));
    let mut chain = Vec::new();
    let mut current: &DslError = &err.error;
    loop {
        match current {
            DslError::Module(m) => {
                chain.push(
                    err.document(m.child_document())
                        .path()
                        .file_name()
                        .unwrap()
                        .to_str()
                        .unwrap()
                        .to_string(),
                );
                current = &m.inner;
            }
            DslError::Lower(e) => {
                assert_eq!(e.kind, LowerErrorKind::ModuleCycle);
                break;
            }
            other => panic!("unexpected error variant: {other:?}"),
        }
    }
    assert_eq!(chain, ["b.tsg", "a.tsg"]);
}

#[test]
fn error_self_inherit_cycle() {
    // A grammar that inherits itself should be caught as a cycle,
    // not spin until MAX_MODULE_DEPTH.
    let err = expect_err(parse_with_modules(
        &[],
        r#"let base = inherit("grammar.tsg")
        grammar { language: "test", inherits: base }
        rule program { "x" }"#,
    ));
    match &err {
        DslError::Module(m) => {
            assert!(
                matches!(*m.inner, DslError::Lower(ref e) if matches!(e.kind, LowerErrorKind::ModuleCycle))
            );
        }
        other => panic!("expected Module(ModuleCycle), got {other:?}"),
    }
}
