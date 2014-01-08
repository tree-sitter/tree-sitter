#include "parser.h"
#include <stdio.h>

static int INITIAL_STACK_SIZE = 100;

struct TSStackEntry {
    TSState state;
    TSTree *node;
};

TSParser TSParserMake(const char *input) {
    TSParser result = {
        .tree = NULL,
        .input = input,
        .position = 0,
        .lookahead_node = NULL,
        .lex_state = 0,
        .stack = calloc(INITIAL_STACK_SIZE, sizeof(TSStackEntry)),
        .stack_size = 0,
    };
    return result;
}

void TSParserShift(TSParser *parser, TSState parse_state) {
    TSStackEntry *entry = (parser->stack + parser->stack_size);
    entry->state = parse_state;
    entry->node = parser->lookahead_node;
    parser->lookahead_node = NULL;
    parser->stack_size++;
}

void TSParserReduce(TSParser *parser, TSSymbol symbol, int child_count) {
    parser->stack_size -= child_count;

    TSTree **children = malloc(child_count * sizeof(TSTree *));
    for (int i = 0; i < child_count; i++) {
        size_t j = parser->stack_size + i;
        children[i] = parser->stack[j].node;
    }
    
    parser->lookahead_node = TSTreeMake(symbol, child_count, children);
}

void TSParserError(TSParser *parser) {
    
}

void TSParserAdvance(TSParser *parser, TSState lex_state) {
    parser->position++;
    parser->lex_state = lex_state;
}

char TSParserLookaheadChar(const TSParser *parser) {
    return parser->input[parser->position];
}

long TSParserLookaheadSym(const TSParser *parser) {
    TSTree *node = parser->lookahead_node;
    return node ? node->value : -1;
}

void TSParserSetLookaheadSym(TSParser *parser, TSSymbol symbol) {
    parser->lookahead_node = TSTreeMake(symbol, 0, NULL);
}

TSState TSParserParseState(const TSParser *parser) {
    return parser->stack[parser->stack_size - 1].state;
}

TSState TSParserLexState(const TSParser *parser) {
    return parser->lex_state;
}

void TSParserSetLexState(TSParser *parser, TSState lex_state) {
    parser->lex_state = lex_state;
}

void TSParserAcceptInput(TSParser *parser) {
    parser->tree = parser->stack[parser->stack_size - 1].node;
}

