#ifndef HELPERS_TEST_LANGUAGES_H_
#define HELPERS_TEST_LANGUAGES_H_

#include "tree_sitter/runtime.h"
#include <string>

const TSLanguage *get_test_language(const std::string &);

#endif  // HELPERS_TEST_LANGUAGES_H_
