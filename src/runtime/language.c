#include "runtime/parser.h"

size_t ts_language_symbol_count(const TSLanguage *) {
  return language->symbol_count;
}

const char *ts_language_symbol_name(TSLanguage *language, TSSymbol symbol) {
  return language->symbol_names[symbol];
}
