#ifndef TEST_HELPER_
#define TEST_HELPER_

#include "bandit/bandit.h"
#include "tree_sitter/compiler.h"
#include "tree_sitter/runtime.h"

namespace tree_sitter {}

using namespace std;
using namespace bandit;
using namespace tree_sitter;

#define START_TEST go_bandit([]() {
#define END_TEST });

#define TREE_SITTER_WRAP_MALLOC

#endif  // TEST_HELPER_
