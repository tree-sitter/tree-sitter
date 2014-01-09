#include "document.h"

struct TSDocument {
    TSParseFn *parse_fn;
    const char **symbol_names;
    const char *text;
    const char *error_message;
    TSTree *tree;
};

TSDocument * TSDocumentMake() {
    TSDocument *result = malloc(sizeof(TSDocument));
    return result;
}

void TSDocumentSetUp(TSDocument *document, TSParseConfig config) {
    document->parse_fn = config.parse_fn;
    document->symbol_names = config.symbol_names;
}

void TSDocumentSetText(TSDocument *document, const char *text) {
    document->text = text;
    TSParseResult result = document->parse_fn(text);
    document->tree = result.tree;
    document->error_message = result.error.message;
}

TSTree * TSDocumentTree(const TSDocument *document) {
    return document->tree;
}

const char * TSDocumentToString(const TSDocument *document) {
    if (document->error_message) {
        return document->error_message;
    } else if (document->tree)
        return TSTreeToString(document->tree, document->symbol_names);
    else
        return "#<null tree>";
}
