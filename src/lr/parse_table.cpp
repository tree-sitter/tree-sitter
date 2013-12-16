#include "parse_table.h"

using namespace std;

namespace tree_sitter {
    namespace lr {
        // Action
        ParseAction::ParseAction() :
            type(ParseActionTypeError),
            state_index(-1),
            symbol_name(""),
            child_symbol_count(-1) {};

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
            bool symbol_ids_eq = symbol_name == other.symbol_name;
            bool child_symbol_counts_eq = child_symbol_count == other.child_symbol_count;
            return types_eq && state_indices_eq && symbol_ids_eq && child_symbol_counts_eq;
        }
        
        ostream& operator<<(ostream &stream, const ParseAction &action) {
            switch (action.type) {
                case ParseActionTypeAccept:
                    return stream << string("accept");
                case ParseActionTypeAdvance:
                    return stream << (string("(advance ") + to_string(action.state_index) + ")");
                case ParseActionTypeShift:
                    return stream << (string("(shift ") + to_string(action.state_index) + ")");
                case ParseActionTypeReduce:
                    return stream << (string("(reduce ") + action.symbol_name + ")");
                case ParseActionTypeError:
                    return stream << string("error");
            }
        }
        
        // State
        ParseState::ParseState() : actions(unordered_map<string, unordered_set<ParseAction>>()) {}
        
        // Table
        unordered_map<string, size_t> get_symbol_id_map(const vector<string> &names) {
            unordered_map<string, size_t> result;
            size_t i = 0;
            for (string name : names) {
                result[name] = i;
                i++;
            }
            return result;
        }
        
        ParseTable::ParseTable(vector<string> symbol_names) :
            symbol_ids(get_symbol_id_map(symbol_names)),
            symbol_names(symbol_names),
            states(vector<ParseState>()) {};
        
        size_t ParseTable::add_state() {
            states.push_back(ParseState());
            return states.size() - 1;
        }
        
        void ParseTable::add_action(size_t state_index, string sym_name, ParseAction action) {
            states[state_index].actions[sym_name].insert(action);
        }
        
        ParseState ParseTable::starting_state() const {
            return states[0];
        }
        
        unordered_map<string, unordered_set<ParseAction>> ParseTable::actions_for(size_t state_index) const {
            return states[state_index].actions;
        }
        
        const string ParseTable::START = "__START__";
        const string ParseTable::END_OF_INPUT = "__END__";
    }
}