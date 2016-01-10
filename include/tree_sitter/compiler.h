#ifndef TREE_SITTER_COMPILER_H_
#define TREE_SITTER_COMPILER_H_

#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace tree_sitter {

class Rule;
typedef std::shared_ptr<Rule> rule_ptr;

rule_ptr blank();
rule_ptr choice(const std::vector<rule_ptr> &);
rule_ptr repeat(const rule_ptr &);
rule_ptr repeat1(const rule_ptr &);
rule_ptr seq(const std::vector<rule_ptr> &);
rule_ptr sym(const std::string &);
rule_ptr pattern(const std::string &);
rule_ptr str(const std::string &);
rule_ptr err(const rule_ptr &);
rule_ptr prec(int precedence, const rule_ptr &);
rule_ptr prec_left(const rule_ptr &);
rule_ptr prec_left(int precedence, const rule_ptr &);
rule_ptr prec_right(const rule_ptr &);
rule_ptr prec_right(int precedence, const rule_ptr &);
rule_ptr token(const rule_ptr &rule);

struct Grammar {
  std::vector<std::pair<std::string, rule_ptr>> rules;
  std::vector<rule_ptr> extra_tokens;
  std::vector<std::vector<std::string>> expected_conflicts;
};

enum GrammarErrorType {
  GrammarErrorTypeRegex,
  GrammarErrorTypeUndefinedSymbol,
  GrammarErrorTypeInvalidUbiquitousToken,
  GrammarErrorTypeLexConflict,
  GrammarErrorTypeParseConflict,
};

class GrammarError {
 public:
  GrammarError(GrammarErrorType type, std::string message) : type(type), message(message) {}
  bool operator==(const GrammarError &other) const {
    return type == other.type && message == other.message;
  }

  GrammarErrorType type;
  std::string message;
};

std::pair<std::string, const GrammarError *> compile(const Grammar &,
                                                     std::string);
struct CompileResult {
  const char *code;
  const char *error_message;
};

extern "C" CompileResult compile(const char *input);

}  // namespace tree_sitter

#endif  // TREE_SITTER_COMPILER_H_
