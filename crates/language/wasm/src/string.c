#include <string.h>

// Derived from musl (MIT): https://git.musl-libc.org/cgit/musl/tree/src/string/memchr.c
void *memchr(const void *src, int c, size_t n) {
	const unsigned char *s = src;
	c = (unsigned char)c;
	for (; n && *s != c; s++, n--);
	return n ? (void *)s : 0;
}

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

char *strchr(const char *str, int c) {
  while (*str != (char)c) {
    if (*str == '\0') {
      return 0;
    }
    str++;
  }
  return (char *)str;
}

size_t strlen(const char *str) {
  const char *s = str;
  while (*s) s++;
  return s - str;
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

char *strncat(char *dst, const char *src, size_t n) {
  char *dst_cursor = dst;
  while (*dst_cursor) {
    dst_cursor++;
  }

  size_t count = 0;
  while (*src && count < n) {
    *dst_cursor = *src;
    dst_cursor++;
    src++;
  }
  *dst_cursor = '\0';

  return dst;
}

int strcmp(const char *left, const char *right) {
  while (*left && (*left == *right)) {
    left++;
    right++;
  }
  return *(const unsigned char *)left - *(const unsigned char *)right;
}

char *strncpy(char *dest, const char *src, size_t n) {
  char *d = dest;
  const char *s = src;
  while (n-- && (*d++ = *s++));
  if (n == (size_t)-1) *d = '\0';
  return dest;
}
