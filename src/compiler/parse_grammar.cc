#include "compiler/parse_grammar.h"
#include <string>
#include <vector>
#include <unordered_set>
#include <utility>
#include "json.h"
#include "compiler/rule.h"

namespace tree_sitter {

using std::move;
using std::string;
using std::vector;
using std::unordered_set;
using std::pair;
using rules::Rule;
using rules::Blank;
using rules::Metadata;
using rules::Pattern;
using rules::String;
using rules::NamedSymbol;

struct ParseRuleResult {
  Rule rule;
  string error_message;

  ParseRuleResult(const string &error_message) : error_message(error_message) {}
  ParseRuleResult(const char *error_message) : error_message(error_message) {}
  ParseRuleResult(Rule rule) : rule(rule) {}
};

ParseRuleResult parse_rule(json_value *rule_json) {
  string error_message;
  json_value rule_type_json;
  string type;

  if (!rule_json) {
    return "Rule cannot be null";
  }

  if (rule_json->type != json_object) {
    return "Rule type must be an object";
  }

  rule_type_json = rule_json->operator[]("type");
  if (rule_type_json.type != json_string) {
    return "Rule type must be a string";
  }

  type = rule_type_json.u.string.ptr;

  if (type == "BLANK") {
    return Rule(Blank{});
  }

  if (type == "CHOICE") {
    json_value members_json = rule_json->operator[]("members");
    if (members_json.type != json_array) {
      return "Choice members must be an array";
    }

    vector<Rule> members;
    for (size_t i = 0, length = members_json.u.array.length; i < length; i++) {
      json_value *member_json = members_json.u.array.values[i];
      auto result = parse_rule(member_json);
      if (!result.error_message.empty()) {
        return "Invalid choice member: " + result.error_message;
      }
      members.push_back(result.rule);
    }
    return Rule::choice(members);
  }

  if (type == "SEQ") {
    json_value members_json = rule_json->operator[]("members");
    if (members_json.type != json_array) {
      return "Seq members must be an array";
    }

    vector<Rule> members;
    for (size_t i = 0, length = members_json.u.array.length; i < length; i++) {
      json_value *member_json = members_json.u.array.values[i];
      auto result = parse_rule(member_json);
      if (!result.error_message.empty()) {
        return "Invalid choice member: " + result.error_message;
      }
      members.push_back(result.rule);
    }
    return Rule::seq(members);
  }

  if (type == "REPEAT") {
    json_value content_json = rule_json->operator[]("content");
    auto result = parse_rule(&content_json);
    if (!result.error_message.empty()) {
      return "Invalid repeat content: " + result.error_message;
    }
    return Rule::choice({Rule::repeat(result.rule), Blank{}});
  }

  if (type == "REPEAT1") {
    json_value content_json = rule_json->operator[]("content");
    auto result = parse_rule(&content_json);
    if (!result.error_message.empty()) {
      return "Invalid repeat content: " + result.error_message;
    }
    return Rule::repeat(result.rule);
  }

  if (type == "TOKEN") {
    json_value content_json = rule_json->operator[]("content");
    auto result = parse_rule(&content_json);
    if (!result.error_message.empty()) {
      return "Invalid token content: " + result.error_message;
    }
      return Rule(Metadata::token(move(result.rule)));
  }

  if (type == "IMMEDIATE_TOKEN") {
    json_value content_json = rule_json->operator[]("content");
    auto result = parse_rule(&content_json);
    if (!result.error_message.empty()) {
      return "Invalid token content: " + result.error_message;
    }
      return Rule(Metadata::immediate_token(move(result.rule)));
  }

  if (type == "PATTERN") {
    json_value value_json = rule_json->operator[]("value");
    if (value_json.type == json_string) {
      return Rule(Pattern{value_json.u.string.ptr});
    } else {
      return "Pattern value must be a string";
    }
  }

  if (type == "STRING") {
    json_value value_json = rule_json->operator[]("value");
    if (value_json.type == json_string) {
      return Rule(String{value_json.u.string.ptr});
    } else {
      return "String rule value must be a string";
    }
  }

  if (type == "SYMBOL") {
    json_value value_json = rule_json->operator[]("name");
    if (value_json.type == json_string) {
      return Rule(NamedSymbol{value_json.u.string.ptr});
    } else {
      return "Symbol value must be a string";
    }
  }

  if (type == "PREC") {
    json_value precedence_json = rule_json->operator[]("value");
    if (precedence_json.type != json_integer) {
      return "Precedence value must be an integer";
    }

    json_value content_json = rule_json->operator[]("content");
    auto result = parse_rule(&content_json);
    if (!result.error_message.empty()) {
      return "Invalid precedence content: " + result.error_message;
    }
    return Rule(Metadata::prec(precedence_json.u.integer, move(result.rule)));
  }

  if (type == "PREC_LEFT") {
    json_value precedence_json = rule_json->operator[]("value");
    if (precedence_json.type != json_integer) {
      return "Precedence value must be an integer";
    }

    json_value content_json = rule_json->operator[]("content");
    auto result = parse_rule(&content_json);
    if (!result.error_message.empty()) {
      return "Invalid precedence content: " + result.error_message;
    }
    return Rule(Metadata::prec_left(precedence_json.u.integer, move(result.rule)));
  }

  if (type == "PREC_RIGHT") {
    json_value precedence_json = rule_json->operator[]("value");
    if (precedence_json.type != json_integer) {
      return "Precedence value must be an integer";
    }

    json_value content_json = rule_json->operator[]("content");
    auto result = parse_rule(&content_json);
    if (!result.error_message.empty()) {
      return "Invalid precedence content: " + result.error_message;
    }
    return Rule(Metadata::prec_right(precedence_json.u.integer, move(result.rule)));
  }

  if (type == "PREC_DYNAMIC") {
    json_value precedence_json = rule_json->operator[]("value");
    if (precedence_json.type != json_integer) {
      return "Precedence value must be an integer";
    }

    json_value content_json = rule_json->operator[]("content");
    auto result = parse_rule(&content_json);
    if (!result.error_message.empty()) {
      return "Invalid precedence content: " + result.error_message;
    }
    return Rule(Metadata::prec_dynamic(precedence_json.u.integer, move(result.rule)));
  }

  if (type == "ALIAS") {
    json_value value_json = rule_json->operator[]("value");
    if (value_json.type != json_string) {
      return "Rename value must be a string";
    }

    json_value is_named_json = rule_json->operator[]("named");
    if (is_named_json.type != json_boolean) {
      return "Rename named value must be a boolean";
    }

    json_value content_json = rule_json->operator[]("content");
    auto result = parse_rule(&content_json);
    if (!result.error_message.empty()) {
      return "Invalid rename content: " + result.error_message;
    }
    return Rule(Metadata::alias(
      string(value_json.u.string.ptr),
      is_named_json.u.boolean,
      move(result.rule)
    ));
  }

  return "Unknown rule type: " + type;
}

ParseGrammarResult parse_grammar(const string &input) {
  string error_message;
  string name;
  InputGrammar grammar;
  json_value
    name_json, rules_json, extras_json, conflicts_json, external_tokens_json,
    inline_rules_json, word_rule_json;

  json_settings settings = { 0, json_enable_comments, 0, 0, 0, 0 };
  char parse_error[json_error_max];
  json_value *grammar_json =
    json_parse_ex(&settings, input.c_str(), input.size(), parse_error);
  if (!grammar_json) {
    error_message = string("Invalid JSON at ") + parse_error;
    goto error;
  }

  if (grammar_json->type != json_object) {
    error_message = "Body must be an object";
    goto error;
  }

  name_json = grammar_json->operator[]("name");
  if (name_json.type != json_string) {
    error_message = "Name must be a string";
    goto error;
  }

  name = name_json.u.string.ptr;

  rules_json = grammar_json->operator[]("rules");
  if (rules_json.type != json_object) {
    error_message = "Rules must be an object";
    goto error;
  }

  for (size_t i = 0, length = rules_json.u.object.length; i < length; i++) {
    json_object_entry entry_json = rules_json.u.object.values[i];
    auto result = parse_rule(entry_json.value);
    if (!result.error_message.empty()) {
      error_message = result.error_message;
      goto error;
    }
    grammar.variables.push_back(Variable{
      string(entry_json.name),
      VariableTypeNamed,
      result.rule
    });
  }

  extras_json = grammar_json->operator[]("extras");
  if (extras_json.type != json_none) {
    if (extras_json.type != json_array) {
      error_message = "Extras must be an array";
      goto error;
    }

    for (size_t i = 0, length = extras_json.u.array.length; i < length; i++) {
      json_value *extra_json = extras_json.u.array.values[i];
      auto result = parse_rule(extra_json);
      if (!result.error_message.empty()) {
        error_message = "Invalid extra token: " + result.error_message;
        goto error;
      }
      grammar.extra_tokens.push_back(result.rule);
    }
  }

  conflicts_json = grammar_json->operator[]("conflicts");
  if (conflicts_json.type != json_none) {
    if (conflicts_json.type != json_array) {
      error_message = "Conflicts must be an array";
      goto error;
    }

    for (size_t i = 0, length = conflicts_json.u.array.length; i < length; i++) {
      json_value *conflict_json = conflicts_json.u.array.values[i];
      if (conflict_json->type != json_array) {
        error_message = "Each conflict entry must be an array";
        goto error;
      }

      unordered_set<NamedSymbol> conflict;
      for (size_t j = 0, conflict_length = conflict_json->u.array.length;
           j < conflict_length; j++) {
        json_value *conflict_entry_json = conflict_json->u.array.values[j];
        if (conflict_entry_json->type != json_string) {
          error_message = "Each conflict entry must be an array of strings";
          goto error;
        }

        conflict.insert(rules::NamedSymbol{
          string(conflict_entry_json->u.string.ptr)
        });
      }

      grammar.expected_conflicts.push_back(conflict);
    }
  }

  inline_rules_json = grammar_json->operator[]("inline");
  if (inline_rules_json.type != json_none) {
    if (inline_rules_json.type != json_array) {
      error_message = "Inline rules must be an array";
      goto error;
    }

    for (size_t i = 0, length = inline_rules_json.u.array.length; i < length; i++) {
      json_value *inline_rule_json = inline_rules_json.u.array.values[i];
      if (inline_rule_json->type != json_string) {
        error_message = "Inline rules must be an array of rule names";
        goto error;
      }

      grammar.variables_to_inline.insert(rules::NamedSymbol{string(inline_rule_json->u.string.ptr)});
    }
  }

  external_tokens_json = grammar_json->operator[]("externals");
  if (external_tokens_json.type != json_none) {
    if (external_tokens_json.type != json_array) {
      error_message = "External tokens must be an array";
      goto error;
    }

    for (size_t i = 0, length = external_tokens_json.u.array.length; i < length; i++) {
      json_value *external_token_json = external_tokens_json.u.array.values[i];
      auto result = parse_rule(external_token_json);
      if (!result.error_message.empty()) {
        error_message = "Invalid external token: " + result.error_message;
        goto error;
      }
      grammar.external_tokens.push_back(result.rule);
    }
  }

  word_rule_json = grammar_json->operator[]("word");
  if (word_rule_json.type != json_none) {
    if (word_rule_json.type != json_string) {
      error_message = "Invalid word property";
      goto error;
    }

    grammar.word_token = NamedSymbol { word_rule_json.u.string.ptr };
  }

  json_value_free(grammar_json);
  return { name, grammar, "" };

error:
  if (grammar_json) {
    json_value_free(grammar_json);
  }

  return { "", InputGrammar(), error_message };
}

}  // namespace tree_sitter
