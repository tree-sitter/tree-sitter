#ifndef TREE_SITTER_PARSER_H_
#define TREE_SITTER_PARSER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "tree_sitter/runtime.h"

typedef struct TSTree TSTree;

#define ts_lex_state_error 0

typedef struct TSLexer {
  TSInput input;
  int debug;
  const char *chunk;
  size_t chunk_start;
  size_t chunk_size;
  size_t position_in_chunk;
  size_t token_end_position;
  size_t token_start_position;
  int reached_end;

  TSTree *(*accept_fn)(struct TSLexer *, TSSymbol, int);
  int (*advance_fn)(struct TSLexer *);
} TSLexer;

static inline size_t ts_lexer_position(const TSLexer *lexer) {
  return lexer->chunk_start + lexer->position_in_chunk;
}

static inline char ts_lexer_lookahead_char(const TSLexer *lexer) {
  return lexer->chunk[lexer->position_in_chunk];
}

static inline void ts_lexer_start_token(TSLexer *lexer) {
  lexer->token_start_position = ts_lexer_position(lexer);
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

#define SYMBOL_NAMES static const char *ts_symbol_names[]

#define HIDDEN_SYMBOLS static const int ts_hidden_symbol_flags[SYMBOL_COUNT]

#define LEX_STATES static TSStateId ts_lex_states[STATE_COUNT]

#define PARSE_TABLE \
  static const TSParseAction ts_parse_actions[STATE_COUNT][SYMBOL_COUNT]

#define LEX_FN() static TSTree *ts_lex(TSLexer *lexer, TSStateId lex_state)

#define DEBUG_LEX(...)                 \
  if (lexer->debug) {                  \
    fprintf(stderr, "\n" __VA_ARGS__); \
  }

#define START_LEXER()                         \
  DEBUG_LEX("LEX %d", lex_state);             \
  char lookahead;                             \
  next_state:                                 \
  lookahead = ts_lexer_lookahead_char(lexer); \
  DEBUG_LEX("CHAR '%c'", lookahead);

#define START_TOKEN() ts_lexer_start_token(lexer);

#define ADVANCE(state_index)              \
  {                                       \
    DEBUG_LEX("ADVANCE %d", state_index); \
    if (!ts_lexer_advance(lexer))         \
      ACCEPT_TOKEN(ts_builtin_sym_end);   \
    lex_state = state_index;              \
    goto next_state;                      \
  }

#define ACCEPT_TOKEN(symbol)                                               \
  {                                                                        \
    DEBUG_LEX("TOKEN %s", ts_symbol_names[symbol]);                        \
    return ts_lexer_accept(lexer, symbol, ts_hidden_symbol_flags[symbol]); \
  }

#define LEX_ERROR()     \
  {                     \
    DEBUG_LEX("ERROR"); \
    return NULL;        \
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

#define EXPORT_LANGUAGE(language_name)                      \
  static TSLanguage language = {                            \
    .symbol_count = SYMBOL_COUNT,                           \
    .hidden_symbol_flags = ts_hidden_symbol_flags,          \
    .parse_table = (const TSParseAction *)ts_parse_actions, \
    .lex_states = ts_lex_states,                            \
    .symbol_names = ts_symbol_names,                        \
    .lex_fn = ts_lex,                                       \
  };                                                        \
                                                            \
  const TSLanguage *language_name() { return &language; }

#ifdef __cplusplus
}
#endif

#endif  // TREE_SITTER_PARSER_H_
