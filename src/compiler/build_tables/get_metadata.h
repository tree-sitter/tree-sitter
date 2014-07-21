#ifndef COMPILER_BUILD_TABLES_GET_METADATA_H_
#define COMPILER_BUILD_TABLES_GET_METADATA_H_

#include "compiler/rules/rule.h"
#include "compiler/rules/metadata.h"

namespace tree_sitter {
namespace build_tables {
int get_metadata(const rules::rule_ptr &rule, rules::MetadataKey key);
}
}

#endif  // COMPILER_BUILD_TABLES_GET_METADATA_H_
