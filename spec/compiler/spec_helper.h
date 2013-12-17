#ifndef TreeSitter_SpecHelper_h
#define TreeSitter_SpecHelper_h

#include "igloo/igloo_alt.h"
#include "transition_map.h"

#include "rules.h"
#include "item.h"
#include "item_set.h"
#include "grammar.h"
#include "parse_table.h"
#include "parse_table_builder.h"

#include "../fixtures/grammars/arithmetic.h"


using namespace tree_sitter;
using namespace std;
using namespace igloo;

// Assertion helpers for transition maps
typedef bool (* rule_tmap_comparator)(const std::pair<rules::rule_ptr, rules::rule_ptr> &, const std::pair<rules::rule_ptr, rules::rule_ptr> &);
EqualsContainerConstraint<TransitionMap<rules::Rule>, rule_tmap_comparator> EqualsTransitionMap(const TransitionMap<rules::Rule> &expected);

namespace tree_sitter {
    namespace lr {
        std::ostream& operator<<(std::ostream &stream, const unordered_map<string, unordered_set<ParseAction>> &map);
    }
}

string src_dir();

#endif
