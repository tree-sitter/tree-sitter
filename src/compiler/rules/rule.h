#ifndef __TreeSitter__rule__
#define __TreeSitter__rule__

#include <string>

namespace tree_sitter {
    namespace rules {
        class Visitor;

        class Rule {
        public:
            virtual bool operator==(const Rule& other) const = 0;
            virtual size_t hash_code() const = 0;
            virtual std::string to_string() const = 0;
            virtual void accept(Visitor &visitor) const = 0;
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
            return rule.hash_code();
        }
    };
}

#endif