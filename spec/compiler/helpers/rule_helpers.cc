#include "rule_helpers.h"
#include <memory>
#include "compiler/rules/symbol.h"

namespace tree_sitter {
  using std::make_shared;
  using std::set;
  using std::map;

  namespace rules {
    rule_ptr character(const set<uint32_t> &ranges) {
      return character(ranges, true);
    }

    rule_ptr character(const set<uint32_t> &chars, bool sign) {
      CharacterSet result;
      if (sign) {
        for (uint32_t c : chars)
          result.include(c);
      } else {
        result.include_all();
        for (uint32_t c : chars)
          result.exclude(c);
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
