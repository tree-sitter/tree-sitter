#include "tree_sitter/parser.h"

const TSParseAction *ts_language_actions(const TSLanguage *language, TSStateId state, TSSymbol sym, size_t *count) {
  unsigned short action_index = (language->parse_table + (state * language->symbol_count))[sym];
  *count = language->parse_actions[action_index].count;
  const TSParseActionEntry *entry = language->parse_actions + action_index + 1;
  return (const TSParseAction *)entry;
}

TSParseAction ts_language_last_action(const TSLanguage *language,
                                      TSStateId state, TSSymbol sym) {
  size_t count;
  const TSParseAction *actions = ts_language_actions(language, state, sym, &count);
  return actions[count - 1];
}

size_t ts_language_symbol_count(const TSLanguage *language) {
  return language->symbol_count;
}

const char *ts_language_symbol_name(TSLanguage *language, TSSymbol symbol) {
  return language->symbol_names[symbol];
}
