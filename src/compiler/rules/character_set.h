#ifndef COMPILER_RULES_CHARACTER_SET_H_
#define COMPILER_RULES_CHARACTER_SET_H_

#include <stdint.h>
#include <set>
#include <string>
#include <utility>
#include <vector>
#include "compiler/rule.h"
#include "compiler/rules/character_range.h"

namespace tree_sitter {
namespace rules {

class CharacterSet : public Rule {
 public:
  CharacterSet();

  CharacterSet &include_all();
  CharacterSet &include(uint32_t c);
  CharacterSet &include(uint32_t min, uint32_t max);
  CharacterSet &exclude(uint32_t c);
  CharacterSet &exclude(uint32_t min, uint32_t max);

  bool operator==(const Rule &other) const;
  bool operator<(const CharacterSet &) const;
  size_t hash_code() const;
  rule_ptr copy() const;
  std::string to_string() const;
  void accept(Visitor *visitor) const;

  void add_set(const CharacterSet &other);
  CharacterSet remove_set(const CharacterSet &other);
  bool is_empty() const;

  std::vector<CharacterRange> included_ranges() const;
  std::vector<CharacterRange> excluded_ranges() const;

  bool includes_all;
  std::set<uint32_t> included_chars;
  std::set<uint32_t> excluded_chars;
};

}  // namespace rules
}  // namespace tree_sitter

namespace std {

template <>
struct hash<tree_sitter::rules::CharacterSet> {
  size_t operator()(const tree_sitter::rules::CharacterSet &rule) const {
    return rule.hash_code();
  }
};

}  // namespace std

#endif  // COMPILER_RULES_CHARACTER_SET_H_
