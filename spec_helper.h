#ifndef TreeSitter_SpecHelper_h
#define TreeSitter_SpecHelper_h

#include "igloo/igloo_alt.h"
#include "transition_map.h"
#include "rules.h"

using namespace igloo;
using namespace tree_sitter;

// Assertion helpers for transition maps
namespace snowhouse {
    template<>
    std::string Stringize(const tree_sitter::TransitionMap<tree_sitter::rules::Rule> &map) {
        std::string result("[");
        bool started = false;
        for (auto pair : map) {
            if (started) result += ", ";
            result += (pair.first->to_string() + " => " + pair.second->to_string());
            started = true;
        }
        return result + "]";
    }
}

typedef TransitionMap<rules::Rule> tmap;
typedef bool (* tmap_comparator)(const tmap::pair_type &, const tmap::pair_type &);
EqualsContainerConstraint<tmap, tmap_comparator> EqualsTransitionMap(const tmap &expected) {
    return EqualsContainer(expected, tmap::elements_equal);
}

#endif
