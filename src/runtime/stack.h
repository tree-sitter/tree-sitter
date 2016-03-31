#ifndef RUNTIME_PARSE_STACK_H_
#define RUNTIME_PARSE_STACK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "tree_sitter/parser.h"
#include "runtime/array.h"
#include "runtime/tree.h"

typedef struct Stack Stack;

typedef struct {
  TreeArray trees;
  int head_index;
} StackSlice;

typedef Array(StackSlice) StackSliceArray;

typedef enum {
  StackPushFailed,
  StackPushMerged,
  StackPushContinued,
} StackPushResult;

typedef struct {
  enum {
    StackPopFailed,
    StackPopStoppedAtError,
    StackPopSucceeded,
  } status;
  StackSliceArray slices;
} StackPopResult;

typedef enum {
  StackIterateContinue,
  StackIterateAbort,
  StackIteratePop,
} StackIterateAction;

typedef StackIterateAction (*StackIterateCallback)(void *, TSStateId state,
                                                   size_t tree_count,
                                                   bool is_done,
                                                   bool is_pending);

typedef int (*TreeSelectionFunction)(void *, TSTree *tree1, TSTree *tree2);

/*
 *  Create a parse stack.
 */
Stack *ts_stack_new();

/*
 *  Release any resources reserved by a parse stack.
 */
void ts_stack_delete(Stack *);

/*
 *  Get the stack's current number of heads.
 */
int ts_stack_head_count(const Stack *);

/*
 *  Get the state at given head of the stack. If the stack is empty, this
 *  returns the initial state (0).
 */
TSStateId ts_stack_top_state(const Stack *, int head_index);

/*
 *  Get the position of the given head of the stack. If the stack is empty, this
 *  returns {0, 0}.
 */
TSLength ts_stack_top_position(const Stack *, int head_index);

/*
 *  Push a (tree, state) pair onto the given head of the stack. This could cause
 *  the head to merge with an existing head.
 */
StackPushResult ts_stack_push(Stack *, int head_index, TSTree *, bool,
                              TSStateId);

/*
 *  Pop the given number of entries from the given head of the stack. This
 *  operation can increase the number of stack heads by revealing multiple heads
 *  which had previously been merged. It returns a struct that indicates the
 *  index of each revealed head and the trees removed from that head.
 */
StackPopResult ts_stack_pop_count(Stack *, int head_index, int count);

StackPopResult ts_stack_pop_until(Stack *, int head_index, StackIterateCallback,
                                  void *);

StackPopResult ts_stack_pop_pending(Stack *, int head_index);

/*
 *  Remove the given number of entries from the given head of the stack.
 */
void ts_stack_shrink(Stack *, int head_index, int count);

/*
 *  Split the given stack head into two heads, so that the stack can be
 *  transformed from its current state in multiple alternative ways. Returns
 *  the index of the newly-created head.
 */
int ts_stack_split(Stack *, int head_index);

/*
 *  Remove the given head from the stack.
 */
void ts_stack_remove_head(Stack *, int head_index);

/*
 *  Remove all entries from the stack.
 */
void ts_stack_clear(Stack *);

void ts_stack_set_tree_selection_callback(Stack *, void *,
                                          TreeSelectionFunction);

char *ts_stack_dot_graph(Stack *, const char **);

#ifdef __cplusplus
}
#endif

#endif  // RUNTIME_PARSE_STACK_H_
