#include <stdio.h>

int fclose(FILE *stream) {
  return 0;
}

FILE* fdopen(int fd, const char *mode) {
  return 0;
}

int fputc(int c, FILE *stream) {
  return c;
}

int fputs(const char *restrict str, FILE *restrict stream) {
  return 0;
}

size_t fwrite(const void *restrict buffer, size_t size, size_t nmemb, FILE  *stream) {
  return size * nmemb;
}

int fprintf(FILE *restrict stream, const char *restrict format, ...) {
  return 0;
}

int snprintf(char *restrict buffer, size_t buffsz, const char *restrict format, ...) {
  return 0;
}

int vsnprintf(char *restrict buffer, size_t buffsz, const char *restrict format, va_list vlist) {
  return 0;
}
