#ifndef INTEGRATION_HELPERS_LOAD_LANGUAGE_H_
#define INTEGRATION_HELPERS_LOAD_LANGUAGE_H_

#include "tree_sitter/compiler.h"
#include "tree_sitter/runtime.h"
#include <string>

const TSLanguage *load_language(const std::string &, const TSCompileResult &);

#endif  // INTEGRATION_HELPERS_LOAD_LANGUAGE_H_
