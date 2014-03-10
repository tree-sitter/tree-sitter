#include "compiler/rules/visitor.h"
#include "compiler/rules/rule.h"
#include "compiler/rules/blank.h"
#include "compiler/rules/symbol.h"
#include "compiler/rules/choice.h"
#include "compiler/rules/seq.h"
#include "compiler/rules/string.h"
#include "compiler/rules/pattern.h"
#include "compiler/rules/character_set.h"
#include "compiler/rules/repeat.h"

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