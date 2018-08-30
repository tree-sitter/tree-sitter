#ifndef COMPILER_GENERATE_CODE_C_CODE_H_
#define COMPILER_GENERATE_CODE_C_CODE_H_

#include <string>
#include <unordered_map>
#include "compiler/rule.h"

namespace tree_sitter {

struct LexicalGrammar;
struct SyntaxGrammar;
struct LexTable;
struct ParseTable;

namespace generate_code {

std::string c_code(
  std::string,
  ParseTable &&,
  LexTable &&,
  LexTable &&,
  rules::Symbol,
  SyntaxGrammar &&,
  LexicalGrammar &&,
  std::unordered_map<rules::Symbol, rules::Alias> &&
);

}  // namespace generate_code
}  // namespace tree_sitter

#endif  // COMPILER_GENERATE_CODE_C_CODE_H_
