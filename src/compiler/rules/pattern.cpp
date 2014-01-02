#include "rules.h"
#include "transition_map.h"

using std::string;
using std::hash;

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
                rule_ptr result = atom();
                if (has_more_input() && (peek() == '+')) {
                    next();
                    result = repeat(result);
                }
                return result;
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
                        result = escaped_char(peek());
                        next();
                        break;
                    default:
                        result = character(peek());
                        next();
                        break;
                }
                return result;
            }
            
            rule_ptr escaped_char(char value) {
                switch (value) {
                    case '(':
                    case ')':
                        return character(value);
                    case 'w':
                        return character(CharClassWord);
                    case 'd':
                        return character(CharClassDigit);
                    default:
                        error("unrecognized escape sequence");
                        return rule_ptr();
                }
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
                throw string("Invalid regex pattern '") + input + "': " + message;
            }
            
            const string input;
            const size_t length;
            int position;
        };
        
        Pattern::Pattern(const string &string) : value(string) {};
        
        bool Pattern::operator==(tree_sitter::rules::Rule const &other) const {
            auto pattern = dynamic_cast<const Pattern *>(&other);
            return pattern && (pattern->value == value);
        }
        
        size_t Pattern::hash_code() const {
            return typeid(this).hash_code() ^ hash<string>()(value);
        }
        
        rule_ptr Pattern::copy() const {
            return std::make_shared<Pattern>(*this);
        }
        
        string Pattern::to_string() const {
            return string("#<pattern '") + value + "'>";
        }
        
        void Pattern::accept(Visitor &visitor) const {
            visitor.visit(this);
        }
        
        rule_ptr Pattern::to_rule_tree() const {
            return PatternParser(value).rule();
        }
    }
}
