#include "compiler/prepare_grammar/parse_regex.h"
#include <string>
#include <utility>
#include <vector>
#include "compiler/rule.h"
#include "compiler/util/string_helpers.h"
#include "utf8proc.h"

namespace tree_sitter {
namespace prepare_grammar {

using std::string;
using std::vector;
using std::pair;
using rules::CharacterSet;
using rules::Blank;
using rules::Rule;

class PatternParser {
 public:
  explicit PatternParser(const string &input)
      : input(input),
        iter((const uint8_t *)input.data()),
        end(iter + input.size()) {
    next();
  }

  pair<Rule, CompileError> rule(bool nested) {
    vector<Rule> choices;
    do {
      if (!choices.empty()) {
        if (peek() == '|') {
          next();
        } else {
          break;
        }
      }
      auto pair = term(nested);
      if (pair.second.type) {
        return {Blank{}, pair.second };
      }
      choices.push_back(pair.first);
    } while (has_more_input());
    return {Rule::choice(choices), CompileError::none()};
  }

 private:
  pair<Rule, CompileError> term(bool nested) {
    Rule result;
    do {
      if (peek() == '|')
        break;
      if (nested && peek() == ')')
        break;
      auto pair = factor();
      if (pair.second) {
        return {Blank{}, pair.second};
      }
      result = Rule::seq({result, pair.first});
    } while (has_more_input());
    return { result, CompileError::none() };
  }

  pair<Rule, CompileError> factor() {
    auto pair = atom();
    if (pair.second.type) {
      return {Blank{}, pair.second};
    }

    Rule result = pair.first;
    if (has_more_input()) {
      switch (peek()) {
        case '*':
          next();
          result = Rule::choice({
            Rule::repeat(result),
            Blank{}
          });
          break;
        case '+':
          next();
          result = Rule::repeat(result);
          break;
        case '?':
          next();
          result = Rule::choice({result, Blank{}});
          break;
      }
    }

    return {result, CompileError::none()};
  }

  pair<Rule, CompileError> atom() {
    switch (peek()) {
      case '(': {
        next();
        auto pair = rule(true);
        if (pair.second.type) {
          return {Blank{}, pair.second};
        }
        if (peek() != ')') {
          return error("unmatched open paren");
        }
        next();
        return {pair.first, CompileError::none()};
      }

      case '[': {
        next();
        auto pair = char_set();
        if (pair.second.type) {
          return {Blank{}, pair.second};
        }
        if (peek() != ']') {
          return error("unmatched open square bracket");
        }
        next();
        return {pair.first, CompileError::none()};
      }

      case ')': {
        return error("unmatched close paren");
      }

      case ']': {
        return error("unmatched close square bracket");
      }

      case '.': {
        next();
        return {
          CharacterSet().include_all().exclude('\n'),
          CompileError::none()
        };
      }

      default: {
        return {single_char(), CompileError::none()};
      }
    }
  }

  pair<CharacterSet, CompileError> char_set() {
    CharacterSet result;
    bool is_affirmative = true;
    if (peek() == '^') {
      next();
      is_affirmative = false;
      result.include_all();
    }

    while (has_more_input() && (peek() != ']')) {
      auto characters = single_char();

      if (peek() == '-') {
        next();
        if (!characters.includes_all && characters.included_chars.size() == 1 && peek() != ']') {
          auto next_characters = single_char();
          if (!next_characters.includes_all && next_characters.included_chars.size() == 1) {
            characters.include(
              *characters.included_chars.begin(),
              *next_characters.included_chars.begin()
            );
          } else {
            characters.include('-');
            characters.add_set(next_characters);
          }
        } else {
          characters.include('-');
        }
      }

      if (is_affirmative)
        result.add_set(characters);
      else
        result.remove_set(characters);
    }

    return { result, CompileError::none() };
  }

  CharacterSet single_char() {
    CharacterSet value;
    if (peek() == '\\') {
      next();
      value = escaped_char(peek());
      next();
    } else {
      value = CharacterSet().include(peek());
      next();
    }
    return value;
  }

  CharacterSet escaped_char(uint32_t value) {
    switch (value) {
      case 'w':
        return CharacterSet()
          .include('a', 'z')
          .include('A', 'Z')
          .include('0', '9')
          .include('_');
      case 'W':
        return CharacterSet()
          .include_all()
          .exclude('a', 'z')
          .exclude('A', 'Z')
          .exclude('0', '9')
          .exclude('_');
      case 'd':
        return CharacterSet().include('0', '9');
      case 'D':
        return CharacterSet().include_all().exclude('0', '9');
      case 's':
        return CharacterSet()
          .include(' ')
          .include('\t')
          .include('\n')
          .include('\r');
      case 'S':
        return CharacterSet()
          .include_all()
          .exclude(' ')
          .exclude('\t')
          .exclude('\n')
          .exclude('\r');
      case '0':
        return CharacterSet().include('\0');
      case 't':
        return CharacterSet().include('\t');
      case 'n':
        return CharacterSet().include('\n');
      case 'r':
        return CharacterSet().include('\r');
      default:
        return CharacterSet().include(value);
    }
  }

  void next() {
    size_t lookahead_size = utf8proc_iterate(iter, end - iter, &lookahead);
    if (!lookahead_size)
      lookahead = 0;
    iter += lookahead_size;
  }

  uint32_t peek() {
    return lookahead;
  }

  bool has_more_input() {
    return lookahead && iter <= end;
  }

  pair<Rule, CompileError> error(string msg) {
    return { Blank{}, CompileError(TSCompileErrorTypeInvalidRegex, msg) };
  }

  string input;
  const uint8_t *iter;
  const uint8_t *end;
  int32_t lookahead;
};

pair<Rule, CompileError> parse_regex(const std::string &input) {
  return PatternParser(input.c_str()).rule(false);
}

}  // namespace prepare_grammar
}  // namespace tree_sitter
