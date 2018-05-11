#include "tree_sitter/runtime.h"
#include "runtime/array.h"
#include "runtime/get_changed_ranges.h"
#include "runtime/subtree.h"
#include "runtime/tree_cursor.h"
#include "runtime/tree.h"

TSTree *ts_tree_new(const Subtree *root, const TSLanguage *language) {
  TSTree *result = ts_malloc(sizeof(TSTree));
  result->root = root;
  result->language = language;
  return result;
}

TSTree *ts_tree_copy(const TSTree *self) {
  ts_subtree_retain(self->root);
  return ts_tree_new(self->root, self->language);
}

void ts_tree_delete(TSTree *self) {
  SubtreePool pool = ts_subtree_pool_new(0);
  ts_subtree_release(&pool, self->root);
  ts_subtree_pool_delete(&pool);
  ts_free(self);
}

TSNode ts_tree_root_node(const TSTree *self) {
  return (TSNode) {
    .subtree = self->root,
    .tree = self,
    .position = {0, 0},
    .byte = 0,
    .alias_symbol = 0,
  };
}

void ts_tree_edit(TSTree *self, const TSInputEdit *edit) {
  SubtreePool pool = ts_subtree_pool_new(0);
  self->root = ts_subtree_edit(self->root, edit, &pool);
  assert(pool.tree_stack.capacity == 0 && pool.free_trees.capacity == 0);
}

TSRange *ts_tree_get_changed_ranges(const TSTree *self, const TSTree *other, uint32_t *count) {
  TSRange *result;
  TSTreeCursor cursor1, cursor2;
  ts_tree_cursor_init(&cursor1, self);
  ts_tree_cursor_init(&cursor2, self);
  *count = ts_subtree_get_changed_ranges(
    self->root, other->root, &cursor1, &cursor2,
    self->language, &result
  );
  array_delete(&cursor1.stack);
  array_delete(&cursor2.stack);
  return result;
}

void ts_tree_print_dot_graph(const TSTree *self, FILE *file) {
  ts_subtree_print_dot_graph(self->root, self->language, file);
}
