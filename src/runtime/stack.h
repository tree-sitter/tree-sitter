#ifndef RUNTIME_PARSE_STACK_H_
#define RUNTIME_PARSE_STACK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "tree_sitter/parser.h"
#include "runtime/array.h"
#include "runtime/tree.h"
#include <stdio.h>

typedef struct Stack Stack;

typedef unsigned int StackVersion;

#define STACK_VERSION_NONE ((StackVersion)-1)

typedef struct {
  TreeArray trees;
  StackVersion version;
} StackSlice;

typedef Array(StackSlice) StackSliceArray;

typedef struct {
  enum {
    StackPopFailed,
    StackPopStoppedAtError,
    StackPopSucceeded,
  } status;
  StackSliceArray slices;
} StackPopResult;

enum {
  StackIterateNone,
  StackIterateStop = 1 << 0,
  StackIteratePop = 1 << 1,
};

typedef unsigned int StackIterateAction;

typedef StackIterateAction (*StackIterateCallback)(void *, TSStateId state,
                                                   TreeArray *trees,
                                                   size_t tree_count,
                                                   bool is_done,
                                                   bool is_pending);

/*
 *  Create a parse stack.
 */
Stack *ts_stack_new();

/*
 *  Release any resources reserved by a parse stack.
 */
void ts_stack_delete(Stack *);

/*
 *  Get the stack's current number of versions.
 */
size_t ts_stack_version_count(const Stack *);

/*
 *  Get the state at the top of the given version of the stack. If the stack is
 *  empty, this returns the initial state (0).
 */
TSStateId ts_stack_top_state(const Stack *, StackVersion);

/*
 *  Get the position at the top of the given version of the stack. If the stack
 *  is empty, this returns zero.
 */
TSLength ts_stack_top_position(const Stack *, StackVersion);

size_t ts_stack_error_length(const Stack *, StackVersion);

size_t ts_stack_last_repaired_error_size(const Stack *, StackVersion);

/*
 *  Push a tree and state onto the given head of the stack. This could cause
 *  the version to merge with an existing version.
 */
bool ts_stack_push(Stack *, StackVersion, TSTree *, bool, TSStateId);

/*
 *  Pop the given number of entries from the given version of the stack. This
 *  operation can increase the number of stack versions by revealing multiple
 *  versions which had previously been merged. It returns a struct that
 *  indicates the index of each revealed version and the trees removed from that
 *  version.
 */
StackPopResult ts_stack_pop_count(Stack *, StackVersion, size_t count);

StackPopResult ts_stack_iterate(Stack *, StackVersion, StackIterateCallback,
                                void *);

StackPopResult ts_stack_pop_pending(Stack *, StackVersion);

StackPopResult ts_stack_pop_all(Stack *, StackVersion);

void ts_stack_merge_from(Stack *, StackVersion);

void ts_stack_merge(Stack *);

void ts_stack_renumber_version(Stack *, StackVersion, StackVersion);

StackVersion ts_stack_duplicate_version(Stack *, StackVersion);

/*
 *  Remove the given version from the stack.
 */
void ts_stack_remove_version(Stack *, StackVersion);

/*
 *  Remove all entries from the stack.
 */
void ts_stack_clear(Stack *);

int ts_stack_print_dot_graph(Stack *, const char **, FILE *);

#ifdef __cplusplus
}
#endif

#endif  // RUNTIME_PARSE_STACK_H_
