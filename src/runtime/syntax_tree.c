#include "tree_sitter/runtime.h"
#include "runtime/alloc.h"
#include "runtime/array.h"
#include "runtime/atomic.h"
#include "runtime/language.h"
#include "runtime/length.h"
#include "runtime/syntax_tree.h"

#define TREE_HEIGHT_SLICE UINT16_MAX

uint32_t TREE_BRANCHING_FACTOR = DEFAULT_TREE_BRANCHING_FACTOR;

struct SyntaxNode {
  uint32_t child_count;
  uint32_t next_sibling_node_count;
  uint32_t node_count_to_parent;
  union {
    struct {
      Length padding;
      Length size;
    };
    struct {
      uint32_t node_count;
      uint32_t visible_child_count;
      uint32_t named_child_count;
      uint32_t first_child_node_count;
      uint32_t alias_sequence_id;
      int32_t dynamic_precedence;
    };
  };
  TSSymbol symbol;
  TSSymbol first_leaf_symbol;
  TSLexMode first_leaf_lex_mode;
  TSSymbol alias_symbol : 15;
  bool alias_is_named : 1;
  bool is_visible : 1;
  bool is_named : 1;
  bool has_changes : 1;
};

struct SyntaxTree {
  SyntaxTree *previous;
  volatile uint32_t ref_count;
  uint16_t height;
  uint16_t count;
};

typedef struct {
  Length size;
  uint32_t node_count;
} SyntaxTreeSummary;

typedef struct {
  SyntaxTree base;
  SyntaxNode entries[DEFAULT_TREE_BRANCHING_FACTOR];
} SyntaxTreeLeaf;

typedef struct {
  SyntaxTree base;
  SyntaxTree *children[DEFAULT_TREE_BRANCHING_FACTOR];
  SyntaxTreeSummary summaries[DEFAULT_TREE_BRANCHING_FACTOR];
} SyntaxTreeInternal;

typedef struct {
  SyntaxTree base;
  uint32_t start_index;
  uint32_t end_index;
} SyntaxTreeSlice;

typedef struct {
  SyntaxTree *tree;
  uint32_t index;
  Length position;
} TreeIteratorEntry;

typedef struct {
  Array(TreeIteratorEntry) entries;
  uint32_t index;
} TreeIterator;

typedef struct {
  SyntaxTree *tree;
  uint16_t start_index;
  uint16_t end_index;
} TreeIteratorItem;

typedef struct {
  SyntaxNode *node;
  uint32_t index;
} ChildStackEntry;

typedef struct {
  const TSLanguage *language;
  Array(ChildStackEntry) child_stack;
  Array(SyntaxTree *) rightmost_trees;
  uint32_t node_count;
} TreeBuilder;

typedef struct {
  Length start;
  Length added;
  Length removed;
} Edit;

typedef Array(uint32_t) IndexSet;

// IndexSet

static void ts_index_set_insert(IndexSet *self, uint32_t value) {
  for (unsigned i = 0; i < self->size; i++) {
    if (self->contents[i] == value) return;
    if (self->contents[i] > value) {
      array_insert(self, i, value);
      return;
    }
  }
  array_push(self, value);
}

// SyntaxTreeSummary

static SyntaxTreeSummary ts_syntax_tree_summary_new(const SyntaxNode *node) {
  return (SyntaxTreeSummary) {
    .node_count = 1,
    .size = node->child_count == 0
      ? length_add(node->padding, node->size)
      : length_zero(),
  };
}

static void ts_syntax_tree_summary_add(SyntaxTreeSummary *self, SyntaxTreeSummary other) {
  self->node_count += other.node_count;
  self->size = length_add(self->size, other.size);
}

// SyntaxTree

static SyntaxTreeLeaf *ts_syntax_tree_new_leaf() {
  SyntaxTreeLeaf *self = ts_malloc(sizeof(SyntaxTreeLeaf));
  self->base = (SyntaxTree) {
    .ref_count = 1,
    .count = 0,
    .height = 0,
  };
  return self;
}

static SyntaxTreeInternal *ts_syntax_tree_new_internal(uint16_t height) {
  SyntaxTreeInternal *self = ts_malloc(sizeof(SyntaxTreeInternal));
  self->base = (SyntaxTree) {
    .ref_count = 1,
    .count = 0,
    .height = height,
  };
  return self;
}

static SyntaxTreeSlice *ts_syntax_tree_new_slice(uint32_t start_index, uint32_t end_index) {
  SyntaxTreeSlice *self = ts_malloc(sizeof(SyntaxTreeSlice));
  self->base = (SyntaxTree) {
    .ref_count = 1,
    .count = 0,
    .height = TREE_HEIGHT_SLICE,
  };
  self->start_index = start_index;
  self->end_index = end_index;
  return self;
}

static void ts_syntax_tree_retain(const SyntaxTree *self) {
  atomic_inc(&((SyntaxTree *)self)->ref_count);
}

void ts_syntax_tree_delete(SyntaxTree *self) {
  if (atomic_dec(&self->ref_count) == 0) {
    if (self->height > 0) {
      for (unsigned i = 0; i < self->count; i++) {
        ts_syntax_tree_delete(((SyntaxTreeInternal *)self)->children[i]);
      }
    }
    ts_free(self);
  }
}

static SyntaxTreeSummary ts_syntax_tree_summarize(const SyntaxTree *self,
                                                  uint32_t start, uint32_t end) {
  SyntaxTreeSummary result = {
    .node_count = 0,
    .size = length_zero(),
  };
  if (self->height == 0) {
    SyntaxTreeLeaf *leaf = (SyntaxTreeLeaf *)self;
    for (unsigned i = start; i < end; i++) {
      ts_syntax_tree_summary_add(&result, ts_syntax_tree_summary_new(&leaf->entries[i]));
    }
  } else {
    SyntaxTreeInternal *internal = (SyntaxTreeInternal *)self;
    for (unsigned i = start; i < end; i++) {
      ts_syntax_tree_summary_add(&result, internal->summaries[i]);
    }
  }
  return result;
}

static bool ts_syntax_tree_push_node(SyntaxTreeLeaf *self, SyntaxNode *entry) {
  if (self->base.count < TREE_BRANCHING_FACTOR || self->base.ref_count > 1) {
    self->entries[self->base.count] = *entry;
    self->base.count++;
    return true;
  } else {
    return false;
  }
}

static bool ts_syntax_tree_push_child(SyntaxTreeInternal *self, SyntaxTree *child,
                                      const SyntaxTreeSummary *summary) {
  if (self->base.count < TREE_BRANCHING_FACTOR || self->base.ref_count > 1) {
    assert(child->height == self->base.height - 1);
    assert(child->count > 0);
    self->children[self->base.count] = child;
    self->summaries[self->base.count] = *summary;
    self->base.count++;
    return true;
  } else {
    return false;
  }
}

static bool ts_syntax_tree_push_slice(SyntaxTree *self, SyntaxTree *other,
                                      uint32_t start, uint32_t end) {
  if (self->count + end - start > TREE_BRANCHING_FACTOR || self->ref_count > 1) {
    return false;
  }

  assert(self->height == other->height);
  if (self->height == 0) {
    SyntaxTreeLeaf *leaf = (SyntaxTreeLeaf *)self;
    SyntaxTreeLeaf *other_leaf = (SyntaxTreeLeaf *)other;
    memcpy(
      &leaf->entries[leaf->base.count],
      &other_leaf->entries[start],
      (end - start) * sizeof(SyntaxNode)
    );
    leaf->base.count += end - start;
  } else {
    SyntaxTreeInternal *internal = (SyntaxTreeInternal *)self;
    SyntaxTreeInternal *other_internal = (SyntaxTreeInternal *)other;
    for (unsigned i = 0; i < (end - start); i++) {
      SyntaxTree *child = other_internal->children[start + i];
      ts_syntax_tree_retain(child);
      internal->children[internal->base.count + i] = child;
    }
    memcpy(
      &internal->summaries[internal->base.count],
      &other_internal->summaries[start],
      (end - start) * sizeof(SyntaxTreeSummary)
    );
    internal->base.count += end - start;
  }
  return true;
}

static SyntaxTree *ts_syntax_tree_copy_slice(SyntaxTree *self, uint32_t start, uint32_t end) {
  if (self->height == 0) {
    SyntaxTreeLeaf *leaf = ts_syntax_tree_new_leaf();
    SyntaxTree *result = &leaf->base;
    ts_syntax_tree_push_slice(result, self, start, end);
    return result;
  } else {
    SyntaxTreeInternal *internal = ts_syntax_tree_new_internal(self->height);
    SyntaxTree *result = &internal->base;
    ts_syntax_tree_push_slice(result, self, start, end);
    SyntaxTree **last = &internal->children[result->count - 1];
    *last = ts_syntax_tree_copy_slice(*last, 0, (*last)->count);
    return result;
  }
}

static SyntaxTree *ts_syntax_tree_copy(SyntaxTree *self) {
  SyntaxTree *result;
  if (self->height == 0) {
    result = (SyntaxTree *)ts_syntax_tree_new_leaf();
  } else {
    result = (SyntaxTree *)ts_syntax_tree_new_internal(self->height);
  }
  ts_syntax_tree_push_slice(result, self, 0, self->count);
  return result;
}

static void ts_syntax_tree_update_last_summary(SyntaxTreeInternal *self,
                                               const SyntaxTreeSummary *summary) {
  ts_syntax_tree_summary_add(&self->summaries[self->base.count - 1], *summary);
}

static SyntaxTree *ts_syntax_tree_last_child(SyntaxTreeInternal *self) {
  return self->children[self->base.count - 1];
}

TSNode2 ts_syntax_tree_node_at_index(const SyntaxTree *self, uint32_t goal_index) {
  const SyntaxTree *tree = self;
  uint32_t index = 0;
  while (tree->height > 0) {
    const SyntaxTreeInternal *internal = (const SyntaxTreeInternal *)tree;
    for (unsigned i = 0; i < internal->base.count; i++) {
      uint32_t next_index = index + internal->summaries[i].node_count;
      SyntaxTree *child = internal->children[i];
      if (next_index > goal_index || i == internal->base.count - 1u) {
        tree = child;
        break;
      }
      index = next_index;
    }
  }
  const SyntaxTreeLeaf *leaf = (const SyntaxTreeLeaf *)tree;
  uint32_t last_index = index + leaf->base.count - 1;
  if (goal_index > last_index) goal_index = last_index;
  return (TSNode2) {
    .tree = self,
    .node = &leaf->entries[goal_index - index],
    .index = goal_index,
    .byte = 0,
    .row = 0,
  };
}

TSNode2 ts_syntax_tree_root_node(const SyntaxTree *self) {
  return ts_syntax_tree_node_at_index(self, UINT32_MAX);
}

static SyntaxTree *ts_syntax_tree__edit(SyntaxTree *self, const Edit *edit,
                                 uint32_t start_index,
                                 IndexSet *internal_node_indices,
                                 uint32_t *edited_internal_node_count) {
  SyntaxTree *result;
  Length edit_old_end = edit ? length_add(edit->start, edit->removed) : length_zero();

  // If we see a reference count of one here, then this tree is not being used by any other
  // threads, so it is safe to mutate. Otherwise, we copy the tree.
  if (self->ref_count == 1) {
    result = self;
  } else {
    result = ts_syntax_tree_copy(self);
    ts_syntax_tree_delete(self);
  }

  if (result->height == 0) {
    SyntaxTreeLeaf *leaf = (SyntaxTreeLeaf *)result;
    Length position = {};
    for (unsigned i = 0; i < leaf->base.count; i++) {
      SyntaxNode *node = &leaf->entries[i];

      // Mark leaf nodes intersecting the edit as having changes and resize them.
      if (node->child_count == 0) {
        Length total_size = length_add(node->padding, node->size);
        Length end_position = length_add(position, total_size);

        if (edit && end_position.bytes >= edit->start.bytes) {
          Edit node_edit;
          if (edit->start.bytes < position.bytes) {
            node_edit = (Edit) {{}, {}, length_sub(edit_old_end, position)};
          } else {
            node_edit = (Edit) {length_sub(edit->start, position), edit->added, edit->removed};
          }

          if (edit_old_end.bytes > end_position.bytes) {
            node_edit.removed = length_sub(total_size, node_edit.start);
          }

          Length node_edit_old_end = length_add(node_edit.start, node_edit.removed);
          Length node_edit_new_end = length_add(node_edit.start, node_edit.added);

          node->has_changes = true;
          ts_index_set_insert(internal_node_indices, start_index + i + node->node_count_to_parent);
          if (node_edit_old_end.bytes <= node->padding.bytes) {
            node->padding = length_add(node_edit_new_end, length_sub(node->padding, node_edit_old_end));
          } else if (node_edit.start.bytes < node->padding.bytes) {
            node->size = length_sub(node->size, length_sub(node_edit_old_end, node->padding));
            node->padding = node_edit_new_end;
          } else if (node_edit.start.bytes == node->padding.bytes && node_edit.removed.bytes == 0) {
            node->padding = length_add(node->padding, edit->added);
          } else {
            node->size = length_sub(
              length_add(node_edit_new_end, length_sub(total_size, node_edit_old_end)),
              node->padding
            );
          }

          if (end_position.bytes >= edit_old_end.bytes) edit = NULL;
        }

        position = end_position;
      }

      // Mark internal nodes intersecting the edit as having changes.
      else if (
        *edited_internal_node_count < internal_node_indices->size &&
        internal_node_indices->contents[*edited_internal_node_count] == start_index + i
      ) {
        node->has_changes = true;
        *edited_internal_node_count += 1;
        ts_index_set_insert(internal_node_indices, start_index + i + node->node_count_to_parent);
      }
    }
  } else {
    SyntaxTreeInternal *internal = (SyntaxTreeInternal *)result;
    Length position = {};
    uint32_t index = start_index;
    for (unsigned i = 0; i < internal->base.count; i++) {
      SyntaxTree **child = &internal->children[i];
      SyntaxTreeSummary *summary = &internal->summaries[i];
      Length end_position = length_add(position, summary->size);
      uint32_t next_index = index + summary->node_count;
      if (position.bytes > edit_old_end.bytes) edit = NULL;

      if (edit && end_position.bytes > edit->start.bytes) {
        Edit child_edit;
        if (edit->start.bytes < position.bytes) {
          child_edit = (Edit) {{}, {}, length_sub(edit_old_end, position)};
        } else {
          child_edit = (Edit) {length_sub(edit->start, position), edit->added, edit->removed};
        }

        if (edit_old_end.bytes > end_position.bytes) {
          child_edit.removed = length_sub(summary->size, child_edit.start);
        }

        summary->size = length_add(
          length_add(
            child_edit.start,
            child_edit.added
          ),
          length_sub(
            summary->size,
            length_add(
              child_edit.start,
              child_edit.removed
            )
          )
        );

        *child = ts_syntax_tree__edit(
          *child, &child_edit, index,
          internal_node_indices, edited_internal_node_count
        );
      } else if (
        *edited_internal_node_count < internal_node_indices->size &&
        internal_node_indices->contents[*edited_internal_node_count] < next_index
      ) {
        *child = ts_syntax_tree__edit(
          *child, NULL, index,
          internal_node_indices, edited_internal_node_count
        );
      }

      position = end_position;
      index = next_index;
    }
  }

  return result;
}

SyntaxTree *ts_syntax_tree_edit(SyntaxTree *self, TSInputEdit input_edit) {
  IndexSet internal_node_indices = {};
  uint32_t edited_internal_node_count = 0;
  Edit edit = (Edit) {
    .start = {input_edit.start_byte, input_edit.start_point},
    .added = {input_edit.bytes_added, input_edit.extent_added},
    .removed = {input_edit.bytes_removed, input_edit.extent_removed},
  };
  SyntaxTree *result = ts_syntax_tree__edit(
    self, &edit, 0,
    &internal_node_indices, &edited_internal_node_count
  );
  array_delete(&internal_node_indices);
  return result;
}

// TreeIterator

static TreeIterator ts_tree_iterator_new(SyntaxTree *tree) {
  TreeIterator self = { .entries = array_new(), .index = 0 };
  while (tree) {
    array_push(&self.entries, ((TreeIteratorEntry){ .tree = tree, .index = 0 }));
    if (tree->height > 0) {
      tree = ((SyntaxTreeInternal *)tree)->children[0];
    } else {
      tree = NULL;
    }
  }
  return self;
}

static void ts_tree_iterator_delete(TreeIterator *self) {
  if (self->entries.contents) array_delete(&self->entries);
}

static void ts_tree_iterator_seek(TreeIterator *self, uint32_t goal_index) {
  SyntaxTree *tree = array_front(&self->entries)->tree;
  array_clear(&self->entries);
  uint32_t index = 0;

  while (tree) {
    if (tree->height == 0) {
      uint32_t last_index = index + tree->count - 1;
      if (goal_index > last_index) goal_index = last_index;
      self->index = goal_index;
      array_push(&self->entries, ((TreeIteratorEntry){
        .tree = tree,
        .index = goal_index - index,
      }));
      break;
    } else {
      const SyntaxTreeInternal *internal = (const SyntaxTreeInternal *)tree;
      for (unsigned i = 0; i < internal->base.count; i++) {
        uint32_t next_index = index + internal->summaries[i].node_count;
        SyntaxTree *child = internal->children[i];
        if (next_index > goal_index) {
          array_push(&self->entries, ((TreeIteratorEntry){
            .tree = tree,
            .index = i,
          }));
          tree = child;
          break;
        }
        index = next_index;
      }
    }
  }
}

static uint32_t ts_tree_iterator_prepare(TreeIterator *self) {
  // Ensure that the iterators is not at the end of a subtree.
  TreeIteratorEntry *last_entry = array_back(&self->entries);
  uint32_t ascend_count = 0;
  while (last_entry->index == last_entry->tree->count) {
    self->entries.size--;
    last_entry--;
    last_entry->index++;
    ascend_count++;
  }

  // Descend to a leaf.
  while (last_entry && last_entry->tree->height > 0) {
    SyntaxTreeInternal *internal = (SyntaxTreeInternal *)last_entry->tree;
    array_push(&self->entries, ((TreeIteratorEntry){
      .tree = internal->children[last_entry->index],
      .index = 0
    }));
    last_entry++;
  }

  return ascend_count;
}

static TreeIteratorItem ts_tree_iterator_advance(TreeIterator *self, uint32_t goal_index) {
  uint32_t goal_node_count = goal_index - self->index;

  // If only a subset of this leaf is needed, advance to the end of this leaf.
  // Otherwise, advance within a larger subtree.
  TreeIteratorEntry *last_entry = array_back(&self->entries);
  uint32_t node_count = last_entry->tree->count - last_entry->index;
  if (node_count > goal_node_count) node_count = goal_node_count;
  if (last_entry->index > 0 || node_count >= goal_node_count) {
    uint32_t start_index = last_entry->index;
    SyntaxTree *tree = last_entry->tree;
    self->index += node_count;
    last_entry->index += node_count;
    ts_tree_iterator_prepare(self);
    return (TreeIteratorItem) {
      .tree = tree,
      .start_index = start_index,
      .end_index = start_index + node_count,
    };
  }

  // Walk up the tree to find which subtree to advance within.
  for (uint32_t i = self->entries.size - 2; i + 1 > 0; i--) {
    TreeIteratorEntry *entry = &self->entries.contents[i];
    SyntaxTreeInternal *internal = (SyntaxTreeInternal *)entry->tree;

    // Determine if one a child of this tree contains the given index.
    uint32_t node_count = 0;
    uint32_t end_index = internal->base.count;
    for (unsigned j = entry->index; j < internal->base.count; j++) {
      uint32_t next_node_count = node_count + internal->summaries[j].node_count;
      if (next_node_count > goal_node_count) {
        end_index = j;
        break;
      }
      node_count = next_node_count;
    }

    // If only a subset of this subtree is needed, advance to the end of this subtree.
    // Otherwise, advance at a higher level in the tree.
    if (entry->index > 0 || node_count >= goal_node_count) {
      uint32_t start_index = last_entry->index;
      SyntaxTree *tree = last_entry->tree;
      last_entry->index = end_index;
      self->entries.size = i + 1;
      self->index += node_count;
      ts_tree_iterator_prepare(self);
      return (TreeIteratorItem) {
        .tree = tree,
        .start_index = start_index,
        .end_index = end_index,
      };
    }
  }

  assert(!"Tried to walk tree iterator past its end");
}

// TreeBuilder

static TreeBuilder ts_tree_builder_new(const TSLanguage *language) {
  TreeBuilder self = {
    .language = language,
    .child_stack = array_new(),
    .rightmost_trees = array_new(),
    .node_count = 0,
  };
  array_push(&self.rightmost_trees, NULL);
  return self;
}

static SyntaxTree *ts_tree_builder_to_tree(TreeBuilder *self) {
  SyntaxTree *result = *array_back(&self->rightmost_trees);
  array_delete(&self->rightmost_trees);
  array_delete(&self->child_stack);
  return result;
}

static void ts_tree_builder_grow(TreeBuilder *self, uint32_t height) {
  while (self->rightmost_trees.size < height) {
    SyntaxTree *root = *array_back(&self->rightmost_trees);
    SyntaxTreeInternal *new_root = ts_syntax_tree_new_internal(self->rightmost_trees.size);
    SyntaxTreeSummary summary = ts_syntax_tree_summarize(root, 0, root->count);
    ts_syntax_tree_push_child(new_root, root, &summary);
    array_push(&self->rightmost_trees, &new_root->base);
  }
}

static void ts_tree_builder_populate_new_node(TreeBuilder *self, SyntaxNode *node) {
  TSSymbolMetadata metadata = ts_language_symbol_metadata(self->language, node->symbol);
  node->is_visible = metadata.visible;
  node->is_named = metadata.named;

  if (node->child_count > 0) {
    assert(self->child_stack.size >= node->child_count);

    // Pop this node's children off of the child stack.
    self->child_stack.size -= node->child_count;
    ChildStackEntry *children = &self->child_stack.contents[self->child_stack.size];

    // Assign the properties of this node that derive from its children, and the properties
    // of the children that derive from their context.
    node->node_count = 1;
    SyntaxNode *prev_child = NULL;
    for (unsigned i = 0; i < node->child_count; i++) {
      SyntaxNode *child = children[i].node;
      uint32_t child_index = children[i].index;
      uint32_t child_node_count = child->child_count > 0 ? child->node_count : 1;

      if (prev_child) {
        prev_child->next_sibling_node_count = child_node_count;
      } else {
        node->first_child_node_count = child_node_count;
      }

      if (child->is_visible) {
        node->visible_child_count++;
        if (child->is_named) node->named_child_count++;
      } else if (child->child_count > 0) {
        node->visible_child_count += child->visible_child_count;
        node->named_child_count += child->named_child_count;
      }

      node->node_count += child_node_count;

      child->node_count_to_parent = self->node_count - child_index;
      prev_child = child;
    }
  }

  // Add this node to the child stack.
  array_push(&self->child_stack, ((ChildStackEntry){node, self->node_count++}));
}

static void ts_tree_builder_push_tree(TreeBuilder *self, SyntaxTree *tree,
                                      uint32_t initial_height, SyntaxTreeSummary *summary) {
  // Walk up the existing tree to find a subtree where the new tree can be inserted.
  // Continue walking upward after the insertion is complete in order to update each
  // tree's summary.
  SyntaxTree *tree_to_push = tree;
  for (unsigned height = initial_height + 1; height < self->rightmost_trees.size; height++) {
    SyntaxTreeInternal *internal = (SyntaxTreeInternal *)self->rightmost_trees.contents[height];
    if (tree_to_push) {
      if (ts_syntax_tree_push_child(internal, tree_to_push, summary)) {
        tree_to_push = NULL;
      } else {
        SyntaxTreeInternal *parent = ts_syntax_tree_new_internal(height);
        ts_syntax_tree_push_child(parent, tree_to_push, summary);
        tree_to_push = &parent->base;
        self->rightmost_trees.contents[height] = tree_to_push;
      }
    } else {
      ts_syntax_tree_update_last_summary(internal, summary);
    }
  }

  // If the tree could not be inserted into any existing tree, create a new root node
  // to contain the tree.
  if (tree_to_push) {
    SyntaxTreeInternal *root = ts_syntax_tree_new_internal(self->rightmost_trees.size);
    ts_syntax_tree_push_child(root, tree_to_push, summary);
    array_push(&self->rightmost_trees, &root->base);
  }

  // Update the rightmost trees to reflect the addition of the new tree.
  if (tree) {
    SyntaxTree *descendant = tree;
    for (unsigned height = tree->height;; height--) {
      self->rightmost_trees.contents[height] = descendant;
      if (height > 0) {
        descendant = ts_syntax_tree_last_child((SyntaxTreeInternal *)descendant);
      } else {
        break;
      }
    }
  }
}

static void ts_tree_builder_push_leaf(TreeBuilder *self, SyntaxTreeLeaf *leaf) {
  // Populate the derived state of each node stored in this leaf.
  for (unsigned j = 0; j < leaf->base.count; j++) {
    SyntaxNode *node = &leaf->entries[j];
    ts_tree_builder_populate_new_node(self, node);
  }

  // Add the leaf to the tree.
  SyntaxTree *tree = &leaf->base;
  SyntaxTreeSummary summary = ts_syntax_tree_summarize(tree, 0, tree->count);
  ts_tree_builder_push_tree(self, tree, tree->height, &summary);
}

static void ts_tree_builder_reuse_chunk(TreeBuilder *self, SyntaxTree *tree,
                                               uint32_t start_index, uint32_t end_index,
                                               bool is_last) {
  SyntaxTreeSummary summary = ts_syntax_tree_summarize(tree, start_index, end_index);

  // When pushing an entire subtree that doesn't contain the final node
  // being reused, reuse the subtree itself without copying.
  if (!is_last && start_index == 0 && end_index == tree->count) {
    ts_syntax_tree_retain(tree);
    ts_tree_builder_push_tree(self, tree, tree->height, &summary);
  } else {
    SyntaxTree *existing_tree = self->rightmost_trees.contents[tree->height];

    // Try to insert these entries into an existing subtree.
    if (existing_tree && ts_syntax_tree_push_slice(existing_tree, tree, start_index, end_index)) {
      ts_tree_builder_push_tree(self, NULL, tree->height, &summary);
    }

    // Otherwise, copy the tree so that its final entry can be mutated.
    else {
      tree = ts_syntax_tree_copy_slice(tree, start_index, end_index);
      ts_tree_builder_push_tree(self, tree, tree->height, &summary);
    }
  }

  // Add the final entry to the child stack.
  if (is_last) {
    SyntaxTree *leaf = self->rightmost_trees.contents[0];
    SyntaxNode *root_node = (SyntaxNode *)ts_syntax_tree_root_node(leaf).node;
    self->node_count += root_node->node_count;
    array_push(&self->child_stack, ((ChildStackEntry) { root_node, self->node_count - 1 }));
  }
}

// TSNode

Length ts_syntax_tree__position_at_index(const SyntaxTree *tree, uint32_t goal_index,
                                         SyntaxNode *out_node) {
  uint32_t index = 0;
  Length result = {};
  for (;;) {
    if (tree->height == 0) {
      SyntaxTreeLeaf *leaf = (SyntaxTreeLeaf *)tree;
      SyntaxNode *node = NULL;
      for (unsigned i = 0; i < leaf->base.count; i++) {
        node = &leaf->entries[i];
        if (index == goal_index) break;
        index++;
        if (node->child_count == 0) {
          result = length_add(result, length_add(node->padding, node->size));
        }
      }
      *out_node = *node;
      return result;
    } else {
      SyntaxTreeInternal *internal = (SyntaxTreeInternal *)tree;
      for (unsigned i = 0; i < internal->base.count; i++) {
        uint32_t next_index = index + internal->summaries[i].node_count;
        if (next_index > goal_index || i == internal->base.count - 1) {
          tree = internal->children[i];
          break;
        }
        index = next_index;
        result = length_add(result, internal->summaries[i].size);
      }
    }
  }
}

TSPoint ts_node2_start_point(const TSNode2 *self) {
  SyntaxNode node;
  if (self->node->child_count > 0) {
    TSPoint result = ts_syntax_tree__position_at_index(
      self->tree,
      self->index - self->node->node_count + 1,
      &node
    ).extent;
    return point_add(result, node.padding.extent);
  } else {
    TSPoint result = ts_syntax_tree__position_at_index(
      self->tree,
      self->index,
      &node
    ).extent;
    return point_add(result, node.padding.extent);
  }
}

TSPoint ts_node2_end_point(const TSNode2 *self) {
  SyntaxNode node;
  return ts_syntax_tree__position_at_index(self->tree, self->index + 1, &node).extent;
}

TSSymbol ts_node2_symbol(const TSNode2 *self) {
  return self->node->symbol;
}

uint32_t ts_node2_child_count(const TSNode2 *self) {
  return self->node->child_count;
}

static TSNode2 ts_node2__first_immediate_child(const TSNode2 *self) {
  return ts_syntax_tree_node_at_index(
    self->tree,
    self->index - self->node->node_count + self->node->first_child_node_count
  );
}

static TSNode2 ts_node2__next_immediate_sibling(const TSNode2 *self) {
  return ts_syntax_tree_node_at_index(
    self->tree,
    self->index + self->node->next_sibling_node_count
  );
}

TSNode2 ts_node2_child(const TSNode2 *self, unsigned goal_index) {
  if (self->node->child_count == 0 || goal_index >= self->node->visible_child_count) {
    return (TSNode2) { .node = NULL };
  }

  unsigned child_index = 0;
  TSNode2 child = ts_node2__first_immediate_child(self);

  bool did_descend = true;
  while (did_descend) {
    did_descend = false;

    for (;;) {
      if (child.node->is_visible) {
        if (child_index == goal_index) {
          return child;
        } else {
          child_index++;
        }
      } else {
        unsigned grandchild_index = goal_index - child_index;
        unsigned grandchild_count = child.node->child_count > 0 ? child.node->visible_child_count : 0;
        if (grandchild_count > grandchild_index) {
          did_descend = true;
          goal_index = grandchild_index;
          child = ts_node2__first_immediate_child(&child);
          break;
        } else {
          child_index += grandchild_count;
        }
      }

      child = ts_node2__next_immediate_sibling(&child);
    }
  }

  assert(false);
}

TSNode2 ts_node2_parent(const TSNode2 *self) {
  TSNode2 result = *self;
  do {
    result = ts_syntax_tree_node_at_index(
      result.tree,
      result.index + result.node->node_count_to_parent
    );
  } while (!result.node->is_visible);
  return result;
}

bool ts_node2_has_changes(const TSNode2 *self) {
  return self->node->has_changes;
}

// NodeList

NodeList ts_node_list_new() {
  return (NodeList) { .last = NULL };
}

void ts_node_list_delete(NodeList *self) {
  SyntaxTree *tree = self->last;
  while (tree) {
    if (atomic_dec(&tree->ref_count) == 0) {
      SyntaxTree *previous = tree->previous;
      ts_free(tree);
      tree = previous;
    } else {
      tree = NULL;
    }
  }
}

void ts_node_list__push(NodeList *self, SyntaxNode *node) {
  if (!self->last || self->last->height != 0 ||
      !ts_syntax_tree_push_node((SyntaxTreeLeaf *)self->last, node)) {
    SyntaxTreeLeaf *last = ts_syntax_tree_new_leaf();
    last->base.previous = self->last,
    ts_syntax_tree_push_node(last, node);
    self->last = &last->base;
    self->count++;
  }
}

void ts_node_list_push_leaf(NodeList *self, TSSymbol symbol, Length padding, Length size) {
  SyntaxNode node = {
    .symbol = symbol,
    .child_count = 0,
    .padding = padding,
    .size = size,
  };
  ts_node_list__push(self, &node);
}

void ts_node_list_push_parent(NodeList *self, TSSymbol symbol, uint32_t child_count) {
  SyntaxNode node = {
    .symbol = symbol,
    .child_count = child_count,
  };
  ts_node_list__push(self, &node);
}

void ts_node_list_reuse(NodeList *self, TSNode2 node) {
  SyntaxTreeSlice *last = ts_syntax_tree_new_slice(
    node.index + 1 - node.node->node_count,
    node.index + 1
  );
  last->base.previous = self->last;
  self->last = &last->base;
  self->count++;
}

SyntaxTree *ts_node_list_to_tree(NodeList *self, const TSLanguage *language, SyntaxTree *old_tree) {
  assert(self->last && self->count > 0);

  // Convert the list into an array so that it can be processed from left to right.
  Array(SyntaxTree *) parts = array_new();
  array_reserve(&parts, self->count);
  parts.size = self->count;
  SyntaxTree *tree = self->last;
  uint32_t index = self->count - 1;
  while (tree) {
    parts.contents[index--] = tree;
    SyntaxTree *previous = tree->previous;
    tree->previous = NULL;
    tree = previous;
  }

  // Assemble the leaves and reused slices into a new tree.
  TreeBuilder builder = ts_tree_builder_new(language);
  TreeIterator old_tree_iterator = ts_tree_iterator_new(old_tree);
  for (unsigned i = 0, n = parts.size; i < n; i++) {
    SyntaxTree *part = parts.contents[i];

    if (part->height == 0) {
      ts_tree_builder_push_leaf(&builder, (SyntaxTreeLeaf *)part);
    } else {
      SyntaxTreeSlice *slice = (SyntaxTreeSlice *)part;

      ts_tree_iterator_seek(&old_tree_iterator, slice->start_index);
      for (;;) {
        TreeIteratorItem chunk = ts_tree_iterator_advance(&old_tree_iterator, slice->end_index);
        bool is_last = old_tree_iterator.index == slice->end_index;
        ts_tree_builder_grow(&builder, chunk.tree->height);
        ts_tree_builder_reuse_chunk(
          &builder, chunk.tree,
          chunk.start_index, chunk.end_index,
          is_last
        );
        if (is_last) break;
      }

      ts_syntax_tree_delete(&slice->base);
    }
  }

  array_delete(&parts);
  ts_tree_iterator_delete(&old_tree_iterator);
  return ts_tree_builder_to_tree(&builder);
}
