#include "choice.h"
#include "seq.h"
#include "Pattern.h"
#include "transition_map.h"

using namespace std;

namespace tree_sitter {
    namespace rules {
        class PatternParser {
        public:
            PatternParser(const string &input) :
                input(input),
                position(0),
                length(input.length()) {}
            
            rule_ptr rule() {
                auto result = term();
                while (has_more_input() && peek() == '|') {
                    next();
                    result = choice({ result, term() });
                }
                return result;
            }
            
        private:
            rule_ptr term() {
                rule_ptr result = factor();
                while (has_more_input() && (peek() != '|') && (peek() != ')'))
                    result = seq({ result, factor() });
                return result;
            }
            
            rule_ptr factor() {
                return atom();
            }
            
            rule_ptr atom() {
                rule_ptr result;
                switch (peek()) {
                    case '(':
                        next();
                        result = rule();
                        if (peek() != ')')
                            error("mismatched parens");
                        else
                            next();
                        break;
                    case ')':
                        error("mismatched parens");
                        break;
                    case '\\':
                        next();
                        result = character(peek());
                        next();
                        break;
                    default:
                        result = character(peek());
                        next();
                        break;
                }
                return result;
            }
            
            void next() {
                position++;
            }
            
            char peek() {
                return input[position];
            }
            
            bool has_more_input() {
                return position < length;
            }
            
            void error(const char *message) {
                throw std::string("Invalid regex pattern '") + input + "': " + message;
            }
            
            const std::string input;
            const size_t length;
            int position;
        };
        
        Pattern::Pattern(const std::string &string) : value(string) {};
        
        pattern_ptr pattern(const std::string &value) {
            return std::make_shared<Pattern>(value);
        }

        TransitionMap<Rule> Pattern::transitions() const {
            return to_rule_tree()->transitions();
        }
        
        rule_ptr Pattern::to_rule_tree() const {
            return PatternParser(value).rule();
        }
        
        bool Pattern::operator ==(tree_sitter::rules::Rule const &other) const {
            return false;
        }

        std::string Pattern::to_string() const {
            return value;
        }
    }
}
