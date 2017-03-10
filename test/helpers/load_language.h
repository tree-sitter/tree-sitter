#ifndef HELPERS_LOAD_LANGUAGE_H_
#define HELPERS_LOAD_LANGUAGE_H_

#include "tree_sitter/compiler.h"
#include "tree_sitter/runtime.h"
#include <string>

const TSLanguage *load_real_language(const std::string &name);

const TSLanguage *load_test_language(const std::string &name,
                                     const TSCompileResult &compile_result,
                                     std::string external_scanner_path = "");

#endif  // HELPERS_LOAD_LANGUAGE_H_
