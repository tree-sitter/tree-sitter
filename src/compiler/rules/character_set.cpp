#include "rules.h"

using std::string;
using std::hash;
using std::set;

namespace tree_sitter  {
    namespace rules {
        const char MAX_CHAR = '\xff';
        
        CharacterRange::CharacterRange(char value) : min(value), max(value) {}
        CharacterRange::CharacterRange(char min, char max) :
            min(min),
            max(max)
        {}
        
        bool CharacterRange::operator==(const CharacterRange &other) const {
            return min == other.min && max == other.max;
        }

        bool CharacterRange::operator<(const CharacterRange &other) const {
            if (min < other.min) return true;
            if (min > other.min) return false;
            if (max < other.max) return true;
            return false;
        }

        string escape_character(char input) {
            switch (input) {
                case '\0':
                    return "<EOF>";
                case MAX_CHAR:
                    return "<MAX>";
                default:
                    return string() + input;
            }
        }
        
        int CharacterRange::max_int() const {
            return max == MAX_CHAR ? 255 : (int)max;
        }
        
        int CharacterRange::min_int() const {
            return (int)min;
        }
        
        bool CharacterRange::is_adjacent(const CharacterRange &other) const {
            return
            (min_int() <= other.min_int() && max_int() >= (other.min_int() - 1)) || 
            (min_int() <= (other.max_int() + 1) && max_int() >= other.max_int());
        }
        
        void CharacterRange::add_range(const CharacterRange &other) {
            if (other.min < min) min = other.min;
            if (other.max_int() > max_int()) max = other.max;
        }
        
        string CharacterRange::to_string() const {
            if (min == 0 && max == MAX_CHAR)
                return "<ANY>";
            if (min == max)
                return escape_character(min);
            else
                return string() + escape_character(min) + "-" + escape_character(max);
        }
        
        CharacterSet::CharacterSet() : ranges({}) {}
        CharacterSet::CharacterSet(const set<CharacterRange> &ranges) : ranges(ranges) {}
        CharacterSet::CharacterSet(const set<CharacterRange> &ranges, bool sign) :
            ranges(sign ? ranges : CharacterSet(ranges).complement().ranges) {}
        
        bool CharacterSet::operator==(const Rule &rule) const {
            const CharacterSet *other = dynamic_cast<const CharacterSet *>(&rule);
            return other && (ranges == other->ranges);
        }
        
        size_t CharacterSet::hash_code() const {
            return typeid(this).hash_code() ^ hash<string>()(to_string());
        }

        rule_ptr CharacterSet::copy() const {
            return std::make_shared<CharacterSet>(*this);
        }

        string CharacterSet::to_string() const {
            string result("#<char {");
            for (auto &range : ranges)
                result += " " + range.to_string();
            return result + " }>";
        }
        
        CharacterSet CharacterSet::complement() const {
            set<CharacterRange> result;
            char current_char = 0;
            for (auto &range : ranges) {
                if (range.min != 0)
                    result.insert(CharacterRange(current_char, range.min - 1));
                current_char = range.max + 1;
            }
            if (current_char != 0)
                result.insert(CharacterRange(current_char, MAX_CHAR));
            return CharacterSet(result);
        }
        
        std::pair<CharacterSet, bool> CharacterSet::most_compact_representation() const {
            auto first_range = *ranges.begin();
            if (first_range.min == 0 && first_range.max > 0) {
                return { this->complement(), false };
            } else {
                return { *this, true };
            }
        }
        
        void add_range(CharacterSet *self, CharacterRange new_range) {
            set<CharacterRange> new_ranges;
            for (auto range : self->ranges) {
                if (range.is_adjacent(new_range)) {
                    new_range.add_range(range);
                } else {
                    new_ranges.insert(range);
                }
            }
            new_ranges.insert(new_range);
            self->ranges = new_ranges;
        }
        
        void CharacterSet::union_with(const CharacterSet &other) {
            for (auto &other_range : other.ranges) {
                add_range(this, other_range);
            }
        }
        
        void CharacterSet::accept(Visitor &visitor) const {
            visitor.visit(this);
        }
    }
}
