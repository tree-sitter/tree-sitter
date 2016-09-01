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

static double error_threshold(unsigned push_count) {
  return 6 * ERROR_COST_PER_SKIPPED_TREE / (1 + push_count / 2);
}

static inline int error_status_compare(ErrorStatus a, ErrorStatus b) {
  // TODO remove
  a.cost += ERROR_COST_PER_SKIPPED_TREE * a.count;
  b.cost += ERROR_COST_PER_SKIPPED_TREE * b.count;

  if ((a.count + 1 < b.count) ||
      (a.count < b.count && a.cost <= b.cost)) {
    return -1;
  }

  if ((b.count + 1 < a.count) ||
      (b.count < a.count && b.cost <= a.cost)) {
    return 1;
  }

  if (a.cost == b.cost) {
    if (a.cost + error_threshold(a.push_count) < b.cost) {
      return -1;
    }

    if (b.cost + error_threshold(b.push_count) < a.cost) {
      return 1;
    }
  }

  return 0;
}

#endif
