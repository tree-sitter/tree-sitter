#ifndef tree_sitter_parser_h
#define tree_sitter_parser_h

#ifdef __cplusplus
extern "C" {
#endif

#include "./runtime.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

//#define TS_DEBUG_PARSE
//#define TS_DEBUG_LEX

#ifdef TS_DEBUG_LEX
#define DEBUG_LEX(...) fprintf(stderr, __VA_ARGS__)
#else
#define DEBUG_LEX(...)
#endif

#ifdef TS_DEBUG_PARSE
#define DEBUG_PARSE(...) fprintf(stderr, __VA_ARGS__)
#else
#define DEBUG_PARSE(...)
#endif

static int INITIAL_STACK_SIZE = 100;
static const char *ts_symbol_names[];

typedef int ts_state;
static const ts_state ts_lex_state_error = -1;

typedef struct {
    ts_state state;
    ts_tree *node;
} ts_stack_entry;

typedef struct {
    ts_input input;
    const char *current_chunk;
    size_t position;
    size_t token_end_position;
    size_t token_start_position;
    ts_tree *lookahead_node;
    ts_tree *prev_lookahead_node;
    ts_state lex_state;
    ts_stack_entry *stack;
    size_t stack_size;
} ts_parser;

static void ts_lex(ts_parser *parser);
static const ts_symbol * ts_recover(ts_state state, ts_state *to_state, size_t *count);

static ts_parser ts_parser_make(ts_input input) {
    ts_parser result = {
        .input = input,
        .token_start_position = 0,
        .token_end_position = 0,
        .position = 0,
        .current_chunk = input.read_fn(input.data),
        .lookahead_node = NULL,
        .prev_lookahead_node = NULL,
        .lex_state = 0,
        .stack = calloc(INITIAL_STACK_SIZE, sizeof(ts_stack_entry)),
        .stack_size = 0,
    };
    return result;
}

static char ts_parser_lookahead_char(const ts_parser *parser) {
    return parser->current_chunk[parser->position];
}

static ts_symbol ts_parser_lookahead_sym(const ts_parser *parser) {
    ts_tree *node = parser->lookahead_node;
    return node ? node->symbol : ts_builtin_sym_error;
}

static ts_state ts_parser_parse_state(const ts_parser *parser) {
    if (parser->stack_size == 0) return 0;
    return parser->stack[parser->stack_size - 1].state;
}

static void ts_parser_push(ts_parser *parser, ts_state state, ts_tree *node) {
    ts_stack_entry *entry = (parser->stack + parser->stack_size);
    entry->state = state;
    entry->node = node;
    parser->stack_size++;
}

static void ts_parser_shift(ts_parser *parser, ts_state parse_state) {
    DEBUG_PARSE("shift: %d \n", parse_state);
    ts_parser_push(parser, parse_state, parser->lookahead_node);
    parser->lookahead_node = parser->prev_lookahead_node;
    parser->prev_lookahead_node = NULL;
}

static void ts_parser_shrink_stack(ts_parser *parser, size_t new_size) {
    for (size_t i = new_size; i < parser->stack_size; i++)
        ts_tree_release(parser->stack[i].node);
    parser->stack_size = new_size;
}

static void ts_parser_reduce(ts_parser *parser, ts_symbol symbol, int immediate_child_count, const int *collapse_flags) {
    size_t new_stack_size = parser->stack_size - immediate_child_count;

    int child_count = 0;
    for (int i = 0; i < immediate_child_count; i++) {
        ts_tree *child = parser->stack[new_stack_size + i].node;
        child_count += collapse_flags[i] ? ts_tree_child_count(child) : 1;
    }

    int child_index = 0;
    size_t size = 0, offset = 0;
    ts_tree **children = malloc(child_count * sizeof(ts_tree *));
    for (int i = 0; i < immediate_child_count; i++) {
        ts_tree *child = parser->stack[new_stack_size + i].node;
        if (i == 0) {
            offset = child->offset;
            size = child->size;
        } else {
            size += child->offset + child->size;
        }

        if (collapse_flags[i]) {
            size_t grandchild_count = ts_tree_child_count(child);
            memcpy(children + child_index, ts_tree_children(child), (grandchild_count * sizeof(ts_tree *)));
            child_index += grandchild_count;
        } else {
            memcpy(children + child_index, &child, sizeof(ts_tree *));
            child_index++;
        }
    }

    parser->prev_lookahead_node = parser->lookahead_node;
    parser->lookahead_node = ts_tree_make_node(symbol, child_count, children, size, offset);
    ts_parser_shrink_stack(parser, new_stack_size);
    DEBUG_PARSE("reduce: %s, state: %u \n", ts_symbol_names[symbol], ts_parser_parse_state(parser));
}

static void ts_parser_advance(ts_parser *parser) {
    if (parser->current_chunk && parser->current_chunk[parser->position]) {
        parser->position++;
    } else {
        parser->current_chunk = parser->input.read_fn(parser->input.data);
        parser->position = 0;
    }
}

static void ts_parser_advance_to_state(ts_parser *parser, ts_state lex_state) {
    DEBUG_LEX("character: '%c' \n", ts_parser_lookahead_char(parser));
    ts_parser_advance(parser);
    parser->lex_state = lex_state;
}

static void ts_parser_set_lookahead_sym(ts_parser *parser, ts_symbol symbol) {
    DEBUG_LEX("token: %s \n", ts_symbol_names[symbol]);
    size_t size = parser->position - parser->token_start_position;
    size_t offset = parser->token_start_position - parser->token_end_position;
    parser->lookahead_node = ts_tree_make_leaf(symbol, size, offset);
    parser->token_end_position = parser->position;
}

static ts_tree * ts_parser_tree(ts_parser *parser) {
    DEBUG_PARSE("accept \n");
    return parser->stack[0].node;
}

static void ts_parser_skip_whitespace(ts_parser *parser) {
    while (isspace(ts_parser_lookahead_char(parser)))
        ts_parser_advance(parser);
    parser->token_start_position = parser->position;
}

static int ts_parser_handle_error(ts_parser *parser, size_t count, const ts_symbol *expected_symbols) {
    ts_tree *error = ts_tree_make_error(ts_parser_lookahead_char(parser), count, expected_symbols, 0, 0);

    while (1) {
        ts_tree_release(parser->lookahead_node);
        parser->lookahead_node = NULL;
        parser->lex_state = ts_lex_state_error;
        ts_lex(parser);

        for (long i = parser->stack_size - 1; i >= 0; i--) {
            size_t count;
            ts_state to_state;
            const ts_symbol *symbols = ts_recover(parser->stack[i].state, &to_state, &count);
            for (size_t j = 0; j < count; j++) {
                if (symbols[j] == ts_parser_lookahead_sym(parser)) {
                    ts_parser_shrink_stack(parser, i + 1);
                    ts_parser_push(parser, to_state, error);
                    return 1;
                }
            }
        }

        if (!ts_parser_lookahead_char(parser)) {
            parser->stack[0].node = error;
            return 0;
        }
    }
}

#pragma mark - DSL

#define LEX_FN() \
static void ts_lex(ts_parser *parser)

#define PARSE_FN() \
static const ts_tree * ts_parse(ts_input input)

#define SYMBOL_NAMES \
static const char *ts_symbol_names[] =

#define EXPORT_PARSER(name) \
ts_parse_config name = { \
    .parse_fn = ts_parse, \
    .symbol_names = ts_symbol_names \
};

#define START_PARSER() \
ts_parser p = ts_parser_make(input), *parser = &p; \
next_state:

#define START_LEXER() \
ts_parser_skip_whitespace(parser); \
if (!ts_parser_lookahead_char(parser)) { \
    parser->lookahead_node = ts_tree_make_leaf(ts_builtin_sym_end, 0, 0); \
    return; \
} \
next_state:

#define LOOKAHEAD_SYM() \
ts_parser_lookahead_sym(parser)

#define LOOKAHEAD_CHAR() \
ts_parser_lookahead_char(parser)

#define PARSE_STATE() \
ts_parser_parse_state(parser)

#define LEX_STATE() \
parser->lex_state

#define SET_LEX_STATE(state_index) \
{ \
    parser->lex_state = state_index; \
    if (!parser->lookahead_node) ts_lex(parser); \
}

#define SHIFT(state) \
{ ts_parser_shift(parser, state); goto next_state; }

#define ADVANCE(state_index) \
{ ts_parser_advance_to_state(parser, state_index); goto next_state; }

#define REDUCE(symbol, child_count, collapse_flags) \
{ \
    static const int flags[] = collapse_flags; \
    ts_parser_reduce(parser, symbol, child_count, flags); \
    goto next_state; \
}

#define ACCEPT_INPUT() \
{ goto done; }

#define ACCEPT_TOKEN(symbol) \
{ ts_parser_set_lookahead_sym(parser, symbol); return; }

#define LEX_ERROR() \
{ ts_parser_set_lookahead_sym(parser, ts_builtin_sym_error); return; }

#define PARSE_ERROR(count, inputs) \
{ \
    static const ts_symbol expected_inputs[] = inputs; \
    if (ts_parser_handle_error(parser, count, expected_inputs)) \
        goto next_state; \
    else \
        goto done; \
}

#define LEX_PANIC() \
printf("Lex error: unexpected state %d", LEX_STATE());

#define PARSE_PANIC() \
printf("Parse error: unexpected state %d", PARSE_STATE());

#define RECOVER(new_state, symbol_count, values) \
{ \
    *count = symbol_count; \
    *to_state = new_state; \
    static ts_symbol symbols[] = values; \
    return symbols; \
}

#define EXPECT(...) __VA_ARGS__
#define COLLAPSE(...) __VA_ARGS__

#define FINISH_PARSER() \
done: \
return ts_parser_tree(parser);

#ifdef __cplusplus
}
#endif

#endif
