#include "compiler/build_tables/lookahead_set.h"
#include <set>
#include <memory>
#include "compiler/rule.h"

namespace tree_sitter {
namespace build_tables {

using std::vector;
using rules::Symbol;

LookaheadSet::LookaheadSet() {}

LookaheadSet::LookaheadSet(const vector<Symbol> &symbols) {
  for (auto symbol : symbols) insert(symbol);
}

bool LookaheadSet::empty() const {
  return terminal_bits.empty() && external_bits.empty() && !eof;
}

bool LookaheadSet::operator==(const LookaheadSet &other) const {
  return
    eof == other.eof &&
    external_bits == other.external_bits &&
    terminal_bits == other.terminal_bits;
}

bool LookaheadSet::contains(const Symbol &symbol) const {
  if (symbol == rules::END_OF_INPUT()) return eof;
  auto &bits = symbol.is_external() ? external_bits : terminal_bits;
  return bits.size() > static_cast<size_t>(symbol.index) && bits[symbol.index];
}

bool LookaheadSet::intersects(const LookaheadSet &other) const {
  bool result = false;
  for_each([&](Symbol symbol) {
    if (other.contains(symbol)) {
      result = true;
      return false;
    }
    return true;
  });
  return result;
}

size_t LookaheadSet::size() const {
  size_t result = 0;
  for (bool bit : external_bits) if (bit) result++;
  for (bool bit : terminal_bits) if (bit) result++;
  if (eof) result++;
  return result;
}

bool LookaheadSet::insert_all(const LookaheadSet &other) {
  bool result = false;

  if (other.eof) {
    if (!eof) {
      eof = true;
      result = true;
    }
  }

  if (other.external_bits.size() > external_bits.size()) {
    external_bits.resize(other.external_bits.size());
  }

  auto iter = external_bits.begin();
  auto other_iter = other.external_bits.begin();
  auto other_end = other.external_bits.end();
  while (other_iter != other_end) {
    if (*other_iter && !*iter) {
      result = true;
      *iter = true;
    }
    ++iter;
    ++other_iter;
  }

  if (other.terminal_bits.size() > terminal_bits.size()) {
    terminal_bits.resize(other.terminal_bits.size());
  }

  iter = terminal_bits.begin();
  other_iter = other.terminal_bits.begin();
  other_end = other.terminal_bits.end();
  while (other_iter != other_end) {
    if (*other_iter && !*iter) {
      result = true;
      *iter = true;
    }
    ++iter;
    ++other_iter;
  }

  return result;
}

bool LookaheadSet::insert(const Symbol &symbol) {
  if (symbol == rules::END_OF_INPUT()) {
    if (!eof) {
      eof = true;
      return true;
    }
    return false;
  }

  auto &bits = symbol.is_external() ? external_bits : terminal_bits;
  if (bits.size() <= static_cast<size_t>(symbol.index)) {
    bits.resize(symbol.index + 1);
  }
  if (!bits[symbol.index]) {
    bits[symbol.index] = true;
    return true;
  }
  return false;
}

bool LookaheadSet::remove(const Symbol &symbol) {
  if (symbol == rules::END_OF_INPUT()) {
    if (eof) {
      eof = false;
      return true;
    }
    return false;
  }

  auto &bits = symbol.is_external() ? external_bits : terminal_bits;
  if (bits.size() > static_cast<size_t>(symbol.index)) {
    if (bits[symbol.index]) {
      bits[symbol.index] = false;
      return true;
    }
  }

  return false;
}

void LookaheadSet::clear() {
  eof = false;
  terminal_bits.clear();
  external_bits.clear();
}

}  // namespace build_tables
}  // namespace tree_sitter
