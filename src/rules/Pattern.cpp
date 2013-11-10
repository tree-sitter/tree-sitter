#include "Pattern.h"
#include "transition_map.h"

namespace tree_sitter {
    namespace rules {
        Pattern::Pattern(const std::string &string) : value(string) {};
        Pattern::Pattern(const char *string) : value(string) {};

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
