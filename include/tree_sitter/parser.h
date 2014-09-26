#ifndef TREE_SITTER_PARSER_H_
#define TREE_SITTER_PARSER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>
#include "tree_sitter/runtime.h"

typedef struct TSTree TSTree;

#define ts_lex_state_error 0

typedef struct TSLexer {
  TSInput input;
  int debug;

  const char *chunk;
  size_t chunk_start;
  size_t chunk_size;

  TSLength current_position;
  TSLength token_end_position;
  TSLength token_start_position;

  size_t lookahead_size;
  int32_t lookahead;

  TSTree *(*accept_fn)(struct TSLexer *, TSSymbol, int);
  int (*advance_fn)(struct TSLexer *);
} TSLexer;

static inline int32_t ts_lexer_lookahead_char(const TSLexer *lexer) {
  return lexer->lookahead;
}

static inline void ts_lexer_start_token(TSLexer *lexer) {
  lexer->token_start_position = lexer->current_position;
}

static inline int ts_lexer_advance(TSLexer *lexer) {
  return lexer->advance_fn(lexer);
}

static inline TSTree *ts_lexer_accept(TSLexer *lexer, TSSymbol symbol,
                                      int is_hidden) {
  return lexer->accept_fn(lexer, symbol, is_hidden);
}

typedef unsigned short TSStateId;

typedef enum {
  TSParseActionTypeError,
  TSParseActionTypeShift,
  TSParseActionTypeShiftExtra,
  TSParseActionTypeReduce,
  TSParseActionTypeReduceExtra,
  TSParseActionTypeAccept,
} TSParseActionType;

typedef struct {
  TSParseActionType type;
  union {
    TSStateId to_state;
    struct {
      TSSymbol symbol;
      unsigned short child_count;
    };
  } data;
} TSParseAction;

struct TSLanguage {
  size_t symbol_count;
  const char **symbol_names;
  const int *hidden_symbol_flags;
  const TSParseAction *parse_table;
  const TSStateId *lex_states;
  TSTree *(*lex_fn)(TSLexer *, TSStateId);
};

#define DEBUG_LEX(...)                   \
  if (lexer->debug) {                    \
    fprintf(stderr, "LEX " __VA_ARGS__); \
    fprintf(stderr, "\n");               \
  }

#define START_LEXER()                         \
  DEBUG_LEX("START %d", lex_state);           \
  int32_t lookahead;                             \
  next_state:                                 \
  lookahead = ts_lexer_lookahead_char(lexer); \
  DEBUG_LEX("CHAR '%c'", lookahead);

#define START_TOKEN() ts_lexer_start_token(lexer);

#define ADVANCE(state_index)                                \
  {                                                         \
    DEBUG_LEX("ADVANCE %d", state_index);                   \
    ts_lexer_advance(lexer);                                \
    lex_state = state_index;                                \
    goto next_state;                                        \
  }

#define ACCEPT_TOKEN(symbol)                                               \
  {                                                                        \
    DEBUG_LEX("TOKEN %s", ts_symbol_names[symbol]);                        \
    return ts_lexer_accept(lexer, symbol, ts_hidden_symbol_flags[symbol]); \
  }

#define LEX_ERROR()                                         \
  {                                                         \
    DEBUG_LEX("ERROR");                                     \
    return ts_lexer_accept(lexer, ts_builtin_sym_error, 0); \
  }

#define SHIFT(to_state_value)                                              \
  {                                                                        \
    .type = TSParseActionTypeShift, .data = { .to_state = to_state_value } \
  }

#define SHIFT_EXTRA() \
  { .type = TSParseActionTypeShiftExtra }

#define REDUCE_EXTRA(symbol_val)                                           \
  {                                                                        \
    .type = TSParseActionTypeReduceExtra, .data = { .symbol = symbol_val } \
  }

#define REDUCE(symbol_val, child_count_val)                          \
  {                                                                  \
    .type = TSParseActionTypeReduce,                                 \
    .data = { .symbol = symbol_val, .child_count = child_count_val } \
  }

#define ACCEPT_INPUT() \
  { .type = TSParseActionTypeAccept }

#define EXPORT_LANGUAGE(language_name)                                          \
  static TSLanguage language = { .symbol_count = SYMBOL_COUNT,                  \
                                 .hidden_symbol_flags = ts_hidden_symbol_flags, \
                                 .parse_table =                                 \
                                     (const TSParseAction *)ts_parse_actions,   \
                                 .lex_states = ts_lex_states,                   \
                                 .symbol_names = ts_symbol_names,               \
                                 .lex_fn = ts_lex, };                           \
                                                                                \
  const TSLanguage *language_name() { return &language; }

#ifdef __cplusplus
}
#endif

#endif  // TREE_SITTER_PARSER_H_
