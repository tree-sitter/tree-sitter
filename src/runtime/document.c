#include "tree_sitter/parser.h"
#include "runtime/alloc.h"
#include "runtime/node.h"
#include "runtime/tree.h"
#include "runtime/parser.h"
#include "runtime/string_input.h"
#include "runtime/document.h"

TSDocument *ts_document_new() {
  TSDocument *self = ts_calloc(1, sizeof(TSDocument));
  if (!self)
    goto error;

  if (!parser_init(&self->parser))
    goto error;

  return self;

error:
  if (self)
    ts_free(self);
  return NULL;
}

void ts_document_free(TSDocument *self) {
  parser_destroy(&self->parser);
  if (self->tree)
    ts_tree_release(self->tree);
  ts_document_set_input(self,
                        (TSInput){ NULL, NULL, NULL, TSInputEncodingUTF8 });
  ts_free(self);
}

const TSLanguage *ts_document_language(TSDocument *self) {
  return self->parser.language;
}

void ts_document_set_language(TSDocument *self, const TSLanguage *language) {
  ts_document_invalidate(self);
  self->parser.language = language;
  if (self->tree) {
    ts_tree_release(self->tree);
    self->tree = NULL;
  }
}

TSLogger ts_document_logger(const TSDocument *self) {
  return self->parser.lexer.logger;
}

void ts_document_set_logger(TSDocument *self, TSLogger logger) {
  self->parser.lexer.logger = logger;
}

void ts_document_print_debugging_graphs(TSDocument *self, bool should_print) {
  self->parser.print_debugging_graphs = should_print;
}

TSInput ts_document_input(TSDocument *self) {
  return self->input;
}

void ts_document_set_input(TSDocument *self, TSInput input) {
  if (self->owns_input)
    ts_free(self->input.payload);
  self->input = input;
  self->owns_input = false;
}

void ts_document_set_input_string(TSDocument *self, const char *text) {
  ts_document_invalidate(self);
  TSInput input = ts_string_input_make(text);
  ts_document_set_input(self, input);
  if (input.payload) {
    self->owns_input = true;
  }
}

void ts_document_edit(TSDocument *self, TSInputEdit edit) {
  if (!self->tree)
    return;

  size_t max_bytes = ts_tree_total_bytes(self->tree);
  if (edit.start_byte > max_bytes)
    return;
  if (edit.bytes_removed > max_bytes - edit.start_byte)
    edit.bytes_removed = max_bytes - edit.start_byte;

  ts_tree_edit(self->tree, &edit);
}

typedef Array(TSRange) RangeArray;

#define NAME(t)                                                                 \
  ((t)                                                                          \
     ? (ts_language_symbol_name(doc->parser.language, ((TSTree *)(t))->symbol)) \
     : "<NULL>")

static bool push_change(RangeArray *results, TSPoint start, TSPoint end) {
  if (results->size > 0) {
    TSRange *last_range = array_back(results);
    if (ts_point_lte(start, last_range->end)) {
      last_range->end = end;
      return true;
    }
  }

  if (ts_point_lt(start, end)) {
    TSRange range = { start, end };
    return array_push(results, range);
  }

  return true;
}

static bool tree_path_descend(TreePath *path, TSPoint position) {
  bool did_descend;
  do {
    did_descend = false;
    TreePathEntry entry = *array_back(path);
    TSLength child_position = entry.position;
    for (size_t i = 0; i < entry.tree->child_count; i++) {
      TSTree *child = entry.tree->children[i];
      TSLength child_right_position =
        ts_length_add(child_position, ts_tree_total_size(child));
      if (ts_point_lt(position, child_right_position.extent)) {
        TreePathEntry child_entry = { child, child_position, i };
        if (child->visible) {
          array_push(path, child_entry);
          return true;
        } else if (child->visible_child_count > 0) {
          array_push(path, child_entry);
          did_descend = true;
          break;
        }
      }
      child_position = child_right_position;
    }
  } while (did_descend);
  return false;
}

static size_t tree_path_advance(TreePath *path) {
  size_t ascend_count = 0;
  while (path->size > 0) {
    TreePathEntry entry = array_pop(path);
    if (path->size == 0)
      break;
    TreePathEntry parent_entry = *array_back(path);
    if (parent_entry.tree->visible) {
      ascend_count++;
    }
    TSLength position =
      ts_length_add(entry.position, ts_tree_total_size(entry.tree));
    for (size_t i = entry.child_index + 1, n = parent_entry.tree->child_count;
         i < n; i++) {
      TSTree *next_child = parent_entry.tree->children[i];
      if (next_child->visible || next_child->visible_child_count > 0) {
        if (parent_entry.tree->visible) {
          ascend_count--;
        }
        array_push(path,
                   ((TreePathEntry){
                     .tree = next_child, .child_index = i, .position = position,
                   }));
        if (!next_child->visible)
          tree_path_descend(path, (TSPoint){ 0, 0 });
        return ascend_count;
      }
      position = ts_length_add(position, ts_tree_total_size(next_child));
    }
  }
  return ascend_count;
}

static void tree_path_ascend(TreePath *path, size_t count) {
  for (size_t i = 0; i < count; i++) {
    do {
      array_pop(path);
    } while (path->size > 0 && !array_back(path)->tree->visible);
  }
}

static void tree_path_init(TreePath *path, TSTree *tree) {
  array_clear(path);
  array_push(path,
             ((TreePathEntry){
               .tree = tree, .position = { 0, 0, { 0, 0 } }, .child_index = 0,
             }));
  if (!tree->visible)
    tree_path_descend(path, (TSPoint){ 0, 0 });
}

static bool ts_tree_get_changes(TSDocument *doc, TreePath *old_path,
                                TreePath *new_path, size_t depth,
                                RangeArray *results) {
  TSPoint position = { 0, 0 };

  while (old_path->size && new_path->size) {
    bool is_different = false;
    TSPoint next_position = position;

    TreePathEntry old_entry = *array_back(old_path);
    TreePathEntry new_entry = *array_back(new_path);
    TSTree *old_tree = old_entry.tree;
    TSTree *new_tree = new_entry.tree;
    TSSymbol old_symbol = old_tree->symbol;
    TSSymbol new_symbol = new_tree->symbol;
    size_t old_start_byte = old_entry.position.bytes;
    size_t new_start_byte = new_entry.position.bytes;
    size_t old_end_byte = old_start_byte + ts_tree_total_bytes(old_tree);
    size_t new_end_byte = new_start_byte + ts_tree_total_bytes(new_tree);
    TSPoint old_start_point =
      ts_point_add(old_entry.position.extent, old_tree->padding.extent);
    TSPoint new_start_point =
      ts_point_add(new_entry.position.extent, new_tree->padding.extent);
    TSPoint old_end_point = ts_point_add(old_start_point, old_tree->size.extent);
    TSPoint new_end_point = ts_point_add(new_start_point, new_tree->size.extent);

    // printf("At [%-2lu, %-2lu] Compare (%-20s\t [%-2lu, %-2lu] - [%lu, %lu])\tvs\t(%-20s\t [%lu, %lu] - [%lu, %lu])\t",
    //   position.row, position.column, NAME(old_tree), old_start_point.row,
    //   old_start_point.column, old_end_point.row, old_end_point.column,
    //   NAME(new_tree), new_start_point.row, new_start_point.column,
    //   new_end_point.row, new_end_point.column);

    if (ts_point_lt(position, old_start_point)) {
      if (ts_point_lt(position, new_start_point)) {
        next_position = ts_point_min(old_start_point, new_start_point);
      } else {
        is_different = true;
        next_position = old_start_point;
      }
    } else if (ts_point_lt(position, new_start_point)) {
      is_different = true;
      next_position = new_start_point;
    } else {
      if (old_tree == new_tree ||
          (!old_tree->has_changes && old_symbol == new_symbol &&
           old_start_byte == new_start_byte && old_end_byte == new_end_byte &&
           old_tree->parse_state != TS_TREE_STATE_NONE &&
           new_tree->parse_state != TS_TREE_STATE_NONE)) {
        next_position = old_end_point;
      } else if (old_symbol == new_symbol) {
        bool old_descended = tree_path_descend(old_path, position);
        bool new_descended = tree_path_descend(new_path, position);
        if (old_descended) {
          if (!new_descended) {
            tree_path_ascend(old_path, 1);
            is_different = true;
            next_position = new_end_point;
          }
        } else if (new_descended) {
          tree_path_ascend(new_path, 1);
          is_different = true;
          next_position = old_end_point;
        } else {
          next_position = ts_point_min(old_end_point, new_end_point);
        }
      } else {
        is_different = true;
        next_position = ts_point_min(old_end_point, new_end_point);
      }
    }

    bool advance_old = ts_point_lte(old_end_point, next_position);
    bool advance_new = ts_point_lte(new_end_point, next_position);

    if (advance_new && advance_old) {
      size_t old_ascend_count = tree_path_advance(old_path);
      size_t new_ascend_count = tree_path_advance(new_path);
      if (old_ascend_count > new_ascend_count) {
        tree_path_ascend(new_path, old_ascend_count - new_ascend_count);
      } else if (new_ascend_count > old_ascend_count) {
        tree_path_ascend(old_path, new_ascend_count - old_ascend_count);
      }
    } else if (advance_new) {
      size_t ascend_count = tree_path_advance(new_path);
      tree_path_ascend(old_path, ascend_count);
    } else if (advance_old) {
      size_t ascend_count = tree_path_advance(old_path);
      tree_path_ascend(new_path, ascend_count);
    }

    if (is_different)
      push_change(results, position, next_position);
    position = next_position;
  }

  return true;
}

int ts_document_parse_and_get_changed_ranges(TSDocument *self, TSRange **ranges,
                                             size_t *range_count) {
  if (ranges)
    *ranges = NULL;
  if (range_count)
    *range_count = 0;

  if (!self->input.read || !self->parser.language)
    return -1;

  TSTree *reusable_tree = self->valid ? self->tree : NULL;
  if (reusable_tree && !reusable_tree->has_changes)
    return 0;

  TSTree *tree = parser_parse(&self->parser, self->input, reusable_tree);
  if (!tree)
    return -1;

  if (self->tree) {
    TSTree *old_tree = self->tree;
    self->tree = tree;

    if (ranges && range_count) {
      RangeArray result = { 0, 0, 0 };
      tree_path_init(&self->parser.tree_path1, old_tree);
      tree_path_init(&self->parser.tree_path2, tree);
      if (!ts_tree_get_changes(self, &self->parser.tree_path1,
                               &self->parser.tree_path2, 0, &result))
        return -1;
      *ranges = result.contents;
      *range_count = result.size;
    }

    ts_tree_release(old_tree);
  }

  self->tree = tree;
  self->parse_count++;
  self->valid = true;
  return 0;
}

int ts_document_parse(TSDocument *self) {
  return ts_document_parse_and_get_changed_ranges(self, NULL, NULL);
}

void ts_document_invalidate(TSDocument *self) {
  self->valid = false;
}

TSNode ts_document_root_node(const TSDocument *self) {
  TSNode result = ts_node_make(self->tree, 0, 0, 0);
  while (result.data && !((TSTree *)result.data)->visible)
    result = ts_node_named_child(result, 0);
  return result;
}

size_t ts_document_parse_count(const TSDocument *self) {
  return self->parse_count;
}
