#include "compiler/prepare_grammar/parse_regex.h"
#include <string>
#include <utility>
#include <vector>
#include "compiler/rules/choice.h"
#include "compiler/rules/seq.h"
#include "compiler/rules/repeat.h"
#include "compiler/rules/character_set.h"
#include "compiler/rules/blank.h"
#include "compiler/util/string_helpers.h"

namespace tree_sitter {
namespace prepare_grammar {

using std::string;
using std::vector;
using std::pair;
using std::make_shared;
using rules::rule_ptr;
using rules::CharacterSet;
using rules::Seq;
using rules::Blank;
using rules::Choice;
using rules::Repeat;
using rules::CharacterRange;
using rules::blank;

class PatternParser {
 public:
  explicit PatternParser(const string &input)
      : input(input), length(input.length()), position(0) {}

  pair<rule_ptr, const GrammarError *> rule(bool nested) {
    vector<rule_ptr> choices = {};
    do {
      if (!choices.empty()) {
        if (peek() == '|')
          next();
        else
          break;
      }
      auto pair = term(nested);
      if (pair.second)
        return { blank(), pair.second };
      choices.push_back(pair.first);
    } while (has_more_input());
    auto rule =
        (choices.size() > 1) ? make_shared<Choice>(choices) : choices.front();
    return { rule, nullptr };
  }

 private:
  pair<rule_ptr, const GrammarError *> term(bool nested) {
    rule_ptr result = blank();
    do {
      if (peek() == '|')
        break;
      if (nested && peek() == ')')
        break;
      auto pair = factor();
      if (pair.second)
        return { blank(), pair.second };
      result = Seq::Build({ result, pair.first });
    } while (has_more_input());
    return { result, nullptr };
  }

  pair<rule_ptr, const GrammarError *> factor() {
    auto pair = atom();
    if (pair.second)
      return { blank(), pair.second };
    rule_ptr result = pair.first;
    if (has_more_input()) {
      switch (peek()) {
        case '*':
          next();
          result = make_shared<Repeat>(result);
          break;
        case '+':
          next();
          result = make_shared<Seq>(result, make_shared<Repeat>(result));
          break;
        case '?':
          next();
          result = Choice::Build({ result, make_shared<Blank>() });
          break;
      }
    }
    return { result, nullptr };
  }

  pair<rule_ptr, const GrammarError *> atom() {
    switch (peek()) {
      case '(': {
        next();
        auto pair = rule(true);
        if (pair.second)
          return { blank(), pair.second };
        if (peek() != ')')
          return error("unmatched open paren");
        next();
        return { pair.first, nullptr };
      }
      case '[': {
        next();
        auto pair = char_set();
        if (pair.second)
          return { blank(), pair.second };
        if (peek() != ']')
          return error("unmatched open square bracket");
        next();
        return { pair.first.copy(), nullptr };
      }
      case ')': { return error("unmatched close paren"); }
      case ']': { return error("unmatched close square bracket"); }
      case '.': {
        next();
        return { CharacterSet({ '\n' }).complement().copy(), nullptr };
      }
      default: {
        auto pair = single_char();
        if (pair.second)
          return { blank(), pair.second };
        return { pair.first.copy(), nullptr };
      }
    }
  }

  pair<CharacterSet, const GrammarError *> char_set() {
    bool is_affirmative = true;
    if (peek() == '^') {
      next();
      is_affirmative = false;
    }
    CharacterSet result;
    while (has_more_input() && (peek() != ']')) {
      auto pair = single_char();
      if (pair.second)
        return { CharacterSet(), pair.second };
      result.add_set(pair.first);
    }
    if (!is_affirmative)
      result = result.complement();
    return { result, nullptr };
  }

  pair<CharacterSet, const GrammarError *> single_char() {
    CharacterSet value;
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
          value = CharacterSet({ CharacterRange(first_char, peek()) });
          next();
        } else {
          value = CharacterSet({ first_char });
        }
    }
    return { value, nullptr };
  }

  CharacterSet escaped_char(char value) {
    switch (value) {
      case 'a':
        return CharacterSet({ { 'a', 'z' }, { 'A', 'Z' } });
      case 'w':
        return CharacterSet({ { 'a', 'z' }, { 'A', 'Z' }, { '0', '9' } });
      case 'd':
        return CharacterSet({ { '0', '9' } });
      default:
        return CharacterSet({ value });
    }
  }

  void next() { position++; }

  char peek() { return input[position]; }

  bool has_more_input() { return position < length; }

  pair<rule_ptr, const GrammarError *> error(string msg) {
    return { blank(), new GrammarError(GrammarErrorTypeRegex, msg) };
  }

  const string input;
  const size_t length;
  size_t position;
};

pair<rule_ptr, const GrammarError *> parse_regex(const std::string &input) {
  return PatternParser(input).rule(false);
}

}  // namespace prepare_grammar
}  // namespace tree_sitter
