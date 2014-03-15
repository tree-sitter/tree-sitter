#ifndef TREE_SITTER_PARSER_H_
#define TREE_SITTER_PARSER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <ctype.h>
#include <stdio.h>
#include "tree_sitter/runtime.h"

/*
 *  Parsing DSL Macros
 *
 *  Generated parser use these macros. They prevent the code generator
 *  from having too much knowledge of the runtime types and functions.
 */

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

#define PARSE_FN() \
static const ts_tree * \
ts_parse(void *data, ts_input input)

#define LEX_FN() \
static ts_tree * \
ts_lex(ts_lexer *lexer, state_id lex_state)

#define RECOVER_FN() \
static const ts_symbol * \
ts_recover(state_id state, state_id *to_state, size_t *count)

#define SYMBOL_NAMES \
static const char *ts_symbol_names[] =

#define EXPORT_PARSER(constructor_name) \
ts_parser constructor_name() { \
    ts_parser result = { \
        .parse_fn = ts_parse, \
        .symbol_names = ts_symbol_names, \
        .data = ts_lr_parser_make(), \
        .free_fn = NULL \
    }; \
    return result; \
}

#define START_PARSER() \
ts_lr_parser *parser = (ts_lr_parser *)data; \
ts_lr_parser_reset(parser); \
parser->lexer.input = input; \
ts_lexer_advance(&parser->lexer); \
next_state:

#define LOOKAHEAD_SYM() \
ts_lr_parser_lookahead_sym(parser)

#define PARSE_STATE() \
ts_stack_top_state(&parser->stack)

#define SET_LEX_STATE(state_index) \
{ if (!parser->lookahead) parser->lookahead = ts_lex(&parser->lexer, state_index); }

#define SHIFT(state) \
{ \
    DEBUG_PARSE("shift: %d \n", state); \
    ts_lr_parser_shift(parser, state); \
    goto next_state; \
}

#define REDUCE(symbol, child_count, collapse_flags) \
{ \
    static const int flags[] = collapse_flags; \
    ts_lr_parser_reduce(parser, symbol, child_count, flags); \
    DEBUG_PARSE("reduce: %s, state: %u \n", ts_symbol_names[symbol], ts_stack_state(stack)); \
    goto next_state; \
}

#define ACCEPT_INPUT() \
goto done;

#define PARSE_ERROR(count, inputs) \
{ \
    static const ts_symbol expected_inputs[] = inputs; \
    if (ts_lr_parser_handle_error(parser, count, expected_inputs)) \
        goto next_state; \
    else \
        goto done; \
}

#define FINISH_PARSER() \
done: \
DEBUG_PARSE("accept \n"); \
return ts_stack_root(&parser->stack);

#define START_LEXER() \
ts_lexer_skip_whitespace(lexer); \
if (!ts_lexer_lookahead_char(lexer)) { \
    return ts_tree_make_leaf(ts_builtin_sym_end, 0, 0); \
} \
next_state:

#define LEX_STATE() \
lex_state

#define LOOKAHEAD_CHAR() \
ts_lexer_lookahead_char(lexer)

#define ADVANCE(state_index) \
{ \
    ts_lexer_advance(lexer); \
    lex_state = state_index; \
    goto next_state; \
}

#define ACCEPT_TOKEN(symbol) \
{ \
    DEBUG_LEX("token: %s \n", ts_symbol_names[symbol]); \
    return ts_lexer_build_node(lexer, symbol); \
}

#define LEX_ERROR() \
return ts_lexer_build_node(lexer, ts_builtin_sym_error);

#define LEX_PANIC() \
{ DEBUG_LEX("Lex error: unexpected state %d", LEX_STATE()); return NULL; }

#define PARSE_PANIC() \
{ DEBUG_PARSE("Parse error: unexpected state %d", PARSE_STATE()); }

#define RECOVER(new_state, symbol_count, values) \
{ \
    *count = symbol_count; \
    *to_state = new_state; \
    static ts_symbol symbols[] = values; \
    return symbols; \
}

#define EXPECT(...) __VA_ARGS__
#define COLLAPSE(...) __VA_ARGS__


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
ts_tree * ts_stack_root(ts_stack *stack);
ts_tree * ts_stack_reduce(ts_stack *stack, ts_symbol symbol, int immediate_child_count, const int *collapse_flags);
void ts_stack_shrink(ts_stack *stack, size_t new_size);
void ts_stack_push(ts_stack *stack, state_id state, ts_tree *node);
state_id ts_stack_top_state(const ts_stack *stack);


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

static const char empty_chunk[1] = "";

static void ts_lexer_advance(ts_lexer *lexer) {
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

static ts_tree * ts_lexer_build_node(ts_lexer *lexer, ts_symbol symbol) {
    size_t current_position = ts_lexer_position(lexer);
    size_t size = current_position - lexer->token_start_position;
    size_t offset = lexer->token_start_position - lexer->token_end_position;
    lexer->token_end_position = current_position;
    return ts_tree_make_leaf(symbol, size, offset);
}

static void ts_lexer_skip_whitespace(ts_lexer *lexer) {
    while (isspace(ts_lexer_lookahead_char(lexer)))
        ts_lexer_advance(lexer);
    lexer->token_start_position = ts_lexer_position(lexer);
}

static const state_id ts_lex_state_error = -1;


/*
 *  Forward declarations
 *  The file including this header should define these functions
 */
PARSE_FN();
LEX_FN();
RECOVER_FN();


/*
 *  Parser
 */
typedef struct {
    ts_lexer lexer;
    ts_stack stack;
    ts_tree *lookahead;
    ts_tree *next_lookahead;
} ts_lr_parser;

static ts_lr_parser * ts_lr_parser_make() {
    ts_lr_parser *result = malloc(sizeof(ts_lr_parser));
    result->lexer = ts_lexer_make();
    result->stack = ts_stack_make();
    return result;
}

static void ts_lr_parser_reset(ts_lr_parser *parser) {
    ts_stack_shrink(&parser->stack, 0);
    parser->lookahead = NULL;
    parser->next_lookahead = NULL;
    parser->lexer = ts_lexer_make();
}

static ts_symbol ts_lr_parser_lookahead_sym(const ts_lr_parser *parser) {
    ts_tree *node = parser->lookahead;
    return node ? node->symbol : ts_builtin_sym_error;
}

static void ts_lr_parser_shift(ts_lr_parser *parser, state_id parse_state) {
    ts_stack_push(&parser->stack, parse_state, parser->lookahead);
    parser->lookahead = parser->next_lookahead;
    parser->next_lookahead = NULL;
}

static void ts_lr_parser_reduce(ts_lr_parser *parser, ts_symbol symbol, int immediate_child_count, const int *collapse_flags) {
    ts_tree *lookahead = ts_stack_reduce(&parser->stack, symbol, immediate_child_count, collapse_flags);
    parser->next_lookahead = parser->lookahead;
    parser->lookahead = lookahead;
}

static int ts_lr_parser_handle_error(ts_lr_parser *parser, size_t count, const ts_symbol *expected_symbols) {
    ts_tree *error = ts_tree_make_error(ts_lexer_lookahead_char(&parser->lexer), count, expected_symbols, 0, 0);

    for (;;) {
        ts_tree_release(parser->lookahead);
        parser->lookahead = ts_lex(&parser->lexer, ts_lex_state_error);
        if (parser->lookahead->symbol == ts_builtin_sym_end) {
            parser->stack.entries[0].node = error;
            return 0;
        }

        /*
         *  Unwind the stack, looking for a state in which this token
         *  may appear after an error.
         */
        for (long i = parser->stack.size - 1; i >= 0; i--) {
            size_t count;
            state_id to_state;
            const ts_symbol *symbols = ts_recover(parser->stack.entries[i].state, &to_state, &count);
            for (size_t j = 0; j < count; j++) {
                if (symbols[j] == ts_lr_parser_lookahead_sym(parser)) {
                    ts_stack_shrink(&parser->stack, i + 1);
                    ts_stack_push(&parser->stack, to_state, error);
                    return 1;
                }
            }
        }
    }
}

#ifdef __cplusplus
}
#endif

#endif  // TREE_SITTER_PARSER_H_
