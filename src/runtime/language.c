#include "tree_sitter/parser.h"
#include "runtime/language.h"
#include "runtime/tree.h"

const TSParseAction *ts_language_actions(const TSLanguage *self, TSStateId state,
                                         TSSymbol symbol, size_t *count) {
  if (state == ts_parse_state_error) {
    *count = 1;
    return &self->recovery_actions[symbol];
  }

  size_t action_index = 0;
  if (symbol != ts_builtin_sym_error)
    action_index = self->parse_table[state * self->symbol_count + symbol];

  *count = self->parse_actions[action_index].count;
  const TSParseActionEntry *entry = self->parse_actions + action_index + 1;
  return (const TSParseAction *)entry;
}

TSParseAction ts_language_last_action(const TSLanguage *self, TSStateId state,
                                      TSSymbol sym) {
  size_t count;
  const TSParseAction *actions = ts_language_actions(self, state, sym, &count);
  return actions[count - 1];
}

bool ts_language_has_action(const TSLanguage *self, TSStateId state,
                            TSSymbol symbol) {
  TSParseAction action = ts_language_last_action(self, state, symbol);
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
