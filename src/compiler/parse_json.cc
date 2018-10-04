#include "compiler/parse_json.h"
#include <string>
#include <vector>
#include <unordered_set>
#include <utility>
#include "json.h"
#include "compiler/rule.h"
#include "compiler/util/result.h"

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
using util::Result;

Result<Rule> parse_rule_json(json_value *rule_json) {
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
      auto result = parse_rule_json(member_json);
      if (!result.ok()) {
        return "Invalid choice member: " + result.error;
      }
      members.push_back(result.value);
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
      auto result = parse_rule_json(member_json);
      if (!result.ok()) {
        return "Invalid choice member: " + result.error;
      }
      members.push_back(result.value);
    }
    return Rule::seq(members);
  }

  if (type == "REPEAT") {
    json_value content_json = rule_json->operator[]("content");
    auto result = parse_rule_json(&content_json);
    if (!result.ok()) {
      return "Invalid repeat content: " + result.error;
    }
    return Rule::choice({Rule::repeat(result.value), Blank{}});
  }

  if (type == "REPEAT1") {
    json_value content_json = rule_json->operator[]("content");
    auto result = parse_rule_json(&content_json);
    if (!result.ok()) {
      return "Invalid repeat content: " + result.error;
    }
    return Rule::repeat(result.value);
  }

  if (type == "TOKEN") {
    json_value content_json = rule_json->operator[]("content");
    auto result = parse_rule_json(&content_json);
    if (!result.ok()) {
      return "Invalid token content: " + result.error;
    }
      return Rule(Metadata::token(move(result.value)));
  }

  if (type == "IMMEDIATE_TOKEN") {
    json_value content_json = rule_json->operator[]("content");
    auto result = parse_rule_json(&content_json);
    if (!result.ok()) {
      return "Invalid token content: " + result.error;
    }
      return Rule(Metadata::immediate_token(move(result.value)));
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
    auto result = parse_rule_json(&content_json);
    if (!result.ok()) {
      return "Invalid precedence content: " + result.error;
    }
    return Rule(Metadata::prec(precedence_json.u.integer, move(result.value)));
  }

  if (type == "PREC_LEFT") {
    json_value precedence_json = rule_json->operator[]("value");
    if (precedence_json.type != json_integer) {
      return "Precedence value must be an integer";
    }

    json_value content_json = rule_json->operator[]("content");
    auto result = parse_rule_json(&content_json);
    if (!result.ok()) {
      return "Invalid precedence content: " + result.error;
    }
    return Rule(Metadata::prec_left(precedence_json.u.integer, move(result.value)));
  }

  if (type == "PREC_RIGHT") {
    json_value precedence_json = rule_json->operator[]("value");
    if (precedence_json.type != json_integer) {
      return "Precedence value must be an integer";
    }

    json_value content_json = rule_json->operator[]("content");
    auto result = parse_rule_json(&content_json);
    if (!result.ok()) {
      return "Invalid precedence content: " + result.error;
    }
    return Rule(Metadata::prec_right(precedence_json.u.integer, move(result.value)));
  }

  if (type == "PREC_DYNAMIC") {
    json_value precedence_json = rule_json->operator[]("value");
    if (precedence_json.type != json_integer) {
      return "Precedence value must be an integer";
    }

    json_value content_json = rule_json->operator[]("content");
    auto result = parse_rule_json(&content_json);
    if (!result.ok()) {
      return "Invalid precedence content: " + result.error;
    }
    return Rule(Metadata::prec_dynamic(precedence_json.u.integer, move(result.value)));
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
    auto result = parse_rule_json(&content_json);
    if (!result.ok()) {
      return "Invalid rename content: " + result.error;
    }
    return Rule(Metadata::alias(
      string(value_json.u.string.ptr),
      is_named_json.u.boolean,
      move(result.value)
    ));
  }

  return "Unknown rule type: " + type;
}

ParseGrammarResult parse_grammar_json(const string &input) {
  string error_message;
  string name;
  InputGrammar grammar;
  json_value
    name_json, rules_json, extras_json, conflicts_json, external_tokens_json,
    inline_rules_json, word_rule_json;

  char parse_error[json_error_max];
  json_settings settings = { 0, json_enable_comments, 0, 0, 0, 0 };
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
    auto result = parse_rule_json(entry_json.value);
    if (!result.ok()) {
      error_message = result.error;
      goto error;
    }
    grammar.variables.push_back(Variable{
      string(entry_json.name),
      VariableTypeNamed,
      result.value
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
      auto result = parse_rule_json(extra_json);
      if (!result.ok()) {
        error_message = "Invalid extra token: " + result.error;
        goto error;
      }
      grammar.extra_tokens.push_back(result.value);
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
      auto result = parse_rule_json(external_token_json);
      if (!result.ok()) {
        error_message = "Invalid external token: " + result.error;
        goto error;
      }
      grammar.external_tokens.push_back(result.value);
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
  if (grammar_json) json_value_free(grammar_json);
  return { "", InputGrammar(), error_message };
}

Result<PropertyRule> parse_property_rule_json(json_value *rule_json) {
  PropertyRule result;

  if (rule_json->type != json_object) return "Rule must be an object";

  json_value selectors_json = rule_json->operator[]("selectors");
  if (selectors_json.type != json_array) return "Selectors must be an array";

  for (unsigned i = 0; i < selectors_json.u.array.length; i++) {
    PropertySelector selector;
    json_value *selector_json = selectors_json.u.array.values[i];
    if (selector_json->type != json_array) return "Each selector must be an array";

    for (unsigned j = 0; j < selector_json->u.array.length; j++) {
      json_value *selector_step_json = selector_json->u.array.values[j];
      if (selector_step_json->type != json_object) return "Each selector must be an array of objects";
      PropertySelectorStep step;
      step.type = selector_step_json->operator[]("type").u.string.ptr;
      step.named = selector_step_json->operator[]("named").u.boolean;
      step.is_immediate = selector_step_json->operator[]("immediate").u.boolean;

      json_value index_json = selector_step_json->operator[]("index");
      if (index_json.type == json_integer) {
        step.index = index_json.u.integer;
      } else {
        step.index = -1;
      }

      json_value text_pattern_json = selector_step_json->operator[]("text");
      if (text_pattern_json.type == json_string) {
        step.text_pattern = text_pattern_json.u.string.ptr;
      }

      selector.push_back(step);
    }

    result.selectors.push_back(selector);
  }

  json_value properties_json = rule_json->operator[]("properties");
  if (properties_json.type != json_object) return "Properties must be an object";

  for (unsigned i = 0; i < properties_json.u.object.length; i++) {
    json_object_entry entry_json = properties_json.u.object.values[i];
    json_value *value_json = entry_json.value;
    if (value_json->type != json_string) return "Property values must be strings";
    result.properties[entry_json.name] = value_json->u.string.ptr;
  }

  return result;
}

Result<PropertySheet> parse_property_sheet_json(const string &input) {
  PropertySheet sheet;
  string error_message;
  char parse_error[json_error_max];
  json_settings settings = { 0, json_enable_comments, 0, 0, 0, 0 };
  json_value *sheet_json = json_parse_ex(&settings, input.c_str(), input.size(), parse_error);
  if (!sheet_json) {
    error_message = string("Invalid JSON at ") + parse_error;
    goto error;
  }

  if (sheet_json->type != json_array) {
    error_message = "Property sheet must be an array";
    goto error;
  }

  for (unsigned i = 0; i < sheet_json->u.array.length; i++) {
    json_value *rule_json = sheet_json->u.array.values[i];
    auto result = parse_property_rule_json(rule_json);
    if (!result.ok()) {
      error_message = "Invalid external token: " + result.error;
      goto error;
    }
    sheet.push_back(result.value);
  }

  return sheet;

error:
  if (sheet_json) json_value_free(sheet_json);
  return error_message.c_str();
}

}  // namespace tree_sitter
