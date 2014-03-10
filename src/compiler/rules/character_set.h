#ifndef COMPILER_RULES_CHARACTER_SET_H_
#define COMPILER_RULES_CHARACTER_SET_H_

#include <initializer_list>
#include <set>
#include "compiler/rules/rule.h"
#include "compiler/rules/character_range.h"

namespace tree_sitter  {
    namespace rules {
        class CharacterSet : public Rule {
        public:
            CharacterSet();
            CharacterSet(const std::set<CharacterRange> &ranges);
            CharacterSet(const std::initializer_list<CharacterRange> &ranges);

            bool operator==(const Rule& other) const;
            bool operator<(const CharacterSet &) const;
            size_t hash_code() const;
            rule_ptr copy() const;
            std::string to_string() const;
            void accept(Visitor &visitor) const;

            void add_set(const CharacterSet &other);
            CharacterSet remove_set(const CharacterSet &other);
            CharacterSet complement() const;
            CharacterSet intersect(const CharacterSet &) const;
            std::pair<CharacterSet, bool> most_compact_representation() const;
            bool is_empty() const;

            std::set<CharacterRange> ranges;
        };
    }
}

namespace std {
    template<>
    struct hash<tree_sitter::rules::CharacterSet> {
        size_t operator()(const tree_sitter::rules::CharacterSet &rule) const {
            return rule.hash_code();
        }
    };
}

#endif  // COMPILER_RULES_CHARACTER_SET_H_
