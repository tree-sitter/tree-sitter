#include "rule.h"

namespace tree_sitter {
    namespace rules {
        bool Rule::operator==(const rule_ptr other) const {
            return true;
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
