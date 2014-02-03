#include "rules.h"

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
            
            rule_ptr char_set() {
                bool is_affirmative = true;
                if (peek() == '^') {
                    next();
                    is_affirmative = false;
                }
                std::unordered_set<CharacterRange> matches;
                while (has_more_input() && (peek() != ']'))
                    matches.insert(single_char());
                return character(matches, is_affirmative);
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
                    case '[':
                        next();
                        result = char_set();
                        if (peek() != ']')
                            error("mismatched square brackets");
                        else
                            next();
                        break;
                    case ')':
                        error("mismatched parens");
                        break;
                    default:
                        result = character({ single_char() }, true);
                }
                return result;
            }
            
            CharacterRange single_char() {
                CharacterRange value('\0');
                switch (peek()) {
                    case '\\':
                        next();
                        value = escaped_char(peek());
                        next();
                        break;
                    default:
                        char first_char = peek();
                        next();
                        if (peek() == '-') {
                            next();
                            value = CharacterRange({ first_char, peek() });
                            next();
                        } else {
                            value = first_char;
                        }
                }
                return value;
            }
            
            CharacterRange escaped_char(char value) {
                switch (value) {
                    case '\\':
                    case '(':
                    case ')':
                        return value;
                    case 'w':
                        return CharClassWord;
                    case 'd':
                        return CharClassDigit;
                    default:
                        error("unrecognized escape sequence");
                        return '\0';
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
