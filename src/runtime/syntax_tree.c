#include "tree_sitter/runtime.h"
#include "runtime/alloc.h"
#include "runtime/array.h"
#include "runtime/atomic.h"
#include "runtime/language.h"
#include "runtime/length.h"
#include "runtime/syntax_tree.h"

#define TREE_HEIGHT_SLICE UINT16_MAX

uint32_t TREE_BRANCHING_FACTOR = DEFAULT_TREE_BRANCHING_FACTOR;

typedef struct {
  Length size;
  uint32_t node_count;
} SyntaxTreeSummary;

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
  bool visible : 1;
  bool named : 1;
};

struct SyntaxTree {
  SyntaxTree *previous;
  volatile uint32_t ref_count;
  uint16_t height;
  uint16_t count;
};

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
  SyntaxNode *node;
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

typedef struct {
  const TSLanguage *language;
  Array(ChildStackEntry) child_stack;
  Array(SyntaxTree *) rightmost_trees;
  uint32_t node_count;
} TreeBuilder;

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

static void ts_syntax_tree_retain(SyntaxTree *self) {
  atomic_inc(&self->ref_count);
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
  }
  return true;
}

static SyntaxTree *ts_syntax_tree_copy(SyntaxTree *other, uint32_t start, uint32_t end) {
  if (other->height == 0) {
    SyntaxTreeLeaf *leaf = ts_syntax_tree_new_leaf();
    SyntaxTree *result = &leaf->base;
    ts_syntax_tree_push_slice(result, other, start, end);
    return result;
  } else {
    SyntaxTreeInternal *internal = ts_syntax_tree_new_internal(other->height);
    SyntaxTree *result = &internal->base;
    ts_syntax_tree_push_slice(result, other, start, end);
    SyntaxTree **last = &internal->children[result->count - 1];
    *last = ts_syntax_tree_copy(*last, 0, (*last)->count);
    return result;
  }
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

static void ts_tree_iterator_prepare(TreeIterator *self) {
  // Ensure that the iterators is not at the end of a subtree.
  TreeIteratorEntry *last_entry = array_back(&self->entries);
  while (last_entry->index == last_entry->tree->count) {
    self->entries.size--;
    last_entry--;
    last_entry->index++;
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
  node->visible = metadata.visible;
  node->named = metadata.named;
  node->node_count = 1;

  assert(self->child_stack.size >= node->child_count);

  // Pop this node's children off of the child stack.
  self->child_stack.size -= node->child_count;
  ChildStackEntry *children = &self->child_stack.contents[self->child_stack.size];

  // Assign the properties of this node that derive from its children, and the properties
  // of the children that derive from their context.
  SyntaxNode *prev_child = NULL;
  for (unsigned i = 0; i < node->child_count; i++) {
    SyntaxNode *child = children[i].node;
    uint32_t child_index = children[i].index;

    if (prev_child) {
      prev_child->next_sibling_node_count = child->node_count;
    } else {
      node->first_child_node_count = child->node_count;
    }

    if (child->visible) {
      node->visible_child_count++;
      if (child->named) node->named_child_count++;
    } else if (child->child_count > 0) {
      node->visible_child_count += child->visible_child_count;
      node->named_child_count += child->named_child_count;
    }

    node->node_count += child->node_count;

    child->node_count_to_parent = self->node_count - child_index;
    prev_child = child;
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

static void ts_syntax_tree_builder_reuse_chunk(TreeBuilder *self, SyntaxTree *tree,
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
      tree = ts_syntax_tree_copy(tree, start_index, end_index);
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

TSPoint ts_node2_start_point(const TSNode2 *self) {
  return (TSPoint) { .row = 0, .column = 0 };
}

TSPoint ts_node2_end_point(const TSNode2 *self) {
  return (TSPoint) { .row = 0, .column = 0 };
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
      if (child.node->visible) {
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
  } while (!result.node->visible);
  return result;
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
        ts_syntax_tree_builder_reuse_chunk(
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
