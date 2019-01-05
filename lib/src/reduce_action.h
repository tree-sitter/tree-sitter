#ifndef RUNTIME_REDUCE_ACTION_H_
#define RUNTIME_REDUCE_ACTION_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "runtime/array.h"
#include "tree_sitter/runtime.h"

typedef struct {
  uint32_t count;
  TSSymbol symbol;
  int dynamic_precedence;
  unsigned short alias_sequence_id;
} ReduceAction;

typedef Array(ReduceAction) ReduceActionSet;

static inline void ts_reduce_action_set_add(ReduceActionSet *self,
                                            ReduceAction new_action) {
  for (uint32_t i = 0; i < self->size; i++) {
    ReduceAction action = self->contents[i];
    if (action.symbol == new_action.symbol && action.count == new_action.count)
      return;
  }
  array_push(self, new_action);
}

#ifdef __cplusplus
}
#endif

#endif  // RUNTIME_REDUCE_ACTION_H_
