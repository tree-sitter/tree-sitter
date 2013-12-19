#ifndef __tree_sitter__rule_visitor__
#define __tree_sitter__rule_visitor__

#include "rules.h"

namespace tree_sitter {
    namespace rules {
        class RuleVisitor {
        public:
            virtual void visit(const Blank *rule) = 0;
            virtual void visit(const Symbol *rule) = 0;
            virtual void visit(const Char *rule) = 0;
            virtual void visit(const CharClass *rule) = 0;
            virtual void visit(const Choice *rule) = 0;
            virtual void visit(const Repeat *rule) = 0;
            virtual void visit(const Seq *rule) = 0;
            virtual void visit(const String *rule) = 0;
            virtual void visit(const Pattern *rule) = 0;
        };
    }
}

#endif
