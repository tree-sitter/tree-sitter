#ifndef HELPERS_POINT_HELPERS_H_
#define HELPERS_POINT_HELPERS_H_

bool operator==(const TSPoint &left, const TSPoint &right);

bool operator<(const TSPoint &left, const TSPoint &right);

bool operator>(const TSPoint &left, const TSPoint &right);

std::ostream &operator<<(std::ostream &stream, const TSPoint &point);

#endif  // HELPERS_POINT_HELPERS_H_
