#ifndef tree_sitter_runtime_h
#define tree_sitter_runtime_h

#ifdef __cplusplus
extern "C" {
#endif
    
#include <stdlib.h>
    
typedef struct {
    const char **expected_inputs;
    size_t expected_input_count;
    size_t position;
    long lookahead_sym;
} TSParseError;

const char * TSParseErrorToString(const TSParseError *error, const char *input_string, const char **symbol_names);

typedef size_t TSSymbol;
    
typedef struct TSTree {
    TSSymbol value;
    struct TSTree **children;
    size_t child_count;
    size_t ref_count;
} TSTree;

TSTree * TSTreeMake(TSSymbol value, size_t child_count, TSTree **children);
void TSTreeRetain(TSTree *tree);
void TSTreeRelease(TSTree *tree);
int TSTreeEquals(const TSTree *tree1, const TSTree *tree2);
char * TSTreeToString(const TSTree *tree, const char **names);

typedef struct {
    TSParseError error;
    TSTree *tree;
} TSParseResult;

typedef TSParseResult TSParseFn(const char *);

typedef struct {
    TSParseFn *parse_fn;
    const char **symbol_names;
} TSParseConfig;

typedef struct TSDocument TSDocument;

TSDocument * TSDocumentMake();
void TSDocumentSetUp(TSDocument *document, TSParseConfig config);
void TSDocumentSetText(TSDocument *document, const char *text);
TSTree * TSDocumentTree(const TSDocument *document);
const char * TSDocumentToString(const TSDocument *document);
    
#ifdef __cplusplus
}
#endif

#endif
