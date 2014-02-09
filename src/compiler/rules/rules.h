#ifndef __TreeSitter__rules__
#define __TreeSitter__rules__

#include "rule.h"
#include "blank.h"
#include "symbol.h"
#include "choice.h"
#include "seq.h"
#include "string.h"
#include "pattern.h"
#include "character_set.h"
#include "repeat.h"
#include "visitor.h"
#include <vector>

namespace tree_sitter {
    namespace rules {
        rule_ptr blank();
        char_ptr character(char value);
        char_ptr character(const std::set<CharacterRange> &matches);
        char_ptr character(const std::set<CharacterRange> &matches, bool);
        
        rule_ptr choice(const std::vector<rule_ptr> &rules);
        rule_ptr pattern(const std::string &value);
        rule_ptr repeat(const rule_ptr content);
        rule_ptr seq(const std::vector<rule_ptr> &rules);
        rule_ptr str(const std::string &value);
        sym_ptr sym(const std::string &name);
        rule_ptr aux_sym(const std::string &name);
    }
}

#endif
