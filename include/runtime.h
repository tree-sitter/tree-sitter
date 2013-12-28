#ifndef tree_sitter_runtime_h
#define tree_sitter_runtime_h

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

#pragma mark - Tree

typedef struct {
} TSTree;
    
TSTree TSTreeMake();

#pragma mark - Parser

typedef size_t TSSymbol;
typedef int TSState;
    
typedef struct {
    TSTree tree;
    const char *input;
    size_t position;
    TSState *state_stack;
    TSSymbol *symbol_stack;
    size_t state_count;
    size_t symbol_count;
} TSParser;

TSParser TSParserMake(const char *input);
void TSParserShift(TSParser *parser, TSState state);
void TSParserReduce(TSParser *parser, TSSymbol symbol, int child_count);
void TSParserError(TSParser *parser);
TSState TSParserParseState(const TSParser *parser);
TSState TSParserLexState(const TSParser *parser);
TSSymbol TSParserLookahead(const TSParser *parser);

#pragma mark - DSL

#define START_PARSER() \
    TSParser parser = TSParserMake(input); \
    start: \
    ts_lex(&parser);

#define START_LEXER() \
    start:

#define LOOKAHEAD_SYM() \
    TSParserLookahead(&parser)

#define LOOKAHEAD_CHAR() \
    'a'

#define PARSE_STATE() \
    TSParserParseState(&parser)

#define LEX_STATE() \
    TSParserLexState(parser)

#define SHIFT(number) \
    { TSParserShift(&parser, number); break; }

#define ADVANCE(state_index) \
    { break; }

#define ACCEPT_INPUT() \
    { goto done; }

#define ACCEPT_TOKEN(symbol) \
    { goto done; }

#define REDUCE(symbol, child_count) \
    { TSParserReduce(&parser, symbol, child_count); break; }

#define PARSE_ERROR() \
    TSParserError(&parser)

#define LEX_ERROR() \
    TSParserError(parser)

#define FINISH_PARSER() \
    done: \
    return parser.tree;

#define FINISH_LEXER() \
    done:

#endif
    
#ifdef __cplusplus
}
#endif
