#include <emscripten.h>
#include <tree_sitter/api.h>
#include <stdio.h>

/*****************************/
/* Section - Data marshaling */
/*****************************/

static const uint32_t INPUT_BUFFER_SIZE = 10 * 1024;

const void *TRANSFER_BUFFER[12] = {
  NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL,
};

void *ts_init() {
  return TRANSFER_BUFFER;
}

static uint32_t code_unit_to_byte(uint32_t unit) {
  return unit << 1;
}

static uint32_t byte_to_code_unit(uint32_t byte) {
  return byte >> 1;
}

static void marshal_node(TSNode node) {
  TRANSFER_BUFFER[0] = (const void *)node.id;
  TRANSFER_BUFFER[1] = (const void *)node.context[0];
  TRANSFER_BUFFER[2] = (const void *)node.context[1];
  TRANSFER_BUFFER[3] = (const void *)node.context[2];
  TRANSFER_BUFFER[4] = (const void *)node.context[3];
}

static TSNode unmarshal_node(const TSTree *tree) {
  TSNode node;
  node.id = TRANSFER_BUFFER[0];
  node.context[0] = (uint32_t)TRANSFER_BUFFER[1];
  node.context[1] = (uint32_t)TRANSFER_BUFFER[2];
  node.context[2] = (uint32_t)TRANSFER_BUFFER[3];
  node.context[3] = (uint32_t)TRANSFER_BUFFER[4];
  node.tree = tree;
  return node;
}

static void marshal_point(TSPoint point) {
  TRANSFER_BUFFER[0] = (const void *)point.row;
  TRANSFER_BUFFER[1] = (const void *)byte_to_code_unit(point.column);
}

static TSPoint unmarshal_point(const void **address) {
  TSPoint point;
  point.row = (uint32_t)address[0];
  point.column = code_unit_to_byte((uint32_t)address[1]);
  return point;
}

static TSInputEdit unmarshal_edit() {
  TSInputEdit edit;
  const void **address = TRANSFER_BUFFER;
  edit.start_point = unmarshal_point(address); address += 2;
  edit.old_end_point = unmarshal_point(address); address += 2;
  edit.new_end_point = unmarshal_point(address); address += 2;
  edit.start_byte = code_unit_to_byte((uint32_t)*address); address += 1;
  edit.old_end_byte = code_unit_to_byte((uint32_t)*address); address += 1;
  edit.new_end_byte = code_unit_to_byte((uint32_t)*address); address += 1;
  return edit;
}

/********************/
/* Section - Parser */
/********************/

extern void tree_sitter_parse_callback(
  char *input_buffer,
  uint32_t index,
  uint32_t row,
  uint32_t column,
  uint32_t *length_read
);

extern void tree_sitter_log_callback(
  void *payload,
  TSLogType log_type,
  const char *message
);

void ts_parser_new_wasm() {
  TSParser *parser = ts_parser_new();
  char *input_buffer = calloc(INPUT_BUFFER_SIZE, sizeof(char));
  TRANSFER_BUFFER[0] = parser;
  TRANSFER_BUFFER[1] = input_buffer;
}

static const char *call_parse_callback(
  void *payload,
  uint32_t byte,
  TSPoint position,
  uint32_t *bytes_read
) {
  char *buffer = (char *)payload;
  tree_sitter_parse_callback(
    buffer,
    byte_to_code_unit(byte),
    position.row,
    byte_to_code_unit(position.column),
    bytes_read
  );
  *bytes_read = code_unit_to_byte(*bytes_read);
  if (*bytes_read > INPUT_BUFFER_SIZE) *bytes_read = INPUT_BUFFER_SIZE;
  if (*bytes_read > 0) *bytes_read -= 2; // Remove null character
  return buffer;
}

void ts_parser_enable_logger_wasm(TSParser *self, bool should_log) {
  TSLogger logger = {self, should_log ? tree_sitter_log_callback : NULL};
  ts_parser_set_logger(self, logger);
}

TSTree *ts_parser_parse_wasm(
  TSParser *self,
  char *input_buffer,
  const TSTree *old_tree
) {
  TSInput input = {
    input_buffer,
    call_parse_callback,
    TSInputEncodingUTF16
  };
  return ts_parser_parse(self, old_tree, input);
}

/******************/
/* Section - Tree */
/******************/

void ts_tree_root_node_wasm(const TSTree *tree) {
  marshal_node(ts_tree_root_node(tree));
}

void ts_tree_edit_wasm(TSTree *tree) {
  TSInputEdit edit = unmarshal_edit();
  ts_tree_edit(tree, &edit);
}

/******************/
/* Section - Node */
/******************/

uint16_t ts_node_symbol_wasm(const TSTree *tree) {
  TSNode node = unmarshal_node(tree);
  return ts_node_symbol(node);
}

uint32_t ts_node_child_count_wasm(const TSTree *tree) {
  TSNode node = unmarshal_node(tree);
  return ts_node_child_count(node);
}

uint32_t ts_node_named_child_count_wasm(const TSTree *tree) {
  TSNode node = unmarshal_node(tree);
  return ts_node_named_child_count(node);
}

void ts_node_child_wasm(const TSTree *tree, uint32_t index) {
  TSNode node = unmarshal_node(tree);
  marshal_node(ts_node_child(node, index));
}

void ts_node_named_child_wasm(const TSTree *tree, uint32_t index) {
  TSNode node = unmarshal_node(tree);
  marshal_node(ts_node_named_child(node, index));
}

void ts_node_parent_wasm(const TSTree *tree) {
  TSNode node = unmarshal_node(tree);
  marshal_node(ts_node_parent(node));
}

void ts_node_descendant_for_position_wasm(const TSTree *tree) {
  TSNode node = unmarshal_node(tree);
  const void **address = TRANSFER_BUFFER + 5;
  TSPoint start = unmarshal_point(address); address += 2;
  TSPoint end = unmarshal_point(address);
  marshal_node(ts_node_descendant_for_point_range(node, start, end));
}

void ts_node_named_descendant_for_position_wasm(const TSTree *tree) {
  TSNode node = unmarshal_node(tree);
  const void **address = TRANSFER_BUFFER + 5;
  TSPoint start = unmarshal_point(address); address += 2;
  TSPoint end = unmarshal_point(address);
  marshal_node(ts_node_named_descendant_for_point_range(node, start, end));
}

void ts_node_start_point_wasm(const TSTree *tree) {
  TSNode node = unmarshal_node(tree);
  marshal_point(ts_node_start_point(node));
}

void ts_node_end_point_wasm(const TSTree *tree) {
  TSNode node = unmarshal_node(tree);
  marshal_point(ts_node_end_point(node));
}

uint32_t ts_node_start_index_wasm(const TSTree *tree) {
  TSNode node = unmarshal_node(tree);
  return byte_to_code_unit(ts_node_start_byte(node));
}

uint32_t ts_node_end_index_wasm(const TSTree *tree) {
  TSNode node = unmarshal_node(tree);
  return byte_to_code_unit(ts_node_end_byte(node));
}

char *ts_node_to_string_wasm(const TSTree *tree) {
  TSNode node = unmarshal_node(tree);
  return ts_node_string(node);
}
