#include "lex_table.h"

using std::string;
using std::to_string;
using std::unordered_map;
using std::unordered_set;
using std::vector;

namespace tree_sitter {
    namespace lr {

        // Action
        LexAction::LexAction(LexActionType type, size_t state_index, std::string symbol_name) :
            type(type),
            state_index(state_index),
            symbol_name(symbol_name) {}
        
        LexAction LexAction::Error() {
            return LexAction(LexActionTypeError, -1, "");
        }
        
        LexAction LexAction::Advance(size_t state_index) {
            return LexAction(LexActionTypeAdvance, state_index, "");
        }
        
        LexAction LexAction::Accept(std::string symbol_name) {
            return LexAction(LexActionTypeAccept, -1, symbol_name);
        }
        
        bool LexAction::operator==(const LexAction &other) const {
            return
                (type == other.type) &&
                (state_index == other.state_index) &&
                (symbol_name == other.symbol_name);
        }
        
        std::ostream& operator<<(std::ostream &stream, const LexAction &action) {
            switch (action.type) {
                case LexActionTypeError:
                    return stream << string("#<error>");
                case LexActionTypeAccept:
                    return stream << string("#<accept ") + action.symbol_name + ">";
                case LexActionTypeAdvance:
                    return stream << string("#<advance ") + to_string(action.state_index) + ">";
            }
        }
        
        // State
        unordered_set<CharMatch> LexState::expected_inputs() const {
            unordered_set<CharMatch> result;
            for (auto pair : actions)
                result.insert(pair.first);
            return result;
        }
        
        // Table
        size_t LexTable::add_state() {
            states.push_back(LexState());
            return states.size() - 1;
        }
        
        void LexTable::add_action(size_t state_index, CharMatch match, LexAction action) {
            states[state_index].actions[match].insert(action);
        }

        void LexTable::add_default_action(size_t state_index, LexAction action) {
            states[state_index].default_actions.insert(action);
        }
    }
}