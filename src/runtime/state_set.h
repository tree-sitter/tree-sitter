#ifndef RUNTIME_STATE_SET_H_
#define RUNTIME_STATE_SET_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "tree_sitter/parser.h"

#define STATE_SET_SHORT_LENGTH (sizeof(TSStateId *) / sizeof(TSStateId))

typedef struct {
  union {
    TSStateId *long_contents;
    TSStateId short_contents[STATE_SET_SHORT_LENGTH];
  };
  uint32_t length;
} StateSet;

StateSet ts_state_set_new(TSStateId state);
void ts_state_set_delete(StateSet *self);
void ts_state_set_add(StateSet *self, TSStateId state);
const TSStateId *ts_state_set_contents(const StateSet *self);
bool ts_state_set_eq(const StateSet *, const StateSet *);
bool ts_state_set_has(const StateSet *, TSStateId);

#ifdef __cplusplus
}
#endif

#endif  // RUNTIME_STATE_SET_H_
