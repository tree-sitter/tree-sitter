#ifndef HELPERS_SCOPE_SEQUENCE_H_
#define HELPERS_SCOPE_SEQUENCE_H_

#include <string>
#include <vector>
#include "tree_sitter/runtime.h"

typedef std::string Scope;
typedef std::vector<Scope> ScopeStack;
typedef std::vector<ScopeStack> ScopeSequence;

ScopeSequence build_scope_sequence(TSDocument *document, const std::string &text);

void verify_changed_ranges(const ScopeSequence &old, const ScopeSequence &new_sequence, const std::string &text, TSRange *ranges, size_t range_count);

#endif  // HELPERS_SCOPE_SEQUENCE_H_
