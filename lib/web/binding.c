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
  TRANSFER_BUFFER[0] = (const void *)TREE_SITTER_LANGUAGE_VERSION;
  TRANSFER_BUFFER[1] = (const void *)TREE_SITTER_LANGUAGE_VERSION;
  return TRANSFER_BUFFER;
}

static uint32_t code_unit_to_byte(uint32_t unit) {
  return unit << 1;
}

static uint32_t byte_to_code_unit(uint32_t byte) {
  return byte >> 1;
}

static inline void marshal_node(const void **buffer, TSNode node) {
  buffer[0] = (const void *)node.id;
  buffer[1] = (const void *)node.context[0];
  buffer[2] = (const void *)node.context[1];
  buffer[3] = (const void *)node.context[2];
  buffer[4] = (const void *)node.context[3];
}

static inline TSNode unmarshal_node(const TSTree *tree) {
  TSNode node;
  node.id = TRANSFER_BUFFER[0];
  node.context[0] = (uint32_t)TRANSFER_BUFFER[1];
  node.context[1] = (uint32_t)TRANSFER_BUFFER[2];
  node.context[2] = (uint32_t)TRANSFER_BUFFER[3];
  node.context[3] = (uint32_t)TRANSFER_BUFFER[4];
  node.tree = tree;
  return node;
}

static inline void marshal_cursor(const TSTreeCursor *cursor) {
  TRANSFER_BUFFER[0] = (const void *)cursor->id;
  TRANSFER_BUFFER[1] = (const void *)cursor->context[0];
  TRANSFER_BUFFER[2] = (const void *)cursor->context[1];
}

static inline TSTreeCursor unmarshal_cursor(const void **buffer, const TSTree *tree) {
  TSTreeCursor cursor;
  cursor.id = buffer[0];
  cursor.context[0] = (uint32_t)buffer[1];
  cursor.context[1] = (uint32_t)buffer[2];
  cursor.tree = tree;
  return cursor;
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
  if (*bytes_read >= INPUT_BUFFER_SIZE) {
    *bytes_read = INPUT_BUFFER_SIZE - 2;
  }
  return buffer;
}

void ts_parser_enable_logger_wasm(TSParser *self, bool should_log) {
  TSLogger logger = {self, should_log ? tree_sitter_log_callback : NULL};
  ts_parser_set_logger(self, logger);
}

TSTree *ts_parser_parse_wasm(
  TSParser *self,
  char *input_buffer,
  const TSTree *old_tree,
  TSRange *ranges,
  uint32_t range_count
) {
  TSInput input = {
    input_buffer,
    call_parse_callback,
    TSInputEncodingUTF16
  };
  if (range_count) {
    for (unsigned i = 0; i < range_count; i++) {
      TSRange *range = &ranges[i];
      range->start_byte = code_unit_to_byte(range->start_byte);
      range->end_byte = code_unit_to_byte(range->end_byte);
      range->start_point.column = code_unit_to_byte(range->start_point.column);
      range->end_point.column = code_unit_to_byte(range->end_point.column);
    }
    ts_parser_set_included_ranges(self, ranges, range_count);
    free(ranges);
  } else {
    ts_parser_set_included_ranges(self, NULL, 0);
  }
  return ts_parser_parse(self, old_tree, input);
}

/******************/
/* Section - Tree */
/******************/

void ts_tree_root_node_wasm(const TSTree *tree) {
  marshal_node(TRANSFER_BUFFER, ts_tree_root_node(tree));
}

void ts_tree_edit_wasm(TSTree *tree) {
  TSInputEdit edit = unmarshal_edit();
  ts_tree_edit(tree, &edit);
}

/************************/
/* Section - TreeCursor */
/************************/

void ts_tree_cursor_new_wasm(const TSTree *tree) {
  TSNode node = unmarshal_node(tree);
  TSTreeCursor cursor = ts_tree_cursor_new(node);
  marshal_cursor(&cursor);
}

void ts_tree_cursor_delete_wasm(const TSTree *tree) {
  TSTreeCursor cursor = unmarshal_cursor(TRANSFER_BUFFER, tree);
  ts_tree_cursor_delete(&cursor);
}

void ts_tree_cursor_reset_wasm(const TSTree *tree) {
  TSNode node = unmarshal_node(tree);
  TSTreeCursor cursor = unmarshal_cursor(&TRANSFER_BUFFER[5], tree);
  ts_tree_cursor_reset(&cursor, node);
  marshal_cursor(&cursor);
}

bool ts_tree_cursor_goto_first_child_wasm(const TSTree *tree) {
  TSTreeCursor cursor = unmarshal_cursor(TRANSFER_BUFFER, tree);
  bool result = ts_tree_cursor_goto_first_child(&cursor);
  marshal_cursor(&cursor);
  return result;
}

bool ts_tree_cursor_goto_next_sibling_wasm(const TSTree *tree) {
  TSTreeCursor cursor = unmarshal_cursor(TRANSFER_BUFFER, tree);
  bool result = ts_tree_cursor_goto_next_sibling(&cursor);
  marshal_cursor(&cursor);
  return result;
}

bool ts_tree_cursor_goto_parent_wasm(const TSTree *tree) {
  TSTreeCursor cursor = unmarshal_cursor(TRANSFER_BUFFER, tree);
  bool result = ts_tree_cursor_goto_parent(&cursor);
  marshal_cursor(&cursor);
  return result;
}

uint16_t ts_tree_cursor_current_node_type_id_wasm(const TSTree *tree) {
  TSTreeCursor cursor = unmarshal_cursor(TRANSFER_BUFFER, tree);
  TSNode node = ts_tree_cursor_current_node(&cursor);
  return ts_node_symbol(node);
}

bool ts_tree_cursor_current_node_is_named_wasm(const TSTree *tree) {
  TSTreeCursor cursor = unmarshal_cursor(TRANSFER_BUFFER, tree);
  TSNode node = ts_tree_cursor_current_node(&cursor);
  return ts_node_is_named(node);
}

bool ts_tree_cursor_current_node_is_missing_wasm(const TSTree *tree) {
  TSTreeCursor cursor = unmarshal_cursor(TRANSFER_BUFFER, tree);
  TSNode node = ts_tree_cursor_current_node(&cursor);
  return ts_node_is_missing(node);
}

const uint32_t ts_tree_cursor_current_node_id_wasm(const TSTree *tree) {
  TSTreeCursor cursor = unmarshal_cursor(TRANSFER_BUFFER, tree);
  TSNode node = ts_tree_cursor_current_node(&cursor);
  return (uint32_t)node.id;
}

void ts_tree_cursor_start_position_wasm(const TSTree *tree) {
  TSTreeCursor cursor = unmarshal_cursor(TRANSFER_BUFFER, tree);
  TSNode node = ts_tree_cursor_current_node(&cursor);
  marshal_point(ts_node_start_point(node));
}

void ts_tree_cursor_end_position_wasm(const TSTree *tree) {
  TSTreeCursor cursor = unmarshal_cursor(TRANSFER_BUFFER, tree);
  TSNode node = ts_tree_cursor_current_node(&cursor);
  marshal_point(ts_node_end_point(node));
}

uint32_t ts_tree_cursor_start_index_wasm(const TSTree *tree) {
  TSTreeCursor cursor = unmarshal_cursor(TRANSFER_BUFFER, tree);
  TSNode node = ts_tree_cursor_current_node(&cursor);
  return byte_to_code_unit(ts_node_start_byte(node));
}

uint32_t ts_tree_cursor_end_index_wasm(const TSTree *tree) {
  TSTreeCursor cursor = unmarshal_cursor(TRANSFER_BUFFER, tree);
  TSNode node = ts_tree_cursor_current_node(&cursor);
  return byte_to_code_unit(ts_node_end_byte(node));
}

void ts_tree_cursor_current_node_wasm(const TSTree *tree) {
  TSTreeCursor cursor = unmarshal_cursor(TRANSFER_BUFFER, tree);
  marshal_node(TRANSFER_BUFFER, ts_tree_cursor_current_node(&cursor));
}

/******************/
/* Section - Node */
/******************/

static TSTreeCursor scratch_cursor = {0};

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
  marshal_node(TRANSFER_BUFFER, ts_node_child(node, index));
}

void ts_node_named_child_wasm(const TSTree *tree, uint32_t index) {
  TSNode node = unmarshal_node(tree);
  marshal_node(TRANSFER_BUFFER, ts_node_named_child(node, index));
}

void ts_node_next_sibling_wasm(const TSTree *tree) {
  TSNode node = unmarshal_node(tree);
  marshal_node(TRANSFER_BUFFER, ts_node_next_sibling(node));
}

void ts_node_prev_sibling_wasm(const TSTree *tree) {
  TSNode node = unmarshal_node(tree);
  marshal_node(TRANSFER_BUFFER, ts_node_prev_sibling(node));
}

void ts_node_next_named_sibling_wasm(const TSTree *tree) {
  TSNode node = unmarshal_node(tree);
  marshal_node(TRANSFER_BUFFER, ts_node_next_named_sibling(node));
}

void ts_node_prev_named_sibling_wasm(const TSTree *tree) {
  TSNode node = unmarshal_node(tree);
  marshal_node(TRANSFER_BUFFER, ts_node_prev_named_sibling(node));
}

void ts_node_parent_wasm(const TSTree *tree) {
  TSNode node = unmarshal_node(tree);
  marshal_node(TRANSFER_BUFFER, ts_node_parent(node));
}

void ts_node_descendant_for_index_wasm(const TSTree *tree) {
  TSNode node = unmarshal_node(tree);
  const void **address = TRANSFER_BUFFER + 5;
  uint32_t start = code_unit_to_byte((uint32_t)address[0]);
  uint32_t end = code_unit_to_byte((uint32_t)address[1]);
  marshal_node(TRANSFER_BUFFER, ts_node_descendant_for_byte_range(node, start, end));
}

void ts_node_named_descendant_for_index_wasm(const TSTree *tree) {
  TSNode node = unmarshal_node(tree);
  const void **address = TRANSFER_BUFFER + 5;
  uint32_t start = code_unit_to_byte((uint32_t)address[0]);
  uint32_t end = code_unit_to_byte((uint32_t)address[1]);
  marshal_node(TRANSFER_BUFFER, ts_node_named_descendant_for_byte_range(node, start, end));
}

void ts_node_descendant_for_position_wasm(const TSTree *tree) {
  TSNode node = unmarshal_node(tree);
  const void **address = TRANSFER_BUFFER + 5;
  TSPoint start = unmarshal_point(address); address += 2;
  TSPoint end = unmarshal_point(address);
  marshal_node(TRANSFER_BUFFER, ts_node_descendant_for_point_range(node, start, end));
}

void ts_node_named_descendant_for_position_wasm(const TSTree *tree) {
  TSNode node = unmarshal_node(tree);
  const void **address = TRANSFER_BUFFER + 5;
  TSPoint start = unmarshal_point(address); address += 2;
  TSPoint end = unmarshal_point(address);
  marshal_node(TRANSFER_BUFFER, ts_node_named_descendant_for_point_range(node, start, end));
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

void ts_node_children_wasm(const TSTree *tree) {
  TSNode node = unmarshal_node(tree);
  uint32_t count = ts_node_child_count(node);
  const void **result = NULL;
  if (count > 0) {
    result = calloc(sizeof(void *), 5 * count);
    const void **address = result;
    ts_tree_cursor_reset(&scratch_cursor, node);
    ts_tree_cursor_goto_first_child(&scratch_cursor);
    marshal_node(address, ts_tree_cursor_current_node(&scratch_cursor));
    for (uint32_t i = 1; i < count; i++) {
      address += 5;
      ts_tree_cursor_goto_next_sibling(&scratch_cursor);
      TSNode child = ts_tree_cursor_current_node(&scratch_cursor);
      marshal_node(address, child);
    }
  }
  TRANSFER_BUFFER[0] = (const void *)count;
  TRANSFER_BUFFER[1] = result;
}

void ts_node_named_children_wasm(const TSTree *tree) {
  TSNode node = unmarshal_node(tree);
  uint32_t count = ts_node_named_child_count(node);
  const void **result = NULL;
  if (count > 0) {
    result = calloc(sizeof(void *), 5 * count);
    const void **address = result;
    ts_tree_cursor_reset(&scratch_cursor, node);
    ts_tree_cursor_goto_first_child(&scratch_cursor);
    uint32_t i = 0;
    for (;;) {
      TSNode child = ts_tree_cursor_current_node(&scratch_cursor);
      if (ts_node_is_named(child)) {
        marshal_node(address, child);
        address += 5;
        i++;
        if (i == count) break;
      }
      if (!ts_tree_cursor_goto_next_sibling(&scratch_cursor)) break;
    }
  }
  TRANSFER_BUFFER[0] = (const void *)count;
  TRANSFER_BUFFER[1] = result;
}

int ts_node_is_named_wasm(const TSTree *tree) {
  TSNode node = unmarshal_node(tree);
  return ts_node_is_named(node);
}

int ts_node_has_changes_wasm(const TSTree *tree) {
  TSNode node = unmarshal_node(tree);
  return ts_node_has_changes(node);
}

int ts_node_has_error_wasm(const TSTree *tree) {
  TSNode node = unmarshal_node(tree);
  return ts_node_has_error(node);
}

int ts_node_is_missing_wasm(const TSTree *tree) {
  TSNode node = unmarshal_node(tree);
  return ts_node_is_missing(node);
}
