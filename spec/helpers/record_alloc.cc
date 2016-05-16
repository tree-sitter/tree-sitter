#include <stdlib.h>
#include <map>
#include <set>
#include "bandit/bandit.h"

using std::map;
using std::set;

bool _enabled = false;
static size_t _allocation_count = 0;
static map<void *, size_t> _outstanding_allocations;
static size_t _allocation_failure_index = -1;

namespace record_alloc {

void start() {
  _enabled = true;
  _allocation_count = 0;
  _outstanding_allocations.clear();
  _allocation_failure_index = -1;
}

void stop() {
  _enabled = false;
}

void fail_at_allocation_index(size_t failure_index) {
  _allocation_failure_index = failure_index;
}

set<size_t> outstanding_allocation_indices() {
  set<size_t> result;
  for (const auto &entry : _outstanding_allocations) {
    result.insert(entry.second);
  }
  return result;
}

size_t allocation_count() {
  return _allocation_count;
}

}  // namespace record_alloc

static bool can_allocate() {
  if (!_enabled)
    return true;

  return _allocation_count < _allocation_failure_index;
}

static void *record_allocation(void *result) {
  if (!_enabled)
    return result;

  _outstanding_allocations[result] = _allocation_count;
  _allocation_count++;
  return result;
}

static void record_allocation_failure() {
  _allocation_count++;
}

static void record_deallocation(void *pointer) {
  if (!_enabled)
    return;

  auto entry = _outstanding_allocations.find(pointer);
  if (entry != _outstanding_allocations.end()) {
    _outstanding_allocations.erase(entry);
  }
}

extern "C" {

void *ts_record_malloc(size_t size) {
  if (can_allocate()) {
    return record_allocation(malloc(size));
  } else {
    record_allocation_failure();
    return NULL;
  }
}

void *ts_record_realloc(void *pointer, size_t size) {
  if (can_allocate()) {
    record_deallocation(pointer);
    return record_allocation(realloc(pointer, size));
  } else {
    record_allocation_failure();
    return NULL;
  }
}

void *ts_record_calloc(size_t count, size_t size) {
  if (can_allocate()) {
    return record_allocation(calloc(count, size));
  } else {
    record_allocation_failure();
    return NULL;
  }
}

void ts_record_free(void *pointer) {
  free(pointer);
  record_deallocation(pointer);
}

bool ts_record_allocations_toggle(bool value) {
  bool previous_value = _enabled;
  _enabled = value;
  return previous_value;
}

}
