#ifndef COMPILER_RULES_METADATA_H_
#define COMPILER_RULES_METADATA_H_

#include <string>
#include <map>
#include "compiler/rule.h"

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

  MetadataParams();
  bool operator==(const MetadataParams &) const;
};

class Metadata : public Rule {
 public:
  Metadata(rule_ptr rule, MetadataParams);
  static rule_ptr build(rule_ptr rule, MetadataParams);
  static rule_ptr main_token(rule_ptr rule);
  static rule_ptr separator(rule_ptr rule);

  bool operator==(const Rule &other) const;
  size_t hash_code() const;
  rule_ptr copy() const;
  std::string to_string() const;
  void accept(Visitor *visitor) const;

  const rule_ptr rule;
  MetadataParams params;
};

}  // namespace rules
}  // namespace tree_sitter

#endif  // COMPILER_RULES_METADATA_H_
