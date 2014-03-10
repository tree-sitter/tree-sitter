#ifndef COMPILER_LEX_TABLE_H_
#define COMPILER_LEX_TABLE_H_

#include <map>
#include <vector>
#include <set>
#include <string>
#include "compiler/rules/symbol.h"
#include "compiler/rules/character_set.h"

namespace tree_sitter {
    typedef enum {
        LexActionTypeAccept,
        LexActionTypeError,
        LexActionTypeAdvance
    } LexActionType;

    class LexAction {
        LexAction(LexActionType type, size_t state_index, rules::Symbol symbol);
    public:
        static LexAction Accept(rules::Symbol symbol);
        static LexAction Error();
        static LexAction Advance(size_t state_index);
        bool operator==(const LexAction &action) const;
        bool operator<(const LexAction &action) const;

        LexActionType type;
        rules::Symbol symbol;
        size_t state_index;
    };

    std::ostream& operator<<(std::ostream &stream, const LexAction &item);
}

namespace std {
    template<>
    struct hash<tree_sitter::LexAction> {
        size_t operator()(const tree_sitter::LexAction &action) const {
            return (hash<int>()(action.type) ^
                    hash<tree_sitter::rules::Symbol>()(action.symbol) ^
                    hash<size_t>()(action.state_index));
        }
    };
}

namespace tree_sitter {
    class LexState {
    public:
        std::map<rules::CharacterSet, std::set<LexAction>> actions;
        std::set<LexAction> default_actions;
        std::set<rules::CharacterSet> expected_inputs() const;
    };

    typedef int64_t LexStateId;

    class LexTable {
    public:
        static const LexStateId ERROR_STATE_ID;
        LexStateId add_state();
        void add_action(LexStateId state_id, rules::CharacterSet rule, LexAction action);
        void add_default_action(LexStateId state_id, LexAction action);

        std::vector<LexState> states;
        LexState error_state;
    };
}

#endif  // COMPILER_LEX_TABLE_H_
