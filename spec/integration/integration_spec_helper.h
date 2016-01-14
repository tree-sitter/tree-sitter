#ifndef INTEGRATION_SPEC_HELPER_
#define INTEGRATION_SPEC_HELPER_

#include "bandit/bandit.h"
#include "tree_sitter/compiler.h"
#include "tree_sitter/runtime.h"

using namespace std;
using namespace bandit;

#define START_TEST go_bandit([]() {
#define END_TEST });

#endif  // INTEGRATION_SPEC_HELPER_
