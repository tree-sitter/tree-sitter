//! JSON-to-tables lexical policy tests; no generated C parser is needed.

use serde_json::{Map, Value, json};

use super::{ParseTableBuilderError, Tables, build_tables};
use crate::{
    OptLevel, node_types,
    parse_grammar::parse_grammar,
    prepare_grammar::{PreparedGrammar, prepare_grammar},
    rules::{Symbol, SymbolView},
    tables::{LexTable, ParseAction},
};

fn symbol(name: &str) -> Value {
    json!({"type": "SYMBOL", "name": name})
}

fn string(value: &str) -> Value {
    json!({"type": "STRING", "value": value})
}

fn pattern(value: &str) -> Value {
    json!({"type": "PATTERN", "value": value})
}

fn choice(members: Vec<Value>) -> Value {
    let mut rule = json!({"type": "CHOICE"});
    rule["members"] = Value::Array(members);
    rule
}

fn seq(members: Vec<Value>) -> Value {
    let mut rule = json!({"type": "SEQ"});
    rule["members"] = Value::Array(members);
    rule
}

fn token(content: Value) -> Value {
    let mut rule = json!({"type": "TOKEN"});
    rule["content"] = content;
    rule
}

fn prec(value: i32, content: Value) -> Value {
    let mut rule = json!({"type": "PREC", "value": value});
    rule["content"] = content;
    rule
}

fn grammar(root: Value, tokens: &[(&str, Value)], reverse: bool) -> Value {
    // Keep the start rule first and the root's choice order fixed. Only token
    // declarations move, so parser context cannot account for changed results.
    let mut rules = Map::new();
    rules.insert("root".into(), root);
    let mut declarations = tokens.to_vec();
    if reverse {
        declarations.reverse();
    }
    for (name, rule) in declarations {
        rules.insert(name.into(), rule);
    }
    json!({"name": "lexical_policy", "rules": rules})
}

fn alternatives(tokens: &[(&str, Value)], reverse: bool) -> Value {
    grammar(
        choice(tokens.iter().map(|(name, _)| symbol(name)).collect()),
        tokens,
        reverse,
    )
}

fn build(input: &Value) -> Result<(PreparedGrammar, Tables), ParseTableBuilderError> {
    let mut diagnostics = Vec::new();
    let input = parse_grammar(&input.to_string(), &mut diagnostics).unwrap();
    let prepared = prepare_grammar(input, &mut diagnostics).unwrap();
    let variable_info = node_types::get_variable_info(
        &prepared.syntax_grammar,
        &prepared.lexical_grammar,
        &prepared.default_aliases,
        &prepared.str_pool,
    )
    .unwrap();
    let tables = build_tables(
        &prepared.syntax_grammar,
        &prepared.lexical_grammar,
        &prepared.default_aliases,
        &variable_info,
        &prepared.inlines,
        &prepared.str_pool,
        None,
        OptLevel::default(),
        &mut diagnostics,
    )?;
    Ok((prepared, tables))
}

/// Remember the last acceptance, just as the generated lexer does. Byte offsets
/// let tests check longest-match behavior as well as token identity.
fn lex(table: &LexTable, start: u32, input: &str) -> Option<(Symbol, usize)> {
    lex_span(table, start, input).map(|(symbol, _, end)| (symbol, end))
}

fn lex_span(table: &LexTable, start: u32, input: &str) -> Option<(Symbol, usize, usize)> {
    let mut state = start as usize;
    let mut token_start = 0;
    let mut accepted = table.states[state]
        .accept_action
        .map(|symbol| (symbol, 0, 0));
    for (offset, ch) in input.char_indices() {
        let Some((_, action)) = table.states[state]
            .advance_actions
            .iter()
            .find(|(characters, _)| characters.contains(ch))
        else {
            break;
        };
        if !action.in_main_token {
            token_start = offset + ch.len_utf8();
        }
        state = action.state as usize;
        if let Some(symbol) = table.states[state].accept_action {
            accepted = Some((symbol, token_start, offset + ch.len_utf8()));
        }
    }
    accepted
}

fn lex_in_state(tables: &Tables, state: usize, input: &str) -> (Symbol, usize) {
    lex(
        &tables.main_lex_table,
        tables.parse_table.states[state].lex_state_id,
        input,
    )
    .unwrap_or_else(|| panic!("no token accepted for {input:?} in parse state {state}"))
}

fn token_name(prepared: &PreparedGrammar, symbol: Symbol) -> &str {
    let SymbolView::Terminal(index) = symbol.view() else {
        panic!("expected an internal token, got {symbol:?}");
    };
    prepared
        .str_pool
        .resolve(prepared.lexical_grammar.variables[usize::from(index)].name)
}

fn assert_token(input: &Value, text: &str, expected: &str, length: usize) {
    let (prepared, tables) = build(input).unwrap();
    let state = &tables.parse_table.states[1];
    let (mut symbol, start, consumed) =
        lex_span(&tables.main_lex_table, state.lex_state_id, text).unwrap();
    if Some(symbol) == prepared.syntax_grammar.word_token
        && !tables.keyword_lex_table.states.is_empty()
        && let Some((keyword, length)) = lex(&tables.keyword_lex_table, 0, &text[start..consumed])
        && length == consumed - start
        && (state.terminal_entries.contains_key(&keyword) || state.reserved_words.contains(keyword))
    {
        symbol = keyword;
    }
    assert_eq!(token_name(&prepared, symbol), expected, "{text:?}");
    assert_eq!(consumed, length, "{text:?}");
}

#[test]
fn keyword_substitution_preserves_the_winner_against_remaining_tokens() {
    for (other, word) in [("[a1]", "[ab1]"), ("[ab]", "[abc]")] {
        for reverse in [false, true] {
            for explicit in [false, true] {
                let mut input = alternatives(
                    &[
                        ("keyword", token(string("a"))),
                        ("other", token(pattern(other))),
                        ("word", token(pattern(word))),
                    ],
                    reverse,
                );
                input["word"] = json!("word");
                if explicit {
                    input["precedences"] = json!([[symbol("keyword"), symbol("other")]]);
                }
                assert_token(&input, "a", "keyword", 1);
            }
        }
    }
}

#[test]
fn ordinary_disjoint_keywords_are_still_extracted() {
    let mut input = alternatives(
        &[
            ("first", string("a")),
            ("second", string("b")),
            ("word", pattern("[abc]+")),
        ],
        false,
    );
    input["word"] = json!("word");
    let (prepared, tables) = build(&input).unwrap();
    assert_eq!(
        token_name(&prepared, lex_in_state(&tables, 1, "a").0),
        "word"
    );
    assert_token(&input, "a", "first", 1);
    assert_token(&input, "b", "second", 1);
    assert_token(&input, "abc", "word", 3);
}

#[test]
fn keyword_substitution_preserves_numeric_precedence_and_immediacy() {
    for reverse in [false, true] {
        let mut input = alternatives(
            &[
                ("keyword", token(prec(1, string("a")))),
                ("word", pattern("[ab]+")),
            ],
            reverse,
        );
        input["word"] = json!("word");
        assert_token(&input, "ab", "keyword", 1);

        let mut input = alternatives(
            &[
                (
                    "keyword",
                    json!({"type": "IMMEDIATE_TOKEN", "content": string("a")}),
                ),
                ("word", pattern("[ab]+")),
            ],
            reverse,
        );
        input["word"] = json!("word");
        input["extras"] = json!([pattern("\\s")]);
        assert_token(&input, "a", "keyword", 1);
        assert_token(&input, " a", "word", 2);
    }
}

fn assert_ambiguity(input: &Value, witness: &str, expected_tokens: &[&str]) {
    let Err(error) = build(input) else {
        panic!("expected lexical ambiguity for {witness:?}");
    };
    let ParseTableBuilderError::LexicalAmbiguity { input, tokens } = error else {
        panic!("expected lexical ambiguity, got {error:?}");
    };
    assert_eq!(input, witness);
    let mut actual: Vec<&str> = tokens.iter().map(AsRef::as_ref).collect();
    let mut expected = expected_tokens.to_vec();
    actual.sort_unstable();
    expected.sort_unstable();
    assert_eq!(actual, expected);
}

#[test]
fn proper_subset_wins_independently_of_declaration_order() {
    let cases = [
        (pattern("[a-z]+"), string("if"), "if"),
        (
            token(choice(vec![string("if"), string("else"), string("while")])),
            token(choice(vec![string("if"), string("else")])),
            "else",
        ),
        (
            pattern("[a-z]+"),
            token(seq(vec![string("i"), string("f")])),
            "if",
        ),
        (pattern("[a-z]+"), pattern("[a-f]+"), "face"),
    ];
    for (broad, narrow, text) in cases {
        for reverse in [false, true] {
            let input = alternatives(
                &[("broad", broad.clone()), ("narrow", narrow.clone())],
                reverse,
            );
            assert_token(&input, text, "narrow", text.len());
        }
    }
}

#[test]
fn explicit_token_precedence_overrides_subset_only_at_equal_length() {
    for reverse in [false, true] {
        let mut input = alternatives(
            &[("broad", pattern("[a-z]+")), ("narrow", string("if"))],
            reverse,
        );
        input["precedences"] = json!([[symbol("broad"), symbol("narrow")]]);
        assert_token(&input, "if", "broad", 2);
        input["precedences"] = json!([[symbol("narrow"), symbol("broad")]]);
        assert_token(&input, "iffy", "broad", 4);
        assert_token(&input, "if!", "narrow", 2);
    }
}

#[test]
fn numeric_precedence_is_stronger_than_symbol_order_subset_and_length() {
    for reverse in [false, true] {
        let mut input = alternatives(
            &[
                ("broad", token(prec(1, pattern("[a-z]+")))),
                ("narrow", string("if")),
            ],
            reverse,
        );
        input["precedences"] = json!([[symbol("narrow"), symbol("broad")]]);
        assert_token(&input, "if", "broad", 2);
        let mut input = alternatives(
            &[
                ("short", token(prec(1, string("a")))),
                ("long", string("ab")),
            ],
            reverse,
        );
        input["precedences"] = json!([[symbol("long"), symbol("short")]]);
        assert_token(&input, "ab", "short", 1);
    }
}

#[test]
fn equivalent_and_incomparable_covalid_tokens_are_ambiguous() {
    for reverse in [false, true] {
        // Different ASTs prevent structural token deduplication.
        assert_ambiguity(
            &alternatives(&[("a", string("b")), ("b", pattern("[b]"))], reverse),
            "b",
            &["a", "b"],
        );
        assert_ambiguity(
            &alternatives(&[("a", pattern("[ab]")), ("b", pattern("[bc]"))], reverse),
            "b",
            &["a", "b"],
        );
    }
}

#[test]
fn a_third_subset_candidate_resolves_an_incomparable_pair() {
    for reverse in [false, true] {
        let input = alternatives(
            &[
                ("a", pattern("[ab]")),
                ("b", pattern("[bc]")),
                ("c", string("b")),
            ],
            reverse,
        );
        assert_token(&input, "b", "c", 1);
        assert_token(&input, "a", "a", 1);
        assert_token(&input, "c", "b", 1);
    }
}

#[test]
fn equivalent_tokens_in_disjoint_parser_contexts_remain_distinct() {
    for reverse in [false, true] {
        let input = grammar(
            choice(vec![
                seq(vec![symbol("left"), symbol("a")]),
                seq(vec![symbol("right"), symbol("b")]),
            ]),
            &[
                ("left", string("x")),
                ("right", string("y")),
                ("a", string("b")),
                ("b", pattern("[b]")),
            ],
            reverse,
        );
        // Recovery construction and lexer merging must neither reject these
        // tokens nor conflate the two parser contexts.
        let (prepared, tables) = build(&input).unwrap();
        for (prefix, expected) in [("x", "a"), ("y", "b")] {
            let (prefix_symbol, _) = lex_in_state(&tables, 1, prefix);
            let entry = tables.parse_table.states[1].terminal_entries[&prefix_symbol];
            let state = tables
                .parse_table
                .action_lists
                .get(entry)
                .iter()
                .find_map(|action| match action {
                    ParseAction::Shift { state, .. } => Some(*state as usize),
                    _ => None,
                })
                .expect("prefix must shift");
            let (symbol, consumed) = lex_in_state(&tables, state, "b");
            assert_eq!(token_name(&prepared, symbol), expected);
            assert_eq!(consumed, 1);
            assert!(
                tables.parse_table.states[state]
                    .terminal_entries
                    .contains_key(&symbol)
            );
        }
    }
}

#[test]
fn keyword_optimization_cannot_hide_equivalent_keyword_ambiguity() {
    for reverse in [false, true] {
        let mut input = alternatives(
            &[
                ("word", pattern("[a-z]+")),
                ("a", string("if")),
                ("b", token(seq(vec![string("i"), string("f")]))),
            ],
            reverse,
        );
        input["word"] = json!("word");
        assert_ambiguity(&input, "if", &["a", "b"]);
    }
}

#[test]
fn explicit_precedence_paths_are_transitive() {
    for reverse in [false, true] {
        let mut input = alternatives(
            &[
                ("a", pattern("[ab]")),
                ("bridge", string("z")),
                ("b", pattern("[bc]")),
            ],
            reverse,
        );
        // The middle token does not match: selection requires a transitive path.
        input["precedences"] = json!([
            [symbol("a"), symbol("bridge")],
            [symbol("bridge"), symbol("b")]
        ]);
        assert_token(&input, "b", "a", 1);
    }
}

#[test]
fn explicit_token_precedence_cycles_are_rejected() {
    let mut input = alternatives(
        &[("a", string("a")), ("b", string("b")), ("c", string("c"))],
        false,
    );
    input["precedences"] = json!([
        [symbol("a"), symbol("b")],
        [symbol("b"), symbol("c")],
        [symbol("c"), symbol("a")]
    ]);
    let Err(error) = build(&input) else {
        panic!("expected a token precedence cycle");
    };
    let ParseTableBuilderError::CyclicTokenPrecedence(tokens) = error else {
        panic!("expected token precedence cycle, got {error:?}");
    };
    let mut tokens: Vec<&str> = tokens.iter().map(AsRef::as_ref).collect();
    tokens.sort_unstable();
    assert_eq!(tokens, ["a", "b", "c"]);
}

#[test]
fn named_parse_precedence_still_resolves_expression_conflicts() {
    let binary = |name: &str, operator: &str| {
        json!({
            "type": "PREC_LEFT",
            "value": name,
            "content": seq(vec![symbol("expression"), string(operator), symbol("expression")])
        })
    };
    let mut input = grammar(
        symbol("expression"),
        &[
            (
                "expression",
                choice(vec![symbol("sum"), symbol("product"), symbol("number")]),
            ),
            ("sum", binary("sum", "+")),
            ("product", binary("product", "*")),
            ("number", pattern("[0-9]+")),
        ],
        false,
    );
    input["precedences"] = json!([[string("product"), string("sum")]]);
    assert_token(&input, "123", "number", 3);
}
