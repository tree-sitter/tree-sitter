#include "compiler/rule.h"
#include "compiler/util/hash_combine.h"

namespace tree_sitter {
namespace rules {

using std::move;
using util::hash_combine;

Rule::Rule(const Rule &other) : blank(Blank{}), type(BlankType) {
  *this = other;
}

Rule::Rule(Rule &&other) noexcept : blank(Blank{}), type(BlankType) {
  *this = move(other);
}

static void destroy_value(Rule *rule) {
  switch (rule->type) {
    case Rule::BlankType: return rule->blank.~Blank();
    case Rule::CharacterSetType: return rule->character_set.~CharacterSet();
    case Rule::StringType: return rule->string .~String();
    case Rule::PatternType: return rule->pattern .~Pattern();
    case Rule::NamedSymbolType: return rule->named_symbol.~NamedSymbol();
    case Rule::SymbolType: return rule->symbol .~Symbol();
    case Rule::ChoiceType: return rule->choice .~Choice();
    case Rule::MetadataType: return rule->metadata .~Metadata();
    case Rule::RepeatType: return rule->repeat .~Repeat();
    case Rule::SeqType: return rule->seq .~Seq();
  }
}

Rule &Rule::operator=(const Rule &other) {
  destroy_value(this);
  type = other.type;
  switch (type) {
    case BlankType:
      new (&blank) Blank(other.blank);
      break;
    case CharacterSetType:
      new (&character_set) CharacterSet(other.character_set);
      break;
    case StringType:
      new (&string) String(other.string);
      break;
    case PatternType:
      new (&pattern) Pattern(other.pattern);
      break;
    case NamedSymbolType:
      new (&named_symbol) NamedSymbol(other.named_symbol);
      break;
    case SymbolType:
      new (&symbol) Symbol(other.symbol);
      break;
    case ChoiceType:
      new (&choice) Choice(other.choice);
      break;
    case MetadataType:
      new (&metadata) Metadata(other.metadata);
      break;
    case RepeatType:
      new (&repeat) Repeat(other.repeat);
      break;
    case SeqType:
      new (&seq) Seq(other.seq);
      break;
  }
  return *this;
}

Rule &Rule::operator=(Rule &&other) noexcept {
  destroy_value(this);
  type = other.type;
  switch (type) {
    case BlankType:
      new (&blank) Blank(move(other.blank));
      break;
    case CharacterSetType:
      new (&character_set) CharacterSet(move(other.character_set));
      break;
    case StringType:
      new (&string) String(move(other.string));
      break;
    case PatternType:
      new (&pattern) Pattern(move(other.pattern));
      break;
    case NamedSymbolType:
      new (&named_symbol) NamedSymbol(move(other.named_symbol));
      break;
    case SymbolType:
      new (&symbol) Symbol(move(other.symbol));
      break;
    case ChoiceType:
      new (&choice) Choice(move(other.choice));
      break;
    case MetadataType:
      new (&metadata) Metadata(move(other.metadata));
      break;
    case RepeatType:
      new (&repeat) Repeat(move(other.repeat));
      break;
    case SeqType:
      new (&seq) Seq(move(other.seq));
      break;
  }
  other.type = BlankType;
  other.blank = Blank{};
  return *this;
}

Rule::~Rule() noexcept {
  destroy_value(this);
}

bool Rule::operator==(const Rule &other) const {
  if (type != other.type) return false;
  switch (type) {
    case Rule::BlankType: return blank == other.blank;
    case Rule::CharacterSetType: return character_set == other.character_set;
    case Rule::StringType: return string == other.string;
    case Rule::PatternType: return pattern == other.pattern;
    case Rule::NamedSymbolType: return named_symbol == other.named_symbol;
    case Rule::SymbolType: return symbol == other.symbol;
    case Rule::ChoiceType: return choice == other.choice;
    case Rule::MetadataType: return metadata == other.metadata;
    case Rule::RepeatType: return repeat == other.repeat;
    case Rule::SeqType: return seq == other.seq;
  }
}

template <>
bool Rule::is<Blank>() const { return type == BlankType; }

template <>
bool Rule::is<Symbol>() const { return type == SymbolType; }

template <>
bool Rule::is<Repeat>() const { return type == RepeatType; }

template <>
const Symbol & Rule::get_unchecked<Symbol>() const { return symbol; }

}  // namespace rules
}  // namespace tree_sitter

namespace std {

size_t hash<Symbol>::operator()(const Symbol &symbol) const {
  auto result = hash<int>()(symbol.index);
  hash_combine(&result, hash<int>()(symbol.type));
  return result;
}

size_t hash<NamedSymbol>::operator()(const NamedSymbol &symbol) const {
  return hash<string>()(symbol.value);
}

size_t hash<Pattern>::operator()(const Pattern &symbol) const {
  return hash<string>()(symbol.value);
}

size_t hash<String>::operator()(const String &symbol) const {
  return hash<string>()(symbol.value);
}

size_t hash<CharacterSet>::operator()(const CharacterSet &character_set) const {
  size_t result = 0;
  hash_combine(&result, character_set.includes_all);
  hash_combine(&result, character_set.included_chars.size());
  for (uint32_t c : character_set.included_chars) {
    hash_combine(&result, c);
  }
  hash_combine(&result, character_set.excluded_chars.size());
  for (uint32_t c : character_set.excluded_chars) {
    hash_combine(&result, c);
  }
  return result;
}

size_t hash<Blank>::operator()(const Blank &blank) const {
  return 0;
}

size_t hash<Choice>::operator()(const Choice &choice) const {
  size_t result = 0;
  for (const auto &element : choice.elements) {
    symmetric_hash_combine(&result, element);
  }
  return result;
}

size_t hash<Repeat>::operator()(const Repeat &repeat) const {
  size_t result = 0;
  hash_combine(&result, *repeat.rule);
  return result;
}

size_t hash<Seq>::operator()(const Seq &seq) const {
  size_t result = 0;
  hash_combine(&result, *seq.left);
  hash_combine(&result, *seq.right);
  return result;
}

size_t hash<Metadata>::operator()(const Metadata &metadata) const {
  size_t result = 0;
  hash_combine(&result, *metadata.rule);
  hash_combine(&result, metadata.params.precedence);
  hash_combine<int>(&result, metadata.params.associativity);
  hash_combine(&result, metadata.params.has_precedence);
  hash_combine(&result, metadata.params.has_associativity);
  hash_combine(&result, metadata.params.is_token);
  hash_combine(&result, metadata.params.is_string);
  hash_combine(&result, metadata.params.is_active);
  hash_combine(&result, metadata.params.is_main_token);
  return result;
}

size_t hash<Rule>::operator()(const Rule &rule) const {
  size_t result = hash<int>()(rule.type);
  switch (rule.type) {
    case Rule::BlankType: return result ^ hash<Blank>()(rule.blank);
    case Rule::CharacterSetType: return result ^ hash<CharacterSet>()(rule.character_set);
    case Rule::StringType: return result ^ hash<String>()(rule.string);
    case Rule::PatternType: return result ^ hash<Pattern>()(rule.pattern);
    case Rule::NamedSymbolType: return result ^ hash<NamedSymbol>()(rule.named_symbol);
    case Rule::SymbolType: return result ^ hash<Symbol>()(rule.symbol);
    case Rule::ChoiceType: return result ^ hash<Choice>()(rule.choice);
    case Rule::MetadataType: return result ^ hash<Metadata>()(rule.metadata);
    case Rule::RepeatType: return result ^ hash<Repeat>()(rule.repeat);
    case Rule::SeqType: return result ^ hash<Seq>()(rule.seq);
  }
}

}  // namespace std