#include "tree_sitter/runtime.h"
#include <string.h>

struct ts_document {
    ts_parser parser;
    const ts_tree *tree;
    ts_input input;
    size_t error_count;
};

ts_document * ts_document_make() {
    return malloc(sizeof(ts_document));
}

void ts_document_free(ts_document *document) {
    if (document->parser.free_fn)
        document->parser.free_fn(document->parser.data);
    if (document->input.release_fn)
        document->input.release_fn(document->input.data);
    free(document);
}

void ts_document_set_parser(ts_document *document, ts_parser parser) {
    document->parser = parser;
}

const ts_tree * ts_document_tree(const ts_document *document) {
    return document->tree;
}

const char * ts_document_string(const ts_document *document) {
    return ts_tree_string(document->tree, document->parser.symbol_names);
}

void ts_document_set_input(ts_document *document, ts_input input) {
    document->input = input;
    document->tree = document->parser.parse_fn(document->parser.data, input, NULL);
}

void ts_document_edit(ts_document *document, ts_input_edit edit) {
    document->tree = document->parser.parse_fn(document->parser.data, document->input, &edit);
}

const char * ts_document_symbol_name(const ts_document *document, const ts_tree *tree) {
    return document->parser.symbol_names[ts_tree_symbol(tree)];
}

typedef struct {
    const char *string;
    size_t position;
    size_t length;
} ts_string_input_data;

const char * ts_string_input_read(void *d, size_t *bytes_read) {
    ts_string_input_data *data = (ts_string_input_data *)d;
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
    ts_string_input_data *data = (ts_string_input_data *)d;
    data->position = position;
    return (position < data->length);
}

ts_input ts_string_input_make(const char *string) {
    ts_string_input_data *data = malloc(sizeof(ts_string_input_data));
    data->string = string;
    data->position = 0;
    data->length = strlen(string);
    ts_input input = {
        .data = (void *)data,
        .read_fn = ts_string_input_read,
        .seek_fn = ts_string_input_seek,
        .release_fn = free,
    };
    return input;
}

void ts_document_set_input_string(ts_document *document, const char *text) {
    ts_document_set_input(document, ts_string_input_make(text));
}
