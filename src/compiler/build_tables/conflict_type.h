#ifndef COMPILER_BUILD_TABLES_CONFLICT_TYPE_H_
#define COMPILER_BUILD_TABLES_CONFLICT_TYPE_H_

namespace tree_sitter {
namespace build_tables {

enum ConflictType {
  ConflictTypeNone,
  ConflictTypeResolved,
  ConflictTypeUnresolved
};

}  // namespace build_tables
}  // namespace tree_sitter

#endif  // COMPILER_BUILD_TABLES_CONFLICT_TYPE_H_
