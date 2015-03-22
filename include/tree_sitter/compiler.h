#ifndef TREE_SITTER_COMPILER_H_
#define TREE_SITTER_COMPILER_H_

#include <memory>
#include <set>
#include <string>
#include <utility>
#include <vector>

namespace tree_sitter {

namespace rules {

class Rule;
typedef std::shared_ptr<Rule> rule_ptr;

rule_ptr blank();
rule_ptr choice(const std::vector<rule_ptr> &);
rule_ptr repeat(const rule_ptr &);
rule_ptr seq(const std::vector<rule_ptr> &);
rule_ptr sym(const std::string &);
rule_ptr pattern(const std::string &);
rule_ptr str(const std::string &);
rule_ptr err(const rule_ptr &);
rule_ptr left_assoc(int precedence, const rule_ptr &);
rule_ptr right_assoc(int precedence, const rule_ptr &);
rule_ptr token(const rule_ptr &rule);

std::ostream &operator<<(std::ostream &stream, const rules::rule_ptr &rule);

}  // namespace rules

class Grammar {
  const std::vector<std::pair<std::string, rules::rule_ptr>> rules_;
  std::set<rules::rule_ptr> ubiquitous_tokens_;

 public:
  explicit Grammar(const std::vector<std::pair<std::string, rules::rule_ptr>> &);
  bool operator==(const Grammar &) const;
  std::string start_rule_name() const;
  const rules::rule_ptr rule(const std::string &) const;
  const std::vector<std::pair<std::string, rules::rule_ptr>> &rules() const;
  const std::set<rules::rule_ptr> &ubiquitous_tokens() const;
  Grammar &ubiquitous_tokens(const std::set<rules::rule_ptr> &);
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
  GrammarError(GrammarErrorType type, std::string message);
  bool operator==(const GrammarError &other) const;
  GrammarErrorType type;
  std::string message;
};

std::pair<std::string, const GrammarError *> compile(const Grammar &, std::string);

std::ostream &operator<<(std::ostream &stream, const Grammar &grammar);
std::ostream &operator<<(std::ostream &stream, const GrammarError *error);

}  // namespace tree_sitter

#endif  // TREE_SITTER_COMPILER_H_
