#include "compiler/precedence_range.h"

namespace tree_sitter {

PrecedenceRange::PrecedenceRange() : min(0), max(0), empty(true) {}

PrecedenceRange::PrecedenceRange(int min, int max)
    : min(min), max(max), empty(false) {}

PrecedenceRange::PrecedenceRange(int value)
    : min(value), max(value), empty(false) {}

void PrecedenceRange::add(int new_value) {
  if (empty) {
    min = new_value;
    max = new_value;
    empty = false;
  } else {
    if (new_value < min)
      min = new_value;
    else if (new_value > max)
      max = new_value;
  }
}

void PrecedenceRange::add(const PrecedenceRange &other) {
  if (!other.empty) {
    add(other.min);
    add(other.max);
  }
}

bool PrecedenceRange::operator<(const PrecedenceRange &other) const {
  if (empty)
    return !other.empty;
  else
    return (min < other.min && max <= other.min) ||
           (min == other.min && max < other.max);
}

bool PrecedenceRange::operator==(const PrecedenceRange &other) const {
  return (empty == other.empty) && (min == other.min) && (max == other.max);
}

}  // namespace tree_sitter
