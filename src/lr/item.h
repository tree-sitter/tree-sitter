#ifndef __TreeSitter__item__
#define __TreeSitter__item__

#include <string>
#include "rule.h"
#include "transition_map.h"

namespace tree_sitter {
    namespace lr {
        class Item {
        public:
            Item(const std::string &rule_name, rules::rule_ptr rule, int consumed_sym_count);
            TransitionMap<Item> transitions() const;
        private:
            std::string rule_name;
            rules::rule_ptr rule;
            int consumed_sym_count;
        };
        
        typedef std::shared_ptr<Item> item_ptr;
    }
}

#endif