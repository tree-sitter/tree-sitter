#ifndef __TreeSitter__rules__
#define __TreeSitter__rules__

#include "rule.h"
#include "blank.h"
#include "symbol.h"
#include "choice.h"
#include "seq.h"
#include "string.h"
#include "pattern.h"
#include "char.h"
#include "char_class.h"
#include "repeat.h"
#include "visitor.h"

namespace tree_sitter {
    namespace rules {
        rule_ptr blank();
        rule_ptr character(char value);
        rule_ptr char_class(CharClassType value);
        rule_ptr choice(const std::initializer_list<rule_ptr> &rules);
        rule_ptr pattern(const std::string &value);
        rule_ptr repeat(const rule_ptr content);
        rule_ptr seq(const std::initializer_list<rule_ptr> &rules);
        rule_ptr str(const std::string &value);
        rule_ptr sym(const std::string &name);
    }
}

#endif
