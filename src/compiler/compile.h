#ifndef COMPILER_COMPILE_H_
#define COMPILER_COMPILE_H_

#include <string>
#include <utility>
#include "compiler/compile_error.h"

namespace tree_sitter {

struct InputGrammar;

std::pair<std::string, CompileError> compile(const InputGrammar &, std::string);

}  // namespace tree_sitter

#endif  // COMPILER_COMPILE_H_
