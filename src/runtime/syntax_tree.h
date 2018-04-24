#ifndef RUNTIME_SYNTAX_TREE_H_
#define RUNTIME_SYNTAX_TREE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "tree_sitter/parser.h"
#include "runtime/length.h"

#define DEFAULT_TREE_BRANCHING_FACTOR 32
extern uint32_t TREE_BRANCHING_FACTOR;

typedef struct SyntaxNode SyntaxNode;
typedef struct SyntaxTree SyntaxTree;

typedef struct {
  SyntaxTree *last;
  uint32_t count;
} NodeList;

typedef struct {
  const SyntaxTree *tree;
  const SyntaxNode *node;
  uint32_t index;
  uint32_t byte;
  uint32_t row;
} TSNode2;

NodeList ts_node_list_new();
void ts_node_list_delete(NodeList *);
void ts_node_list_push_leaf(NodeList *, TSSymbol, Length padding, Length size);
void ts_node_list_push_parent(NodeList *, TSSymbol, uint32_t child_count);
void ts_node_list_reuse(NodeList *, TSNode2);
SyntaxTree *ts_node_list_to_tree(NodeList *, const TSLanguage *, SyntaxTree *);

void ts_syntax_tree_delete(SyntaxTree *);
TSNode2 ts_syntax_tree_root_node(const SyntaxTree *);
SyntaxTree *ts_syntax_tree_edit(SyntaxTree *, TSInputEdit);

TSPoint ts_node2_start_point(const TSNode2 *);
TSPoint ts_node2_end_point(const TSNode2 *);
TSSymbol ts_node2_symbol(const TSNode2 *);
unsigned ts_node2_child_count(const TSNode2 *);
TSNode2 ts_node2_child(const TSNode2 *, unsigned);
TSNode2 ts_node2_parent(const TSNode2 *);
bool ts_node2_has_changes(const TSNode2 *);

#ifdef __cplusplus
}
#endif

#endif  // RUNTIME_SYNTAX_TREE_H_
