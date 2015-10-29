#include "runtime/parser.h"

const char *ts_language_symbol_name(TSLanguage *language, TSSymbol symbol) {
  return language->symbol_names[symbol];
}
