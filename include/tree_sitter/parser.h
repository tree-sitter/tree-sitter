#ifndef TREE_SITTER_PARSER_H_
#define TREE_SITTER_PARSER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include "tree_sitter/runtime.h"

#define ts_lex_state_error 0
#define ts_parse_state_error ((TSStateId)-1)
#define TS_DEBUG_BUFFER_SIZE 512

typedef unsigned short TSStateId;

typedef struct {
  size_t bytes;
  size_t chars;
  size_t rows;
  size_t columns;
} TSLength;

typedef struct {
  bool visible : 1;
  bool named : 1;
  bool extra : 1;
  bool structural : 1;
} TSSymbolMetadata;

typedef enum {
  TSTransitionTypeMain,
  TSTransitionTypeSeparator,
  TSTransitionTypeError,
} TSTransitionType;

typedef struct TSLexer {
  void (*advance)(struct TSLexer *, TSStateId, TSTransitionType);

  TSLength current_position;
  TSLength token_end_position;
  TSLength token_start_position;
  TSLength error_end_position;

  const char *chunk;
  size_t chunk_start;
  size_t chunk_size;

  size_t lookahead_size;
  int32_t lookahead;
  TSStateId starting_state;
  TSSymbol result_symbol;
  bool result_is_fragile;
  bool result_follows_error;
  int32_t first_unexpected_character;

  TSInput input;
  TSDebugger debugger;
  char debug_buffer[TS_DEBUG_BUFFER_SIZE];
} TSLexer;

typedef enum {
  TSParseActionTypeError,
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
  } data;
  TSParseActionType type : 3;
  bool extra : 1;
  bool fragile : 1;
  bool can_hide_split : 1;
} TSParseAction;

typedef union {
  TSParseAction action;
  unsigned int count;
} TSParseActionEntry;

struct TSLanguage {
  size_t symbol_count;
  const char **symbol_names;
  const TSSymbolMetadata *symbol_metadata;
  const unsigned short *parse_table;
  const TSParseActionEntry *parse_actions;
  const TSStateId *lex_states;
  const TSParseAction *recovery_actions;
  bool (*lex_fn)(TSLexer *, TSStateId, bool);
};

/*
 *  Lexer Macros
 */

#define START_LEXER() \
  int32_t lookahead;  \
  next_state:         \
  lookahead = lexer->lookahead;

#define GO_TO_STATE(state_value) \
  {                              \
    state = state_value;         \
    goto next_state;             \
  }

#define ADVANCE(state_value)                                  \
  {                                                           \
    lexer->advance(lexer, state_value, TSTransitionTypeMain); \
    GO_TO_STATE(state_value);                                 \
  }

#define SKIP(state_value)                                          \
  {                                                                \
    lexer->advance(lexer, state_value, TSTransitionTypeSeparator); \
    GO_TO_STATE(state_value);                                      \
  }

#define ACCEPT_FRAGILE_TOKEN(symbol_value) \
  {                                        \
    lexer->result_is_fragile = true;       \
    lexer->result_symbol = symbol_value;   \
    return true;                           \
  }

#define ACCEPT_TOKEN(symbol_value)       \
  {                                      \
    lexer->result_symbol = symbol_value; \
    return true;                         \
  }

#define LEX_ERROR()                                        \
  if (error_mode) {                                        \
    if (state == ts_lex_state_error)                       \
      lexer->advance(lexer, state, TSTransitionTypeError); \
    GO_TO_STATE(ts_lex_state_error);                       \
  } else {                                                 \
    return false;                                          \
  }

/*
 *  Parse Table Macros
 */

enum {
  FRAGILE = 1,
  CAN_HIDE_SPLIT = 2,
};

#define ERROR()                        \
  {                                    \
    { .type = TSParseActionTypeError } \
  }

#define SHIFT(to_state_value, flags)                   \
  {                                                    \
    {                                                  \
      .type = TSParseActionTypeShift,                  \
      .can_hide_split = (flags & CAN_HIDE_SPLIT) != 0, \
      .data = {.to_state = to_state_value }            \
    }                                                  \
  }

#define RECOVER(to_state_value)                                             \
  {                                                                         \
    .type = TSParseActionTypeRecover, .data = {.to_state = to_state_value } \
  }

#define SHIFT_EXTRA()                                 \
  {                                                   \
    { .type = TSParseActionTypeShift, .extra = true } \
  }

#define REDUCE_EXTRA(symbol_val)                        \
  {                                                     \
    {                                                   \
      .type = TSParseActionTypeReduce, .extra = true,   \
      .data = {.symbol = symbol_val, .child_count = 1 } \
    }                                                   \
  }

#define REDUCE(symbol_val, child_count_val, flags)                        \
  {                                                                       \
    {                                                                     \
      .type = TSParseActionTypeReduce, .fragile = (flags & FRAGILE) != 0, \
      .can_hide_split = (flags & CAN_HIDE_SPLIT) != 0,                    \
      .data = {.symbol = symbol_val, .child_count = child_count_val }     \
    }                                                                     \
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
    .recovery_actions = ts_recovery_actions,               \
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
