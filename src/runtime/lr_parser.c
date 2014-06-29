#include "tree_sitter/parser/lr_parser.h"
#include "runtime/tree.h"

/*
 *  Private
 */

static const ts_parse_action * actions_for_state(ts_lr_parser *parser, TSStateId state) {
    return parser->config.parse_table + (state * parser->config.symbol_count);
}

void shift(ts_lr_parser *parser, TSStateId parse_state, int is_extra) {
    parser->lookahead->is_extra = is_extra;
    ts_stack_push(&parser->stack, parse_state, parser->lookahead);
    parser->lookahead = parser->next_lookahead;
    parser->next_lookahead = NULL;
}

void reduce(ts_lr_parser *parser, TSSymbol symbol, size_t child_count) {
    parser->next_lookahead = parser->lookahead;
    parser->lookahead = ts_stack_reduce(&parser->stack,
                                        symbol,
                                        child_count,
                                        parser->config.hidden_symbol_flags,
                                        1);
}

static size_t breakdown_stack(ts_lr_parser *parser, ts_input_edit *edit) {
    if (!edit) return 0;

    ts_stack *stack = &parser->stack;
    size_t position = 0;

    for (;;) {
        TSTree *node = ts_stack_top_node(stack);
        if (!node) break;

        position = ts_stack_right_position(stack);
        size_t child_count;
        TSTree **children = ts_tree_immediate_children(node, &child_count);
        if (position <= edit->position && !children) break;

        stack->size--;
        position -= ts_tree_total_size(node);

        for (size_t i = 0; i < child_count && position < edit->position; i++) {
            TSTree *child = children[i];
            TSStateId state = ts_stack_top_state(stack);
            TSStateId next_state = actions_for_state(parser, state)[ts_tree_symbol(child)].data.to_state;
            ts_stack_push(stack, next_state, child);
            ts_tree_retain(child);
            position += ts_tree_total_size(child);
        }

        ts_tree_release(node);
    }

    return position;
}

TSSymbol * expected_symbols(ts_lr_parser *parser, size_t *count) {
    *count = 0;
    const ts_parse_action *actions = actions_for_state(parser, ts_stack_top_state(&parser->stack));
    for (size_t i = 0; i < parser->config.symbol_count; i++)
        if (actions[i].type != ts_parse_action_type_error)
            ++(*count);

    size_t n = 0;
    TSSymbol *result = malloc(*count * sizeof(*result));
    for (TSSymbol i = 0; i < parser->config.symbol_count; i++)
        if (actions[i].type != ts_parse_action_type_error)
            result[n++] = i;

    return result;
}

int handle_error(ts_lr_parser *parser) {
    size_t count = 0;
    const TSSymbol *inputs = expected_symbols(parser, &count);
    TSTree *error = ts_tree_make_error(ts_lexer_lookahead_char(&parser->lexer),
                                        count,
                                        inputs,
                                        0,
                                        0);

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
            TSStateId stack_state = parser->stack.entries[i].state;
            ts_parse_action action_on_error = actions_for_state(parser, stack_state)[ts_builtin_sym_error];
            if (action_on_error.type == ts_parse_action_type_shift) {
                TSStateId state_after_error = action_on_error.data.to_state;
                if (actions_for_state(parser, state_after_error)[ts_tree_symbol(parser->lookahead)].type != ts_parse_action_type_error) {
                    ts_stack_shrink(&parser->stack, i + 1);
                    ts_stack_push(&parser->stack, state_after_error, error);
                    return 1;
                }
            }
        }
    }
}

TSTree * get_tree_root(ts_lr_parser *parser) {
    ts_stack *stack = &parser->stack;
    TSTree *top_node = ts_stack_top_node(stack);
    if (stack->size <= 1)
        return top_node;
    if (ts_tree_symbol(top_node) == ts_builtin_sym_error)
        return top_node;

    size_t immediate_child_count;
    TSTree **immedate_children = ts_tree_immediate_children(top_node, &immediate_child_count);

    stack->size--;
    for (size_t i = 0; i < immediate_child_count; i++) {
        TSTree *child = immedate_children[i];
        child->is_extra = 0;
        ts_tree_retain(child);
        TSStateId state = ts_stack_top_state(stack);
        TSStateId next_state = actions_for_state(parser, state)[ts_tree_symbol(child)].data.to_state;
        ts_stack_push(stack, next_state, child);
    }

    TSTree *new_node = ts_stack_reduce(stack,
                                        top_node->symbol,
                                        stack->size,
                                        parser->config.hidden_symbol_flags,
                                        0);
    ts_tree_release(top_node);
    return new_node;
}

ts_parse_action get_next_action(ts_lr_parser *parser) {
    TSStateId state = ts_stack_top_state(&parser->stack);
    if (!parser->lookahead)
        parser->lookahead = parser->config.lex_fn(&parser->lexer, parser->config.lex_states[state]);
    return actions_for_state(parser, state)[ts_tree_symbol(parser->lookahead)];
}

/*
 *  Public API
 */

ts_lr_parser * ts_lr_parser_make(size_t symbol_count,
                                 const ts_parse_action *parse_table,
                                 const TSStateId *lex_states,
                                 TSTree * (* lex_fn)(ts_lexer *, TSStateId),
                                 const int *hidden_symbol_flags) {
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
        },
    };
    return result;
}

void ts_lr_parser_free(void *data) {
    ts_lr_parser *parser = (ts_lr_parser *)data;
    if (parser->lookahead) ts_tree_release(parser->lookahead);
    if (parser->next_lookahead) ts_tree_release(parser->next_lookahead);
    ts_stack_delete(&parser->stack);
    free(parser);
}

void ts_lr_parser_initialize(ts_lr_parser *parser, TSInput input, ts_input_edit *edit) {
    if (!edit) ts_stack_shrink(&parser->stack, 0);
    parser->lookahead = NULL;
    parser->next_lookahead = NULL;

    size_t position = breakdown_stack(parser, edit);
    input.seek_fn(input.data, position);

    parser->lexer = ts_lexer_make();
    parser->lexer.input = input;
    ts_lexer_advance(&parser->lexer);
}

/* #define TS_DEBUG_PARSE */

#ifdef TS_DEBUG_PARSE
#include <stdio.h>
#define DEBUG_PARSE(...) fprintf(stderr, "\n" __VA_ARGS__)
#else
#define DEBUG_PARSE(...)
#endif

TSTree * ts_lr_parser_parse(ts_lr_parser *parser, const char **symbol_names) {
    ts_parse_action action = get_next_action(parser);
    DEBUG_PARSE("LOOKAHEAD %s", symbol_names[ts_tree_symbol(parser->lookahead)]);
    switch (action.type) {
        case ts_parse_action_type_shift:
            DEBUG_PARSE("SHIFT %d", action.data.to_state);
            shift(parser, action.data.to_state, 0);
            return NULL;
        case ts_parse_action_type_shift_extra:
            DEBUG_PARSE("SHIFT EXTRA");
            shift(parser, ts_stack_top_state(&parser->stack), 1);
            return NULL;
        case ts_parse_action_type_reduce:
            DEBUG_PARSE("REDUCE %s %d", symbol_names[action.data.symbol], action.data.child_count);
            reduce(parser, action.data.symbol, action.data.child_count);
            return NULL;
        case ts_parse_action_type_accept:
            DEBUG_PARSE("ACCEPT");
            return get_tree_root(parser);
        case ts_parse_action_type_error:
            DEBUG_PARSE("ERROR");
            if (handle_error(parser))
                return NULL;
            else
                return get_tree_root(parser);
        default:
            return NULL;
    }
}
