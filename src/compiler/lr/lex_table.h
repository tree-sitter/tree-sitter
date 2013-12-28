#ifndef __TreeSitter__lex_table__
#define __TreeSitter__lex_table__

#include <unordered_map>
#include <vector>
#include <string>
#include <unordered_set>
#include "char_match.h"

namespace tree_sitter {
    namespace lr {
        typedef enum {
            LexActionTypeAccept,
            LexActionTypeError,
            LexActionTypeAdvance
        } LexActionType;
        
        class LexAction {
            LexAction(LexActionType type, size_t state_index, std::string symbol_name);
        public:
            static LexAction Accept(std::string symbol_name);
            static LexAction Error();
            static LexAction Advance(size_t state_index);
            bool operator==(const LexAction &action) const;
            
            LexActionType type;
            std::string symbol_name;
            size_t state_index;
        };
    }
}

namespace std {
    template<>
    struct hash<tree_sitter::lr::LexAction> {
        size_t operator()(const tree_sitter::lr::LexAction &action) const {
            return (
                    hash<int>()(action.type) ^
                    hash<string>()(action.symbol_name) ^
                    hash<size_t>()(action.state_index));
        }
    };
}

namespace tree_sitter {
    namespace lr {
        std::ostream& operator<<(std::ostream &stream, const LexAction &item);
        
        class LexState {
        public:
            LexState();
            std::unordered_map<CharMatch, std::unordered_set<LexAction>> actions;
            std::unordered_set<LexAction> default_actions;
        };
        
        class LexTable {
        public:
            LexTable(std::vector<std::string> rule_names);
            
            size_t add_state();
            void add_action(size_t state_index, CharMatch match, LexAction action);
            void add_default_action(size_t state_index, LexAction action);
            
            static const std::string START;
            static const std::string END_OF_INPUT;
            std::vector<LexState> states;
            const std::vector<std::string> symbol_names;
        };
    }
}

#endif
