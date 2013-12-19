#ifndef __tree_sitter__string__
#define __tree_sitter__string__

#include "rule.h"

namespace tree_sitter  {
    namespace rules {
        class String : public Rule {
        public:
            String(std::string value);
            bool operator==(const Rule& other) const;
            std::string to_string() const;
            void accept(RuleVisitor &visitor) const;

            const std::string value;
        };
        
        typedef std::shared_ptr<const String> string_ptr;
        string_ptr str(const std::string &value);
    }
}

#endif
