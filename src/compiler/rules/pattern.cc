#include "compiler/rules/pattern.h"
#include <set>
#include <string>
#include "compiler/rules/visitor.h"
#include "compiler/rules/choice.h"
#include "compiler/rules/seq.h"
#include "compiler/rules/repeat.h"
#include "compiler/rules/character_set.h"

namespace tree_sitter {
    namespace rules {
        using std::string;
        using std::hash;
        using std::make_shared;
        using std::set;

        class PatternParser {
        public:
            PatternParser(const string &input) :
                input(input),
                length(input.length()),
                position(0) {}

            rule_ptr rule() {
                auto result = term();
                while (has_more_input() && peek() == '|') {
                    next();
                    result = make_shared<Choice>(result, term());
                }
                return result;
            }

        private:
            rule_ptr term() {
                rule_ptr result = factor();
                while (has_more_input() && (peek() != '|') && (peek() != ')'))
                    result = Seq::Build({ result, factor() });
                return result;
            }

            rule_ptr factor() {
                rule_ptr result = atom();
                if (has_more_input() && (peek() == '+')) {
                    next();
                    result = make_shared<Repeat>(result);
                }
                return result;
            }

            rule_ptr atom() {
                rule_ptr result;
                switch (peek()) {
                    case '(':
                        next();
                        result = rule();
                        if (has_error()) return result;
                        if (peek() != ')') {
                            error = "mismatched parens";
                            return result;
                        }
                        next();
                        break;
                    case '[':
                        next();
                        result = char_set().copy();
                        if (has_error()) return result;
                        if (peek() != ']') {
                            error = "mismatched square brackets";
                            return result;
                        }
                        next();
                        break;
                    case ')':
                        error = "mismatched parens";
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
                CharacterSet value;
                switch (peek()) {
                    case '\\':
                        next();
                        value = escaped_char(peek());
                        if (has_error()) return value;
                        next();
                        break;
                    default:
                        char first_char = peek();
                        next();
                        if (peek() == '-') {
                            next();
                            value = CharacterSet({ CharacterRange(first_char, peek()) });
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
                        return CharacterSet({{'a', 'z'}, {'A', 'Z'}});
                    case 'd':
                        return CharacterSet({CharacterRange('0', '9')});
                    default:
                        error = "unrecognized escape sequence";
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

            bool has_error() {
                return error != "";
            }

            string error;
            const string input;
            const size_t length;
            size_t position;
        };

        Pattern::Pattern(const string &string) : value(string) {}

        bool Pattern::operator==(tree_sitter::rules::Rule const &other) const {
            auto pattern = dynamic_cast<const Pattern *>(&other);
            return pattern && (pattern->value == value);
        }

        size_t Pattern::hash_code() const {
            return hash<string>()(value);
        }

        rule_ptr Pattern::copy() const {
            return std::make_shared<Pattern>(*this);
        }

        string Pattern::to_string() const {
            return string("#<pattern '") + value + "'>";
        }

        void Pattern::accept(Visitor *visitor) const {
            visitor->visit(this);
        }

        rule_ptr Pattern::to_rule_tree() const {
            return PatternParser(value).rule();
        }
    }
}
