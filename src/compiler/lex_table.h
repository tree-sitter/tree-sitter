#ifndef __TreeSitter__lex_table__
#define __TreeSitter__lex_table__

#include <unordered_map>
#include <vector>
#include <string>
#include <unordered_set>
#include "symbol.h"
#include "character.h"

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
        std::unordered_map<rules::Character, std::unordered_set<LexAction>> actions;
        std::unordered_set<LexAction> default_actions;
        std::unordered_set<rules::Character> expected_inputs() const;
    };
    
    class LexTable {
    public:
        size_t add_state();
        void add_action(size_t state_index, rules::Character rule, LexAction action);
        void add_default_action(size_t state_index, LexAction action);
        
        std::vector<LexState> states;
    };
}

#endif
