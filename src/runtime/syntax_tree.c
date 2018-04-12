#include <stdatomic.h>
#include "tree_sitter/runtime.h"
#include "runtime/alloc.h"
#include "runtime/array.h"
#include "runtime/language.h"
#include "runtime/length.h"
#include "runtime/syntax_tree.h"

uint32_t TREE_BRANCHING_FACTOR = DEFAULT_TREE_BRANCHING_FACTOR;

typedef struct {
  Length size;
  uint32_t node_count;
} SyntaxTreeSummary;

typedef enum {
  SyntaxTreeTypeLeaf,
  SyntaxTreeTypeInternal,
  SyntaxTreeTypeSlice,
} SyntaxTreeType;

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
  uint16_t count;
  uint16_t type;
  uint16_t height;
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

static SyntaxTreeSummary ts_syntax_tree_summary_new(const SyntaxTreeEntry *entry) {
  return (SyntaxTreeSummary) {
    .node_count = 1,
    .size = entry->node.child_count == 0
      ? length_add(entry->node.padding, entry->node.size)
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

static SyntaxTreeSummary ts_syntax_tree_leaf_summarize(const SyntaxTreeLeaf *self) {
  SyntaxTreeSummary result = {
    .node_count = 0,
    .size = length_zero(),
  };
  for (unsigned i = 0; i < self->header.count; i++) {
    ts_syntax_tree_summary_add(&result, ts_syntax_tree_summary_new(&self->entries[i]));
  }
  return result;
}

static SyntaxTreeLeaf *ts_syntax_tree_leaf_new() {
  SyntaxTreeLeaf *self = ts_malloc(sizeof(SyntaxTreeLeaf));
  self->header = (SyntaxTree) {
    .type = SyntaxTreeTypeLeaf,
    .ref_count = 1,
    .count = 0,
    .height = 0,
  };
  return self;
}

static SyntaxTreeInternal *ts_syntax_tree_internal_new(uint16_t height) {
  SyntaxTreeInternal *self = ts_malloc(sizeof(SyntaxTreeInternal));
  self->header = (SyntaxTree) {
    .type = SyntaxTreeTypeInternal,
    .ref_count = 1,
    .count = 0,
    .height = height,
  };
  return self;
}

static bool ts_syntax_tree_leaf_push(SyntaxTreeLeaf *self, SyntaxNode node) {
  if (self->header.count < TREE_BRANCHING_FACTOR) {
    self->entries[self->header.count] = (SyntaxTreeEntry) {
      .node = node,
      .node_count = 1,
    };
    self->header.count++;
    return true;
  } else {
    return false;
  }
}

static bool ts_syntax_tree_internal_push(SyntaxTreeInternal *self, SyntaxTree *child,
                                         const SyntaxTreeSummary *summary) {
  if (self->header.count < TREE_BRANCHING_FACTOR) {
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

static void ts_syntax_tree_internal_update_summary(SyntaxTreeInternal *self,
                                                   const SyntaxTreeSummary *summary) {
  ts_syntax_tree_summary_add(&self->summaries[self->header.count - 1], *summary);
}

void ts_syntax_tree_delete(SyntaxTree *self) {
  self->ref_count--;
  if (self->ref_count == 0) {
    if (self->type == SyntaxTreeTypeInternal) {
      for (unsigned i = 0; i < self->count; i++) {
        ts_syntax_tree_delete(((SyntaxTreeInternal *)self)->children[i]);
      }
    }
    ts_free(self);
  }
}

TSNode2 ts_syntax_tree_node_at_index(const SyntaxTree *self, uint32_t goal_index) {
  const SyntaxTree *tree = self;
  uint32_t index = 0;
  while (tree) {
    if (tree->type == SyntaxTreeTypeLeaf) {
      const SyntaxTreeLeaf *leaf = (const SyntaxTreeLeaf *)tree;
      for (unsigned i = 0; i < tree->count; i++) {
        if (index == goal_index || i == tree->count - 1) {
          return (TSNode2) {
            .tree = self,
            .entry = &leaf->entries[i],
            .index = index,
            .byte = 0,
            .row = 0,
          };
        }
        index++;
      }
    } else {
      const SyntaxTreeInternal *internal = (const SyntaxTreeInternal *)tree;
      for (unsigned i = 0; i < tree->count; i++) {
        uint32_t next_index = index + internal->summaries[i].node_count;
        SyntaxTree *child = internal->children[i];
        if (next_index > goal_index || i == tree->count - 1) {
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

TSPoint ts_node2_start_point(const TSNode2 *self) {
}

TSPoint ts_node2_end_point(const TSNode2 *self) {
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
  if (!self->last ||
      self->last->ref_count > 1 ||
      self->last->type != SyntaxTreeTypeLeaf ||
      !ts_syntax_tree_leaf_push((SyntaxTreeLeaf *)self->last, node)) {
    SyntaxTreeLeaf *last = ts_syntax_tree_leaf_new();
    last->header.previous = self->last,
    ts_syntax_tree_leaf_push(last, node);
    self->last = (SyntaxTree *)last;
    self->count++;
  }
}

SyntaxTree *ts_tree_builder_build(TreeBuilder *self, const TSLanguage *language) {
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
  Array(SyntaxTreeInternal *) stack = array_new();
  index = 0;
  for (unsigned i = 0, n = parts.size; i < n; i++) {
    SyntaxTree *part = parts.contents[i];

    if (part->type == SyntaxTreeTypeLeaf) {
      SyntaxTreeLeaf *leaf = (SyntaxTreeLeaf *)part;

      // Populated the derived state for each entry in the subtree.
      for (unsigned j = 0; j < leaf->header.count; j++) {
        SyntaxTreeEntry *entry = &leaf->entries[j];
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

      // If possible, add the subtree to an existing internal node.
      SyntaxTree *tree_to_push = (SyntaxTree *)leaf;
      SyntaxTreeSummary summary = ts_syntax_tree_leaf_summarize(leaf);

      for (unsigned height = 1; height <= stack.size; height++) {
        SyntaxTreeInternal *internal = stack.contents[height - 1];
        if (tree_to_push) {
          if (ts_syntax_tree_internal_push(internal, tree_to_push, &summary)) {
            tree_to_push = NULL;
          } else {
            SyntaxTreeInternal *parent = ts_syntax_tree_internal_new(height + 1);
            ts_syntax_tree_internal_push(parent, tree_to_push, &summary);
            tree_to_push = (SyntaxTree *)parent;
          }
        } else {
          ts_syntax_tree_internal_update_summary(internal, &summary);
        }
      }

      // Otherwise, create a new root node to contain this subtree.
      if (tree_to_push) {
        SyntaxTreeInternal *root = ts_syntax_tree_internal_new(stack.size + 1);
        ts_syntax_tree_internal_push(root, tree_to_push, &summary);
        array_push(&stack, root);
      }
    } else {
      // TODO - handle reused slices
    }
  }

  SyntaxTreeInternal *root = *array_front(&stack);
  array_delete(&stack);
  array_delete(&parts);
  array_delete(&child_stack);

  return (SyntaxTree *)root;
}
