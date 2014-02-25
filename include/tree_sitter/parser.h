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
    const char *input;
    int error_mode;
    size_t position;
    ts_tree *lookahead_node;
    ts_tree *prev_lookahead_node;
    ts_state lex_state;
    ts_stack_entry *stack;
    size_t stack_size;
    ts_tree *result;
} ts_parser;

static void ts_lex(ts_parser *parser);

static ts_parser ts_parser_make(const char *input) {
    ts_parser result = {
        .input = input,
        .position = 0,
        .lookahead_node = NULL,
        .lex_state = 0,
        .stack = calloc(INITIAL_STACK_SIZE, sizeof(ts_stack_entry)),
        .stack_size = 0,
        .result = NULL,
    };
    return result;
}

static char ts_parser_lookahead_char(const ts_parser *parser) {
    return parser->input[parser->position];
}

static ts_symbol ts_parser_lookahead_sym(const ts_parser *parser) {
    ts_tree *node = parser->lookahead_node;
    return node ? node->symbol : ts_symbol_error;
}

static ts_state ts_parser_parse_state(const ts_parser *parser) {
    if (parser->stack_size == 0) return 0;
    return parser->stack[parser->stack_size - 1].state;
}

static void ts_parser_shift(ts_parser *parser, ts_state parse_state) {
    DEBUG_PARSE("shift: %d \n", parse_state);
    ts_stack_entry *entry = (parser->stack + parser->stack_size);
    entry->state = parse_state;
    entry->node = parser->lookahead_node;
    parser->lookahead_node = parser->prev_lookahead_node;
    parser->prev_lookahead_node = NULL;
    parser->stack_size++;
}

static void ts_parser_reduce(ts_parser *parser, ts_symbol symbol, int immediate_child_count, const int *collapse_flags) {
    parser->stack_size -= immediate_child_count;
    
    int total_child_count = 0;
    for (int i = 0; i < immediate_child_count; i++) {
        ts_tree *child = parser->stack[parser->stack_size + i].node;
        if (collapse_flags[i]) {
            total_child_count += ts_tree_child_count(child);
        } else {
            total_child_count++;
        }
    }
    
    ts_tree **children = malloc(total_child_count * sizeof(ts_tree *));
    int n = 0;
    for (int i = 0; i < immediate_child_count; i++) {
        ts_tree *child = parser->stack[parser->stack_size + i].node;
        if (collapse_flags[i]) {
            size_t grandchild_count = ts_tree_child_count(child);
            if (grandchild_count > 0) {
                memcpy(children + n, ts_tree_children(child), (grandchild_count * sizeof(ts_tree *)));
                n += grandchild_count;
            }
        } else {
            children[n] = child;
            n++;
        }
    }
    
    parser->prev_lookahead_node = parser->lookahead_node;
    parser->lookahead_node = ts_tree_make_node(symbol, total_child_count, children);
    DEBUG_PARSE("reduce: %s, state: %u \n", ts_symbol_names[symbol], ts_parser_parse_state(parser));
}

static void ts_parser_advance(ts_parser *parser, ts_state lex_state) {
    DEBUG_LEX("character: '%c' \n", ts_parser_lookahead_char(parser));
    parser->position++;
    parser->lex_state = lex_state;
}

static void ts_parser_set_lookahead_sym(ts_parser *parser, ts_symbol symbol) {
    DEBUG_LEX("token: %s \n", ts_symbol_names[symbol]);
    parser->lookahead_node = ts_tree_make_leaf(symbol);
}

static ts_tree * ts_parser_tree(ts_parser *parser) {
    DEBUG_PARSE("accept \n");
    return parser->stack[0].node;
}

static void ts_parser_skip_whitespace(ts_parser *parser) {
    while (isspace(ts_parser_lookahead_char(parser)))
        parser->position++;
}
 
static void ts_parser_handle_error(ts_parser *parser, size_t count, const ts_symbol *expected_symbols) {
    if (parser->error_mode) {
        parser->lex_state = ts_lex_state_error;
        ts_lex(parser);
    } else {
        parser->error_mode = 1;
        parser->lookahead_node = ts_tree_make_error(ts_parser_lookahead_char(parser), count, expected_symbols);
    }
}

#pragma mark - DSL

#define LEX_FN() \
static void ts_lex(ts_parser *parser)
    
#define PARSE_FN() \
static const ts_tree * ts_parse(const char *input)
    
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
if (ts_parser_lookahead_char(parser) == '\0') { \
    ACCEPT_TOKEN(ts_aux_sym_end) \
} \
ts_parser_skip_whitespace(parser); \
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
    if (LOOKAHEAD_SYM() < 0) ts_lex(parser); \
}

#define SHIFT(state) \
{ ts_parser_shift(parser, state); goto next_state; }

#define ADVANCE(state_index) \
{ ts_parser_advance(parser, state_index); goto next_state; }

#define REDUCE(symbol, child_count, collapse_flags) \
{ \
static const int flags[] = collapse_flags; \
ts_parser_reduce(parser, symbol, child_count, flags); \
goto next_state; \
}

#define ACCEPT_INPUT() \
{ goto done; }

#define ACCEPT_TOKEN(symbol) \
{ ts_parser_set_lookahead_sym(parser, symbol); goto done; }

#define LEX_ERROR() \
{ ts_parser_set_lookahead_sym(parser, -1); goto done; }
    
#define PARSE_ERROR(count, inputs) \
{ \
static const ts_symbol expected_inputs[] = inputs; \
ts_parser_handle_error(parser, count, expected_inputs); \
goto next_state; \
}

#define LEX_PANIC() \
printf("Lex error: unexpected state %d", LEX_STATE());
    
#define PARSE_PANIC() \
printf("Parse error: unexpected state %d", PARSE_STATE());

#define EXPECT(...) __VA_ARGS__
#define COLLAPSE(...) __VA_ARGS__

#define FINISH_PARSER() \
done: \
return ts_parser_tree(parser);

#define FINISH_LEXER() \
done:

#ifdef __cplusplus
}
#endif

#endif
