#ifndef COMPILER_BUILD_TABLES_GET_METADATA_H_
#define COMPILER_BUILD_TABLES_GET_METADATA_H_

#include "compiler/rules/metadata.h"
#include "tree_sitter/compiler.h"

namespace tree_sitter {
namespace build_tables {

int get_metadata(const rules::rule_ptr &, rules::MetadataKey);

}  // namespace build_tables
}  // namespace tree_sitter

#endif  // COMPILER_BUILD_TABLES_GET_METADATA_H_
