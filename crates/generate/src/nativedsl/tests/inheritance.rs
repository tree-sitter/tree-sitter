use super::*;
use crate::grammars::PrecedenceEntry;

#[test]
fn inherit_rules_and_config() {
    let g = dsl(r#"
        let base = inherit("inherit_base/grammar.tsg")
        grammar { language: "derived", inherits: base }
    "#);
    assert_eq!(g.pool.resolve(g.name), "derived");
    assert_eq!(
        rule_names(&g),
        vec![
            "program",
            "statement",
            "expression",
            "identifier",
            "_inline_rule"
        ]
    );
    assert_eq!(g.word_name.map(|w| g.pool.resolve(w)), Some("identifier"));
    assert_eq!(
        g.inline_names
            .iter()
            .map(|&n| g.pool.resolve(n))
            .collect::<Vec<_>>(),
        vec!["_inline_rule"]
    );
    assert_eq!(g.extra_roots.len(), 1);
}

#[test]
fn inherit_inline_in_config() {
    // `inherits: inherit(...)` directly, with no let binding.
    let g = dsl(r#"
        grammar { language: "derived", inherits: inherit("inherit_base/grammar.tsg") }
        rule extra { "x" }
    "#);
    let names = rule_names(&g);
    assert!(names.contains(&"program"));
    assert!(names.contains(&"extra"));
}

#[test]
fn inherited_rule_set_macro_at_item_position() {
    let mut g = parse_with_modules(
        &[(
            "base.tsg",
            r#"
                rules make(s: str_t) { rule generated { s } }
                grammar { language: "base", start: base_rule }
                rule base_rule { "base" }
            "#,
        )],
        r#"
            let base = inherit("base.tsg")
            grammar { language: "derived", inherits: base, start: generated }
            @base::make("x")
        "#,
    )
    .unwrap();

    let generated = find_rule(&g, "generated");
    let expected = {
        let p = &mut g.pool;
        r_str!(p, "x")
    };
    assert_rule_eq(&g.pool, generated, expected);
    assert!(rule_names(&g).contains(&"base_rule"));
}

#[test]
fn inherit_config_append_inline() {
    let g = dsl(r#"
        let base = inherit("inherit_base/grammar.tsg")
        grammar {
            language: "derived",
            inherits: base,
            inline: append(grammar_config(base, inline), [_extra_inline]),
        }
        rule _extra_inline { "extra" }
    "#);
    assert_eq!(
        g.inline_names
            .iter()
            .map(|&n| g.pool.resolve(n))
            .collect::<Vec<_>>(),
        vec!["_inline_rule", "_extra_inline"]
    );
}

#[test]
fn inherit_config_append_extras() {
    let g = dsl(r#"
        let base = inherit("inherit_base/grammar.tsg")
        grammar {
            language: "derived",
            inherits: base,
            extras: append(grammar_config(base, extras), [comment]),
        }
        rule comment { regexp(r"//.*") }
    "#);
    assert_eq!(g.extra_roots.len(), 2);
}

#[test]
fn config_expr_let_binding() {
    let g = dsl(r#"
        let my_extras: list_t<rule_t> = [regexp(r"\s"), comment]
        grammar {
            language: "test",
            extras: my_extras,
        }
        rule program { "x" }
        rule comment { regexp(r"//.*") }
    "#);
    assert_eq!(g.extra_roots.len(), 2);
}

#[test]
fn config_expr_word() {
    let g = dsl(r#"
        let base = inherit("inherit_base/grammar.tsg")
        grammar { language: "derived", inherits: base, word: grammar_config(base, word) }
    "#);
    assert_eq!(g.word_name.map(|w| g.pool.resolve(w)), Some("identifier"));
}

#[test]
fn override_rule_emitted_by_rule_set_macro() {
    // `override rule` inside a `rules` body propagates is_override through
    // expansion, so the generated rule replaces the inherited base rule.
    let mut g = dsl(r#"
        let base = inherit("inherit_base/grammar.tsg")
        rules wrap_expression(rhs: rule_t) {
            override rule expression { choice(identifier, rhs) }
        }
        grammar { language: "derived", inherits: base }
        @wrap_expression("99")
    "#);
    let actual = find_rule(&g, "expression");
    let expected = {
        let p = &mut g.pool;
        r_choice!(p, [r_sym!(p, "identifier"), r_str!(p, "99")])
    };
    assert_rule_eq(&g.pool, actual, expected);
    // Sibling inherited rules untouched.
    let actual = find_rule(&g, "_inline_rule");
    let expected = {
        let p = &mut g.pool;
        r_str!(p, "inline")
    };
    assert_rule_eq(&g.pool, actual, expected);
}

#[test]
fn override_rule_replaces_body() {
    let mut g = dsl(r#"
        let base = inherit("inherit_base/grammar.tsg")
        grammar { language: "derived", inherits: base }
        override rule expression { choice(identifier, "42") }
    "#);
    let actual = find_rule(&g, "expression");
    let expected = {
        let p = &mut g.pool;
        r_choice!(p, [r_sym!(p, "identifier"), r_str!(p, "42")])
    };
    assert_rule_eq(&g.pool, actual, expected);
    let actual = find_rule(&g, "_inline_rule");
    let expected = {
        let p = &mut g.pool;
        r_str!(p, "inline")
    };
    assert_rule_eq(&g.pool, actual, expected);
}

#[test]
fn override_preserves_rule_order() {
    let mut g = dsl(r#"
        let base = inherit("inherit_base/grammar.tsg")
        grammar { language: "derived", inherits: base }
        override rule statement { "overridden" }
    "#);
    assert_eq!(g.pool.resolve(g.variables[1].name), "statement");
    let actual = g.variables[1].root;
    let expected = {
        let p = &mut g.pool;
        r_str!(p, "overridden")
    };
    assert_rule_eq(&g.pool, actual, expected);
}

#[test]
fn new_rules_appended() {
    let mut g = dsl(r#"
        let base = inherit("inherit_base/grammar.tsg")
        grammar { language: "derived", inherits: base }
        rule new_rule { "hello" }
    "#);
    assert_eq!(g.pool.resolve(g.variables.last().unwrap().name), "new_rule");
    let actual = g.variables.last().unwrap().root;
    let expected = {
        let p = &mut g.pool;
        r_str!(p, "hello")
    };
    assert_rule_eq(&g.pool, actual, expected);
    assert_eq!(g.variables.len(), 6);
}

#[test]
fn override_and_new_combined() {
    let mut g = dsl(r#"
        let base = inherit("inherit_base/grammar.tsg")
        grammar { language: "derived", inherits: base }
        override rule expression { choice(identifier, number) }
        rule number { regexp("[0-9]+") }
    "#);
    assert_eq!(g.variables.len(), 6);
    let actual = find_rule(&g, "expression");
    let expected = {
        let p = &mut g.pool;
        r_choice!(p, [r_sym!(p, "identifier"), r_sym!(p, "number")])
    };
    assert_rule_eq(&g.pool, actual, expected);
}

#[test]
fn config_override_replaces() {
    let g = dsl(r#"
        let base = inherit("inherit_base/grammar.tsg")
        grammar {
            language: "derived",
            inherits: base,
            extras: [regexp(r"\s"), regexp(r"//.*")],
        }
    "#);
    assert_eq!(g.extra_roots.len(), 2);
}

#[test]
fn config_word_overridden() {
    let g = dsl(r#"
        let base = inherit("inherit_base/grammar.tsg")
        grammar { language: "derived", inherits: base, word: expression }
    "#);
    assert_eq!(g.word_name.map(|w| g.pool.resolve(w)), Some("expression"));
}

#[test]
fn rule_inline_expands_base_rule_body() {
    let mut g = dsl(r#"
        let base = inherit("inherit_base/grammar.tsg")
        grammar { language: "derived", inherits: base }
        override rule expression { choice(base::expression, "extended") }
    "#);
    let actual = find_rule(&g, "expression");
    let expected = {
        let p = &mut g.pool;
        r_choice!(p, [r_sym!(p, "identifier"), r_str!(p, "extended")])
    };
    assert_rule_eq(&g.pool, actual, expected);
}

#[test]
fn config_access_extras() {
    let mut g = dsl(r#"
        let base = inherit("inherit_base/grammar.tsg")
        grammar { language: "derived", inherits: base, extras: grammar_config(base, extras) }
        override rule program { "x" }
    "#);
    assert_eq!(g.pool.resolve(g.name), "derived");
    // base has extras: [regexp("\\s")], verify it was inherited
    assert_eq!(g.extra_roots.len(), 1);
    let actual = g.extra_roots[0];
    let expected = {
        let p = &mut g.pool;
        r_pattern!(p, "\\s")
    };
    assert_rule_eq(&g.pool, actual, expected);
}

#[test]
fn config_all_fields_access_and_append() {
    let mut g = dsl(r#"
        let base = inherit("inherit_base/grammar_full_config.tsg")
        grammar {
            language: "derived",
            inherits: base,
            extras: grammar_config(base, extras),
            externals: append(grammar_config(base, externals), [eof_marker]),
            inline: grammar_config(base, inline),
            supertypes: append(grammar_config(base, supertypes), [_statement]),
            word: grammar_config(base, word),
            conflicts: append(grammar_config(base, conflicts), [[keyword, _statement]]),
            precedences: append(grammar_config(base, precedences), [["unary", "binary"]]),
        }
        rule _statement { "stmt" }
        rule eof_marker { "EOF" }
    "#);
    let extras = g.extra_roots.clone();
    let externals = g.external_roots.clone();
    let (expected_extras, expected_externals) = {
        let p = &mut g.pool;
        (
            vec![r_pattern!(p, "\\s")],
            vec![r_sym!(p, "heredoc"), r_sym!(p, "eof_marker")],
        )
    };
    assert_rules_eq(&g.pool, &extras, &expected_extras);
    assert_rules_eq(&g.pool, &externals, &expected_externals);
    assert_eq!(
        g.inline_names
            .iter()
            .map(|&n| g.pool.resolve(n))
            .collect::<Vec<_>>(),
        vec!["_inline_rule"]
    );
    assert_eq!(
        g.supertype_names
            .iter()
            .map(|&n| g.pool.resolve(n))
            .collect::<Vec<_>>(),
        vec!["_expression", "_statement"]
    );
    assert_eq!(g.word_name.map(|w| g.pool.resolve(w)), Some("identifier"));
    assert_eq!(
        conflict_names(&g),
        vec![vec!["identifier", "keyword"], vec!["keyword", "_statement"],]
    );
    assert_eq!(
        g.precedence_orderings,
        vec![
            vec![
                PrecedenceEntry::Name(g.pool.intern("member")),
                PrecedenceEntry::Name(g.pool.intern("call")),
            ],
            vec![
                PrecedenceEntry::Name(g.pool.intern("unary")),
                PrecedenceEntry::Name(g.pool.intern("binary")),
            ],
        ]
    );
}

#[test]
fn externals_append_inherited_with_new_undeclared() {
    // Append a new undeclared external to inherited externals
    let g = dsl(r#"
        let base = inherit("inherit_base/grammar_full_config.tsg")
        grammar {
            language: "derived",
            inherits: base,
            externals: append(grammar_config(base, externals), [_eof_marker]),
        }
    "#);
    // base has [heredoc], we add [_eof_marker]
    assert_eq!(g.external_roots.len(), 2);
}

#[test]
fn externals_inherited_directly() {
    // grammar_config(base, externals) used directly (no append)
    let g = dsl(r#"
        let base = inherit("inherit_base/grammar_full_config.tsg")
        grammar {
            language: "derived",
            inherits: base,
            externals: grammar_config(base, externals),
        }
    "#);
    assert_eq!(g.external_roots.len(), 1);
}

#[test]
fn append_concatenates_lists() {
    let mut g = dsl(r#"
        grammar { language: "test" }
        let a: list_t<str_t> = ["x", "y"]
        let b: list_t<str_t> = ["z"]
        let c: list_t<str_t> = append(a, b)
        rule program { choice(for (s: str_t) in c { s }) }
    "#);
    let actual = g.variables[0].root;
    let expected = {
        let p = &mut g.pool;
        r_choice!(p, [r_str!(p, "x"), r_str!(p, "y"), r_str!(p, "z")])
    };
    assert_rule_eq(&g.pool, actual, expected);
}

#[test]
fn inherit_from_grammar_that_imports() {
    // The base imports a helper whose rule is used by its grammar.
    // This ensures nested module references remain valid during inheritance.
    let g = dsl(r#"
        let base = inherit("inherit_base/grammar_with_import.tsg")
        grammar { language: "derived", inherits: base }
        rule extra { "extra" }
    "#);
    assert_eq!(g.pool.resolve(g.name), "derived");
    // Inherited rule from base uses the imported helper macro
    assert!(rule_names(&g).contains(&"program"));
    assert!(rule_names(&g).contains(&"extra"));
}

#[test]
fn override_rule_can_access_base_let() {
    // An override rule body referencing a base let exercises eager evaluation of
    // the base's let bindings before the override body reads them.
    let mut g = parse_with_modules(
        &[(
            "base.tsg",
            r#"
        let GREETING: str_t = "hello"
        grammar { language: "base" }
        rule program { GREETING }
        "#,
        )],
        r#"
        let base = inherit("base.tsg")
        grammar { language: "derived", inherits: base }
        override rule program { seq(base::GREETING, "!") }
        "#,
    )
    .unwrap();
    let actual = find_rule(&g, "program");
    let expected = {
        let p = &mut g.pool;
        r_seq!(p, [r_str!(p, "hello"), r_str!(p, "!")])
    };
    assert_rule_eq(&g.pool, actual, expected);
}

#[test]
fn nested_inheritance_merges_all_rules() {
    // child inherits parent inherits grandparent. All three levels' rules
    // should appear in the child's grammar.
    let mut g = dsl(r#"
        let parent = inherit("inherit_base/nested_parent.tsg")
        grammar { language: "child", inherits: parent }
        rule child_only { "child" }
    "#);
    assert_eq!(g.pool.resolve(g.name), "child");
    let names = rule_names(&g);
    // Grandparent's rules
    assert!(names.contains(&"program"));
    assert!(names.contains(&"identifier"));
    assert!(names.contains(&"_gp_inline"));
    // Parent's added rules
    assert!(names.contains(&"parent_only"));
    assert!(names.contains(&"_parent_inline"));
    // Child's own rule
    assert!(names.contains(&"child_only"));
    // Parent's override of statement should be present (not grandparent's)
    let actual = find_rule(&g, "statement");
    let expected = {
        let p = &mut g.pool;
        r_choice!(p, [r_sym!(p, "identifier"), r_str!(p, "!")])
    };
    assert_rule_eq(&g.pool, actual, expected);
}

#[test]
fn nested_inheritance_qualified_access_to_grandparent_via_parent() {
    // The child references parent::identifier, which is defined in the
    // grandparent. The parent's lowering merges it into parent.lowered.variables.
    let g = dsl(r#"
        let parent = inherit("inherit_base/nested_parent.tsg")
        grammar { language: "child", inherits: parent }
        rule wrapper { parent::identifier }
    "#);
    let wrapper = find_rule(&g, "wrapper");
    assert!(matches!(g.pool.node(wrapper), Rule::Pattern(v, _) if g.pool.resolve(v) == "[a-z]+"));
}

#[test]
fn nested_inheritance_explicit_chain_access() {
    // child reaches grandparent via parent::gp::identifier, traversing
    // parent's own inherit binding (`gp`).
    let g = dsl(r#"
        let parent = inherit("inherit_base/nested_parent.tsg")
        grammar { language: "child", inherits: parent }
        rule wrapper { parent::gp::identifier }
    "#);
    let wrapper = find_rule(&g, "wrapper");
    assert!(matches!(g.pool.node(wrapper), Rule::Pattern(v, _) if g.pool.resolve(v) == "[a-z]+"));
}

#[test]
fn nested_inheritance_child_override_of_grandparent_rule() {
    // child overrides identifier (defined in grandparent, untouched by parent).
    // The override should win.
    let g = dsl(r#"
        let parent = inherit("inherit_base/nested_parent.tsg")
        grammar { language: "child", inherits: parent }
        override rule identifier { regexp("[A-Z]+") }
    "#);
    let identifier = find_rule(&g, "identifier");
    assert!(
        matches!(g.pool.node(identifier), Rule::Pattern(v, _) if g.pool.resolve(v) == "[A-Z]+")
    );
}

#[test]
fn nested_inheritance_child_override_of_parent_override() {
    // parent overrides statement (originally from grandparent).
    // child overrides statement again. Child's version wins.
    let mut g = dsl(r#"
        let parent = inherit("inherit_base/nested_parent.tsg")
        grammar { language: "child", inherits: parent }
        override rule statement { "child_statement" }
    "#);
    let statement = find_rule(&g, "statement");
    let actual = statement;
    let expected = {
        let p = &mut g.pool;
        r_str!(p, "child_statement")
    };
    assert_rule_eq(&g.pool, actual, expected);
}

#[test]
fn nested_inheritance_grammar_config_transitive() {
    // parent appended _parent_inline to gp's inline. child reads
    // grammar_config(parent, inline) which should return [_gp_inline, _parent_inline].
    let g = dsl(r#"
        let parent = inherit("inherit_base/nested_parent.tsg")
        grammar {
            language: "child",
            inherits: parent,
            inline: append(grammar_config(parent, inline), [_child_inline]),
        }
        rule _child_inline { "c" }
    "#);
    assert_eq!(
        g.inline_names
            .iter()
            .map(|&n| g.pool.resolve(n))
            .collect::<Vec<_>>(),
        vec!["_gp_inline", "_parent_inline", "_child_inline"]
    );
}

#[test]
fn nested_inheritance_chain_accesses_pre_override_rule() {
    // parent overrides `statement`: from the child, `parent::statement` yields
    // parent's override while `parent::gp::statement` yields grandparent's.
    let mut g = dsl(r#"
        let parent = inherit("inherit_base/nested_parent.tsg")
        grammar { language: "child", inherits: parent }
        rule via_parent { parent::statement }
        rule via_chain { parent::gp::statement }
    "#);
    let via_parent = find_rule(&g, "via_parent");
    let via_chain = find_rule(&g, "via_chain");
    // parent::statement -> parent's override: choice(identifier, "!")
    let actual = via_parent;
    let expected = {
        let p = &mut g.pool;
        r_choice!(p, [r_sym!(p, "identifier"), r_str!(p, "!")])
    };
    assert_rule_eq(&g.pool, actual, expected);
    // parent::gp::statement -> grandparent's original: identifier
    let actual = via_chain;
    let expected = {
        let p = &mut g.pool;
        r_sym!(p, "identifier")
    };
    assert_rule_eq(&g.pool, actual, expected);
}

#[test]
fn nested_inheritance_word_token_propagates() {
    // grandparent set word: identifier. parent didn't override. child should
    // see the inherited word_name.
    let g = dsl(r#"
        let parent = inherit("inherit_base/nested_parent.tsg")
        grammar { language: "child", inherits: parent }
    "#);
    assert_eq!(g.word_name.map(|w| g.pool.resolve(w)), Some("identifier"));
}

#[test]
fn import_before_inherit_in_source_order() {
    // Import before inherit in source order. Tests that eval order doesn't
    // corrupt the module values table.
    let mut g = dsl(r#"
        let h = import("import_helpers/helpers.tsg")
        let base = inherit("inherit_base/grammar.tsg")
        grammar { language: "derived", inherits: base }
        rule new_rule { h::comma_sep1(identifier) }
    "#);
    assert_eq!(g.pool.resolve(g.name), "derived");
    let actual = find_rule(&g, "new_rule");
    let expected = comma_sep1_rule(&mut g.pool, "identifier");
    assert_rule_eq(&g.pool, actual, expected);
}

#[test]
fn inherited_external_qualified_access() {
    // A child can reference an inherited external via `base::name`, resolving
    // through the base's lowered external_roots.
    let mut g = parse_with_modules(
        &[(
            "base.tsg",
            r#"
        grammar { language: "base", externals: [_token] }
        rule program { _token }
    "#,
        )],
        r#"
        let base = inherit("base.tsg")
        grammar { language: "child", inherits: base, externals: [base::_token] }
        override rule program { seq(base::_token, "!") }
    "#,
    )
    .unwrap();
    assert_eq!(g.external_roots.len(), 1);
    let actual = g.external_roots[0];
    let expected = {
        let p = &mut g.pool;
        r_sym!(p, "_token")
    };
    assert_rule_eq(&g.pool, actual, expected);
    let actual = find_rule(&g, "program");
    let expected = {
        let p = &mut g.pool;
        r_seq!(p, [r_sym!(p, "_token"), r_str!(p, "!")])
    };
    assert_rule_eq(&g.pool, actual, expected);
}

#[test]
fn inherited_external_bare_reference() {
    // An inherited external is referenceable by bare name, like an inherited
    // rule (as in grammar.js's `$.name`), not only via `base::name`.
    let mut g = parse_with_modules(
        &[(
            "base.tsg",
            r#"grammar { language: "base", externals: [_token] }
        expect _token
        rule program { _token }
        "#,
        )],
        r#"let base = inherit("base.tsg")
        grammar { language: "child", inherits: base }
        rule extra { _token }"#,
    )
    .unwrap();
    let actual = find_rule(&g, "extra");
    let expected = {
        let p = &mut g.pool;
        r_sym!(p, "_token")
    };
    assert_rule_eq(&g.pool, actual, expected);
}

#[test]
fn inherited_rule_also_in_externals() {
    // A base may list one of its own rules in `externals` (external-scanner token
    // with a grammar-rule fallback), so the name is in both variables and
    // external_roots. Inheriting it must not double-register in the child.
    let mut g = parse_with_modules(
        &[(
            "base.tsg",
            r#"grammar { language: "base", externals: [tok] }
        rule tok { "x" }
        "#,
        )],
        r#"let base = inherit("base.tsg")
        grammar { language: "child", inherits: base }
        rule extra { tok }"#,
    )
    .unwrap();
    let actual = find_rule(&g, "extra");
    let expected = {
        let p = &mut g.pool;
        r_sym!(p, "tok")
    };
    assert_rule_eq(&g.pool, actual, expected);
}

#[test]
fn config_only_base_is_allowed() {
    // A config-only base (no rules) is a native-DSL extension: it can't compile
    // standalone but contributes config to a child. Only the root's rule count
    // is enforced.
    let mut g = parse_with_modules(
        &[(
            "base.tsg",
            r#"grammar { language: "base", externals: [_eof] }
        expect _eof
        "#,
        )],
        r#"let base = inherit("base.tsg")
        grammar { language: "child", inherits: base }
        rule program { "x" }"#,
    )
    .unwrap();
    // Child supplies the only rule; base contributes its externals as config.
    assert_eq!(rule_names(&g), vec!["program"]);
    let actual = g.external_roots.clone();
    let expected = {
        let p = &mut g.pool;
        vec![r_sym!(p, "_eof")]
    };
    assert_rules_eq(&g.pool, &actual, &expected);
}

#[test]
fn start_rotates_inherited_rule_to_front() {
    // The start rule lives mid-grammar in the base; `start:` makes it the start
    // in the inheriting grammar without re-declaring every rule.
    let g = dsl(r#"
        let base = inherit("inherit_base/grammar.tsg")
        grammar { language: "derived", inherits: base, start: identifier }
    "#);
    let names = rule_names(&g);
    assert_eq!(names[0], "identifier");
    // All other base rules still present, just shifted.
    assert!(names.contains(&"program"));
    assert!(names.contains(&"statement"));
    assert!(names.contains(&"expression"));
}

#[test]
fn start_picks_derived_rule_under_inheritance() {
    // `start:` can name a derived-grammar rule (not the base); the rotation must
    // find names across the base/local/helper buckets build_grammar produces.
    let g = dsl(r#"
        let base = inherit("inherit_base/grammar.tsg")
        grammar { language: "derived", inherits: base, start: extra }
        rule extra { "added" }
    "#);
    let names = rule_names(&g);
    assert_eq!(names[0], "extra");
    assert!(names.contains(&"program"));
    assert!(names.contains(&"identifier"));
}

#[test]
fn grammar_config_reads_base_language() {
    // grammar_config(base, language) reads the base grammar's name as a str_t.
    let mut g = dsl(r#"
        let base = inherit("inherit_base/grammar.tsg")
        grammar { language: "derived", inherits: base }
        rule lang_name { grammar_config(base, language) }
    "#);
    let actual = find_rule(&g, "lang_name");
    let expected = {
        let p = &mut g.pool;
        r_str!(p, "base")
    };
    assert_rule_eq(&g.pool, actual, expected);
}

#[test]
fn override_with_rule_from_two_sources_errors() {
    // `expr` comes from two imported helpers; an `override rule expr` claims one,
    // so the second collides as a duplicate declaration, not a silent dup.
    let err = expect_err(parse_with_modules(
        &[
            ("a.tsg", "rule expr { \"from_a\" }\n"),
            ("b.tsg", "rule expr { \"from_b\" }\n"),
        ],
        r#"
        let a = import("a.tsg")
        let b = import("b.tsg")
        grammar { language: "test" }
        rule program { expr }
        override rule expr { "overridden" }
    "#,
    ));
    let e = assert_err!(err, Resolve);
    assert_eq!(
        e.kind,
        ResolveErrorKind::DuplicateDeclaration("expr".into())
    );
}
