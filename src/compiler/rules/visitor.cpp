#include "visitor.h"

namespace tree_sitter {
    namespace rules {
        void Visitor::default_visit(const Rule *rule) {};
        void Visitor::visit(const Blank *rule) { default_visit(rule); }
        void Visitor::visit(const Symbol *rule) { default_visit(rule); }
        void Visitor::visit(const CharacterSet *rule) { default_visit(rule); }
        void Visitor::visit(const Choice *rule) { default_visit(rule); }
        void Visitor::visit(const Repeat *rule) { default_visit(rule); }
        void Visitor::visit(const Seq *rule) { default_visit(rule); }
        void Visitor::visit(const String *rule) { default_visit(rule); }
        void Visitor::visit(const Pattern *rule) { default_visit(rule); }
    }
}