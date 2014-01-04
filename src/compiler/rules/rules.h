#ifndef __TreeSitter__rules__
#define __TreeSitter__rules__

#include "rule.h"
#include "blank.h"
#include "symbol.h"
#include "token.h"
#include "choice.h"
#include "seq.h"
#include "string.h"
#include "pattern.h"
#include "character.h"
#include "repeat.h"
#include "non_terminal.h"
#include "visitor.h"

namespace tree_sitter {
    namespace rules {
        rule_ptr blank();
        char_ptr character(char value);
        char_ptr character(char min, char max);
        char_ptr character(CharClass value);
        rule_ptr choice(const std::initializer_list<rule_ptr> &rules);
        rule_ptr pattern(const std::string &value);
        rule_ptr repeat(const rule_ptr content);
        rule_ptr seq(const std::initializer_list<rule_ptr> &rules);
        rule_ptr str(const std::string &value);
        sym_ptr sym(const std::string &name);
        rule_ptr token(const std::string &name);
    }
}

#endif
