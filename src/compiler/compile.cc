#include "tree_sitter/compiler.h"
#include "compiler/prepare_grammar/prepare_grammar.h"
#include "compiler/build_tables/parse_table_builder.h"
#include "compiler/generate_code/c_code.h"
#include "compiler/syntax_grammar.h"
#include "compiler/log.h"
#include "compiler/lexical_grammar.h"
#include "compiler/parse_grammar.h"
#include "json.h"

namespace tree_sitter {

using std::move;
using std::pair;
using std::string;
using std::vector;
using std::get;
using std::make_tuple;

extern "C" TSCompileResult ts_compile_grammar(const char *input, FILE *log_file) {
  set_log_file(log_file);

  ParseGrammarResult parse_result = parse_grammar(string(input));
  if (!parse_result.error_message.empty()) {
    return {nullptr, strdup(parse_result.error_message.c_str()), TSCompileErrorTypeInvalidGrammar};
  }

  auto prepare_grammar_result = prepare_grammar::prepare_grammar(parse_result.grammar);
  SyntaxGrammar &syntax_grammar = prepare_grammar_result.syntax_grammar;
  LexicalGrammar &lexical_grammar = prepare_grammar_result.lexical_grammar;
  auto &simple_aliases = prepare_grammar_result.simple_aliases;
  CompileError error = prepare_grammar_result.error;
  if (error.type) {
    return {nullptr, strdup(error.message.c_str()), error.type};
  }

  auto builder = build_tables::ParseTableBuilder::create(
    syntax_grammar,
    lexical_grammar,
    simple_aliases
  );
  auto build_tables_result = builder->build();
  error = build_tables_result.error;
  if (error.type != 0) {
    return {nullptr, strdup(error.message.c_str()), error.type};
  }

  string code = generate_code::c_code(
    parse_result.name,
    move(build_tables_result.parse_table),
    move(build_tables_result.main_lex_table),
    move(build_tables_result.keyword_lex_table),
    build_tables_result.keyword_capture_token,
    move(syntax_grammar),
    move(lexical_grammar),
    move(simple_aliases)
  );

  set_log_file(nullptr);
  return {strdup(code.c_str()), nullptr, TSCompileErrorTypeNone};
}

}  // namespace tree_sitter
