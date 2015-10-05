#ifndef tree_sitter_stream_methods_h
#define tree_sitter_stream_methods_h

#include <iostream>
#include <set>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <vector>
#include "tree_sitter/compiler.h"

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
struct Variable;
struct SyntaxVariable;
class LexAction;
class ParseAction;
class ParseState;
struct ProductionStep;

ostream &operator<<(ostream &, const Grammar &);
ostream &operator<<(ostream &, const GrammarError &);
ostream &operator<<(ostream &, const Rule &);
ostream &operator<<(ostream &, const rule_ptr &);
ostream &operator<<(ostream &, const Variable &);
ostream &operator<<(ostream &, const SyntaxVariable &);
ostream &operator<<(ostream &, const LexAction &);
ostream &operator<<(ostream &, const ParseAction &);
ostream &operator<<(ostream &, const ParseState &);
ostream &operator<<(ostream &, const ProductionStep &);

namespace build_tables {

struct MetadataRange;
class LexItem;
class LexItemSet;
class ParseItem;
class ParseItemSet;
class LookaheadSet;

ostream &operator<<(ostream &, const MetadataRange &);
ostream &operator<<(ostream &, const LexItem &);
ostream &operator<<(ostream &, const LexItemSet &);
ostream &operator<<(ostream &, const ParseItem &);
ostream &operator<<(ostream &, const ParseItemSet &);
ostream &operator<<(ostream &, const LookaheadSet &);

}  // namespace build_tables
}  // namespace tree_sitter

#endif
