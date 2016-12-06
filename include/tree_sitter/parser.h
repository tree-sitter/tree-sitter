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

typedef struct {
  bool visible : 1;
  bool named : 1;
  bool extra : 1;
  bool structural : 1;
} TSSymbolMetadata;

typedef struct {
  void (*advance)(void *, bool);
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

typedef struct {
  uint16_t lex_state;
  uint16_t external_tokens;
} TSLexMode;

typedef union {
  TSParseAction action;
  struct {
    unsigned short count;
    bool reusable : 1;
    bool depends_on_lookahead : 1;
  };
} TSParseActionEntry;

typedef struct TSLanguage {
  uint32_t symbol_count;
  uint32_t token_count;
  uint32_t external_token_count;
  const char **symbol_names;
  const TSSymbolMetadata *symbol_metadata;
  const unsigned short *parse_table;
  const TSParseActionEntry *parse_actions;
  const TSLexMode *lex_modes;
  bool (*lex_fn)(TSLexer *, TSStateId);
  const TSSymbol *external_token_symbol_map;
  const bool *external_token_lists;
  struct {
    void * (*create)();
    bool (*scan)(void *, TSLexer *, const bool *symbol_whitelist);
    void (*destroy)(void *);
  } external_scanner;
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
    lexer->advance(lexer, false); \
    state = state_value;                       \
    goto next_state;                           \
  }

#define SKIP(state_value)                     \
  {                                           \
    lexer->advance(lexer, true); \
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

#define STATE(id) id
#define ACTIONS(id) id

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

#define GET_LANGUAGE(...)                                          \
  static TSLanguage language = {                                   \
    .symbol_count = SYMBOL_COUNT,                                  \
    .token_count = TOKEN_COUNT,                                    \
    .symbol_metadata = ts_symbol_metadata,                         \
    .parse_table = (const unsigned short *)ts_parse_table,         \
    .parse_actions = ts_parse_actions,                             \
    .lex_modes = ts_lex_modes,                                     \
    .symbol_names = ts_symbol_names,                               \
    .lex_fn = ts_lex,                                              \
    .external_token_count = EXTERNAL_TOKEN_COUNT,                  \
    .external_token_lists = (const bool *)ts_external_token_lists, \
    .external_token_symbol_map = ts_external_token_symbol_map,     \
    .external_scanner = {__VA_ARGS__}                              \
  };                                                               \
  return &language                                                 \

#ifdef __cplusplus
}
#endif

#endif  // TREE_SITTER_PARSER_H_
