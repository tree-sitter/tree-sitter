#ifndef TreeSitter_SpecHelper_h
#define TreeSitter_SpecHelper_h

#include "igloo/igloo_alt.h"
#include "transition_map.h"
#include "rule.h"

namespace snowhouse {
    template<>
    std::string Stringize(const tree_sitter::rules::TransitionMap<tree_sitter::rules::Rule> &map) {
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

#endif
