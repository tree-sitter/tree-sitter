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

typedef struct {
    ts_state state;
    ts_tree *node;
} ts_stack_entry;

typedef struct {
    const char *input;
    size_t position;
    ts_tree *lookahead_node;
    ts_tree *prev_lookahead_node;
    ts_state lex_state;
    ts_stack_entry *stack;
    size_t stack_size;
    ts_parse_result result;
} ts_parser;

static ts_parser TSParserMake(const char *input) {
    ts_parser result = {
        .input = input,
        .position = 0,
        .lookahead_node = NULL,
        .lex_state = 0,
        .stack = calloc(INITIAL_STACK_SIZE, sizeof(ts_stack_entry)),
        .stack_size = 0,
        .result = {
            .tree = NULL,
            .error = {
                .expected_inputs = NULL,
                .expected_input_count = 0
            },
        },
    };
    return result;
}

static char TSParserLookaheadChar(const ts_parser *parser) {
    return parser->input[parser->position];
}

static long TSParserLookaheadSym(const ts_parser *parser) {
    ts_tree *node = parser->lookahead_node;
    return node ? node->value : -1;
}

static ts_state TSParserParseState(const ts_parser *parser) {
    if (parser->stack_size == 0) return 0;
    return parser->stack[parser->stack_size - 1].state;
}

static void TSParserShift(ts_parser *parser, ts_state parse_state) {
    DEBUG_PARSE("shift: %d \n", parse_state);
    ts_stack_entry *entry = (parser->stack + parser->stack_size);
    entry->state = parse_state;
    entry->node = parser->lookahead_node;
    parser->lookahead_node = parser->prev_lookahead_node;
    parser->prev_lookahead_node = NULL;
    parser->stack_size++;
}

static void TSParserReduce(ts_parser *parser, ts_symbol symbol, int immediate_child_count, const int *collapse_flags) {
    parser->stack_size -= immediate_child_count;
    
    int total_child_count = 0;
    for (int i = 0; i < immediate_child_count; i++) {
        ts_tree *child = parser->stack[parser->stack_size + i].node;
        if (collapse_flags[i]) {
            total_child_count += child->child_count;
        } else {
            total_child_count++;
        }
    }
    
    ts_tree **children = malloc(total_child_count * sizeof(ts_tree *));
    int n = 0;
    for (int i = 0; i < immediate_child_count; i++) {
        ts_tree *child = parser->stack[parser->stack_size + i].node;
        if (collapse_flags[i]) {
            memcpy(children + n, child->children, (child->child_count * sizeof(ts_tree *)));
            n += child->child_count;
        } else {
            children[n] = child;
            n++;
        }
    }
    
    parser->prev_lookahead_node = parser->lookahead_node;
    parser->lookahead_node = ts_tree_make(symbol, total_child_count, children);
    DEBUG_PARSE("reduce: %s, state: %u \n", ts_symbol_names[symbol], TSParserParseState(parser));
}

static void TSParserError(ts_parser *parser, size_t count, const char **expected_inputs) {
    ts_error *error = &parser->result.error;
    error->position = parser->position;
    error->lookahead_char = TSParserLookaheadChar(parser);
    error->expected_input_count = count;
    error->expected_inputs = expected_inputs;
}
    
static int TSParserHasError(const ts_parser *parser) {
    return (parser->result.error.expected_inputs != NULL);
}

static void TSParserAdvance(ts_parser *parser, ts_state lex_state) {
    DEBUG_LEX("character: '%c' \n", TSParserLookaheadChar(parser));
    parser->position++;
    parser->lex_state = lex_state;
}

static void TSParserSetLookaheadSym(ts_parser *parser, ts_symbol symbol) {
    DEBUG_LEX("token: %s \n", ts_symbol_names[symbol]);
    parser->lookahead_node = ts_tree_make(symbol, 0, NULL);
}

static void TSParserAcceptInput(ts_parser *parser) {
    parser->result.tree = parser->stack[parser->stack_size - 1].node;
    DEBUG_PARSE("accept \n");
}

static void TSParserSkipWhitespace(ts_parser *parser) {
    while (isspace(parser->input[parser->position]))
        parser->position++;
}

#pragma mark - DSL

#define LEX_FN() \
static void ts_lex(ts_parser *parser)
    
#define PARSE_FN() \
static ts_parse_result ts_parse(const char *input)
    
#define SYMBOL_NAMES \
static const char *ts_symbol_names[] =

#define EXPORT_PARSER(name) \
ts_parse_config name = { \
    .parse_fn = ts_parse, \
    .symbol_names = ts_symbol_names \
};

#define START_PARSER() \
ts_parser p = TSParserMake(input), *parser = &p; \
next_state:

#define START_LEXER() \
TSParserSkipWhitespace(parser); \
next_state:

#define LOOKAHEAD_SYM() \
TSParserLookaheadSym(parser)

#define LOOKAHEAD_CHAR() \
TSParserLookaheadChar(parser)

#define PARSE_STATE() \
TSParserParseState(parser)

#define LEX_STATE() \
parser->lex_state

#define SET_LEX_STATE(state_index) \
{ \
    parser->lex_state = state_index; \
    if (LOOKAHEAD_SYM() < 0) ts_lex(parser); \
    if (TSParserHasError(parser)) goto done; \
}

#define SHIFT(state) \
{ TSParserShift(parser, state); goto next_state; }

#define ADVANCE(state_index) \
{ TSParserAdvance(parser, state_index); goto next_state; }

#define REDUCE(symbol, child_count, collapse_flags) \
{ \
static const int flags[] = collapse_flags; \
TSParserReduce(parser, symbol, child_count, flags); \
goto next_state; \
}

#define ACCEPT_INPUT() \
{ TSParserAcceptInput(parser); goto done; }

#define ACCEPT_TOKEN(symbol) \
{ TSParserSetLookaheadSym(parser, symbol); goto done; }

#define LEX_ERROR(count, inputs) \
{ \
static const char *expected_inputs[] = inputs; \
TSParserError(parser, count, expected_inputs); \
goto done; \
}

#define LEX_PANIC() \
printf("Lex error: unexpected state %ud", LEX_STATE());
    
#define PARSE_PANIC() \
printf("Parse error: unexpected state %ud", PARSE_STATE());

#define EXPECT(...) __VA_ARGS__
#define COLLAPSE(...) __VA_ARGS__

#define FINISH_PARSER() \
done: \
return parser->result;

#define FINISH_LEXER() \
done:

#ifdef __cplusplus
}
#endif

#endif
