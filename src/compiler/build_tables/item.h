#ifndef __TreeSitter__item__
#define __TreeSitter__item__

#include <string>
#include "rule.h"
#include <set>
#include <unordered_set>

namespace tree_sitter {
    class Grammar;
    
    namespace build_tables {
        class Item {
        public:
            Item(const std::string &rule_name, const rules::rule_ptr rule);
            bool is_done() const;

            const std::string rule_name;
            const rules::rule_ptr rule;
        };

        class LexItem : public Item {
        public:
            LexItem(const std::string &rule_name, const rules::rule_ptr rule);
            bool operator<(const LexItem &other) const;
            bool operator==(const LexItem &other) const;
        };

        class ParseItem : public Item {
        public:
            ParseItem(const std::string &rule_name, const rules::rule_ptr rule, int consumed_sym_count, const std::string &lookahead_sym_name);
            bool operator<(const ParseItem &other) const;
            bool operator==(const ParseItem &other) const;

            const int consumed_sym_count;
            const std::string lookahead_sym_name;
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
                hash<std::string>()(item.rule_name) ^
            hash<tree_sitter::rules::Rule>()(*item.rule);
        }
    };

    template<>
    struct hash<tree_sitter::build_tables::ParseItem> {
        size_t operator()(const tree_sitter::build_tables::ParseItem &item) const {
            return
            hash<std::string>()(item.rule_name) ^
            hash<tree_sitter::rules::Rule>()(*item.rule) ^
            hash<size_t>()(item.consumed_sym_count) ^
            hash<std::string>()(item.lookahead_sym_name);
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
