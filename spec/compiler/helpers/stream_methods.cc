#include "compiler/helpers/stream_methods.h"
#include "compiler/compiler_spec_helper.h"
#include "tree_sitter/compiler.h"
#include "compiler/parse_table.h"
#include "compiler/build_tables/parse_item.h"
#include "compiler/build_tables/lex_item.h"
#include "compiler/build_tables/get_metadata.h"

namespace tree_sitter {

ostream &operator<<(ostream &stream, const Grammar &grammar) {
  stream << string("#<grammar");
  stream << string(" rules: {");
  bool started = false;
  for (auto pair : grammar.rules()) {
    if (started)
      stream << string(", ");
    stream << pair.first;
    stream << string(" => ");
    stream << pair.second;
    started = true;
  }
  return stream << string("}>");
}

ostream &operator<<(ostream &stream, const GrammarError *error) {
  if (error)
    return stream << (string("#<grammar-error '") + error->message + "'>");
  else
    return stream << string("#<null>");
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

ostream &operator<<(ostream &stream, const RuleEntry &entry) {
  return stream << string("{") << entry.name << string(", ") << entry.rule << string(", ") << to_string(entry.type) << string("}");
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
      return stream << (string("#<shift ") + to_string(action.state_index) +
                        ">");
    case ParseActionTypeShiftExtra:
      return stream << string("#<shift_extra");
    case ParseActionTypeReduceExtra:
      return stream << ("#<reduce_extra sym" + to_string(action.symbol.index) +
                        ">");
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

namespace build_tables {

ostream &operator<<(ostream &stream, const build_tables::LexItem &item) {
  return stream << string("(item ") << item.lhs << string(" ") << *item.rule
                << string(")");
}

ostream &operator<<(ostream &stream, const build_tables::ParseItem &item) {
  return stream << string("(item ") << item.lhs << string(" ") << *item.rule
                << string(")");
}

std::ostream &operator<<(std::ostream &stream, const MetadataRange &range) {
  return stream << string("{") << to_string(range.min) << string(", ")
                << to_string(range.max) << string("}");
}

}  // namespace build_tables

} // namespace tree_sitter
