#ifndef HELPERS_RECORD_ALLOC_H_
#define HELPERS_RECORD_ALLOC_H_

#include <vector>

namespace record_alloc {

void start(bool multi_threaded_mode = false);
void stop();
void fail_at_allocation_index(size_t failure_index);
std::vector<size_t> outstanding_allocation_indices();
size_t allocation_count();

}  // namespace record_alloc

#endif  // HELPERS_RECORD_ALLOC_H_
