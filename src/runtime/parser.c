#include "parser.h"
#include <stdio.h>

static int INITIAL_STACK_SIZE = 100;

TSParser TSParserMake(const char *input) {
    TSParser result = {
        .tree = TSTreeMake(),
        .input = input,
        .position = 0,
        .lookahead_sym = 0,
        .lex_state = 0,
        .stack = calloc(INITIAL_STACK_SIZE, sizeof(TSStackEntry)),
        .stack_size = 0,
    };
    return result;
}

void TSParserShift(TSParser *parser, TSState parse_state) {
    TSStackEntry *entry = (parser->stack + parser->stack_size);
    entry->state = parse_state;
    entry->symbol = parser->lookahead_sym;
    parser->lookahead_sym = -1;
    parser->stack_size++;
}

void TSParserReduce(TSParser *parser, TSSymbol symbol, int child_count) {
    parser->lookahead_sym = symbol;
    parser->stack_size -= child_count;
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

TSSymbol TSParserLookaheadSym(const TSParser *parser) {
    return parser->lookahead_sym;
}

void TSParserSetLookaheadSym(TSParser *parser, TSSymbol symbol) {
    parser->lookahead_sym = symbol;
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
