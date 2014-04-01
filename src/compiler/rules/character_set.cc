#include "compiler/rules/character_set.h"
#include <string>
#include <utility>
#include "compiler/rules/visitor.h"

using std::string;
using std::hash;
using std::set;
using std::pair;
using std::initializer_list;

namespace tree_sitter  {
    namespace rules {
        static const unsigned char MAX_CHAR = -1;

        CharacterSet::CharacterSet() : ranges({}) {}
        CharacterSet::CharacterSet(const set<CharacterRange> &ranges) : ranges(ranges) {}
        CharacterSet::CharacterSet(const initializer_list<CharacterRange> &ranges) : ranges(ranges) {}

        bool CharacterSet::operator==(const Rule &rule) const {
            const CharacterSet *other = dynamic_cast<const CharacterSet *>(&rule);
            return other && (ranges == other->ranges);
        }

        bool CharacterSet::operator<(const CharacterSet &other) const {
            return ranges < other.ranges;
        }

        size_t CharacterSet::hash_code() const {
            size_t result = std::hash<size_t>()(ranges.size());
            for (auto &range : ranges) {
                result ^= std::hash<unsigned char>()(range.min);
                result ^= std::hash<unsigned char>()(range.max);
            }
            return result;
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
            CharacterSet result({ {0, MAX_CHAR} });
            result.remove_set(*this);
            return result;
        }

        std::pair<CharacterSet, bool> CharacterSet::most_compact_representation() const {
            auto first_range = *ranges.begin();
            if (first_range.min == 0 && first_range.max > 0) {
                return { this->complement(), false };
            } else {
                return { *this, true };
            }
        }

        void add_range(CharacterSet *self, CharacterRange addition) {
            set<CharacterRange> new_ranges;
            for (auto range : self->ranges) {
                bool is_adjacent = false;
                if (range.min < addition.min && range.max >= addition.min - 1) {
                    is_adjacent = true;
                    addition.min = range.min;
                }
                if (range.max > addition.max && range.min <= addition.max + 1) {
                    is_adjacent = true;
                    addition.max = range.max;
                }
                if (!is_adjacent) {
                    new_ranges.insert(range);
                }
            }
            new_ranges.insert(addition);
            self->ranges = new_ranges;
        }

        CharacterSet remove_range(CharacterSet *self, CharacterRange range_to_remove) {
            CharacterSet removed_set;
            set<CharacterRange> new_ranges;
            for (auto range : self->ranges) {
                if (range_to_remove.min <= range.min) {
                    if (range_to_remove.max < range.min) {
                        new_ranges.insert(range);
                    } else if (range_to_remove.max < range.max) {
                        new_ranges.insert(CharacterRange(range_to_remove.max + 1, range.max));
                        add_range(&removed_set, CharacterRange(range.min, range_to_remove.max));
                    } else {
                        add_range(&removed_set, range);
                    }
                } else if (range_to_remove.min <= range.max) {
                    if (range_to_remove.max < range.max) {
                        new_ranges.insert(CharacterRange(range.min, range_to_remove.min - 1));
                        new_ranges.insert(CharacterRange(range_to_remove.max + 1, range.max));
                        add_range(&removed_set, range_to_remove);
                    } else {
                        new_ranges.insert(CharacterRange(range.min, range_to_remove.min - 1));
                        add_range(&removed_set, CharacterRange(range_to_remove.min, range.max));
                    }
                } else {
                    new_ranges.insert(range);
                }
            }
            self->ranges = new_ranges;
            return removed_set;
        }

        bool CharacterSet::is_empty() const {
            return ranges.empty();
        }

        void CharacterSet::add_set(const CharacterSet &other) {
            for (auto &other_range : other.ranges) {
                add_range(this, other_range);
            }
        }

        CharacterSet CharacterSet::remove_set(const CharacterSet &other) {
            CharacterSet result;
            for (auto &other_range : other.ranges) {
                auto removed_set = remove_range(this, other_range);
                result.add_set(removed_set);
            }
            return result;
        }

        CharacterSet CharacterSet::intersect(const CharacterSet &set) const {
            CharacterSet copy = *this;
            return copy.remove_set(set);
        }

        void CharacterSet::accept(Visitor *visitor) const {
            visitor->visit(this);
        }
    }
}
