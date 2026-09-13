use std::path::{Path, PathBuf};

use crate::grammars::InputGrammar;
use crate::nativedsl::lexer::TokenKind;
use crate::rules::{Alias, Associativity, MetadataParams, Precedence, Rule, RuleId, RulePool};

use super::{
    CfgErrorKind, Constraint, ContainerKind, DataTy, DisallowedItemKind, DslError, ElemTy,
    ExpandErrorKind, InnerTy, LexErrorKind, LowerErrorKind, NativeDslError, NoteMessage,
    ParseErrorKind, ResolveErrorKind, ScalarTy, TupleSig, Ty, TypeErrorKind, parse_native_dsl,
};

// Raw builders for test expectations.
//
// These deliberately bypass `RulePool`'s smart constructors - `choice` flattens
// and dedups, `metadata_with` merges into an existing node - so an expectation
// describes a *literal* shape. Building expectations with the same constructors
// under test would hide constructor bugs, which is exactly the defect class the
// pool port introduced and the grammar.json roundtrip caught.
//
// They are macros rather than functions so expectations nest: each expands to a
// `let` binding first, sequencing the inner `&mut RulePool` borrows before the
// outer call. The equivalent functions do not compile - `seq(p, &[choice(p, ..)])`
// is two overlapping mutable borrows, and two-phase borrows do not apply to
// explicit `&mut` arguments.

macro_rules! r_str {
    ($p:expr, $v:expr) => {{
        let id = $p.intern($v);
        $p.push_node(Rule::String(id))
    }};
}

macro_rules! r_sym {
    ($p:expr, $v:expr) => {{
        let id = $p.intern($v);
        $p.push_node(Rule::NamedSymbol(id))
    }};
}

macro_rules! r_pattern {
    ($p:expr, $v:expr) => {
        r_pattern!($p, $v, "")
    };
    ($p:expr, $v:expr, $f:expr) => {{
        let v = $p.intern($v);
        let f = $p.intern($f);
        $p.push_node(Rule::Pattern(v, f))
    }};
}

macro_rules! r_blank {
    ($p:expr) => {{ $p.push_node(Rule::Blank) }};
}

macro_rules! r_seq {
    ($p:expr, [$($x:expr),* $(,)?]) => {{
        let ids = [$($x),*];
        let r = $p.push_children(&ids);
        $p.push_node(Rule::Seq(r))
    }};
}

macro_rules! r_choice {
    ($p:expr, [$($x:expr),* $(,)?]) => {{
        let ids = [$($x),*];
        let r = $p.push_children(&ids);
        $p.push_node(Rule::Choice(r))
    }};
}

macro_rules! r_repeat {
    ($p:expr, $inner:expr) => {{
        let rule = $inner;
        $p.push_node(Rule::Repeat(rule))
    }};
}

macro_rules! r_reserved {
    ($p:expr, $ctx:expr, $inner:expr) => {{
        let rule = $inner;
        let ctx = $p.intern($ctx);
        $p.push_node(Rule::Reserved { rule, ctx })
    }};
}

/// Wrap `$inner` in a metadata node carrying `$params` verbatim. Unlike
/// `RulePool::metadata_with` this never merges into an existing metadata child,
/// so nested metadata in an expectation stays nested.
macro_rules! r_meta {
    ($p:expr, $params:expr, $inner:expr) => {{
        let rule = $inner;
        let params = $p.push_params($params);
        $p.push_node(Rule::Metadata { params, rule })
    }};
}

macro_rules! r_prec {
    ($p:expr, $v:expr, $inner:expr) => {
        r_meta!(
            $p,
            MetadataParams {
                precedence: $v,
                ..MetadataParams::default()
            },
            $inner
        )
    };
}

macro_rules! r_prec_left {
    ($p:expr, $v:expr, $inner:expr) => {
        r_meta!(
            $p,
            MetadataParams {
                precedence: $v,
                associativity: Some(Associativity::Left),
                ..MetadataParams::default()
            },
            $inner
        )
    };
}

macro_rules! r_prec_right {
    ($p:expr, $v:expr, $inner:expr) => {
        r_meta!(
            $p,
            MetadataParams {
                precedence: $v,
                associativity: Some(Associativity::Right),
                ..MetadataParams::default()
            },
            $inner
        )
    };
}

macro_rules! r_prec_dynamic {
    ($p:expr, $v:expr, $inner:expr) => {
        r_meta!(
            $p,
            MetadataParams {
                dynamic_precedence: $v,
                ..MetadataParams::default()
            },
            $inner
        )
    };
}

macro_rules! r_token {
    ($p:expr, $inner:expr) => {
        r_meta!(
            $p,
            MetadataParams {
                is_token: true,
                ..MetadataParams::default()
            },
            $inner
        )
    };
}

macro_rules! r_immediate_token {
    ($p:expr, $inner:expr) => {
        r_meta!(
            $p,
            MetadataParams {
                is_token: true,
                is_main_token: true,
                ..MetadataParams::default()
            },
            $inner
        )
    };
}

macro_rules! r_field {
    ($p:expr, $name:expr, $inner:expr) => {{
        let rule = $inner;
        let name = $p.intern($name);
        let params = $p.push_params(MetadataParams {
            field: Some(name),
            ..MetadataParams::default()
        });
        $p.push_node(Rule::Metadata { params, rule })
    }};
}

macro_rules! r_alias {
    ($p:expr, $value:expr, $named:expr, $inner:expr) => {{
        let rule = $inner;
        let value = $p.intern($value);
        let params = $p.push_params(MetadataParams {
            alias: Some(Alias {
                value,
                is_named: $named,
            }),
            ..MetadataParams::default()
        });
        $p.push_node(Rule::Metadata { params, rule })
    }};
}

/// Generate tests that parse a grammar and assert on the first variable's rule.
/// `$p` names the pool inside `$expected`, which builds the expected shape with
/// the `r_*` macros above.
macro_rules! rule_tests {
    ($($name:ident { $input:expr, |$p:ident| $expected:expr })*) => {
        $(#[test] fn $name() {
            let mut g = dsl($input);
            let actual = g.variables[0].root;
            let expected = { let $p = &mut g.pool; $expected };
            assert_rule_eq(&g.pool, actual, expected);
        })*
    };
}

/// Generate tests that just verify a grammar compiles without error.
macro_rules! compile_tests {
    ($($name:ident { $input:expr })*) => {
        $(#[test] fn $name() { dsl($input); })*
    };
}

/// Generate tests that parse a grammar and assert on a named rule's body.
macro_rules! find_rule_tests {
    ($($name:ident { $input:expr, $rule:expr, |$p:ident| $expected:expr })*) => {
        $(#[test] fn $name() {
            let mut g = dsl($input);
            let actual = find_rule(&g, $rule);
            let expected = { let $p = &mut g.pool; $expected };
            assert_rule_eq(&g.pool, actual, expected);
        })*
    };
}

/// Generate tests that parse a grammar and assert on its full rule-name list.
macro_rules! rule_names_tests {
    ($($name:ident { $input:expr, $expected:expr })*) => {
        $(#[test] fn $name() {
            let g = dsl($input);
            assert_eq!(rule_names(&g), $expected);
        })*
    };
}

/// Generate tests that parse a grammar and assert on its full external-token list.
macro_rules! externals_tests {
    ($($name:ident { $input:expr, |$p:ident| $expected:expr })*) => {
        $(#[test] fn $name() {
            let mut g = dsl($input);
            let actual = g.external_roots.clone();
            let expected: Vec<RuleId> = { let $p = &mut g.pool; $expected };
            assert_rules_eq(&g.pool, &actual, &expected);
        })*
    };
}

macro_rules! assert_err {
    ($err:expr, $variant:ident) => {
        match $err {
            DslError::$variant(e) => e,
            other => panic!("expected {} error, got {other:?}", stringify!($variant)),
        }
    };
}

/// Generate test functions asserting a specific error kind for a given input.
/// `$variant` is the `DslError` variant to match (e.g. Parse, Resolve, Lower).
///
/// Two forms:
/// - `error_tests! { Variant { name { input, EXPECTED } ... } }` compares the
///   kind by value (`assert_eq!`); for kinds that derive `Eq`.
/// - `error_tests! { match Variant { name { input, PATTERN [if GUARD] } ... } }`
///   pattern-matches the kind (`matches!`); for kinds that can't derive `Eq`
///   (e.g. holding a non-`Eq` `io::Error`). The optional guard keeps the payload
///   assertion.
macro_rules! error_tests {
    ($variant:ident { $($name:ident { $input:expr, $expected:expr })* }) => {
        $(#[test] fn $name() {
            let e = assert_err!(dsl_err($input), $variant);
            assert_eq!(e.kind, $expected);
        })*
    };
    (match $variant:ident { $($name:ident { $input:expr, $expected:pat $(if $guard:expr)? })* }) => {
        $(#[test] fn $name() {
            let e = assert_err!(dsl_err($input), $variant);
            assert!(
                matches!(&e.kind, $expected $(if $guard)?),
                "unexpected error kind: {:?}", e.kind
            );
        })*
    };
}

mod bindings;
mod cfg;
mod combinators;
mod config;
mod errors;
mod imports;
mod inheritance;
mod rule_set_macros;
mod types;

/// Compare a lowered rule against an expected shape, rendering both as
/// `grammar.json` on mismatch.
#[track_caller]
pub(super) fn assert_rule_eq(pool: &RulePool, actual: RuleId, expected: RuleId) {
    if !pool.subtree_eq(actual, expected) {
        let show = |id| {
            serde_json::to_string_pretty(&super::serialize::rule_to_json(pool, id))
                .expect("rule JSON")
        };
        panic!(
            "rule mismatch\n--- actual ---\n{}\n--- expected ---\n{}",
            show(actual),
            show(expected)
        );
    }
}

/// [`assert_rule_eq`] over two lists, checking length first.
#[track_caller]
pub(super) fn assert_rules_eq(pool: &RulePool, actual: &[RuleId], expected: &[RuleId]) {
    assert_eq!(
        actual.len(),
        expected.len(),
        "rule list length differs: {} actual vs {} expected",
        actual.len(),
        expected.len()
    );
    for (a, e) in actual.iter().zip(expected) {
        assert_rule_eq(pool, *a, *e);
    }
}

/// `Result::unwrap_err` without requiring `InputGrammar: Debug`.
///
/// Deriving `Debug` on `InputGrammar` would pull it onto `RulePool` too, making
/// the whole arena formattable in the shared backend's public surface purely for
/// test convenience. Not worth it for an unwrap.
#[track_caller]
pub(super) fn expect_err<E>(r: Result<InputGrammar, E>) -> E {
    match r {
        Err(e) => e,
        Ok(_) => panic!("expected an error, got a grammar"),
    }
}

/// Structural equality for two grammars that own *separate* pools.
///
/// `RuleId`s are pool-local, so cross-pool comparison has to go through resolved
/// shape. The start-rule check preserves the one order-sensitive grammar
/// property.
#[track_caller]
pub(super) fn assert_grammar_eq(a: &InputGrammar, b: &InputGrammar) {
    let a_start = a.variables.first().map(|v| a.pool.resolve(v.name));
    let b_start = b.variables.first().map(|v| b.pool.resolve(v.name));
    assert_eq!(a_start, b_start, "start rule differs");
    assert_eq!(
        super::serialize::grammar_to_json(a),
        super::serialize::grammar_to_json(b)
    );
}

/// Directory containing DSL-specific helper fixtures (inherit bases, import helpers).
pub(super) fn test_fixtures_dir() -> std::path::PathBuf {
    Path::new(env!("CARGO_MANIFEST_DIR")).join("src/nativedsl/tests/fixtures")
}

/// Convert a path to a forward-slash string for embedding in DSL source.
/// Ensures import/inherit paths work on Windows where `display()` produces `\`.
pub(super) fn dsl_path(p: &std::path::Path) -> String {
    p.to_str().unwrap().replace('\\', "/")
}

pub(super) fn dsl(input: &str) -> InputGrammar {
    parse_native_dsl(input, &test_fixtures_dir().join("grammar.tsg")).unwrap()
}

pub(super) fn dsl_err(input: &str) -> DslError {
    expect_err(parse_native_dsl(
        input,
        &test_fixtures_dir().join("grammar.tsg"),
    ))
    .into_err()
}

/// Write `modules` (filename -> source) into a fresh tempdir and parse `root`
/// against it, so imports/inherits resolve by relative filename - e.g.
/// `import("helper.tsg")`. The tempdir drops after parsing, which has already
/// read every file. Returns the raw result so callers `.unwrap()` for the
/// grammar or `.unwrap_err()` for the error.
pub(super) fn parse_with_modules(
    modules: &[(&str, &str)],
    root: &str,
) -> Result<InputGrammar, DslError> {
    parse_with_module_documents(modules, root).map_err(NativeDslError::into_err)
}

pub(super) fn parse_with_module_documents(
    modules: &[(&str, &str)],
    root: &str,
) -> Result<InputGrammar, NativeDslError> {
    let dir = tempfile::tempdir().unwrap();
    for (name, src) in modules {
        std::fs::write(dir.path().join(name), src).unwrap();
    }
    // The root path must exist on disk - it's canonicalized to seed cycle
    // detection - even though parsing reads `root` directly.
    let root_path = dir.path().join("grammar.tsg");
    std::fs::write(&root_path, root).unwrap();
    parse_native_dsl(root, &root_path)
}

/// Build the expected shape for `comma_sep1(item)`:
/// `seq(item, choice(repeat(seq(",", item)), blank))`
pub(super) fn comma_sep1_rule(p: &mut RulePool, item: &str) -> RuleId {
    sep_by1_rule(p, ",", item)
}

/// Build the expected shape for `comma_sep(item)`:
/// `choice(comma_sep1(item), blank)`
pub(super) fn comma_sep_rule(p: &mut RulePool, item: &str) -> RuleId {
    let first = comma_sep1_rule(p, item);
    let blank = r_blank!(p);
    r_choice!(p, [first, blank])
}

/// Build the expected shape for `sep_by1(sep, item)`:
/// `seq(item, choice(repeat(seq(sep, item)), blank))`
pub(super) fn sep_by1_rule(p: &mut RulePool, sep: &str, item: &str) -> RuleId {
    let head = r_sym!(p, item);
    let sep_str = r_str!(p, sep);
    let tail_item = r_sym!(p, item);
    let pair = r_seq!(p, [sep_str, tail_item]);
    let rep = r_repeat!(p, pair);
    let blank = r_blank!(p);
    let tail = r_choice!(p, [rep, blank]);
    r_seq!(p, [head, tail])
}

/// Parse a grammar that inherits from a tempfile base, returning the error.
/// `base_content` is written to `base.tsg`, and the parent grammar is:
/// `let base = inherit("base.tsg") grammar { language: "derived", inherits: base } rule extra { "hello" }`
pub(super) fn inherit_err(base_content: &str) -> (NativeDslError, PathBuf) {
    let dir = tempfile::tempdir().unwrap();
    let base_path = dir.path().join("base.tsg");
    std::fs::write(&base_path, base_content).unwrap();
    let base_path = dunce::canonicalize(&base_path).unwrap();
    let parent_path = dir.path().join("parent.tsg");
    let parent_src = "let base = inherit(\"base.tsg\")\n\
                      grammar { language: \"derived\", inherits: base }\n\
                      rule extra { \"hello\" }\n";
    std::fs::write(&parent_path, parent_src).unwrap();
    let err = expect_err(parse_native_dsl(parent_src, &parent_path));
    (err, base_path)
}

pub(super) fn rule_names(g: &InputGrammar) -> Vec<&str> {
    g.variables.iter().map(|v| g.pool.resolve(v.name)).collect()
}

/// The conflict sets as text, for comparison against `vec![vec!["a", "b"]]`.
pub(super) fn conflict_names(g: &InputGrammar) -> Vec<Vec<&str>> {
    g.conflict_names
        .iter()
        .map(|c| c.iter().map(|&n| g.pool.resolve(n)).collect())
        .collect()
}

pub(super) fn find_rule(g: &InputGrammar, name: &str) -> RuleId {
    g.variables
        .iter()
        .find(|v| g.pool.resolve(v.name) == name)
        .unwrap_or_else(|| panic!("rule '{name}' not found"))
        .root
}
