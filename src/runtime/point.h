#ifndef RUNTIME_POINT_H_
#define RUNTIME_POINT_H_

#include "tree_sitter/runtime.h"

static inline TSPoint ts_point_add(TSPoint a, TSPoint b) {
  if (b.row > 0)
    return (TSPoint){a.row + b.row, b.column};
  else
    return (TSPoint){a.row, a.column + b.column};
}

static inline TSPoint ts_point_sub(TSPoint a, TSPoint b) {
  if (a.row > b.row)
    return (TSPoint){a.row - b.row, a.column};
  else
    return (TSPoint){0, a.column - b.column};
}

static inline bool ts_point_lte(TSPoint a, TSPoint b) {
  return (a.row < b.row) || (a.row == b.row && a.column <= b.column);
}

static inline bool ts_point_lt(TSPoint a, TSPoint b) {
  return (a.row < b.row) || (a.row == b.row && a.column < b.column);
}

static inline bool ts_point_eq(TSPoint a, TSPoint b) {
  return a.row == b.row && a.column == b.column;
}

static inline TSPoint ts_point_min(TSPoint a, TSPoint b) {
  if (a.row < b.row || (a.row == b.row && a.column < b.column))
    return a;
  else
    return b;
}

static inline TSPoint ts_point_max(TSPoint a, TSPoint b) {
  if (a.row > b.row || (a.row == b.row && a.column > b.column))
    return a;
  else
    return b;
}

#endif
