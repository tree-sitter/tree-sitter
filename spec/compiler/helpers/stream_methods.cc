#include "compiler/helpers/stream_methods.h"
#include "compiler/compiler_spec_helper.h"
#include "tree_sitter/compiler.h"
#include "compiler/parse_table.h"
#include "compiler/syntax_grammar.h"
#include "compiler/build_tables/parse_item.h"
#include "compiler/build_tables/lex_item.h"

namespace tree_sitter {

ostream &operator<<(ostream &stream, const Grammar &grammar) {
  stream << string("#<grammar");
  stream << string(" rules: {");
  bool started = false;
  for (auto pair : grammar.rules) {
    if (started)
      stream << string(", ");
    stream << pair.first;
    stream << string(" => ");
    stream << pair.second;
    started = true;
  }
  return stream << string("}>");
}

ostream &operator<<(ostream &stream, const CompileError &error) {
  if (error.type)
    return stream << (string("#<compile-error '") + error.message + "'>");
  else
    return stream << string("#<no-compile-error>");
}

ostream &operator<<(ostream &stream, const Rule &rule) {
  return stream << rule.to_string();
}

ostream &operator<<(ostream &stream, const rule_ptr &rule) {
  if (rule.get())
    stream << *rule;
  else
    stream << string("(null-rule)");
  return stream;
}

ostream &operator<<(ostream &stream, const Variable &variable) {
  return stream << string("{") << variable.name << string(", ") << variable.rule << string(", ") << to_string(variable.type) << string("}");
}

ostream &operator<<(ostream &stream, const SyntaxVariable &variable) {
  return stream << string("{") << variable.name << string(", ") << variable.productions << string(", ") << to_string(variable.type) << string("}");
}

std::ostream &operator<<(std::ostream &stream, const LexAction &action) {
  switch (action.type) {
    case LexActionTypeError:
      return stream << string("#<error>");
    case LexActionTypeAccept:
      return stream << string("#<accept ") + to_string(action.symbol.index) +
                         ">";
    case LexActionTypeAdvance:
      return stream << string("#<advance ") + to_string(action.state_index) +
                         ">";
    default:
      return stream;
  }
}

ostream &operator<<(ostream &stream, const ParseAction &action) {
  switch (action.type) {
    case ParseActionTypeError:
      return stream << string("#<error>");
    case ParseActionTypeAccept:
      return stream << string("#<accept>");
    case ParseActionTypeShift:
      return stream << string("#<shift state:") << to_string(action.state_index) <<
                        string(" precedence:") << action.precedence_range << ">";
    case ParseActionTypeReduce:
      return stream << ("#<reduce sym" + to_string(action.symbol.index) + " " +
                        to_string(action.consumed_symbol_count) + ">");
    default:
      return stream;
  }
}

ostream &operator<<(ostream &stream, const ParseState &state) {
  stream << string("#<parse_state ");
  bool started = false;
  for (auto pair : state.actions) {
    if (started)
      stream << string(", ");
    stream << pair.first << string(" => {");
    for (auto &action : pair.second) {
      stream << string(" ") << action;
    }
    stream << string("}");
    started = true;
  }
  stream << string(">");
  return stream;
}

ostream &operator<<(ostream &stream, const ProductionStep &step) {
  return stream << string("(production_step symbol:") << step.symbol << string(" precedence:") << to_string(step.precedence) << ")";
}

ostream &operator<<(ostream &stream, const PrecedenceRange &range) {
  if (range.empty)
    return stream << string("{empty}");
  else
    return stream << string("{") << to_string(range.min) << string(", ") << to_string(range.max) << string("}");
}

namespace build_tables {

ostream &operator<<(ostream &stream, const LexItem &item) {
  return stream << string("(item ") << item.lhs << string(" ") << *item.rule
                << string(")");
}

ostream &operator<<(ostream &stream, const LexItemSet &item_set) {
  return stream << item_set.entries;
}

ostream &operator<<(ostream &stream, const ParseItem &item) {
  return stream << string("(item variable:") << to_string(item.variable_index)
                << string(" production:") << to_string((size_t)item.production % 1000)
                << string(" step:") << to_string(item.step_index)
                << string(")");
}

std::ostream &operator<<(std::ostream &stream, const ParseItemSet &item_set) {
  return stream << item_set.entries;
}

std::ostream &operator<<(std::ostream &stream, const LookaheadSet &set) {
  return stream << *set.entries;
}

}  // namespace build_tables

} // namespace tree_sitter
