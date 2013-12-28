#include "item_set.h"

using std::vector;
using std::initializer_list;
using std::dynamic_pointer_cast;
using std::ostream;
using std::string;

namespace tree_sitter {
    namespace lr {
        ItemSet::ItemSet(const vector<Item> &items) : contents(items) {}
        ItemSet::ItemSet(const initializer_list<Item> &items) : contents(items) {}

        static bool vector_contains(vector<Item> items, lr::Item item) {
            return (std::find(items.begin(), items.end(), item) != items.end());
        }
        
        static void add_item(vector<Item> &vector, const Item &item, const Grammar &grammar) {
            if (!vector_contains(vector, item)) {
                vector.push_back(item);
                for (rules::Symbol rule : item.next_symbols()) {
                    Item next_item = Item::at_beginning_of_rule(rule.name, grammar);
                    add_item(vector, next_item, grammar);
                }
            }
        }
        
        static vector<Item> closure_in_grammar(const Item &item, const Grammar &grammar) {
            vector<Item> result;
            add_item(result, item, grammar);
            return result;
        }
        
        ItemSet::ItemSet(const Item &item, const Grammar &grammar) : contents(closure_in_grammar(item, grammar)) {}
        
        template<typename RuleClass>
        static transition_map<RuleClass, ItemSet> transitions(const ItemSet &item_set, const Grammar &grammar) {
            transition_map<RuleClass, ItemSet> result;
            for (auto item : item_set) {
                auto item_transitions = item.transitions();
                for (auto pair : item_transitions) {
                    std::shared_ptr<const RuleClass> rule = dynamic_pointer_cast<const RuleClass>(pair.first);
                    Item item = *pair.second;
                    if (rule.get() != nullptr)
                        result.add(rule, std::make_shared<ItemSet>(item, grammar));
                }
            }
            return result;
        }

        transition_map<rules::Character, ItemSet> ItemSet::char_transitions(const Grammar &grammar) const {
            return transitions<rules::Character>(*this, grammar);
        }
        
        transition_map<rules::Symbol, ItemSet> ItemSet::sym_transitions(const Grammar &grammar) const {
            return transitions<rules::Symbol>(*this, grammar);
        }

        bool ItemSet::operator==(const tree_sitter::lr::ItemSet &other) const {
            return contents == other.contents;
        }
        
#pragma mark - container
        
        ItemSet::const_iterator ItemSet::begin() const {
            return contents.begin();
        }

        ItemSet::const_iterator ItemSet::end() const {
            return contents.end();
        }

        size_t ItemSet::size() const {
            return contents.size();
        }
        
#pragma mark - printing
        
        ostream& operator<<(ostream &stream, const ItemSet &item_set) {
            stream << string("(item_set ");
            for (Item item : item_set) {
                stream << item;
                stream << string(" ");
            }
            stream << string(")");
            return stream;
        }
    }
}
