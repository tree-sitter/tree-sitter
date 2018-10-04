#ifndef COMPILER_BUILD_TABLES_PROPERTY_TABLE_BUILDER_H_
#define COMPILER_BUILD_TABLES_PROPERTY_TABLE_BUILDER_H_

#include <memory>
#include "compiler/property_table.h"

namespace tree_sitter {
namespace build_tables {

PropertyTable build_property_table(const PropertySheet &);

}  // namespace build_tables
}  // namespace tree_sitter

#endif  // COMPILER_BUILD_TABLES_PROPERTY_TABLE_BUILDER_H_
