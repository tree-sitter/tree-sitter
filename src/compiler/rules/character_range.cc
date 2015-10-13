#include "compiler/rules/character_range.h"
#include <string>
#include "compiler/util/string_helpers.h"

namespace tree_sitter {
namespace rules {

using std::string;

CharacterRange::CharacterRange(uint32_t value) : min(value), max(value) {}
CharacterRange::CharacterRange(uint32_t min, uint32_t max)
    : min(min), max(max) {}

bool CharacterRange::operator==(const CharacterRange &other) const {
  return min == other.min && max == other.max;
}

bool CharacterRange::operator<(const CharacterRange &other) const {
  if (min < other.min)
    return true;
  if (min > other.min)
    return false;
  if (max < other.max)
    return true;
  return false;
}

string CharacterRange::to_string() const {
  if (min == max)
    return util::escape_char(min);
  else
    return util::escape_char(min) + "-" + util::escape_char(max);
}

}  // namespace rules
}  // namespace tree_sitter
