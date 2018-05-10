#ifndef RUNTIME_PARSER_H_
#define RUNTIME_PARSER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "runtime/stack.h"
#include "runtime/array.h"
#include "runtime/lexer.h"
#include "runtime/reusable_node.h"
#include "runtime/reduce_action.h"
#include "runtime/subtree.h"

typedef struct {
  Subtree *token;
  Subtree *last_external_token;
  uint32_t byte_index;
} TokenCache;

typedef struct {
  Lexer lexer;
  Stack *stack;
  SubtreePool tree_pool;
  const TSLanguage *language;
  ReduceActionSet reduce_actions;
  Subtree *finished_tree;
  Subtree scratch_tree;
  TokenCache token_cache;
  ReusableNode reusable_node;
  void *external_scanner_payload;
  bool in_ambiguity;
  bool print_debugging_graphs;
  unsigned accept_count;
} Parser;

bool parser_init(Parser *);
void parser_destroy(Parser *);
Subtree *parser_parse(Parser *, TSInput, Subtree *, bool halt_on_error);
void parser_set_language(Parser *, const TSLanguage *);

#ifdef __cplusplus
}
#endif

#endif  // RUNTIME_PARSER_H_
