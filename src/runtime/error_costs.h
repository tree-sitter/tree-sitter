#ifndef RUNTIME_ERROR_COSTS_H_
#define RUNTIME_ERROR_COSTS_H_

#define ERROR_COST_PER_SKIPPED_TREE 10
#define ERROR_COST_PER_SKIPPED_LINE 3
#define ERROR_COST_PER_SKIPPED_CHAR 0

typedef struct {
  unsigned cost;
  unsigned count;
  unsigned push_count;
} ErrorStatus;

static inline unsigned error_status_min_cost(ErrorStatus status) {
  return status.cost +
    ERROR_COST_PER_SKIPPED_TREE * status.count * status.count;
}

static inline unsigned error_status_max_cost(ErrorStatus status) {
  return status.cost +
    ERROR_COST_PER_SKIPPED_TREE * status.count * status.count +
    (6 * ERROR_COST_PER_SKIPPED_TREE * status.count + 12 * ERROR_COST_PER_SKIPPED_TREE) /
    (1 + status.push_count / 2);
}

static inline int error_status_compare(ErrorStatus a, ErrorStatus b) {
  if ((a.count + 1 < b.count) || (a.count < b.count && a.cost <= b.cost))
    return -1;
  if ((a.count > b.count + 1) || (b.count < a.count && b.cost <= a.cost))
    return 1;

  if (error_status_max_cost(a) < error_status_min_cost(b))
    return -1;
  if (error_status_min_cost(a) > error_status_max_cost(b))
    return 1;

  return 0;
}

#endif
