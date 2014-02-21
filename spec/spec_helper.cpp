#include "spec_helper.h"
#include "rules/character_set.h"

string src_dir() {
    const char * dir = getenv("TREESITTER_DIR");
    if (!dir) dir = getenv("PWD");
    return dir;
}

namespace tree_sitter {
    namespace rules {
        rule_ptr character(const set<CharacterRange> &ranges) {
            return make_shared<CharacterSet>(ranges);
        }
        
        rule_ptr character(const set<CharacterRange> &ranges, bool sign) {
            if (sign)
                return character(ranges);
            else
                return CharacterSet(ranges).complement().copy();
        }
    }
}