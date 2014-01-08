#include "document.h"

struct TSDocument {
    TSDocumentParseFn *parse_fn;
    const char **symbol_names;
    const char *text;
    TSTree *tree;
};

TSDocument * TSDocumentMake() {
    TSDocument *result = malloc(sizeof(TSDocument));
    return result;
}

void TSDocumentSetUp(TSDocument *document, TSDocumentParseFn fn, const char **symbol_names) {
    document->parse_fn = fn;
    document->symbol_names = symbol_names;
}

void TSDocumentSetText(TSDocument *document, const char *text) {
    document->text = text;
    document->tree = document->parse_fn(document->text);
}

TSTree * TSDocumentTree(const TSDocument *document) {
    return document->tree;
}

char * TSDocumentToString(const TSDocument *document) {
    if (document->tree)
        return TSTreeToString(document->tree, document->symbol_names);
    else
        return "#<null tree>";
}
