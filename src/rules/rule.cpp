#include "rule.h"

std::ostream& operator<<(std::ostream& stream, const tree_sitter::rules::Rule &rule)
{
    stream << rule.to_string();
    return stream;
}
