#ifndef COMPILER_BUILD_TABLES_PARSE_ITEM_H_
#define COMPILER_BUILD_TABLES_PARSE_ITEM_H_

#include <unordered_set>
#include <string>
#include "compiler/rules/symbol.h"
#include "compiler/build_tables/item.h"
#include "compiler/rules/metadata.h"

namespace tree_sitter {
    namespace build_tables {
        class ParseItem : public Item {
        public:
            ParseItem(const rules::Symbol &lhs,
                      rules::rule_ptr rule,
                      const size_t consumed_symbol_count,
                      const rules::Symbol &lookahead_sym);
            bool operator==(const ParseItem &other) const;
            int precedence() const;

            size_t consumed_symbol_count;
            rules::Symbol lookahead_sym;
        };

        std::ostream& operator<<(std::ostream &stream, const ParseItem &item);

        typedef std::unordered_set<ParseItem> ParseItemSet;
    }
}

namespace std {
    template<>
    struct hash<tree_sitter::build_tables::ParseItem> {
        size_t operator()(const tree_sitter::build_tables::ParseItem &item) const {
            return
            hash<tree_sitter::rules::Symbol>()(item.lhs) ^
            hash<tree_sitter::rules::rule_ptr>()(item.rule) ^
            hash<size_t>()(item.consumed_symbol_count) ^
            hash<tree_sitter::rules::Symbol>()(item.lookahead_sym);
        }
    };

    template<>
    struct hash<const tree_sitter::build_tables::ParseItemSet> {
        size_t operator()(const tree_sitter::build_tables::ParseItemSet &set) const {
            size_t result = hash<size_t>()(set.size());
            for (auto item : set)
                result ^= hash<tree_sitter::build_tables::ParseItem>()(item);
            return result;
        }
    };
}

#endif  // COMPILER_BUILD_TABLES_PARSE_ITEM_H_
