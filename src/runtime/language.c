#include "tree_sitter/parser.h"
#include "runtime/language.h"
#include "runtime/tree.h"

static const TSParseAction ERROR_SHIFT_EXTRA = {
  .type = TSParseActionTypeShift, .extra = true,
};

void ts_language_table_entry(const TSLanguage *self, TSStateId state,
                             TSSymbol symbol, TableEntry *result) {
  if (state == ts_parse_state_error) {
    result->action_count = 1;
    result->is_reusable = false;
    result->depends_on_lookahead = false;
    if (symbol == ts_builtin_sym_error ||
        self->recovery_actions[symbol].type == TSParseActionTypeError)
      result->actions = &ERROR_SHIFT_EXTRA;
    else
      result->actions = &self->recovery_actions[symbol];
    return;
  }

  size_t action_index =
    (symbol != ts_builtin_sym_error)
      ? self->parse_table[state * self->symbol_count + symbol]
      : 0;

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
