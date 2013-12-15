#ifndef __TreeSitter__parse_table__
#define __TreeSitter__parse_table__

#include <unordered_map>
#include <vector>
#include <unordered_set>
#include "rule.h"

namespace tree_sitter {
    namespace lr {
        typedef enum {
            ParseActionTypeAccept,
            ParseActionTypeAdvance,
            ParseActionTypeError,
            ParseActionTypeShift,
            ParseActionTypeReduce,
        } ParseActionType;
        
        class ParseAction {
        public:
            ParseAction();
            ParseAction(ParseActionType type, size_t state_index, std::string symbol_name, size_t child_symbol_count);
            bool operator==(const ParseAction &action) const;
            static ParseAction Accept();
            static ParseAction Advance(size_t state_index);
            static ParseAction Error();
            static ParseAction Shift(size_t state_index);
            static ParseAction Reduce(std::string symbol_name, size_t child_symbol_count);

            ParseActionType type;
            size_t child_symbol_count;
            std::string symbol_name;
            size_t state_index;
        };
        
        std::ostream& operator<<(std::ostream &stream, const ParseAction &item);
        
        class ParseState {
        public:
            ParseState();
            std::unordered_map<std::string, std::unordered_set<ParseAction>> actions;
        };
        
        class ParseTable {
            std::vector<ParseState> states;
        public:
            const std::unordered_map<std::string, size_t> symbol_ids;
            const std::vector<std::string> symbol_names;

            ParseTable(std::vector<std::string> rule_names);

            ParseState starting_state() const;
            ParseState get_state(size_t index) const;
            ParseAction action_for(size_t state_index, std::string symbol_name) const;
            std::unordered_map<std::string, std::unordered_set<ParseAction>> actions_for(size_t state_index) const;
            size_t add_state();
            void add_action(size_t state_index, std::string symbol_name, ParseAction action);
            
            static const std::string START;
            static const std::string END_OF_INPUT;
        };
    }
}

namespace std {
    template<>
    struct hash<tree_sitter::lr::ParseAction> {
        size_t operator()(const tree_sitter::lr::ParseAction &action) const {
            return (
                hash<int>()(action.type) ^
                hash<string>()(action.symbol_name) ^
                hash<size_t>()(action.state_index) ^
                hash<size_t>()(action.child_symbol_count));
        }
    };
}

#endif
