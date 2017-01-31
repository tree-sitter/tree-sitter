#include "spec_helper.h"
#include "compiler/prepare_grammar/parse_regex.h"
#include "helpers/equals_pointer.h"
#include "helpers/rule_helpers.h"

START_TEST

using namespace rules;
using prepare_grammar::parse_regex;

describe("parse_regex", []() {
  struct ValidInputRow {
    string description;
    string pattern;
    rule_ptr rule;
  };

  vector<ValidInputRow> valid_inputs = {
    {
      "character sets",
      "[aAeE]",
      character({ 'a', 'A', 'e', 'E' })
    },

    {
      "'.' characters as wildcards",
      ".",
      character({ '\n' }, false)
    },

    {
      "character classes",
      "\\w-\\d-\\s-\\S",
      seq({
        character({
          'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
          'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
          'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
          'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
          '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '_' }),
        character({ '-' }),
        character({ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' }),
        character({ '-' }),
        character({ ' ', '\t', '\r', '\n' }),
        character({ '-' }),
        character({ ' ', '\t', '\r', '\n' }, false)
      })
    },

    {
      "choices",
      "ab|cd|ef",
      choice({
        seq({
          character({ 'a' }),
          character({ 'b' }) }),
        seq({
          character({ 'c' }),
          character({ 'd' }) }),
        seq({
          character({ 'e' }),
          character({ 'f' }) }) })
    },

    {
      "simple sequences",
      "abc",
      seq({
        character({ 'a' }),
        character({ 'b' }),
        character({ 'c' }) })
    },

    {
      "character ranges",
      "[12a-dA-D3]",
      character({
        '1', '2', '3',
        'a', 'b', 'c', 'd',
        'A', 'B', 'C', 'D' })
    },

    {
      "negated characters",
      "[^a\\d]",
      character({ 'a', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' }, false)
    },

    {
      "backslashes",
      "\\\\",
      character({ '\\' })
    },

    {
      "character groups in sequences",
      "x([^x]|\\\\x)*x",
      seq({
        character({ 'x' }),
        repeat(choice({
          character({ 'x' }, false),
          seq({ character({ '\\' }), character({ 'x' }) }) })),
        character({ 'x' }) })
    },

    {
      "choices in sequences",
      "(a|b)cd",
      seq({
        choice({
          character({ 'a' }),
          character({ 'b' }) }),
        character({ 'c' }),
        character({ 'd' }) })
    },

    {
      "escaped parentheses",
      "a\\(b",
      seq({
        character({ 'a' }),
        character({ '(' }),
        character({ 'b' }) })
    },

    {
      "escaped periods",
      "a\\.",
      seq({
        character({ 'a' }),
        character({ '.' }) })
    },

    {
      "escaped characters",
      "\\t\\n\\r",
      seq({
        character({ '\t' }),
        character({ '\n' }),
        character({ '\r' }) })
    },

    {
      "plus repeats",
      "(ab)+(cd)+",
      seq({
        repeat1(seq({ character({ 'a' }), character({ 'b' }) })),
        repeat1(seq({ character({ 'c' }), character({ 'd' }) })) })
    },

    {
      "asterix repeats",
      "(ab)*(cd)*",
      seq({
        repeat(seq({ character({ 'a' }), character({ 'b' }) })),
        repeat(seq({ character({ 'c' }), character({ 'd' }) })) })
    },

    {
      "optional rules",
      "a(bc)?",
      seq({
        character({ 'a' }),
        choice({
          seq({ character({ 'b' }), character({ 'c' }) }),
          blank() }) })
    },

    {
      "choices containing negated character classes",
      "/([^/]|(\\\\/))*/",
      seq({
        character({ '/' }),
        repeat(choice({
          character({ '/' }, false),
          seq({ character({ '\\' }), character({ '/' }) }) })),
        character({ '/' }), }),
    },
  };

  struct InvalidInputRow {
    string description;
    string pattern;
    const char *message;
  };

  vector<InvalidInputRow> invalid_inputs = {
    {
      "mismatched open parens",
      "(a",
      "unmatched open paren",
    },
    {
      "mismatched nested open parens",
      "((a) (b)",
      "unmatched open paren",
    },
    {
      "mismatched close parens",
      "a)",
      "unmatched close paren",
    },
    {
      "mismatched nested close parens",
      "((a) b))",
      "unmatched close paren",
    },
    {
      "mismatched brackets for character classes",
      "[a",
      "unmatched open square bracket",
    },
    {
      "mismatched brackets for character classes",
      "a]",
      "unmatched close square bracket",
    },
  };

  for (auto &row : valid_inputs) {
    it(("parses " + row.description).c_str(), [&]() {
      auto result = parse_regex(row.pattern);
      AssertThat(result.first, EqualsPointer(row.rule));
    });
  }

  for (auto &row : invalid_inputs) {
    it(("handles invalid regexes with " + row.description).c_str(), [&]() {
      auto result = parse_regex(row.pattern);
      AssertThat(result.second.type, Equals(TSCompileErrorTypeInvalidRegex));
      AssertThat(result.second.message, Contains(row.message));
    });
  }
});

END_TEST
