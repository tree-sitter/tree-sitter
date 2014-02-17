#ifndef __tree_sitter__rule_visitor__
#define __tree_sitter__rule_visitor__

namespace tree_sitter {
    namespace rules {
        class Rule;
        class Blank;
        class Symbol;
        class CharacterSet;
        class Choice;
        class Repeat;
        class Seq;
        class String;
        class Pattern;
        
        class Visitor {
        public:
            virtual void default_visit(const Rule *rule);
            virtual void visit(const Blank *rule);
            virtual void visit(const Symbol *rule);
            virtual void visit(const CharacterSet *rule);
            virtual void visit(const Choice *rule);
            virtual void visit(const Repeat *rule);
            virtual void visit(const Seq *rule);
            virtual void visit(const String *rule);
            virtual void visit(const Pattern *rule);
        };
    }
}

#endif
