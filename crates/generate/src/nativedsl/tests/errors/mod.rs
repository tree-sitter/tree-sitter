/// Generate test functions for errors in inherited (child) modules.
/// Calls `inherit_err()` and asserts the error kind + path match. Mirrors
/// [`error_tests!`]: a plain `$variant` compares by value (`assert_eq!`), a
/// leading `match` pattern-matches the kind with an optional `if` guard (for
/// kinds that can't derive `Eq`).
macro_rules! inherit_error_tests {
    ($variant:ident { $($name:ident { $base:expr, $expected:expr })* }) => {
        $(#[test] fn $name() {
            let (err, base_path) = inherit_err($base);
            let DslError::Module(m) = &err.error else { panic!("expected Module, got {err:?}") };
            let DslError::$variant(e) = m.inner.as_ref() else {
                panic!(concat!("expected ", stringify!($variant), ", got {:?}"), m.inner)
            };
            assert_eq!(e.kind, $expected);
            assert_eq!(err.document(m.child_document()).path(), base_path);
        })*
    };
    (match $variant:ident { $($name:ident { $base:expr, $expected:pat $(if $guard:expr)? })* }) => {
        $(#[test] fn $name() {
            let (err, base_path) = inherit_err($base);
            let DslError::Module(m) = &err.error else { panic!("expected Module, got {err:?}") };
            let DslError::$variant(e) = m.inner.as_ref() else {
                panic!(concat!("expected ", stringify!($variant), ", got {:?}"), m.inner)
            };
            assert!(
                matches!(&e.kind, $expected $(if $guard)?),
                "unexpected error kind: {:?}", e.kind
            );
            assert_eq!(err.document(m.child_document()).path(), base_path);
        })*
    };
}

mod expand;
mod lex;
mod lower;
mod parse;
mod resolve;
mod typecheck;
