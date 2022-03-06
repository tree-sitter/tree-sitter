#include <emscripten.h>
#include <tree_sitter/api.h>
#include <stdio.h>
#include "array.h"
#include "point.h"

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
  TRANSFER_BUFFER[1] = (const void *)TREE_SITTER_MIN_COMPATIBLE_LANGUAGE_VERSION;
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
  buffer[1] = (const void *)byte_to_code_unit(node.context[0]);
  buffer[2] = (const void *)node.context[1];
  buffer[3] = (const void *)byte_to_code_unit(node.context[2]);
  buffer[4] = (const void *)node.context[3];
}

static inline TSNode unmarshal_node(const TSTree *tree) {
  TSNode node;
  node.id = TRANSFER_BUFFER[0];
  node.context[0] = code_unit_to_byte((uint32_t)TRANSFER_BUFFER[1]);
  node.context[1] = (uint32_t)TRANSFER_BUFFER[2];
  node.context[2] = code_unit_to_byte((uint32_t)TRANSFER_BUFFER[3]);
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

static void marshal_range(TSRange *range) {
  range->start_byte = byte_to_code_unit(range->start_byte);
  range->end_byte = byte_to_code_unit(range->end_byte);
  range->start_point.column = byte_to_code_unit(range->start_point.column);
  range->end_point.column = byte_to_code_unit(range->end_point.column);
}

static void unmarshal_range(TSRange *range) {
  range->start_byte = code_unit_to_byte(range->start_byte);
  range->end_byte = code_unit_to_byte(range->end_byte);
  range->start_point.column = code_unit_to_byte(range->start_point.column);
  range->end_point.column = code_unit_to_byte(range->end_point.column);
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
  bool is_lex_message,
  const char *message
);

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

static void call_log_callback(
  void *payload,
  TSLogType log_type,
  const char *message
) {
  tree_sitter_log_callback(log_type == TSLogTypeLex, message);
}

void ts_parser_new_wasm() {
  TSParser *parser = ts_parser_new();
  char *input_buffer = calloc(INPUT_BUFFER_SIZE, sizeof(char));
  TRANSFER_BUFFER[0] = parser;
  TRANSFER_BUFFER[1] = input_buffer;
}

void ts_parser_enable_logger_wasm(TSParser *self, bool should_log) {
  TSLogger logger = {self, should_log ? call_log_callback : NULL};
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
      unmarshal_range(&ranges[i]);
    }
    ts_parser_set_included_ranges(self, ranges, range_count);
    free(ranges);
  } else {
    ts_parser_set_included_ranges(self, NULL, 0);
  }
  return ts_parser_parse(self, old_tree, input);
}

/**********************/
/* Section - Language */
/**********************/

int ts_language_type_is_named_wasm(const TSLanguage *self, TSSymbol typeId) {
  const TSSymbolType symbolType = ts_language_symbol_type(self, typeId);
  return symbolType == TSSymbolTypeRegular;
}

int ts_language_type_is_visible_wasm(const TSLanguage *self, TSSymbol typeId) {
  const TSSymbolType symbolType = ts_language_symbol_type(self, typeId);
  return symbolType <= TSSymbolTypeAnonymous;
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

void ts_tree_get_changed_ranges_wasm(TSTree *tree, TSTree *other) {
  unsigned range_count;
  TSRange *ranges = ts_tree_get_changed_ranges(tree, other, &range_count);
  for (unsigned i = 0; i < range_count; i++) {
    marshal_range(&ranges[i]);
  }
  TRANSFER_BUFFER[0] = (const void *)range_count;
  TRANSFER_BUFFER[1] = (const void *)ranges;
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

uint32_t ts_tree_cursor_current_field_id_wasm(const TSTree *tree) {
  TSTreeCursor cursor = unmarshal_cursor(TRANSFER_BUFFER, tree);
  return ts_tree_cursor_current_field_id(&cursor);
}

void ts_tree_cursor_current_node_wasm(const TSTree *tree) {
  TSTreeCursor cursor = unmarshal_cursor(TRANSFER_BUFFER, tree);
  marshal_node(TRANSFER_BUFFER, ts_tree_cursor_current_node(&cursor));
}

/******************/
/* Section - Node */
/******************/

static TSTreeCursor scratch_cursor = {0};
static TSQueryCursor *scratch_query_cursor = NULL;

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

void ts_node_child_by_field_id_wasm(const TSTree *tree, uint32_t field_id) {
  TSNode node = unmarshal_node(tree);
  marshal_node(TRANSFER_BUFFER, ts_node_child_by_field_id(node, field_id));
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

bool symbols_contain(const uint32_t *set, uint32_t length, uint32_t value) {
  for (unsigned i = 0; i < length; i++) {
    if (set[i] == value) return true;
    if (set[i] > value) break;
  }
  return false;
}

void ts_node_descendants_of_type_wasm(
  const TSTree *tree,
  const uint32_t *symbols,
  uint32_t symbol_count,
  uint32_t start_row,
  uint32_t start_column,
  uint32_t end_row,
  uint32_t end_column
) {
  TSNode node = unmarshal_node(tree);
  TSPoint start_point = {start_row, code_unit_to_byte(start_column)};
  TSPoint end_point = {end_row, code_unit_to_byte(end_column)};
  if (end_point.row == 0 && end_point.column == 0) {
    end_point = (TSPoint) {UINT32_MAX, UINT32_MAX};
  }

  Array(const void *) result = array_new();

  // Walk the tree depth first looking for matching nodes.
  ts_tree_cursor_reset(&scratch_cursor, node);
  bool already_visited_children = false;
  while (true) {
    TSNode descendant = ts_tree_cursor_current_node(&scratch_cursor);

    if (!already_visited_children) {
      // If this node is before the selected range, then avoid
      // descending into it.
      if (point_lte(ts_node_end_point(descendant), start_point)) {
        if (ts_tree_cursor_goto_next_sibling(&scratch_cursor)) {
          already_visited_children = false;
        } else {
          if (!ts_tree_cursor_goto_parent(&scratch_cursor)) break;
          already_visited_children = true;
        }
        continue;
      }

      // If this node is after the selected range, then stop walking.
      if (point_lte(end_point, ts_node_start_point(descendant))) break;

      // Add the node to the result if its type matches one of the given
      // node types.
      if (symbols_contain(symbols, symbol_count, ts_node_symbol(descendant))) {
        array_grow_by(&result, 5);
        marshal_node(result.contents + result.size - 5, descendant);
      }

      // Continue walking.
      if (ts_tree_cursor_goto_first_child(&scratch_cursor)) {
        already_visited_children = false;
      } else if (ts_tree_cursor_goto_next_sibling(&scratch_cursor)) {
        already_visited_children = false;
      } else {
        if (!ts_tree_cursor_goto_parent(&scratch_cursor)) break;
        already_visited_children = true;
      }
    } else {
      if (ts_tree_cursor_goto_next_sibling(&scratch_cursor)) {
        already_visited_children = false;
      } else {
        if (!ts_tree_cursor_goto_parent(&scratch_cursor)) break;
      }
    }
  }

  TRANSFER_BUFFER[0] = (const void *)(result.size / 5);
  TRANSFER_BUFFER[1] = result.contents;
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

/******************/
/* Section - Query */
/******************/

void ts_query_matches_wasm(
  const TSQuery *self,
  const TSTree *tree,
  uint32_t start_row,
  uint32_t start_column,
  uint32_t end_row,
  uint32_t end_column,
  uint32_t match_limit
) {
  if (!scratch_query_cursor) scratch_query_cursor = ts_query_cursor_new();
  if (match_limit == 0) {
    ts_query_cursor_set_match_limit(scratch_query_cursor, UINT32_MAX);
  } else {
    ts_query_cursor_set_match_limit(scratch_query_cursor, match_limit);
  }

  TSNode node = unmarshal_node(tree);
  TSPoint start_point = {start_row, code_unit_to_byte(start_column)};
  TSPoint end_point = {end_row, code_unit_to_byte(end_column)};
  ts_query_cursor_set_point_range(scratch_query_cursor, start_point, end_point);
  ts_query_cursor_exec(scratch_query_cursor, self, node);

  uint32_t index = 0;
  uint32_t match_count = 0;
  Array(const void *) result = array_new();

  TSQueryMatch match;
  while (ts_query_cursor_next_match(scratch_query_cursor, &match)) {
    match_count++;
    array_grow_by(&result, 2 + 6 * match.capture_count);
    result.contents[index++] = (const void *)(uint32_t)match.pattern_index;
    result.contents[index++] = (const void *)(uint32_t)match.capture_count;
    for (unsigned i = 0; i < match.capture_count; i++) {
      const TSQueryCapture *capture = &match.captures[i];
      result.contents[index++] = (const void *)capture->index;
      marshal_node(result.contents + index, capture->node);
      index += 5;
    }
  }

  bool did_exceed_match_limit =
    ts_query_cursor_did_exceed_match_limit(scratch_query_cursor);
  TRANSFER_BUFFER[0] = (const void *)(match_count);
  TRANSFER_BUFFER[1] = result.contents;
  TRANSFER_BUFFER[2] = (const void *)(did_exceed_match_limit);
}

void ts_query_captures_wasm(
  const TSQuery *self,
  const TSTree *tree,
  uint32_t start_row,
  uint32_t start_column,
  uint32_t end_row,
  uint32_t end_column,
  uint32_t match_limit
) {
  if (!scratch_query_cursor) scratch_query_cursor = ts_query_cursor_new();
  if (match_limit == 0) {
    ts_query_cursor_set_match_limit(scratch_query_cursor, UINT32_MAX);
  } else {
    ts_query_cursor_set_match_limit(scratch_query_cursor, match_limit);
  }

  TSNode node = unmarshal_node(tree);
  TSPoint start_point = {start_row, code_unit_to_byte(start_column)};
  TSPoint end_point = {end_row, code_unit_to_byte(end_column)};
  ts_query_cursor_set_point_range(scratch_query_cursor, start_point, end_point);
  ts_query_cursor_exec(scratch_query_cursor, self, node);

  unsigned index = 0;
  unsigned capture_count = 0;
  Array(const void *) result = array_new();

  TSQueryMatch match;
  uint32_t capture_index;
  while (ts_query_cursor_next_capture(
    scratch_query_cursor,
    &match,
    &capture_index
  )) {
    capture_count++;

    array_grow_by(&result, 3 + 6 * match.capture_count);
    result.contents[index++] = (const void *)(uint32_t)match.pattern_index;
    result.contents[index++] = (const void *)(uint32_t)match.capture_count;
    result.contents[index++] = (const void *)(uint32_t)capture_index;
    for (unsigned i = 0; i < match.capture_count; i++) {
      const TSQueryCapture *capture = &match.captures[i];
      result.contents[index++] = (const void *)capture->index;
      marshal_node(result.contents + index, capture->node);
      index += 5;
    }
  }

  bool did_exceed_match_limit =
    ts_query_cursor_did_exceed_match_limit(scratch_query_cursor);
  TRANSFER_BUFFER[0] = (const void *)(capture_count);
  TRANSFER_BUFFER[1] = result.contents;
  TRANSFER_BUFFER[2] = (const void *)(did_exceed_match_limit);
}
