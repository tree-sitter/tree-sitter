#ifndef __TreeSitter__grammar__
#define __TreeSitter__grammar__

#include <unordered_map>
#include <vector>
#include "rules.h"

namespace tree_sitter {
    class Grammar {
        typedef std::initializer_list<std::pair<const std::string, const rules::rule_ptr>> rule_map_init_list;
    public:
        Grammar(const rule_map_init_list &rules);
        Grammar(std::string start_rule_name, const std::unordered_map<std::string, const rules::rule_ptr> &rules);
        const rules::rule_ptr rule(const std::string &) const;
        const std::string start_rule_name;
        std::vector<std::string> rule_names() const;
        bool operator==(const Grammar &other) const;
        bool has_definition(const rules::Symbol &symbol) const;

        const std::unordered_map<std::string, const rules::rule_ptr> rules;
    };
    
    std::ostream& operator<<(std::ostream &stream, const Grammar &grammar);
}

#endif
