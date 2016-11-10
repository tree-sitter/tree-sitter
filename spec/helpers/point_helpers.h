#ifndef HELPERS_POINT_HELPERS_H_
#define HELPERS_POINT_HELPERS_H_

#include "runtime/length.h"
#include <ostream>

bool operator==(const TSPoint &left, const TSPoint &right);

bool operator<(const TSPoint &left, const TSPoint &right);

bool operator>(const TSPoint &left, const TSPoint &right);

bool operator==(const TSRange &left, const TSRange &right);

bool operator==(const Length &left, const Length &right);

std::ostream &operator<<(std::ostream &stream, const TSPoint &point);

std::ostream &operator<<(std::ostream &stream, const TSRange &range);

std::ostream &operator<<(std::ostream &stream, const Length &length);

#endif  // HELPERS_POINT_HELPERS_H_
