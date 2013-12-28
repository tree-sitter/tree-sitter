#ifndef TreeSitter_SpecHelper_h
#define TreeSitter_SpecHelper_h

#include "bandit/bandit.h"
#include "transition_map.h"
#include "rules.h"
#include "item.h"
#include "item_set.h"
#include "grammar.h"
#include "parse_table.h"
#include "table_builder.h"
#include "../fixtures/grammars/arithmetic.h"

using namespace tree_sitter;
using namespace std;
using namespace bandit;

#define START_TEST go_bandit([]() {
#define END_TEST });

namespace tree_sitter {
    namespace lr {
        std::ostream& operator<<(std::ostream &stream, const unordered_map<string, unordered_set<ParseAction>> &map);
        std::ostream& operator<<(std::ostream &stream, const unordered_map<CharMatch, unordered_set<LexAction>> &map);
    }
}

string src_dir();

#endif
