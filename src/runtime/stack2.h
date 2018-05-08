#ifndef RUNTIME_STACK2_H_
#define RUNTIME_STACK2_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "runtime/array.h"
#include "runtime/syntax_tree.h"
#include <stdio.h>

typedef struct Stack Stack;

typedef unsigned StackVersion;
#define STACK_VERSION_NONE ((StackVersion)-1)

typedef struct {
  Length position;
  unsigned depth;
  TSStateId state;
} StackSummaryEntry;

typedef Array(TSStateId *) StateArray;
typedef Array(StackSummaryEntry) StackSummary;

typedef void (*StackIterateCallback)(void *, TSStateId, uint32_t);

// Lifecycle

Stack *ts_stack2_new();
void ts_stack2_delete(Stack *);

// Queries

uint32_t ts_stack2_version_count(const Stack *);
TSStateId ts_stack2_state(const Stack *, StackVersion);
Length ts_stack2_position(const Stack *, StackVersion);
uint32_t ts_stack2_node_count_since_error(const Stack *, StackVersion);
int32_t ts_stack2_dynamic_precedence(const Stack *, StackVersion);
uint32_t ts_stack2_error_cost(const Stack *, StackVersion);
void ts_stack2_record_summary(Stack *, StackVersion, unsigned);
StackSummary *ts_stack2_get_summary(Stack *, StackVersion);

// Mutations

void ts_stack2_push_leaf(Stack *, StackVersion, TSStateId, LeafNodeParams);
void ts_stack2_push_existing(Stack *, StackVersion, TSStateId, TreeCursor *);
void ts_stack2_push_error(Stack *, StackVersion);
void ts_stack2_reduce(Stack *, StackVersion, InternalNodeParams, StateArray *);
BreakdownResult *ts_stack2_breakdown(Stack *, StackVersion, StateArray *);

// Version management

bool ts_stack2_can_merge(Stack *, StackVersion, StackVersion);
bool ts_stack2_merge(Stack *, StackVersion, StackVersion);
void ts_stack2_renumber_version(Stack *, StackVersion, StackVersion);
void ts_stack2_swap_versions(Stack *, StackVersion, StackVersion);
void ts_stack2_remove_version(Stack *, StackVersion);
void ts_stack2_clear(Stack *);
TSSymbol ts_stack2_resume(Stack *, StackVersion);
void ts_stack2_pause(Stack *, StackVersion, TSSymbol);
void ts_stack2_halt(Stack *, StackVersion);
bool ts_stack2_is_active(const Stack *, StackVersion);
bool ts_stack2_is_paused(const Stack *, StackVersion);
bool ts_stack2_is_halted(const Stack *, StackVersion);

StackVersion ts_stack2_copy_version(Stack *, StackVersion);

// Debugging

bool ts_stack2_print_dot_graph(Stack *, const TSLanguage *, FILE *);
void ts_stack2_iterate(Stack *, StackVersion, StackIterateCallback, void *);

#ifdef __cplusplus
}
#endif

#endif  // RUNTIME_STACK2_H_
