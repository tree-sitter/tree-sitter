#ifndef TREE_SITTER_PARSER_H_
#define TREE_SITTER_PARSER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <ctype.h>
#include <stdio.h>
#include "tree_sitter/runtime.h"

//#define TS_DEBUG_PARSE
//#define TS_DEBUG_LEX

#ifdef TS_DEBUG_LEX
#define DEBUG_LEX(...) fprintf(stderr, "\n" __VA_ARGS__)
#else
#define DEBUG_LEX(...)
#endif

#ifdef TS_DEBUG_PARSE
#define DEBUG_PARSE(...) fprintf(stderr, "\n" __VA_ARGS__)
#else
#define DEBUG_PARSE(...)
#endif

#define SYMBOL_NAMES \
static const char *ts_symbol_names[]

#define HIDDEN_SYMBOLS \
static const int hidden_symbol_flags[SYMBOL_COUNT]

#define LEX_STATES \
static state_id ts_lex_states[STATE_COUNT]

#define LEX_FN() \
static ts_tree * ts_lex(ts_lexer *lexer, state_id lex_state)

#define START_LEXER() \
char lookahead; \
next_state: \
lookahead = ts_lexer_lookahead_char(lexer); \
DEBUG_LEX("CHAR '%c'", lookahead);

#define START_TOKEN() \
ts_lexer_start_token(lexer);

#define ADVANCE(state_index) \
{ DEBUG_LEX("ADVANCE %d", state_index); ts_lexer_advance(lexer); lex_state = state_index; goto next_state; }

#define ACCEPT_TOKEN(symbol) \
{ DEBUG_LEX("TOKEN %s", ts_symbol_names[symbol]); return ts_lexer_build_node(lexer, symbol); }

#define LEX_ERROR() \
{ return ts_lexer_build_node(lexer, ts_builtin_sym_error); }

#define LEX_PANIC() \
{ DEBUG_LEX("LEX ERROR: unexpected state %d", lex_state); return NULL; }

#define PARSE_TABLE \
static const ts_parse_action ts_parse_actions[STATE_COUNT][SYMBOL_COUNT]

#define EXPORT_PARSER(constructor_name) \
ts_parser constructor_name() { \
    return (ts_parser) { \
        .parse_fn = ts_parse, \
        .symbol_names = ts_symbol_names, \
        .data = ts_lr_parser_make(SYMBOL_COUNT, (const ts_parse_action *)ts_parse_actions, ts_lex_states, hidden_symbol_flags), \
        .free_fn = NULL \
    }; \
}

#define SHIFT(to_state_value) \
{ .type = ts_parse_action_type_shift, .data = { .to_state = to_state_value } }

#define REDUCE(symbol_val, child_count_val) \
{ .type = ts_parse_action_type_reduce, .data = { .symbol = symbol_val, .child_count = child_count_val } }

#define ACCEPT_INPUT() \
{ .type = ts_parse_action_type_accept }


/*
 *  Stack
 */
typedef int state_id;
typedef struct {
    size_t size;
    struct {
        ts_tree *node;
        state_id state;
    } *entries;
} ts_stack;

ts_stack ts_stack_make();
ts_tree * ts_stack_root(const ts_stack *stack);
ts_tree * ts_stack_reduce(ts_stack *stack, ts_symbol symbol, int immediate_child_count, const int *collapse_flags);
void ts_stack_shrink(ts_stack *stack, size_t new_size);
void ts_stack_push(ts_stack *stack, state_id state, ts_tree *node);
state_id ts_stack_top_state(const ts_stack *stack);
ts_tree * ts_stack_top_node(const ts_stack *stack);
size_t ts_stack_right_position(const ts_stack *stack);


/*
 *  Lexer
 */
typedef struct {
    ts_input input;
    const char *chunk;
    size_t chunk_start;
    size_t chunk_size;
    size_t position_in_chunk;
    size_t token_end_position;
    size_t token_start_position;
} ts_lexer;

static ts_lexer ts_lexer_make() {
    ts_lexer result = {
        .chunk = NULL,
        .chunk_start = 0,
        .chunk_size = 0,
        .position_in_chunk = 0,
        .token_start_position = 0,
        .token_end_position = 0,
    };
    return result;
}

static size_t ts_lexer_position(const ts_lexer *lexer) {
    return lexer->chunk_start + lexer->position_in_chunk;
}

static char ts_lexer_lookahead_char(const ts_lexer *lexer) {
    return lexer->chunk[lexer->position_in_chunk];
}

static void ts_lexer_advance(ts_lexer *lexer) {
    static const char empty_chunk[1] = "";
    if (lexer->position_in_chunk + 1 < lexer->chunk_size) {
        lexer->position_in_chunk++;
    } else {
        lexer->chunk_start += lexer->chunk_size;
        lexer->chunk = lexer->input.read_fn(lexer->input.data, &lexer->chunk_size);
        if (lexer->chunk_size == 0) {
            lexer->chunk = empty_chunk;
            lexer->chunk_size = 1;
        }
        lexer->position_in_chunk = 0;
    }
}

static void ts_lexer_start_token(ts_lexer *lexer) {
    lexer->token_start_position = ts_lexer_position(lexer);
}

static ts_tree * ts_lexer_build_node(ts_lexer *lexer, ts_symbol symbol) {
    size_t current_position = ts_lexer_position(lexer);
    size_t size = current_position - lexer->token_start_position;
    size_t offset = lexer->token_start_position - lexer->token_end_position;
    lexer->token_end_position = current_position;
    return ts_tree_make_leaf(symbol, size, offset);
}

#define ts_lex_state_error -1


/*
 *  Parse Table components
 */
typedef enum {
    ts_parse_action_type_error,
    ts_parse_action_type_shift,
    ts_parse_action_type_reduce,
    ts_parse_action_type_accept,
} ts_parse_action_type;

typedef struct {
    ts_parse_action_type type;
    union {
        state_id to_state;
        struct {
            ts_symbol symbol;
            int child_count;
        };
    } data;
} ts_parse_action;


/*
 *  Forward declarations
 *  The file including this header should use these macros to provide definitions.
 */
LEX_FN();
SYMBOL_NAMES;


/*
 *  Parser
 */
typedef struct {
    ts_lexer lexer;
    ts_stack stack;
    const int *hidden_symbol_flags;
    ts_tree *lookahead;
    ts_tree *next_lookahead;
    const ts_parse_action *parse_table;
    const state_id *lex_states;
    size_t symbol_count;
} ts_lr_parser;

static ts_lr_parser * ts_lr_parser_make(size_t symbol_count, const ts_parse_action *parse_table, const state_id *lex_states, const int *hidden_symbol_flags) {
    ts_lr_parser *result = malloc(sizeof(ts_lr_parser));
    result->lexer = ts_lexer_make();
    result->stack = ts_stack_make();
    result->symbol_count = symbol_count;
    result->parse_table = parse_table;
    result->lex_states = lex_states;
    result->hidden_symbol_flags = hidden_symbol_flags;
    return result;
}

static const ts_parse_action * ts_lr_parser_table_actions(ts_lr_parser *parser, state_id state) {
    return parser->parse_table + (state * parser->symbol_count);
}

static size_t ts_lr_parser_breakdown_stack(ts_lr_parser *parser, ts_input_edit *edit) {
    ts_stack *stack = &parser->stack;
    if (!edit) return 0;

    ts_tree *node;
    size_t position = 0;
    size_t child_count = 0;

    for (;;) {
        node = ts_stack_top_node(stack);
        if (!node) break;

        position = ts_stack_right_position(stack);
        ts_tree **children = ts_tree_immediate_children(node, &child_count);
        if (position <= edit->position && !children) break;

        stack->size--;
        position -= ts_tree_total_size(node);

        for (size_t i = 0; i < child_count && position < edit->position; i++) {
            ts_tree *child = children[i];
            state_id state = ts_stack_top_state(stack);
            state_id next_state = ts_lr_parser_table_actions(parser, state)[ts_tree_symbol(child)].data.to_state;
            ts_stack_push(stack, next_state, child);
            ts_tree_retain(child);
            position += ts_tree_total_size(child);
        }

        ts_tree_release(node);
    }

    return position;
}

static void ts_lr_parser_initialize(ts_lr_parser *parser, ts_input input, ts_input_edit *edit) {
    if (!edit) ts_stack_shrink(&parser->stack, 0);
    parser->lookahead = NULL;
    parser->next_lookahead = NULL;

    size_t position = ts_lr_parser_breakdown_stack(parser, edit);
    input.seek_fn(input.data, position);

    parser->lexer = ts_lexer_make();
    parser->lexer.input = input;
    ts_lexer_advance(&parser->lexer);
}

static void ts_lr_parser_shift(ts_lr_parser *parser, state_id parse_state) {
    ts_stack_push(&parser->stack, parse_state, parser->lookahead);
    parser->lookahead = parser->next_lookahead;
    parser->next_lookahead = NULL;
}

static void ts_lr_parser_reduce(ts_lr_parser *parser, ts_symbol symbol, int child_count) {
    parser->next_lookahead = parser->lookahead;
    parser->lookahead = ts_stack_reduce(&parser->stack, symbol, child_count, parser->hidden_symbol_flags);
}

static ts_symbol * ts_lr_parser_expected_symbols(ts_lr_parser *parser, size_t *count) {
    *count = 0;
    const ts_parse_action *actions = ts_lr_parser_table_actions(parser, ts_stack_top_state(&parser->stack));
    for (size_t i = 0; i < parser->symbol_count; i++)
        if (actions[i].type != ts_parse_action_type_error)
            ++(*count);

    size_t n = 0;
    ts_symbol *result = malloc(*count * sizeof(*result));
    for (size_t i = 0; i < parser->symbol_count; i++)
        if (actions[i].type != ts_parse_action_type_error)
            result[n++] = i;

    return result;
}

static int ts_lr_parser_handle_error(ts_lr_parser *parser) {
    size_t count = 0;
    ts_symbol *expected_symbols = ts_lr_parser_expected_symbols(parser, &count);
    ts_tree *error = ts_tree_make_error(ts_lexer_lookahead_char(&parser->lexer), count, expected_symbols, 0, 0);

    for (;;) {
        ts_tree_release(parser->lookahead);
        size_t position = ts_lexer_position(&parser->lexer);
        parser->lookahead = ts_lex(&parser->lexer, ts_lex_state_error);
        if (ts_lexer_position(&parser->lexer) == position)
            ts_lexer_advance(&parser->lexer);

        if (ts_tree_symbol(parser->lookahead) == ts_builtin_sym_end) {
            parser->stack.entries[0].node = error;
            return 0;
        }

        /*
         *  Unwind the stack, looking for a state in which this token
         *  may appear after an error.
         */
        for (long i = parser->stack.size - 1; i >= 0; i--) {
            state_id stack_state = parser->stack.entries[i].state;
            ts_parse_action action_on_error = ts_lr_parser_table_actions(parser, stack_state)[ts_builtin_sym_error];
            if (action_on_error.type == ts_parse_action_type_shift) {
                state_id state_after_error = action_on_error.data.to_state;
                if (ts_lr_parser_table_actions(parser, state_after_error)[ts_tree_symbol(parser->lookahead)].type != ts_parse_action_type_error) {
                    ts_stack_shrink(&parser->stack, i + 1);
                    ts_stack_push(&parser->stack, state_after_error, error);
                    return 1;
                }
            }
        }
    }
}

static const ts_tree * ts_parse(void *data, ts_input input, ts_input_edit *edit) {
    int done = 0;
    ts_lr_parser *parser = (ts_lr_parser *)data;
    ts_lr_parser_initialize(parser, input, edit);
    while (!done) {
        state_id state = ts_stack_top_state(&parser->stack);
        if (!parser->lookahead)
            parser->lookahead = ts_lex(&parser->lexer, parser->lex_states[state]);
        ts_parse_action action = ts_lr_parser_table_actions(parser, state)[ts_tree_symbol(parser->lookahead)];
        DEBUG_PARSE("LOOKAHEAD %s", ts_symbol_names[ts_tree_symbol(parser->lookahead)]);
        switch (action.type) {
            case ts_parse_action_type_shift:
                DEBUG_PARSE("SHIFT %d", action.data.to_state);
                ts_lr_parser_shift(parser, action.data.to_state);
                break;
            case ts_parse_action_type_reduce:
                DEBUG_PARSE("REDUCE %s %d", ts_symbol_names[action.data.symbol], action.data.child_count);
                ts_lr_parser_reduce(parser, action.data.symbol, action.data.child_count);
                break;
            case ts_parse_action_type_accept:
                DEBUG_PARSE("ACCEPT");
                done = 1;
                break;
            case ts_parse_action_type_error:
                DEBUG_PARSE("ERROR");
                done = !ts_lr_parser_handle_error(parser);
                break;
        }
    }
    return ts_stack_root(&parser->stack);
}

#ifdef __cplusplus
}
#endif

#endif  // TREE_SITTER_PARSER_H_
