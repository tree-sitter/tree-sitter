#include "tree_sitter/runtime.h"

struct ts_document {
    ts_parse_fn *parse_fn;
    const char **symbol_names;
    ts_error error;
    ts_tree *tree;
};

ts_document * ts_document_make() {
    return new ts_document();
}

void ts_document_free(ts_document *document) {
    delete document;
}

void ts_document_set_parser(ts_document *document, ts_parse_config config) {
    document->parse_fn = config.parse_fn;
    document->symbol_names = config.symbol_names;
}

void ts_document_set_text(ts_document *document, const char *text) {
    ts_parse_result result = document->parse_fn(text);
    document->tree = result.tree;
    document->error = result.error;
}

ts_tree * ts_document_tree(const ts_document *document) {
    return document->tree;
}

const char * ts_document_string(const ts_document *document) {
    if (document->error.expected_inputs != NULL) {
        return ts_error_string(&document->error);
    } else {
        return ts_tree_string(document->tree, document->symbol_names);
    }
}
