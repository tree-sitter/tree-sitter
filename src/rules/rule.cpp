#include "rule.h"

namespace tree_sitter {
    namespace rules {
        std::ostream& operator<<(std::ostream& stream, const Rule &rule)
        {
            stream << rule.to_string();
            return stream;
        }
    }
}
