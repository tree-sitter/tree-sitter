#ifndef COMPILER_LEX_TABLE_H_
#define COMPILER_LEX_TABLE_H_

#include <map>
#include <vector>
#include <set>
#include <string>
#include "compiler/rules/interned_symbol.h"
#include "compiler/rules/character_set.h"

namespace tree_sitter {
    typedef enum {
        LexActionTypeError,
        LexActionTypeAccept,
        LexActionTypeAdvance
    } LexActionType;

    class LexAction {
        LexAction(LexActionType type, size_t state_index, rules::ISymbol symbol);
    public:
        LexAction();
        static LexAction Accept(rules::ISymbol symbol);
        static LexAction Error();
        static LexAction Advance(size_t state_index);
        bool operator==(const LexAction &action) const;

        LexActionType type;
        rules::ISymbol symbol;
        size_t state_index;
    };

    std::ostream& operator<<(std::ostream &stream, const LexAction &item);
}

namespace std {
    template<>
    struct hash<tree_sitter::LexAction> {
        size_t operator()(const tree_sitter::LexAction &action) const {
            return (hash<int>()(action.type) ^
                    hash<tree_sitter::rules::ISymbol>()(action.symbol) ^
                    hash<size_t>()(action.state_index));
        }
    };
}

namespace tree_sitter {
    class LexState {
    public:
        std::map<rules::CharacterSet, LexAction> actions;
        LexAction default_action;
        std::set<rules::CharacterSet> expected_inputs() const;
        bool is_token_start;
    };

    typedef int64_t LexStateId;

    class LexTable {
    public:
        static const LexStateId ERROR_STATE_ID;
        LexStateId add_state();
        void add_action(LexStateId state_id, rules::CharacterSet rule, LexAction action);
        void add_default_action(LexStateId state_id, LexAction action);
        LexState & state(LexStateId state_id);

        std::vector<LexState> states;
        LexState error_state;
    };
}

#endif  // COMPILER_LEX_TABLE_H_
