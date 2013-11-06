#include "rules.h"
#include "spec_helper.h"
#include "transition_map.h"

using namespace std;

namespace tree_sitter  {
    namespace rules {
        // Constructors
        Blank::Blank() {}
        Symbol::Symbol(int id) : id(id) {};
        Seq::Seq(const Rule &left, const Rule &right) : left(left.copy()), right(right.copy()) {};
        Seq::Seq(const Rule *left, const Rule *right) : left(left), right(right) {};
        Seq::Seq(shared_ptr<const Rule> left, shared_ptr<const Rule> right) : left(left), right(right) {};
        Choice::Choice(const Rule &left, const Rule &right) : left(left.copy()), right(right.copy()) {};
        Choice::Choice(const Rule *left, const Rule *right) : left(left), right(right) {};
        Choice::Choice(shared_ptr<const Rule> left, shared_ptr<const Rule> right) : left(left), right(right) {};

        // Transitions
        TransitionMap<Rule> Blank::transitions() const {
            return TransitionMap<Rule>();
        }
        
        TransitionMap<Rule> Symbol::transitions() const {
            return TransitionMap<Rule>({ copy() }, { new Blank() });
        }
        
        TransitionMap<Rule> Choice::transitions() const {
            auto result = left->transitions();
            result.merge(right->transitions(), [&](rule_ptr left, rule_ptr right) -> rule_ptr {
                return rule_ptr(new Choice(left, right));
            });
            return result;
        }
        
        TransitionMap<Rule> Seq::transitions() const {
            return left->transitions().map([&](rule_ptr left_rule) -> rule_ptr {
                if (typeid(*left_rule) == typeid(Blank)) {
                    return right;
                } else {
                    return rule_ptr(new Seq(left_rule, right));
                }
            });
        }
        
        // Equality
        bool Blank::operator==(const Rule &rule) const {
            return dynamic_cast<const Blank *>(&rule) != NULL;
        }

        bool Symbol::operator==(const Rule &rule) const {
            const Symbol *other = dynamic_cast<const Symbol *>(&rule);
            return (other != NULL) && (other->id == id);
        }
        
        bool Choice::operator==(const Rule &rule) const {
            const Choice *other = dynamic_cast<const Choice *>(&rule);
            return (other != NULL) && (*other->left == *left) && (*other->right == *right);
        }

        bool Seq::operator==(const Rule &rule) const {
            const Seq *other = dynamic_cast<const Seq *>(&rule);
            return (other != NULL) && (*other->left == *left) && (*other->right == *right);
        }

        // Copying
        Blank * Blank::copy() const {
            return new Blank();
        }

        Symbol * Symbol::copy() const {
            return new Symbol(id);
        }
        
        Choice * Choice::copy() const {
            return new Choice(left, right);
        }

        Seq * Seq::copy() const {
            return new Seq(left, right);
        }
        
        // Description
        string Blank::to_string() const {
            return "blank";
        }

        string Symbol::to_string() const {
            return string(std::to_string(id));
        }
        
        string Choice::to_string() const {
            return string("(choice ") + left->to_string() + " " + right->to_string() + ")";
        }

        string Seq::to_string() const {
            return string("(seq ") + left->to_string() + " " + right->to_string() + ")";
        }
    }
}