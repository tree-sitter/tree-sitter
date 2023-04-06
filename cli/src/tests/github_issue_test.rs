// Tests in this mod need be executed with enabled UBSAN library:
// ```
// UBSAN_OPTIONS="halt_on_error=1" \
// CFLAGS="-fsanitize=undefined"   \
// RUSTFLAGS="-lubsan"             \
// cargo test --target $(rustc -vV | sed -nr 's/^host: //p') -- --test-threads 1
// ```

use crate::tests::helpers::fixtures::get_language;
use tree_sitter::Query;

#[test]
fn issue_2162_out_of_bound() {
    let language = get_language("java");
    assert!(Query::new(language, "(package_declaration _ (_) @name _)").is_ok());
}
