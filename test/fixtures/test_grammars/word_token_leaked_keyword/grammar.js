/**
 * @file Minimal reproduction of tree-sitter build_lex_table.rs word-token
 *       transition pruning bug.
 *
 * TRIGGER CONDITIONS (all three required):
 *
 *   1. Grammar declares `word: $ => $.identifier`.
 *   2. A keyword token (neqv_op) uses explicit positive precedence via
 *      `token(prec(N, pattern))` with N > 0.
 *   3. A companion operator token exists whose pattern STARTS with the same
 *      characters as the keyword but continues past the keyword completion
 *      point (e.g. "neqv-" vs "neqv").  The companion token must be a
 *      non-keyword-candidate (it matches strings that `identifier` does not:
 *      bare "neqv-" cannot be an identifier because it ends with a hyphen).
 *
 * MECHANISM: why neqv_op stays in ts_lex instead of ts_lex_keywords
 *
 *   `identify_keywords` (build_tables.rs) runs a final filter that excludes
 *   keyword candidates for which substituting the word token (identifier)
 *   would introduce new lexical conflicts.  The filter tests each non-keyword
 *   token X:
 *
 *   Step A: find states where `neqv_op` and X coexist.  In this grammar,
 *           after a complete LHS `_expression`, both `neqv_op` (binary
 *           operator) and `neqv_ext` (companion operator) are valid
 *           lookaheads, but `identifier` is NOT.
 *
 *   Step B: because identifier is not valid in those states, the "no new
 *           conflicts" fast-path does not apply.
 *
 *   Step C: compare conflict status of `neqv_op` vs `identifier` vs X:
 *
 *     status_matrix[neqv_op, neqv_ext]:
 *       At "neqv" completion (prec=1), the `-` advance for neqv_ext has
 *       prec=0 < 1.  prefer_transition() returns FALSE.  MATCHES_PREFIX set.
 *
 *     status_matrix[identifier, neqv_ext]:
 *       At "neqv" completion (prec=0), the `-` advance for neqv_ext has
 *       prec=0 == 0.  prefer_transition() returns TRUE.  DOES_MATCH_CONTIN-
 *       UATION is set on neqv_ext side, not on identifier side.
 *       status_matrix[identifier, neqv_ext] stays EMPTY.
 *
 *     MATCHES_PREFIX != EMPTY
 *     has_same_conflict_status(neqv_op, identifier, neqv_ext) == false
 *     neqv_op is EXCLUDED from keywords and stays in ts_lex.
 *
 * DFA BUG: once neqv_op is in ts_lex
 *
 *   In the DFA state after reading "neqv", neqv_op is COMPLETE (prec=1) and
 *   the identifier continuation transition (prec=0 Advance states) is also
 *   present.  populate_state() calls
 *     prefer_transition(t.prec=0, completed_precedence=1)
 *   0 < 1 returns false, so the identifier-continuation branch is DROPPED.
 *   Input "neqvbase" is lexed as neqv_op("neqv") + identifier("base")
 *   instead of the correct identifier("neqvbase").
 *
 * FIX: populate_state() checks whether the pruned transition leads to the
 *   word-token NFA variable; if it does, the transition is KEPT.  Applied
 *   only to the main lex table (word_token = Some(identifier)).
 *
 */

export default grammar({
  name: "word_token_leaked_keyword",

  // word: declaration is required:
  //   1. It enables the keyword extraction mechanism (ts_lex_keywords).
  //   2. The fix sets word_token = Some(identifier), which is only possible
  //      when a word token is declared.
  word: $ => $.identifier,

  rules: {
    source_file: $ => repeat($._statement),

    // Six statement forms:
    //   expression-statement:   expr ;
    //   standalone-keyword:     neqv_op ;  <-- puts neqv_op and identifier
    //                                          in the SAME initial parse
    //                                          state.  The generator creates
    //                                          a shared lex_state with both
    //                                          the neqv-specific prefix path
    //                                          AND the general identifier
    //                                          path.  This is where the DFA
    //                                          bug manifests: state 8 accepts
    //                                          neqv_op with no identifier
    //                                          continuation.
    //   standalone-companion:   neqv_ext ;  <-- puts neqv_ext and identifier
    //                                          in the SAME initial parse state,
    //                                          allowing the regression tests
    //                                          below to exercise the boundary.
    //   binary-with-companion:  expr  neqv_ext  expr ;
    //                                      <-- keeps neqv_op in ts_lex via
    //                                          the identify_keywords exclusion
    //                                          (conflict-status asymmetry).
    //   standalone-hi-companion: kw_hi ;  <-- kw_hi uses prec=1; demonstrates
    //                                          that the token wins at the
    //                                          "kw-" completion point.
    //   prefix-hi-companion:    kw_hi expr ;
    //                                      <-- kw_hi wins even when word
    //                                          characters follow the hyphen
    //                                          (identifier continuation pruned,
    //                                          rescue does not fire).
    _statement: $ => choice(
      seq($._expression, ";"),
      seq($.neqv_op, ";"),
      seq($.neqv_ext, ";"),
      seq($._expression, $.neqv_ext, $._expression, ";"),
      seq($.kw_hi, ";"),
      seq($.kw_hi, $._expression, ";"),
    ),

    _expression: $ => choice(
      $.identifier,
      $.binary_expr,
    ),

    binary_expr: $ => prec.left(1,
      seq($._expression, $.neqv_op, $._expression),
    ),

    // Keyword with positive precedence (prec=1 > 0 of identifier Advance states).
    // This satisfies prefer_transition(t.prec=0 < completed=1) == false,
    // causing the identifier-continuation to be dropped from the DFA.
    neqv_op: $ => token(prec(1, /neqv/)),

    // Companion operator: same prefix as neqv_op, then a hyphen.
    // Critical properties:
    //   * NOT a keyword candidate: "neqv-" is not in identifier's language
    //     (identifiers cannot end with a hyphen), so
    //     does_match_different_string(neqv_ext, identifier) = true.
    //   * Creates the conflict-status asymmetry between neqv_op and identifier:
    //       neqv_op  (prec=1) vs neqv_ext: MATCHES_PREFIX
    //       identifier (prec=0) vs neqv_ext: EMPTY (continuation goes to
    //         neqv_ext side, not identifier side)
    //     has_same_conflict_status(neqv_op, identifier, neqv_ext) == false
    //     forces neqv_op out of keywords and into ts_lex.
    //   * Appears in operator position where identifier is NOT valid,
    //     so the fast-path ("identifier already valid everywhere") does not
    //     skip the conflict check.
    neqv_ext: $ => token(prec(0, /neqv-/)),

    // High-precedence companion: demonstrates the intentional-priority case.
    // Unlike neqv_ext (prec=0 == identifier prec=0), kw_hi uses prec=1:
    //   * At "kw-" completion: prefer_transition(t.prec=0, completed_prec=1)
    //     == false, so the identifier word-char continuation IS pruned.
    //   * The rescue in populate_state does NOT fire: kw_hi is not a keyword
    //     candidate and is never placed in leaked_keywords.
    //   * Result: kw_hi wins at "kw-" even when word characters follow,
    //     unlike neqv_ext where equal precedence lets identifier continue.
    kw_hi: $ => token(prec(1, /kw-/)),

    // Word token.  Internal hyphens are allowed (e.g. "neqv-base" is a
    // valid identifier), but a trailing hyphen is not.
    //
    // Disambiguation at the "neqv-" DFA state depends on TWO properties:
    //
    //   1. Equal precedence (prec=0 on both neqv_ext and identifier):
    //      prefer_transition(t.prec=0, completed_prec=0) returns TRUE, so
    //      the identifier word-char continuation is NOT pruned after neqv_ext
    //      completes.  If neqv_ext were prec(2), prefer_transition(0, 2)
    //      would be false and "neqv-base" would be lexed as
    //      neqv_ext("neqv-") + identifier("base").
    //
    //   2. No trailing hyphen in identifier:
    //      When ";" follows "neqv-", identifier cannot complete (the
    //      (-\w+)* group requires at least one word character after "-"),
    //      so neqv_ext is the only complete token and wins unambiguously.
    identifier: $ => /[a-zA-Z]\w*(-\w+)*/
  },
});
