#ifndef HELPERS_CONTAINERS_H_
#define HELPERS_CONTAINERS_H_

#include <map>
#include <vector>
#include <string>
#include <initializer_list>
#include "tree_sitter/compiler.h"
#include "compiler/rules/rule.h"

using std::map;
using std::vector;
using std::string;
using std::initializer_list;
using std::pair;
using tree_sitter::rules::rule_ptr;

template<typename T, typename Func>
std::vector<typename std::result_of<Func(T)>::type>
collect(const std::vector<T> &v, Func f) {
  vector<typename std::result_of<Func(T)>::type> result;
  for (const T &item : v)
    result.push_back(f(item));
  return result;
}

template<typename K>
class rule_map : public map<K, rule_ptr> {
 public:
  bool operator==(const map<K, rule_ptr> &other) const {
    if (this->size() != other.size()) return false;
    for (const auto &pair : *this) {
      auto other_pair = other.find(pair.first);
      if (other_pair == other.end()) return false;
      if (!pair.second->operator==(*other_pair->second)) return false;
    }
    return true;
  }

  rule_map(const initializer_list<pair<const K, rule_ptr>> &list) : map<K, rule_ptr>(list) {}
};

class rule_list : public vector<pair<string, rule_ptr>> {
 public:
  bool operator==(const vector<pair<string, rule_ptr>> &other) const {
    if (this->size() != other.size()) return false;
    for (size_t i = 0; i < this->size(); i++) {
      auto pair = this->operator[](i);
      auto other_pair = other[i];
      if (!pair.second->operator==(*other_pair.second))
        return false;
    }
    return true;
  }

  rule_list(const initializer_list<pair<string, rule_ptr>> &list) :
      vector<pair<string, rule_ptr>>(list) {}
};

class rule_vector : public vector<rule_ptr> {
 public:
  bool operator==(const vector<rule_ptr> &other) const {
    if (this->size() != other.size()) return false;
    for (size_t i = 0; i < this->size(); i++) {
      auto rule = this->operator[](i);
      auto other_rule = other[i];
      if (!rule->operator==(*rule))
        return false;
    }
    return true;
  }

  rule_vector(const initializer_list<rule_ptr> &list) :
      vector<rule_ptr>(list) {}
};

#endif  // HELPERS_CONTAINERS_H_
