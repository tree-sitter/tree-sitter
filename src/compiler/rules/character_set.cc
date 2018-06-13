#include "compiler/rules/character_set.h"

using std::set;
using std::vector;

namespace tree_sitter {
namespace rules {

static void add_range(set<uint32_t> *characters, uint32_t min, uint32_t max) {
  for (uint32_t c = min; c <= max; c++) {
    characters->insert(c);
  }
}

static void remove_range(set<uint32_t> *characters, uint32_t min, uint32_t max) {
  for (uint32_t c = min; c <= max; c++) {
    characters->erase(c);
  }
}

static set<uint32_t> remove_chars(set<uint32_t> *left, const set<uint32_t> &right) {
  set<uint32_t> result;
  for (uint32_t c : right) {
    if (left->erase(c)) {
      result.insert(c);
    }
  }
  return result;
}

static set<uint32_t> add_chars(set<uint32_t> *left, const set<uint32_t> &right) {
  set<uint32_t> result;
  for (uint32_t c : right) {
    if (left->insert(c).second) {
      result.insert(c);
    }
  }
  return result;
}

static vector<CharacterRange> consolidate_ranges(const set<uint32_t> &characters) {
  vector<CharacterRange> result;
  for (uint32_t c : characters) {
    if (!result.empty() && result.back().max == c - 1) {
      result.back().max = c;
    } else {
      result.push_back(CharacterRange(c));
    }
  }
  return result;
}

CharacterSet::CharacterSet() : includes_all(false) {}

CharacterSet::CharacterSet(const set<uint32_t> &chars) : included_chars(chars), includes_all(false) {}

bool CharacterSet::operator==(const CharacterSet &other) const {
  return includes_all == other.includes_all &&
         included_chars == other.included_chars &&
         excluded_chars == other.excluded_chars;
}

bool CharacterSet::operator<(const CharacterSet &other) const {
  if (!includes_all && other.includes_all) return true;
  if (includes_all && !other.includes_all) return false;
  if (includes_all) {
    if (excluded_chars.size() > other.excluded_chars.size()) return true;
    if (excluded_chars.size() < other.excluded_chars.size()) return false;
    return excluded_chars < other.excluded_chars;
  } else {
    if (included_chars.size() < other.included_chars.size()) return true;
    if (included_chars.size() > other.included_chars.size()) return false;
    return included_chars < other.included_chars;
  }
}

CharacterSet &CharacterSet::include_all() {
  includes_all = true;
  included_chars = {};
  excluded_chars = { 0 };
  return *this;
}

CharacterSet &CharacterSet::include(uint32_t min, uint32_t max) {
  if (includes_all)
    remove_range(&excluded_chars, min, max);
  else
    add_range(&included_chars, min, max);
  return *this;
}

CharacterSet &CharacterSet::exclude(uint32_t min, uint32_t max) {
  if (includes_all)
    add_range(&excluded_chars, min, max);
  else
    remove_range(&included_chars, min, max);
  return *this;
}

CharacterSet &CharacterSet::include(uint32_t c) {
  return include(c, c);
}

CharacterSet &CharacterSet::exclude(uint32_t c) {
  return exclude(c, c);
}

bool CharacterSet::is_empty() const {
  return !includes_all && included_chars.empty();
}

void CharacterSet::add_set(const CharacterSet &other) {
  if (includes_all) {
    if (other.includes_all) {
      excluded_chars = remove_chars(&excluded_chars, other.excluded_chars);
    } else {
      remove_chars(&excluded_chars, other.included_chars);
    }
  } else {
    if (other.includes_all) {
      includes_all = true;
      for (uint32_t c : other.excluded_chars)
        if (!included_chars.count(c))
          excluded_chars.insert(c);
      included_chars.clear();
    } else {
      included_chars.insert(other.included_chars.begin(), other.included_chars.end());
    }
  }
}

CharacterSet CharacterSet::remove_set(const CharacterSet &other) {
  CharacterSet result;
  if (includes_all) {
    if (other.includes_all) {
      result.includes_all = true;
      result.excluded_chars = excluded_chars;
      included_chars = add_chars(&result.excluded_chars, other.excluded_chars);
      excluded_chars = {};
      includes_all = false;
    } else {
      result.included_chars = add_chars(&excluded_chars, other.included_chars);
    }
  } else {
    if (other.includes_all) {
      result.included_chars = included_chars;
      included_chars =
        remove_chars(&result.included_chars, other.excluded_chars);
    } else {
      result.included_chars =
        remove_chars(&included_chars, other.included_chars);
    }
  }
  return result;
}

bool CharacterSet::intersects(const CharacterSet &other) const {
  CharacterSet copy(*this);
  return !copy.remove_set(other).is_empty();
}

CharacterSet CharacterSet::intersection(const CharacterSet &other) const {
  CharacterSet copy(*this);
  return copy.remove_set(other);
}

vector<CharacterRange> CharacterSet::included_ranges() const {
  return consolidate_ranges(included_chars);
}

vector<CharacterRange> CharacterSet::excluded_ranges() const {
  return consolidate_ranges(excluded_chars);
}

}  // namespace rules
}  // namespace tree_sitter
