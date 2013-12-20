#include "rule_visitor.h"

namespace tree_sitter {
    namespace rules {
        void RuleVisitor::visit(const Blank *rule) {}
        void RuleVisitor::visit(const Symbol *rule) {}
        void RuleVisitor::visit(const Char *rule) {}
        void RuleVisitor::visit(const CharClass *rule) {}
        void RuleVisitor::visit(const Choice *rule) {}
        void RuleVisitor::visit(const Repeat *rule) {}
        void RuleVisitor::visit(const Seq *rule) {}
        void RuleVisitor::visit(const String *rule) {}
        void RuleVisitor::visit(const Pattern *rule) {}
    }
}