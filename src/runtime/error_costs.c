#include "runtime/error_costs.h"

static const unsigned MAX_COST_DIFFERENCE = 16 * ERROR_COST_PER_SKIPPED_TREE;
static const unsigned MAX_PUSH_COUNT_WITH_COUNT_DIFFERENCE = 24;

ErrorComparison error_status_compare(ErrorStatus a, ErrorStatus b, bool are_mergeable) {
  ErrorComparison result = ErrorComparisonNone;

  if (!a.recovering && b.recovering) {
    if (a.push_count > MAX_PUSH_COUNT_WITH_COUNT_DIFFERENCE) {
      return ErrorComparisonTakeLeft;
    } else {
      result = ErrorComparisonPreferLeft;
    }
  }

  if (!b.recovering && a.recovering) {
    if (b.push_count > MAX_PUSH_COUNT_WITH_COUNT_DIFFERENCE) {
      return ErrorComparisonTakeRight;
    } else {
      result = ErrorComparisonPreferRight;
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

  return result;
}
