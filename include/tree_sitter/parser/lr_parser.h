#ifndef TREE_SITTER_PARSER_LR_PARSER_H_
#define TREE_SITTER_PARSER_LR_PARSER_H_

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

static ts_lr_parser *
ts_lr_parser_make(size_t symbol_count,
                  const ts_parse_action *parse_table,
                  const ts_state_id *lex_states,
                  ts_tree * (* lex_fn)(ts_lexer *, ts_state_id),
                  const int *hidden_symbol_flags,
                  const int *ubiquitous_symbol_flags) {
    ts_lr_parser *result = malloc(sizeof(ts_lr_parser));
    *result = (ts_lr_parser) {
        .lexer = ts_lexer_make(),
        .stack = ts_stack_make(),
        .config = {
            .symbol_count = symbol_count,
            .parse_table = parse_table,
            .lex_states = lex_states,
            .lex_fn = lex_fn,
            .hidden_symbol_flags = hidden_symbol_flags,
            .ubiquitous_symbol_flags = ubiquitous_symbol_flags,
        },
    };
    return result;
}

static const ts_parse_action *
ts_lr_parser_table_actions(ts_lr_parser *parser, ts_state_id state) {
    return parser->config.parse_table + (state * parser->config.symbol_count);
}

static size_t
ts_lr_parser_breakdown_stack(ts_lr_parser *parser, ts_input_edit *edit) {
    if (!edit) return 0;

    ts_stack *stack = &parser->stack;
    size_t position = 0;

    for (;;) {
        ts_tree *node = ts_stack_top_node(stack);
        if (!node) break;

        position = ts_stack_right_position(stack);
        size_t child_count;
        ts_tree **children = ts_tree_immediate_children(node, &child_count);
        if (position <= edit->position && !children) break;

        stack->size--;
        position -= ts_tree_total_size(node);

        for (size_t i = 0; i < child_count && position < edit->position; i++) {
            ts_tree *child = children[i];
            ts_state_id state = ts_stack_top_state(stack);
            ts_state_id next_state = ts_lr_parser_table_actions(parser, state)[ts_tree_symbol(child)].data.to_state;
            ts_stack_push(stack, next_state, child);
            ts_tree_retain(child);
            position += ts_tree_total_size(child);
        }

        ts_tree_release(node);
    }

    return position;
}

static void
ts_lr_parser_initialize(ts_lr_parser *parser, ts_input input, ts_input_edit *edit) {
    if (!edit) ts_stack_shrink(&parser->stack, 0);
    parser->lookahead = NULL;
    parser->next_lookahead = NULL;

    size_t position = ts_lr_parser_breakdown_stack(parser, edit);
    input.seek_fn(input.data, position);

    parser->lexer = ts_lexer_make();
    parser->lexer.input = input;
    ts_lexer_advance(&parser->lexer);
}

static void
ts_lr_parser_shift(ts_lr_parser *parser, ts_state_id parse_state) {
    ts_stack_push(&parser->stack, parse_state, parser->lookahead);
    parser->lookahead = parser->next_lookahead;
    parser->next_lookahead = NULL;
}

static void
ts_lr_parser_reduce(ts_lr_parser *parser, ts_symbol symbol, size_t child_count) {
    parser->next_lookahead = parser->lookahead;
    parser->lookahead = ts_stack_reduce(&parser->stack,
                                        symbol,
                                        child_count,
                                        parser->config.hidden_symbol_flags,
                                        parser->config.ubiquitous_symbol_flags);
}

static ts_symbol *
ts_lr_parser_expected_symbols(ts_lr_parser *parser, size_t *count) {
    *count = 0;
    const ts_parse_action *actions = ts_lr_parser_table_actions(parser, ts_stack_top_state(&parser->stack));
    for (size_t i = 0; i < parser->config.symbol_count; i++)
        if (actions[i].type != ts_parse_action_type_error)
            ++(*count);

    size_t n = 0;
    ts_symbol *result = malloc(*count * sizeof(*result));
    for (ts_symbol i = 0; i < parser->config.symbol_count; i++)
        if (actions[i].type != ts_parse_action_type_error)
            result[n++] = i;

    return result;
}

static int
ts_lr_parser_handle_error(ts_lr_parser *parser) {
    size_t count = 0;
    ts_symbol *expected_symbols = ts_lr_parser_expected_symbols(parser, &count);
    ts_tree *error = ts_tree_make_error(ts_lexer_lookahead_char(&parser->lexer), count, expected_symbols, 0, 0);

    for (;;) {
        ts_tree_release(parser->lookahead);
        size_t position = ts_lexer_position(&parser->lexer);
        parser->lookahead = parser->config.lex_fn(&parser->lexer, ts_lex_state_error);

        int at_end = 0;
        if (ts_lexer_position(&parser->lexer) == position)
            at_end = !ts_lexer_advance(&parser->lexer);

        if (at_end || ts_tree_symbol(parser->lookahead) == ts_builtin_sym_end) {
            ts_stack_push(&parser->stack, 0, error);
            return 0;
        }

        /*
         *  Unwind the stack, looking for a state in which this token
         *  may appear after an error.
         */
        for (size_t j = 0; j < parser->stack.size; j++) {
            size_t i = parser->stack.size - 1 - j;
            ts_state_id stack_state = parser->stack.entries[i].state;
            ts_parse_action action_on_error = ts_lr_parser_table_actions(parser, stack_state)[ts_builtin_sym_error];
            if (action_on_error.type == ts_parse_action_type_shift) {
                ts_state_id state_after_error = action_on_error.data.to_state;
                if (ts_lr_parser_table_actions(parser, state_after_error)[ts_tree_symbol(parser->lookahead)].type != ts_parse_action_type_error) {
                    ts_stack_shrink(&parser->stack, i + 1);
                    ts_stack_push(&parser->stack, state_after_error, error);
                    return 1;
                }
            }
        }
    }
}

static ts_tree *
ts_lr_parser_tree_root(ts_lr_parser *parser) {
    ts_stack *stack = &parser->stack;
    ts_tree *top_node = ts_stack_top_node(stack);
    if (stack->size <= 1)
        return top_node;
    if (ts_tree_symbol(top_node) == ts_builtin_sym_error)
        return top_node;

    size_t immediate_child_count;
    ts_tree **immedate_children = ts_tree_immediate_children(top_node, &immediate_child_count);

    stack->size--;
    for (size_t i = 0; i < immediate_child_count; i++) {
        ts_tree *child = immedate_children[i];
        ts_tree_retain(child);
        ts_state_id state = ts_stack_top_state(stack);
        ts_state_id next_state = ts_lr_parser_table_actions(parser, state)[ts_tree_symbol(child)].data.to_state;
        ts_stack_push(stack, next_state, child);
    }

    ts_tree *new_node = ts_stack_reduce(stack,
                                        ts_tree_symbol(top_node),
                                        stack->size,
                                        parser->config.hidden_symbol_flags,
                                        NULL);
    ts_tree_release(top_node);
    return new_node;
}

static ts_parse_action
ts_lr_parser_next_action(ts_lr_parser *parser) {
    ts_state_id state = ts_stack_top_state(&parser->stack);
    if (!parser->lookahead)
        parser->lookahead = parser->config.lex_fn(&parser->lexer, parser->config.lex_states[state]);
    return ts_lr_parser_table_actions(parser, state)[ts_tree_symbol(parser->lookahead)];
}

#endif