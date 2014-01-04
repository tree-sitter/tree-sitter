#include "parse_table.h"

using std::string;
using std::ostream;
using std::to_string;

namespace tree_sitter {
    namespace lr {
        // Action
        ParseAction::ParseAction(ParseActionType type, size_t state_index, string symbol_name, size_t child_symbol_count) :
            type(type),
            state_index(state_index),
            symbol_name(symbol_name),
            child_symbol_count(child_symbol_count) {};

        ParseAction ParseAction::Error() {
            return ParseAction(ParseActionTypeError, -1, "", -1);
        }

        ParseAction ParseAction::Accept() {
            return ParseAction(ParseActionTypeAccept, -1, "", -1);
        }
        
        ParseAction ParseAction::Shift(size_t state_index) {
            return ParseAction(ParseActionTypeShift, state_index, "", -1);
        }

        ParseAction ParseAction::Reduce(std::string symbol_name, size_t child_symbol_count) {
            return ParseAction(ParseActionTypeReduce, -1, symbol_name, child_symbol_count);
        }

        bool ParseAction::operator==(const ParseAction &other) const {
            bool types_eq = type == other.type;
            bool state_indices_eq = state_index == other.state_index;
            bool child_symbol_counts_eq = child_symbol_count == other.child_symbol_count;
            return types_eq && state_indices_eq && child_symbol_counts_eq;
        }
        
        ostream& operator<<(ostream &stream, const ParseAction &action) {
            switch (action.type) {
                case ParseActionTypeError:
                    return stream << string("#<error>");
                case ParseActionTypeAccept:
                    return stream << string("#<accept>");
                case ParseActionTypeShift:
                    return stream << (string("#<shift ") + to_string(action.state_index) + ">");
                case ParseActionTypeReduce:
                    return stream << (string("#<reduce ") + action.symbol_name + ">");
            }
        }
        
        // State
        ParseState::ParseState() : lex_state_index(-1) {}
        
        // Table
        size_t ParseTable::add_state() {
            states.push_back(ParseState());
            return states.size() - 1;
        }
        
        void ParseTable::add_action(size_t state_index, string sym_name, ParseAction action) {
            states[state_index].actions[sym_name].insert(action);
        }

        void ParseTable::add_default_action(size_t state_index, ParseAction action) {
            states[state_index].default_actions.insert(action);
        }
        
        const string ParseTable::START = "__START__";
        const string ParseTable::END_OF_INPUT = "__END__";
    }
}
