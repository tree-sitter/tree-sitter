#ifndef COMPILER_COMPILE_ERROR_H_
#define COMPILER_COMPILE_ERROR_H_

#include <string>
#include "tree_sitter/compiler.h"

namespace tree_sitter {

class CompileError {
 public:
  CompileError() : type(TSCompileErrorTypeNone) {}

  CompileError(TSCompileErrorType type, std::string message)
      : type(type), message(message) {}

  static CompileError none() {
    return CompileError(TSCompileErrorTypeNone, "");
  }

  operator bool() const {
    return type != TSCompileErrorTypeNone;
  }

  bool operator==(const CompileError &other) const {
    return type == other.type && message == other.message;
  }

  TSCompileErrorType type;
  std::string message;
};

}  // namespace tree_sitter

#endif  // COMPILER_COMPILE_ERROR_H_
