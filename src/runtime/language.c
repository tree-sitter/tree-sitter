#include "tree_sitter/parser.h"

static const TSParseAction ERROR_ACTIONS[2] = {
  {.type = TSParseActionTypeError }, {.type = 0 }
};

const TSParseAction *ts_language_actions(const TSLanguage *language,
                                         TSStateId state, TSSymbol sym) {
  const TSParseAction *actions =
    (language->parse_table + (state * language->symbol_count))[sym];
  return actions ? actions : ERROR_ACTIONS;
}

TSParseAction ts_language_last_action(const TSLanguage *language,
                                      TSStateId state, TSSymbol sym) {
  const TSParseAction *action = ts_language_actions(language, state, sym);
  while ((action + 1)->type)
    action++;
  return *action;
}

size_t ts_language_symbol_count(const TSLanguage *language) {
  return language->symbol_count;
}

const char *ts_language_symbol_name(TSLanguage *language, TSSymbol symbol) {
  return language->symbol_names[symbol];
}
