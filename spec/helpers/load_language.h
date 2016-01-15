#ifndef HELPERS_LOAD_LANGUAGE_H_
#define HELPERS_LOAD_LANGUAGE_H_

#include "tree_sitter/compiler.h"
#include "tree_sitter/runtime.h"
#include <string>

const TSLanguage *load_language(const std::string &, const std::string &);
const TSLanguage *load_language(const std::string &, const TSCompileResult &);

#endif  // HELPERS_LOAD_LANGUAGE_H_
