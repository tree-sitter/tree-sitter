#ifndef HELPERS_POINT_HELPERS_H_
#define HELPERS_POINT_HELPERS_H_

bool operator==(const TSPoint &left, const TSPoint &right);

bool operator<(const TSPoint &left, const TSPoint &right);

bool operator>(const TSPoint &left, const TSPoint &right);

bool operator==(const TSRange &left, const TSRange &right);

std::ostream &operator<<(std::ostream &stream, const TSPoint &point);

std::ostream &operator<<(std::ostream &stream, const TSRange &range);

#endif  // HELPERS_POINT_HELPERS_H_
