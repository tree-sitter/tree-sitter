#include "helpers/stream_methods.h"
#include "test_helper.h"
#include "tree_sitter/compiler.h"
#include "compiler/util/string_helpers.h"
#include "compiler/parse_table.h"
#include "compiler/syntax_grammar.h"
#include "compiler/lexical_grammar.h"
#include "compiler/build_tables/parse_item.h"
#include "compiler/build_tables/lex_item.h"

namespace tree_sitter {

ostream &operator<<(ostream &stream, const InputGrammar &grammar) {
  return stream << "(InputGrammar variables: " << grammar.variables << ")";
}

ostream &operator<<(ostream &stream, const CompileError &error) {
  if (error.type) {
    return stream << "(CompileError " << error.message << ")";
  } else {
    return stream << "(No CompileError)";
  }
}

namespace rules {

ostream &operator<<(ostream &stream, Associativity associativity) {
  switch (associativity) {
    case AssociativityLeft:
      return stream << "AssociativityLeft";
    case AssociativityRight:
      return stream << "AssociativityRight";
    case AssociativityNone:
      return stream << "AssociativityNone";
  }
}

ostream &operator<<(ostream &stream, const Blank &) {
  return stream << "(Blank)";
}

ostream &operator<<(ostream &stream, const CharacterRange &range) {
  if (range.min == range.max) {
    return stream << util::escape_char(range.min);
  } else {
    return stream << "(" + util::escape_char(range.min) << "-" << util::escape_char(range.max) << ")";
  }
}

ostream &operator<<(ostream &stream, const CharacterSet &rule) {
  stream << "(CharacterSet";
  if (rule.includes_all) {
    if (rule.excluded_chars.empty()) {
      stream << " all";
    } else {
      stream << " exclude";
      for (const auto &range : rule.excluded_ranges()) {
        stream << " " << range;
      }
    }
  } else {
    for (const auto &range : rule.included_ranges()) {
      stream << " " << range;
    }
  }
  return stream << ")";
}

ostream &operator<<(ostream &stream, const Symbol &rule) {
  stream << "(Symbol ";
  switch (rule.type) {
    case Symbol::External:
      stream << "external";
      break;
    case Symbol::Terminal:
      stream << "terminal";
      break;
    case Symbol::NonTerminal:
      stream << "non-terminal";
      break;
  }
  return stream << " " << rule.index << ")";
}

ostream &operator<<(ostream &stream, const NamedSymbol &rule) {
  return stream << "(NamedSymbol " << rule.value << ")";
}

ostream &operator<<(ostream &stream, const String &rule) {
  return stream << "(String " << rule.value << ")";
}

ostream &operator<<(ostream &stream, const Pattern &rule) {
  return stream << "(Pattern " << rule.value << ")";
}

ostream &operator<<(ostream &stream, const Choice &rule) {
  stream << "(Choice";
  for (const auto &element : rule.elements) {
    stream << " " << element;
  }
  return stream << ")";
}

ostream &operator<<(ostream &stream, const Seq &rule) {
  return stream << "(Seq " << *rule.left << " " << *rule.right << ")";
}

ostream &operator<<(ostream &stream, const Repeat &rule) {
  return stream << "(Repeat " << *rule.rule << ")";
}

ostream &operator<<(ostream &stream, const Metadata &rule) {
  return stream << "(Metadata " << *rule.rule << ")";
}

ostream &operator<<(ostream &stream, const Rule &rule) {
  rule.match(
    [&stream](Blank r) { stream << r; },
    [&stream](NamedSymbol r) { stream << r; },
    [&stream](Symbol r) { stream << r; },
    [&stream](String r) { stream << r; },
    [&stream](Pattern r) { stream << r; },
    [&stream](CharacterSet r) { stream << r; },
    [&stream](Choice r) { stream << r; },
    [&stream](Seq r) { stream << r; },
    [&stream](Repeat r) { stream << r; },
    [&stream](Metadata r) { stream << r; }
  );
  return stream;
}

}  // namespace rules

ostream &operator<<(ostream &stream, const Variable &variable) {
  return stream << "(Variable " << variable.name << " " << variable.rule << ")";
}

ostream &operator<<(ostream &stream, const SyntaxVariable &variable) {
  return stream << "(Variable " << variable.name << " " << variable.productions <<
    " " << to_string(variable.type) << "}";
}

ostream &operator<<(ostream &stream, const LexicalVariable &variable) {
  return stream << "(Variable " << variable.name << " " << to_string(variable.type) <<
    " " << variable.rule << ")";
}

ostream &operator<<(ostream &stream, const ExternalToken &external_token) {
  return stream << "(ExternalToken " << external_token.name << " " <<
    external_token.type << " " << external_token.corresponding_internal_token << ")";
}

ostream &operator<<(ostream &stream, const ProductionStep &step) {
  return stream << "(ProductionStep " << step.symbol << " precedence:" <<
    to_string(step.precedence) << " associativity:" << step.associativity << ")";
}

ostream &operator<<(ostream &stream, const PrecedenceRange &range) {
  if (range.empty) {
    return stream << "(PrecedenceRange)";
  } else {
    return stream << "(PrecedenceRange " << to_string(range.min) << " " <<
      to_string(range.max) << ")";
  }
}

namespace build_tables {

ostream &operator<<(ostream &stream, const LexItem &item) {
  return stream << "(LexItem " << item.lhs << " " << item.rule << ")";
}

ostream &operator<<(ostream &stream, const LexItemSet &item_set) {
  return stream << item_set.entries;
}

ostream &operator<<(ostream &stream, const LexItemSet::Transition &transition) {
  return stream << "(Transition " << transition.destination << " prec:" << transition.precedence << ")";
}

}  // namespace build_tables

} // namespace tree_sitter
