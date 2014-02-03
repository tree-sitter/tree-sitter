#include "lex_table.h"

using std::string;
using std::to_string;
using std::unordered_map;
using std::unordered_set;
using tree_sitter::rules::Symbol;
using tree_sitter::rules::CharacterSet;

namespace tree_sitter {
    // Action
    LexAction::LexAction(LexActionType type, size_t state_index, Symbol symbol) :
        type(type),
        state_index(state_index),
        symbol(symbol) {}
    
    LexAction LexAction::Error() {
        return LexAction(LexActionTypeError, -1, Symbol(""));
    }
    
    LexAction LexAction::Advance(size_t state_index) {
        return LexAction(LexActionTypeAdvance, state_index, Symbol(""));
    }
    
    LexAction LexAction::Accept(Symbol symbol) {
        return LexAction(LexActionTypeAccept, -1, symbol);
    }
    
    bool LexAction::operator==(const LexAction &other) const {
        return
        (type == other.type) &&
        (state_index == other.state_index) &&
        (symbol == other.symbol);
    }
    
    std::ostream& operator<<(std::ostream &stream, const LexAction &action) {
        switch (action.type) {
            case LexActionTypeError:
                return stream << string("#<error>");
            case LexActionTypeAccept:
                return stream << string("#<accept ") + action.symbol.name + ">";
            case LexActionTypeAdvance:
                return stream << string("#<advance ") + to_string(action.state_index) + ">";
        }
    }
    
    // State
    unordered_set<CharacterSet> LexState::expected_inputs() const {
        unordered_set<CharacterSet> result;
        for (auto pair : actions)
            result.insert(pair.first);
        return result;
    }
    
    // Table
    size_t LexTable::add_state() {
        states.push_back(LexState());
        return states.size() - 1;
    }
    
    void LexTable::add_action(size_t state_index, CharacterSet match, LexAction action) {
        states[state_index].actions[match].insert(action);
    }
    
    void LexTable::add_default_action(size_t state_index, LexAction action) {
        states[state_index].default_actions.insert(action);
    }
}