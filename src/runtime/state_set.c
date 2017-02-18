#include "runtime/state_set.h"
#include <string.h>
#include "runtime/alloc.h"

#define STATE_SET_LONG_LENGTH 32

StateSet ts_state_set_new(TSStateId state) {
  StateSet result;
  result.short_contents[0] = state;
  result.length = 1;
  return result;
}

void ts_state_set_delete(StateSet *self) {
  if (self->length > STATE_SET_SHORT_LENGTH) {
    ts_free(self->long_contents);
  }
}

void ts_state_set_add(StateSet *self, TSStateId state) {
  if (self->length < STATE_SET_SHORT_LENGTH) {
    self->short_contents[self->length] = state;
  } else if (self->length == STATE_SET_SHORT_LENGTH) {
    TSStateId *long_contents = ts_calloc(STATE_SET_LONG_LENGTH, sizeof(TSStateId));
    memcpy(long_contents, self->short_contents, self->length * sizeof(TSStateId));
    self->long_contents = long_contents;
    self->long_contents[self->length] = state;
  } else if (self->length < STATE_SET_LONG_LENGTH) {
    self->long_contents[self->length] = state;
  } else {
    self->long_contents = ts_realloc(self->long_contents, (self->length + 1) * sizeof(TSStateId));
    self->long_contents[self->length] = state;
  }
  self->length++;
}

const TSStateId *ts_state_set_contents(const StateSet *self) {
  if (self->length <= STATE_SET_SHORT_LENGTH) {
    return self->short_contents;
  } else {
    return self->long_contents;
  }
}

bool ts_state_set_eq(const StateSet *self, const StateSet *other) {
  if (self->length != other->length) return false;
  const TSStateId *contents = ts_state_set_contents(self);
  const TSStateId *other_contents = ts_state_set_contents(other);
  for (uint32_t i = 0; i < self->length; i++) {
    if (contents[i] != other_contents[i]) return false;
  }
  return true;
}

bool ts_state_set_has(const StateSet *self, TSStateId state) {
  const TSStateId *contents = ts_state_set_contents(self);
  for (uint32_t i = 0; i < self->length; i++) {
    if (contents[i] == state) return true;
  }
  return false;
}
