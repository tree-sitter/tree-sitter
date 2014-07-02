#ifndef TREE_SITTER_PARSER_LR_PARSER_H_
#define TREE_SITTER_PARSER_LR_PARSER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "tree_sitter/parser/stack.h"
#include "tree_sitter/parser/lexer.h"

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

typedef struct {
    TSLexer lexer;
    TSStack stack;
    TSTree *lookahead;
    TSTree *next_lookahead;
    struct {
        size_t symbol_count;
        const int *hidden_symbol_flags;
        const TSParseAction *parse_table;
        const TSStateId *lex_states;
        TSTree * (* lex_fn)(TSLexer *, TSStateId);
    } config;
} TSStateMachine;

TSStateMachine * ts_state_machine_make(
    size_t symbol_count,
    const TSParseAction *parse_table,
    const TSStateId *lex_states,
    TSTree * (* lex_fn)(TSLexer *, TSStateId),
    const int *hidden_symbol_flags);
void ts_state_machine_free(void *data);
void ts_state_machine_initialize(TSStateMachine *, TSInput, TSInputEdit *);
TSTree * ts_state_machine_parse(TSStateMachine *, const char **symbol_names);

#ifdef __cplusplus
}
#endif

#endif
