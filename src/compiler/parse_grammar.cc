#include "compiler/parse_grammar.h"
#include <string>
#include <vector>
#include <utility>
#include "json.h"
#include "compiler/rule.h"
#include "compiler/rules.h"

namespace tree_sitter {

using std::string;
using std::vector;
using std::pair;

struct ParseRuleResult {
  rule_ptr rule;
  string error_message;
};

ParseRuleResult parse_rule(json_value *rule_json) {
  string error_message;
  json_value rule_type_json;
  string type;

  if (!rule_json) {
    error_message = "Rule cannot be null";
    goto error;
  }

  if (rule_json->type != json_object) {
    error_message = "Rule type must be an object";
    goto error;
  }

  rule_type_json = rule_json->operator[]("type");
  if (rule_type_json.type != json_string) {
    error_message = "Rule type must be a string";
    goto error;
  }

  type = rule_type_json.u.string.ptr;

  if (type == "BLANK") {
    return { blank(), "" };
  }

  if (type == "CHOICE") {
    json_value members_json = rule_json->operator[]("members");
    if (members_json.type != json_array) {
      error_message = "Choice members must be an array";
      goto error;
    }

    vector<rule_ptr> members;
    for (size_t i = 0, length = members_json.u.array.length; i < length; i++) {
      json_value *member_json = members_json.u.array.values[i];
      ParseRuleResult member = parse_rule(member_json);
      if (member.rule.get()) {
        members.push_back(member.rule);
      } else {
        error_message = "Invalid choice member: " + member.error_message;
        goto error;
      }
    }
    return { choice(members), "" };
  }

  if (type == "SEQ") {
    json_value members_json = rule_json->operator[]("members");
    if (members_json.type != json_array) {
      error_message = "Seq members must be an array";
      goto error;
    }

    vector<rule_ptr> members;
    for (size_t i = 0, length = members_json.u.array.length; i < length; i++) {
      json_value *member_json = members_json.u.array.values[i];
      ParseRuleResult member = parse_rule(member_json);
      if (member.rule.get()) {
        members.push_back(member.rule);
      } else {
        error_message = "Invalid seq member: " + member.error_message;
        goto error;
      }
    }
    return { seq(members), "" };
  }

  if (type == "ERROR") {
    json_value content_json = rule_json->operator[]("content");
    ParseRuleResult content = parse_rule(&content_json);
    if (content.rule.get()) {
      return { err(content.rule), "" };
    } else {
      error_message = "Invalid error content: " + content.error_message;
      goto error;
    }
  }

  if (type == "REPEAT") {
    json_value content_json = rule_json->operator[]("content");
    ParseRuleResult content = parse_rule(&content_json);
    if (content.rule.get()) {
      return { repeat(content.rule), "" };
    } else {
      error_message = "Invalid repeat content: " + content.error_message;
      goto error;
    }
  }

  if (type == "REPEAT1") {
    json_value content_json = rule_json->operator[]("content");
    ParseRuleResult content = parse_rule(&content_json);
    if (content.rule.get()) {
      return { repeat1(content.rule), "" };
    } else {
      error_message = "Invalid repeat1 content: " + content.error_message;
      goto error;
    }
  }

  if (type == "TOKEN") {
    json_value content_json = rule_json->operator[]("content");
    ParseRuleResult content = parse_rule(&content_json);
    if (content.rule.get()) {
      return { token(content.rule), "" };
    } else {
      error_message = "Invalid token content: " + content.error_message;
      goto error;
    }
  }

  if (type == "PATTERN") {
    json_value value_json = rule_json->operator[]("value");
    if (value_json.type == json_string) {
      return { pattern(value_json.u.string.ptr), "" };
    } else {
      error_message = "Pattern value must be a string";
      goto error;
    }
  }

  if (type == "STRING") {
    json_value value_json = rule_json->operator[]("value");
    if (value_json.type == json_string) {
      return { str(value_json.u.string.ptr), "" };
    } else {
      error_message = "String rule value must be a string";
      goto error;
    }
  }

  if (type == "SYMBOL") {
    json_value value_json = rule_json->operator[]("name");
    if (value_json.type == json_string) {
      return { sym(value_json.u.string.ptr), "" };
    } else {
      error_message = "Symbol value must be a string";
      goto error;
    }
  }

  if (type == "PREC") {
    json_value precedence_json = rule_json->operator[]("value");
    if (precedence_json.type != json_integer) {
      error_message = "Precedence value must be an integer";
      goto error;
    }

    json_value content_json = rule_json->operator[]("content");
    ParseRuleResult content = parse_rule(&content_json);
    if (!content.rule.get()) {
      error_message = "Invalid precedence content: " + content.error_message;
      goto error;
    }

    return { prec(precedence_json.u.integer, content.rule), "" };
  }

  if (type == "PREC_LEFT") {
    json_value precedence_json = rule_json->operator[]("value");
    if (precedence_json.type != json_integer) {
      error_message = "Precedence value must be an integer";
      goto error;
    }

    json_value content_json = rule_json->operator[]("content");
    ParseRuleResult content = parse_rule(&content_json);
    if (!content.rule.get()) {
      error_message = "Invalid precedence content: " + content.error_message;
      goto error;
    }

    return { prec_left(precedence_json.u.integer, content.rule), "" };
  }

  if (type == "PREC_RIGHT") {
    json_value precedence_json = rule_json->operator[]("value");
    if (precedence_json.type != json_integer) {
      error_message = "Precedence value must be an integer";
      goto error;
    }

    json_value content_json = rule_json->operator[]("content");
    ParseRuleResult content = parse_rule(&content_json);
    if (!content.rule.get()) {
      error_message = "Invalid precedence content: " + content.error_message;
      goto error;
    }

    return { prec_right(precedence_json.u.integer, content.rule), "" };
  }

  error_message = "Unknown rule type " + type;

error:
  return { rule_ptr(), error_message };
}

ParseGrammarResult parse_grammar(const string &input) {
  string error_message;
  string name;
  Grammar grammar;
  json_value name_json, rules_json, extras_json, conflicts_json;

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
    ParseRuleResult entry = parse_rule(entry_json.value);

    if (!entry.rule.get()) {
      error_message =
        string("Invalid rule '") + entry_json.name + "' " + entry.error_message;
      goto error;
    }

    grammar.rules.push_back({ string(entry_json.name), entry.rule });
  }

  extras_json = grammar_json->operator[]("extras");
  if (extras_json.type != json_none) {
    if (extras_json.type != json_array) {
      error_message = "Extras must be an array";
      goto error;
    }

    for (size_t i = 0, length = extras_json.u.array.length; i < length; i++) {
      json_value *extra_json = extras_json.u.array.values[i];
      ParseRuleResult extra = parse_rule(extra_json);
      if (!extra.rule.get()) {
        error_message = string("Invalid extra token: ") + extra.error_message;
        goto error;
      }

      grammar.extra_tokens.push_back(extra.rule);
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

      vector<string> conflict;
      for (size_t j = 0, conflict_length = conflict_json->u.array.length;
           j < conflict_length; j++) {
        json_value *conflict_entry_json = conflict_json->u.array.values[j];
        if (conflict_entry_json->type != json_string) {
          error_message = "Each conflict entry must be an array of strings";
          goto error;
        }

        conflict.push_back(string(conflict_entry_json->u.string.ptr));
      }

      grammar.expected_conflicts.push_back(conflict);
    }
  }

  json_value_free(grammar_json);
  return { name, grammar, "" };

error:
  if (grammar_json) {
    json_value_free(grammar_json);
  }

  return { "", Grammar(), error_message };
}

}  // namespace tree_sitter
