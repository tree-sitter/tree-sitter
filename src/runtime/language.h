#ifndef RUNTIME_LANGUAGE_H_
#define RUNTIME_LANGUAGE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "tree_sitter/parser.h"

bool ts_language_symbol_is_in_progress(const TSLanguage *, TSStateId, TSSymbol);

const TSParseAction *ts_language_actions(const TSLanguage *, TSStateId,
                                         TSSymbol, size_t *);
TSParseAction ts_language_last_action(const TSLanguage *, TSStateId, TSSymbol);

bool ts_language_has_action(const TSLanguage *, TSStateId, TSSymbol);

TSSymbolMetadata ts_language_symbol_metadata(const TSLanguage *language,
                                             TSSymbol symbol);

#ifdef __cplusplus
}
#endif

#endif  // RUNTIME_LANGUAGE_H_
