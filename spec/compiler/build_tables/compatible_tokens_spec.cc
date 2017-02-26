#include "spec_helper.h"
#include "compiler/rules/character_set.h"
#include "compiler/build_tables/compatible_tokens.h"
#include "compiler/lexical_grammar.h"
#include "helpers/rule_helpers.h"
#include "helpers/stream_methods.h"
#include "compiler/rules.h"

using namespace rules;
using namespace build_tables;

START_TEST

describe("recovery_tokens(rule)", []() {
  it("includes rules that can only begin and end with an explicit set of characters", [&]() {
    LexicalGrammar grammar;
    grammar.separators = {
      character({ ' ' }),
    };

    grammar.variables = {
      Variable("var0", VariableTypeNamed, character({}, false)),
      Variable("var1", VariableTypeNamed, seq({
        character({ 'a', 'b' }),
        character({}, false),
        character({ 'c', 'd' }),
      })),
    };

    AssertThat(get_compatible_tokens(grammar).recovery_tokens, Equals<set<Symbol>>({ Symbol(1, Symbol::Terminal) }));
  });
});

END_TEST
