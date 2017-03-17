#include "compiler/build_tables/lookahead_set.h"
#include <set>
#include <memory>
#include "compiler/rule.h"

namespace tree_sitter {
namespace build_tables {

using std::set;
using std::make_shared;
using rules::Symbol;

LookaheadSet::LookaheadSet() : entries(nullptr) {}

LookaheadSet::LookaheadSet(const set<Symbol> &symbols)
    : entries(make_shared<set<Symbol>>(symbols)) {}

bool LookaheadSet::empty() const {
  return !entries.get() || entries->empty();
}

bool LookaheadSet::operator==(const LookaheadSet &other) const {
  return *entries == *other.entries;
}

bool LookaheadSet::contains(const Symbol &symbol) const {
  return entries->find(symbol) != entries->end();
}

bool LookaheadSet::insert_all(const LookaheadSet &other) {
  if (!other.entries.get())
    return false;
  if (!entries.get())
    entries = make_shared<set<Symbol>>();
  size_t previous_size = entries->size();
  entries->insert(other.entries->begin(), other.entries->end());
  return entries->size() > previous_size;
}

bool LookaheadSet::insert(const Symbol &symbol) {
  if (!entries.get())
    entries = make_shared<set<Symbol>>();
  return entries->insert(symbol).second;
}

}  // namespace build_tables
}  // namespace tree_sitter
