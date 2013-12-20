#ifndef __tree_sitter__rule_visitor__
#define __tree_sitter__rule_visitor__

#include "rules.h"

namespace tree_sitter {
    namespace rules {
        class RuleVisitor {
        public:
            virtual void visit(const Blank *rule);
            virtual void visit(const Symbol *rule);
            virtual void visit(const Char *rule);
            virtual void visit(const CharClass *rule);
            virtual void visit(const Choice *rule);
            virtual void visit(const Repeat *rule);
            virtual void visit(const Seq *rule);
            virtual void visit(const String *rule);
            virtual void visit(const Pattern *rule);
        };
    }
}

#endif
