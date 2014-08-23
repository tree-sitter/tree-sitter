#ifndef COMPILER_RULES_CHARACTER_RANGE_H_
#define COMPILER_RULES_CHARACTER_RANGE_H_

#include <map>
#include <string>

namespace tree_sitter {
namespace rules {

struct CharacterRange {
  uint32_t min;
  uint32_t max;

  explicit CharacterRange(uint32_t value);
  explicit CharacterRange(uint32_t min, uint32_t max);

  bool operator==(const CharacterRange &other) const;
  bool operator<(const CharacterRange &others) const;
  std::string to_string() const;
};

}  // namespace rules
}  // namespace tree_sitter

#endif  // COMPILER_RULES_CHARACTER_RANGE_H_
