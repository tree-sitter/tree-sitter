#include "runtime/error_costs.h"
#include <math.h>

static inline unsigned error_status__min_cost(ErrorStatus status) {
  return status.cost + ERROR_COST_PER_SKIPPED_TREE * status.count * status.count;
}

static inline unsigned error_status__max_cost(ErrorStatus status) {
  return status.cost +
         ERROR_COST_PER_SKIPPED_TREE * status.count * status.count +
         (6 * ERROR_COST_PER_SKIPPED_TREE * status.count +
          12 * ERROR_COST_PER_SKIPPED_TREE) /
           (1 + status.push_count / 2);
}

int error_status_compare(ErrorStatus a, ErrorStatus b) {
  if ((a.count + 1 < b.count) || (a.count < b.count && a.cost <= b.cost))
    return -1;
  if ((a.count > b.count + 1) || (b.count < a.count && b.cost <= a.cost))
    return 1;

  if (error_status__max_cost(a) < error_status__min_cost(b))
    return -1;
  if (error_status__min_cost(a) > error_status__max_cost(b))
    return 1;

  return 0;
}
