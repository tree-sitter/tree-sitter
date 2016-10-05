#include "runtime/language.h"
#include "runtime/tree.h"
#include "runtime/error_costs.h"

static const TSParseAction ERROR_SHIFT_EXTRA = {
  .type = TSParseActionTypeShift, .extra = true,
};

void ts_language_table_entry(const TSLanguage *self, TSStateId state,
                             TSSymbol symbol, TableEntry *result) {
  size_t action_index;
  if (symbol == ts_builtin_sym_error) {
    if (state == ERROR_STATE) {
      result->action_count = 1;
      result->is_reusable = false;
      result->depends_on_lookahead = false;
      result->actions = &ERROR_SHIFT_EXTRA;
      return;
    }
    action_index = 0;
  } else {
    action_index = self->parse_table[state * self->symbol_count + symbol];
  }

  const TSParseActionEntry *entry = &self->parse_actions[action_index];
  result->action_count = entry->count;
  result->is_reusable = entry->reusable;
  result->depends_on_lookahead = entry->depends_on_lookahead;
  result->actions = (const TSParseAction *)(entry + 1);
}

size_t ts_language_symbol_count(const TSLanguage *language) {
  return language->symbol_count;
}

TSSymbolMetadata ts_language_symbol_metadata(const TSLanguage *language,
                                             TSSymbol symbol) {
  if (symbol == ts_builtin_sym_error)
    return (TSSymbolMetadata){
      .visible = true, .named = true, .extra = false, .structural = true,
    };
  else
    return language->symbol_metadata[symbol];
}

const char *ts_language_symbol_name(const TSLanguage *language, TSSymbol symbol) {
  if (symbol == ts_builtin_sym_error)
    return "ERROR";
  else
    return language->symbol_names[symbol];
}
