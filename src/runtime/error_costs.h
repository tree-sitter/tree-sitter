#ifndef RUNTIME_ERROR_COSTS_H_
#define RUNTIME_ERROR_COSTS_H_

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define ERROR_STATE 0
#define ERROR_COST_PER_SKIPPED_TREE 100
#define ERROR_COST_PER_SKIPPED_LINE 30
#define ERROR_COST_PER_SKIPPED_CHAR 1

typedef struct {
  unsigned cost;
  unsigned push_count;
  unsigned depth;
  bool recovering;
} ErrorStatus;

typedef enum {
  ErrorComparisonTakeLeft,
  ErrorComparisonPreferLeft,
  ErrorComparisonNone,
  ErrorComparisonPreferRight,
  ErrorComparisonTakeRight,
} ErrorComparison;

ErrorComparison error_status_compare(ErrorStatus a, ErrorStatus b, bool can_merge);

#ifdef __cplusplus
}
#endif

#endif
