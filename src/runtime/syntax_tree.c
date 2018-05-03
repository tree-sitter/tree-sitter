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
  SyntaxTree *tree;
  uint32_t start_index;
  uint32_t end_index;
  bool has_root;
} SyntaxTreeSlice;

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

static SyntaxTreeSlice *ts_syntax_tree_new_slice(SyntaxTree *tree, uint32_t start_index,
                                                 uint32_t end_index, bool has_root) {
  SyntaxTreeSlice *self = ts_malloc(sizeof(SyntaxTreeSlice));
  self->base = (SyntaxTree) {
    .ref_count = 1,
    .count = 0,
    .height = TREE_HEIGHT_SLICE,
  };
  self->tree = tree;
  self->start_index = start_index;
  self->end_index = end_index;
  self->has_root = has_root;
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
  if (self->base.count < TREE_BRANCHING_FACTOR && self->base.ref_count == 1) {
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
      SyntaxTreeSummary expected_summary = ts_syntax_tree_summarize(child, 0, child->count);
      assert(child->height == self->height - 1);
      assert(summary->node_count == expected_summary.node_count);
      assert(summary->size.bytes == expected_summary.size.bytes);
      ts_syntax_tree_check_invariants(child);
    }
  }
}

static unsigned get_color(unsigned index) {
  return (index % 12) + 1;
}

static void ts_syntax_tree__print_dot_graph(const SyntaxTree *self, const TSLanguage *language,
                                            FILE *f, uint32_t *node_index) {
  if (self->height == 0) {
    fprintf(f, "node_%p [shape = plaintext, label = <<table cellpadding=\"4\" cellspacing=\"0\" border=\"0\"><tr>", self);
    const SyntaxTreeLeaf *leaf = (const SyntaxTreeLeaf *)self;
    for (unsigned i = 0; i < leaf->base.count; i++) {
      const SyntaxNode *node = &leaf->entries[i];
      const char *name = ts_language_symbol_name(language, node->symbol);
      unsigned color = get_color((*node_index)++);
      fprintf(f, "<td bgcolor=\"%u\">%s</td>", color, name);
      if (node->child_count > 0) fprintf(f, " %u", node->child_count);
    }
    fprintf(f, "</tr></table>>];\n");
  } else {
    fprintf(f, "node_%p [label = \"", self);
    const SyntaxTreeInternal *internal = (const SyntaxTreeInternal *)self;
    for (unsigned i = 0; i < internal->base.count; i++) {
      if (i > 0) fprintf(f, " | ");
      fprintf(f, "<child_%u> %u", i, internal->summaries[i].node_count);
    }
    fprintf(f, "\"];\n");
    for (unsigned i = 0; i < internal->base.count; i++) {
      fprintf(f, "node_%p:child_%u -> node_%p\n", internal, i, internal->children[i]);
      ts_syntax_tree__print_dot_graph(internal->children[i], language, f, node_index);
    }
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
    unsigned color = get_color(node.index);
    fprintf(f, "node_%u [label = \"%s\", fillcolor = %u];\n", node.index, name, color);
    if (node.node->node_count_to_parent) {
      uint32_t parent_index = node.index + node.node->node_count_to_parent;
      fprintf(f, "node_%u -> node_%u\n", parent_index, node.index);
    }
    if (!ts_tree_cursor_descend(&cursor) && !ts_tree_cursor_advance(&cursor)) break;
  }
  ts_tree_cursor_delete(&cursor);
  fprintf(f, "}\n");
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

static SyntaxTreeSlice *ts_tree_cursor__take_slice(TreeCursor *self) {
  uint32_t current_index = array_back(&self->left)->summary.node_count;
  uint32_t goal_index = array_back(&self->right)->summary.node_count + 1;
  assert(goal_index > current_index);

  // Walk up the tree to find which subtree to advance within.
  for (uint32_t i = self->left.size - 1; i + 1 > 0; i--) {
    TreeCursorEntry *entry = &self->left.contents[i];

    // If only a subset of this subtree is needed, advance to the end of this subtree.
    // Otherwise, advance at a higher level in the tree.
    if (i > 0 && entry->index == 0) {
      TreeCursorEntry *previous_entry = &self->left.contents[i - 1];
      SyntaxTreeInternal *internal = (SyntaxTreeInternal *)previous_entry->tree;
      SyntaxTreeSummary *summary = &internal->summaries[previous_entry->index];
      if (previous_entry->summary.node_count + summary->node_count < goal_index) {
        continue;
      }
    }

    SyntaxTree *tree = entry->tree;
    uint32_t start_index = entry->index;
    uint32_t end_index = entry->tree->count;

    if (entry->tree->height == 0) {
      SyntaxTreeLeaf *leaf = (SyntaxTreeLeaf *)entry->tree;
      for (unsigned j = entry->index; j < leaf->base.count; j++) {
        SyntaxTreeSummary next_summary = entry->summary;
        ts_syntax_tree_summary_add(&next_summary, ts_syntax_tree_summary_new(&leaf->entries[j]));
        if (next_summary.node_count > goal_index) {
          end_index = j;
          break;
        }
        entry->summary = next_summary;
      }
    } else {
      SyntaxTreeInternal *internal = (SyntaxTreeInternal *)entry->tree;
      for (unsigned j = entry->index; j < internal->base.count; j++) {
        SyntaxTreeSummary next_summary = entry->summary;
        ts_syntax_tree_summary_add(&next_summary, internal->summaries[j]);
        if (next_summary.node_count > goal_index) {
          end_index = j;
          break;
        }
        entry->summary = next_summary;
      }
    }

    entry->index = end_index;
    self->left.size = i + 1;
    ts_tree_cursor__prepare(&self->left);
    bool has_root = entry->summary.node_count == goal_index;
    if (has_root) ts_tree_cursor_advance(self);
    return ts_syntax_tree_new_slice(tree, start_index, end_index, has_root);
  }

  assert(!"Tried to walk tree iterator past its end");
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

static void ts_tree_builder_push_slice(TreeBuilder *self, SyntaxTreeSlice *slice) {
  SyntaxTree *tree = slice->tree;
  uint32_t start_index = slice->start_index;
  uint32_t end_index = slice->end_index;
  bool has_root = slice->has_root;
  SyntaxTreeSummary summary = ts_syntax_tree_summarize(tree, start_index, end_index);

  ts_tree_builder_grow(self, tree->height);

  // When pushing an entire subtree that doesn't contain the final node
  // being reused, reuse the subtree itself without copying.
  if (!has_root && start_index == 0 && end_index == tree->count) {
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
  if (has_root) {
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
  for (;;) {
    SyntaxTreeSlice *slice = ts_tree_cursor__take_slice(cursor);
    slice->base.previous = self->last;
    self->last = &slice->base;
    self->count++;
    if (slice->has_root) break;
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
    SyntaxTree *part = parts.contents[i];

    if (part->height == 0) {
      ts_tree_builder_push_leaf(&builder, (SyntaxTreeLeaf *)part);
    } else {
      ts_tree_builder_push_slice(&builder, (SyntaxTreeSlice *)part);
      ts_syntax_tree_delete(part);
    }
  }

  array_delete(&parts);
  return ts_tree_builder_to_tree(&builder);
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
