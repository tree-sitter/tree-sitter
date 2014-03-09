#include "tree_sitter/runtime.h"
#include <string.h>

struct ts_document {
    ts_parse_config parse_config;
    const ts_tree *tree;
    size_t error_count;
};

ts_document * ts_document_make() {
    return malloc(sizeof(ts_document));
}

void ts_document_free(ts_document *document) {
    free(document);
}

void ts_document_set_parser(ts_document *document, ts_parse_config config) {
    document->parse_config = config;
}

const ts_tree * ts_document_tree(const ts_document *document) {
    return document->tree;
}

const char * ts_document_string(const ts_document *document) {
    return ts_tree_string(document->tree, document->parse_config.symbol_names);
}

void ts_document_set_input(ts_document *document, ts_input input) {
    document->tree = document->parse_config.parse_fn(input);
}

typedef struct {
    const char *string;
    size_t position;
    size_t length;
} ts_string_input_data;

const char * ts_string_input_read(void *d) {
    ts_string_input_data *data = (ts_string_input_data *)d;
    return data->string + data->position;
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
