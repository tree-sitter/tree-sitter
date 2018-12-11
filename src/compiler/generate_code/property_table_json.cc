#include "compiler/generate_code/property_table_json.h"
#include <vector>
#include <string>

using std::string;
using std::to_string;
using std::vector;

namespace tree_sitter {
namespace generate_code {

class CodeGenerator {
  string buffer;

 public:
  string generate(const PropertyTable &table) {
    add("{");
    add("\"states\":");
    add("[");
    for (unsigned i = 0; i < table.states.size(); i++) {
      const PropertyState &state = table.states[i];
      if (i != 0) add(",");
      add_state(i, state);
    }
    add("],");
    add("\"property_sets\":");
    add("[");
    bool first = true;
    for (const PropertySet &property_set : table.property_sets) {
      if (!first) add(",");
      first = false;
      add_property_set(property_set);
    }
    add("]");
    add("}");
    return buffer;
  }

 private:
  void add_state(unsigned i, const PropertyState &state) {
    add("{");
    add("\"id\":");
    add(to_string(i));
    add(",\"property_set_id\":");
    add(to_string(state.property_set_id));
    add(",");
    add("\"transitions\":[");
    bool first = true;
    for (const auto &transition : state.transitions) {
      if (!first) add(",");
      first = false;
      add_transition(transition);
    }
    add("],");
    add("\"default_next_state_id\":");
    add(to_string(state.default_next_state_id));
    add("}");
  }

  void add_property_set(const PropertySet &property_set) {
    add("{");
    bool first = true;
    for (const auto &pair : property_set) {
      if (!first) add(",");
      first = false;
      add_string(pair.first);
      add(":");
      add_string(pair.second);
    }
    add("}");
  }

  void add_transition(const PropertyTransition &transition) {
    add("{");
    add("\"type\":");
    add_string(transition.type);
    add(",\"named\":");
    add(transition.named ? "true" : "false");
    if (transition.index != -1) {
      add(",\"index\":");
      add(to_string(transition.index));
    }
    if (!transition.text_pattern.empty()) {
      add(",\"text\":");
      add_string(transition.text_pattern);
    }
    add(",\"state_id\": ");
    add(to_string(transition.state_id));
    add("}");
  }

  void add_string(const string &s) {
    add("\"");
    for (const char c : s) {
      if (c == '"' || c == '\\') add("\\");
      add(c);
    }
    add("\"");
  }

  void add(string input) {
    buffer += input;
  }

  void add(char c) {
    buffer += c;
  }
};

string property_table_json(PropertyTable table) {
  return CodeGenerator().generate(table);
}

}  // namespace generate_code
}  // namespace tree_sitter
