#ifndef __TreeSitter__rule__
#define __TreeSitter__rule__

#include <string>

namespace tree_sitter {
    template<class value> class TransitionMap;
    
    namespace rules {
        class Rule;
        typedef std::shared_ptr<const Rule> rule_ptr;

        class Rule {
        public:
            virtual TransitionMap<Rule> transitions() const = 0;
            virtual bool operator==(const Rule& other) const = 0;
            virtual std::string to_string() const = 0;
            bool operator==(const rule_ptr other) const;
        };
        

        std::ostream& operator<<(std::ostream& stream, const Rule &rule);
        std::ostream& operator<<(std::ostream& stream, const rule_ptr &rule);

        template <typename RuleClass>
        rule_ptr build_binary_rule_tree(const std::initializer_list<rule_ptr> &rules) {
            rule_ptr result;
            for (auto rule : rules)
                result = result.get() ? std::make_shared<RuleClass>(result, rule) : rule;
            return result;
        }
    }
}


#endif