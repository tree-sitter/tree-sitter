#ifndef __tree_sitter_spec_helper_h__
#define __tree_sitter_spec_helper_h__

#include "bandit/bandit.h"
#include "helpers/stream_methods.h"
#include "helpers/equals_pointer.h"
#include "tree_sitter/compiler.h"
#include "tree_sitter/runtime.h"
#include "rules/character_range.h"

using namespace tree_sitter;
using namespace std;
using namespace bandit;

#define START_TEST go_bandit([]() {
#define END_TEST });

string src_dir();

namespace tree_sitter {
    namespace rules {
        rule_ptr character(const std::set<CharacterRange> &matches);
        rule_ptr character(const std::set<CharacterRange> &matches, bool);
    }
}

#endif
