#ifndef COMPILER_RULES_VISITOR_H_
#define COMPILER_RULES_VISITOR_H_

#include "compiler/rules/rule.h"

namespace tree_sitter {
namespace rules {

class Blank;
class NamedSymbol;
class CharacterSet;
class Choice;
class Repeat;
class Seq;
class String;
class Symbol;
class Pattern;
class Metadata;

class Visitor {
 public:
  virtual void visit(const Blank *rule) = 0;
  virtual void visit(const CharacterSet *rule) = 0;
  virtual void visit(const Choice *rule) = 0;
  virtual void visit(const Metadata *rule) = 0;
  virtual void visit(const Pattern *rule) = 0;
  virtual void visit(const Repeat *rule) = 0;
  virtual void visit(const Seq *rule) = 0;
  virtual void visit(const String *rule) = 0;
  virtual void visit(const NamedSymbol *rule) = 0;
  virtual void visit(const Symbol *rule) = 0;
  virtual ~Visitor();
};

template <typename T>
class RuleFn : private Visitor {
 public:
  T apply(const rule_ptr &rule) {
    value_ = T();
    rule->accept(this);
    return value_;
  }

 protected:
  virtual T default_apply(const Rule *rule) { return T(); }

  virtual T apply_to(const Blank *rule) {
    return default_apply((const Rule *)rule);
  }
  virtual T apply_to(const CharacterSet *rule) {
    return default_apply((const Rule *)rule);
  }
  virtual T apply_to(const Choice *rule) {
    return default_apply((const Rule *)rule);
  }
  virtual T apply_to(const Metadata *rule) {
    return default_apply((const Rule *)rule);
  }
  virtual T apply_to(const Pattern *rule) {
    return default_apply((const Rule *)rule);
  }
  virtual T apply_to(const Repeat *rule) {
    return default_apply((const Rule *)rule);
  }
  virtual T apply_to(const Seq *rule) {
    return default_apply((const Rule *)rule);
  }
  virtual T apply_to(const String *rule) {
    return default_apply((const Rule *)rule);
  }
  virtual T apply_to(const NamedSymbol *rule) {
    return default_apply((const Rule *)rule);
  }
  virtual T apply_to(const Symbol *rule) {
    return default_apply((const Rule *)rule);
  }

  void visit(const Blank *rule) { value_ = apply_to(rule); }
  void visit(const CharacterSet *rule) { value_ = apply_to(rule); }
  void visit(const Choice *rule) { value_ = apply_to(rule); }
  void visit(const Metadata *rule) { value_ = apply_to(rule); }
  void visit(const Pattern *rule) { value_ = apply_to(rule); }
  void visit(const Repeat *rule) { value_ = apply_to(rule); }
  void visit(const Seq *rule) { value_ = apply_to(rule); }
  void visit(const String *rule) { value_ = apply_to(rule); }
  void visit(const NamedSymbol *rule) { value_ = apply_to(rule); }
  void visit(const Symbol *rule) { value_ = apply_to(rule); }

 private:
  T value_;
};

template <>
class RuleFn<void> : private Visitor {
 public:
  void apply(const rule_ptr &rule) {
    rule->accept(this);
  }

 protected:
  virtual void default_apply(const Rule *rule) {}

  virtual void apply_to(const Blank *rule) {
    return default_apply((const Rule *)rule);
  }
  virtual void apply_to(const CharacterSet *rule) {
    return default_apply((const Rule *)rule);
  }
  virtual void apply_to(const Choice *rule) {
    return default_apply((const Rule *)rule);
  }
  virtual void apply_to(const Metadata *rule) {
    return default_apply((const Rule *)rule);
  }
  virtual void apply_to(const Pattern *rule) {
    return default_apply((const Rule *)rule);
  }
  virtual void apply_to(const Repeat *rule) {
    return default_apply((const Rule *)rule);
  }
  virtual void apply_to(const Seq *rule) {
    return default_apply((const Rule *)rule);
  }
  virtual void apply_to(const String *rule) {
    return default_apply((const Rule *)rule);
  }
  virtual void apply_to(const NamedSymbol *rule) {
    return default_apply((const Rule *)rule);
  }
  virtual void apply_to(const Symbol *rule) {
    return default_apply((const Rule *)rule);
  }

  void visit(const Blank *rule) { apply_to(rule); }
  void visit(const CharacterSet *rule) { apply_to(rule); }
  void visit(const Choice *rule) { apply_to(rule); }
  void visit(const Metadata *rule) { apply_to(rule); }
  void visit(const Pattern *rule) { apply_to(rule); }
  void visit(const Repeat *rule) { apply_to(rule); }
  void visit(const Seq *rule) { apply_to(rule); }
  void visit(const String *rule) { apply_to(rule); }
  void visit(const NamedSymbol *rule) { apply_to(rule); }
  void visit(const Symbol *rule) { apply_to(rule); }
};

class IdentityRuleFn : public RuleFn<rule_ptr> {
 protected:
  virtual rule_ptr default_apply(const Rule *rule);
  virtual rule_ptr apply_to(const Choice *rule);
  virtual rule_ptr apply_to(const Metadata *rule);
  virtual rule_ptr apply_to(const Seq *rule);
  virtual rule_ptr apply_to(const Repeat *rule);
};

}  // namespace rules
}  // namespace tree_sitter

#endif  // COMPILER_RULES_VISITOR_H_
