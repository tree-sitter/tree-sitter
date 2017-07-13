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

  template <typename Callback>
  void for_each(const Callback &callback) const {
    for (auto begin = external_bits.begin(),
         end = external_bits.end(),
         iter = begin;
         iter != end;
         ++iter) {
      if (*iter) {
        callback(rules::Symbol::external(iter - begin));
      }
    }

    if (eof) {
      callback(rules::END_OF_INPUT());
    }

    for (auto begin = terminal_bits.begin(),
         end = terminal_bits.end(),
         iter = begin;
         iter != end;
         ++iter) {
      if (*iter) {
        callback(rules::Symbol::terminal(iter - begin));
      }
    }
  }
};

}  // namespace build_tables
}  // namespace tree_sitter

#endif  // COMPILER_BUILD_TABLES_LOOKAHEAD_SET_H_
