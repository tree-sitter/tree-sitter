#ifndef COMPILER_RULE_H_
#define COMPILER_RULE_H_

#include <memory>
#include "compiler/util/make_visitor.h"
#include "compiler/util/hash_combine.h"
#include "compiler/rules/blank.h"
#include "compiler/rules/character_set.h"
#include "compiler/rules/choice.h"
#include "compiler/rules/metadata.h"
#include "compiler/rules/named_symbol.h"
#include "compiler/rules/pattern.h"
#include "compiler/rules/repeat.h"
#include "compiler/rules/seq.h"
#include "compiler/rules/string.h"
#include "compiler/rules/symbol.h"

namespace tree_sitter {
namespace rules {

struct Rule {
  union {
    Blank blank;
    CharacterSet character_set;
    String string;
    Pattern pattern;
    NamedSymbol named_symbol;
    Symbol symbol;
    Choice choice;
    Metadata metadata;
    Repeat repeat;
    Seq seq;
  };

  enum {
    BlankType,
    CharacterSetType,
    StringType,
    PatternType,
    NamedSymbolType,
    SymbolType,
    ChoiceType,
    MetadataType,
    RepeatType,
    SeqType,
  } type;

  Rule() : blank(Blank{}), type(BlankType) {};
  Rule(const Blank &value) : blank(value), type(BlankType) {};
  Rule(const CharacterSet &value) : character_set(value), type(CharacterSetType) {};
  Rule(const String &value) : string(value), type(StringType) {};
  Rule(const Pattern &value) : pattern(value), type(PatternType) {};
  Rule(const NamedSymbol &value) : named_symbol(value), type(NamedSymbolType) {};
  Rule(const Symbol &value) : symbol(value), type(SymbolType) {};
  Rule(const Choice &value) : choice(value), type(ChoiceType) {};
  Rule(const Metadata &value) : metadata(value), type(MetadataType) {};
  Rule(const Repeat &value) : repeat(value), type(RepeatType) {};
  Rule(const Seq &value) : seq(value), type(SeqType) {};

  Rule(const std::shared_ptr<Rule> &value) : Rule(*value) {}

  Rule(const Rule &other);
  Rule(Rule &&other) noexcept;
  Rule &operator=(const Rule &other);
  Rule &operator=(Rule &&other) noexcept;
  ~Rule() noexcept;

  template <typename RuleType>
  bool is() const;

  template <typename RuleType>
  const RuleType & get_unchecked() const;

  template <typename FunctionType>
  inline auto accept(FunctionType function) const -> decltype(function(blank)) {
    switch (type) {
      case CharacterSetType: return function(character_set);
      case StringType: return function(string);
      case PatternType: return function(pattern);
      case NamedSymbolType: return function(named_symbol);
      case SymbolType: return function(symbol);
      case ChoiceType: return function(choice);
      case MetadataType: return function(metadata);
      case RepeatType: return function(repeat);
      case SeqType: return function(seq);
      default: return function(blank);
    }
  }

  template <typename ...FunctionTypes>
  inline auto match(FunctionTypes && ...functions) const -> decltype(accept(util::make_visitor(std::forward<FunctionTypes>(functions)...))){
    return accept(util::make_visitor(std::forward<FunctionTypes>(functions)...));
  }

  bool operator==(const Rule &other) const;
};

}  // namespace rules
}  // namespace tree_sitter

namespace std {

using namespace tree_sitter::rules;
using namespace tree_sitter::util;

template <>
struct hash<Symbol> { size_t operator()(const Symbol &) const; };

template <>
struct hash<NamedSymbol> { size_t operator()(const NamedSymbol &) const; };

template <>
struct hash<Pattern> { size_t operator()(const Pattern &) const; };

template <>
struct hash<String> { size_t operator()(const String &) const; };

template <>
struct hash<CharacterSet> { size_t operator()(const CharacterSet &) const; };

template <>
struct hash<Blank> { size_t operator()(const Blank &) const; };

template <>
struct hash<Choice> { size_t operator()(const Choice &) const; };

template <>
struct hash<Repeat> { size_t operator()(const Repeat &) const; };

template <>
struct hash<Seq> { size_t operator()(const Seq &) const; };

template <>
struct hash<Metadata> { size_t operator()(const Metadata &) const; };

template <>
struct hash<Rule> { size_t operator()(const Rule &) const; };

}  // namespace std

#endif  // COMPILER_RULE_H_
