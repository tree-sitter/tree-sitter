#ifndef __tree_sitter_runtime_spec_helper_h__
#define __tree_sitter_runtime_spec_helper_h__

#include "bandit/bandit.h"
#include "tree_sitter/runtime.h"

using namespace std;
using namespace bandit;

#define START_TEST go_bandit([]() {
#define END_TEST });

#endif
