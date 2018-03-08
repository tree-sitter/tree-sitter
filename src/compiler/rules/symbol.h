#ifndef COMPILER_RULES_SYMBOL_H_
#define COMPILER_RULES_SYMBOL_H_

namespace tree_sitter {
namespace rules {

struct Symbol {
  using Index = int;
  enum Type {
    External,
    Terminal,
    NonTerminal,
  };

  inline bool operator==(const Symbol &other) const {
    return index == other.index && type == other.type;
  }

  inline bool operator!=(const Symbol &other) const {
    return !operator==(other);
  }

  inline bool operator<(const Symbol &other) const {
    if (type < other.type) return true;
    if (type > other.type) return false;
    return index < other.index;
  }

  Index index;
  Type type;

  static Symbol terminal(Index index) {
    return Symbol{index, Type::Terminal};
  }

  static Symbol external(Index index) {
    return Symbol{index, Type::External};
  }

  static Symbol non_terminal(Index index) {
    return Symbol{index, Type::NonTerminal};
  }

  bool is_non_terminal() const {
    return type == Type::NonTerminal;
  }

  bool is_terminal() const {
    return type == Type::Terminal;
  }

  bool is_external() const {
    return type == Type::External;
  }

  bool is_built_in() const {
    return index < 0;
  }
};

inline Symbol END_OF_INPUT() {
  return Symbol{-1, Symbol::Terminal};
}

inline Symbol START() {
  return Symbol{-2, Symbol::NonTerminal};
}

inline Symbol NONE() {
  return Symbol{-3, Symbol::Type(-1)};
}

}  // namespace rules
}  // namespace tree_sitter

#endif  // COMPILER_RULES_SYMBOL_H_
