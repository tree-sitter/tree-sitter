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
 *  Get the state at given head of the stack. If the stack is empty, this
 *  returns the initial state (0).
 */
TSStateId ts_parse_stack_top_state(const ParseStack *, int head);

/*
 *  Get the tree at given head of the stack. If the stack is empty, this
 *  returns NULL.
 */
TSTree *ts_parse_stack_top_tree(const ParseStack *, int head);

/*
 *  Get the entry at the given head of the stack.
 */
ParseStackEntry *ts_parse_stack_head(ParseStack *, int head);

/*
 *  Get the number of successors for the parse stack entry.
 */
int ts_parse_stack_entry_next_count(const ParseStackEntry *);

/*
 *  Get the given successor for the parse stack entry.
 */
ParseStackEntry *ts_parse_stack_entry_next(const ParseStackEntry *, int);

/*
 *  Push a (tree, state) pair onto the given head of the stack. Returns
 *  a boolean indicating whether the stack head was merged with an
 *  existing head.
 */
bool ts_parse_stack_push(ParseStack *, int head, TSStateId, TSTree *);

/*
 *  Add an alternative tree for the given head of the stack.
 */
void ts_parse_stack_add_alternative(ParseStack *, int head, TSTree *);

/*
 *  Pop the given number of entries from the given head of the stack. This
 *  operation can increase the number of stack heads by revealing multiple heads
 *  which had previously been merged. It returns a struct that indicates the
 *  index of each revealed head and the trees removed from that head.
 */
ParseStackPopResultList ts_parse_stack_pop(ParseStack *, int head, int count, bool count_extra);

/*
 *  Remove the given number of entries from the given head of the stack.
 */
void ts_parse_stack_shrink(ParseStack *, int head, int count);

/*
 *  Split the given stack head into two heads, so that the stack can be
 *  transformed from its current state in multiple alternative ways. Returns
 *  the index of the newly-created head.
 */
int ts_parse_stack_split(ParseStack *, int head);

/*
 *  Remove the given head from the stack.
 */
void ts_parse_stack_remove_head(ParseStack *, int head);

/*
 *  Remove all entries from the stack.
 */
void ts_parse_stack_clear(ParseStack *);

#ifdef __cplusplus
}
#endif

#endif  // RUNTIME_PARSE_STACK_H_
