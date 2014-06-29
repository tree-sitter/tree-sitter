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
{ .type = ts_parse_action_type_shift, .data = { .to_state = to_state_value } }

#define SHIFT_EXTRA() \
{ .type = ts_parse_action_type_shift_extra }

#define REDUCE(symbol_val, child_count_val) \
{ .type = ts_parse_action_type_reduce, .data = { .symbol = symbol_val, .child_count = child_count_val } }

#define ACCEPT_INPUT() \
{ .type = ts_parse_action_type_accept }

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
} ts_lr_parser;

ts_lr_parser * ts_lr_parser_make(size_t symbol_count,
                                 const TSParseAction *parse_table,
                                 const TSStateId *lex_states,
                                 TSTree * (* lex_fn)(TSLexer *, TSStateId),
                                 const int *hidden_symbol_flags);
void ts_lr_parser_free(void *data);
void ts_lr_parser_initialize(ts_lr_parser *parser, TSInput input, TSInputEdit *edit);
TSTree * ts_lr_parser_parse(ts_lr_parser *parser, const char **symbol_names);

#ifdef __cplusplus
}
#endif

#endif
