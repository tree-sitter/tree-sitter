#ifndef HELPERS_STREAM_METHODS_H_
#define HELPERS_STREAM_METHODS_H_

#include <iostream>
#include <set>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <vector>
#include "compiler/grammar.h"
#include "compiler/prepare_grammar/interned_grammar.h"
#include "compiler/prepare_grammar/initial_syntax_grammar.h"
#include "compiler/lexical_grammar.h"
#include "compiler/syntax_grammar.h"
#include "compiler/rule.h"
#include "compiler/compile_error.h"
#include "compiler/build_tables/lex_item.h"

using std::cout;

namespace std {

template<typename T>
inline std::ostream& operator<<(std::ostream &stream, const std::vector<T> &vector) {
  stream << std::string("(vector: ");
  bool started = false;
  for (auto item : vector) {
    if (started) stream << std::string(", ");
    stream << item;
    started = true;
  }
  return stream << ")";
}

template<typename T>
inline std::ostream& operator<<(std::ostream &stream, const std::set<T> &set) {
  stream << std::string("(set: ");
  bool started = false;
  for (auto item : set) {
    if (started) stream << std::string(", ");
    stream << item;
    started = true;
  }
  return stream << ")";
}

template<typename T, typename H, typename E>
inline std::ostream& operator<<(std::ostream &stream, const std::unordered_set<T, H, E> &set) {
  stream << std::string("(set: ");
  bool started = false;
  for (auto item : set) {
    if (started) stream << std::string(", ");
    stream << item;
    started = true;
  }
  return stream << ")";
}

template<typename TKey, typename TValue>
inline std::ostream& operator<<(std::ostream &stream, const std::map<TKey, TValue> &map) {
  stream << std::string("(map: ");
  bool started = false;
  for (auto pair : map) {
    if (started) stream << std::string(", ");
    stream << pair.first;
    stream << std::string(" => ");
    stream << pair.second;
    started = true;
  }
  return stream << ")";
}

template<typename TKey, typename TValue>
inline std::ostream& operator<<(std::ostream &stream, const std::unordered_map<TKey, TValue> &map) {
  stream << std::string("(map: ");
  bool started = false;
  for (auto pair : map) {
    if (started) stream << std::string(", ");
    stream << pair.first;
    stream << std::string(" => ");
    stream << pair.second;
    started = true;
  }
  return stream << ")";
}

template<typename T1, typename T2>
inline std::ostream& operator<<(std::ostream &stream, const std::pair<T1, T2> &pair) {
  return stream << "{" << pair.first << ", " << pair.second << "}";
}

}  // namespace std

namespace tree_sitter {

using std::ostream;
using std::string;
using std::to_string;

struct InputGrammar;
struct AdvanceAction;
struct AcceptTokenAction;
struct ParseAction;
struct ParseState;
struct ExternalToken;
struct ProductionStep;
struct PrecedenceRange;

ostream &operator<<(ostream &, const InputGrammar &);
ostream &operator<<(ostream &, const CompileError &);
ostream &operator<<(ostream &, const ExternalToken &);
ostream &operator<<(ostream &, const ProductionStep &);
ostream &operator<<(ostream &, const PrecedenceRange &);
ostream &operator<<(ostream &, const Variable &);
ostream &operator<<(ostream &, const LexicalVariable &);

namespace rules {

ostream &operator<<(ostream &, const Blank &);
ostream &operator<<(ostream &, const CharacterRange &);
ostream &operator<<(ostream &, const CharacterSet &);
ostream &operator<<(ostream &, const Symbol &);
ostream &operator<<(ostream &, const NamedSymbol &);
ostream &operator<<(ostream &, const String &);
ostream &operator<<(ostream &, const Pattern &);
ostream &operator<<(ostream &stream, const Choice &rule);
ostream &operator<<(ostream &stream, const Seq &rule);
ostream &operator<<(ostream &stream, const Repeat &rule);
ostream &operator<<(ostream &stream, const Metadata &rule);
ostream &operator<<(ostream &stream, const Rule &rule);

}  // namespace rules

namespace build_tables {

class LexItem;
class LexItemSet;
struct ParseItem;
struct ParseItemSet;
class LookaheadSet;

ostream &operator<<(ostream &, const LexItem &);
ostream &operator<<(ostream &, const LexItemSet &);
ostream &operator<<(ostream &, const LexItemSet::Transition &);
ostream &operator<<(ostream &, const ParseItem &);
ostream &operator<<(ostream &, const ParseItemSet &);
ostream &operator<<(ostream &, const LookaheadSet &);

}  // namespace build_tables
}  // namespace tree_sitter

#endif  // HELPERS_STREAM_METHODS_H_
