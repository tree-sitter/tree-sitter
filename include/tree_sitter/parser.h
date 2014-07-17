#ifndef TREE_SITTER_PARSER_H_
#define TREE_SITTER_PARSER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "tree_sitter/runtime.h"

#define ts_lex_state_error 0

typedef struct {
    TSInput input;
    int debug;
    const char *chunk;
    size_t chunk_start;
    size_t chunk_size;
    size_t position_in_chunk;
    size_t token_end_position;
    size_t token_start_position;
    int reached_end;
} TSLexer;

TSLexer ts_lexer_make();
int ts_lexer_advance(TSLexer *lexer);
TSTree * ts_lexer_build_node(TSLexer *lexer, TSSymbol symbol, int is_hidden);

static inline size_t ts_lexer_position(const TSLexer *lexer) {
    return lexer->chunk_start + lexer->position_in_chunk;
}

static inline char ts_lexer_lookahead_char(const TSLexer *lexer) {
    return lexer->chunk[lexer->position_in_chunk];
}

static inline void ts_lexer_start_token(TSLexer *lexer) {
    lexer->token_start_position = ts_lexer_position(lexer);
}

typedef unsigned short TSStateId;

typedef struct {
    size_t size;
    struct {
        TSTree *node;
        TSStateId state;
        int is_extra;
    } *entries;
} TSStack;

TSStack ts_stack_make();
void ts_stack_delete(TSStack *);
TSTree * ts_stack_reduce(TSStack *stack, TSSymbol symbol, size_t immediate_child_count, const int *hidden_symbol_flags, int gather_extras);
void ts_stack_shrink(TSStack *stack, size_t new_size);
void ts_stack_push(TSStack *stack, TSStateId state, TSTree *node);
TSStateId ts_stack_top_state(const TSStack *stack);
TSTree * ts_stack_top_node(const TSStack *stack);
size_t ts_stack_right_position(const TSStack *stack);

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

typedef struct {
    size_t symbol_count;
    const char **symbol_names;
    const int *hidden_symbol_flags;
    const TSParseAction *parse_table;
    const TSStateId *lex_states;
    TSTree * (* lex_fn)(TSParser *, TSStateId);
} TSParserConfig;

struct TSParser {
    TSLexer lexer;
    TSStack stack;
    int debug;
    TSTree *lookahead;
    TSTree *next_lookahead;
    TSParserConfig config;
};

TSParser * ts_parser_make(TSParserConfig);
void ts_parser_free(TSParser *);
TSParserConfig ts_parser_config(TSParser *);
const TSTree * ts_parser_parse(TSParser *parser, TSInput input, TSInputEdit *edit);
void ts_parser_start(TSParser *parser, TSInput input, TSInputEdit *edit);
TSTree * ts_parser_step(TSParser *parser);

#define SYMBOL_NAMES \
static const char *ts_symbol_names[]

#define HIDDEN_SYMBOLS \
static const int ts_hidden_symbol_flags[SYMBOL_COUNT]

#define LEX_STATES \
static TSStateId ts_lex_states[STATE_COUNT]

#define PARSE_TABLE \
static const TSParseAction ts_parse_actions[STATE_COUNT][SYMBOL_COUNT]

#define LEX_FN() \
static TSTree * ts_lex(TSParser *parser, TSStateId lex_state)

#define DEBUG_LEX(...) \
if (parser->lexer.debug) { fprintf(stderr, "\n" __VA_ARGS__); }

#define START_LEXER() \
DEBUG_LEX("LEX %d", lex_state); \
char lookahead; \
next_state: \
lookahead = ts_lexer_lookahead_char(&parser->lexer); \
DEBUG_LEX("CHAR '%c'", lookahead);

#define START_TOKEN() \
ts_lexer_start_token(&parser->lexer);

#define ADVANCE(state_index) \
{ \
    DEBUG_LEX("ADVANCE %d", state_index); \
    if (!ts_lexer_advance(&parser->lexer)) ACCEPT_TOKEN(ts_builtin_sym_end); \
    lex_state = state_index; goto next_state; \
}

#define ACCEPT_TOKEN(symbol) \
{ \
    DEBUG_LEX("TOKEN %s", ts_symbol_names[symbol]); \
    return ts_lexer_build_node(&parser->lexer, symbol, ts_hidden_symbol_flags[symbol]); \
}

#define LEX_ERROR() \
{ \
    DEBUG_LEX("ERROR"); \
    return ts_lexer_build_node(&parser->lexer, ts_builtin_sym_error, 0); \
}

#define LEX_PANIC() \
{ \
    DEBUG_LEX("LEX ERROR: unexpected state %d", lex_state); \
    return NULL; \
}

#define SHIFT(to_state_value) \
{ .type = TSParseActionTypeShift, .data = { .to_state = to_state_value } }

#define SHIFT_EXTRA() \
{ .type = TSParseActionTypeShiftExtra }

#define REDUCE_EXTRA(symbol_val) \
{ .type = TSParseActionTypeReduceExtra, .data = { .symbol = symbol_val } }

#define REDUCE(symbol_val, child_count_val) \
{ .type = TSParseActionTypeReduce, .data = { .symbol = symbol_val, .child_count = child_count_val } }

#define ACCEPT_INPUT() \
{ .type = TSParseActionTypeAccept }

#define EXPORT_PARSER(constructor_name) \
TSParser * constructor_name() { \
    return ts_parser_make((TSParserConfig) { \
        .symbol_count = SYMBOL_COUNT, \
        .hidden_symbol_flags = ts_hidden_symbol_flags, \
        .parse_table = (const TSParseAction *)ts_parse_actions, \
        .lex_states = ts_lex_states, \
        .symbol_names =  ts_symbol_names, \
        .lex_fn = ts_lex, \
    }); \
}

#ifdef __cplusplus
}
#endif

#endif  // TREE_SITTER_PARSER_H_
