#ifndef TreeSitter_SpecHelper_h
#define TreeSitter_SpecHelper_h

#include "igloo/igloo_alt.h"
#include "transition_map.h"

#include "rules.h"
#include "item.h"
#include "item_set.h"
#include "grammar.h"

using namespace tree_sitter;
using namespace std;
using namespace igloo;

// Assertion helpers for transition maps
typedef TransitionMap<rules::Rule> rule_tmap;
typedef bool (* rule_tmap_comparator)(const std::pair<rules::rule_ptr, rules::rule_ptr> &, const std::pair<rules::rule_ptr, rules::rule_ptr> &);
EqualsContainerConstraint<TransitionMap<rules::Rule>, rule_tmap_comparator> EqualsTransitionMap(const TransitionMap<rules::Rule> &expected);

#endif
