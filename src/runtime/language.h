#ifndef RUNTIME_LANGUAGE_H_
#define RUNTIME_LANGUAGE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "tree_sitter/parser.h"

const TSParseAction *ts_language_actions(const TSLanguage *, TSStateId, TSSymbol, size_t *);
TSParseAction ts_language_last_action(const TSLanguage *, TSStateId, TSSymbol);

#ifdef __cplusplus
}
#endif

#endif  // RUNTIME_LANGUAGE_H_
