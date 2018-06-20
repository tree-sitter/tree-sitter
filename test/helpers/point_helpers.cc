#include "./point_helpers.h"
#include <string>
#include <ostream>
#include "runtime/length.h"
#include "tree_sitter/runtime.h"

using namespace std;

bool operator==(const TSPoint &left, const TSPoint &right) {
  return left.row == right.row && left.column == right.column;
}

bool operator==(const TSRange &left, const TSRange &right) {
  return (
    left.start_byte == right.start_byte &&
    left.end_byte == right.end_byte &&
    left.start_point == right.start_point &&
    left.end_point == right.end_point
  );
}

bool operator==(const Length &left, const Length &right) {
  return left.bytes == right.bytes && left.extent == right.extent;
}

bool operator<(const TSPoint &left, const TSPoint &right) {
  if (left.row < right.row) return true;
  if (left.row > right.row) return false;

  return left.column < right.column;
}

bool operator>(const TSPoint &left, const TSPoint &right) {
  return right < left;
}

std::ostream &operator<<(std::ostream &stream, const TSPoint &point) {
  return stream << "{" << point.row << ", " << point.column << "}";
}

std::ostream &operator<<(std::ostream &stream, const TSRange &range) {
  return stream << "{" << range.start_point << ", " << range.end_point << "}";
}

ostream &operator<<(ostream &stream, const Length &length) {
  return stream << "{bytes:" << length.bytes << ", extent:" << length.extent << "}";
}
