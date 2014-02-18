#ifndef __TreeSitter__parse_table__
#define __TreeSitter__parse_table__

#include <map>
#include <vector>
#include <set>
#include "rules/symbol.h"

namespace tree_sitter {
    typedef enum {
        ParseActionTypeAccept,
        ParseActionTypeError,
        ParseActionTypeShift,
        ParseActionTypeReduce,
    } ParseActionType;
    
    class ParseAction {
        ParseAction(ParseActionType type, size_t state_index, rules::Symbol symbol, const std::vector<bool> &child_flags);
    public:
        static ParseAction Accept();
        static ParseAction Error();
        static ParseAction Shift(size_t state_index);
        static ParseAction Reduce(rules::Symbol symbol, const std::vector<bool> &child_flags);
        bool operator==(const ParseAction &action) const;
        bool operator<(const ParseAction &action) const;
        
        ParseActionType type;
        rules::Symbol symbol;
        size_t state_index;
        std::vector<bool> child_flags;
    };

    std::ostream& operator<<(std::ostream &stream, const ParseAction &item);
}
        
namespace std {
    template<>
    struct hash<tree_sitter::ParseAction> {
        size_t operator()(const tree_sitter::ParseAction &action) const {
            return (
                    hash<int>()(action.type) ^
                    hash<tree_sitter::rules::Symbol>()(action.symbol) ^
                    hash<size_t>()(action.state_index) ^
                    hash<size_t>()(action.child_flags.size()));
        }
    };
}

namespace tree_sitter {
    class ParseState {
    public:
        ParseState();
        std::map<rules::Symbol, std::set<ParseAction>> actions;
        std::set<rules::Symbol> expected_inputs() const;
        size_t lex_state_index;
    };
    
    std::ostream& operator<<(std::ostream &stream, const ParseState &state);
    
    class ParseTable {
    public:
        size_t add_state();
        void add_action(size_t state_index, rules::Symbol symbol, ParseAction action);
        
        std::vector<ParseState> states;
        std::set<rules::Symbol> symbols;
    };
}

#endif
