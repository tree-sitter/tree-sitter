#ifndef RUNTIME_STRING_INPUT_H_
#define RUNTIME_STRING_INPUT_H_

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
TSStateId *ts_state_set_contents(StateSet *self);

#ifdef __cplusplus
}
#endif

#endif  // RUNTIME_STRING_INPUT_H_
