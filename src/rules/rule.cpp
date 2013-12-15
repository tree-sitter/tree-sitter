#include "rule.h"
#include <set>

namespace tree_sitter {
    namespace rules {
        size_t Rule::hash_code() const {
            return std::hash<std::string>()(to_string());
        }

        std::ostream& operator<<(std::ostream& stream, const Rule &rule)
        {
            stream << rule.to_string();
            return stream;
        }

        std::ostream& operator<<(std::ostream& stream, const rule_ptr &rule)
        {
            if (rule.get() == nullptr)
                stream << std::string("<NULL rule>");
            else
                stream << rule->to_string();
            return stream;
        }
    }
}
