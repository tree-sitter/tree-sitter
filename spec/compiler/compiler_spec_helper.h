#ifndef __tree_sitter_compiler_spec_helper_h__
#define __tree_sitter_compiler_spec_helper_h__

#include "bandit/bandit.h"
#include "helpers/stream_methods.h"
#include "helpers/equals_pointer.h"
#include "helpers/character_set_helpers.h"
#include "tree_sitter/compiler.h"
#include "compiler/rules/character_set.h"

using namespace tree_sitter;
using namespace std;
using namespace bandit;

#define START_TEST go_bandit([]() {
#define END_TEST });

#endif
