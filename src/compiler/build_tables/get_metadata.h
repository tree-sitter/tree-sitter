#ifndef COMPILER_BUILD_TABLES_CHECK_METADATA_
#define COMPILER_BUILD_TABLES_CHECK_METADATA_

#include "compiler/rules/rule.h"
#include "compiler/rules/metadata.h"

namespace tree_sitter {
    namespace build_tables {
        int get_metadata(const rules::rule_ptr &rule, rules::MetadataKey key);
    }
}

#endif  // COMPILER_BUILD_TABLES_CHECK_METADATA_
