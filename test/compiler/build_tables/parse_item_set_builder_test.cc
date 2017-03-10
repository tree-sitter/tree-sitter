#include "test_helper.h"
#include "compiler/syntax_grammar.h"
#include "compiler/lexical_grammar.h"
#include "compiler/build_tables/parse_item_set_builder.h"
#include "compiler/build_tables/lookahead_set.h"
#include "compiler/rules/built_in_symbols.h"
#include "helpers/rule_helpers.h"

using namespace build_tables;
using namespace rules;

START_TEST

describe("ParseItemSetBuilder", []() {
  vector<LexicalVariable> lexical_variables;
  for (size_t i = 0; i < 20; i++) {
    lexical_variables.push_back({
      "token_" + to_string(i),
      VariableTypeNamed,
      blank(),
      false
    });
  }

  LexicalGrammar lexical_grammar{lexical_variables, {}};

  it("adds items at the beginnings of referenced rules", [&]() {
    SyntaxGrammar grammar{{
      SyntaxVariable{"rule0", VariableTypeNamed, {
        Production({
          {Symbol(1, Symbol::NonTerminal), 0, AssociativityNone},
          {Symbol(11, Symbol::Terminal), 0, AssociativityNone},
        }),
      }},
      SyntaxVariable{"rule1", VariableTypeNamed, {
        Production({
          {Symbol(12, Symbol::Terminal), 0, AssociativityNone},
          {Symbol(13, Symbol::Terminal), 0, AssociativityNone},
        }),
        Production({
          {Symbol(2, Symbol::NonTerminal), 0, AssociativityNone},
        })
      }},
      SyntaxVariable{"rule2", VariableTypeNamed, {
        Production({
          {Symbol(14, Symbol::Terminal), 0, AssociativityNone},
          {Symbol(15, Symbol::Terminal), 0, AssociativityNone},
        })
      }},
    }, {}, {}, {}};

    auto production = [&](int variable_index, int production_index) -> const Production & {
      return grammar.variables[variable_index].productions[production_index];
    };

    ParseItemSet item_set({
      {
        ParseItem(Symbol(0, Symbol::NonTerminal), production(0, 0), 0),
        LookaheadSet({ Symbol(10, Symbol::Terminal) }),
      }
    });

    ParseItemSetBuilder item_set_builder(grammar, lexical_grammar);
    item_set_builder.apply_transitive_closure(&item_set);

    AssertThat(item_set, Equals(ParseItemSet({
      {
        ParseItem(Symbol(0, Symbol::NonTerminal), production(0, 0), 0),
        LookaheadSet({ Symbol(10, Symbol::Terminal) })
        },
      {
        ParseItem(Symbol(1, Symbol::NonTerminal), production(1, 0), 0),
        LookaheadSet({ Symbol(11, Symbol::Terminal) })
      },
      {
        ParseItem(Symbol(1, Symbol::NonTerminal), production(1, 1), 0),
        LookaheadSet({ Symbol(11, Symbol::Terminal) })
      },
      {
        ParseItem(Symbol(2, Symbol::NonTerminal), production(2, 0), 0),
        LookaheadSet({ Symbol(11, Symbol::Terminal) })
      },
    })));
  });

  it("handles rules with empty productions", [&]() {
    SyntaxGrammar grammar{{
      SyntaxVariable{"rule0", VariableTypeNamed, {
        Production({
          {Symbol(1, Symbol::NonTerminal), 0, AssociativityNone},
          {Symbol(11, Symbol::Terminal), 0, AssociativityNone},
        }),
      }},
      SyntaxVariable{"rule1", VariableTypeNamed, {
        Production({
          {Symbol(12, Symbol::Terminal), 0, AssociativityNone},
          {Symbol(13, Symbol::Terminal), 0, AssociativityNone},
        }),
        Production({})
      }},
    }, {}, {}, {}};

    auto production = [&](int variable_index, int production_index) -> const Production & {
      return grammar.variables[variable_index].productions[production_index];
    };

    ParseItemSet item_set({
      {
        ParseItem(Symbol(0, Symbol::NonTerminal), production(0, 0), 0),
        LookaheadSet({ Symbol(10, Symbol::Terminal) }),
      }
    });

    ParseItemSetBuilder item_set_builder(grammar, lexical_grammar);
    item_set_builder.apply_transitive_closure(&item_set);

    AssertThat(item_set, Equals(ParseItemSet({
      {
        ParseItem(Symbol(0, Symbol::NonTerminal), production(0, 0), 0),
        LookaheadSet({ Symbol(10, Symbol::Terminal) })
      },
      {
        ParseItem(Symbol(1, Symbol::NonTerminal), production(1, 0), 0),
        LookaheadSet({ Symbol(11, Symbol::Terminal) })
      },
      {
        ParseItem(Symbol(1, Symbol::NonTerminal), production(1, 1), 0),
        LookaheadSet({ Symbol(11, Symbol::Terminal) })
      },
    })));
  });
});

END_TEST
