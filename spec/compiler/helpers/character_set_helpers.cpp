#include "character_set_helpers.h"
#include <memory>

namespace tree_sitter {
    using std::make_shared;
    using std::set;
    
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
