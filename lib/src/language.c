#include "runtime/language.h"
#include "runtime/subtree.h"
#include "runtime/error_costs.h"
#include <string.h>

void ts_language_table_entry(const TSLanguage *self, TSStateId state,
                             TSSymbol symbol, TableEntry *result) {
  if (symbol == ts_builtin_sym_error || symbol == ts_builtin_sym_error_repeat) {
    result->action_count = 0;
    result->is_reusable = false;
    result->actions = NULL;
  } else {
    assert(symbol < self->token_count);
    uint32_t action_index = self->parse_table[state * self->symbol_count + symbol];
    const TSParseActionEntry *entry = &self->parse_actions[action_index];
    result->action_count = entry->count;
    result->is_reusable = entry->reusable;
    result->actions = (const TSParseAction *)(entry + 1);
  }
}

uint32_t ts_language_symbol_count(const TSLanguage *language) {
  return language->symbol_count + language->alias_count;
}

uint32_t ts_language_version(const TSLanguage *language) {
  return language->version;
}

TSSymbolMetadata ts_language_symbol_metadata(const TSLanguage *language, TSSymbol symbol) {
  if (symbol == ts_builtin_sym_error)  {
    return (TSSymbolMetadata){.visible = true, .named = true};
  } else if (symbol == ts_builtin_sym_error_repeat) {
    return (TSSymbolMetadata){.visible = false, .named = false};
  } else {
    return language->symbol_metadata[symbol];
  }
}

const char *ts_language_symbol_name(const TSLanguage *language, TSSymbol symbol) {
  if (symbol == ts_builtin_sym_error) {
    return "ERROR";
  } else if (symbol == ts_builtin_sym_error_repeat) {
    return "_ERROR";
  } else {
    return language->symbol_names[symbol];
  }
}

TSSymbol ts_language_symbol_for_name(const TSLanguage *self, const char *name) {
  if (!strcmp(name, "ERROR")) return ts_builtin_sym_error;

  uint32_t count = ts_language_symbol_count(self);
  for (TSSymbol i = 0; i < count; i++) {
    if (!strcmp(self->symbol_names[i], name)) {
      return i;
    }
  }
  return 0;
}

TSSymbolType ts_language_symbol_type(const TSLanguage *language, TSSymbol symbol) {
  TSSymbolMetadata metadata = ts_language_symbol_metadata(language, symbol);
  if (metadata.named) {
    return TSSymbolTypeRegular;
  } else if (metadata.visible) {
    return TSSymbolTypeAnonymous;
  } else {
    return TSSymbolTypeAuxiliary;
  }
}
