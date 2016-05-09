#ifndef RUNTIME_REDUCE_ACTION_H_
#define RUNTIME_REDUCE_ACTION_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "runtime/array.h"
#include "tree_sitter/runtime.h"

typedef struct {
  TSSymbol symbol;
  size_t count;
} ReduceAction;

typedef Array(ReduceAction) ReduceActionSet;

static inline bool ts_reduce_action_set_add(ReduceActionSet *self,
                                            ReduceAction new_action) {
  for (size_t i = 0; i < self->size; i++) {
    ReduceAction action = self->contents[i];
    if (action.symbol == new_action.symbol && action.count == new_action.count)
      return true;
  }
  return array_push(self, new_action);
}

#ifdef __cplusplus
}
#endif

#endif  // RUNTIME_REDUCE_ACTION_H_
