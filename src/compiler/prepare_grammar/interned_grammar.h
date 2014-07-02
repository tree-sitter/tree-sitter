#ifndef COMPILER_PREPARE_GRAMMAR_INTERNED_GRAMMAR_H_
#define COMPILER_PREPARE_GRAMMAR_INTERNED_GRAMMAR_H_

#include <utility>
#include <vector>
#include <set>
#include <string>
#include "tree_sitter/compiler.h"
#include "compiler/rules/symbol.h"

namespace tree_sitter {
    namespace prepare_grammar {
        class InternedGrammar {
        public:
            std::vector<std::pair<std::string, rules::rule_ptr>> rules;
            std::set<rules::Symbol> ubiquitous_tokens;
            std::set<char> separators;
        };
    }
}

#endif  // COMPILER_PREPARE_GRAMMAR_INTERNED_GRAMMAR_H_
