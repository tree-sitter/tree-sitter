#include "runtime.h"


static int INITIAL_STATE_STACK_SIZE = 100;
static int INITIAL_SYMBOL_STACK_SIZE = 100;


TSParser TSParserMake(const char *input) {
    TSState *state_stack = calloc(INITIAL_STATE_STACK_SIZE, sizeof(*state_stack));
    TSSymbol *symbol_stack = calloc(INITIAL_SYMBOL_STACK_SIZE, sizeof(*symbol_stack));
    TSParser result = {
        .input = input,
        .tree = TSTreeMake(),
        .position = 0,
        .state_stack = state_stack,
        .symbol_stack = symbol_stack,
        .state_count = 0,
        .symbol_count = 0
    };
    return result;
}

void TSParserShift(TSParser *parser, TSState state) {
    
}

void TSParserReduce(TSParser *parser, TSSymbol symbol, int child_count) {
    
}

void TSParserError(TSParser *parser) {
    
}

TSSymbol TSParserLookahead(const TSParser *parser) {
    return 1;
}

TSState TSParserParseState(const TSParser *parser) {
    return 5;
}

TSState TSParserLexState(const TSParser *parser) {
    return 5;
}
