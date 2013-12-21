#include "visitor.h"

namespace tree_sitter {
    namespace rules {
        void Visitor::visit(const Blank *rule) {}
        void Visitor::visit(const Symbol *rule) {}
        void Visitor::visit(const Char *rule) {}
        void Visitor::visit(const CharClass *rule) {}
        void Visitor::visit(const Choice *rule) {}
        void Visitor::visit(const Repeat *rule) {}
        void Visitor::visit(const Seq *rule) {}
        void Visitor::visit(const String *rule) {}
        void Visitor::visit(const Pattern *rule) {}
    }
}