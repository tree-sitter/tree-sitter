#include "tree_sitter/parser/state_machine.h"
#include "runtime/tree.h"

/*
 *  Private
 */

static const TSParseAction * actions_for_state(TSStateMachine *machine, TSStateId state) {
    return machine->config.parse_table + (state * machine->config.symbol_count);
}

void shift(TSStateMachine *machine, TSStateId parse_state) {
    if (machine->lookahead->is_extra)
        parse_state = ts_stack_top_state(&machine->stack);
    ts_stack_push(&machine->stack, parse_state, machine->lookahead);
    machine->lookahead = machine->next_lookahead;
    machine->next_lookahead = NULL;
}

void shift_extra(TSStateMachine *machine) {
    machine->lookahead->is_extra = 1;
    shift(machine, 0);
}

void reduce(TSStateMachine *machine, TSSymbol symbol, size_t child_count) {
    machine->next_lookahead = machine->lookahead;
    machine->lookahead = ts_stack_reduce(
        &machine->stack,
        symbol,
        child_count,
        machine->config.hidden_symbol_flags, 1);
}

int reduce_extra(TSStateMachine *machine, TSSymbol symbol) {
    TSTree *top_node = ts_stack_top_node(&machine->stack);
    if (top_node->symbol == symbol && !top_node->is_extra) {
        reduce(machine, symbol, 1);
        machine->lookahead->is_extra = 1;
        return 1;
    } else {
        return 0;
    }
}

static size_t breakdown_stack(TSStateMachine *machine, TSInputEdit *edit) {
    if (!edit) return 0;

    TSStack *stack = &machine->stack;
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
            TSStateId next_state = actions_for_state(machine, state)[ts_tree_symbol(child)].data.to_state;
            ts_stack_push(stack, next_state, child);
            ts_tree_retain(child);
            position += ts_tree_total_size(child);
        }

        ts_tree_release(node);
    }

    return position;
}

TSSymbol * expected_symbols(TSStateMachine *machine, size_t *count) {
    *count = 0;
    const TSParseAction *actions = actions_for_state(machine, ts_stack_top_state(&machine->stack));
    for (size_t i = 0; i < machine->config.symbol_count; i++)
        if (actions[i].type != TSParseActionTypeError)
            ++(*count);

    size_t n = 0;
    TSSymbol *result = malloc(*count * sizeof(*result));
    for (TSSymbol i = 0; i < machine->config.symbol_count; i++)
        if (actions[i].type != TSParseActionTypeError)
            result[n++] = i;

    return result;
}

int handle_error(TSStateMachine *machine) {
    size_t count = 0;
    const TSSymbol *inputs = expected_symbols(machine, &count);
    TSTree *error = ts_tree_make_error(ts_lexer_lookahead_char(&machine->lexer),
                                        count,
                                        inputs,
                                        0,
                                        0);

    for (;;) {
        ts_tree_release(machine->lookahead);
        size_t position = ts_lexer_position(&machine->lexer);
        machine->lookahead = machine->config.lex_fn(&machine->lexer, ts_lex_state_error);

        int at_end = 0;
        if (ts_lexer_position(&machine->lexer) == position)
            at_end = !ts_lexer_advance(&machine->lexer);

        if (at_end || ts_tree_symbol(machine->lookahead) == ts_builtin_sym_end) {
            ts_stack_push(&machine->stack, 0, error);
            return 0;
        }

        /*
         *  Unwind the stack, looking for a state in which this token
         *  may appear after an error.
         */
        for (size_t j = 0; j < machine->stack.size; j++) {
            size_t i = machine->stack.size - 1 - j;
            TSStateId stack_state = machine->stack.entries[i].state;
            TSParseAction action_on_error = actions_for_state(machine, stack_state)[ts_builtin_sym_error];
            if (action_on_error.type == TSParseActionTypeShift) {
                TSStateId state_after_error = action_on_error.data.to_state;
                if (actions_for_state(machine, state_after_error)[ts_tree_symbol(machine->lookahead)].type != TSParseActionTypeError) {
                    ts_stack_shrink(&machine->stack, i + 1);
                    ts_stack_push(&machine->stack, state_after_error, error);
                    return 1;
                }
            }
        }
    }
}

TSTree * get_tree_root(TSStateMachine *machine) {
    TSStack *stack = &machine->stack;
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
        TSStateId next_state = actions_for_state(machine, state)[ts_tree_symbol(child)].data.to_state;
        ts_stack_push(stack, next_state, child);
    }

    TSTree *new_node = ts_stack_reduce(stack,
                                        top_node->symbol,
                                        stack->size,
                                        machine->config.hidden_symbol_flags,
                                        0);
    ts_tree_release(top_node);
    return new_node;
}

TSParseAction get_next_action(TSStateMachine *machine) {
    TSStateId state = ts_stack_top_state(&machine->stack);
    if (!machine->lookahead)
        machine->lookahead = machine->config.lex_fn(&machine->lexer, machine->config.lex_states[state]);
    return actions_for_state(machine, state)[ts_tree_symbol(machine->lookahead)];
}

/*
 *  Public API
 */

TSStateMachine * ts_state_machine_make(size_t symbol_count,
                                 const TSParseAction *parse_table,
                                 const TSStateId *lex_states,
                                 TSTree * (* lex_fn)(TSLexer *, TSStateId),
                                 const int *hidden_symbol_flags) {
    TSStateMachine *result = malloc(sizeof(TSStateMachine));
    *result = (TSStateMachine) {
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

void ts_state_machine_free(void *data) {
    TSStateMachine *machine = (TSStateMachine *)data;
    if (machine->lookahead) ts_tree_release(machine->lookahead);
    if (machine->next_lookahead) ts_tree_release(machine->next_lookahead);
    ts_stack_delete(&machine->stack);
    free(machine);
}

void ts_state_machine_initialize(TSStateMachine *machine, TSInput input, TSInputEdit *edit) {
    if (!edit) ts_stack_shrink(&machine->stack, 0);
    machine->lookahead = NULL;
    machine->next_lookahead = NULL;

    size_t position = breakdown_stack(machine, edit);
    input.seek_fn(input.data, position);

    machine->lexer = ts_lexer_make();
    machine->lexer.input = input;
    ts_lexer_advance(&machine->lexer);
}

// #define TS_DEBUG_PARSE

#ifdef TS_DEBUG_PARSE
#include <stdio.h>
#define DEBUG_PARSE(...) fprintf(stderr, "\n" __VA_ARGS__)
#else
#define DEBUG_PARSE(...)
#endif

TSTree * ts_state_machine_parse(TSStateMachine *machine, const char **symbol_names) {
    TSParseAction action = get_next_action(machine);
    DEBUG_PARSE("LOOKAHEAD %s", symbol_names[ts_tree_symbol(machine->lookahead)]);
    switch (action.type) {
        case TSParseActionTypeShift:
            DEBUG_PARSE("SHIFT %d", action.data.to_state);
            shift(machine, action.data.to_state);
            return NULL;
        case TSParseActionTypeShiftExtra:
            DEBUG_PARSE("SHIFT EXTRA");
            shift_extra(machine);
            return NULL;
        case TSParseActionTypeReduce:
            DEBUG_PARSE("REDUCE %s %d", symbol_names[action.data.symbol], action.data.child_count);
            reduce(machine, action.data.symbol, action.data.child_count);
            return NULL;
        case TSParseActionTypeReduceExtra:
            if (!reduce_extra(machine, action.data.symbol))
                goto error;
            DEBUG_PARSE("REDUCE EXTRA");
            return NULL;
        case TSParseActionTypeAccept:
            DEBUG_PARSE("ACCEPT");
            return get_tree_root(machine);
        case TSParseActionTypeError:
            goto error;
        default:
            return NULL;
    }
error:
    DEBUG_PARSE("ERROR");
    if (handle_error(machine))
        return NULL;
    else
        return get_tree_root(machine);
}
