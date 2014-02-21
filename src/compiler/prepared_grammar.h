#ifndef __tree_sitter__prepared_grammar__
#define __tree_sitter__prepared_grammar__

#include "tree_sitter/compiler.h"
#include "rules/symbol.h"

namespace tree_sitter {
    class PreparedGrammar : public Grammar {
    public:
        PreparedGrammar(std::string start_rule_name,
                        const std::map<const std::string, const rules::rule_ptr> &rules,
                        const std::map<const std::string, const rules::rule_ptr> &aux_rules);
        PreparedGrammar(std::string start_rule_name,
                        const std::initializer_list<std::pair<const std::string, const rules::rule_ptr>> &rules,
                        const std::initializer_list<std::pair<const std::string, const rules::rule_ptr>> &aux_rules);
        PreparedGrammar(const Grammar &grammar);
            
        bool operator==(const PreparedGrammar &other) const;
        bool has_definition(const rules::Symbol &symbol) const;
        const rules::rule_ptr rule(const rules::Symbol &symbol) const;
        
        const std::map<const std::string, const rules::rule_ptr> aux_rules;
    };
    
    std::ostream& operator<<(std::ostream &stream, const PreparedGrammar &grammar);
    
    std::string compile(const Grammar &grammar, std::string name);
}

#endif
