#ifndef COMPILER_RULES_METADATA_H_
#define COMPILER_RULES_METADATA_H_

#include <memory>

namespace tree_sitter {
namespace rules {

enum Associativity {
  AssociativityNone,
  AssociativityLeft,
  AssociativityRight,
};

struct MetadataParams {
  int precedence;
  Associativity associativity;
  bool has_precedence;
  bool has_associativity;
  bool is_token;
  bool is_string;
  bool is_active;
  bool is_main_token;

  inline MetadataParams() :
    precedence{0}, associativity{AssociativityNone}, has_precedence{false},
    has_associativity{false}, is_token{false}, is_string{false},
    is_active{false}, is_main_token{false} {}

  inline bool operator==(const MetadataParams &other) const {
    return (
      precedence == other.precedence &&
      associativity == other.associativity &&
      has_precedence == other.has_precedence &&
      has_associativity == other.has_associativity &&
      is_token == other.is_token &&
      is_string == other.is_string &&
      is_active == other.is_active &&
      is_main_token == other.is_main_token
    );
  }
};

struct Rule;

struct Metadata {
  std::shared_ptr<Rule> rule;
  MetadataParams params;

  Metadata(const Rule &rule, MetadataParams params);

  static Metadata token(const Rule &rule);
  static Metadata active_prec(int precedence, const Rule &rule);
  static Metadata prec(int precedence, const Rule &rule);
  static Metadata prec_left(int precedence, const Rule &rule);
  static Metadata prec_right(int precedence, const Rule &rule);
  static Metadata separator(const Rule &rule);
  static Metadata main_token(const Rule &rule);

  bool operator==(const Metadata &other) const;
};

}  // namespace rules
}  // namespace tree_sitter

#endif  // COMPILER_RULES_METADATA_H_