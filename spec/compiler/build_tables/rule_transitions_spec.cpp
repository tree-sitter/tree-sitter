#include "compiler_spec_helper.h"
#include "build_tables/rule_transitions.h"

using namespace rules;
using namespace build_tables;

template<typename K>
class rule_map : public map<K, rule_ptr> {
public:
    bool operator==(const map<K, rule_ptr> &other) const {
        if (this->size() != other.size()) return false;
        for (const auto &pair : *this) {
            auto other_pair = other.find(pair.first);
            if (other_pair == other.end()) return false;
            if (!pair.second->operator==(*other_pair->second)) return false;
        }
        return true;
    }

    rule_map(const initializer_list<pair<const K, rule_ptr>> &list) : map<K, rule_ptr>(list) {}
};

START_TEST

describe("rule transitions", []() {
    it("handles symbols", [&]() {
        AssertThat(
            sym_transitions(sym("1")),
            Equals(rule_map<Symbol>({
                { Symbol("1"), blank() }
            })));
    });

    it("handles choices", [&]() {
        AssertThat(
            sym_transitions(choice({ sym("1"), sym("2") })),
            Equals(rule_map<Symbol>({
                { Symbol("1"), blank() },
                { Symbol("2"), blank() }
            })));
    });

    it("handles sequences", [&]() {
        AssertThat(
            sym_transitions(seq({ sym("1"), sym("2") })),
            Equals(rule_map<Symbol>({
                { Symbol("1"), sym("2") }
            })));
    });

    it("handles long sequences", [&]() {
        AssertThat(
            sym_transitions(seq({
                sym("1"),
                sym("2"),
                sym("3"),
                sym("4")
            })),
            Equals(rule_map<Symbol>({
                { Symbol("1"), seq({ sym("2"), sym("3"), sym("4") }) }
            })));
    });

    it("handles sequences whose left sides can be blank", [&]() {
        AssertThat(
            sym_transitions(seq({
                choice({
                    sym("1"),
                    blank(),
                }),
                seq({
                    sym("1"),
                    sym("2")
                })
            })), Equals(rule_map<Symbol>({
                { Symbol("1"), choice({ seq({ sym("1"), sym("2") }), sym("2"), }) }
            })));
    });

    it("handles choices with common starting symbols", [&]() {
        AssertThat(
            sym_transitions(
                choice({
                    seq({ sym("1"), sym("2") }),
                    seq({ sym("1"), sym("3") }) })),
            Equals(rule_map<Symbol>({
                { Symbol("1"), choice({ sym("2"), sym("3") }) }
            })));
    });

    it("handles characters", [&]() {
        AssertThat(
            char_transitions(character({ '1' })),
            Equals(rule_map<CharacterSet>({
                { CharacterSet({ '1' }), blank() }
            })));
    });

    it("handles strings", [&]() {
        AssertThat(
            char_transitions(str("bad")),
            Equals(rule_map<CharacterSet>({
                { CharacterSet({ 'b' }), seq({ character({ 'a' }), character({ 'd' }) }) }
            })));
    });

    it("handles patterns", [&]() {
        AssertThat(
            char_transitions(pattern("a|b")),
            Equals(rule_map<CharacterSet>({
                { CharacterSet({ 'a' }), blank() },
                { CharacterSet({ 'b' }), blank() }
            })));
    });


    it("handles choices between overlapping character sets", [&]() {
        AssertThat(
            char_transitions(choice({
                seq({
                    character({ {'a', 's'} }),
                    sym("x") }),
                seq({
                    character({ { 'm', 'z' } }),
                    sym("y") }) })),
            Equals(rule_map<CharacterSet>({
                { CharacterSet({ {'a','l'} }), sym("x") },
                { CharacterSet({ {'m','s'} }), choice({ sym("x"), sym("y") }) },
                { CharacterSet({ {'t','z'} }), sym("y") },
            })));
    });

    it("handles repeats", [&]() {
        rule_ptr rule = repeat(str("ab"));
        AssertThat(
            char_transitions(rule),
            Equals(rule_map<CharacterSet>({
                {
                    CharacterSet({ 'a' }),
                    seq({
                        character({ 'b' }),
                        choice({
                            rule,
                            blank()
                        })
                    })
                }})));

        rule = repeat(str("a"));
        AssertThat(
            char_transitions(rule),
            Equals(rule_map<CharacterSet>({
            {
                CharacterSet({ 'a' }),
                choice({
                    rule,
                    blank()
                })
            }})));
    });

    describe("regression tests (somewhat redundant, should maybe be deleted later)", []() {
        it("handles sequences that start with repeating characters", [&]() {
            auto rule = seq({
                choice({
                    repeat(character({ '"' }, false)),
                    blank(),
                }),
                character({ '"' }),
            });

            AssertThat(char_transitions(rule), Equals(rule_map<CharacterSet>({
                { CharacterSet({ '"' }).complement(), seq({
                    choice({
                        repeat(character({ '"' }, false)),
                        blank(),
                    }),
                    character({ '"' }), }) },
                { CharacterSet({ '"' }), blank() },
            })));
        });
    });
});


END_TEST
