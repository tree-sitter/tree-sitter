#include "visitor.h"
#include "rule.h"
#include "blank.h"
#include "symbol.h"
#include "choice.h"
#include "seq.h"
#include "string.h"
#include "pattern.h"
#include "character_set.h"
#include "repeat.h"

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