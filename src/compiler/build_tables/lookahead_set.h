#ifndef COMPILER_BUILD_TABLES_LOOKAHEAD_SET_H_
#define COMPILER_BUILD_TABLES_LOOKAHEAD_SET_H_

#include <set>
#include <memory>
#include "compiler/rules/symbol.h"

namespace tree_sitter {
namespace build_tables {

class LookaheadSet {
 public:
  LookaheadSet();
  explicit LookaheadSet(const std::set<rules::Symbol::Index> &);

  bool empty() const;
  bool operator==(const LookaheadSet &) const;
  bool contains(const rules::Symbol::Index &) const;
  bool insert_all(const LookaheadSet &);
  bool insert(const rules::Symbol::Index &);

  std::shared_ptr<std::set<rules::Symbol::Index>> entries;
};

}  // namespace build_tables
}  // namespace tree_sitter

#endif  // COMPILER_BUILD_TABLES_LOOKAHEAD_SET_H_
