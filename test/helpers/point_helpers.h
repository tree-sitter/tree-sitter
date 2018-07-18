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

TSPoint extent_for_string(const std::string &text, size_t end_index = std::string::npos);

TSRange range_for_substring(const std::string &text, const std::string &substring);

#endif  // HELPERS_POINT_HELPERS_H_
