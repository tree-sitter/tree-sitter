#include "compiler_spec_helper.h"
#include "compiler/prepare_grammar/parse_regex.h"

START_TEST

using namespace rules;
using prepare_grammar::parse_regex;

describe("parsing regex patterns", []() {
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
            CharacterSet({'\n'}).complement().copy()
        },

        {
            "character classes",
            "\\w-\\d",
            seq({
                character({ {'a', 'z'}, {'A', 'Z'}, {'0', '9'} }),
                character({ '-' }),
                character({ {'0', '9'} }) })
        },

        {
            "choices",
            "ab|cd|ef",
            choice({
                seq({
                    character({ 'a' }),
                    character({ 'b' }),
                }),
                seq({
                    character({ 'c' }),
                    character({ 'd' })
                }),
                seq({
                    character({ 'e' }),
                    character({ 'f' })
                })
            })
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
            character({ {'1', '3'}, {'a', 'd'}, { 'A', 'D' }, })
        },

        {
            "negated characters",
            "[^a\\d]",
            character({ {'a'}, {'0', '9'} }, false)
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
                    seq({ character({ '\\' }), character({ 'x' }) })
                })),
                character({ 'x' })
            })
        },

        {
            "choices in sequences",
            "(a|b)cd",
            seq({
                choice({
                    character({ 'a' }),
                    character({ 'b' }),
                }),
                character({ 'c' }),
                character({ 'd' })
            })
        },

        {
            "escaped parentheses",
            "a\\(b",
            seq({
                character({ 'a' }),
                character({ '(' }),
                character({ 'b' })
            })
        },

        {
            "escaped periods",
            "a\\.",
            seq({
                character({ 'a' }),
                character({ '.' })
            })
        },

        {
            "plus repeats",
            "(ab)+(cd)+",
            seq({
                seq({
                    seq({ character({ 'a' }), character({ 'b' }) }),
                    repeat(seq({ character({ 'a' }), character({ 'b' }) })),
                }),
                seq({
                    seq({ character({ 'c' }), character({ 'd' }) }),
                    repeat(seq({ character({ 'c' }), character({ 'd' }) })),
                }),
            })
        },

        {
            "asterix repeats",
            "(ab)*(cd)*",
            seq({
                repeat(seq({ character({ 'a' }), character({ 'b' }) })),
                repeat(seq({ character({ 'c' }), character({ 'd' }) })),
            })
        },

        {
            "optional rules",
            "a(bc)?",
            seq({
                character({ 'a' }),
                choice({
                    seq({ character({ 'b' }), character({ 'c' }) }),
                    blank()
                })
            })
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
            AssertThat(result.second, !Equals((const GrammarError *)nullptr));
            AssertThat(result.second->message, Contains(row.message));
        });
    }
});

END_TEST