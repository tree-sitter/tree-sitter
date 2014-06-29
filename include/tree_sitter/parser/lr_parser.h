#ifndef TREE_SITTER_PARSER_LR_PARSER_H_
#define TREE_SITTER_PARSER_LR_PARSER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "tree_sitter/parser/stack.h"
#include "tree_sitter/parser/lexer.h"

typedef enum {
    ts_parse_action_type_error,
    ts_parse_action_type_shift,
    ts_parse_action_type_shift_extra,
    ts_parse_action_type_reduce,
    ts_parse_action_type_accept,
} ts_parse_action_type;

typedef struct {
    ts_parse_action_type type;
    union {
        TSStateId to_state;
        struct {
            ts_symbol symbol;
            unsigned short child_count;
        };
    } data;
} ts_parse_action;

#define SHIFT(to_state_value) \
{ .type = ts_parse_action_type_shift, .data = { .to_state = to_state_value } }

#define SHIFT_EXTRA() \
{ .type = ts_parse_action_type_shift_extra }

#define REDUCE(symbol_val, child_count_val) \
{ .type = ts_parse_action_type_reduce, .data = { .symbol = symbol_val, .child_count = child_count_val } }

#define ACCEPT_INPUT() \
{ .type = ts_parse_action_type_accept }

typedef struct {
    ts_lexer lexer;
    ts_stack stack;
    TSTree *lookahead;
    TSTree *next_lookahead;
    struct {
        size_t symbol_count;
        const int *hidden_symbol_flags;
        const ts_parse_action *parse_table;
        const TSStateId *lex_states;
        TSTree * (* lex_fn)(ts_lexer *, TSStateId);
    } config;
} ts_lr_parser;

ts_lr_parser * ts_lr_parser_make(size_t symbol_count,
                                 const ts_parse_action *parse_table,
                                 const TSStateId *lex_states,
                                 TSTree * (* lex_fn)(ts_lexer *, TSStateId),
                                 const int *hidden_symbol_flags);
void ts_lr_parser_free(void *data);
void ts_lr_parser_initialize(ts_lr_parser *parser, ts_input input, ts_input_edit *edit);
TSTree * ts_lr_parser_parse(ts_lr_parser *parser, const char **symbol_names);

#ifdef __cplusplus
}
#endif

#endif
