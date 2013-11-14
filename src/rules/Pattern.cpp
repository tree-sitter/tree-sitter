#include "Pattern.h"
#include "transition_map.h"

namespace tree_sitter {
    namespace rules {
        Pattern::Pattern(const std::string &string) : value(string) {};
        
        pattern_ptr pattern(const std::string &value) {
            return std::make_shared<Pattern>(value);
        }

        TransitionMap<Rule> Pattern::transitions() const {
            return tree_sitter::TransitionMap<Rule>();
        }

        bool Pattern::operator ==(tree_sitter::rules::Rule const &other) const {
            return false;
        }

        std::string Pattern::to_string() const {
            return value;
        }
    }
}
