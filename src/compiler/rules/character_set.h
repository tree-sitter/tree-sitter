#ifndef COMPILER_RULES_CHARACTER_SET_H_
#define COMPILER_RULES_CHARACTER_SET_H_

#include <vector>
#include <set>
#include <cstdint>

namespace tree_sitter {
namespace rules {

struct CharacterRange {
  uint32_t min;
  uint32_t max;

  inline explicit CharacterRange(uint32_t value) : min{value}, max{value} {}
  inline CharacterRange(uint32_t min, uint32_t max) : min{min}, max{max} {}

  inline bool operator==(const CharacterRange &other) const {
    return min == other.min && max == other.max;
  }
};

struct CharacterSet {
  CharacterSet();
  CharacterSet(const std::set<uint32_t> &);

  CharacterSet &include_all();
  CharacterSet &include(uint32_t c);
  CharacterSet &include(uint32_t min, uint32_t max);
  CharacterSet &exclude(uint32_t c);
  CharacterSet &exclude(uint32_t min, uint32_t max);

  bool operator==(const CharacterSet &) const;
  bool operator<(const CharacterSet &) const;

  void add_set(const CharacterSet &other);
  CharacterSet remove_set(const CharacterSet &other);
  CharacterSet intersection(const CharacterSet &other) const;
  bool intersects(const CharacterSet &other) const;
  bool is_empty() const;

  std::vector<CharacterRange> included_ranges() const;
  std::vector<CharacterRange> excluded_ranges() const;

  std::set<uint32_t> included_chars;
  std::set<uint32_t> excluded_chars;
  bool includes_all;
};

}  // namespace rules
}  // namespace tree_sitter

#endif  // COMPILER_RULES_CHARACTER_SET_H_
