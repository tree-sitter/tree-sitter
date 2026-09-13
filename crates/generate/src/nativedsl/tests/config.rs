use super::*;

#[test]
fn grammar_config_all_fields() {
    let g = dsl(r#"
        grammar {
            language: "test",
            extras: [regexp(r"\s"), comment],
            externals: [heredoc],
            supertypes: [_expression],
            inline: [_statement],
            conflicts: [[primary, arrow]],
            word: identifier,
        }
        rule program { _expression }
        rule _expression { "x" }
        rule _statement { "s" }
        rule primary { "p" }
        rule arrow { "->" }
        rule comment { regexp(r"\/\/.*") }
        rule identifier { regexp("[a-z]+") }
    "#);
    assert_eq!(g.extra_roots.len(), 2);
    assert_eq!(g.external_roots.len(), 1);
    assert_eq!(
        g.supertype_names
            .iter()
            .map(|&n| g.pool.resolve(n))
            .collect::<Vec<_>>(),
        vec!["_expression"]
    );
    assert_eq!(
        g.inline_names
            .iter()
            .map(|&n| g.pool.resolve(n))
            .collect::<Vec<_>>(),
        vec!["_statement"]
    );
    assert_eq!(conflict_names(&g), vec![vec!["primary", "arrow"]]);
    assert_eq!(g.word_name.map(|w| g.pool.resolve(w)), Some("identifier"));
}

#[test]
fn config_precedences() {
    let mut g = dsl(r#"
        grammar {
            language: "test",
            precedences: [["add", multiply]],
        }
        rule program { "x" }
        rule multiply { "y" }
    "#);
    assert_eq!(
        g.precedence_orderings,
        vec![vec![
            crate::grammars::PrecedenceEntry::Name(g.pool.intern("add")),
            crate::grammars::PrecedenceEntry::Symbol(g.pool.intern("multiply")),
        ]]
    );
}

#[test]
fn conflicts_accepts_appended_list() {
    let g = dsl(r#"
        grammar {
            language: "test",
            conflicts: append([[a, b]], [[a, c]]),
        }
        rule program { "x" }
        rule a { "a" }
        rule b { "b" }
        rule c { "c" }
    "#);
    assert_eq!(conflict_names(&g), vec![vec!["a", "b"], vec!["a", "c"]]);
}

#[test]
fn precedences_mixed_names_and_idents() {
    let g = dsl(r#"
        grammar {
            language: "test",
            precedences: [["member", call, "binary"]],
        }
        rule program { "x" }
        rule call { "c" }
    "#);
    assert_eq!(g.precedence_orderings.len(), 1);
    assert_eq!(g.precedence_orderings[0].len(), 3);
}

#[test]
fn empty_list_compatible_with_any_list_type() {
    // Empty list in extras (list_t<rule_t> context)
    dsl(r#"
        grammar { language: "test", extras: [] }
        rule foo { "x" }
    "#);
    // Empty list in a let with explicit list_t<str_t> annotation
    dsl(r#"
        grammar { language: "test" }
        let x: list_t<str_t> = []
        rule foo { "x" }
    "#);
}

#[test]
fn empty_list_append() {
    let g = dsl(r#"
        grammar { language: "test", extras: append([], [regexp("\\s")]) }
        rule foo { "x" }
    "#);
    assert_eq!(g.extra_roots.len(), 1);
}

#[test]
fn raw_string_literal() {
    #[expect(clippy::needless_raw_string_hashes, reason = "false positive")]
    let mut g = dsl(r##"
        grammar { language: "test" }
        rule program { regexp(r#""[^"]*""#) }
    "##);
    let actual = g.variables[0].root;
    let expected = {
        let p = &mut g.pool;
        r_pattern!(p, r#""[^"]*""#)
    };
    assert_rule_eq(&g.pool, actual, expected);
}

#[test]
fn string_with_escapes() {
    let mut g = dsl(r#"
        grammar { language: "test" }
        rule program { "\n\t\\" }
    "#);
    let actual = g.variables[0].root;
    let expected = {
        let p = &mut g.pool;
        r_str!(p, "\n\t\\")
    };
    assert_rule_eq(&g.pool, actual, expected);
}

#[test]
fn json_roundtrip() {
    let input = r##"
        grammar {
            language: "test",
            extras: [regexp(r"\s")],
            externals: [heredoc],
            inline: [_inline],
            supertypes: [_expression],
            word: identifier,
            conflicts: [[primary, call]],
            precedences: [["add", multiply]],
            reserved: { default: ["if", "else"] },
        }
        rule program { seq(repeat(choice(_expression, blank())), eof()) }
        rule _expression { choice(primary, call, prec_left("add", seq(_expression, "+", _expression))) }
        rule primary { identifier }
        rule call { seq(identifier, "(", ")") }
        rule multiply { seq(_expression, "*", _expression) }
        rule _inline { "x" }
        rule identifier { regexp(r#"[a-z]+"#) }
    "##;
    let path = test_fixtures_dir().join("grammar.tsg");
    let grammar = parse_native_dsl(input, &path)
        .unwrap()
        .normalize(&mut Vec::new());
    let json_str =
        serde_json::to_string_pretty(&crate::nativedsl::serialize::grammar_to_json(&grammar))
            .expect("grammar JSON serialization should not fail");
    let reparsed = crate::parse_grammar::parse_grammar(&json_str, &mut Vec::new()).unwrap();
    assert_grammar_eq(&grammar, &reparsed);
}

#[test]
fn config_word_with_conflicts() {
    let g = dsl(r#"
        grammar {
            language: "test",
            word: identifier,
            conflicts: [[identifier, keyword]],
        }
        rule program { choice(identifier, keyword) }
        rule identifier { regexp(r"[a-z]+") }
        rule keyword { "if" }
    "#);
    assert_eq!(g.word_name.map(|w| g.pool.resolve(w)), Some("identifier"));
    assert_eq!(conflict_names(&g), vec![vec!["identifier", "keyword"]]);
}

#[test]
fn config_extras_with_inline() {
    let g = dsl(r#"
        grammar {
            language: "test",
            extras: [_ws],
            inline: [_ws],
        }
        rule program { "x" }
        rule _ws { regexp(r"\s") }
    "#);
    assert_eq!(g.extra_roots.len(), 1);
    assert_eq!(
        g.inline_names
            .iter()
            .map(|&n| g.pool.resolve(n))
            .collect::<Vec<_>>(),
        vec!["_ws"]
    );
}

#[test]
fn config_all_fields_at_once() {
    let g = dsl(r#"
        grammar {
            language: "test",
            extras: [regexp(r"\s")],
            externals: [heredoc],
            inline: [_inline],
            supertypes: [_expr],
            word: ident,
            conflicts: [[ident, kw]],
            precedences: [["+" , ident]],
        }
        rule program { choice(_expr, heredoc) }
        rule _expr { choice(ident, kw) }
        rule ident { regexp(r"[a-z]+") }
        rule kw { "if" }
        rule _inline { "x" }
        rule heredoc { "<<" }
    "#);
    assert_eq!(g.extra_roots.len(), 1);
    assert_eq!(g.external_roots.len(), 1);
    assert_eq!(
        g.inline_names
            .iter()
            .map(|&n| g.pool.resolve(n))
            .collect::<Vec<_>>(),
        vec!["_inline"]
    );
    assert_eq!(
        g.supertype_names
            .iter()
            .map(|&n| g.pool.resolve(n))
            .collect::<Vec<_>>(),
        vec!["_expr"]
    );
    assert_eq!(g.word_name.map(|w| g.pool.resolve(w)), Some("ident"));
    assert_eq!(g.conflict_names.len(), 1);
    assert_eq!(g.precedence_orderings.len(), 1);
}

#[test]
fn externals_used_in_extras() {
    let g = dsl(r#"
        grammar {
            language: "test",
            externals: [_newline],
            extras: [regexp(r"\s"), _newline],
        }
        rule program { "x" }
    "#);
    assert_eq!(g.external_roots.len(), 1);
    assert_eq!(g.extra_roots.len(), 2);
}

#[test]
fn externals_used_in_conflicts() {
    let g = dsl(r#"
        grammar {
            language: "test",
            externals: [heredoc],
            conflicts: [[program, heredoc]],
        }
        rule program { "x" }
    "#);
    assert_eq!(g.conflict_names.len(), 1);
}

#[test]
fn externals_via_let_bindings() {
    // Direct and chained let indirection both resolve external names.
    for src in [
        r#"let ext: list_t<rule_t> = [heredoc]
        grammar { language: "test", externals: ext }
        rule program { "x" }"#,
        r#"let a: list_t<rule_t> = [heredoc]
        let b: list_t<rule_t> = a
        grammar { language: "test", externals: b }
        rule program { "x" }"#,
    ] {
        let mut g = dsl(src);
        let actual = g.external_roots.clone();
        let expected = {
            let p = &mut g.pool;
            vec![r_sym!(p, "heredoc")]
        };
        assert_rules_eq(&g.pool, &actual, &expected);
    }
}

#[test]
fn externals_used_in_extras_via_let() {
    let g = dsl(r#"
        let ext: list_t<rule_t> = [_newline]
        grammar {
            language: "test",
            externals: ext,
            extras: [regexp(r"\s"), _newline],
        }
        rule program { "x" }
    "#);
    assert_eq!(g.external_roots.len(), 1);
    assert_eq!(g.extra_roots.len(), 2);
}

#[test]
fn external_and_rule_same_name_is_valid() {
    // A rule can also be an external token - the rule is registered first,
    // then the externals walk sees it's already declared and skips re-registration.
    let mut g = dsl(r#"
        grammar { language: "test", externals: [foo] }
        rule program { "x" }
        rule foo { "y" }
    "#);
    let actual = g.external_roots.clone();
    let expected = {
        let p = &mut g.pool;
        vec![r_sym!(p, "foo")]
    };
    assert_rules_eq(&g.pool, &actual, &expected);
    assert_eq!(g.variables.len(), 2);
}

#[test]
fn error_externals_via_function_call() {
    let e = assert_err!(
        dsl_err(
            r#"
            macro mk_ext() list_t<rule_t> { [heredoc] }
            grammar { language: "test", externals: mk_ext() }
            rule program { "x" }
        "#
        ),
        Resolve
    );
    assert_eq!(e.kind, ResolveErrorKind::InvalidExternalsExpression);
}

#[test]
fn expect_decl_in_grammar_file() {
    let mut g = dsl(r#"
        expect _foo
        grammar { language: "test", externals: [_foo] }
        rule program { _foo }
    "#);
    assert_eq!(g.external_roots.len(), 1);
    let actual = find_rule(&g, "program");
    let expected = {
        let p = &mut g.pool;
        r_sym!(p, "_foo")
    };
    assert_rule_eq(&g.pool, actual, expected);
}

#[test]
fn expect_fulfilled_by_same_file_rule() {
    // A forward-decl is fulfilled by a later same-file definition, not collided
    // with: the `rule` claims the name the `expect` declared.
    let mut g = dsl(r#"
        expect helper
        grammar { language: "test" }
        rule program { helper }
        rule helper { "x" }
    "#);
    let actual = find_rule(&g, "program");
    let expected = {
        let p = &mut g.pool;
        r_sym!(p, "helper")
    };
    assert_rule_eq(&g.pool, actual, expected);
    let actual = find_rule(&g, "helper");
    let expected = {
        let p = &mut g.pool;
        r_str!(p, "x")
    };
    assert_rule_eq(&g.pool, actual, expected);
}

#[test]
fn expect_referenced_but_not_defined_is_rejected() {
    // An `expect` whose name is never defined (no rule, no externals token) leaves
    // a dangling NamedSymbol when referenced, so it must be rejected.
    let err = dsl_err(
        r#"
        expect _foo
        grammar { language: "test" }
        rule program { _foo }
    "#,
    );
    let e = assert_err!(err, Lower);
    assert_eq!(
        e.kind,
        LowerErrorKind::UndefinedSymbols(vec!["_foo".into()])
    );
}

#[test]
fn expect_decl_repeated_is_idempotent() {
    // Forward-decls are idempotent (like C): repeating `expect` for a name is
    // redundant, not a duplicate - only definitions collide.
    let mut g = dsl(r#"
        expect _foo
        expect _foo
        grammar { language: "test", externals: [_foo] }
        rule program { _foo }
    "#);
    assert_eq!(g.external_roots.len(), 1);
    let actual = find_rule(&g, "program");
    let expected = {
        let p = &mut g.pool;
        r_sym!(p, "_foo")
    };
    assert_rule_eq(&g.pool, actual, expected);
}

#[test]
fn expect_decl_redundant_with_grammar_block() {
    // `expect _foo` and `externals: [_foo]` declare the same name. The grammar
    // block's pre-registration skips already-declared names.
    let g = dsl(r#"
        expect _foo
        grammar { language: "test", externals: [_foo, _bar] }
        rule program { seq(_foo, _bar) }
    "#);
    assert_eq!(g.external_roots.len(), 2);
}

#[test]
fn error_start_unknown_rule() {
    // Resolver catches `start: <undeclared>` as UnknownIdentifier
    let e = assert_err!(
        dsl_err(
            r#"
            grammar { language: "test", start: nonexistent }
            rule program { "x" }
        "#
        ),
        Resolve
    );
    assert_eq!(
        e.kind,
        ResolveErrorKind::UnknownIdentifier("nonexistent".into())
    );
}

externals_tests! {
    externals_inline_list {
        r#"grammar { language: "test", externals: [heredoc, _eof] } rule program { "x" }"#,
        |p| vec![
            r_sym!(p, "heredoc"),
            r_sym!(p, "_eof"),
        ]
    }
    externals_with_string_literals {
        // String literals in externals (anonymous tokens) don't need pre-registration.
        r#"grammar { language: "test", externals: [heredoc, "||"] } rule program { "x" }"#,
        |p| vec![r_sym!(p, "heredoc"), r_str!(p, "||")]
    }
    externals_mixed_with_declared_rules {
        r#"grammar { language: "test", externals: [heredoc, comment] }
        rule program { "x" }
        rule comment { regexp("//.*") }"#,
        |p| vec![
            r_sym!(p, "heredoc"),
            r_sym!(p, "comment"),
        ]
    }
    externals_with_regexp_literal {
        r#"grammar { language: "test", externals: [regexp(r"\n")] } rule program { "x" }"#,
        |p| vec![r_pattern!(p, r"\n")]
    }
    externals_used_in_rule_body {
        r#"grammar { language: "test", externals: [heredoc] } rule program { choice("x", heredoc) }"#,
        |p| vec![r_sym!(p, "heredoc")]
    }
    externals_append_inline_lists {
        r#"grammar { language: "test", externals: append([heredoc], [_eof]) } rule program { "x" }"#,
        |p| vec![
            r_sym!(p, "heredoc"),
            r_sym!(p, "_eof"),
        ]
    }
    externals_empty_list {
        r#"grammar { language: "test", externals: [] } rule program { "x" }"#,
        |_p| vec![]
    }
    externals_via_let_with_append {
        r#"let ext: list_t<rule_t> = append([heredoc], [_eof])
        grammar { language: "test", externals: ext }
        rule program { "x" }"#,
        |p| vec![
            r_sym!(p, "heredoc"),
            r_sym!(p, "_eof"),
        ]
    }
    externals_dag_let_referenced_twice_via_append {
        // Same `let` value reached through both arms of `append` is not a cycle.
        r#"let ext: list_t<rule_t> = [heredoc]
        grammar { language: "test", externals: append(ext, ext) }
        rule program { "x" }"#,
        |p| vec![
            r_sym!(p, "heredoc"),
            r_sym!(p, "heredoc"),
        ]
    }
    externals_via_let_mixed_declared_and_undeclared {
        r#"let ext: list_t<rule_t> = [heredoc, comment]
        grammar { language: "test", externals: ext }
        rule program { "x" }
        rule comment { regexp("//.*") }"#,
        |p| vec![
            r_sym!(p, "heredoc"),
            r_sym!(p, "comment"),
        ]
    }
    externals_via_append_let_and_inline {
        r#"let base_ext: list_t<rule_t> = [heredoc]
        grammar { language: "test", externals: append(base_ext, [_eof]) }
        rule program { "x" }"#,
        |p| vec![
            r_sym!(p, "heredoc"),
            r_sym!(p, "_eof"),
        ]
    }
    externals_via_chained_let_with_append {
        r#"let a: list_t<rule_t> = [heredoc]
        let b: list_t<rule_t> = append(a, [_eof])
        grammar { language: "test", externals: b }
        rule program { "x" }"#,
        |p| vec![
            r_sym!(p, "heredoc"),
            r_sym!(p, "_eof"),
        ]
    }
}

rule_names_tests! {
    start_picks_named_rule {
        // `start: third` rotates `third` to position 0, overriding the default
        // "first declared rule is the start symbol" convention.
        r#"grammar { language: "test", start: third }
        rule first { "a" }
        rule second { "b" }
        rule third { "c" }"#,
        vec!["third", "first", "second"]
    }
    start_default_first_rule_when_unset {
        // Regression: omitting `start:` keeps the existing positional behavior.
        r#"grammar { language: "test" }
        rule alpha { "a" }
        rule beta { "b" }"#,
        vec!["alpha", "beta"]
    }
}
