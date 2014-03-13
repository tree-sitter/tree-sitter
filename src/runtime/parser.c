#include "tree_sitter/runtime.h"

const ts_tree * ts_parser_parse(ts_parser *parser, ts_input input) {
    return parser->parse_fn(parser->data, input);
}

void ts_parser_free(ts_parser *parser) {
    if (parser->free_fn != NULL)
        parser->free_fn(parser->data);
}