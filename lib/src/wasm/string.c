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

int strcmp(const char *left, const char *right) {
  while (*left && *left == *right) {
    left++;
    right++;
  }
  return *(unsigned char *)left - *(unsigned char *)right;
}

size_t strlen(const char *str) {
  const char *s = str;
  while (*s) s++;
  return s - str;
}

char *strncat(char *restrict dest, const char *restrict src, size_t count) {
  char *result = dest;
  while (*dest) dest++;
  while (count-- && (*dest++ = *src++));
  if (count == (size_t)-1) *dest = '\0';
  return result;
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

char *strncpy(char *restrict dest, const char *restrict src, size_t count) {
  char *result = dest;
  while (count && (*dest++ = *src++)) count--;
  while (count--) *dest++ = '\0';
  return result;
}
