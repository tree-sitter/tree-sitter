#ifndef COMPILER_BUILD_TABLES_GET_METADATA_H_
#define COMPILER_BUILD_TABLES_GET_METADATA_H_

#include "compiler/rules/metadata.h"
#include "tree_sitter/compiler.h"

namespace tree_sitter {
namespace build_tables {

struct MetadataRange {
  MetadataRange() : min(0), max(0) {}
  MetadataRange(int min, int max) : min(min), max(max) {}

  bool operator==(const MetadataRange &other) const {
    return min == other.min && max == other.max;
  }

  int min;
  int max;
};

std::ostream &operator<<(std::ostream &stream, const MetadataRange &range);

MetadataRange get_metadata(const rule_ptr &, rules::MetadataKey);

}  // namespace build_tables
}  // namespace tree_sitter

#endif  // COMPILER_BUILD_TABLES_GET_METADATA_H_
