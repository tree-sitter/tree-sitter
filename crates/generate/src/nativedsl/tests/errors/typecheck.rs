use super::super::*;

error_tests! { Type {
    error_library_macro_param_rejected {
        r#"grammar { language: "test" } macro f(m: library_t) rule_t { "x" } rule program { "x" }"#,
        TypeErrorKind::ModuleTypeNotAllowed
    }
    error_library_macro_return_rejected {
        r#"grammar { language: "test" } macro g() library_t { "x" } rule program { "x" }"#,
        TypeErrorKind::ModuleTypeNotAllowed
    }
    error_duplicate_fn_param {
        r#"grammar { language: "test" }
        macro f(x: rule_t, x: str_t) rule_t { x }
        rule program { f("a") }"#,
        TypeErrorKind::DuplicateParameter("x".into())
    }
    error_duplicate_for_binding {
        r#"grammar { language: "test" }
        rule program { choice(for (x: str_t, x: int_t) in [("a", 1)] { x }) }"#,
        TypeErrorKind::DuplicateBinding("x".into())
    }
    error_duplicate_object_key {
        r#"grammar { language: "test" } let x = { a: 1, b: 2, a: 3 } rule foo { "x" }"#,
        TypeErrorKind::DuplicateObjectKey("a".into())
    }
    error_object_field_type_mismatch {
        r#"grammar { language: "test" }
        let x = { a: program, b: 1 }
        rule program { "p" }"#,
        TypeErrorKind::ObjectFieldTypeMismatch { first: Ty::RULE, got: Ty::INT }
    }
    error_empty_for_bindings {
        r#"grammar { language: "test" }
        rule program { choice(for () in [program] { "x" }) }"#,
        TypeErrorKind::EmptyForBindings
    }
    error_type_mismatch_fn_args {
        r#"grammar { language: "test" }
        macro needs_int(x: int_t) rule_t { prec(x, "a") }
        rule program { needs_int("not_an_int") }"#,
        TypeErrorKind::TypeMismatch { expected: Ty::INT, got: Ty::STR }
    }
    error_computed_rule_name_not_string {
        // `rule @<expr>` computes the name from a value that must be a string; a
        // rule reference resolves but is the wrong type (a value, not a decl).
        r#"grammar { language: "test" }
        rules r() { rule @program { "x" } }
        rule program { "x" }"#,
        TypeErrorKind::TypeMismatch { expected: Ty::STR, got: Ty::RULE }
    }
    error_for_binding_count_mismatch {
        r#"grammar { language: "test" }
        rule bad { choice(for (a: str_t, b: str_t, c: str_t) in [("x", "y")] { a }) }"#,
        TypeErrorKind::ForBindingCountMismatch { bindings: 3, tuple_elements: 2 }
    }
    error_append_non_list_arg {
        r#"grammar { language: "test" }
        let c = append("x", ["y"])
        rule program { "x" }"#,
        TypeErrorKind::AppendRequiresList(Ty::STR)
    }
    error_append_non_list {
        r#"grammar { language: "test" }
        let a: str_t = "x"
        let b: list_t<str_t> = ["y"]
        let c = append(a, b)
        rule program { "x" }"#,
        TypeErrorKind::AppendRequiresList(Ty::STR)
    }
    error_let_type_annotation_mismatch {
        r#"grammar { language: "test" }
        let X: int_t = "not_an_int"
        rule program { "x" }"#,
        TypeErrorKind::TypeMismatch { expected: Ty::INT, got: Ty::STR }
    }
    error_library_t_annotation_mismatch {
        r#"grammar { language: "test" }
        let X: library_t = "not_a_module"
        rule program { "x" }"#,
        TypeErrorKind::TypeMismatch { expected: Ty::ANY_LIBRARY, got: Ty::STR }
    }
    error_inherits_without_inherit {
        r#"grammar { language: "test", inherits: "not_inherit" }
        rule program { "x" }"#,
        TypeErrorKind::InheritsMustReferenceBase
    }
    error_inherits_not_bound_to_inherit {
        r#"let base = inherit("inherit_base/grammar.tsg")
        grammar { language: "derived", inherits: some_rule }
        rule some_rule { "x" }"#,
        TypeErrorKind::InheritsMustReferenceBase
    }
    error_inherits_references_ancestor_of_base {
        r#"let parent = inherit("inherit_base/nested_parent.tsg")
        grammar { language: "child", inherits: parent::gp }
        rule child_rule { "c" }"#,
        TypeErrorKind::InheritsMustReferenceBase
    }
    error_rule_called_as_function {
        r#"grammar { language: "test", word: ident }
        rule ident { regexp("[a-z]+") }
        rule program { ident("default", regexp("[a-z]+")) }"#,
        TypeErrorKind::UndefinedMacro("ident".into())
    }
    error_wrong_arg_count {
        r#"grammar { language: "test" }
        macro one_arg(x: rule_t) rule_t { x }
        rule program { one_arg("a", "b") }"#,
        TypeErrorKind::ArgCountMismatch { macro_name: "one_arg".into(), expected: 1, got: 2 }
    }
    error_member_access_requires_module {
        r#"grammar { language: "test" }
        let obj = { x: 1 }
        rule program { obj::x }"#,
        TypeErrorKind::MemberAccessRequiresModule(Ty::Data(DataTy::Object(InnerTy::Scalar(
            ScalarTy::Int,
        ))))
    }
    error_field_access_on_non_object {
        r#"grammar { language: "test" }
        let x: int_t = 5
        rule program { prec(x.foo, "a") }"#,
        TypeErrorKind::ConstraintMismatch {
            expected: Constraint::AnyObject,
            got: Ty::INT,
        }
    }
    error_field_not_found {
        r#"grammar { language: "test" }
        let x = { a: 1 }
        rule program { prec(x.b, "a") }"#,
        TypeErrorKind::FieldNotFound { field: "b".into(), available: vec!["a".into()] }
    }
    error_word_non_rule_var {
        r#"let my_word = 42
        grammar { language: "test", word: my_word }
        rule program { "y" }"#,
        TypeErrorKind::TypeMismatch { expected: Ty::RULE, got: Ty::INT }
    }
    error_for_requires_list {
        r#"grammar { language: "test" }
        let x: int_t = 5
        rule program { choice(for (v: int_t) in x { prec(v, "a") }) }"#,
        TypeErrorKind::ForRequiresList(Ty::INT)
    }
    error_rule_body_not_rule_typed {
        r#"grammar { language: "test" }
        rule program { 42 }"#,
        TypeErrorKind::TypeMismatch { expected: Ty::RULE, got: Ty::INT }
    }
    error_fn_return_type_mismatch {
        r#"grammar { language: "test" }
        macro bad(x: rule_t) int_t { x }
        rule program { "x" }"#,
        TypeErrorKind::TypeMismatch { expected: Ty::INT, got: Ty::RULE }
    }
    error_prec_value_not_int_or_str {
        r#"grammar { language: "test" }
        rule program { prec(identifier, "x") }
        rule identifier { "id" }"#,
        TypeErrorKind::ConstraintMismatch {
            expected: Constraint::IntOrStr,
            got: Ty::RULE,
        }
    }
    error_list_inconsistent_types {
        r#"grammar { language: "test" }
        let x = ["a", 1]
        rule program { "x" }"#,
        TypeErrorKind::ListElementTypeMismatch { first: Ty::STR, got: Ty::INT }
    }
    error_expected_rule_name_in_word {
        r#"grammar { language: "test", word: "not_a_name" }
        rule program { "x" }"#,
        TypeErrorKind::ExpectedRuleName
    }
    error_let_rhs_for_loop_rejected {
        r#"grammar { language: "test" }
        let foo = for (k: str_t) in ["a", "b"] { k }
        rule program { seq(foo) }"#,
        TypeErrorKind::BoundForLoop
    }
    error_tuple_arity_too_small {
        r#"grammar { language: "test" }
        let x = ("a")
        rule program { "x" }"#,
        TypeErrorKind::TupleArityInvalid(1)
    }
    error_tuple_arity_too_large {
        r#"grammar { language: "test" }
        let x = ("a", "b", "c", "d", "e", "f", "g", "h", "i")
        rule program { "x" }"#,
        TypeErrorKind::TupleArityInvalid(9)
    }
    error_tuple_element_not_scalar {
        r#"grammar { language: "test" }
        let x = (["a"], "b")
        rule program { "x" }"#,
        TypeErrorKind::TupleElementNotScalar(Ty::Data(DataTy::List(ElemTy::Scalar(ScalarTy::Str))))
    }
    error_tuple_used_as_rule {
        r#"grammar { language: "test" }
        rule program { ("a", "b") }"#,
        TypeErrorKind::TypeMismatch {
            expected: Ty::RULE,
            got: Ty::Data(DataTy::Tuple(TupleSig::new(&[ScalarTy::Str, ScalarTy::Str]).unwrap())),
        }
    }
    error_for_multi_binding_non_scalar {
        r#"grammar { language: "test" }
        rule bad { choice(for (a: list_t<rule_t>, b: rule_t) in [] { b }) }"#,
        TypeErrorKind::TupleElementNotScalar(Ty::LIST_RULE)
    }
    error_tuple_rows_differing_arity {
        r#"grammar { language: "test" }
        let xs = [("a", 1), ("b", 2, 3)]
        rule program { "x" }"#,
        TypeErrorKind::ListElementTypeMismatch {
            first: Ty::Data(DataTy::Tuple(TupleSig::new(&[ScalarTy::Str, ScalarTy::Int]).unwrap())),
            got: Ty::Data(DataTy::Tuple(
                TupleSig::new(&[ScalarTy::Str, ScalarTy::Int, ScalarTy::Int]).unwrap(),
            )),
        }
    }
    error_conflicts_rejects_non_name {
        r#"grammar {
            language: "test",
            conflicts: [[repeat("x")]],
        }
        rule program { "x" }"#,
        TypeErrorKind::ExpectedRuleName
    }
    error_qualified_access_in_name_ref_config {
        r#"let base = inherit("inherit_base/grammar.tsg")
        grammar { language: "derived", inherits: base, inline: [base::_inline_rule] }"#,
        TypeErrorKind::ExpectedRuleName
    }
    error_int_literal_assigned_to_list_rule {
        r#"grammar { language: "test" }
        let x: list_t<rule_t> = [1, 2]
        rule program { "x" }"#,
        TypeErrorKind::TypeMismatch { expected: Ty::RULE, got: Ty::INT }
    }
    error_flat_list_assigned_to_list_list_rule {
        r#"grammar { language: "test" }
        let x: list_t<list_t<rule_t>> = [a, b]
        rule program { "x" }
        rule a { "a" }
        rule b { "b" }"#,
        TypeErrorKind::TypeMismatch { expected: Ty::LIST_RULE, got: Ty::RULE }
    }
    error_for_bindings_not_tuple {
        r#"grammar { language: "test" }
        let items: list_t<rule_t> = [identifier]
        rule identifier { regexp("[a-z]+") }
        rule program { seq(for (a: rule_t, b: rule_t) in items { a }) }"#,
        TypeErrorKind::ForRequiresTuples
    }
    error_invalid_object_value {
        r#"grammar { language: "test" }
        let inner = { a: 1 }
        let x = { nested: inner }
        rule program { "x" }"#,
        TypeErrorKind::InvalidObjectValue(Ty::Data(DataTy::Object(InnerTy::Scalar(ScalarTy::Int))))
    }
    error_invalid_list_element {
        r#"grammar { language: "test" }
        let inner: list_t<list_t<rule_t>> = [[a]]
        let x = [inner]
        rule program { "x" }
        rule a { "a" }"#,
        TypeErrorKind::InvalidListElement(Ty::LIST_LIST_RULE)
    }
    error_empty_list_needs_annotation {
        r#"grammar { language: "test" }
        let x = []
        rule program { "x" }"#,
        TypeErrorKind::EmptyContainerNeedsAnnotation(ContainerKind::List)
    }
    error_empty_list_with_non_list_annotation {
        r#"grammar { language: "test" }
        let x: int_t = []
        rule program { "x" }"#,
        TypeErrorKind::EmptyContainerAnnotationMismatch { declared: Ty::INT, kind: ContainerKind::List }
    }
    error_empty_object_with_non_object_annotation {
        r#"grammar { language: "test" }
        let x: str_t = {}
        rule program { "x" }"#,
        TypeErrorKind::EmptyContainerAnnotationMismatch { declared: Ty::STR, kind: ContainerKind::Object }
    }
    error_for_requires_tuples {
        r#"grammar { language: "test" }
        let items: list_t<str_t> = ["a", "b"]
        rule program { choice(for (a: str_t, b: str_t) in items { a }) }"#,
        TypeErrorKind::ForRequiresTuples
    }
    error_invalid_alias_target {
        r#"grammar { language: "test" }
        rule program { alias("x", 42) }"#,
        TypeErrorKind::InvalidAliasTarget(Ty::INT)
    }
    error_expected_reserved_config {
        r#"grammar { language: "test", reserved: "not_an_object" }
        rule program { "x" }"#,
        TypeErrorKind::ReservedMustBeLiteral
    }
    error_reserved_computed_rejected {
        // A let-bound (computed) reserved is rejected: the first set is the
        // default, so set order must be explicit, not from an unordered value.
        r#"let r: obj_t<list_t<rule_t>> = { global: ["if"] }
        grammar { language: "test", reserved: r }
        rule program { "x" }"#,
        TypeErrorKind::ReservedMustBeLiteral
    }
    error_reserved_duplicate_context {
        // Without this check the second set would silently win (dsl.js object
        // semantics); duplicate keys error like any other object literal.
        r#"grammar { language: "test", reserved: { default: ["if"], default: ["else"] } }
        rule program { "x" }"#,
        TypeErrorKind::DuplicateObjectKey("default".into())
    }
    error_empty_object_needs_annotation {
        r#"grammar { language: "test" }
        let x = {}
        rule program { "x" }"#,
        TypeErrorKind::EmptyContainerNeedsAnnotation(ContainerKind::Object)
    }
    error_bare_function_reference {
        r#"grammar { language: "test" }
        macro make_rule(x: str_t) rule_t { x }
        rule program { make_rule }"#,
        TypeErrorKind::MacroUsedAsValue("make_rule".into())
    }
    error_concat_with_non_string_arg {
        r#"grammar { language: "test" }
        rule program { regexp(concat("a", 1)) }"#,
        TypeErrorKind::TypeMismatch { expected: Ty::STR, got: Ty::INT }
    }
    error_regexp_with_non_string_pattern {
        r#"grammar { language: "test" }
        let x: int_t = 1
        rule program { regexp(x) }"#,
        TypeErrorKind::TypeMismatch { expected: Ty::STR, got: Ty::INT }
    }
    error_regexp_with_non_string_flags {
        r#"grammar { language: "test" }
        let f: int_t = 1
        rule program { regexp("[a-z]+", f) }"#,
        TypeErrorKind::TypeMismatch { expected: Ty::STR, got: Ty::INT }
    }
    error_prec_dynamic_with_string_value {
        r#"grammar { language: "test" }
        rule program { prec_dynamic("high", "x") }"#,
        TypeErrorKind::TypeMismatch { expected: Ty::INT, got: Ty::STR }
    }
    error_int_arith_lhs_not_int {
        r#"grammar { language: "test" }
        rule program { prec("x" + 1, "y") }"#,
        TypeErrorKind::TypeMismatch { expected: Ty::INT, got: Ty::STR }
    }
    error_int_arith_rhs_not_int {
        r#"grammar { language: "test" }
        rule program { prec(1 + "x", "y") }"#,
        TypeErrorKind::TypeMismatch { expected: Ty::INT, got: Ty::STR }
    }
}}

inherit_error_tests! { Type {
    error_inherited_type_error {
        "grammar { language: \"base\" }\nrule program { 42 }\n",
        TypeErrorKind::TypeMismatch { expected: Ty::RULE, got: Ty::INT }
    }
}}

#[test]
fn error_duplicate_object_key_has_note() {
    let e = assert_err!(
        dsl_err(r#"grammar { language: "test" } let x = { a: 1, b: 2, a: 3 } rule foo { "x" }"#),
        Type
    );
    assert_eq!(e.kind, TypeErrorKind::DuplicateObjectKey("a".into()));
    assert!(!e.notes.is_empty());
}

#[test]
fn error_alias_to_module_rule_suggests_bare_name() {
    let e = assert_err!(
        dsl_err(
            r#"let base = inherit("inherit_base/grammar.tsg")
            grammar { language: "derived", inherits: base }
            rule extra { alias("x", base::identifier) }"#
        ),
        Type
    );
    assert_eq!(e.kind, TypeErrorKind::InvalidAliasTarget(Ty::RULE));
    let [note] = e.notes.as_slice() else {
        panic!("expected one note, got {:?}", e.notes);
    };
    assert_eq!(note.message, NoteMessage::UseBareName("identifier".into()));
}

#[test]
fn error_module_rule_in_name_position_suggests_bare_name() {
    let e = assert_err!(
        dsl_err(
            r#"let base = inherit("inherit_base/grammar.tsg")
            grammar { language: "derived", inherits: base, inline: [base::_inline_rule] }
            rule extra { "x" }"#
        ),
        Type
    );
    assert_eq!(e.kind, TypeErrorKind::ExpectedRuleName);
    let [note] = e.notes.as_slice() else {
        panic!("expected one note, got {:?}", e.notes);
    };
    assert_eq!(
        note.message,
        NoteMessage::UseBareName("_inline_rule".into())
    );
}

#[test]
fn error_grammar_config_on_import_module() {
    let err = expect_err(parse_with_modules(
        &[("helper.tsg", "let X: int_t = 1")],
        "let h = import(\"helper.tsg\")\n\
         grammar { language: \"t\", extras: grammar_config(h, extras) }\n\
         rule program { \"x\" }",
    ));
    let e = assert_err!(err, Type);
    assert_eq!(e.kind, TypeErrorKind::GrammarConfigRequiresInherit);
}

#[test]
fn deep_let_chain_type_checks_without_overflow() {
    // A long, acyclic `let` chain once overflowed the stack: type_of_let recursed
    // one frame per hop with no parse-depth bound. typecheck now resolves let
    // dependencies with an explicit stack, so a chain of any length type-checks.
    // The chain is unused by any rule, so it also lowers cleanly.
    use std::fmt::Write as _;
    let n = 4000;
    let mut src = String::from("grammar { language: \"test\" }\n");
    for i in 0..n {
        writeln!(src, "let l{i} = l{}", i + 1).unwrap();
    }
    writeln!(src, "let l{n} = \"x\"").unwrap();
    src.push_str("rule program { \"literal\" }\n");
    // Must not overflow the stack; `dsl` unwraps, so any error fails the test too.
    let _ = dsl(&src);
}
