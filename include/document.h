#ifndef __tree_sitter_document_h__
#define __tree_sitter_document_h__

#include "./tree.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct TSDocument TSDocument;
typedef TSTree * TSDocumentParseFn(const char *);

TSDocument * TSDocumentMake();
void TSDocumentSetUp(TSDocument *document, TSDocumentParseFn fn, const char **symbol_names);
void TSDocumentSetText(TSDocument *document, const char *text);
TSTree * TSDocumentTree(const TSDocument *document);
char * TSDocumentToString(const TSDocument *document);

#ifdef __cplusplus
}
#endif
#endif
