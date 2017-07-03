#include "runtime/error_costs.h"

static const unsigned MAX_COST_DIFFERENCE = 16 * ERROR_COST_PER_SKIPPED_TREE;
static const unsigned MAX_PUSH_COUNT_WITH_COUNT_DIFFERENCE = 24;
static const unsigned MAX_DEPTH_TO_ALLOW_MULTIPLE = 12;

ErrorComparison error_status_compare(ErrorStatus a, ErrorStatus b, bool are_mergeable) {
  if (a.count < b.count) {
    if (are_mergeable ||
        a.cost <= b.cost ||
        a.count + 1 < b.count ||
        b.push_count > MAX_PUSH_COUNT_WITH_COUNT_DIFFERENCE) {
      return ErrorComparisonTakeLeft;
    } else {
      return ErrorComparisonPreferLeft;
    }
  }

  if (b.count < a.count) {
    if (are_mergeable ||
        b.cost <= a.cost ||
        b.count + 1 < a.count ||
        a.push_count > MAX_PUSH_COUNT_WITH_COUNT_DIFFERENCE) {
      return ErrorComparisonTakeRight;
    } else {
      return ErrorComparisonPreferRight;
    }
  }

  if (a.cost < b.cost) {
    if (are_mergeable || (b.cost - a.cost) * (1 + a.push_count) > MAX_COST_DIFFERENCE) {
      return ErrorComparisonTakeLeft;
    } else {
      return ErrorComparisonPreferLeft;
    }
  }

  if (b.cost < a.cost) {
    if (are_mergeable || (a.cost - b.cost) * (1 + b.push_count) > MAX_COST_DIFFERENCE) {
      return ErrorComparisonTakeRight;
    } else {
      return ErrorComparisonPreferRight;
    }
  }

  if (a.count > 0) {
    if (a.depth > MAX_DEPTH_TO_ALLOW_MULTIPLE ||
        b.depth > MAX_DEPTH_TO_ALLOW_MULTIPLE) {
      return a.depth <= b.depth ?
        ErrorComparisonTakeLeft :
        ErrorComparisonTakeRight;
    }
  }

  return ErrorComparisonNone;
}
