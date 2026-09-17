use super::*;

rule_tests! {
    seq_and_choice {
        r#"grammar { language: "test" } rule program { seq(choice("a", "b"), "c") }"#,
        |p| r_seq!(p, [r_choice!(p, [r_str!(p, "a"), r_str!(p, "b")]), r_str!(p, "c")])
    }
    optional_of_choice_flattens {
        r#"grammar { language: "test" } rule program { optional(choice("a", "b")) }"#,
        |p| r_choice!(p, [r_str!(p, "a"), r_str!(p, "b"), r_blank!(p)])
    }
    repeat1 {
        r#"grammar { language: "test" } rule program { repeat1("x") }"#,
        |p| r_repeat!(p, r_str!(p, "x"))
    }
    optional_combinator {
        r#"grammar { language: "test" } rule program { optional("x") }"#,
        |p| r_choice!(p, [r_str!(p, "x"), r_blank!(p)])
    }
    blank_combinator {
        r#"grammar { language: "test" } rule program { blank() }"#,
        |p| r_blank!(p)
    }
    token_combinator {
        r#"grammar { language: "test" } rule program { token(seq("a", "b")) }"#,
        |p| r_token!(p, r_seq!(p, [r_str!(p, "a"), r_str!(p, "b")]))
    }
    token_immediate_combinator {
        r#"grammar { language: "test" } rule program { token_immediate("x") }"#,
        |p| r_immediate_token!(p, r_str!(p, "x"))
    }
    field_combinator {
        r#"grammar { language: "test" }
        rule program { field(name, "x") }
        rule name { "n" }"#,
        |p| r_field!(p, "name", r_str!(p, "x"))
    }
    alias_with_string {
        r#"grammar { language: "test" }
        rule program { alias(identifier, "id") }
        rule identifier { regexp("[a-z]+") }"#,
        |p| r_alias!(p, "id", false, r_sym!(p, "identifier"))
    }
    alias_with_named_rule {
        r#"grammar { language: "test" }
        rule program { alias(_impl, block) }
        rule _impl { "impl" }
        rule block { "{}" }"#,
        |p| r_alias!(p, "block", true, r_sym!(p, "_impl"))
    }
    alias_with_variable_target {
        r#"grammar { language: "test" }
        macro make_alias(target: rule_t) rule_t { alias("x", target) }
        rule program { make_alias(some_rule) }
        rule some_rule { "y" }"#,
        |p| r_alias!(p, "some_rule", true, r_str!(p, "x"))
    }
    alias_with_let_string_target {
        // A let-bound string alias target resolves to the let's value (unnamed
        // alias "renamed"), not a named rule "FOO" - matches grammar.js.
        r#"grammar { language: "test" }
        let FOO = "renamed"
        rule program { alias(identifier, FOO) }
        rule identifier { regexp("[a-z]+") }"#,
        |p| r_alias!(p, "renamed", false, r_sym!(p, "identifier"))
    }
    alias_with_forward_let_target {
        // Same, but the `let` is defined after the alias use; lets resolve
        // regardless of order, so it stays an unnamed alias to the let's value.
        r#"grammar { language: "test" }
        rule program { alias(identifier, FOO) }
        rule identifier { regexp("[a-z]+") }
        let FOO = "renamed""#,
        |p| r_alias!(p, "renamed", false, r_sym!(p, "identifier"))
    }
    prec_default {
        r#"grammar { language: "test" } rule program { prec(1, "x") }"#,
        |p| r_prec!(p, Precedence::Integer(1), r_str!(p, "x"))
    }
    prec_left {
        r#"grammar { language: "test" } rule program { prec_left(2, "x") }"#,
        |p| r_prec_left!(p, Precedence::Integer(2), r_str!(p, "x"))
    }
    prec_right {
        r#"grammar { language: "test" } rule program { prec_right(3, "x") }"#,
        |p| r_prec_right!(p, Precedence::Integer(3), r_str!(p, "x"))
    }
    prec_dynamic {
        r#"grammar { language: "test" } rule program { prec_dynamic(4, "x") }"#,
        |p| r_prec_dynamic!(p, 4, r_str!(p, "x"))
    }
    prec_dynamic_negative {
        r#"grammar { language: "test" } rule program { prec_dynamic(-1, "x") }"#,
        |p| r_prec_dynamic!(p, -1, r_str!(p, "x"))
    }
    prec_with_string_name {
        r#"grammar { language: "test" } rule program { prec_left("assign", "x") }"#,
        |p| {
            let name = p.intern("assign");
            r_prec_left!(p, Precedence::Name(name), r_str!(p, "x"))
        }
    }
    rule_reference_in_body {
        r#"grammar { language: "test" }
        rule program { other }
        rule other { "x" }"#,
        |p| r_sym!(p, "other")
    }
    for_inline_in_seq {
        r#"grammar { language: "test" }
        rule program {
            seq("start", for (kw: str_t) in ["a", "b"] { kw }, "end")
        }"#,
        |p| r_seq!(p, [
            r_str!(p, "start"),
            r_str!(p, "a"),
            r_str!(p, "b"),
            r_str!(p, "end"),
        ])
    }
    raw_ident_as_rule_reference {
        // r#let escapes the `let` keyword so it can name a rule.
        r#"grammar { language: "test" }
        rule program { r#let }
        rule r#let { "in" }"#,
        |p| r_sym!(p, "let")
    }
    string_hex_escape {
        // \xHH (ASCII range) decodes to the literal byte. Matches perl's __DATA__ ctrl-D usage.
        "grammar { language: \"test\" } rule program { \"a\\x04b\" }",
        |p| r_str!(p, "a\x04b")
    }
    string_unicode_escape_4digit {
        // \uHHHH (4 hex) decodes to UTF-8.
        r#"grammar { language: "test" } rule program { "\u00A0" }"#,
        |p| r_str!(p, "\u{00A0}")
    }
    string_unicode_escape_braced {
        // \u{H..H} (1-6 hex in braces) decodes to UTF-8, allows non-BMP.
        r#"grammar { language: "test" } rule program { "\u{1F389}" }"#,
        |p| r_str!(p, "\u{1F389}")
    }
    string_unicode_escape_max {
        // \u{10FFFF} is the maximum valid scalar value (the accept edge of the range check).
        r#"grammar { language: "test" } rule program { "\u{10FFFF}" }"#,
        |p| r_str!(p, "\u{10FFFF}")
    }
    string_hex_escape_max_ascii {
        // \x7F is the maximum allowed \x value (the accept edge of the <= 0x7F check).
        r#"grammar { language: "test" } rule program { "\x7F" }"#,
        |p| r_str!(p, "\x7f")
    }
    string_simple_escapes {
        // \r, \0, and \" decode to CR, NUL, and a double quote.
        r#"grammar { language: "test" } rule program { "a\rb\0c\"d" }"#,
        |p| r_str!(p, "a\rb\0c\"d")
    }
    int_arith_add_literals {
        r#"grammar { language: "test" } rule program { prec(1 + 2, "x") }"#,
        |p| r_prec!(p, Precedence::Integer(3), r_str!(p, "x"))
    }
    int_arith_sub_literals {
        r#"grammar { language: "test" } rule program { prec(10 - 3, "x") }"#,
        |p| r_prec!(p, Precedence::Integer(7), r_str!(p, "x"))
    }
    int_arith_chained {
        // Left-associative: 1 + 2 - 5 + 10 = 8.
        r#"grammar { language: "test" } rule program { prec(1 + 2 - 5 + 10, "x") }"#,
        |p| r_prec!(p, Precedence::Integer(8), r_str!(p, "x"))
    }
    int_arith_named_plus_literal {
        // Named-int + literal: PREC.foo = 5, +1 = 6.
        r#"let PREC = { foo: 5 } grammar { language: "test" } rule program { prec(PREC.foo + 1, "x") }"#,
        |p| r_prec!(p, Precedence::Integer(6), r_str!(p, "x"))
    }
    int_arith_two_named {
        // Both sides named: PREC.a + PREC.b = 8.
        r#"let PREC = { a: 5, b: 3 } grammar { language: "test" } rule program { prec(PREC.a + PREC.b, "x") }"#,
        |p| r_prec!(p, Precedence::Integer(8), r_str!(p, "x"))
    }
    int_arith_in_let_binding {
        // Arithmetic in a let RHS is folded at bind time.
        r#"let PREC = { base: 10 } let X = PREC.base + 1 grammar { language: "test" } rule program { prec(X, "x") }"#,
        |p| r_prec!(p, Precedence::Integer(11), r_str!(p, "x"))
    }
    int_arith_with_unary_neg {
        // -PREC.foo combined with new + arithmetic: -5 + 10 = 5.
        r#"let PREC = { foo: 5 } grammar { language: "test" } rule program { prec(-PREC.foo + 10, "x") }"#,
        |p| r_prec!(p, Precedence::Integer(5), r_str!(p, "x"))
    }
    raw_ident_keyword_collisions {
        // Shadowing builtin combinator/keyword names: r#field, r#import, r#alias.
        // Each is a normal rule whose grammar.json key is the bare keyword.
        r#"grammar { language: "test" }
        rule program { seq(r#field, r#import, r#alias) }
        rule r#field { "f" }
        rule r#import { "i" }
        rule r#alias { "a" }"#,
        |p| r_seq!(p, [
            r_sym!(p, "field"),
            r_sym!(p, "import"),
            r_sym!(p, "alias"),
        ])
    }
    regexp_combinator {
        r#"grammar { language: "test" } rule program { regexp("[a-z]+") }"#,
        |p| r_pattern!(p, "[a-z]+")
    }
    regexp_with_flags {
        r#"grammar { language: "test" } rule program { regexp("[a-z]+", "i") }"#,
        |p| r_pattern!(p, "[a-z]+", "i")
    }
    concat_combinator {
        r#"grammar { language: "test" } rule program { regexp(concat("[", "a-z", "]+")) }"#,
        |p| r_pattern!(p, "[a-z]+")
    }
    raw_ident_as_let_binding_name {
        // `r#name` works in let-binding position when the bare name collides
        // with a DSL keyword.
        r#"grammar { language: "test" }
        let r#for: str_t = "x"
        rule program { r#for }"#,
        |p| r_str!(p, "x")
    }
    raw_ident_as_object_key {
        // `r#name` works as an object literal key when the bare name collides
        // with a DSL keyword.
        r#"grammar { language: "test" }
        let cfg = { r#for: 1, r#in: 2 }
        rule program { prec(cfg.r#for, "x") }"#,
        |p| r_prec!(p, Precedence::Integer(1), r_str!(p, "x"))
    }
    object_key_accepts_contextual_keyword {
        // An object-literal key is a name, so it accepts contextual keywords like
        // `field`, the same as the field-access member position already does.
        r#"
        let x = { field: "y" }
        grammar { language: "test" }
        rule program { x.field }
        "#,
        |p| r_str!(p, "y")
    }
}

#[test]
fn raw_ident_emits_bare_name_in_grammar_json() {
    let g = dsl(r#"grammar { language: "test" }
        rule program { r#let }
        rule r#let { "in" }"#);
    // grammar.json rule names must match the bare identifier, not `r#let`.
    assert_eq!(rule_names(&g), vec!["program", "let"]);
}

#[test]
fn prec_inside_token_immediate() {
    let g = dsl(r#"
        grammar { language: "test" }
        rule program { token_immediate(prec(1, regexp("[a-z]+"))) }
    "#);
    let root = g.pool.node(g.variables[0].root);
    let Rule::Metadata { params, .. } = root else {
        panic!("expected Metadata, got {root:?}");
    };
    let params = g.pool.params(params);
    assert_eq!(params.precedence, Precedence::Integer(1));
    assert!(params.is_token && params.is_main_token);
}

#[test]
fn reserved_combinator() {
    let mut g = dsl(r#"grammar {
        language: "test", reserved: { default: [identifier] },
    }
    rule program { reserved("default", identifier) }
    rule identifier { regexp("[a-z]+") }"#);
    let actual = g.variables[0].root;
    let expected = {
        let p = &mut g.pool;
        r_reserved!(p, "default", r_sym!(p, "identifier"))
    };
    assert_rule_eq(&g.pool, actual, expected);
}

#[test]
fn reserved_multiple_sets() {
    let g = dsl(r#"grammar {
        language: "test",
        reserved: { global: ["if", "else", "for"], properties: ["get", "set"] },
    }
    rule program { reserved("global", regexp("[a-z]+")) }"#);
    assert_eq!(g.reserved_sets.len(), 2);
    assert_eq!(g.pool.resolve(g.reserved_sets[0].name), "global");
    assert_eq!(g.reserved_sets[0].roots.len(), 3);
    assert_eq!(g.pool.resolve(g.reserved_sets[1].name), "properties");
    assert_eq!(g.reserved_sets[1].roots.len(), 2);
}

#[test]
fn reserved_inherited() {
    // A child with no `reserved` inherits the base's sets in base order (default
    // set preserved), with no explicit grammar_config re-import needed.
    let mut g = dsl(r#"
        let base = inherit("inherit_base/grammar_with_reserved.tsg")
        grammar { language: "derived", inherits: base }
    "#);
    assert_eq!(g.reserved_sets.len(), 2);
    assert_eq!(g.pool.resolve(g.reserved_sets[0].name), "global");
    assert_eq!(g.pool.resolve(g.reserved_sets[1].name), "properties");

    let global = g.reserved_sets[0].roots.clone();
    let properties = g.reserved_sets[1].roots.clone();
    let (expected_global, expected_properties) = {
        let p = &mut g.pool;
        (
            vec![r_str!(p, "if"), r_str!(p, "else"), r_str!(p, "for")],
            vec![r_str!(p, "get"), r_str!(p, "set")],
        )
    };
    assert_rules_eq(&g.pool, &global, &expected_global);
    assert_rules_eq(&g.pool, &properties, &expected_properties);
}

#[test]
fn reserved_child_merges_with_base() {
    // The child adds a set and overrides one: base order is preserved (global
    // stays default), overridden sets keep position, new sets append.
    let mut g = dsl(r#"
        let base = inherit("inherit_base/grammar_with_reserved.tsg")
        grammar {
            language: "derived",
            inherits: base,
            reserved: { global: ["if"], extra: ["new"] },
        }
    "#);
    assert_eq!(g.reserved_sets.len(), 3);
    // Base "global" stays first (default), with the child's overriding words.
    assert_eq!(g.pool.resolve(g.reserved_sets[0].name), "global");
    // Base "properties" kept (not redefined by the child).
    assert_eq!(g.pool.resolve(g.reserved_sets[1].name), "properties");
    // Child's new set appended.
    assert_eq!(g.pool.resolve(g.reserved_sets[2].name), "extra");

    let global = g.reserved_sets[0].roots.clone();
    let expected = {
        let p = &mut g.pool;
        vec![r_str!(p, "if")]
    };
    assert_rules_eq(&g.pool, &global, &expected);
}

#[test]
fn reserved_empty_inherited() {
    // A base with no reserved contributes none; the child inherits an empty set.
    let g = dsl(r#"
        let base = inherit("inherit_base/grammar.tsg")
        grammar { language: "derived", inherits: base }
    "#);
    assert!(g.reserved_sets.is_empty());
}

#[test]
fn trailing_comma_in_builtins() {
    macro_rules! g {
        ($expr:expr) => {
            concat!(r#"grammar { language: "test" } rule foo { "#, $expr, " }")
        };
    }
    for src in [
        g!(r#"repeat("x",)"#),
        g!(r#"repeat1("x",)"#),
        g!(r#"optional("x",)"#),
        g!(r#"token("x",)"#),
        g!(r#"token_immediate("x",)"#),
        g!(r#"prec(1, "x",)"#),
        g!(r#"prec_left(1, "x",)"#),
        g!(r#"prec_right(1, "x",)"#),
        g!(r#"prec_dynamic(1, "x",)"#),
        g!(r#"field(name, "x",)"#),
        g!(r#"alias("x", foo,)"#),
        g!(r#"reserved("ctx", "x",)"#),
        g!(r#"regexp("pat",)"#),
        g!(r#"regexp("pat", "flags",)"#),
    ] {
        dsl(src);
    }
    dsl(r#"grammar { language: "test", extras: append(["x"], ["y"],) } rule foo { "x" }"#);
}
