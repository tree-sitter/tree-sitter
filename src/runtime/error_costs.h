#ifndef RUNTIME_ERROR_COSTS_H_
#define RUNTIME_ERROR_COSTS_H_

#define ERROR_COST_PER_SKIPPED_TREE 10
#define ERROR_COST_PER_SKIPPED_LINE 3
#define ERROR_COST_PER_SKIPPED_CHAR 0

typedef struct {
  unsigned cost;
  unsigned count;
  unsigned depth;
} ErrorStatus;

static inline int error_status_compare(ErrorStatus a, ErrorStatus b) {
  static unsigned ERROR_COST_THRESHOLD = 3 * ERROR_COST_PER_SKIPPED_TREE;
  static unsigned ERROR_COUNT_THRESHOLD = 1;

  // TODO remove
  a.cost += ERROR_COST_PER_SKIPPED_TREE * a.count;
  b.cost += ERROR_COST_PER_SKIPPED_TREE * b.count;

  if ((a.count + ERROR_COUNT_THRESHOLD < b.count) ||
      (a.count < b.count && a.cost <= b.cost)) {
    return -1;
  }

  if ((b.count + ERROR_COUNT_THRESHOLD < a.count) ||
      (b.count < a.count && b.cost <= a.cost)) {
    return 1;
  }

  if (a.cost + ERROR_COST_THRESHOLD < b.cost) {
    return -1;
  }

  if (b.cost + ERROR_COST_THRESHOLD < a.cost) {
    return 1;
  }

  return 0;
}

#endif
