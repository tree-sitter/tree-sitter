#ifndef __TreeSitter__lex_table__
#define __TreeSitter__lex_table__

#include <vector>
#include <string>
#include <set>
#include <map>
#include "symbol.h"
#include "character_set.h"

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
    
    class LexTable {
    public:
        size_t add_state();
        void add_action(size_t state_index, rules::CharacterSet rule, LexAction action);
        void add_default_action(size_t state_index, LexAction action);
        
        std::vector<LexState> states;
    };
}

#endif
