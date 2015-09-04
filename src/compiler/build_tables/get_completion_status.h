#ifndef COMPILER_BUILD_TABLES_GET_COMPLETION_STATUS_H_
#define COMPILER_BUILD_TABLES_GET_COMPLETION_STATUS_H_

#include "tree_sitter/compiler.h"

namespace tree_sitter {
namespace build_tables {

struct CompletionStatus {
  bool is_done;
  int precedence;
  Associativity associativity;
};

CompletionStatus get_completion_status(const rule_ptr &);

}  // namespace build_tables
}  // namespace tree_sitter

#endif  // COMPILER_BUILD_TABLES_GET_COMPLETION_STATUS_H_
