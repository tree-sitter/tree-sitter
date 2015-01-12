#include "compiler/compiler_spec_helper.h"
#include "compiler/prepare_grammar/flatten_grammar.h"
#include "compiler/prepare_grammar/initial_syntax_grammar.h"
#include "compiler/syntax_grammar.h"
#include "compiler/helpers/containers.h"

START_TEST

using namespace rules;
using prepare_grammar::flatten_grammar;
using prepare_grammar::InitialSyntaxGrammar;

describe("flatten_grammar", []() {
  InitialSyntaxGrammar input_grammar({
    { "rule1", seq({
        i_sym(1),
        choice({ i_sym(2), i_sym(3) }),
        i_sym(4) }) },
    { "rule2", seq({
        i_sym(1),
        prec(50, seq({
          i_sym(2),
          choice({
            prec(100, seq({
              i_sym(3),
              i_sym(4)
            })),
            i_sym(5),
          }),
          i_sym(6) })),
        i_sym(7) }) },
  }, {});

  it("turns each rule into a list of possible symbol sequences", [&]() {
    SyntaxGrammar grammar = flatten_grammar(input_grammar);

    auto get_symbol_lists = [&](int rule_index) {
      return collect(grammar.rules[rule_index].second, [](Production p) {
        return collect(p.entries, [](ProductionEntry e) {
          return e.symbol;
        });
      });
    };

    AssertThat(grammar.rules[0].first, Equals("rule1"));
    AssertThat(grammar.rules[1].first, Equals("rule2"));

    AssertThat(
      get_symbol_lists(0),
      Equals(vector<vector<Symbol>>({
        { Symbol(1), Symbol(2), Symbol(4) },
        { Symbol(1), Symbol(3), Symbol(4) }
      })));

    AssertThat(
      get_symbol_lists(1),
      Equals(vector<vector<Symbol>>({
        { Symbol(1), Symbol(2), Symbol(3), Symbol(4), Symbol(6), Symbol(7) },
        { Symbol(1), Symbol(2), Symbol(5), Symbol(6), Symbol(7) }
      })));
  });

  it("associates each symbol with the precedence binding it to its previous neighbor", [&]() {
    SyntaxGrammar grammar = flatten_grammar(input_grammar);

    auto get_precedence_lists = [&](int rule_index) {
      return collect(grammar.rules[rule_index].second, [](Production p) {
        return collect(p.entries, [](ProductionEntry e) {
          return e.precedence;
        });
      });
    };

    AssertThat(
      get_precedence_lists(0),
      Equals(vector<vector<int>>({
        { 0, 0, 0 },
        { 0, 0, 0 }
      })));

    AssertThat(
      get_precedence_lists(1),
      Equals(vector<vector<int>>({
        { 0, 0, 50, 100, 50, 0 },
        { 0, 0, 50, 50, 0 }
      })));
  });

  it("associates each unique subsequence of symbols and precedences with a rule_id", [&]() {
    SyntaxGrammar grammar = flatten_grammar(input_grammar);

    auto rule_id = [&](int rule_index, int production_index, int symbol_index) {
      return grammar.rules[rule_index].second[production_index].rule_id_at(symbol_index);
    };

    // Rule 1: last symbol is the same for both productions.
    AssertThat(rule_id(0, 0, 0), !Equals(rule_id(0, 1, 0)));
    AssertThat(rule_id(0, 0, 1), !Equals(rule_id(0, 1, 1)));
    AssertThat(rule_id(0, 0, 2),  Equals(rule_id(0, 1, 2)));

    // Rule 2: last two symbols are the same for both productions.
    AssertThat(rule_id(1, 0, 0), !Equals(rule_id(1, 1, 0)));
    AssertThat(rule_id(1, 0, 1), !Equals(rule_id(1, 1, 1)));
    AssertThat(rule_id(1, 0, 4),  Equals(rule_id(1, 1, 3)));
    AssertThat(rule_id(1, 0, 5),  Equals(rule_id(1, 1, 4)));
  });
});

END_TEST
