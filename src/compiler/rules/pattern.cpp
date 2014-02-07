#include "rules.h"

using std::string;
using std::hash;
using std::set;

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
                    case '[':
                        next();
                        result = char_set().copy();
                        if (peek() != ']')
                            error("mismatched square brackets");
                        else
                            next();
                        break;
                    case ')':
                        error("mismatched parens");
                        break;
                    default:
                        result = single_char().copy();
                }
                return result;
            }
            
            CharacterSet char_set() {
                bool is_affirmative = true;
                if (peek() == '^') {
                    next();
                    is_affirmative = false;
                }
                CharacterSet result;
                while (has_more_input() && (peek() != ']'))
                    result.add_set(single_char());
                return is_affirmative ? result : result.complement();
            }
            
            CharacterSet single_char() {
                CharacterSet value({ '\0' });
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
                            value = CharacterSet({ {first_char, peek()} }, true);
                            next();
                        } else {
                            value = CharacterSet({ first_char });
                        }
                }
                return value;
            }
            
            CharacterSet escaped_char(char value) {
                switch (value) {
                    case '\\':
                    case '(':
                    case ')':
                        return CharacterSet({ value });
                    case 'w':
                        return CharacterSet({{'a', 'z'}, {'A', 'Z'}}, true);
                    case 'd':
                        return CharacterSet({{'0', '9'}}, true);
                    default:
                        error("unrecognized escape sequence");
                        return CharacterSet();
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
