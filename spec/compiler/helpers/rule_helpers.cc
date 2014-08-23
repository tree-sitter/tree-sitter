#include "rule_helpers.h"
#include <memory>
#include "compiler/rules/symbol.h"

namespace tree_sitter {
  using std::make_shared;
  using std::set;
  using std::map;

  namespace rules {
    rule_ptr character(const set<CharacterRange> &ranges) {
      return character(ranges, true);
    }

    rule_ptr character(const set<CharacterRange> &ranges, bool sign) {
      CharacterSet result;
      if (sign) {
        for (auto &range : ranges)
          result.include(range.min, range.max);
      } else {
        result.include_all();
        for (auto &range : ranges)
          result.exclude(range.min, range.max);
      }
      return result.copy();
    }

    rule_ptr i_sym(size_t index) {
      return make_shared<rules::Symbol>(index);
    }

    rule_ptr i_aux_sym(size_t index) {
      return make_shared<rules::Symbol>(index, SymbolOptionAuxiliary);
    }

    rule_ptr i_token(size_t index) {
      return make_shared<rules::Symbol>(index, SymbolOptionToken);
    }

    rule_ptr i_aux_token(size_t index) {
      return make_shared<rules::Symbol>(index, SymbolOption(SymbolOptionAuxiliary|SymbolOptionToken));
    }

    rule_ptr metadata(rule_ptr rule, map<MetadataKey, int> values) {
      return make_shared<Metadata>(rule, values);
    }
  }
}
