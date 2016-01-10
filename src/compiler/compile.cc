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

CompileResult compile(const char *input) {
  ParseGrammarResult parse_result = parse_grammar(string(input));
  if (!parse_result.error_message.empty()) {
    return {nullptr, parse_result.error_message.c_str()};
  }

  auto compile_result = compile(parse_result.grammar, parse_result.name);
  if (compile_result.second) {
    return {nullptr, compile_result.second->message.c_str()};
  }

  return {compile_result.first.c_str(), nullptr};
}

pair<string, const GrammarError *> compile(const Grammar &grammar,
                                           std::string name) {
  auto prepare_grammar_result = prepare_grammar::prepare_grammar(grammar);
  const SyntaxGrammar &syntax_grammar = get<0>(prepare_grammar_result);
  const LexicalGrammar &lexical_grammar = get<1>(prepare_grammar_result);
  const GrammarError *error = get<2>(prepare_grammar_result);

  if (error)
    return { "", error };

  auto table_build_result =
    build_tables::build_tables(syntax_grammar, lexical_grammar);
  const ParseTable &parse_table = get<0>(table_build_result);
  const LexTable &lex_table = get<1>(table_build_result);
  error = get<2>(table_build_result);

  if (error)
    return { "", error };

  string code = generate_code::c_code(name, parse_table, lex_table,
                                      syntax_grammar, lexical_grammar);

  return { code, nullptr };
}

}  // namespace tree_sitter
