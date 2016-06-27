#ifndef RUNTIME_LANGUAGE_H_
#define RUNTIME_LANGUAGE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "tree_sitter/parser.h"
#include "runtime/tree.h"

typedef struct {
  const TSParseAction *actions;
  size_t action_count;
  bool is_reusable;
  bool depends_on_lookahead;
} TableEntry;

void ts_language_table_entry(const TSLanguage *, TSStateId, TSSymbol,
                             TableEntry *);

bool ts_language_symbol_is_in_progress(const TSLanguage *, TSStateId, TSSymbol);

static inline const TSParseAction *ts_language_actions(const TSLanguage *self,
                                                       TSStateId state,
                                                       TSSymbol symbol,
                                                       size_t *count) {
  TableEntry entry;
  ts_language_table_entry(self, state, symbol, &entry);
  *count = entry.action_count;
  return entry.actions;
}

static inline const TSParseAction *ts_language_last_action(
  const TSLanguage *self, TSStateId state, TSSymbol symbol) {
  TableEntry entry;
  ts_language_table_entry(self, state, symbol, &entry);
  if (entry.action_count)
    return &entry.actions[entry.action_count - 1];
  else
    return NULL;
}

static inline bool ts_language_is_reusable(const TSLanguage *self,
                                           TSStateId state, TSSymbol symbol) {
  TableEntry entry;
  ts_language_table_entry(self, state, symbol, &entry);
  return entry.is_reusable;
}

TSSymbolMetadata ts_language_symbol_metadata(const TSLanguage *, TSSymbol);

#ifdef __cplusplus
}
#endif

#endif  // RUNTIME_LANGUAGE_H_
