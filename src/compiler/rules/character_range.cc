#include "compiler/rules/character_range.h"
#include <algorithm>
#include <string>

namespace tree_sitter {
namespace rules {

using std::ostream;
using std::string;
using std::to_string;

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

string escape_character(uint32_t input) {
  if (input >= 255)
    return to_string(input);

  switch (input) {
    case '\0':
      return "\\0";
    case '\n':
      return "\\n";
    case '\r':
      return "\\r";
    case '\t':
      return "\\t";
    default:
      return string() + static_cast<char>(input);
  }
}

string CharacterRange::to_string() const {
  if (min == max)
    return escape_character(min);
  else
    return string() + escape_character(min) + "-" + escape_character(max);
}

ostream &operator<<(ostream &stream, const CharacterRange &range) {
  return stream << range.to_string();
}

}  // namespace rules
}  // namespace tree_sitter
