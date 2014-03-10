#ifndef __TreeSitter__rule__
#define __TreeSitter__rule__

#include <string>
#include <memory>

namespace tree_sitter {
    namespace rules {
        class Visitor;
        class Rule;

        typedef std::shared_ptr<Rule> rule_ptr;

        class Rule {
        public:
            virtual bool operator==(const Rule& other) const = 0;
            bool operator!=(const Rule& other) const;
            virtual size_t hash_code() const = 0;
            virtual rule_ptr copy() const = 0;
            virtual std::string to_string() const = 0;
            virtual void accept(Visitor &visitor) const = 0;
        };

        std::ostream& operator<<(std::ostream& stream, const Rule &rule);
        std::ostream& operator<<(std::ostream& stream, const rule_ptr &rule);
    }
}

namespace std {
    template<>
    struct hash<tree_sitter::rules::rule_ptr> {
        size_t operator()(const tree_sitter::rules::rule_ptr &rule) const {
            return typeid(*rule).hash_code() ^ rule->hash_code();
        }
    };
}

#endif