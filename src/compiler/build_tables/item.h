#ifndef __TreeSitter__item__
#define __TreeSitter__item__

#include <string>
#include "rule.h"
#include <set>
#include "symbol.h"
#include <vector>

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
            bool operator<(const LexItem &other) const;
            bool operator==(const LexItem &other) const;
        };

        class ParseItem : public Item {
        public:
            ParseItem(const rules::Symbol &lhs, const rules::rule_ptr rule, const std::vector<bool> &consumed_symbols, const rules::Symbol &lookahead_sym);
            bool operator<(const ParseItem &other) const;
            bool operator==(const ParseItem &other) const;

            const std::vector<bool> consumed_symbols;
            const rules::Symbol lookahead_sym;
        };

        typedef std::set<ParseItem> ParseItemSet;
        typedef std::set<LexItem> LexItemSet;
        
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
                hash<tree_sitter::rules::Rule>()(*item.rule);
        }
    };

    template<>
    struct hash<tree_sitter::build_tables::ParseItem> {
        size_t operator()(const tree_sitter::build_tables::ParseItem &item) const {
            return
            hash<string>()(item.lhs.name) ^
            hash<tree_sitter::rules::Rule>()(*item.rule) ^
            hash<size_t>()(item.consumed_symbols.size()) ^
            hash<string>()(item.lookahead_sym.name);
        }
    };
    
    template<typename T>
    struct hash<const set<T>> {
        size_t operator()(const set<T> &set) const {
            size_t result = hash<size_t>()(set.size());
            for (auto item : set)
                result ^= hash<T>()(item);
            return result;
        }
    };
}


#endif
