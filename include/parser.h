#ifndef tree_sitter_parser_h
#define tree_sitter_parser_h

#ifdef __cplusplus
extern "C" {
#endif
    
#include "runtime.h"
#include <stdio.h>
#include <string.h>

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

typedef int TSState;

typedef struct {
    TSState state;
    TSTree *node;
} TSStackEntry;

typedef struct {
    const char *input;
    size_t position;
    TSTree *lookahead_node;
    TSTree *prev_lookahead_node;
    TSState lex_state;
    TSStackEntry *stack;
    size_t stack_size;
    TSParseResult result;
} TSParser;

static TSParser TSParserMake(const char *input) {
    TSParser result = {
        .input = input,
        .position = 0,
        .lookahead_node = NULL,
        .lex_state = 0,
        .stack = calloc(INITIAL_STACK_SIZE, sizeof(TSStackEntry)),
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

static char TSParserLookaheadChar(const TSParser *parser) {
    return parser->input[parser->position];
}

static long TSParserLookaheadSym(const TSParser *parser) {
    TSTree *node = parser->lookahead_node;
    return node ? node->value : -1;
}

static TSState TSParserParseState(const TSParser *parser) {
    if (parser->stack_size == 0) return 0;
    return parser->stack[parser->stack_size - 1].state;
}

static void TSParserShift(TSParser *parser, TSState parse_state) {
    DEBUG_PARSE("shift: %d \n", parse_state);
    TSStackEntry *entry = (parser->stack + parser->stack_size);
    entry->state = parse_state;
    entry->node = parser->lookahead_node;
    parser->lookahead_node = parser->prev_lookahead_node;
    parser->prev_lookahead_node = NULL;
    parser->stack_size++;
}

static void TSParserReduce(TSParser *parser, TSSymbol symbol, int immediate_child_count, const int *collapse_flags) {
    parser->stack_size -= immediate_child_count;
    
    int total_child_count = 0;
    for (int i = 0; i < immediate_child_count; i++) {
        TSTree *child = parser->stack[parser->stack_size + i].node;
        if (collapse_flags[i]) {
            total_child_count += child->child_count;
        } else {
            total_child_count++;
        }
    }
    
    TSTree **children = malloc(total_child_count * sizeof(TSTree *));
    int n = 0;
    for (int i = 0; i < immediate_child_count; i++) {
        TSTree *child = parser->stack[parser->stack_size + i].node;
        if (collapse_flags[i]) {
            memcpy(children + n, child->children, (child->child_count * sizeof(TSTree *)));
            n += child->child_count;
        } else {
            children[n] = child;
            n++;
        }
    }
    
    parser->prev_lookahead_node = parser->lookahead_node;
    parser->lookahead_node = TSTreeMake(symbol, total_child_count, children);
    DEBUG_PARSE("reduce: %s, state: %u \n", ts_symbol_names[symbol], TSParserParseState(parser));
}

static void TSParserError(TSParser *parser, size_t count, const char **expected_inputs) {
    TSParseError *error = &parser->result.error;
    error->position = parser->position;
    error->expected_input_count = count;
    error->expected_inputs = expected_inputs;
    error->lookahead_sym = TSParserLookaheadSym(parser);
}
    
static int TSParserHasError(const TSParser *parser) {
    return (parser->result.error.expected_inputs != NULL);
}

static void TSParserAdvance(TSParser *parser, TSState lex_state) {
    DEBUG_LEX("character: '%c' \n", TSParserLookaheadChar(parser));
    parser->position++;
    parser->lex_state = lex_state;
}

static void TSParserSetLookaheadSym(TSParser *parser, TSSymbol symbol) {
    DEBUG_LEX("token: %s \n", ts_symbol_names[symbol]);
    parser->lookahead_node = TSTreeMake(symbol, 0, NULL);
}

static void TSParserAcceptInput(TSParser *parser) {
    parser->result.tree = parser->stack[parser->stack_size - 1].node;
    DEBUG_PARSE("accept \n");
}

#pragma mark - DSL

#define START_PARSER() \
TSParser p = TSParserMake(input), *parser = &p; \
next_state:

#define START_LEXER() \
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
