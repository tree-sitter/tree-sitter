#ifndef RUNTIME_PARSE_STACK_H_
#define RUNTIME_PARSE_STACK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "tree_sitter/parser.h"

typedef struct ParseStack ParseStack;

typedef struct {
  TSTree *tree;
  TSStateId state;
} ParseStackEntry;

typedef struct {
  int index;
  int tree_count;
  TSTree **trees;
} ParseStackPopResult;

typedef struct {
  int size;
  ParseStackPopResult *contents;
} ParseStackPopResultList;

/*
 *  Create a ParseStack.
 */
ParseStack *ts_parse_stack_new();

/*
 *  Release any resources reserved by a parse stack.
 */
void ts_parse_stack_delete(ParseStack *);

/*
 *  Get the stack's current number of heads.
 */
int ts_parse_stack_head_count(const ParseStack *);

/*
 *  Get the tree and state that are at the top of the given stack head.
 */
const ParseStackEntry *ts_parse_stack_head(const ParseStack *, int head);

/*
 *  Get the number of successors for a given parse stack entry.
 */
int ts_parse_stack_entry_next_count(const ParseStackEntry *);

/*
 *  Get the nth successor to a given parse stack entry.
 */
const ParseStackEntry *ts_parse_stack_entry_next(const ParseStackEntry *, int);

/*
 *  Push a (tree, state) pair onto the given head of the stack. Returns
 *  a boolean indicating whether the stack head was merged with an
 *  existing head.
 */
bool ts_parse_stack_push(ParseStack *, int head, TSStateId, TSTree *);

/*
 *  Pop the given number of entries from the given head of the stack. This
 *  operation can increase the number of stack heads by revealing multiple heads
 *  which had previously been merged. It returns a struct that indicates the
 *  index of each revealed head and the trees removed from that head.
 */
ParseStackPopResultList ts_parse_stack_pop(ParseStack *, int head, int count);

/*
 *  Split the given stack head into two heads, so that the stack can be
 *  transformed from its current state in multiple alternative ways. Returns
 *  the index of the newly-created head.
 */
int ts_parse_stack_split(ParseStack *, int head);

#ifdef __cplusplus
}
#endif

#endif  // RUNTIME_PARSE_STACK_H_
