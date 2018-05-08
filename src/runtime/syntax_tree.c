#include "tree_sitter/runtime.h"
#include "runtime/alloc.h"
#include "runtime/array.h"
#include "runtime/atomic.h"
#include "runtime/language.h"
#include "runtime/length.h"
#include "runtime/syntax_tree.h"

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
  // The previous subtree in the NodeList, or NULL if this is the first subtree.
  // This field is only used during the parsing process and is set to NULL afterwards.
  SyntaxTree *previous;

  // A bitmask indicating which of this tree's children have been directly reused
  // (as opposed to being indirectly reused as part of a larger syntax subtree).
  //
  // In the case of a leaf node, the bits refer to individual syntax nodes. In
  // the case of an internal node, the bits refer to children that *contain*
  // reused syntax nodes.
  //
  // Syntax nodes that are reused must each be processed by the TreeBuilder at
  // the end of the parsing process. Their bottom-up derived state (e.g. node_count,
  // visible_child_count) does not need to be recomputed, but their top-down
  // derived state (e.g. node_count_to_parent, next_sibling_node_count) does need
  // to be recomputed, and they must be accessed in order to compute their parents'
  // bottom-up derived state.
  uint32_t reused_children;

  // The node's reference count. It is volatile because it can be mutated concurrently
  // by multiple threads.
  volatile uint32_t ref_count;

  // The tree's height. Zero indicates a leaf node.
  uint16_t height;

  // The number of syntax nodes stored in leaf node, or the number of children
  // in an internal node.
  uint8_t count;

  // A flag indicating whether this leaf node was newly created during this parse
  // and still needs to have all of its derived state assigned.
  bool is_new;
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

struct TreeCursorEntry {
  SyntaxTree *tree;
  uint32_t index;
  SyntaxTreeSummary summary;
};

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
    .is_new = true,
    .reused_children = 0,
  };
  return self;
}

static SyntaxTreeInternal *ts_syntax_tree_new_internal(uint16_t height) {
  SyntaxTreeInternal *self = ts_malloc(sizeof(SyntaxTreeInternal));
  self->base = (SyntaxTree) {
    .ref_count = 1,
    .count = 0,
    .height = height,
    .is_new = false,
    .reused_children = 0,
  };
  return self;
}

static void ts_syntax_tree_retain(const SyntaxTree *self) {
  atomic_inc(&((SyntaxTree *)self)->ref_count);
}

bool ts_syntax_tree_delete(SyntaxTree *self) {
  if (atomic_dec(&self->ref_count) == 0) {
    if (self->height > 0) {
      for (unsigned i = 0; i < self->count; i++) {
        ts_syntax_tree_delete(((SyntaxTreeInternal *)self)->children[i]);
      }
    }
    ts_free(self);
    return true;
  } else {
    return false;
  }
}

static SyntaxTreeSummary ts_syntax_tree_summarize(const SyntaxTree *self) {
  SyntaxTreeSummary result = {
    .node_count = 0,
    .size = length_zero(),
  };
  if (self->height == 0) {
    SyntaxTreeLeaf *leaf = (SyntaxTreeLeaf *)self;
    for (unsigned i = 0; i < self->count; i++) {
      ts_syntax_tree_summary_add(&result, ts_syntax_tree_summary_new(&leaf->entries[i]));
    }
  } else {
    SyntaxTreeInternal *internal = (SyntaxTreeInternal *)self;
    for (unsigned i = 0; i < self->count; i++) {
      ts_syntax_tree_summary_add(&result, internal->summaries[i]);
    }
  }
  return result;
}

static bool ts_syntax_tree_push_node(SyntaxTreeLeaf *self, SyntaxNode *entry) {
  if (self->base.count < TREE_BRANCHING_FACTOR && self->base.ref_count == 1 && self->base.is_new) {
    self->entries[self->base.count] = *entry;
    self->base.count++;
    return true;
  } else {
    return false;
  }
}

static bool ts_syntax_tree_push_child(SyntaxTreeInternal *self, SyntaxTree *child,
                                      const SyntaxTreeSummary *summary) {
  if (self->base.count < TREE_BRANCHING_FACTOR && self->base.ref_count == 1) {
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

static bool ts_syntax_tree_combine(SyntaxTree *self, SyntaxTree *other) {
  if (self->count + other->count > TREE_BRANCHING_FACTOR || self->ref_count > 1) {
    return false;
  }

  self->reused_children |= (other->reused_children << self->count);

  assert(self->height == other->height);
  if (self->height == 0) {
    SyntaxTreeLeaf *leaf = (SyntaxTreeLeaf *)self;
    SyntaxTreeLeaf *other_leaf = (SyntaxTreeLeaf *)other;
    memcpy(
      &leaf->entries[leaf->base.count],
      &other_leaf->entries[0],
      other->count * sizeof(SyntaxNode)
    );
  } else {
    SyntaxTreeInternal *internal = (SyntaxTreeInternal *)self;
    SyntaxTreeInternal *other_internal = (SyntaxTreeInternal *)other;
    for (unsigned i = 0; i < other->count; i++) {
      SyntaxTree *child = other_internal->children[i];
      ts_syntax_tree_retain(child);
      internal->children[internal->base.count + i] = child;
    }
    memcpy(
      &internal->summaries[internal->base.count],
      &other_internal->summaries[0],
      other->count * sizeof(SyntaxTreeSummary)
    );
  }
  self->count += other->count;

  return true;
}

static SyntaxTree *ts_syntax_tree_copy(SyntaxTree *self) {
  SyntaxTree *result;
  if (self->height == 0) {
    result = &ts_syntax_tree_new_leaf()->base;
  } else {
    result = &ts_syntax_tree_new_internal(self->height)->base;
  }
  result->is_new = false;
  ts_syntax_tree_combine(result, self);
  return result;
}

static bool ts_syntax_tree_is_child_reused(const SyntaxTree *self, uint32_t index) {
  return (self->reused_children & (1 << index)) != 0;
}

static SyntaxTree *ts_syntax_tree_mark_child_reused(SyntaxTree *self, uint32_t index) {
  SyntaxTree *result;
  if (self->ref_count == 1) {
    result = self;
  } else {
    result = ts_syntax_tree_copy(self);
    ts_syntax_tree_delete(self);
  }

  result->reused_children |= (1 << index);
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
    Length position = length_zero();
    for (unsigned i = 0; i < leaf->base.count; i++) {
      SyntaxNode *node = &leaf->entries[i];

      // Mark leaf nodes intersecting the edit as having changes and resize them.
      if (node->child_count == 0) {
        Length total_size = length_add(node->padding, node->size);
        Length end_position = length_add(position, total_size);

        if (edit && end_position.bytes >= edit->start.bytes) {
          Edit node_edit;
          if (edit->start.bytes < position.bytes) {
            node_edit = (Edit) {
              length_zero(),
              length_zero(),
              length_sub(edit_old_end, position)
            };
          } else {
            node_edit = (Edit) {
              length_sub(edit->start, position),
              edit->added,
              edit->removed
            };
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
    Length position = length_zero();
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
          child_edit = (Edit) {
            length_zero(),
            length_zero(),
            length_sub(edit_old_end, position)
          };
        } else {
          child_edit = (Edit) {
            length_sub(edit->start, position),
            edit->added,
            edit->removed
          };
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
  IndexSet internal_node_indices = array_new();
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

void ts_syntax_tree_check_invariants(const SyntaxTree *self) {
  if (self->height > 0) {
    const SyntaxTreeInternal *internal = (const SyntaxTreeInternal *)self;
    for (unsigned i = 0; i < internal->base.count; i++) {
      const SyntaxTree *child = internal->children[i];
      const SyntaxTreeSummary *summary = &internal->summaries[i];
      SyntaxTreeSummary expected_summary = ts_syntax_tree_summarize(child);
      assert(child->height == self->height - 1);
      assert(summary->node_count == expected_summary.node_count);
      assert(summary->size.bytes == expected_summary.size.bytes);
      ts_syntax_tree_check_invariants(child);
    }
  }
}

static const char *get_color(const unsigned index) {
  static const char *colors[] = {
    "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11",
  };
  return colors[index % (sizeof(colors) / sizeof(colors[0]))];
}

static const SyntaxTree *ts_syntax_tree__print_dot_graph(const SyntaxTree *self,
                                                         const TSLanguage *language,
                                                         FILE *f, uint32_t *node_index) {
  if (self->height == 0) {
    fprintf(
      f,
      "node_%p ["
      "shape = plaintext, "
      "label = <<table cellpadding=\"4\" cellspacing=\"0\" border=\"0\"><tr>",
      self
    );
    const SyntaxTreeLeaf *leaf = (const SyntaxTreeLeaf *)self;
    for (unsigned i = 0; i < self->count; i++) {
      const SyntaxNode *node = &leaf->entries[i];
      const char *name = ts_language_symbol_name(language, node->symbol);
      const char *color = "white";
      if (node_index) {
        color = get_color(*node_index);
        *node_index += 1;
      } else if (ts_syntax_tree_is_child_reused(self, i)) {
        color = "lightblue";
      }
      fprintf(f,
        "<td "
        "bgcolor=\"%s\" "
        "href=\"#\" "
        "tooltip=\"node_count: %u, first_child_node_count: %u, next_sibling_node_count: %u\""
        ">",
        color,
        node->child_count > 0 ? node->node_count : 1,
        node->child_count > 0 ? node->first_child_node_count : 0,
        node->next_sibling_node_count
      );
      fprintf(f, "%s", name);
      if (node->child_count > 0) fprintf(f, " %u", node->child_count);
      fprintf(f, "</td>");
    }
    fprintf(f, "</tr></table>>];\n");
    return self;
  } else {
    fprintf(f, "node_%p [style=filled, fillcolor = white, label = \"", self);
    const SyntaxTreeInternal *internal = (const SyntaxTreeInternal *)self;
    for (unsigned i = 0; i < self->count; i++) {
      if (i > 0) fprintf(f, " | ");
      fprintf(f, "<child_%u> %u", i, internal->summaries[i].node_count);
    }
    fprintf(f, "\"];\n");
    const SyntaxTree *first_leaf = NULL;
    for (unsigned i = 0; i < self->count; i++) {
      SyntaxTree *child = internal->children[i];
      fprintf(f, "node_%p:child_%u -> node_%p\n", internal, i, child);
      const SyntaxTree *leaf = ts_syntax_tree__print_dot_graph(
        child, language, f, node_index
      );
      if (i == 0) first_leaf = leaf;
    }
    return first_leaf;
  }
}

void ts_syntax_tree_print_dot_graph(const SyntaxTree *self, const TSLanguage *language, FILE *f) {
  fprintf(f, "digraph tree {\n");
  fprintf(f, "node [shape = record, height = 0.1, colorscheme=spectral11];\n");

  fprintf(f, "subgraph cluster_storage {\n");
  fprintf(f, "color = white\n");
  fprintf(f, "label = \"storage\";\n");
  uint32_t index = 0;
  ts_syntax_tree__print_dot_graph(self, language, f, &index);
  fprintf(f, "}\n");

  fprintf(f, "subgraph cluster_syntax {\n");
  fprintf(f, "color = white\n");
  fprintf(f, "node [style = filled];\n");
  fprintf(f, "label = \"syntax\";\n");
  TreeCursor cursor = ts_tree_cursor_new((SyntaxTree *)self);
  for (;;) {
    TSNode2 node = ts_tree_cursor_current_node(&cursor);
    const char *name = ts_language_symbol_name(language, node.node->symbol);
    const char *color = get_color(node.index);
    fprintf(f, "node_%u [label = \"%s\", fillcolor = %s];\n", node.index, name, color);
    if (node.node->node_count_to_parent) {
      uint32_t parent_index = node.index + node.node->node_count_to_parent;
      fprintf(f, "node_%u -> node_%u\n", parent_index, node.index);
    }
    if (!ts_tree_cursor_descend(&cursor) && !ts_tree_cursor_advance(&cursor)) break;
  }
  ts_tree_cursor_delete(&cursor);
  fprintf(f, "}\n\n");
  fprintf(f, "}\n\n");
}

// TreeCursor

static void ts_tree_cursor__seek(TreeCursorEntries *self, uint32_t goal_index) {
  TreeCursorEntry *last_entry = array_back(self);

  SyntaxTree *tree;
  SyntaxTreeSummary summary;

  // Ascend the B-tree to find the lowest node that contains both the current syntax node
  // and the goal syntax node.
  for (;;) {
    tree = last_entry->tree;
    array_pop(self);
    if (self->size > 0) {
      last_entry = array_back(self);
      summary = last_entry->summary;
      if (summary.node_count <= goal_index) {
        SyntaxTreeInternal *internal = (SyntaxTreeInternal *)last_entry->tree;
        if (summary.node_count + internal->summaries[last_entry->index].node_count > goal_index) {
          break;
        }
      }
    } else {
      summary = (SyntaxTreeSummary) {length_zero(), 0};
      break;
    }
  }

  // Descend the B-tree to find the goal syntax node.
  for (;;) {
    if (tree->height == 0) {
      SyntaxTreeLeaf *leaf = (SyntaxTreeLeaf *)tree;
      unsigned index_in_leaf = goal_index - summary.node_count;
      if (index_in_leaf >= leaf->base.count) index_in_leaf = leaf->base.count - 1;
      for (unsigned i = 0; i < index_in_leaf; i++) {
        SyntaxNode *node = &leaf->entries[i];
        ts_syntax_tree_summary_add(&summary, ts_syntax_tree_summary_new(node));
      }
      array_push(self, ((TreeCursorEntry){
        .tree = tree,
        .index = index_in_leaf,
        .summary = summary,
      }));
      break;
    } else {
      const SyntaxTreeInternal *internal = (const SyntaxTreeInternal *)tree;
      for (unsigned i = 0; i < internal->base.count; i++) {
        SyntaxTree *child = internal->children[i];
        SyntaxTreeSummary next_summary = summary;
        ts_syntax_tree_summary_add(&next_summary, internal->summaries[i]);
        if (next_summary.node_count > goal_index || i == internal->base.count - 1) {
          array_push(self, ((TreeCursorEntry){
            .tree = tree,
            .index = i,
            .summary = summary
          }));
          tree = child;
          break;
        }
        summary = next_summary;
      }
    }
  }
}

static void ts_tree_cursor__assign(TreeCursorEntries *self, TreeCursorEntries *other) {
  memcpy(self->contents, other->contents, self->size * sizeof(TreeCursorEntries));
}

static void ts_tree_cursor__prepare(TreeCursorEntries *self) {
  // Ensure that the iterators is not at the end of a subtree.
  TreeCursorEntry *last_entry = array_back(self);
  SyntaxTreeSummary summary = last_entry->summary;
  while (last_entry->index == last_entry->tree->count) {
    self->size--;
    last_entry--;
    last_entry->index++;
    last_entry->summary = summary;
  }

  // Descend to a leaf.
  while (last_entry && last_entry->tree->height > 0) {
    SyntaxTreeInternal *internal = (SyntaxTreeInternal *)last_entry->tree;
    array_push(self, ((TreeCursorEntry){
      .tree = internal->children[last_entry->index],
      .index = 0,
      .summary = summary,
    }));
    last_entry++;
  }
}

TreeCursor ts_tree_cursor_new(SyntaxTree *tree) {
  TreeCursor self = {array_new(), array_new()};
  array_reserve(&self.left, tree->height + 1);
  array_reserve(&self.right, tree->height + 1);
  array_push(&self.left, ((TreeCursorEntry) {
    .tree = tree,
    .index = 0,
    .summary = {length_zero(), 0},
  }));
  array_push(&self.right, ((TreeCursorEntry) {
    .tree = tree,
    .index = 0,
    .summary = {length_zero(), 0},
  }));
  ts_tree_cursor__seek(&self.left, 0);
  ts_tree_cursor__seek(&self.right, UINT32_MAX);
  return self;
}

void ts_tree_cursor_delete(TreeCursor *self) {
  array_delete(&self->left);
  array_delete(&self->right);
}

bool ts_tree_cursor_descend(TreeCursor *self) {
  TreeCursorEntry *last_entry = array_back(&self->right);
  SyntaxTreeLeaf *leaf = (SyntaxTreeLeaf *)last_entry->tree;
  SyntaxNode *node = &leaf->entries[last_entry->index];
  if (node->child_count == 0) return false;

  // Find the first child. The first leaf does not change.
  uint32_t current_index = last_entry->summary.node_count;
  uint32_t child_index = current_index - node->node_count + node->first_child_node_count;
  ts_tree_cursor__seek(&self->right, child_index);

  return true;
}

bool ts_tree_cursor_advance(TreeCursor *self) {
  TreeCursorEntry *last_entry = array_back(&self->right);
  SyntaxTreeLeaf *leaf = (SyntaxTreeLeaf *)last_entry->tree;
  SyntaxNode *node = &leaf->entries[last_entry->index];

  // Walk up the syntax tree until a node is found that has a next sibling.
  while (node->next_sibling_node_count == 0) {
    if (node->node_count_to_parent == 0) return false;
    uint32_t parent_index = last_entry->summary.node_count + node->node_count_to_parent;
    ts_tree_cursor__seek(&self->right, parent_index);
    last_entry = array_back(&self->right);
    leaf = (SyntaxTreeLeaf *)last_entry->tree;
    node = &leaf->entries[last_entry->index];
  }

  // Find the next sibling's first leaf.
  unsigned current_index = last_entry->summary.node_count;
  ts_tree_cursor__assign(&self->left, &self->right);
  ts_tree_cursor__seek(&self->left, current_index + 1);

  // Find the next sibling itself.
  uint32_t sibling_index = current_index + node->next_sibling_node_count;
  ts_tree_cursor__seek(&self->right, sibling_index);
  return true;
}

TSNode2 ts_tree_cursor_current_node(TreeCursor *self) {
  TreeCursorEntry *last_entry = array_back(&self->right);
  SyntaxTreeLeaf *leaf = (SyntaxTreeLeaf *)last_entry->tree;
  return (TSNode2) {
    .tree = array_front(&self->left)->tree,
    .node = &leaf->entries[last_entry->index],
    .index = last_entry->summary.node_count,
  };
}

Length ts_tree_cursor_position(TreeCursor *self) {
  return array_back(&self->left)->summary.size;
}

uint32_t ts_tree_cursor__index(TreeCursorEntries *self) {
  return array_back(self)->summary.node_count;
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
  if (self->rightmost_trees.size < height) {
    SyntaxTree *root = *array_back(&self->rightmost_trees);
    SyntaxTreeSummary summary = ts_syntax_tree_summarize(root);
    do {
      SyntaxTreeInternal *new_root = ts_syntax_tree_new_internal(self->rightmost_trees.size);
      ts_syntax_tree_push_child(new_root, root, &summary);
      array_push(&self->rightmost_trees, &new_root->base);
      root = &new_root->base;
    } while (self->rightmost_trees.size < height);
  }
}

static void ts_tree_builder_populate_new_node(TreeBuilder *self, SyntaxNode *node,
                                              ChildStackEntry *children) {
  TSSymbolMetadata metadata = ts_language_symbol_metadata(self->language, node->symbol);
  node->is_visible = metadata.visible;
  node->is_named = metadata.named;

  if (node->child_count > 0) {

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
}

static void ts_tree_builder_populate_new_nodes(TreeBuilder *self, SyntaxTree *tree,
                                               unsigned start_index) {
  const bool is_new = tree->is_new;
  if (tree->height == 0) {
    SyntaxTreeLeaf *leaf = (SyntaxTreeLeaf *)tree;
    for (unsigned i = start_index; i < leaf->base.count; i++) {
      if (is_new || ts_syntax_tree_is_child_reused(tree, i)) {
        SyntaxNode *node = &leaf->entries[i];
        if (is_new) {
          assert(self->child_stack.size >= node->child_count);
          self->child_stack.size -= node->child_count;
          ChildStackEntry *children = &self->child_stack.contents[self->child_stack.size];
          ts_tree_builder_populate_new_node(self, node, children);
        }
        array_push(&self->child_stack, ((ChildStackEntry){node, self->node_count}));
      }
      self->node_count++;
    }
  } else {
    SyntaxTreeInternal *internal = (SyntaxTreeInternal *)tree;
    for (unsigned i = start_index; i < internal->base.count; i++) {
      if (ts_syntax_tree_is_child_reused(tree, i)) {
        ts_tree_builder_populate_new_nodes(self, internal->children[i], 0);
      } else {
        self->node_count += internal->summaries[i].node_count;
      }
    }
  }
  if (is_new) tree->is_new = false;
}

static void ts_tree_builder_push_tree(TreeBuilder *self, SyntaxTree *tree) {
  unsigned child_count = tree->count;
  SyntaxTreeSummary summary = ts_syntax_tree_summarize(tree);

  // Try to insert these entries into an existing subtree. Otherwise, copy the tree so
  // that its final entry can be mutated.
  uint32_t initial_height = tree->height;
  ts_tree_builder_grow(self, initial_height);

  SyntaxTree *tree_to_push = tree;
  SyntaxTree *existing_tree = self->rightmost_trees.contents[tree->height];
  if (existing_tree && ts_syntax_tree_combine(existing_tree, tree)) {
    ts_syntax_tree_delete(tree);
    tree = existing_tree;
    tree_to_push = NULL;
  }

  SyntaxTree *old_root = *array_back(&self->rightmost_trees);

  // Walk up the existing tree to find a subtree where the new tree can be inserted.
  // Continue walking upward after the insertion is complete in order to update each
  // tree's summary.
  for (unsigned height = initial_height + 1; height < self->rightmost_trees.size; height++) {
    SyntaxTreeInternal *internal = (SyntaxTreeInternal *)self->rightmost_trees.contents[height];
    if (tree_to_push) {
      if (ts_syntax_tree_push_child(internal, tree_to_push, &summary)) {
        tree_to_push = NULL;
      } else {
        SyntaxTreeInternal *parent = ts_syntax_tree_new_internal(height);
        ts_syntax_tree_push_child(parent, tree_to_push, &summary);
        tree_to_push = &parent->base;
        self->rightmost_trees.contents[height] = tree_to_push;
      }
    } else {
      ts_syntax_tree_update_last_summary(internal, &summary);
    }
  }

  // If the tree could not be inserted into any existing tree, create a new root node
  // to contain the tree.
  if (tree_to_push) {
    SyntaxTreeInternal *root = ts_syntax_tree_new_internal(self->rightmost_trees.size);
    if (old_root) {
      SyntaxTreeSummary old_summary = ts_syntax_tree_summarize(old_root);
      ts_syntax_tree_push_child(root, old_root, &old_summary);
    }
    ts_syntax_tree_push_child(root, tree_to_push, &summary);
    array_push(&self->rightmost_trees, &root->base);
  }

  // Update the rightmost trees to reflect the addition of the new tree.
  SyntaxTree *descendant = tree;
  while (descendant) {
    self->rightmost_trees.contents[descendant->height] = descendant;
    if (descendant->height > 0) {
      descendant = ts_syntax_tree_last_child((SyntaxTreeInternal *)descendant);
    } else {
      descendant = NULL;
    }
  }

  ts_tree_builder_populate_new_nodes(self, tree, tree->count - child_count);
}

// TSNode

Length ts_syntax_tree__position_at_index(const SyntaxTree *tree, uint32_t goal_index,
                                         SyntaxNode *out_node) {
  uint32_t index = 0;
  Length result = length_zero();
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
      assert(node);
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
  return (NodeList) {
    .last = NULL,
    .count = 0,
  };
}

NodeList ts_node_list_copy(NodeList *self) {
  ts_syntax_tree_retain(self->last);
  return (NodeList) {
    .last = self->last,
    .count = self->count,
  };
}

void ts_node_list_delete(NodeList *self) {
  SyntaxTree *tree = self->last;
  while (tree) {
    SyntaxTree *previous = tree->previous;
    if (ts_syntax_tree_delete(tree)) {
      tree = previous;
    } else {
      tree = NULL;
    }
  }
}

NodeListIterator ts_node_list_iterator_new() {
  return (NodeListIterator) {
    .stack = array_new(),
    .next_trees = array_new(),
  };
}

void ts_node_list_iterator_delete(NodeListIterator *self) {
  if (self->stack.contents) array_delete(&self->stack);
  if (self->next_trees.contents) array_delete(&self->next_trees);
}

void ts_node_list__push_tree(NodeList *self, SyntaxTree *tree) {
  tree->previous = self->last;
  self->last = tree;
  self->count++;
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

void ts_node_list_push_leaf(NodeList *self, LeafNodeParams params) {
  SyntaxNode node = {
    .symbol = params.symbol,
    .child_count = 0,
    .padding = params.padding,
    .size = params.size,
  };
  ts_node_list__push(self, &node);
}

void ts_node_list_push_parent(NodeList *self, InternalNodeParams params) {
  SyntaxNode node = {
    .symbol = params.symbol,
    .child_count = params.child_count,
  };
  ts_node_list__push(self, &node);
}

void ts_node_list_reuse(NodeList *self, TreeCursor *cursor) {
  uint32_t goal_index = array_back(&cursor->right)->summary.node_count + 1;
  bool done = false;

  while (!done) {
    // Walk up the tree to find the largest subtree that can be reused in its entirety.
    for (uint32_t i = cursor->left.size - 1; i + 1 > 0; i--) {
      TreeCursorEntry *entry = &cursor->left.contents[i];

      if (i > 0 && entry->index == 0) {
        TreeCursorEntry *previous_entry = &cursor->left.contents[i - 1];
        SyntaxTreeInternal *internal = (SyntaxTreeInternal *)previous_entry->tree;
        SyntaxTreeSummary *summary = &internal->summaries[previous_entry->index];
        if (previous_entry->summary.node_count + summary->node_count < goal_index) {
          continue;
        }
      }

      // Find what span of this tree is needed.
      if (entry->tree->height == 0) {
        SyntaxTreeLeaf *leaf = (SyntaxTreeLeaf *)entry->tree;
        while (entry->index < leaf->base.count) {
          SyntaxNode *node = &leaf->entries[entry->index];
          ts_node_list__push(self, node);
          ts_syntax_tree_summary_add(&entry->summary, ts_syntax_tree_summary_new(node));
          entry->index++;
          if (entry->summary.node_count == goal_index) {
            done = true;
            break;
          }
        }
      } else {
        SyntaxTreeInternal *internal = (SyntaxTreeInternal *)entry->tree;
        while (entry->index < internal->base.count) {
          SyntaxTree *child = internal->children[entry->index];
          SyntaxTreeSummary next_summary = entry->summary;
          ts_syntax_tree_summary_add(&next_summary, internal->summaries[entry->index]);
          if (next_summary.node_count > goal_index) break;
          ts_node_list__push_tree(self, ts_syntax_tree_copy(child));
          entry->index++;
          entry->summary = next_summary;
          if (entry->summary.node_count == goal_index) {
            done = true;
            break;
          }
        }
      }

      cursor->left.size = i + 1;
      ts_tree_cursor__prepare(&cursor->left);
      break;
    }
  }

  ts_tree_cursor_advance(cursor);
  SyntaxTree **tree = &self->last;
  for (;;) {
    *tree = ts_syntax_tree_mark_child_reused(*tree, (*tree)->count - 1);
    if ((*tree)->height > 0) {
      SyntaxTreeInternal *internal = (SyntaxTreeInternal *)*tree;
      tree = &internal->children[internal->base.count - 1];
    } else {
      break;
    }
  }
}

void ts_node_list_breakdown(NodeList *self, NodeListIterator *iterator, BreakdownResult *result) {
  // Find the last syntax node in the list and remove it.
  SyntaxNode *removed_node;
  SyntaxTree *tree = self->last;
  for (;;) {
    uint32_t last_index = tree->count - 1;
    if (tree->height > 0) {
      SyntaxTreeInternal *internal = (SyntaxTreeInternal *)tree;

      // TODO copy tree if necessary
      internal->summaries[last_index].node_count--;

      tree = internal->children[last_index];
    } else {
      SyntaxTreeLeaf *leaf = (SyntaxTreeLeaf *)tree;
      removed_node = &leaf->entries[last_index];
      tree->count--;
      break;
    }
  }

  // Iterate back through the list to find the subtree that contains the first syntax
  // node within the removed node. Store any subsequent subtrees in an array.
  tree = self->last;
  uint32_t node_count_from_end = 1;
  array_clear(&iterator->next_trees);
  array_clear(&iterator->stack);
  for (;;) {
    bool done = false;
    if (tree->height > 0) {
      SyntaxTreeInternal *internal = (SyntaxTreeInternal *)tree;
      for (unsigned i = internal->base.count - 1; i + 1 > 0; i--) {
        node_count_from_end += internal->summaries[i].node_count;
        if (node_count_from_end >= removed_node->node_count) {
          array_push(&iterator->stack, ((TreeCursorEntry) {
            .tree = tree,
            .index = i,
            .summary = {length_zero(), 0},
          }));
          ts_tree_cursor__seek(&iterator->stack, node_count_from_end - removed_node->node_count);
          done = true;
          break;
        }
      }
      if (done) break;
    } else {
      node_count_from_end += tree->count;
      if (node_count_from_end >= removed_node->node_count) {
        array_push(&iterator->stack, ((TreeCursorEntry) {
          .tree = tree,
          .index = node_count_from_end - removed_node->node_count,
          .summary = {length_zero(), 0},
        }));
        done = true;
      }
    }

    if (done) break;
    array_push(&iterator->next_trees, tree);
    tree = tree->previous;
  }

  array_clear(result);
  Length previous_child_position = length_zero();
  SyntaxTreeSummary previous_trees_summary = {length_zero(), 0};
  unsigned next_child_index = removed_node->first_child_node_count - 1;
  for (unsigned i = 0; i < removed_node->child_count; i++) {
    for (;;) {
      ts_tree_cursor__seek(&iterator->stack, next_child_index);
      TreeCursorEntry *last_entry = array_back(&iterator->stack);
      SyntaxTreeSummary summary = last_entry->summary;
      SyntaxTreeLeaf *leaf = (SyntaxTreeLeaf *)last_entry->tree;
      SyntaxNode *node = &leaf->entries[last_entry->index];
      if (summary.node_count == next_child_index) {
        ts_syntax_tree_summary_add(&summary, ts_syntax_tree_summary_new(node));
        array_push(result, ((BreakdownEntry) {
          .symbol = node->symbol,
          .size = length_sub(length_add(previous_trees_summary.size, summary.size), previous_child_position),
        }));

        for (unsigned j = 0; j < iterator->stack.size; j++) {
          TreeCursorEntry *entry = &iterator->stack.contents[j];
          entry->tree = ts_syntax_tree_mark_child_reused(entry->tree, entry->index);
          if (j > 0) {
            TreeCursorEntry *parent_entry = &iterator->stack.contents[j - 1];
            SyntaxTreeInternal *parent = (SyntaxTreeInternal *)parent_entry->tree;
            parent->children[parent_entry->index] = entry->tree;
          }
        }

        previous_child_position = summary.size;
        next_child_index += node->next_sibling_node_count;
        break;
      }

      ts_syntax_tree_summary_add(&summary, ts_syntax_tree_summary_new(node));
      ts_syntax_tree_summary_add(&previous_trees_summary, summary);
      next_child_index -= summary.node_count;
      array_clear(&iterator->stack);
      array_push(&iterator->stack, ((TreeCursorEntry) {
        .tree = array_pop(&iterator->next_trees),
        .index = 0,
        .summary = {length_zero(), 0},
      }));
    }
  }
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
  for (unsigned i = 0, n = parts.size; i < n; i++) {
    ts_tree_builder_push_tree(&builder, parts.contents[i]);
  }

  array_delete(&parts);
  return ts_tree_builder_to_tree(&builder);
}

void ts_node_list_print_dot_graph(NodeList *self, const TSLanguage *language, FILE *f) {
  fprintf(f, "digraph node_list {\n");
  fprintf(f, "compound = true;\n");
  fprintf(f, "rankdir = RL;\n");
  fprintf(f, "node [shape = record, height = 0.1, colorscheme=spectral11];\n");

  const SyntaxTree *next_tree = NULL, *next_leaf = NULL;
  const SyntaxTree *tree = self->last;
  while (tree) {
    fprintf(f, "subgraph cluster_%p {\n", tree);
    fprintf(f, "style = filled;\n");

    if (tree->is_new) {
      fprintf(f, "fillcolor = white;\n");
    } else {
      fprintf(f, "fillcolor = lightgray;\n");
    }

    const SyntaxTree *leaf = ts_syntax_tree__print_dot_graph(tree, language, f, NULL);
    fprintf(f, "}\n");
    if (next_tree) {
      fprintf(
        f,
        "node_%p -> node_%p ["
        "style=dashed, "
        "ltail=cluster_%p, "
        "lhead=cluster_%p"
        "];\n",
        next_leaf, tree, next_tree, tree
      );
    }

    next_tree = tree;
    next_leaf = leaf;
    tree = tree->previous;
  }

  fprintf(f, "}\n\n");
}

#ifdef TREE_SITTER_TEST_MODE

const SyntaxTreeInternal *itree(const SyntaxTree *self) {
  assert(self->height > 0);
  return (const SyntaxTreeInternal *)self;
}

const SyntaxTreeLeaf *ltree(const SyntaxTree *self) {
  assert(self->height == 0);
  return (const SyntaxTreeLeaf *)self;
}

#endif
