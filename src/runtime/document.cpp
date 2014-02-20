#include "tree_sitter/runtime.h"

struct TSDocument {
    TSParseFn *parse_fn;
    const char **symbol_names;
    const char *text;
    TSParseError error;
    TSTree *tree;
};

TSDocument * TSDocumentMake() {
    return new TSDocument();
}

void TSDocumentSetUp(TSDocument *document, TSParseConfig config) {
    document->parse_fn = config.parse_fn;
    document->symbol_names = config.symbol_names;
}

void TSDocumentSetText(TSDocument *document, const char *text) {
    TSParseResult result = document->parse_fn(text);
    document->text = text;
    document->tree = result.tree;
    document->error = result.error;
}

TSTree * TSDocumentTree(const TSDocument *document) {
    return document->tree;
}

const char * TSDocumentToString(const TSDocument *document) {
    if (document->error.expected_inputs != NULL) {
        return TSParseErrorToString(&document->error, document->text, document->symbol_names);
    } else {
        return TSTreeToString(document->tree, document->symbol_names);
    }
}
