#ifndef __tree_sitter_parser_h__
#define __tree_sitter_parser_h__

#include "tree.h"
#include "parse_config.h"
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int TSState;
typedef struct TSStackEntry TSStackEntry;
typedef struct TSParser {
    TSTree *tree;
    const char *input;
    char *error_message;
    size_t position;
    TSTree *lookahead_node;
    TSState lex_state;
    TSStackEntry *stack;
    size_t stack_size;
} TSParser;

TSParser TSParserMake(const char *input);
void TSParserShift(TSParser *parser, TSState state);
void TSParserReduce(TSParser *parser, TSSymbol symbol, int child_count);
void TSParserLexError(TSParser *parser, size_t count, const char **expected_inputs);
void TSParserError(TSParser *parser, size_t count, const char **expected_inputs);
void TSParserAcceptInput(TSParser *parser);
void TSParserAdvance(TSParser *parser, TSState lex_state);
TSState TSParserParseState(const TSParser *parser);
TSState TSParserLexState(const TSParser *parser);
TSParseResult TSParserResult(TSParser *parser);
void TSParserSetLexState(TSParser *parser, TSState state);
char TSParserLookaheadChar(const TSParser *parser);
long TSParserLookaheadSym(const TSParser *parser);
void TSParserSetLookaheadSym(TSParser *parser, TSSymbol symbol);

#pragma mark - DSL

#define START_PARSER() \
TSParser p = TSParserMake(input),  *parser = &p; \
next_state:
    
#define LOOKAHEAD_SYM_NAME() \
ts_symbol_names[LOOKAHEAD_SYM()]

#define START_LEXER() \
if (LOOKAHEAD_SYM() > 0) return; \
if (LOOKAHEAD_CHAR() == '\0') { ACCEPT_TOKEN(ts_symbol___END__); } \
next_state:

#define LOOKAHEAD_SYM() \
TSParserLookaheadSym(parser)

#define LOOKAHEAD_CHAR() \
TSParserLookaheadChar(parser)

#define PARSE_STATE() \
TSParserParseState(parser)

#define LEX_STATE() \
TSParserLexState(parser)

#define SHIFT(state) \
{ TSParserShift(parser, state); goto next_state; }

#define SET_LEX_STATE(state_index) \
{ TSParserSetLexState(parser, state_index); ts_lex(parser); }

#define ADVANCE(state_index) \
{ TSParserAdvance(parser, state_index); goto next_state; }

#define ACCEPT_INPUT() \
{ TSParserAcceptInput(parser); goto done; }

#define ACCEPT_TOKEN(symbol) \
{ TSParserSetLookaheadSym(parser, symbol); goto done; }

#define REDUCE(symbol, child_count) \
{ TSParserReduce(parser, symbol, child_count); goto next_state; }

#define PARSE_ERROR(count, inputs) \
{ \
static const char *expected_inputs[] = inputs; \
TSParserError(parser, count, expected_inputs); \
goto done; \
}

#define LEX_ERROR(count, inputs) \
{ \
    static const char *expected_inputs[] = inputs; \
    TSParserLexError(parser, count, expected_inputs); \
    goto done; \
}
    
#define EXPECT(...) __VA_ARGS__

#define FINISH_PARSER() \
done: \
return TSParserResult(parser);

#define FINISH_LEXER() \
done:
    
#define LEX_PANIC() \
printf("Lex error: unexpected state %ud", LEX_STATE());

#define PARSE_PANIC() \
printf("Parse error: unexpected state %ud", PARSE_STATE());

#ifdef __cplusplus
}
#endif

#endif
