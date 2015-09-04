#ifndef TREE_SITTER_COMPILER_H_
#define TREE_SITTER_COMPILER_H_

#include <memory>
#include <set>
#include <string>
#include <utility>
#include <vector>

namespace tree_sitter {

class Rule;
typedef std::shared_ptr<Rule> rule_ptr;

enum Associativity {
  AssociativityNone,
  AssociativityLeft,
  AssociativityRight,
};

rule_ptr blank();
rule_ptr choice(const std::vector<rule_ptr> &);
rule_ptr repeat(const rule_ptr &);
rule_ptr seq(const std::vector<rule_ptr> &);
rule_ptr sym(const std::string &);
rule_ptr pattern(const std::string &);
rule_ptr str(const std::string &);
rule_ptr err(const rule_ptr &);
rule_ptr prec(int precedence, const rule_ptr &);
rule_ptr prec(int precedence, const rule_ptr &, Associativity);
rule_ptr token(const rule_ptr &rule);

class Grammar {
  const std::vector<std::pair<std::string, rule_ptr>> rules_;
  std::set<rule_ptr> ubiquitous_tokens_;
  std::set<std::set<std::string>> expected_conflicts_;

 public:
  explicit Grammar(const std::vector<std::pair<std::string, rule_ptr>> &);
  Grammar &ubiquitous_tokens(const std::set<rule_ptr> &);
  Grammar &expected_conflicts(const std::set<std::set<std::string>> &);
  const std::vector<std::pair<std::string, rule_ptr>> &rules() const;
  const std::set<rule_ptr> &ubiquitous_tokens() const;
  const std::set<std::set<std::string>> &expected_conflicts() const;
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

std::pair<std::string, const GrammarError *> compile(const Grammar &,
                                                     std::string);

std::ostream &operator<<(std::ostream &stream, const Grammar &grammar);
std::ostream &operator<<(std::ostream &stream, const GrammarError *error);
std::ostream &operator<<(std::ostream &stream, const rule_ptr &rule);

}  // namespace tree_sitter

#endif  // TREE_SITTER_COMPILER_H_
