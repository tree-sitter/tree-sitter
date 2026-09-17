//! Tests for grammar feature flags and `#[cfg(...)]` attributes.

use super::*;

#[test]
fn cfg_in_non_list_position_parse_error() {
    let err = dsl_err(
        r#"
        grammar { language: "t", flags: { enabled: ["GFM"] } }
        rule program { #[cfg(GFM)] "x" }
    "#,
    );
    assert_err!(err, Parse);
}

#[test]
fn cfg_flag_declared_twice_errors() {
    let err = dsl_err(
        r#"
        grammar { language: "t", flags: { enabled: ["X"], disabled: ["X"] } }
        rule program { "x" }
    "#,
    );
    let e = assert_err!(err, Cfg);
    assert_eq!(e.kind, CfgErrorKind::FlagDeclaredTwice("X".into()));
    let note = e.notes.first().expect("expected FirstDefinedHere note");
    assert_eq!(note.message, NoteMessage::FirstDefinedHere);
}

#[test]
fn cfg_in_grammar_config_field() {
    // Grammar config fields are traversed separately from other root items.
    let g = dsl(r#"
        grammar {
            language: "t",
            flags: { enabled: ["A"], disabled: ["B"] },
            conflicts: [
                [foo, bar],
                #[cfg(A)] [foo, baz],
                #[cfg(B)] [bar, baz],
            ],
        }
        rule foo { "a" }
        rule bar { "b" }
        rule baz { "c" }
    "#);
    assert_eq!(g.conflict_names.len(), 2);
}

#[test]
fn cfg_dropped_decl_enriches_undefined_symbol_error() {
    let err = dsl_err(
        r#"
        grammar { language: "t", flags: { disabled: ["GFM"] } }
        rule program { strikethrough }
        #[cfg(GFM)]
        rule strikethrough { "~~" }
    "#,
    );
    let e = assert_err!(err, Resolve);
    assert_eq!(
        e.kind,
        ResolveErrorKind::UnknownIdentifier("strikethrough".into())
    );
    let note = e.notes.first().expect("expected cfg note on error");
    assert_eq!(note.message, NoteMessage::GatedByDisabledCfg("GFM".into()));
}

#[test]
fn cfg_enrichment_preserves_existing_note() {
    let err = dsl_err(
        r#"
        grammar { language: "t", flags: { disabled: ["X"] } }
        #[cfg(X)] rule widget { "x" }
        rule widgets { "y" }
        rule program { widget }
    "#,
    );
    let e = assert_err!(err, Resolve);
    assert_eq!(e.kind, ResolveErrorKind::UnknownIdentifier("widget".into()));
    let kinds: Vec<_> = e.notes.iter().map(|n| &n.message).collect();
    assert!(
        kinds
            .iter()
            .any(|m| matches!(m, NoteMessage::DidYouMean(s) if s == "widgets")),
        "expected DidYouMean note, got {kinds:?}"
    );
    assert!(
        kinds
            .iter()
            .any(|m| matches!(m, NoteMessage::GatedByDisabledCfg(f) if f == "X")),
        "expected GatedByDisabledCfg note, got {kinds:?}"
    );
}

#[test]
fn cfg_dropped_macro_enriches_error() {
    let err = dsl_err(
        r#"
        grammar { language: "t", flags: { disabled: ["X"] } }
        rule program { gated() }
        #[cfg(X)] macro gated() rule_t { "a" }
    "#,
    );
    let e = assert_err!(err, Resolve);
    assert_eq!(e.kind, ResolveErrorKind::UnknownIdentifier("gated".into()));
    let note = e.notes.first().expect("expected cfg note on error");
    assert_eq!(note.message, NoteMessage::GatedByDisabledCfg("X".into()));
}

#[test]
fn cfg_dropped_ruleset_macro_enriches_error() {
    let err = dsl_err(
        r#"
        #[cfg(X)] rules gated() { rule a { "x" } }
        grammar { language: "t", flags: { disabled: ["X"] } }
        rule program { "p" }
        @gated()
    "#,
    );
    let e = assert_err!(err, Expand);
    assert_eq!(e.kind, ExpandErrorKind::UnknownMacro("gated".into()));
    let note = e.notes.first().expect("expected cfg note on error");
    assert_eq!(note.message, NoteMessage::GatedByDisabledCfg("X".into()));
}

#[test]
fn cfg_dropped_macro_keeps_same_named_survivor() {
    // The macro index must be rebuilt after cfg filtering.
    let mut g = dsl(r#"
        #[cfg(Y)] rules dup() { rule program { "stable" } }
        #[cfg(X)] rules dup() { rule program { "gated" } }
        grammar { language: "test", flags: { enabled: ["Y"], disabled: ["X"] } }
        @dup()
    "#);
    assert_eq!(g.pool.resolve(g.variables[0].name), "program");
    let actual = g.variables[0].root;
    let expected = {
        let p = &mut g.pool;
        r_str!(p, "stable")
    };
    assert_rule_eq(&g.pool, actual, expected);
}

#[test]
fn helper_module_inherits_cfg_from_importer() {
    // Helper modules use the importing grammar's cfg environment.
    let mut g = parse_with_modules(
        &[(
            "h.tsg",
            r#"
            macro gated() rule_t { choice("a", #[cfg(GFM)] "b", "c") }
        "#,
        )],
        r#"
        let h = import("h.tsg")
        grammar { language: "t", flags: { enabled: ["GFM"] } }
        rule program { h::gated() }
        "#,
    )
    .unwrap();
    let actual = find_rule(&g, "program");
    let expected = {
        let p = &mut g.pool;
        r_choice!(p, [r_str!(p, "a"), r_str!(p, "b"), r_str!(p, "c")])
    };
    assert_rule_eq(&g.pool, actual, expected);
}

#[test]
fn cfg_attribute_nesting_is_bounded() {
    let nest = "#[cfg(X)] ".repeat(300);
    let src = format!(
        r#"grammar {{ language: "t", flags: {{ enabled: ["X"] }} }} {nest} rule r {{ "x" }}"#
    );
    let err = dsl_err(&src);
    let e = assert_err!(err, Parse);
    assert_eq!(e.kind, ParseErrorKind::NestingTooDeep);
}

#[test]
fn cfg_disabled_import_does_not_load_file() {
    let input = r#"
        grammar { language: "t", flags: { disabled: ["GFM"] } }
        #[cfg(GFM)]
        let h = import("does-not-exist.tsg")
        rule program { "x" }
    "#;
    let g = parse_native_dsl(input, std::path::Path::new(".")).unwrap();
    assert_eq!(rule_names(&g), vec!["program"]);
}

#[test]
fn cfg_disabled_inherit_does_not_merge_parent() {
    let g = parse_with_modules(
        &[(
            "parent.tsg",
            r#"
            grammar { language: "p" }
            rule parent_only { "p" }
        "#,
        )],
        r#"
        grammar { language: "t", flags: { disabled: ["EXT"] } }
        #[cfg(EXT)]
        let base = inherit("parent.tsg")
        rule program { "x" }
        "#,
    )
    .unwrap();
    assert_eq!(rule_names(&g), vec!["program"]);
}

#[test]
fn cfg_enabled_inherit_still_loads_parent() {
    let g = parse_with_modules(
        &[(
            "parent.tsg",
            r#"
            grammar { language: "p" }
            rule parent_only { "p" }
        "#,
        )],
        r#"
        #[cfg(EXT)]
        let base = inherit("parent.tsg")
        grammar {
            language: "t",
            flags: { enabled: ["EXT"] },
            inherits: base,
        }
        rule program { "x" }
        "#,
    )
    .unwrap();
    assert_eq!(rule_names(&g), vec!["parent_only", "program"]);
}

#[test]
fn cfg_disabled_first_inherit_promotes_second() {
    // Filtering the first inherit must promote the second.
    let g = parse_with_modules(
        &[(
            "base.tsg",
            "grammar { language: \"base\" }\nrule base_rule { \"b\" }\n",
        )],
        r#"
        #[cfg(X)] let skipped = inherit("missing.tsg")
        let chosen = inherit("base.tsg")
        grammar { language: "t", inherits: chosen, flags: { disabled: ["X"] } }
        rule program { "x" }
        "#,
    )
    .unwrap();
    assert!(
        rule_names(&g).contains(&"base_rule"),
        "got {:?}",
        rule_names(&g)
    );
}

#[test]
fn cfg_disabled_second_inherit_is_not_multiple_inherits() {
    // Filtering the second inherit must clear the duplicate marker.
    let g = parse_with_modules(
        &[(
            "base.tsg",
            "grammar { language: \"base\" }\nrule base_rule { \"b\" }\n",
        )],
        r#"
        let chosen = inherit("base.tsg")
        #[cfg(X)] let skipped = inherit("missing.tsg")
        grammar { language: "t", inherits: chosen, flags: { disabled: ["X"] } }
        rule program { "x" }
        "#,
    )
    .unwrap();
    assert!(
        rule_names(&g).contains(&"base_rule"),
        "got {:?}",
        rule_names(&g)
    );
}

#[test]
fn cfg_dropped_attribution_uses_owning_module() {
    // Dropped declarations are attributed to the module that owns them.
    let err = expect_err(parse_with_modules(
        &[(
            "parent.tsg",
            r#"
            grammar { language: "p", flags: { disabled: ["P"] } }
            rule program_p { strikethrough }
            #[cfg(P)] rule strikethrough { "p" }
        "#,
        )],
        r#"
        let base = inherit("parent.tsg")
        grammar {
            language: "t",
            flags: { disabled: ["C"] },
            inherits: base,
        }
        rule program { "x" }
        #[cfg(C)] rule strikethrough { "c" }
        "#,
    ));
    let inner = *assert_err!(err, Module).inner;
    let e = assert_err!(inner, Resolve);
    let note = e.notes.first().expect("expected cfg note on error");
    assert_eq!(note.message, NoteMessage::GatedByDisabledCfg("P".into()));
}

#[test]
fn cfg_inheriting_grammar_overrides_parent_flag_value() {
    // The inheriting grammar's cfg values override the parent's declarations.
    let g = parse_with_modules(
        &[(
            "parent.tsg",
            r#"
            grammar { language: "p", flags: { disabled: ["X"] } }
            rule parent_base { "p" }
            #[cfg(X)]
            rule parent_only { "po" }
        "#,
        )],
        r#"
        let base = inherit("parent.tsg")
        grammar {
            language: "t",
            flags: { enabled: ["X"] },
            inherits: base,
        }
        rule program { "x" }
        #[cfg(X)]
        rule child_only { "co" }
        "#,
    )
    .unwrap();
    assert_eq!(
        rule_names(&g),
        vec!["parent_base", "parent_only", "program", "child_only"]
    );
}

#[test]
fn inherited_grammar_must_declare_used_cfg_flag() {
    let err = expect_err(parse_with_modules(
        &[(
            "parent.tsg",
            r#"
            grammar { language: "p" }
            #[cfg(X)] rule parent_only { "p" }
        "#,
        )],
        r#"
        let base = inherit("parent.tsg")
        grammar {
            language: "t",
            flags: { enabled: ["X"] },
            inherits: base,
        }
        rule program { "x" }
        "#,
    ));
    let inner = *assert_err!(err, Module).inner;
    let error = assert_err!(inner, Cfg);
    assert_eq!(error.kind, CfgErrorKind::FlagUnknown("X".into()));
}

#[test]
fn cfg_three_level_inheritance_root_flag_wins() {
    // The root grammar's cfg value applies throughout its inheritance chain.
    let g = parse_with_modules(
        &[
            (
                "grandparent.tsg",
                r#"
            grammar { language: "g", flags: { enabled: ["X"] } }
            rule grandparent_base { "g" }
            #[cfg(X)]
            rule grandparent_only { "go" }
        "#,
            ),
            (
                "parent.tsg",
                r#"
                let gbase = inherit("grandparent.tsg")
                grammar {
                    language: "p",
                    flags: { enabled: ["X"] },
                    inherits: gbase,
                }
                rule parent_base { "p" }
                #[cfg(X)]
                rule parent_only { "po" }
            "#,
            ),
        ],
        r#"
        let pbase = inherit("parent.tsg")
        grammar {
            language: "t",
            flags: { disabled: ["X"] },
            inherits: pbase,
        }
        rule program { "x" }
        #[cfg(X)]
        rule root_only { "ro" }
        "#,
    )
    .unwrap();
    assert_eq!(
        rule_names(&g),
        vec!["grandparent_base", "parent_base", "program"]
    );
}

#[test]
fn wrapper_overrides_base_extension_flags() {
    // A ruleless wrapper may override the inherited grammar's cfg defaults.
    let g = parse_with_modules(
        &[(
            "base.tsg",
            r#"
            grammar { language: "md", flags: { enabled: ["TABLE"], disabled: ["TAGS"] } }
            rule document { "x" }
            #[cfg(TABLE)] rule pipe_table { "|" }
            #[cfg(TAGS)] rule tag { "<" }
        "#,
        )],
        r#"
        let base = inherit("base.tsg")
        grammar {
            language: "md",
            inherits: base,
            flags: { enabled: ["TAGS"], disabled: ["TABLE"] },
        }
        "#,
    )
    .unwrap();
    assert_eq!(rule_names(&g), vec!["document", "tag"]);
}

#[test]
fn cfg_base_flag_does_not_leak_to_sibling_import() {
    let modules = [
        (
            "base.tsg",
            r#"
              grammar { language: "base", flags: { enabled: ["BASE_FEATURE"] } }
              rule base_rule { "b" }
              "#,
        ),
        (
            "helper.tsg",
            "#[cfg(BASE_FEATURE)]\nrule helper_rule { \"h\" }",
        ),
    ];

    for refs in [
        r#"
          let base = inherit("base.tsg")
          let helper = import("helper.tsg")
          "#,
        r#"
          let helper = import("helper.tsg")
          let base = inherit("base.tsg")
          "#,
    ] {
        let root = format!(
            r#"
              {refs}
              grammar {{ language: "root", inherits: base }}
              rule program {{ helper_rule }}
              "#
        );
        let err = expect_err(parse_with_modules(&modules, &root));
        let inner = *assert_err!(err, Module).inner;
        let error = assert_err!(inner, Cfg);
        assert_eq!(error.kind, CfgErrorKind::FlagUnknown("BASE_FEATURE".into()));
    }
}

#[test]
fn cfg_cached_helper_respects_current_flags() {
    let err = expect_err(parse_with_modules(
        &[
            (
                "base.tsg",
                r#"
                  let shared = import("shared.tsg")
                  grammar { language: "base", flags: { enabled: ["F"] } }
                  rule base_rule { shared_rule }
                  "#,
            ),
            ("shared.tsg", "#[cfg(F)]\nrule shared_rule { \"s\" }"),
        ],
        r#"
          let base = inherit("base.tsg")
          let shared = import("shared.tsg")
          grammar { language: "root", inherits: base }
          rule program { "p" }
          "#,
    ));

    let inner = *assert_err!(err, Module).inner;
    let error = assert_err!(inner, Cfg);
    assert_eq!(error.kind, CfgErrorKind::FlagUnknown("F".into()));
}

#[test]
fn cfg_base_flag_is_visible_to_its_import() {
    let mut grammar = parse_with_modules(
        &[
            (
                "base.tsg",
                r#"
                  let helper = import("helper.tsg")
                  grammar { language: "base", flags: { enabled: ["F"] } }
                  rule base_rule { helper::gated() }
                  "#,
            ),
            (
                "helper.tsg",
                r#"macro gated() rule_t { choice("a", #[cfg(F)] "b") }"#,
            ),
        ],
        r#"
          let base = inherit("base.tsg")
          grammar { language: "root", inherits: base }
          rule program { "p" }
          "#,
    )
    .unwrap();

    let actual = find_rule(&grammar, "base_rule");
    let expected = {
        let pool = &mut grammar.pool;
        r_choice!(pool, [r_str!(pool, "a"), r_str!(pool, "b")])
    };
    assert_rule_eq(&grammar.pool, actual, expected);
}

#[test]
fn cfg_disabled_nested_import_does_not_merge_rules() {
    let g = parse_with_modules(
        &[("helper.tsg", "rule helper_only { \"h\" }\n")],
        r#"
        grammar {
            language: "t",
            flags: { disabled: ["EXT"] },
            extras: [ #[cfg(EXT)] import("helper.tsg") ],
        }
        rule program { "x" }
    "#,
    )
    .unwrap();
    assert!(
        !g.variables
            .iter()
            .any(|v| g.pool.resolve(v.name) == "helper_only"),
        "cfg-disabled import's rule leaked into the grammar"
    );
}

#[test]
fn cfg_disabled_symref_not_validated() {
    // Filtering a rule set must also remove its stored symbol references.
    let g = dsl(r#"
        rules m(s: str_t) {
            rule program { choice(#[cfg(X)] @concat("missing_", s), "ok") }
        }
        grammar { language: "t", flags: { disabled: ["X"] } }
        @m("rule")
    "#);
    assert!(
        g.variables
            .iter()
            .any(|v| g.pool.resolve(v.name) == "program")
    );
}

find_rule_tests! {
    cfg_choice_member_disabled {
        r#"
        grammar { language: "t", flags: { disabled: ["GFM"] } }
        rule program { choice("a", #[cfg(GFM)] "b", "c") }
    "#,
        "program",
        |p| r_choice!(p, [r_str!(p, "a"), r_str!(p, "c")])
    }
    cfg_concat_member_disabled {
        r#"
        grammar { language: "t", flags: { disabled: ["GFM"] } }
        rule program { concat("a", #[cfg(GFM)] "b", "c") }
    "#,
        "program",
        |p| r_str!(p, "ac")
    }
    cfg_nested_inner_off {
        r#"
        grammar { language: "t", flags: { enabled: ["A"], disabled: ["B"] } }
        rule program { choice("x", #[cfg(A)] #[cfg(B)] "y", "z") }
    "#,
        "program",
        |p| r_choice!(p, [r_str!(p, "x"), r_str!(p, "z")])
    }
}

rule_names_tests! {
    cfg_rule_def_enabled {
        r#"
        grammar { language: "t", flags: { enabled: ["GFM"] } }
        rule program { strikethrough }
        #[cfg(GFM)]
        rule strikethrough { "~~" }
    "#,
        vec!["program", "strikethrough"]
    }
    cfg_active_let_keeps_type_annotation {
        // Unwrapping an active cfg must preserve the declaration's annotation.
        r#"
        grammar { language: "test", flags: { enabled: ["X"] } }
        #[cfg(X)] let x: list_t<str_t> = []
        rule foo { "x" }
    "#,
        vec!["foo"]
    }
    cfg_enabled_definition_with_expect_compiles {
        r#"
        grammar { language: "t", flags: { enabled: ["GFM"] } }
        expect strikethrough
        rule program { strikethrough }
        #[cfg(GFM)]
        rule strikethrough { "~~" }
    "#,
        vec!["program", "strikethrough"]
    }
    cfg_disabled_expect_and_user_compiles {
        // Filtering must remove the forward declaration and its use together.
        r#"
        grammar { language: "t", flags: { disabled: ["GFM"] } }
        #[cfg(GFM)] expect _ext
        #[cfg(GFM)] rule uses_ext { _ext }
        rule program { "x" }
    "#,
        vec!["program"]
    }
    cfg_rule_in_rule_set_disabled {
        r#"
        grammar { language: "test", flags: { disabled: ["X"] } }
        rule program { a }
        rules pair() {
            rule a { "x" }
            #[cfg(X)]
            rule b { "y" }
        }
        @pair()
    "#,
        vec!["program", "a"]
    }
    cfg_rule_set_fully_gated_call_is_noop {
        // Expanding an empty rule set contributes no rules.
        r#"
        grammar { language: "test", flags: { disabled: ["X"] } }
        rule program { "p" }
        rules extras() {
            #[cfg(X)]
            rule a { "x" }
        }
        @extras()
    "#,
        vec!["program"]
    }
}

error_tests! { Cfg {
    cfg_unknown_flag_errors {
        r#"
        grammar { language: "t", flags: { enabled: ["GFM"] } }
        rule program { choice("a", #[cfg(TYPO)] "b") }
    "#,
        CfgErrorKind::FlagUnknown("TYPO".into())
    }
    cfg_flags_not_object_errors {
        r#"
        grammar { language: "t", flags: ["X"] }
        rule program { "x" }
    "#,
        CfgErrorKind::FlagsNotObject
    }
    cfg_flags_not_list_errors {
        r#"
        grammar { language: "t", flags: { enabled: "X" } }
        rule program { "x" }
    "#,
        CfgErrorKind::FlagsNotList
    }
    cfg_flags_unknown_key_errors {
        r#"
        grammar { language: "t", flags: { active: ["GFM"] } }
        rule program { "x" }
    "#,
        CfgErrorKind::FlagsUnknownKey("active".into())
    }
    cfg_inside_flags_errors {
        r#"
        grammar { language: "t", flags: { enabled: ["X", #[cfg(X)] "FOO"] } }
        rule program { "x" }
    "#,
        CfgErrorKind::InsideFlags
    }
    cfg_flags_non_string_errors {
        r#"
        grammar { language: "t", flags: { enabled: [GFM] } }
        rule program { "x" }
    "#,
        CfgErrorKind::FlagsNonLiteral
    }
}}

error_tests! { Resolve {
    cfg_rule_in_rule_set_dropped_reference_is_undefined {
        r#"
        grammar { language: "test", flags: { disabled: ["X"] } }
        rules pair() {
            rule a { b }
            #[cfg(X)]
            rule b { "y" }
        }
        @pair()
    "#,
        ResolveErrorKind::UnknownIdentifier("b".into())
    }
}}

error_tests! { Type {
    cfg_flags_duplicate_key_errors {
        // Flags bypass generic object typechecking.
        r#"
        grammar { language: "t", flags: { enabled: ["A"], enabled: ["B"] } }
        rule program { "x" }
    "#,
        TypeErrorKind::DuplicateObjectKey("enabled".into())
    }
}}

error_tests! { match Lower {
    cfg_disabled_definition_with_expect_is_undefined_symbol {
        // The forward declaration defers this error until lowering.
        r#"
        grammar { language: "t", flags: { disabled: ["GFM"] } }
        expect strikethrough
        rule program { strikethrough }
        #[cfg(GFM)]
        rule strikethrough { "~~" }
    "#,
        LowerErrorKind::UndefinedSymbols(names) if *names == ["strikethrough"]
    }
}}

error_tests! { Parse {
    cfg_on_grammar_block_is_rejected {
        r#"
        #[cfg(X)] grammar { language: "t", flags: { enabled: ["X"] } }
        rule program { "x" }
    "#,
        ParseErrorKind::CfgOnGrammarBlock
    }
}}
