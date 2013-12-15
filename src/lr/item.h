#ifndef __TreeSitter__item__
#define __TreeSitter__item__

#include <string>
#include "rule.h"
#include "transition_map.h"

namespace tree_sitter {
    class Grammar;
    
    namespace lr {
        class Item {
        public:
            Item(const std::string &rule_name, const rules::rule_ptr rule, int consumed_sym_count);
            static Item at_beginning_of_rule(const std::string &rule_name, const Grammar &grammar);

            TransitionMap<Item> transitions() const;
            std::vector<rules::sym_ptr> next_symbols() const;
            bool operator==(const Item &other) const;
            bool is_done() const;

            const std::string rule_name;
            const rules::rule_ptr rule;
            const int consumed_sym_count;
        };
        
        typedef std::shared_ptr<const Item> item_ptr;
        std::ostream& operator<<(std::ostream &stream, const Item &item);
        
    }
}

namespace std {
    template<>
    struct hash<tree_sitter::lr::Item> {
        size_t operator()(const tree_sitter::lr::Item &item) {
            return
                hash<std::string>()(item.rule_name) ^
                hash<tree_sitter::rules::Rule>()(*item.rule) ^
                hash<int>()(item.consumed_sym_count);
        }
    };
}

#endif
