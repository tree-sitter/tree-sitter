// Tests in this mod need be executed with enabled UBSAN library:
// ```
// UBSAN_OPTIONS="halt_on_error=1" \
// CFLAGS="-fsanitize=undefined"   \
// RUSTFLAGS="-lubsan"             \
// cargo test --target $(rustc -vV | sed -nr 's/^host: //p') -- --test-threads 1
// ```

use super::helpers::query_helpers::assert_query_matches;
use crate::tests::helpers::fixtures::get_language;
use indoc::indoc;
use tree_sitter::Query;

#[test]
fn issue_2162_out_of_bound() {
    let language = get_language("java");
    assert!(Query::new(&language, "(package_declaration _ (_) @name _)").is_ok());
}

#[test]
fn issue_2107_first_child_group_anchor_had_no_effect() {
    let language = get_language("c");
    let source_code = indoc! {r#"
        void fun(int a, char b, int c) { };
    "#};
    let query = indoc! {r#"
        (parameter_list
            .
            (
                (parameter_declaration) @constant
                (#match? @constant "^int")
            )
        )
    "#};
    let query = Query::new(&language, query).unwrap();
    assert_query_matches(
        &language,
        &query,
        source_code,
        &[(0, vec![("constant", "int a")])],
    );
}
