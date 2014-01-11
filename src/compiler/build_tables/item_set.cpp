#include "item_set.h"

using std::vector;
using std::set;
using std::initializer_list;
using std::dynamic_pointer_cast;
using std::ostream;
using std::string;
using std::make_shared;

namespace tree_sitter {
    namespace build_tables {
        ItemSet::ItemSet(const vector<Item> &items) : contents(items) {}
        ItemSet::ItemSet(const initializer_list<Item> &items) : contents(items) {}

        static bool vector_contains(vector<Item> items, build_tables::Item item) {
            return (std::find(items.begin(), items.end(), item) != items.end());
        }
        
        static void add_item(vector<Item> &vector, const Item &item, const Grammar &grammar) {
            if (!vector_contains(vector, item)) {
                vector.push_back(item);
                for (rules::Symbol rule : item.next_symbols()) {
                    if (grammar.has_definition(rule)) {
                        Item next_item = Item::at_beginning_of_rule(rule.name, grammar);
                        add_item(vector, next_item, grammar);
                    }
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
        transition_map<RuleClass, ItemSet> transitions(const ItemSet *item_set, const Grammar &grammar) {
            transition_map<RuleClass, ItemSet> result;
            for (Item item : *item_set) {
                for (auto transition : item.transitions()) {
                    auto rule = dynamic_pointer_cast<const RuleClass>(transition.first);
                    if (rule.get()) result.add(rule, make_shared<ItemSet>(*transition.second, grammar));
                }
            }
            return result;
        }

        transition_map<rules::Character, ItemSet> ItemSet::char_transitions(const Grammar &grammar) const {
            return transitions<rules::Character>(this, grammar);
        }

        transition_map<rules::Symbol, ItemSet> ItemSet::sym_transitions(const Grammar &grammar) const {
            return transitions<rules::Symbol>(this, grammar);
        }

        set<rules::Symbol> ItemSet::next_terminal_symbols(const Grammar &grammar) const {
            set<rules::Symbol> result;
            for (Item item : *this)
                for (rules::Symbol symbol : item.next_symbols())
                    if (!grammar.has_definition(symbol))
                        result.insert(symbol);
            return result;
        }

        bool ItemSet::operator==(const tree_sitter::build_tables::ItemSet &other) const {
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
            stream << string("#<item_set ");
            for (Item item : item_set)
                stream << item << string(" ");
            return stream << string(">");
        }
    }
}
