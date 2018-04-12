#ifndef RUNTIME_SYNTAX_TREE_H_
#define RUNTIME_SYNTAX_TREE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "tree_sitter/parser.h"
#include "runtime/length.h"

typedef struct {
  Length size;
  Length padding;
  uint32_t child_count;
  uint32_t alias_sequence_id;
  TSSymbol symbol;
} SyntaxNode;

typedef struct SyntaxTreeEntry SyntaxTreeEntry;
typedef struct SyntaxTree SyntaxTree;

typedef struct {
  SyntaxTree *last;
  uint32_t count;
} TreeBuilder;

#define DEFAULT_TREE_BRANCHING_FACTOR 32
extern uint32_t TREE_BRANCHING_FACTOR;

TreeBuilder ts_tree_builder_new();
void ts_tree_builder_delete(TreeBuilder *);
void ts_tree_builder_push_tree(TreeBuilder *, SyntaxTree *);
void ts_tree_builder_push_node(TreeBuilder *, SyntaxNode);
SyntaxTree *ts_tree_builder_build(TreeBuilder *, const TSLanguage *);

typedef struct {
  const SyntaxTree *tree;
  const SyntaxTreeEntry *entry;
  uint32_t index;
  uint32_t byte;
  uint32_t row;
} TSNode2;

void ts_syntax_tree_delete(SyntaxTree *);
TSNode2 ts_syntax_tree_root_node(const SyntaxTree *);

TSPoint ts_node2_start_point(const TSNode2 *);
TSPoint ts_node2_end_point(const TSNode2 *);
TSSymbol ts_node2_symbol(const TSNode2 *);
unsigned ts_node2_child_count(const TSNode2 *);
TSNode2 ts_node2_child(const TSNode2 *, unsigned);
TSNode2 ts_node2_parent(const TSNode2 *);

#ifdef __cplusplus
}
#endif

#endif  // RUNTIME_SYNTAX_TREE_H_
