#ifndef __TreeSitter__rule__
#define __TreeSitter__rule__

#include <string>

namespace tree_sitter {
    namespace rules {
        class RuleVisitor;

        class Rule {
        public:
            virtual bool operator==(const Rule& other) const = 0;
            virtual std::string to_string() const = 0;
            virtual void accept(RuleVisitor &visitor) const = 0;
        };
        
        typedef std::shared_ptr<const Rule> rule_ptr;
        std::ostream& operator<<(std::ostream& stream, const Rule &rule);
        std::ostream& operator<<(std::ostream& stream, const rule_ptr &rule);
    }
}

namespace std {
    template<>
    struct hash<tree_sitter::rules::Rule> {
        size_t operator()(const tree_sitter::rules::Rule &rule) {
            return std::hash<std::string>()(rule.to_string());
        }
    };
}

#endif