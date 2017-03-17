#include "tree_sitter/compiler.h"
#include "compiler/prepare_grammar/prepare_grammar.h"
#include "compiler/build_tables/build_tables.h"
#include "compiler/generate_code/c_code.h"
#include "compiler/syntax_grammar.h"
#include "compiler/lexical_grammar.h"
#include "compiler/parse_grammar.h"
#include "json.h"

namespace tree_sitter {

using std::pair;
using std::string;
using std::vector;
using std::get;
using std::make_tuple;

extern "C" TSCompileResult ts_compile_grammar(const char *input) {
  ParseGrammarResult parse_result = parse_grammar(string(input));
  if (!parse_result.error_message.empty()) {
    return { nullptr, strdup(parse_result.error_message.c_str()),
             TSCompileErrorTypeInvalidGrammar };
  }

  auto prepare_grammar_result = prepare_grammar::prepare_grammar(parse_result.grammar);
  const SyntaxGrammar &syntax_grammar = get<0>(prepare_grammar_result);
  const LexicalGrammar &lexical_grammar = get<1>(prepare_grammar_result);
  CompileError error = get<2>(prepare_grammar_result);
  if (error.type) {
    return { nullptr, strdup(error.message.c_str()), error.type };
  }

  auto table_build_result =
    build_tables::build_tables(syntax_grammar, lexical_grammar);
  const ParseTable &parse_table = get<0>(table_build_result);
  const LexTable &lex_table = get<1>(table_build_result);
  error = get<2>(table_build_result);
  if (error.type) {
    return { nullptr, strdup(error.message.c_str()), error.type };
  }

  string code = generate_code::c_code(parse_result.name, parse_table, lex_table,
                                      syntax_grammar, lexical_grammar);

  return { strdup(code.c_str()), nullptr, TSCompileErrorTypeNone };
}

pair<string, const CompileError> compile(const InputGrammar &grammar,
                                         std::string name) {
  auto prepare_grammar_result = prepare_grammar::prepare_grammar(grammar);
  const SyntaxGrammar &syntax_grammar = get<0>(prepare_grammar_result);
  const LexicalGrammar &lexical_grammar = get<1>(prepare_grammar_result);
  CompileError error = get<2>(prepare_grammar_result);
  if (error.type) return { "", error };

  auto table_build_result =
    build_tables::build_tables(syntax_grammar, lexical_grammar);
  const ParseTable &parse_table = get<0>(table_build_result);
  const LexTable &lex_table = get<1>(table_build_result);
  error = get<2>(table_build_result);
  if (error.type) return { "", error };

  string code = generate_code::c_code(name, parse_table, lex_table,
                                      syntax_grammar, lexical_grammar);

  return { code, CompileError::none() };
}

}  // namespace tree_sitter
