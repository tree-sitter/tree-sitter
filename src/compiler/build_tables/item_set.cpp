#include "item_set.h"

using std::vector;
using std::ostream;
using std::string;

namespace tree_sitter {
    namespace build_tables {
        ItemSet::ItemSet(const vector<Item> &items) : contents(items) {}
        
        bool ItemSet::operator==(const tree_sitter::build_tables::ItemSet &other) const {
            return contents == other.contents;
        }
        
        ItemSet::const_iterator ItemSet::begin() const {
            return contents.begin();
        }

        ItemSet::const_iterator ItemSet::end() const {
            return contents.end();
        }

        size_t ItemSet::size() const {
            return contents.size();
        }
        
        ostream& operator<<(ostream &stream, const ItemSet &item_set) {
            stream << string("#<item_set ");
            for (Item item : item_set)
                stream << item << string(" ");
            return stream << string(">");
        }
    }
}
