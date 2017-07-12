#ifndef COMPILER_GRAMMAR_JSON_H_
#define COMPILER_GRAMMAR_JSON_H_

#include <string>
#include <unordered_set>
#include "tree_sitter/compiler.h"
#include "compiler/grammar.h"

namespace tree_sitter {

struct ParseGrammarResult {
  std::string name;
  InputGrammar grammar;
  std::string error_message;
};

ParseGrammarResult parse_grammar(const std::string &);

}  // namespace tree_sitter

#endif  // COMPILER_GRAMMAR_JSON_H_
