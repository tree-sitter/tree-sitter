#include "test_helper.h"
#include "compiler/syntax_grammar.h"
#include "compiler/lexical_grammar.h"
#include "compiler/build_tables/parse_item_set_builder.h"
#include "compiler/build_tables/lookahead_set.h"

using namespace build_tables;
using namespace rules;

START_TEST

describe("ParseItemSetBuilder", []() {
  vector<LexicalVariable> lexical_variables;
  for (size_t i = 0; i < 20; i++) {
    lexical_variables.push_back({
      "token_" + to_string(i),
      VariableTypeNamed,
      Blank{},
      false
    });
  }

  LexicalGrammar lexical_grammar{lexical_variables, {}};

  it("adds items at the beginnings of referenced rules", [&]() {
    SyntaxGrammar grammar{{
      SyntaxVariable{"rule0", VariableTypeNamed, {
        Production({
          {Symbol::non_terminal(1), 0, AssociativityNone},
          {Symbol::terminal(11), 0, AssociativityNone},
        }),
      }},
      SyntaxVariable{"rule1", VariableTypeNamed, {
        Production({
          {Symbol::terminal(12), 0, AssociativityNone},
          {Symbol::terminal(13), 0, AssociativityNone},
        }),
        Production({
          {Symbol::non_terminal(2), 0, AssociativityNone},
        })
      }},
      SyntaxVariable{"rule2", VariableTypeNamed, {
        Production({
          {Symbol::terminal(14), 0, AssociativityNone},
          {Symbol::terminal(15), 0, AssociativityNone},
        })
      }},
    }, {}, {}, {}};

    auto production = [&](int variable_index, int production_index) -> const Production & {
      return grammar.variables[variable_index].productions[production_index];
    };

    ParseItemSet item_set({
      {
        ParseItem(Symbol::non_terminal(0), production(0, 0), 0),
        LookaheadSet({ Symbol::terminal(10) }),
      }
    });

    ParseItemSetBuilder item_set_builder(grammar, lexical_grammar);
    item_set_builder.apply_transitive_closure(&item_set);

    AssertThat(item_set, Equals(ParseItemSet({
      {
        ParseItem(Symbol::non_terminal(0), production(0, 0), 0),
        LookaheadSet({ Symbol::terminal(10) })
        },
      {
        ParseItem(Symbol::non_terminal(1), production(1, 0), 0),
        LookaheadSet({ Symbol::terminal(11) })
      },
      {
        ParseItem(Symbol::non_terminal(1), production(1, 1), 0),
        LookaheadSet({ Symbol::terminal(11) })
      },
      {
        ParseItem(Symbol::non_terminal(2), production(2, 0), 0),
        LookaheadSet({ Symbol::terminal(11) })
      },
    })));
  });

  it("handles rules with empty productions", [&]() {
    SyntaxGrammar grammar{{
      SyntaxVariable{"rule0", VariableTypeNamed, {
        Production({
          {Symbol::non_terminal(1), 0, AssociativityNone},
          {Symbol::terminal(11), 0, AssociativityNone},
        }),
      }},
      SyntaxVariable{"rule1", VariableTypeNamed, {
        Production({
          {Symbol::terminal(12), 0, AssociativityNone},
          {Symbol::terminal(13), 0, AssociativityNone},
        }),
        Production({})
      }},
    }, {}, {}, {}};

    auto production = [&](int variable_index, int production_index) -> const Production & {
      return grammar.variables[variable_index].productions[production_index];
    };

    ParseItemSet item_set({
      {
        ParseItem(Symbol::non_terminal(0), production(0, 0), 0),
        LookaheadSet({ Symbol::terminal(10) }),
      }
    });

    ParseItemSetBuilder item_set_builder(grammar, lexical_grammar);
    item_set_builder.apply_transitive_closure(&item_set);

    AssertThat(item_set, Equals(ParseItemSet({
      {
        ParseItem(Symbol::non_terminal(0), production(0, 0), 0),
        LookaheadSet({ Symbol::terminal(10) })
      },
      {
        ParseItem(Symbol::non_terminal(1), production(1, 0), 0),
        LookaheadSet({ Symbol::terminal(11) })
      },
      {
        ParseItem(Symbol::non_terminal(1), production(1, 1), 0),
        LookaheadSet({ Symbol::terminal(11) })
      },
    })));
  });
});

END_TEST
