use super::*;

#[test]
fn extras_mixed_rule_and_str() {
    // extras is list_t<rule_t> - should accept a mix of rule refs and strings
    let g = dsl(r#"
        grammar { language: "test", extras: [ws, "\n"] }
        rule program { "x" }
        rule ws { regexp(r"\s") }
    "#);
    assert_eq!(g.extra_roots.len(), 2);
}

compile_tests! {
    list_mixed_rule_and_str_coerces_to_list_rule {
        // A mixed str/rule list coerces to list_t<rule_t> (str_t <: rule_t).
        r#"grammar { language: "test" }
        let items: list_t<rule_t> = [program, "literal"]
        rule program { choice(for (r: rule_t) in items { r }) }"#
    }
    list_str_first_then_rule_coerces_to_list_rule {
        // First element str, second rule - should widen to list_t<rule_t>
        r#"grammar { language: "test" }
        let items: list_t<rule_t> = ["literal", program]
        rule program { "x" }"#
    }
    object_mixed_str_and_rule_values_coerces {
        r#"grammar { language: "test" }
        let o = { a: program, b: "literal" }
        rule program { o.a }"#
    }
    object_str_first_then_rule_coerces {
        r#"grammar { language: "test" }
        let o = { a: "literal", b: program }
        rule program { o.b }"#
    }
    obj_str_compatible_with_obj_rule_annotation {
        r#"grammar { language: "test" }
        let o: obj_t<rule_t> = { a: "x", b: "y" }
        rule program { o.a }"#
    }
    empty_object_in_macro_arg_uses_param_type {
        r#"grammar { language: "test" }
        macro f(o: obj_t<rule_t>) rule_t { "x" }
        rule program { f({}) }"#
    }
    empty_list_in_macro_arg_uses_param_type {
        r#"grammar { language: "test" }
        macro f(xs: list_t<rule_t>) rule_t { "x" }
        rule program { f([]) }"#
    }
    list_int_literal_infers_list_int {
        r#"grammar { language: "test" }
        let nums: list_t<int_t> = [1, 2, 3]
        rule program { "x" }"#
    }
    list_list_rule_literal_infers_list_list_rule {
        r#"grammar { language: "test" }
        let pairs: list_t<list_t<rule_t>> = [[a, b], [c]]
        rule program { "x" }
        rule a { "a" }
        rule b { "b" }
        rule c { "c" }"#
    }
    list_list_str_subtype_of_list_list_rule {
        r#"grammar { language: "test" }
        let groups: list_t<list_t<rule_t>> = [["a", "b"], ["c"]]
        rule program { "x" }"#
    }
    list_list_int_literal_infers_list_list_int {
        r#"grammar { language: "test" }
        let nested: list_t<list_t<int_t>> = [[1], [2, 3]]
        rule program { "x" }"#
    }
    for_over_list_list_rule_yields_list_rule {
        r#"grammar { language: "test" }
        let groups: list_t<list_t<rule_t>> = [[a], [b]]
        rule program { choice(for (inner: list_t<rule_t>) in groups { seq(for (r: rule_t) in inner { r }) }) }
        rule a { "a" }
        rule b { "b" }"#
    }
    library_t_annotation {
        r#"let h: library_t = import("import_helpers/helpers.tsg")
        grammar { language: "test" }
        rule program { h::comma_sep1(identifier) }
        rule identifier { regexp("[a-z]+") }"#
    }
    obj_t_int_annotation {
        r#"grammar { language: "test" }
        let PREC: obj_t<int_t> = { ADD: 1, MUL: 2 }
        rule program { prec(PREC.ADD, "x") }"#
    }
    obj_t_rule_annotation {
        r#"grammar { language: "test" }
        let o: obj_t<rule_t> = { a: program, b: "literal" }
        rule program { o.a }"#
    }
    obj_t_list_rule_annotation {
        r#"grammar { language: "test" }
        let o: obj_t<list_t<rule_t>> = { items: [a, b] }
        rule program { choice(for (r: rule_t) in o.items { r }) }
        rule a { "a" }
        rule b { "b" }"#
    }
    obj_t_str_annotation {
        r#"grammar { language: "test" }
        let aliases: obj_t<str_t> = { open: "<", close: ">" }
        rule program { seq(aliases.open, aliases.close) }"#
    }
    nested_empty_list_infers_from_outer_annotation {
        r#"grammar { language: "test" }
        let pairs: list_t<list_t<rule_t>> = [[]]
        rule program { "x" }"#
    }
    empty_list_in_obj_value_infers_from_obj_annotation {
        r#"grammar { language: "test" }
        let o: obj_t<list_t<rule_t>> = { a: [] }
        rule program { "x" }"#
    }
    empty_append_arms_infer_from_let_annotation {
        r#"grammar { language: "test" }
        let xs: list_t<rule_t> = append([], [])
        rule program { "x" }"#
    }
}
