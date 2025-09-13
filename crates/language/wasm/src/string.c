#include <string.h>

int memcmp(const void *lhs, const void *rhs, size_t count) {
  const unsigned char *l = lhs;
  const unsigned char *r = rhs;
  while (count--) {
    if (*l != *r) {
      return *l - *r;
    }
    l++;
    r++;
  }
  return 0;
}

void *memcpy(void *restrict dst, const void *restrict src, size_t size) {
  unsigned char *d = dst;
  const unsigned char *s = src;
  while (size--) {
    *d++ = *s++;
  }
  return dst;
}

void *memmove(void *dst, const void *src, size_t count) {
  unsigned char *d = dst;
  const unsigned char *s = src;
  if (d < s) {
    while (count--) {
      *d++ = *s++;
    }
  } else if (d > s) {
    d += count;
    s += count;
    while (count--) {
      *(--d) = *(--s);
    }
  }
  return dst;
}

void *memset(void *dst, int value, size_t count) {
  unsigned char *p = dst;
  while (count--) {
    *p++ = (unsigned char)value;
  }
  return dst;
}

int strncmp(const char *left, const char *right, size_t n) {
  while (n-- > 0) {
    if (*left != *right) {
      return *(unsigned char *)left - *(unsigned char *)right;
    }
    if (*left == '\0') break;
    left++;
    right++;
  }
  return 0;
}
