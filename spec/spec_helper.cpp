#include "spec_helper.h"


EqualsContainerConstraint<rule_tmap, rule_tmap_comparator> EqualsTransitionMap(const rule_tmap &expected) {
    return EqualsContainer(expected, rule_tmap::elements_equal);
}
