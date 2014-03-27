#ifndef COMPILER_BUILD_TABLES_ITEM_H_
#define COMPILER_BUILD_TABLES_ITEM_H_

#include <unordered_set>
#include <string>
#include <vector>
#include "compiler/rules/symbol.h"

namespace tree_sitter {
    class Grammar;

    namespace build_tables {
        class Item {
        public:
            Item(const rules::Symbol &lhs, const rules::rule_ptr rule);
            bool is_done() const;

            const rules::Symbol lhs;
            const rules::rule_ptr rule;
        };

        class LexItem : public Item {
        public:
            LexItem(const rules::Symbol &lhs, const rules::rule_ptr rule);
            bool operator==(const LexItem &other) const;
        };

        class ParseItem : public Item {
        public:
            ParseItem(const rules::Symbol &lhs,
                      const rules::rule_ptr rule,
                      const size_t consumed_symbol_count,
                      const rules::Symbol &lookahead_sym);
            bool operator==(const ParseItem &other) const;

            const size_t consumed_symbol_count;
            const rules::Symbol lookahead_sym;
        };

        typedef std::unordered_set<ParseItem> ParseItemSet;
        typedef std::unordered_set<LexItem> LexItemSet;

        std::ostream& operator<<(std::ostream &stream, const LexItem &item);
        std::ostream& operator<<(std::ostream &stream, const ParseItem &item);
    }
}

namespace std {
    template<>
    struct hash<tree_sitter::build_tables::LexItem> {
        size_t operator()(const tree_sitter::build_tables::Item &item) const {
            return
                hash<tree_sitter::rules::Symbol>()(item.lhs) ^
                hash<tree_sitter::rules::rule_ptr>()(item.rule);
        }
    };

    template<>
    struct hash<tree_sitter::build_tables::ParseItem> {
        size_t operator()(const tree_sitter::build_tables::ParseItem &item) const {
            return
            hash<string>()(item.lhs.name) ^
            hash<tree_sitter::rules::rule_ptr>()(item.rule) ^
            hash<size_t>()(item.consumed_symbol_count) ^
            hash<string>()(item.lookahead_sym.name);
        }
    };

    template<typename T>
    struct hash<const unordered_set<T>> {
        size_t operator()(const unordered_set<T> &set) const {
            size_t result = hash<size_t>()(set.size());
            for (auto item : set)
                result ^= hash<T>()(item);
            return result;
        }
    };
}

#endif  // COMPILER_BUILD_TABLES_ITEM_H_
