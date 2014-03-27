#include "compiler/parse_table.h"
#include <string>

namespace tree_sitter {
    using std::string;
    using std::ostream;
    using std::to_string;
    using std::set;
    using std::vector;
    using rules::Symbol;

    ParseAction::ParseAction(ParseActionType type,
                             size_t state_index,
                             Symbol symbol,
                             size_t consumed_symbol_count) :
        type(type),
        symbol(symbol),
        state_index(state_index),
        consumed_symbol_count(consumed_symbol_count) {}

    ParseAction ParseAction::Error() {
        return ParseAction(ParseActionTypeError, -1, Symbol(""), {});
    }

    ParseAction ParseAction::Accept() {
        return ParseAction(ParseActionTypeAccept, -1, Symbol(""), {});
    }

    ParseAction ParseAction::Shift(size_t state_index) {
        return ParseAction(ParseActionTypeShift, state_index, Symbol(""), {});
    }

    ParseAction ParseAction::Reduce(Symbol symbol, size_t consumed_symbol_count) {
        return ParseAction(ParseActionTypeReduce, -1, symbol, consumed_symbol_count);
    }

    bool ParseAction::operator==(const ParseAction &other) const {
        bool types_eq = type == other.type;
        bool state_indices_eq = state_index == other.state_index;
        bool consumed_symbol_counts_eq = consumed_symbol_count == other.consumed_symbol_count;
        return types_eq && state_indices_eq && consumed_symbol_counts_eq;
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

    ParseState::ParseState() : lex_state_id(-1) {}

    set<Symbol> ParseState::expected_inputs() const {
        set<Symbol> result;
        for (auto pair : actions)
            result.insert(pair.first);
        return result;
    }

    ostream& operator<<(ostream &stream, const ParseState &state) {
        stream << string("#<parse_state ");
        bool started = false;
        for (auto pair : state.actions) {
            if (started) stream << string(", ");
            stream << pair.first << string(" => ") << pair.second;
            started = true;
        }
        stream << string(">");
        return stream;
    }

    ParseStateId ParseTable::add_state() {
        states.push_back(ParseState());
        return states.size() - 1;
    }

    void ParseTable::add_action(ParseStateId id, Symbol symbol, ParseAction action) {
        symbols.insert(symbol);
        states[id].actions.insert({ symbol, action });
    }
}
