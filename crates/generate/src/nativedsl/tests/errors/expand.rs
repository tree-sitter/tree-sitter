use super::super::*;

error_tests! { Parse {
    error_rule_set_body_requires_rule_decl {
        r#"grammar { language: "test" } rules bad() { let x = 1 } rule program { "x" }"#,
        ParseErrorKind::RuleSetBodyRequiresRuleDecl
    }
}}

error_tests! { Expand {
    error_unknown_top_level_macro {
        r#"grammar { language: "test" } rule program { "x" } @not_defined()"#,
        ExpandErrorKind::UnknownMacro("not_defined".into())
    }
    // A cfg-disabled rule-set macro must not stay callable: apply_cfg prunes it
    // from macro_index, so @foo() fails like a cfg-disabled expression-macro ref
    // (it once expanded a never-resolved body or silently emitted its rules).
    error_cfg_disabled_ruleset_macro_ident_body {
        r#"#[cfg(X)]
           rules foo() { rule a { b } }
           grammar { language: "t", flags: { disabled: ["X"] } }
           rule b { "b" }
           @foo()"#,
        ExpandErrorKind::UnknownMacro("foo".into())
    }
    error_cfg_disabled_ruleset_macro_self_contained_body {
        r#"#[cfg(X)]
           rules foo() { rule a { "x" } }
           grammar { language: "t", flags: { disabled: ["X"] } }
           rule program { "p" }
           @foo()"#,
        ExpandErrorKind::UnknownMacro("foo".into())
    }
    error_expression_macro_called_at_top_level {
        r#"macro expr_only() rule_t { "x" }
           grammar { language: "test" }
           rule program { "y" }
           @expr_only()"#,
        ExpandErrorKind::ExpressionMacroAsItem("expr_only".into())
    }
    error_arg_count_mismatch {
        r#"rules one(s: str_t) { rule program { s } }
           grammar { language: "test" }
           @one("a", "b")"#,
        ExpandErrorKind::ArgCountMismatch {
            macro_name: "one".into(),
            expected: 1,
            got: 2,
        }
    }
    error_computed_name_not_identifier {
        r#"rules bad(s: str_t) { rule @concat("with space", s) { "x" } }
           grammar { language: "test" }
           @bad("foo")"#,
        ExpandErrorKind::InvalidRuleName("with spacefoo".into())
    }
    error_computed_name_non_string_node {
        r#"rules bad() { rule @42 { "x" } }
           grammar { language: "test" }
           @bad()"#,
        ExpandErrorKind::NonStringInName
    }
    error_computed_name_empty_string {
        r#"rules bad() { rule @concat("", "") { "x" } }
           grammar { language: "test" }
           @bad()"#,
        ExpandErrorKind::InvalidRuleName(String::new())
    }
}}

error_tests! { Type {
    error_rule_set_macro_in_expression_context {
        r#"rules rs() { rule a { "x" } }
           grammar { language: "test" }
           rule program { rs() }"#,
        TypeErrorKind::RuleSetMacroInExpressionContext("rs".into())
    }
    error_computed_name_expr_not_str {
        // Passing an int_t param into a name position fails at macro
        // definition time, before any call site exercises it.
        r#"rules bad(n: int_t) { rule @n { "x" } }
           grammar { language: "test" }
           rule program { "y" }"#,
        TypeErrorKind::TypeMismatch {
            expected: Ty::STR,
            got: Ty::INT,
        }
    }
    error_symref_inner_not_str {
        r#"rules bad(n: int_t) { rule a { @n } }
           grammar { language: "test" }
           rule program { "y" }"#,
        TypeErrorKind::TypeMismatch {
            expected: Ty::STR,
            got: Ty::INT,
        }
    }
}}

error_tests! { Resolve {
    error_symref_to_unknown_rule {
        r#"rules bad(s: str_t) { rule a { @concat("no_", s) } }
           grammar { language: "test", start: a }
           @bad("such")"#,
        ResolveErrorKind::UnknownIdentifier("no_such".into())
    }
    error_computed_name_collides_with_static_rule {
        r#"rules emit() { rule program { "x" } }
           grammar { language: "test", start: program }
           rule program { "y" }
           @emit()"#,
        ResolveErrorKind::DuplicateDeclaration("program".into())
    }
}}
