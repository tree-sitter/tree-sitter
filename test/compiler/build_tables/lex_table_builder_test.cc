#include "test_helper.h"
#include "compiler/lexical_grammar.h"
#include "compiler/build_tables/lex_table_builder.h"

using namespace build_tables;
using namespace rules;

START_TEST

describe("LexTableBuilder::detect_conflict", []() {
  vector<Rule> separators({
    CharacterSet({ ' ', '\t' }),
  });

  it("returns false for tokens that don't match the same string", [&]() {
    auto builder = LexTableBuilder::create(LexicalGrammar{
      {
        LexicalVariable{
          "token_0",
          VariableTypeNamed,
          Rule::seq({
            CharacterSet({ 'a' }),
            CharacterSet({ 'b' }),
            CharacterSet({ 'c' }),
          }),
          false
        },
        LexicalVariable{
          "token_1",
          VariableTypeNamed,
          Rule::seq({
            CharacterSet({ 'b' }),
            CharacterSet({ 'c' }),
            CharacterSet({ 'd' }),
          }),
          false
        },
      },
      separators
    });

    AssertThat(builder->detect_conflict(0, 1, {{}, {}}), IsFalse());
    AssertThat(builder->detect_conflict(1, 0, {{}, {}}), IsFalse());
  });

  it("returns true when the left token can match a string that the right token matches, "
     "plus a separator character", [&]() {
    LexicalGrammar grammar{
      {
        LexicalVariable{
          "token_0",
          VariableTypeNamed,
          Rule::repeat(CharacterSet().include_all().exclude('\n')), // regex: /.+/
          false
        },
        LexicalVariable{
          "token_1",
          VariableTypeNamed,
          Rule::seq({ CharacterSet({ 'a' }), CharacterSet({ 'b' }), CharacterSet({ 'c' }) }), // string: 'abc'
          true
        },
      },
      separators
    };

    auto builder = LexTableBuilder::create(grammar);
    AssertThat(builder->detect_conflict(0, 1, {{}, {}}), IsTrue());
    AssertThat(builder->detect_conflict(1, 0, {{}, {}}), IsFalse());

    grammar.variables[1].is_string = false;
    AssertThat(builder->detect_conflict(0, 1, {{}, {}}), IsTrue());
    AssertThat(builder->detect_conflict(1, 0, {{}, {}}), IsFalse());
  });

  it("returns true when the left token matches a string that the right token matches, "
     "plus the first character of some token that can follow the right token", [&]() {
    LexicalGrammar grammar{
      {
        LexicalVariable{
          "token_0",
          VariableTypeNamed,
          Rule::seq({
            CharacterSet({ '>' }),
            CharacterSet({ '=' }),
          }),
          true
        },
        LexicalVariable{
          "token_1",
          VariableTypeNamed,
          Rule::seq({
            CharacterSet({ '>' }),
          }),
          true
        },
        LexicalVariable{
          "token_2",
          VariableTypeNamed,
          Rule::seq({
            CharacterSet({ '=' }),
          }),
          true
        },
      },
      separators
    };

    // If no tokens can follow token_1, then there's no conflict
    auto builder = LexTableBuilder::create(grammar);
    vector<set<Symbol::Index>> following_tokens_by_token_index(3);
    AssertThat(builder->detect_conflict(0, 1, following_tokens_by_token_index), IsFalse());
    AssertThat(builder->detect_conflict(1, 0, following_tokens_by_token_index), IsFalse());

    // If token_2 can follow token_1, then token_0 conflicts with token_1
    builder = LexTableBuilder::create(grammar);
    following_tokens_by_token_index[1].insert(2);
    AssertThat(builder->detect_conflict(0, 1, following_tokens_by_token_index), IsTrue());
    AssertThat(builder->detect_conflict(1, 0, following_tokens_by_token_index), IsFalse());
  });
});

END_TEST
