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
          "token_1",
          VariableTypeNamed,
          Rule::seq({
            CharacterSet({ 'a' }),
            CharacterSet({ 'b' }),
            CharacterSet({ 'c' }),
          }),
          false
        },
        LexicalVariable{
          "token_2",
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

    AssertThat(builder->detect_conflict(0, 1), IsFalse());
    AssertThat(builder->detect_conflict(1, 0), IsFalse());
  });

  it("returns true when one token matches a string that the other matches, "
     "plus some addition content that begins with a separator character", [&]() {
    LexicalGrammar grammar{
      {
        LexicalVariable{
          "token_1",
          VariableTypeNamed,
          Rule::repeat(CharacterSet().include_all().exclude('\n')), // regex: /.+/
          false
        },
        LexicalVariable{
          "token_2",
          VariableTypeNamed,
          Rule::seq({ CharacterSet({ 'a' }), CharacterSet({ 'b' }), CharacterSet({ 'c' }) }), // string: 'abc'
          true
        },
      },
      separators
    };

    auto builder = LexTableBuilder::create(grammar);
    AssertThat(builder->detect_conflict(0, 1), IsTrue());
    AssertThat(builder->detect_conflict(1, 0), IsFalse());

    grammar.variables[1].is_string = false;
    AssertThat(builder->detect_conflict(0, 1), IsTrue());
    AssertThat(builder->detect_conflict(1, 0), IsFalse());
  });

  it("returns true when one token matches a string that the other matches, "
     "plus some addition content that matches another one-character token", [&]() {
    LexicalGrammar grammar{
      {
        LexicalVariable{
          "token_1",
          VariableTypeNamed,
          Rule::seq({
            CharacterSet({ '>' }),
            CharacterSet({ '>' }),
          }),
          true
        },
        LexicalVariable{
          "token_2",
          VariableTypeNamed,
          Rule::seq({
            CharacterSet({ '>' }),
          }),
          true
        },
      },
      separators
    };

    auto builder = LexTableBuilder::create(grammar);
    AssertThat(builder->detect_conflict(0, 1), IsTrue());
    AssertThat(builder->detect_conflict(1, 0), IsFalse());
  });
});

END_TEST
