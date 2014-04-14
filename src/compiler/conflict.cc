#include <string>
#include "tree_sitter/compiler.h"

namespace tree_sitter {
    using std::string;

    Conflict::Conflict(string description) : description(description) {}

    bool Conflict::operator==(const tree_sitter::Conflict &other) const {
        return other.description == description;
    }

    bool Conflict::operator<(const tree_sitter::Conflict &other) const {
        return other.description < description;
    }

    std::ostream& operator<<(std::ostream &stream, const Conflict &conflict) {
        return stream << "#<conflict " + conflict.description + ">";
    }
}