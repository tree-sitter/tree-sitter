#ifndef TREE_SITTER_COMPILER_H_
#define TREE_SITTER_COMPILER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

typedef enum {
  TSCompileErrorTypeNone,
  TSCompileErrorTypeInvalidGrammar,
  TSCompileErrorTypeInvalidRegex,
  TSCompileErrorTypeUndefinedSymbol,
  TSCompileErrorTypeInvalidExtraToken,
  TSCompileErrorTypeInvalidExternalToken,
  TSCompileErrorTypeLexConflict,
  TSCompileErrorTypeParseConflict,
  TSCompileErrorTypeEpsilonRule,
  TSCompileErrorTypeInvalidTokenContents,
  TSCompileErrorTypeInvalidRuleName,
  TSCompileErrorTypeInvalidWordRule,
} TSCompileErrorType;

typedef struct {
  char *code;
  char *error_message;
  TSCompileErrorType error_type;
} TSCompileResult;

TSCompileResult ts_compile_grammar(const char *input, FILE *log_file);
TSCompileResult ts_compile_property_sheet(const char *input, FILE *log_file);

#ifdef __cplusplus
}
#endif

#endif  // TREE_SITTER_COMPILER_H_
