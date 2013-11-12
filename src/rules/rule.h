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
    }
}


#endif