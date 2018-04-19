#include <stdatomic.h>
#include "tree_sitter/runtime.h"
#include "runtime/alloc.h"
#include "runtime/array.h"
#include "runtime/language.h"
#include "runtime/length.h"
#include "runtime/syntax_tree.h"

#define TREE_HEIGHT_SLICE UINT16_MAX

uint32_t TREE_BRANCHING_FACTOR = DEFAULT_TREE_BRANCHING_FACTOR;

typedef struct {
  Length size;
  uint32_t node_count;
} SyntaxTreeSummary;

struct SyntaxTreeEntry {
  SyntaxNode node;
  uint32_t node_count;
  uint32_t first_child_node_count;
  uint32_t next_sibling_node_count;
  uint32_t visible_child_count;
  uint32_t named_child_count;
  uint32_t node_count_to_parent;
  TSSymbol alias_symbol : 15;
  bool alias_is_named : 1;
  bool visible : 1;
  bool named : 1;
};

struct SyntaxTree {
  SyntaxTree *previous;
  _Atomic uint32_t ref_count;
  uint16_t height;
  uint16_t count;
};

typedef struct {
  SyntaxTree header;
  SyntaxTreeEntry entries[DEFAULT_TREE_BRANCHING_FACTOR];
} SyntaxTreeLeaf;

typedef struct {
  SyntaxTree header;
  SyntaxTree *children[DEFAULT_TREE_BRANCHING_FACTOR];
  SyntaxTreeSummary summaries[DEFAULT_TREE_BRANCHING_FACTOR];
} SyntaxTreeInternal;

typedef struct {
  SyntaxTree header;
  uint32_t start_index;
  uint32_t end_index;
} SyntaxTreeSlice;

typedef struct {
  SyntaxTreeEntry *entry;
  uint32_t index;
} ChildStackEntry;

typedef struct {
  SyntaxTree *tree;
  uint32_t index;
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

// SyntaxTree

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

static void ts_syntax_tree_entry_populate(SyntaxTreeEntry *self,
                                          uint32_t index,
                                          const TSLanguage *language,
                                          ChildStackEntry *children) {
  TSSymbolMetadata metadata = ts_language_symbol_metadata(language, self->node.symbol);
  self->visible = metadata.visible;
  self->named = metadata.named;
  self->node_count = 1;

  SyntaxTreeEntry *prev_child = NULL;
  for (unsigned i = 0; i < self->node.child_count; i++) {
    SyntaxTreeEntry *child = children[i].entry;
    uint32_t child_index = children[i].index;

    if (prev_child) {
      self->node.size = length_add(self->node.size, child->node.padding);
      prev_child->next_sibling_node_count = child->node_count;
    } else {
      self->node.padding = child->node.padding;
      self->first_child_node_count = child->node_count;
    }

    self->node.size = length_add(self->node.size, child->node.size);

    if (child->visible) {
      self->visible_child_count++;
      if (child->named) self->named_child_count++;
    } else {
      self->visible_child_count += child->visible_child_count;
      self->named_child_count += child->named_child_count;
    }

    self->node_count += child->node_count;

    child->node_count_to_parent = index - child_index;
    prev_child = child;
  }
}

static SyntaxTreeLeaf *ts_syntax_tree_leaf_new() {
  SyntaxTreeLeaf *self = ts_malloc(sizeof(SyntaxTreeLeaf));
  self->header = (SyntaxTree) {
    .ref_count = 1,
    .count = 0,
    .height = 0,
  };
  return self;
}

static SyntaxTreeSlice *ts_syntax_tree_slice_new(uint32_t start_index, uint32_t end_index) {
  SyntaxTreeSlice *self = ts_malloc(sizeof(SyntaxTreeSlice));
  self->header = (SyntaxTree) {
    .ref_count = 1,
    .count = 0,
    .height = TREE_HEIGHT_SLICE,
  };
  self->start_index = start_index;
  self->end_index = end_index;
  return self;
}

static SyntaxTreeInternal *ts_syntax_tree_internal_new(uint16_t height) {
  SyntaxTreeInternal *self = ts_malloc(sizeof(SyntaxTreeInternal));
  self->header = (SyntaxTree) {
    .ref_count = 1,
    .count = 0,
    .height = height,
  };
  return self;
}

static void ts_syntax_tree_retain(SyntaxTree *self) {
  self->ref_count++;
}

void ts_syntax_tree_delete(SyntaxTree *self) {
  self->ref_count--;
  if (self->ref_count == 0) {
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
      ts_syntax_tree_summary_add(&result, ts_syntax_tree_summary_new(&leaf->entries[i].node));
    }
  } else {
    SyntaxTreeInternal *internal = (SyntaxTreeInternal *)self;
    for (unsigned i = start; i < end; i++) {
      ts_syntax_tree_summary_add(&result, internal->summaries[i]);
    }
  }
  return result;
}

static bool ts_syntax_tree_leaf_push(SyntaxTreeLeaf *self, SyntaxTreeEntry *entry) {
  if (self->header.count < TREE_BRANCHING_FACTOR || self->header.ref_count > 1) {
    self->entries[self->header.count] = *entry;
    self->header.count++;
    return true;
  } else {
    return false;
  }
}

static bool ts_syntax_tree_internal_push(SyntaxTreeInternal *self, SyntaxTree *child,
                                         const SyntaxTreeSummary *summary) {
  if (self->header.count < TREE_BRANCHING_FACTOR || self->header.ref_count > 1) {
    assert(child->height == self->header.height - 1);
    assert(child->count > 0);
    self->children[self->header.count] = child;
    self->summaries[self->header.count] = *summary;
    self->header.count++;
    return true;
  } else {
    return false;
  }
}

static bool ts_syntax_tree_push_existing(SyntaxTree *self, SyntaxTree *other,
                                         uint32_t start, uint32_t end) {
  if (self->count + end - start > TREE_BRANCHING_FACTOR || self->ref_count > 1) {
    return false;
  }

  assert(self->height == other->height);
  if (self->height == 0) {
    SyntaxTreeLeaf *leaf = (SyntaxTreeLeaf *)self;
    SyntaxTreeLeaf *other_leaf = (SyntaxTreeLeaf *)other;
    memcpy(
      &leaf->entries[leaf->header.count],
      &other_leaf->entries[start],
      (end - start) * sizeof(SyntaxTreeEntry)
    );
    leaf->header.count += end - start;
  } else {
    SyntaxTreeInternal *internal = (SyntaxTreeInternal *)self;
    SyntaxTreeInternal *other_internal = (SyntaxTreeInternal *)other;
    for (unsigned i = 0; i < (end - start); i++) {
      SyntaxTree *child = other_internal->children[start + i];
      ts_syntax_tree_retain(child);
      internal->children[internal->header.count + i] = child;
    }
    memcpy(
      &internal->summaries[internal->header.count],
      &other_internal->summaries[start],
      (end - start) * sizeof(SyntaxTreeSummary)
    );
  }
  return true;
}

static SyntaxTree *ts_syntax_tree_copy_existing(SyntaxTree *other, uint32_t start, uint32_t end) {
  SyntaxTree *result = other->height == 0
    ? (SyntaxTree *)ts_syntax_tree_leaf_new()
    : (SyntaxTree *)ts_syntax_tree_internal_new(other->height);
  ts_syntax_tree_push_existing(result, other, start, end);
  return result;
}

static void ts_syntax_tree_internal_update_summary(SyntaxTreeInternal *self,
                                                   const SyntaxTreeSummary *summary) {
  ts_syntax_tree_summary_add(&self->summaries[self->header.count - 1], *summary);
}

static SyntaxTreeEntry *ts_syntax_tree_leaf_last_entry(SyntaxTreeLeaf *self) {
  return &self->entries[self->header.count - 1];
}

TSNode2 ts_syntax_tree_node_at_index(const SyntaxTree *self, uint32_t goal_index) {
  const SyntaxTree *tree = self;
  uint32_t index = 0;
  while (tree) {
    if (tree->height == 0) {
      const SyntaxTreeLeaf *leaf = (const SyntaxTreeLeaf *)tree;
      uint32_t last_index = index + leaf->header.count - 1;
      if (goal_index > last_index) goal_index = last_index;
      return (TSNode2) {
        .tree = self,
        .entry = &leaf->entries[goal_index - index],
        .index = goal_index,
        .byte = 0,
        .row = 0,
      };
    } else {
      const SyntaxTreeInternal *internal = (const SyntaxTreeInternal *)tree;
      for (unsigned i = 0; i < internal->header.count; i++) {
        uint32_t next_index = index + internal->summaries[i].node_count;
        SyntaxTree *child = internal->children[i];
        if (next_index > goal_index || i == internal->header.count - 1) {
          tree = child;
          break;
        }
        index = next_index;
      }
    }
  }
  return (TSNode2) {};
}

TSNode2 ts_syntax_tree_root_node(const SyntaxTree *self) {
  return ts_syntax_tree_node_at_index(self, UINT32_MAX);
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
      for (unsigned i = 0; i < internal->header.count; i++) {
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

static void ts_tree_iterator_prepare(TreeIterator *self) {
  TreeIteratorEntry *last_entry = array_back(&self->entries);
  while (last_entry->index == last_entry->tree->count) {
    self->entries.size--;
    last_entry--;
    last_entry->index++;
  }

  while (last_entry && last_entry->tree->height > 0) {
    SyntaxTreeInternal *internal = (SyntaxTreeInternal *)last_entry->tree;
    array_push(&self->entries, ((TreeIteratorEntry){
      .tree = internal->children[last_entry->index],
      .index = 0
    }));
    last_entry++;
  }
}

static inline uint32_t min(uint32_t a, uint32_t b) {
  return a < b ? a : b;
}

// Advance the iterator toward the given goal index, one partial subtree at a time.
static TreeIteratorItem ts_tree_iterator_advance(TreeIterator *self, uint32_t goal_index) {
  uint32_t goal_node_count = goal_index - self->index;

  // If only a subset of this leaf is needed, advance to the end of this leaf.
  // Otherwise, advance within a larger subtree.
  TreeIteratorEntry *last_entry = array_back(&self->entries);
  uint32_t node_count = min(last_entry->tree->count - last_entry->index, goal_node_count);
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

    uint32_t node_count = 0;
    uint32_t end_index = internal->header.count;
    for (unsigned j = entry->index; j < internal->header.count; j++) {
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

static SyntaxTreeEntry *ts_tree_iterator_current_entry(TreeIterator *self) {
  TreeIteratorEntry *leaf_entry = array_back(&self->entries);
  SyntaxTreeLeaf *leaf = (SyntaxTreeLeaf *)leaf_entry->tree;
  return &leaf->entries[leaf_entry->index];
}

// TSNode

TSPoint ts_node2_start_point(const TSNode2 *self) {
  return (TSPoint) {};
}

TSPoint ts_node2_end_point(const TSNode2 *self) {
  return (TSPoint) {};
}

TSSymbol ts_node2_symbol(const TSNode2 *self) {
  return self->entry->node.symbol;
}

uint32_t ts_node2_child_count(const TSNode2 *self) {
  return self->entry->node.child_count;
}

static TSNode2 ts_node2__first_immediate_child(const TSNode2 *self) {
  return ts_syntax_tree_node_at_index(
    self->tree,
    self->index - self->entry->node_count + self->entry->first_child_node_count
  );
}

static TSNode2 ts_node2__next_immediate_sibling(const TSNode2 *self) {
  return ts_syntax_tree_node_at_index(
    self->tree,
    self->index + self->entry->next_sibling_node_count
  );
}

TSNode2 ts_node2_child(const TSNode2 *self, unsigned goal_index) {
  if (goal_index >= self->entry->visible_child_count) return (TSNode2) {};

  unsigned child_index = 0;
  TSNode2 child = ts_node2__first_immediate_child(self);

  bool did_descend = true;
  while (did_descend) {
    did_descend = false;

    for (;;) {
      if (child.entry->visible) {
        if (child_index == goal_index) {
          return child;
        } else {
          child_index++;
        }
      } else {
        unsigned grandchild_index = goal_index - child_index;
        if (child.entry->visible_child_count > grandchild_index) {
          did_descend = true;
          goal_index = grandchild_index;
          child = ts_node2__first_immediate_child(&child);
          break;
        } else {
          child_index += child.entry->visible_child_count;
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
      result.index + result.entry->node_count_to_parent
    );
  } while (!result.entry->visible);
  return result;
}

// TreeBuilder

TreeBuilder ts_tree_builder_new() {
  return (TreeBuilder) { .last = NULL };
}

void ts_tree_builder_delete(TreeBuilder *self) {
  SyntaxTree *tree = self->last;
  while (tree) {
    tree->ref_count--;
    if (tree->ref_count == 0) {
      SyntaxTree *previous = tree->previous;
      ts_free(tree);
      tree = previous;
    } else {
      tree = NULL;
    }
  }
}

void ts_tree_builder_push_node(TreeBuilder *self, SyntaxNode node) {
  SyntaxTreeEntry entry = {.node = node, .node_count = 1};
  if (!self->last || self->last->height != 0 ||
      !ts_syntax_tree_leaf_push((SyntaxTreeLeaf *)self->last, &entry)) {
    SyntaxTreeLeaf *last = ts_syntax_tree_leaf_new();
    last->header.previous = self->last,
    ts_syntax_tree_leaf_push(last, &entry);
    self->last = &last->header;
    self->count++;
  }
}

void ts_tree_builder_reuse_node(TreeBuilder *self, TSNode2 node) {
  SyntaxTreeSlice *last = ts_syntax_tree_slice_new(
    node.index + 1 - node.entry->node_count,
    node.index + 1
  );
  last->header.previous = self->last;
  self->last = &last->header;
  self->count++;
}

SyntaxTree *ts_tree_builder_build(TreeBuilder *self, const TSLanguage *language,
                                  SyntaxTree *old_tree) {
  // Move the subtrees into an array so that they can be processed from left to right.
  Array(SyntaxTree *) parts = array_new();
  array_reserve(&parts, self->count);
  parts.size = self->count;
  uint32_t index = self->count - 1;
  SyntaxTree *tree = self->last;
  while (tree) {
    parts.contents[index--] = tree;
    SyntaxTree *previous = tree->previous;
    tree->previous = NULL;
    tree = previous;
  }

  // Walk the subtrees, incorporating them into a single tree and populating each node's
  // derived state.
  Array(ChildStackEntry) child_stack = array_new();
  Array(SyntaxTree *) tree_stack = array_new();
  array_push(&tree_stack, NULL);
  TreeIterator old_tree_iterator = ts_tree_iterator_new(old_tree);
  index = 0;
  for (unsigned i = 0, n = parts.size; i < n; i++) {
    SyntaxTree *part = parts.contents[i];

    if (part->height == 0) {
      SyntaxTreeLeaf *leaf = (SyntaxTreeLeaf *)part;

      // Populated the derived state for each entry in the leaf.
      for (unsigned j = 0; j < leaf->header.count; j++) {
        SyntaxTreeEntry *entry = &leaf->entries[j];
        assert(child_stack.size >= entry->node.child_count);
        ts_syntax_tree_entry_populate(
          entry,
          index,
          language,
          &child_stack.contents[child_stack.size - entry->node.child_count]
        );
        child_stack.size -= entry->node.child_count;
        array_push(&child_stack, ((ChildStackEntry){entry, index}));
        index++;
      }

      // If possible, add this leaf to an existing internal node.
      SyntaxTree *tree_to_push = &leaf->header;
      SyntaxTreeSummary summary = ts_syntax_tree_summarize(tree_to_push, 0, tree_to_push->count);
      tree_stack.contents[0] = tree_to_push;
      for (unsigned height = 1; height < tree_stack.size; height++) {
        SyntaxTreeInternal *internal = (SyntaxTreeInternal *)tree_stack.contents[height];
        if (tree_to_push) {
          if (ts_syntax_tree_internal_push(internal, tree_to_push, &summary)) {
            tree_to_push = NULL;
          } else {
            SyntaxTreeInternal *parent = ts_syntax_tree_internal_new(height + 1);
            ts_syntax_tree_internal_push(parent, tree_to_push, &summary);
            tree_to_push = &parent->header;
            tree_stack.contents[height] = tree_to_push;
          }
        } else {
          ts_syntax_tree_internal_update_summary(internal, &summary);
        }
      }

      // Otherwise, create a new root node to contain this leaf.
      if (tree_to_push) {
        SyntaxTreeInternal *root = ts_syntax_tree_internal_new(tree_stack.size);
        ts_syntax_tree_internal_push(root, tree_to_push, &summary);
        array_push(&tree_stack, &root->header);
      }
    } else {
      SyntaxTreeSlice *slice = (SyntaxTreeSlice *)part;

      ts_tree_iterator_seek(&old_tree_iterator, slice->start_index);
      while (old_tree_iterator.index < slice->end_index - 1) {
        TreeIteratorItem chunk = ts_tree_iterator_advance(&old_tree_iterator, slice->end_index - 1);

        // Ensure that the current tree is tall enough to contain this chunk.
        while (tree_stack.size < chunk.tree->height) {
          SyntaxTree *root = *array_back(&tree_stack);
          SyntaxTreeSummary summary = ts_syntax_tree_summarize(root, 0, root->count);
          SyntaxTreeInternal *new_root = ts_syntax_tree_internal_new(tree_stack.size);
          ts_syntax_tree_internal_push(new_root, root, &summary);
          array_push(&tree_stack, &new_root->header);
        }

        SyntaxTree *tree_to_push = NULL;
        SyntaxTreeSummary summary = ts_syntax_tree_summarize(chunk.tree, chunk.start_index, chunk.end_index);

        if (chunk.start_index == 0 && chunk.end_index == chunk.tree->count) {
          ts_syntax_tree_retain(chunk.tree);
          tree_to_push = chunk.tree;
        } else {
          SyntaxTree *existing_tree = tree_stack.contents[chunk.tree->height];
          if (!existing_tree || !ts_syntax_tree_push_existing(
            existing_tree, chunk.tree, chunk.start_index, chunk.end_index
          )) {
            tree_to_push = ts_syntax_tree_copy_existing(chunk.tree, chunk.start_index, chunk.end_index);
            tree_stack.contents[chunk.tree->height] = tree_to_push;
          }
        }

        // TODO dedup
        for (unsigned height = chunk.tree->height + 1; height < tree_stack.size; height++) {
          SyntaxTreeInternal *internal = (SyntaxTreeInternal *)tree_stack.contents[height];
          if (tree_to_push) {
            if (ts_syntax_tree_internal_push(internal, tree_to_push, &summary)) {
              tree_to_push = NULL;
            } else {
              SyntaxTreeInternal *parent = ts_syntax_tree_internal_new(height + 1);
              ts_syntax_tree_internal_push(parent, tree_to_push, &summary);
              tree_to_push = &parent->header;
              tree_stack.contents[height] = tree_to_push;
            }
          } else {
            ts_syntax_tree_internal_update_summary(internal, &summary);
          }
        }

        if (tree_to_push) {
          SyntaxTreeInternal *root = ts_syntax_tree_internal_new(tree_stack.size);
          ts_syntax_tree_internal_push(root, tree_to_push, &summary);
          array_push(&tree_stack, &root->header);
        }
      }

      SyntaxTreeEntry *entry_to_push = ts_tree_iterator_current_entry(&old_tree_iterator);
      SyntaxTreeSummary summary = ts_syntax_tree_summary_new(&entry_to_push->node);
      SyntaxTree *tree_to_push = NULL;

      SyntaxTreeLeaf *existing_leaf = (SyntaxTreeLeaf *)tree_stack.contents[0];
      if (!existing_leaf || !ts_syntax_tree_leaf_push(existing_leaf, entry_to_push)) {
        SyntaxTreeLeaf *leaf_to_push = ts_syntax_tree_leaf_new();
        ts_syntax_tree_leaf_push(leaf_to_push, entry_to_push);
        tree_to_push = &leaf_to_push->header;
        tree_stack.contents[0] = tree_to_push;
      }

      for (unsigned height = 1; height < tree_stack.size; height++) {
        SyntaxTreeInternal *internal = (SyntaxTreeInternal *)tree_stack.contents[height];
        if (tree_to_push) {
          if (ts_syntax_tree_internal_push(internal, tree_to_push, &summary)) {
            tree_to_push = NULL;
          } else {
            SyntaxTreeInternal *parent = ts_syntax_tree_internal_new(height + 1);
            ts_syntax_tree_internal_push(parent, tree_to_push, &summary);
            tree_to_push = &parent->header;
            tree_stack.contents[height] = tree_to_push;
          }
        } else {
          ts_syntax_tree_internal_update_summary(internal, &summary);
        }
      }

      index += slice->end_index - slice->start_index;
      array_push(&child_stack, ((ChildStackEntry){
        ts_syntax_tree_leaf_last_entry((SyntaxTreeLeaf *)tree_stack.contents[0]),
        index - 1
      }));
      ts_syntax_tree_delete(&slice->header);
    }
  }

  SyntaxTree *root = *array_back(&tree_stack);
  array_delete(&tree_stack);
  array_delete(&parts);
  array_delete(&child_stack);
  ts_tree_iterator_delete(&old_tree_iterator);

  return root;
}
