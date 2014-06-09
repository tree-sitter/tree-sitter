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
    ts_parse_action_type_reduce,
    ts_parse_action_type_accept,
} ts_parse_action_type;

typedef struct {
    ts_parse_action_type type;
    union {
        ts_state_id to_state;
        struct {
            ts_symbol symbol;
            unsigned short child_count;
        };
    } data;
} ts_parse_action;

#define SHIFT(to_state_value) \
{ .type = ts_parse_action_type_shift, .data = { .to_state = to_state_value } }

#define REDUCE(symbol_val, child_count_val) \
{ .type = ts_parse_action_type_reduce, .data = { .symbol = symbol_val, .child_count = child_count_val } }

#define ACCEPT_INPUT() \
{ .type = ts_parse_action_type_accept }

typedef struct {
    ts_lexer lexer;
    ts_stack stack;
    ts_tree *lookahead;
    ts_tree *next_lookahead;
    struct {
        size_t symbol_count;
        const int *hidden_symbol_flags;
        const int *ubiquitous_symbol_flags;
        const ts_parse_action *parse_table;
        const ts_state_id *lex_states;
        ts_tree * (* lex_fn)(ts_lexer *, ts_state_id);
    } config;
} ts_lr_parser;

ts_lr_parser * ts_lr_parser_make(size_t symbol_count,
                                 const ts_parse_action *parse_table,
                                 const ts_state_id *lex_states,
                                 ts_tree * (* lex_fn)(ts_lexer *, ts_state_id),
                                 const int *hidden_symbol_flags,
                                 const int *ubiquitous_symbol_flags);
void ts_lr_parser_free(void *data);
void ts_lr_parser_initialize(ts_lr_parser *parser, ts_input input, ts_input_edit *edit);
ts_tree * ts_lr_parser_parse(ts_lr_parser *parser, const char **symbol_names);

#ifdef __cplusplus
}
#endif

#endif