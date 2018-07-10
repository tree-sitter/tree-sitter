#include "tree_sitter/runtime.h"
#include "runtime/array.h"
#include "runtime/get_changed_ranges.h"
#include "runtime/subtree.h"
#include "runtime/tree_cursor.h"
#include "runtime/tree.h"

static const unsigned PARENT_CACHE_CAPACITY = 32;

TSTree *ts_tree_new(const Subtree *root, const TSLanguage *language) {
  TSTree *result = ts_malloc(sizeof(TSTree));
  result->root = root;
  result->language = language;
  result->parent_cache = NULL;
  result->parent_cache_start = 0;
  result->parent_cache_size = 0;
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
  if (self->parent_cache) ts_free(self->parent_cache);
  ts_free(self);
}

TSNode ts_tree_root_node(const TSTree *self) {
  return ts_node_new(self, self->root, self->root->padding, 0);
}

const TSLanguage *ts_tree_language(const TSTree *self) {
  return self->language;
}

void ts_tree_edit(TSTree *self, const TSInputEdit *edit) {
  SubtreePool pool = ts_subtree_pool_new(0);
  self->root = ts_subtree_edit(self->root, edit, &pool);
  self->parent_cache_start = 0;
  self->parent_cache_size = 0;
  ts_subtree_pool_delete(&pool);
}

TSRange *ts_tree_get_changed_ranges(const TSTree *self, const TSTree *other, uint32_t *count) {
  TSRange *result;
  TreeCursor cursor1, cursor2;
  TSNode root = ts_tree_root_node(self);
  ts_tree_cursor_init(&cursor1, root);
  ts_tree_cursor_init(&cursor2, root);
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

TSNode ts_tree_get_cached_parent(const TSTree *self, const TSNode *node) {
  for (uint32_t i = 0; i < self->parent_cache_size; i++) {
    uint32_t index = (self->parent_cache_start + i) % PARENT_CACHE_CAPACITY;
    ParentCacheEntry *entry = &self->parent_cache[index];
    if (entry->child == node->id) {
      return ts_node_new(self, entry->parent, entry->position, entry->alias_symbol);
    }
  }
  return ts_node_new(NULL, NULL, length_zero(), 0);
}

void ts_tree_set_cached_parent(const TSTree *_self, const TSNode *node, const TSNode *parent) {
  TSTree *self = (TSTree *)_self;
  if (!self->parent_cache) {
    self->parent_cache = ts_calloc(PARENT_CACHE_CAPACITY, sizeof(ParentCacheEntry));
  }

  uint32_t index = (self->parent_cache_start + self->parent_cache_size) % PARENT_CACHE_CAPACITY;
  self->parent_cache[index] = (ParentCacheEntry) {
    .child = node->id,
    .parent = parent->id,
    .position = {
      parent->context[0],
      {parent->context[1], parent->context[2]}
    },
    .alias_symbol = parent->context[3],
  };

  if (self->parent_cache_size == PARENT_CACHE_CAPACITY) {
    self->parent_cache_start++;
  } else {
    self->parent_cache_size++;
  }
}
