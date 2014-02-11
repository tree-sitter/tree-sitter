#include "parse_table.h"

using std::string;
using std::ostream;
using std::to_string;
using std::set;
using std::vector;
using tree_sitter::rules::Symbol;

namespace tree_sitter {
    // Action
    ParseAction::ParseAction(ParseActionType type, size_t state_index, rules::Symbol symbol, const vector<bool> &child_flags) :
        type(type),
        state_index(state_index),
        symbol(symbol),
        child_flags(child_flags) {};
    
    ParseAction ParseAction::Error() {
        return ParseAction(ParseActionTypeError, -1, Symbol(""), {});
    }
    
    ParseAction ParseAction::Accept() {
        return ParseAction(ParseActionTypeAccept, -1, Symbol(""), {});
    }
    
    ParseAction ParseAction::Shift(size_t state_index) {
        return ParseAction(ParseActionTypeShift, state_index, Symbol(""), {});
    }
    
    ParseAction ParseAction::Reduce(Symbol symbol, const vector<bool> &child_flags) {
        return ParseAction(ParseActionTypeReduce, -1, symbol, child_flags);
    }
    
    bool ParseAction::operator==(const ParseAction &other) const {
        bool types_eq = type == other.type;
        bool state_indices_eq = state_index == other.state_index;
        bool child_flags_eq = child_flags == other.child_flags;
        return types_eq && state_indices_eq && child_flags_eq;
    }
    
    bool ParseAction::operator<(const ParseAction &other) const {
        if (type < other.type) return true;
        if (type > other.type) return false;
        if (state_index < other.state_index) return true;
        if (state_index > other.state_index) return false;
        return (child_flags < other.child_flags);
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
                return stream << (string("#<reduce ") + action.symbol.name + ">");
        }
    }
    
    // State
    ParseState::ParseState() : lex_state_index(-1) {}
    
    set<rules::Symbol> ParseState::expected_inputs() const {
        set<rules::Symbol> result;
        for (auto pair : actions)
            result.insert(pair.first);
        return result;
    }
    
    ostream& operator<<(ostream &stream, const ParseState &state) {
        stream << string("#<parse_state ");
        bool started1 = false;
        for (auto pair : state.actions) {
            if (started1) stream << string(", ");
            stream << pair.first << string(" => #<set: ");
            bool started2 = false;
            for (auto action : pair.second) {
                if (started2) stream << string(", ");
                stream << action;
                started2 = true;
            }
            stream << string(">");
            started1 = true;
        }
        stream << string(">");
        return stream;
    }
    
    // Table
    size_t ParseTable::add_state() {
        states.push_back(ParseState());
        return states.size() - 1;
    }
    
    void ParseTable::add_action(size_t state_index, rules::Symbol symbol, ParseAction action) {
        symbols.insert(symbol);
        states[state_index].actions[symbol].insert(action);
    }
}
