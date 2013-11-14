#ifndef __TreeSitter__rule__
#define __TreeSitter__rule__

#include <string>

namespace tree_sitter {
    template<class value> class TransitionMap;
    
    namespace rules {
        class Rule {
        public:
            virtual TransitionMap<Rule> transitions() const = 0;
            virtual bool operator==(const Rule& other) const = 0;
            virtual std::string to_string() const = 0;
        };
        
        typedef std::shared_ptr<const Rule> rule_ptr;

        std::ostream& operator<<(std::ostream& stream, const Rule &rule);

        template <typename RuleClass>
        rule_ptr build_binary_rule_tree(const std::initializer_list<rule_ptr> &rules) {
            rule_ptr result(nullptr);
            for (auto it = rules.end() - 1; it >= rules.begin(); --it)
                result = result.get() ? std::make_shared<RuleClass>(*it, result) : *it;
            return result;
        }
    }
}


#endif