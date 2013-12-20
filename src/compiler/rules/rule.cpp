#include "rule.h"
#include <set>

using std::ostream;
using std::string;

namespace tree_sitter {
    namespace rules {
        ostream& operator<<(ostream& stream, const Rule &rule) {
            return stream << rule.to_string();
        }

        ostream& operator<<(ostream& stream, const rule_ptr &rule) {
            if (rule.get() == nullptr)
                stream << string("<NULL rule>");
            else
                stream << rule->to_string();
            return stream;
        }
    }
}
