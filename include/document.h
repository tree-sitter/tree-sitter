#ifndef __tree_sitter_document_h__
#define __tree_sitter_document_h__
#ifdef __cplusplus
extern "C" {
#endif
    
#include "./tree.h"
#include "./parse_config.h"

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
