#ifndef RUNTIME_ERROR_COSTS_H_
#define RUNTIME_ERROR_COSTS_H_

#ifdef __cplusplus
extern "C" {
#endif

#define ERROR_STATE 0
#define ERROR_COST_PER_SKIPPED_TREE 10
#define ERROR_COST_PER_SKIPPED_LINE 3
#define ERROR_COST_PER_SKIPPED_CHAR 0

typedef struct {
  unsigned count;
  unsigned cost;
  unsigned push_count;
} ErrorStatus;

int error_status_compare(ErrorStatus a, ErrorStatus b);

#ifdef __cplusplus
}
#endif

#endif
