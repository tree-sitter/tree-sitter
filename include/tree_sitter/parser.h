#ifndef TREE_SITTER_PARSER_H_
#define TREE_SITTER_PARSER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef unsigned short TSSymbol;
typedef unsigned short TSStateId;

#define ts_builtin_sym_error ((TSSymbol)-1)
#define ts_builtin_sym_end 0
#define ts_builtin_sym_start 1

typedef struct {
  bool visible : 1;
  bool named : 1;
  bool extra : 1;
  bool structural : 1;
} TSSymbolMetadata;

typedef struct {
  void (*advance)(void *, TSStateId, bool);
  int32_t lookahead;
  TSSymbol result_symbol;
} TSLexer;

typedef enum {
  TSParseActionTypeShift,
  TSParseActionTypeReduce,
  TSParseActionTypeAccept,
  TSParseActionTypeRecover,
} TSParseActionType;

typedef struct {
  union {
    TSStateId to_state;
    struct {
      TSSymbol symbol;
      unsigned short child_count;
    };
  } params;
  TSParseActionType type : 4;
  bool extra : 1;
  bool fragile : 1;
} TSParseAction;

typedef union {
  TSParseAction action;
  struct {
    unsigned short count;
    bool reusable : 1;
    bool depends_on_lookahead : 1;
  };
} TSParseActionEntry;

typedef struct TSLanguage {
  size_t symbol_count;
  const char **symbol_names;
  const TSSymbolMetadata *symbol_metadata;
  const unsigned short *parse_table;
  const TSParseActionEntry *parse_actions;
  const TSStateId *lex_states;
  bool (*lex_fn)(TSLexer *, TSStateId);
} TSLanguage;

/*
 *  Lexer Macros
 */

#define START_LEXER() \
  int32_t lookahead;  \
  next_state:         \
  lookahead = lexer->lookahead;

#define ADVANCE(state_value)                   \
  {                                            \
    lexer->advance(lexer, state_value, false); \
    state = state_value;                       \
    goto next_state;                           \
  }

#define SKIP(state_value)                     \
  {                                           \
    lexer->advance(lexer, state_value, true); \
    state = state_value;                      \
    goto next_state;                          \
  }

#define ACCEPT_TOKEN(symbol_value)       \
  {                                      \
    lexer->result_symbol = symbol_value; \
    return true;                         \
  }

#define LEX_ERROR() return false

/*
 *  Parse Table Macros
 */

#define SHIFT(to_state_value)                                                 \
  {                                                                           \
    {                                                                         \
      .type = TSParseActionTypeShift, .params = {.to_state = to_state_value } \
    }                                                                         \
  }

#define RECOVER(to_state_value)                                                 \
  {                                                                             \
    {                                                                           \
      .type = TSParseActionTypeRecover, .params = {.to_state = to_state_value } \
    }                                                                           \
  }

#define SHIFT_EXTRA()                                 \
  {                                                   \
    { .type = TSParseActionTypeShift, .extra = true } \
  }

#define REDUCE(symbol_val, child_count_val)                             \
  {                                                                     \
    {                                                                   \
      .type = TSParseActionTypeReduce,                                  \
      .params = {.symbol = symbol_val, .child_count = child_count_val } \
    }                                                                   \
  }

#define REDUCE_FRAGILE(symbol_val, child_count_val)                     \
  {                                                                     \
    {                                                                   \
      .type = TSParseActionTypeReduce, .fragile = true,                 \
      .params = {.symbol = symbol_val, .child_count = child_count_val } \
    }                                                                   \
  }

#define ACCEPT_INPUT()                  \
  {                                     \
    { .type = TSParseActionTypeAccept } \
  }

#define EXPORT_LANGUAGE(language_name)                     \
  static TSLanguage language = {                           \
    .symbol_count = SYMBOL_COUNT,                          \
    .symbol_metadata = ts_symbol_metadata,                 \
    .parse_table = (const unsigned short *)ts_parse_table, \
    .parse_actions = ts_parse_actions,                     \
    .lex_states = ts_lex_states,                           \
    .symbol_names = ts_symbol_names,                       \
    .lex_fn = ts_lex,                                      \
  };                                                       \
                                                           \
  const TSLanguage *language_name() {                      \
    return &language;                                      \
  }

#ifdef __cplusplus
}
#endif

#endif  // TREE_SITTER_PARSER_H_
