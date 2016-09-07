#ifndef HELPERS_STDERR_LOGGER_H_
#define HELPERS_STDERR_LOGGER_H_

#include "tree_sitter/runtime.h"

TSLogger stderr_logger_new(bool include_lexing);

#endif  // HELPERS_STDERR_LOGGER_H_
