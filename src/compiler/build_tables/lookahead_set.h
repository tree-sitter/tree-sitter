#ifndef COMPILER_BUILD_TABLES_LOOKAHEAD_SET_H_
#define COMPILER_BUILD_TABLES_LOOKAHEAD_SET_H_

#include <vector>
#include "compiler/rule.h"

namespace tree_sitter {
namespace build_tables {

class LookaheadSet {
  std::vector<bool> terminal_bits;
  std::vector<bool> external_bits;
  bool eof = false;

 public:
  LookaheadSet();
  explicit LookaheadSet(const std::vector<rules::Symbol> &);

  bool empty() const;
  size_t size() const;
  bool operator==(const LookaheadSet &) const;
  bool contains(const rules::Symbol &) const;
  bool insert_all(const LookaheadSet &);
  bool insert(const rules::Symbol &);
  bool remove(const rules::Symbol &);
  void clear();
  bool intersects(const LookaheadSet &) const;

  template <typename Callback>
  void for_each(const Callback &callback) const {
    for (auto begin = external_bits.begin(),
         end = external_bits.end(),
         iter = begin;
         iter != end;
         ++iter) {
      if (*iter) {
        if (!callback(rules::Symbol::external(iter - begin))) return;
      }
    }

    if (eof) {
      if (!callback(rules::END_OF_INPUT())) return;
    }

    for (auto begin = terminal_bits.begin(),
         end = terminal_bits.end(),
         iter = begin;
         iter != end;
         ++iter) {
      if (*iter) {
        if (!callback(rules::Symbol::terminal(iter - begin))) return;
      }
    }
  }

  template <typename Callback>
  void for_each_difference(const LookaheadSet &other, const Callback &callback) const {
    auto end = external_bits.end();
    auto begin = external_bits.begin();
    auto other_end = other.external_bits.end();
    auto other_begin = other.external_bits.begin();
    auto common_end = other.external_bits.size() < external_bits.size() ?
      begin + other.external_bits.size() :
      end;
    auto iter = begin;
    auto other_iter = other_begin;
    for (; iter != common_end; ++iter, ++other_iter) {
      if (*iter) {
        if (!*other_iter && !callback(true, rules::Symbol::external(iter - begin))) return;
      } else if (*other_iter) {
        if (!callback(false, rules::Symbol::external(iter - begin))) return;
      }
    }
    for (; iter < end; ++iter) {
      if (*iter && !callback(true, rules::Symbol::external(iter - begin))) return;
    }
    for (; other_iter < other_end; ++other_iter) {
      if (*other_iter && !callback(false, rules::Symbol::external(other_iter - other_begin))) return;
    }

    if (eof) {
      if (!other.eof && !callback(true, rules::END_OF_INPUT())) return;
    } else if (other.eof) {
      if (!callback(false, rules::END_OF_INPUT())) return;
    }

    end = terminal_bits.end();
    begin = terminal_bits.begin();
    other_end = other.terminal_bits.end();
    other_begin = other.terminal_bits.begin();
    common_end = other.terminal_bits.size() < terminal_bits.size() ?
      begin + other.terminal_bits.size() :
      end;
    iter = begin;
    other_iter = other_begin;
    for (; iter != common_end; ++iter, ++other_iter) {
      if (*iter) {
        if (!*other_iter && !callback(true, rules::Symbol::terminal(iter - begin))) return;
      } else if (*other_iter) {
        if (!callback(false, rules::Symbol::terminal(iter - begin))) return;
      }
    }
    for (; iter < end; ++iter) {
      if (*iter && !callback(true, rules::Symbol::terminal(iter - begin))) return;
    }
    for (; other_iter < other_end; ++other_iter) {
      if (*other_iter && !callback(false, rules::Symbol::terminal(other_iter - other_begin))) return;
    }
  }
};

}  // namespace build_tables
}  // namespace tree_sitter

#endif  // COMPILER_BUILD_TABLES_LOOKAHEAD_SET_H_
