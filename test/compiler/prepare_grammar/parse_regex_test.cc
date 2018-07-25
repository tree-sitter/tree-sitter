#include "test_helper.h"
#include "compiler/prepare_grammar/parse_regex.h"

START_TEST

using namespace rules;
using prepare_grammar::parse_regex;

describe("parse_regex", []() {
  struct ValidInputRow {
    string description;
    string pattern;
    Rule rule;
  };

  vector<ValidInputRow> valid_inputs = {
    {
      "character sets",
      "[aAeE]",
      CharacterSet{{ 'a', 'A', 'e', 'E' }}
    },

    {
      "'.' characters as wildcards",
      ".",
      CharacterSet().include_all().exclude('\n')
    },

    {
      "character classes",
      "\\w-\\d-\\s-\\W-\\D-\\S",
      Rule::seq({
        CharacterSet{{
          'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
          'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
          'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
          'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
          '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '_' }},
        CharacterSet{{ '-' }},
        CharacterSet{{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' }},
        CharacterSet{{ '-' }},
        CharacterSet{{ ' ', '\t', '\r', '\n' }},
        CharacterSet{{ '-' }},
        CharacterSet().include_all()
          .exclude('a', 'z')
          .exclude('A', 'Z')
          .exclude('0', '9')
          .exclude('_'),
        CharacterSet{{ '-' }},
        CharacterSet().include_all().exclude('0', '9'),
        CharacterSet{{ '-' }},
        CharacterSet().include_all()
          .exclude(' ')
          .exclude('\t')
          .exclude('\r')
          .exclude('\n')
      })
    },

    {
      "choices",
      "ab|cd|ef",
      Rule::choice({
        Seq{
          CharacterSet{{'a'}},
          CharacterSet{{'b'}}
        },
        Seq{
          CharacterSet{{'c'}},
          CharacterSet{{'d'}}
        },
        Seq{
          CharacterSet{{'e'}},
          CharacterSet{{'f'}}
        }
      })
    },

    {
      "simple sequences",
      "abc",
      Rule::seq({
        CharacterSet{{'a'}},
        CharacterSet{{'b'}},
        CharacterSet{{'c'}}
      })
    },

    {
      "character ranges",
      "[12a-dA-D3]",
      CharacterSet{{
        '1', '2', '3',
        'a', 'b', 'c', 'd',
        'A', 'B', 'C', 'D'
      }}
    },

    {
      "negated characters",
      "[^a\\d]",
      CharacterSet().include_all()
        .exclude('a')
        .exclude('0', '9')
    },

    {
      "backslashes",
      "\\\\",
      CharacterSet{{'\\'}}
    },

    {
      "dashes",
      "a-b",
      Rule::seq({
        CharacterSet{{'a'}},
        CharacterSet{{'-'}},
        CharacterSet{{'b'}}
      })
    },

    {
      "literal dashes in character classes",
      "[a-][\\d-a][\\S-a]",
      Rule::seq({
        CharacterSet{{'a', '-'}},
        CharacterSet().include('0', '9').include('-').include('a'),
        CharacterSet().include_all()
          .exclude(' ')
          .exclude('\t')
          .exclude('\r')
          .exclude('\n')
      })
    },

    {
      "character groups in sequences",
      "x([^x]|\\\\x)*x",
      Rule::seq({
        CharacterSet{{'x'}},
        Rule::choice({
          Repeat{Rule::choice({
            CharacterSet().include_all().exclude('x'),
            Rule::seq({
              CharacterSet{{'\\'}},
              CharacterSet{{'x'}}
            })
          })},
          Blank{}
        }),
        CharacterSet{{'x'}}
      })
    },

    {
      "choices in sequences",
      "(a|b)cd",
      Rule::seq({
        Rule::choice({
          CharacterSet{{'a'}},
          CharacterSet{{'b'}} }),
        CharacterSet{{'c'}},
        CharacterSet{{'d'}} })
    },

    {
      "escaped parentheses",
      "a\\(b",
      Rule::seq({
        CharacterSet{{'a'}},
        CharacterSet{{'('}},
        CharacterSet{{'b'}},
      })
    },

    {
      "escaped brackets",
      "\\[\\]",
      Rule::seq({
        CharacterSet{{'['}},
        CharacterSet{{']'}},
      })
    },

    {
      "escaped brackets in choice",
      "[\\[\\]]",
      CharacterSet{{'[', ']'}}
    },

    {
      "escaped brackets in range",
      "[\\[-\\]]",
      CharacterSet{{'[', '\\', ']'}}
    },

    {
      "escaped characters in ranges",
      "[\\0-\\n]",
      CharacterSet().include(0, '\n')
    },

    {
      "escaped periods",
      "a\\.",
      Rule::seq({
        CharacterSet{{'a'}},
        CharacterSet{{'.'}},
      })
    },

    {
      "escaped characters",
      "\\t\\n\\r",
      Rule::seq({
        CharacterSet{{'\t'}},
        CharacterSet{{'\n'}},
        CharacterSet{{'\r'}},
      })
    },

    {
      "plus repeats",
      "(ab)+(cd)+",
      Rule::seq({
        Repeat{Rule::seq({ CharacterSet{{'a'}}, CharacterSet{{'b'}} })},
        Repeat{Rule::seq({ CharacterSet{{'c'}}, CharacterSet{{'d'}} })},
      })
    },

    {
      "asterix repeats",
      "(ab)*(cd)*",
      Rule::seq({
        Rule::choice({
          Repeat{Rule::seq({ CharacterSet{{'a'}}, CharacterSet{{'b'}} })},
          Blank{},
        }),
        Rule::choice({
          Repeat{Rule::seq({ CharacterSet{{'c'}}, CharacterSet{{'d'}} })},
          Blank{},
        }),
      })
    },

    {
      "optional rules",
      "a(bc)?",
      Rule::seq({
        CharacterSet{{'a'}},
        Rule::choice({
          Rule::seq({
            CharacterSet{{'b'}},
            CharacterSet{{'c'}},
          }),
          Blank{}
        }),
      })
    },

    {
      "choices containing negated character classes",
      "/([^/]|(\\\\/))+/",
      Rule::seq({
        CharacterSet{{'/'}},
        Repeat{Rule::choice({
          CharacterSet().include_all().exclude('/'),
          Rule::seq({
            CharacterSet{{'\\'}},
            CharacterSet{{'/'}},
          }),
        })},
        CharacterSet{{'/'}},
      }),
    },

    {
      "characters with quantifiers",
      "a{3}",
      Rule::seq({
        CharacterSet{{'a'}},
        CharacterSet{{'a'}},
        CharacterSet{{'a'}},
      }),
    },

    {
      "character classes with quantifiers",
      "[a-f]{3}",
      Rule::seq({
        CharacterSet().include('a', 'f'),
        CharacterSet().include('a', 'f'),
        CharacterSet().include('a', 'f'),
      }),
    },

    {
      "characters with open range quantifiers",
      "a{,} b{1,} c{,2}",
      Rule::seq({
        Rule::seq({
          Repeat{CharacterSet{{'a'}}},
        }),
        CharacterSet{{' '}},
        Rule::seq({
          CharacterSet{{'b'}},
          Repeat{CharacterSet{{'b'}}},
        }),
        CharacterSet{{' '}},
        Rule::seq({
          Rule::choice({CharacterSet{{'c'}}, Blank{}}),
          Rule::choice({CharacterSet{{'c'}}, Blank{}}),
        }),
      }),
    },

    {
      "characters with closed range quantifiers",
      "a{2,4}",
      Rule::seq({
        CharacterSet{{'a'}},
        CharacterSet{{'a'}},
        Rule::choice({CharacterSet{{'a'}}, Blank{}}),
        Rule::choice({CharacterSet{{'a'}}, Blank{}}),
      }),
    },

    {
      "curly braces that aren't quantifiers",
      "a{1b} c{2,d}",
      Rule::seq({
        CharacterSet{{'a'}},
        CharacterSet{{'{'}},
        CharacterSet{{'1'}},
        CharacterSet{{'b'}},
        CharacterSet{{'}'}},
        CharacterSet{{' '}},
        CharacterSet{{'c'}},
        CharacterSet{{'{'}},
        CharacterSet{{'2'}},
        CharacterSet{{','}},
        CharacterSet{{'d'}},
        CharacterSet{{'}'}},
      }),
    }
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
    {
      "numbers out of order in range quantifiers",
      "a{3,1}",
      "numbers out of order in {} quantifier",
    },
  };

  for (auto &row : valid_inputs) {
    it(("parses " + row.description).c_str(), [&]() {
      auto result = parse_regex(row.pattern);
      AssertThat(result.first, Equals(row.rule));
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
