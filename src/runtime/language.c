#include "tree_sitter/parser.h"

const TSParseAction *ts_language_actions(const TSLanguage *language,
                                         TSStateId state, TSSymbol symbol,
                                         size_t *count) {
  size_t action_index = 0;
  if (symbol != ts_builtin_sym_error) {
    if (state == ts_parse_state_error)
      state = language->out_of_context_states[symbol];
    action_index =
      (language->parse_table + (state * language->symbol_count))[symbol];
  }

  *count = language->parse_actions[action_index].count;
  const TSParseActionEntry *entry = language->parse_actions + action_index + 1;
  return (const TSParseAction *)entry;
}

TSParseAction ts_language_last_action(const TSLanguage *language,
                                      TSStateId state, TSSymbol sym) {
  size_t count;
  const TSParseAction *actions =
    ts_language_actions(language, state, sym, &count);
  return actions[count - 1];
}

bool ts_language_has_action(const TSLanguage *language, TSStateId state,
                            TSSymbol symbol) {
  TSParseAction action = ts_language_last_action(language, state, symbol);
  return action.type != TSParseActionTypeError;
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

bool ts_language_symbol_is_in_progress(const TSLanguage *self, TSStateId state,
                                       TSSymbol symbol) {
  if (state == ts_parse_state_error)
    return false;
  unsigned index = self->in_progress_symbol_table[state];
  size_t count = self->in_progress_symbols[index].count;
  const TSSymbol *symbols = (TSSymbol *)(self->in_progress_symbols + index + 1);
  for (size_t i = 0; i < count; i++) {
    if (symbols[i] == symbol)
      return true;
  }
  return false;
}
