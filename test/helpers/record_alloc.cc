#include <stdlib.h>
#include <map>
#include <vector>
#include <mutex>

using std::map;
using std::vector;

static bool _enabled = false;
static size_t _allocation_count = 0;
static map<void *, size_t> _outstanding_allocations;
static std::mutex _outstanding_allocations_mutex;
static bool _multi_threaded_mode = false;

namespace record_alloc {

void start(bool multi_threaded_mode) {
  _enabled = true;
  _allocation_count = 0;
  _outstanding_allocations.clear();
  _multi_threaded_mode = multi_threaded_mode;
}

void stop() {
  _enabled = false;
}

vector<size_t> outstanding_allocation_indices() {
  vector<size_t> result;
  for (const auto &entry : _outstanding_allocations) {
    result.push_back(entry.second);
  }
  return result;
}

size_t allocation_count() {
  size_t result;
  _outstanding_allocations_mutex.lock();
  result = _allocation_count;
  _outstanding_allocations_mutex.unlock();
  return result;
}

}  // namespace record_alloc

extern "C" {

static void *record_allocation(void *result) {
  if (!_enabled) return result;
  if (_multi_threaded_mode) _outstanding_allocations_mutex.lock();
  _outstanding_allocations[result] = _allocation_count;
  _allocation_count++;
  if (_multi_threaded_mode) _outstanding_allocations_mutex.unlock();
  return result;
}

static void record_deallocation(void *pointer) {
  if (_multi_threaded_mode) _outstanding_allocations_mutex.lock();
  auto entry = _outstanding_allocations.find(pointer);
  if (entry != _outstanding_allocations.end()) {
    _outstanding_allocations.erase(entry);
  }
  if (_multi_threaded_mode) _outstanding_allocations_mutex.unlock();
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
  record_deallocation(pointer);
  free(pointer);
}

bool ts_record_allocations_toggle(bool value) {
  bool previous_value = _enabled;
  _enabled = value;
  return previous_value;
}

}
