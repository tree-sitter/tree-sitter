#include "compiler/rules/character_set.h"
#include "compiler/rules/visitor.h"

using std::string;
using std::hash;
using std::set;
using std::pair;
using std::initializer_list;

namespace tree_sitter  {
    namespace rules {
        static const char MAX_CHAR = '\xff';

        int max_int(const CharacterRange &range) {
            return range.max == MAX_CHAR ? 255 : (int)range.max;
        }

        int min_int(const CharacterRange &range) {
            return (int)range.min;
        }

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
                result ^= std::hash<char>()(range.min);
                result ^= std::hash<char>()(range.max);
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

        void add_range(CharacterSet *self, CharacterRange new_range) {
            set<CharacterRange> new_ranges;

            for (auto range : self->ranges) {
                auto new_min = min_int(new_range);
                auto new_max = max_int(new_range);
                bool is_adjacent = false;

                if (min_int(range) < new_min) {
                    if (max_int(range) >= new_min - 1) {
                        is_adjacent = true;
                        new_range.min = range.min;
                    }
                }
                if (max_int(range) > new_max) {
                    if (min_int(range) <= new_max + 1) {
                        is_adjacent = true;
                        new_range.max = range.max;
                    }
                }

                if (!is_adjacent) {
                    new_ranges.insert(range);
                }
            }
            new_ranges.insert(new_range);
            self->ranges = new_ranges;
        }

        CharacterSet remove_range(CharacterSet *self, CharacterRange new_range) {
            CharacterSet removed_set;
            set<CharacterRange> new_ranges;
            auto new_min = min_int(new_range);
            auto new_max = max_int(new_range);

            for (auto range : self->ranges) {
                if (new_min <= min_int(range)) {
                    if (new_max < min_int(range)) {
                        new_ranges.insert(range);
                    } else if (new_max <= max_int(range)) {
                        new_ranges.insert(CharacterRange(new_max + 1, range.max));
                        add_range(&removed_set, CharacterRange(range.min, new_max));
                    }
                } else if (new_min <= max_int(range)) {
                    if (new_max < max_int(range)) {
                        new_ranges.insert(CharacterRange(range.min, new_min - 1));
                        new_ranges.insert(CharacterRange(new_max + 1, range.max));
                        add_range(&removed_set, new_range);
                    } else {
                        new_ranges.insert(CharacterRange(range.min, new_min - 1));
                        add_range(&removed_set, CharacterRange(new_min, range.max));
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

        void CharacterSet::accept(Visitor &visitor) const {
            visitor.visit(this);
        }
    }
}
