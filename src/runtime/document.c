#include "tree_sitter/runtime.h"
#include "tree_sitter/parser.h"
#include "runtime/tree.h"
#include <string.h>

struct TSDocument {
    TSParser *parser;
    const TSTree *tree;
    TSInput input;
    size_t error_count;
};

TSDocument * ts_document_make() {
    return malloc(sizeof(TSDocument));
}

void ts_document_free(TSDocument *document) {
    ts_parser_free(document->parser);
    if (document->input.release_fn)
        document->input.release_fn(document->input.data);
    free(document);
}

void ts_document_set_parser(TSDocument *document, TSParser *parser) {
    document->parser = parser;
}

const TSTree * ts_document_tree(const TSDocument *document) {
    return document->tree;
}

const char * ts_document_string(const TSDocument *document) {
    return ts_tree_string(document->tree, ts_parser_config(document->parser).symbol_names);
}

void ts_document_set_input(TSDocument *document, TSInput input) {
    document->input = input;
    document->tree = ts_parser_parse(document->parser, document->input, NULL);
}

void ts_document_edit(TSDocument *document, TSInputEdit edit) {
    document->tree = ts_parser_parse(document->parser, document->input, &edit);
}

const char * ts_document_symbol_name(const TSDocument *document, const TSTree *tree) {
    return ts_parser_config(document->parser).symbol_names[tree->symbol];
}

typedef struct {
    const char *string;
    size_t position;
    size_t length;
} TSStringInput;

const char * ts_string_input_read(void *d, size_t *bytes_read) {
    TSStringInput *data = (TSStringInput *)d;
    if (data->position >= data->length) {
        *bytes_read = 0;
        return "";
    }
    size_t previous_position = data->position;
    data->position = data->length;
    *bytes_read = data->position - previous_position;
    return data->string + previous_position;
}

int ts_string_input_seek(void *d, size_t position) {
    TSStringInput *data = (TSStringInput *)d;
    data->position = position;
    return (position < data->length);
}

TSInput ts_string_input_make(const char *string) {
    TSStringInput *data = malloc(sizeof(TSStringInput));
    data->string = string;
    data->position = 0;
    data->length = strlen(string);
    TSInput input = {
        .data = (void *)data,
        .read_fn = ts_string_input_read,
        .seek_fn = ts_string_input_seek,
        .release_fn = free,
    };
    return input;
}

void ts_document_set_input_string(TSDocument *document, const char *text) {
    ts_document_set_input(document, ts_string_input_make(text));
}
