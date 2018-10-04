#ifndef COMPILER_PARSE_JSON_H_
#define COMPILER_PARSE_JSON_H_

#include <string>
#include <unordered_set>
#include "tree_sitter/compiler.h"
#include "compiler/grammar.h"
#include "compiler/property_sheet.h"
#include "compiler/util/result.h"

namespace tree_sitter {

struct ParseGrammarResult {
  std::string name;
  InputGrammar grammar;
  std::string error_message;
};

struct ParsePropertySheetResult {
  PropertySheet property_sheet;
  std::string error_message;
};

ParseGrammarResult parse_grammar_json(const std::string &);
util::Result<PropertySheet> parse_property_sheet_json(const std::string &);

}  // namespace tree_sitter

#endif  // COMPILER_PARSE_JSON_H_
