#include "compiler/rules/metadata.h"
#include <climits>
#include <string>
#include "compiler/rule.h"

namespace tree_sitter {
namespace rules {

using std::move;
using std::string;

bool Alias::operator==(const Alias &other) const {
  return value == other.value && is_named == other.is_named;
}

bool Alias::operator!=(const Alias &other) const {
  return !operator==(other);
}

bool Alias::operator<(const Alias &other) const {
  if (value < other.value) return true;
  if (other.value < value) return false;
  return is_named < other.is_named;
}

Metadata::Metadata(const Rule &rule, MetadataParams params) :
  rule(std::make_shared<Rule>(rule)), params(params) {}

bool Metadata::operator==(const Metadata &other) const {
  return rule->operator==(*other.rule) && params == other.params;
}

template <typename T>
static Metadata add_metadata(Rule &&rule, T &&callback) {
  if (rule.is<Metadata>()) {
    Metadata metadata = rule.get_unchecked<Metadata>();
    callback(metadata.params);
    return metadata;
  } else {
    MetadataParams params;
    callback(params);
    return Metadata{move(rule), params};
  }
}

Metadata Metadata::merge(Rule &&rule, MetadataParams new_params) {
  return add_metadata(move(rule), [&](MetadataParams &params) {
    if (new_params.has_precedence && !params.has_precedence) {
      params.has_precedence = true;
      params.precedence = new_params.precedence;
    }

    if (new_params.has_associativity && !params.has_associativity) {
      params.has_associativity = true;
      params.associativity = new_params.associativity;
    }

    if (new_params.dynamic_precedence != 0) {
      params.dynamic_precedence = new_params.dynamic_precedence;
    }

    if (new_params.is_string) params.is_string = true;
    if (new_params.is_active) params.is_active = true;
    if (new_params.is_main_token) params.is_main_token = true;

    if (!new_params.alias.value.empty()) {
      params.alias = new_params.alias;
    }
  });
}

Metadata Metadata::token(Rule &&rule) {
  return add_metadata(move(rule), [](MetadataParams &params) {
    params.is_token = true;
  });
}

Metadata Metadata::immediate_token(Rule &&rule) {
  return add_metadata(move(rule), [](MetadataParams &params) {
    params.is_token = true;
    params.is_main_token = true;
  });
}

Metadata Metadata::active_prec(int precedence, Rule &&rule) {
  return add_metadata(move(rule), [&](MetadataParams &params) {
    params.has_precedence = true;
    params.precedence = precedence;
    params.is_active = true;
  });
}

Metadata Metadata::prec(int precedence, Rule &&rule) {
  return add_metadata(move(rule), [&](MetadataParams &params) {
    if (!params.has_precedence) {
      params.has_precedence = true;
      params.precedence = precedence;
    }
  });
}

Metadata Metadata::prec_left(int precedence, Rule &&rule) {
  return add_metadata(move(rule), [&](MetadataParams &params) {
    if (!params.has_precedence) {
      params.has_precedence = true;
      params.precedence = precedence;
    }
    if (!params.has_associativity) {
      params.has_associativity = true;
      params.associativity = AssociativityLeft;
    }
  });
}

Metadata Metadata::prec_right(int precedence, Rule &&rule) {
  return add_metadata(move(rule), [&](MetadataParams &params) {
    if (!params.has_precedence) {
      params.has_precedence = true;
      params.precedence = precedence;
    }
    if (!params.has_associativity) {
      params.has_associativity = true;
      params.associativity = AssociativityRight;
    }
  });
}

Metadata Metadata::prec_dynamic(int dynamic_precedence, Rule &&rule) {
  return add_metadata(move(rule), [&](MetadataParams &params) {
    params.dynamic_precedence = dynamic_precedence;
  });
}

Metadata Metadata::separator(Rule &&rule) {
  return add_metadata(move(rule), [&](MetadataParams &params) {
    if (!params.has_precedence) {
      params.has_precedence = true;
      params.precedence = INT_MIN;
    }
    params.is_active = true;
  });
}

Metadata Metadata::main_token(Rule &&rule) {
  return add_metadata(move(rule), [&](MetadataParams &params) {
    if (!params.has_precedence) {
      params.has_precedence = true;
      params.precedence = 0;
    }
    params.is_main_token = true;
  });
}

Metadata Metadata::alias(string &&value, bool is_named, Rule &&rule) {
  return add_metadata(move(rule), [&](MetadataParams &params) {
    params.alias.value = move(value);
    params.alias.is_named = is_named;
  });
}

}  // namespace rules
}  // namespace tree_sitter
