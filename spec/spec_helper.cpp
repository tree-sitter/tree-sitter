#include "spec_helper.h"


EqualsContainerConstraint<TransitionMap<rules::Rule>, rule_tmap_comparator> EqualsTransitionMap(const TransitionMap<rules::Rule> &expected) {
    return EqualsContainer(expected, TransitionMap<rules::Rule>::elements_equal);
}
