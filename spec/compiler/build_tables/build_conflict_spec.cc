#include "compiler/compiler_spec_helper.h"
#include "compiler/build_tables/build_conflict.h"
#include "compiler/prepared_grammar.h"

using namespace rules;
using namespace build_tables;

START_TEST

describe("build_conflict", []() {
  Conflict conflict("");

  SyntaxGrammar parse_grammar({
      { "in_progress_rule1", i_token(0) },
      { "in_progress_rule2", i_token(0) },
      { "reduced_rule", i_token(0) },
      { "other_ruel1", i_token(0) },
      { "other_rule2", i_token(0) },
  }, {}, { Symbol(2, SymbolOptionToken) });

  LexicalGrammar lex_grammar({
      { "other_token", pattern("[a-b]") },
      { "lookahead_token", pattern("[c-d]") },
  }, {});

  it("uses the given item-set to determine which symbols are involved in the shift", [&]() {
    conflict = build_conflict(
      ParseAction::Shift(2, set<int>()),
      ParseAction::Reduce(Symbol(2), 1, 0), // reduced_rule
      ParseItemSet({
        {
          ParseItem(Symbol(0), blank(), 2), // in_progress_rule1
          set<Symbol>({ Symbol(2, SymbolOptionToken) })
        },
        {
          ParseItem(Symbol(1), blank(), 2), // in_progress_rule2
          set<Symbol>({ Symbol(2, SymbolOptionToken) })
        },
        {
          ParseItem(Symbol(3), blank(), 0), // other_rule1
          set<Symbol>({ Symbol(2, SymbolOptionToken) })
        },
      }),
      Symbol(1, SymbolOptionToken), // lookahead_token
      parse_grammar, lex_grammar
    );

    AssertThat(conflict.description, Equals(
        "lookahead_token: "
        "shift ( in_progress_rule2 in_progress_rule1 ) / "
        "reduce ( reduced_rule )"));
  });

  it("always puts shift actions before reduce actions", [&]() {
    conflict = build_conflict(
      ParseAction::Reduce(Symbol(2), 1, 0), // reduced_rule
      ParseAction::Shift(2, set<int>()),
      ParseItemSet({
        {
          ParseItem(Symbol(0), blank(), 2), // in_progress_rule1
          set<Symbol>({ Symbol(2, SymbolOptionToken) })
        },
        {
          ParseItem(Symbol(1), blank(), 2), // in_progress_rule2
          set<Symbol>({ Symbol(2, SymbolOptionToken) })
        },
      }),
      Symbol(1, SymbolOptionToken), // lookahead_token
      parse_grammar, lex_grammar
    );

    AssertThat(conflict.description, Equals(
        "lookahead_token: "
        "shift ( in_progress_rule2 in_progress_rule1 ) / "
        "reduce ( reduced_rule )"));
  });
});


END_TEST
