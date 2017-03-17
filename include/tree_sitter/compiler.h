#ifndef TREE_SITTER_COMPILER_H_
#define TREE_SITTER_COMPILER_H_

#ifdef __cplusplus
extern "C" {
#endif

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
} TSCompileErrorType;

typedef struct {
  char *code;
  char *error_message;
  TSCompileErrorType error_type;
} TSCompileResult;

TSCompileResult ts_compile_grammar(const char *input);

#ifdef __cplusplus
}
#endif

#endif  // TREE_SITTER_COMPILER_H_
