use super::*;

#[test]
fn rule_set_macro_single_rule() {
    let mut g = dsl(r#"
        rules make_program() {
            rule program { "x" }
        }
        grammar { language: "test" }
        @make_program()
        "#);
    assert_eq!(g.variables.len(), 1);
    assert_eq!(g.pool.resolve(g.variables[0].name), "program");
    let actual = g.variables[0].root;
    let expected = {
        let p = &mut g.pool;
        r_str!(p, "x")
    };
    assert_rule_eq(&g.pool, actual, expected);
}

#[test]
fn rule_set_macro_str_param_substitution() {
    let mut g = dsl(r#"
        rules lit(s: str_t) {
            rule program { s }
        }
        grammar { language: "test" }
        @lit("hello")
        "#);
    assert_eq!(g.pool.resolve(g.variables[0].name), "program");
    let actual = g.variables[0].root;
    let expected = {
        let p = &mut g.pool;
        r_str!(p, "hello")
    };
    assert_rule_eq(&g.pool, actual, expected);
}

#[test]
fn rule_set_macro_symref_in_expr_position() {
    // pair("foo") produces a_foo and b_foo. b_foo's body references
    // a_foo by computed name via @concat(...) in expression position.
    let mut g = dsl(r#"
        rules pair(s: str_t) {
            rule @concat("a_", s) { "x" }
            rule @concat("b_", s) { seq(@concat("a_", s), "y") }
        }
        grammar { language: "test", start: a_foo }
        @pair("foo")
        "#);
    let names: Vec<&str> = g.variables.iter().map(|v| g.pool.resolve(v.name)).collect();
    assert_eq!(names, vec!["a_foo", "b_foo"]);
    let b = g
        .variables
        .iter()
        .find(|v| g.pool.resolve(v.name) == "b_foo")
        .unwrap();
    let actual = b.root;
    let expected = {
        let p = &mut g.pool;
        r_seq!(p, [r_sym!(p, "a_foo"), r_str!(p, "y")])
    };
    assert_rule_eq(&g.pool, actual, expected);
}

#[test]
fn rule_set_macro_literal_name_via_at_string() {
    // `@"foo"` evaluates the StringLit to "foo" and produces a rule named foo.
    // Pins behavior - shape is unusual but parser+expand accept it.
    let mut g = dsl(r#"
        rules emit() {
            rule @"foo" { "x" }
        }
        grammar { language: "test", start: foo }
        @emit()
    "#);
    assert_eq!(g.pool.resolve(g.variables[0].name), "foo");
    let actual = g.variables[0].root;
    let expected = {
        let p = &mut g.pool;
        r_str!(p, "x")
    };
    assert_rule_eq(&g.pool, actual, expected);
}

#[test]
fn rule_set_macro_at_string_name_unescapes() {
    // `@"..."` decodes escapes like any string literal: \u{41} is 'A', so the
    // rule is named "aA" - consistent with rule-body string decoding.
    let g = dsl(r#"
        rules emit() {
            rule @"a\u{41}" { "x" }
        }
        grammar { language: "test", start: aA }
        @emit()
    "#);
    assert_eq!(g.pool.resolve(g.variables[0].name), "aA");
}

#[test]
fn dup_macro_with_call_reports_duplicate_not_argcount() {
    // A duplicated rule-set macro plus a call must report the duplicate, not an
    // arg-count mismatch against whichever def macro_index happened to keep.
    let err = dsl_err(
        r#"
        rules m() { rule a { "x" } }
        rules m(p: rule_t) { rule b { p } }
        grammar { language: "test" }
        @m()
    "#,
    );
    let e = assert_err!(err, Resolve);
    assert_eq!(e.kind, ResolveErrorKind::DuplicateDeclaration("m".into()));
}

#[test]
fn dup_macro_with_call_reports_duplicate_reversed() {
    // Same as above with the definitions swapped: the reported error must not
    // depend on declaration order.
    let err = dsl_err(
        r#"
        rules m(p: rule_t) { rule b { p } }
        rules m() { rule a { "x" } }
        grammar { language: "test" }
        @m()
    "#,
    );
    let e = assert_err!(err, Resolve);
    assert_eq!(e.kind, ResolveErrorKind::DuplicateDeclaration("m".into()));
}

#[test]
fn computed_ref_to_macro_name_rejected() {
    // `@"m"` computes the name of a macro. Without the rule-ness check it would
    // pass existence and lower a dangling NamedSymbol.
    let err = dsl_err(
        r#"
        macro m() str_t { "x" }
        rules r() {
            rule program { @"m" }
        }
        grammar { language: "test" }
        @r()
    "#,
    );
    let e = assert_err!(err, Resolve);
    assert_eq!(e.kind, ResolveErrorKind::ComputedNameNotARule("m".into()));
}

#[test]
fn computed_ref_to_let_name_rejected() {
    let err = dsl_err(
        r#"
        let width = "w"
        rules r() {
            rule program { @"width" }
        }
        grammar { language: "test" }
        @r()
    "#,
    );
    let e = assert_err!(err, Resolve);
    assert_eq!(
        e.kind,
        ResolveErrorKind::ComputedNameNotARule("width".into())
    );
}

#[test]
fn computed_ref_unknown_gets_suggestion() {
    // Truly-unknown computed names get the same DidYouMean treatment as
    // ordinary identifiers.
    let err = dsl_err(
        r#"
        rules r() {
            rule extra { @"porgram" }
        }
        grammar { language: "test" }
        @r()
        rule program { "x" }
    "#,
    );
    let e = assert_err!(err, Resolve);
    assert_eq!(
        e.kind,
        ResolveErrorKind::UnknownIdentifier("porgram".into())
    );
    assert!(
        e.notes
            .iter()
            .any(|n| matches!(&n.message, NoteMessage::DidYouMean(s) if s == "program")),
        "expected DidYouMean note, got {:?}",
        e.notes
    );
}

rule_names_tests! {
    rule_set_macro_empty_body_is_noop {
        // An empty `rules` body is allowed. Calling it contributes no rules.
        r#"
        grammar { language: "test" }
        rule program { "p" }
        rules nothing() {}
        @nothing()
        "#,
        vec!["program"]
    }
    rule_set_macro_multiple_rules {
        r#"
        rules pair() {
            rule a { "x" }
            rule b { "y" }
        }
        grammar { language: "test", start: a }
        @pair()
        "#,
        vec!["a", "b"]
    }
    rule_set_macro_computed_name_via_concat {
        r#"
        rules suffixed(s: str_t) {
            rule @concat("foo_", s) { "x" }
        }
        grammar { language: "test", start: foo_bar }
        @suffixed("bar")
        "#,
        vec!["foo_bar"]
    }
    rule_set_macro_multiple_invocations {
        r#"
        rules one(s: str_t) {
            rule @concat("k_", s) { s }
        }
        grammar { language: "test", start: k_a }
        @one("a")
        @one("b")
        @one("c")
        "#,
        vec!["k_a", "k_b", "k_c"]
    }
    rule_set_macro_cfg_gated_top_level_call {
        // apply_cfg runs before expand_macro_calls. A cfg-disabled @call should
        // be dropped entirely, leaving no ExpandedRule items behind.
        r#"
        rules extra_rules() {
            rule extra_a { "ea" }
            rule extra_b { "eb" }
        }
        grammar { language: "test", flags: { disabled: ["GFM"] } }
        rule program { "p" }
        #[cfg(GFM)]
        @extra_rules()
    "#,
        vec!["program"]
    }
    rule_set_macro_cfg_gated_top_level_call_enabled {
        // Mirror of the above with the flag enabled - the @call survives apply_cfg
        // and expands as normal.
        r#"
        rules extra_rules() {
            rule extra_a { "ea" }
            rule extra_b { "eb" }
        }
        grammar { language: "test", flags: { enabled: ["GFM"] } }
        rule program { "p" }
        #[cfg(GFM)]
        @extra_rules()
    "#,
        vec!["program", "extra_a", "extra_b"]
    }
    rule_set_macro_only_decls_no_static_rules {
        // Grammar has zero static `rule` decls outside the macro - all variables
        // come from expansion.
        r#"
        rules core(name: str_t) {
            rule @concat(name, "_a") { "a" }
            rule @concat(name, "_b") { "b" }
        }
        grammar { language: "test", start: x_a }
        @core("x")
    "#,
        vec!["x_a", "x_b"]
    }
    rule_set_macro_with_regular_rules_around {
        // start: program rotates program to position 0. Remaining order is preserved.
        r#"
        rules extras() {
            rule helper_a { "ha" }
            rule helper_b { "hb" }
        }
        grammar { language: "test", start: program }
        rule program { seq(helper_a, helper_b) }
        @extras()
        "#,
        vec!["program", "helper_a", "helper_b"]
    }
}

find_rule_tests! {
    rule_set_macro_rule_param_substitution {
        r#"
        rules wrap(inner: rule_t) {
            rule program { seq("(", inner, ")") }
        }
        rule digit { "1" }
        grammar { language: "test", start: program }
        @wrap(digit)
        "#,
        "program",
        |p| r_seq!(p, [r_str!(p, "("), r_sym!(p, "digit"), r_str!(p, ")")])
    }
    rule_set_macro_with_for_loop_over_param {
        // A for-loop in a rule-set body iterating a list_t<rule_t> param must read
        // the substituted arg, not the template's MacroParam (the iterable lives in
        // ForConfig, separate from the cloned body).
        r#"
        rules with_choices(items: list_t<rule_t>) {
            rule program {
                choice(for (x: rule_t) in items { x })
            }
        }
        rule a { "a" }
        rule b { "b" }
        grammar { language: "test", start: program }
        @with_choices([a, b])
    "#,
        "program",
        |p| r_choice!(p, [r_sym!(p, "a"), r_sym!(p, "b")])
    }
    rule_set_macro_param_in_combinator_positions {
        // Exercises the Repeat/Optional/Field/Alias/Prec arms of clone_with_subst
        // at once. A regression in any arm's recursive subst breaks the assertion.
        r#"
        rules wrap(inner: rule_t, name: rule_t) {
            rule program {
                prec(1, seq(
                    repeat1(inner),
                    optional(inner),
                    field(label, inner),
                    alias(inner, name),
                ))
            }
        }
        rule digit { "1" }
        rule pretty { "pretty" }
        grammar { language: "test", start: program }
        @wrap(digit, pretty)
    "#,
        "program",
        |p| r_prec!(p, Precedence::Integer(1), r_seq!(p, [
            r_repeat!(p, r_sym!(p, "digit")),
            r_choice!(p, [r_sym!(p, "digit"), r_blank!(p)]),
            r_field!(p, "label", r_sym!(p, "digit")),
            r_alias!(p, "pretty", true, r_sym!(p, "digit")),
        ]))
    }
}
