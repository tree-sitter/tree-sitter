#include "compiler/compiler_spec_helper.h"
#include "compiler/build_tables/rule_transitions.h"
#include "compiler/rules/metadata.h"

using namespace rules;
using namespace build_tables;

class transition_map : public std::map<CharacterSet, rule_ptr> {
 public:
  bool operator==(const std::map<CharacterSet, rule_ptr> &other) const {
    if (this->size() != other.size()) return false;
    for (const auto &pair : *this) {
      auto other_pair = other.find(pair.first);
      if (other_pair == other.end()) return false;
      if (!pair.second->operator==(*other_pair->second)) return false;
    }
    return true;
  }

  transition_map(const std::initializer_list<std::pair<const CharacterSet, rule_ptr>> &list) :
    std::map<CharacterSet, rule_ptr>(list) {}
};

START_TEST

describe("rule_transitions", []() {
  it("handles single characters", [&]() {
    AssertThat(
      rule_transitions(character({ '1' })),
      Equals(transition_map({
        { CharacterSet().include('1'), blank() }
      })));
  });

  it("handles sequences", [&]() {
    AssertThat(
      rule_transitions(seq({ character({ '1' }), character({ '2' }) })),
      Equals(transition_map({
        { CharacterSet().include('1'), character({ '2' }) }
      })));
  });

  it("handles long sequences", [&]() {
    AssertThat(
      rule_transitions(seq({
        character({ '1' }),
        character({ '2' }),
        character({ '3' }),
        character({ '4' })
      })),
      Equals(transition_map({
        {
          CharacterSet().include('1'),
          seq({ character({ '2' }), character({ '3' }), character({ '4' }) }),
        }
      })));
  });

  it("handles sequences whose left sides can be blank", [&]() {
    AssertThat(
      rule_transitions(seq({
        choice({
          character({ '1' }),
          blank() }),
        seq({
          character({ '1' }),
          character({ '2' }) })
      })), Equals(transition_map({
        {
          CharacterSet().include('1'),
          choice({ seq({ character({ '1' }), character({ '2' }) }), character({ '2' }), }),
        }
      })));
  });

  it("handles choices between overlapping character sets", [&]() {
    AssertThat(
      rule_transitions(choice({
        seq({
          character({ 'a', 'b', 'c', 'd'  }),
          sym("x") }),
        seq({
          character({ 'c', 'd', 'e', 'f' }),
          sym("y") }) })),
      Equals(transition_map({
        { CharacterSet().include('a', 'b'), sym("x") },
        { CharacterSet().include('c', 'd'), choice({ sym("x"), sym("y") }) },
        { CharacterSet().include('e', 'f'), sym("y") },
      })));
  });

  it("handles choices between whitelisted and blacklisted character sets", [&]() {
    AssertThat(
      rule_transitions(seq({
        choice({
          character({ '/' }, false),
          seq({
            character({ '\\' }),
            character({ '/' }) }) }),
        character({ '/' }) })),

      Equals(transition_map({
        { CharacterSet()
            .include_all()
            .exclude('/')
            .exclude('\\'),
          character({ '/' }) },
        { CharacterSet()
            .include('\\'),
          seq({
            choice({
              blank(),
              character({ '/' }) }),
            character({ '/' }) }) },
      })));
  });

  it("handles choices between a subset and a superset of characters", [&]() {
    AssertThat(
      rule_transitions(choice({
        seq({
          character({ 'b', 'c', 'd' }),
          sym("x") }),
        seq({
          character({ 'a', 'b', 'c', 'd', 'e', 'f' }),
          sym("y") }) })),
      Equals(transition_map({
        { CharacterSet().include('b', 'd'), choice({ sym("x"), sym("y") }) },
        { CharacterSet().include('a').include('e', 'f'), sym("y") },
      })));

    AssertThat(
      rule_transitions(choice({
        seq({
          character({ 'a', 'b', 'c', 'd', 'e', 'f' }),
          sym("x") }),
        seq({
          character({ 'b', 'c', 'd' }),
          sym("y") }) })),
      Equals(transition_map({
        { CharacterSet().include('b', 'd'), choice({ sym("x"), sym("y") }) },
        { CharacterSet().include('a').include('e', 'f'), sym("x") },
      })));
  });

  it("handles blanks", [&]() {
    AssertThat(rule_transitions(blank()), Equals(transition_map({})));
  });

  it("handles repeats", [&]() {
    rule_ptr rule = repeat(seq({ character({ 'a' }), character({ 'b' }) }));

    AssertThat(
      rule_transitions(rule),
      Equals(transition_map({
        {
          CharacterSet().include('a'),
          seq({
            character({ 'b' }),
            rule })
        }})));

    rule = repeat(character({ 'a' }));

    AssertThat(
      rule_transitions(rule),
      Equals(transition_map({
        { CharacterSet().include('a'), rule }
      })));
  });
});

END_TEST
