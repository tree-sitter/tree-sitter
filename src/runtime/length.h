#ifndef RUNTIME_LENGTH_H_
#define RUNTIME_LENGTH_H_

#include "tree_sitter/runtime.h"
#include <stdbool.h>

static inline TSLength ts_length_add(TSLength len1, TSLength len2) {
  TSLength result;
  result.bytes = len1.bytes + len2.bytes;
  result.chars = len1.chars + len2.chars;

  if ((len1.chars > 0 && len1.bytes == 0) || (len2.chars > 0 && len2.bytes == 0))
    result.bytes = 0;

  return result;
}

static inline TSLength ts_length_sub(TSLength len1, TSLength len2) {
  TSLength result;
  result.bytes = len1.bytes - len2.bytes;
  result.chars = len1.chars - len2.chars;

  if ((len1.chars > 0 && len1.bytes == 0) || (len2.chars > 0 && len2.bytes == 0))
    result.bytes = 0;

  return result;
}

static inline TSPoint ts_point_add(TSPoint point1, TSPoint point2) {
	size_t row = point1.row + point2.row;

	size_t column;
	if (point2.row == 0) {
		column = point1.column + point2.column;
	} else {
		column = point2.column;
	}

  return (TSPoint){ .row = row, .column = column };
}

static inline TSPoint ts_point_sub(TSPoint point1, TSPoint point2) {
	size_t row, column;
	if (point1.row == point2.row) {
		row = 0;
		column = point1.column - point2.column;
	} else {
		row = point1.row - point2.row;
		column = point1.column;
	}

  return (TSPoint){ .row = row, .column = column };
}

static inline TSLength ts_length_zero() {
  TSLength result;
  result.bytes = result.chars = 0;
  return result;
}

static inline bool ts_length_eq(TSLength len1, TSLength len2) {
  return len1.bytes == len2.bytes && len1.chars == len2.chars;
}

static inline TSPoint ts_point_zero() {
	return (TSPoint){ .row = 1, .column = 1 };
}

static inline TSPoint ts_point_make(size_t row, size_t column) {
	return (TSPoint){ .row = row, .column = column };
}

static inline TSLength ts_length_make(size_t bytes, size_t chars) {
  TSLength result;
  result.bytes = bytes;
  result.chars = chars;
  return result;
}

#endif
