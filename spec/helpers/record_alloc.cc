#include <stdlib.h>
#include <map>
#include <set>
#include "bandit/bandit.h"

using std::map;
using std::set;

static bool _enabled = false;
static size_t _allocation_count = 0;
static map<void *, size_t> _outstanding_allocations;

namespace record_alloc {

void start() {
  _enabled = true;
  _allocation_count = 0;
  _outstanding_allocations.clear();
}

void stop() {
  _enabled = false;
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

extern "C" {

static void *record_allocation(void *result) {
  if (!_enabled)
    return result;

  _outstanding_allocations[result] = _allocation_count;
  _allocation_count++;
  return result;
}

static void record_deallocation(void *pointer) {
  if (!_enabled)
    return;

  auto entry = _outstanding_allocations.find(pointer);
  if (entry != _outstanding_allocations.end()) {
    _outstanding_allocations.erase(entry);
  }
}

void *ts_record_malloc(size_t size) {
  return record_allocation(malloc(size));
}

void *ts_record_realloc(void *pointer, size_t size) {
  record_deallocation(pointer);
  return record_allocation(realloc(pointer, size));
}

void *ts_record_calloc(size_t count, size_t size) {
  return record_allocation(calloc(count, size));
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
