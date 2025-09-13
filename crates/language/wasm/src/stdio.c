#include <stdio.h>

typedef struct {
  bool left_justify;   // -
  bool zero_pad;       // 0
  bool show_sign;      // +
  bool space_prefix;   // ' '
  bool alternate_form; // #
} format_flags_t;

static const char* parse_format_spec(
  const char *format,
  int *width,
  int *precision,
  format_flags_t *flags
) {
  *width = 0;
  *precision = -1;
  flags->left_justify = false;
  flags->zero_pad = false;
  flags->show_sign = false;
  flags->space_prefix = false;
  flags->alternate_form = false;

  const char *p = format;

  // Parse flags
  while (*p == '-' || *p == '+' || *p == ' ' || *p == '#' || *p == '0') {
    switch (*p) {
      case '-': flags->left_justify = true; break;
      case '0': flags->zero_pad = true; break;
      case '+': flags->show_sign = true; break;
      case ' ': flags->space_prefix = true; break;
      case '#': flags->alternate_form = true; break;
    }
    p++;
  }

  // width
  while (*p >= '0' && *p <= '9') {
    *width = (*width * 10) + (*p - '0');
    p++;
  }

  // precision
  if (*p == '.') {
    p++;
    *precision = 0;
    while (*p >= '0' && *p <= '9') {
      *precision = (*precision * 10) + (*p - '0');
      p++;
    }
  }

  return p;
}

static int int_to_str(
  long long value,
  char *buffer,
  int base,
  bool is_signed,
  bool uppercase
) {
  if (base < 2 || base > 16) return 0;

  const char *digits = uppercase ? "0123456789ABCDEF" : "0123456789abcdef";
  char temp[32];
  int i = 0, len = 0;
  bool is_negative = false;

  if (value == 0) {
    buffer[0] = '0';
    buffer[1] = '\0';
    return 1;
  }

  if (is_signed && value < 0 && base == 10) {
    is_negative = true;
    value = -value;
  }

  unsigned long long uval = (unsigned long long)value;
  while (uval > 0) {
    temp[i++] = digits[uval % base];
    uval /= base;
  }

  if (is_negative) {
    buffer[len++] = '-';
  }

  while (i > 0) {
    buffer[len++] = temp[--i];
  }

  buffer[len] = '\0';
  return len;
}

static int ptr_to_str(void *ptr, char *buffer) {
  buffer[0] = '0';
  buffer[1] = 'x';
  int len = int_to_str((uintptr_t)ptr, buffer + 2, 16, 0, 0);
  return 2 + len;
}

size_t strlen(const char *str) {
  const char *s = str;
  while (*s) s++;
  return s - str;
}

char *strncpy(char *dest, const char *src, size_t n) {
  char *d = dest;
  const char *s = src;
  while (n-- && (*d++ = *s++));
  if (n == (size_t)-1) *d = '\0';
  return dest;
}

static int write_formatted_to_buffer(
  char *buffer,
  size_t buffer_size,
  size_t *pos,
  const char *str,
  int width,
  const format_flags_t *flags
) {
  int len = strlen(str);
  int written = 0;
  int pad_len = (width > len) ? (width - len) : 0;
  int zero_pad = flags->zero_pad && !flags->left_justify;

  if (!flags->left_justify && pad_len > 0) {
    char pad_char = zero_pad ? '0' : ' ';
    for (int i = 0; i < pad_len && *pos < buffer_size - 1; i++) {
      buffer[(*pos)++] = pad_char;
      written++;
    }
  }

  for (int i = 0; i < len && *pos < buffer_size - 1; i++) {
    buffer[(*pos)++] = str[i];
    written++;
  }

  if (flags->left_justify && pad_len > 0) {
    for (int i = 0; i < pad_len && *pos < buffer_size - 1; i++) {
      buffer[(*pos)++] = ' ';
      written++;
    }
  }

  return written;
}

static int vsnprintf_impl(char *buffer, size_t buffsz, const char *format, va_list args) {
  if (!buffer || buffsz == 0 || !format) return -1;

  size_t pos = 0;
  int total_chars = 0;
  const char *p = format;

  while (*p) {
    if (*p == '%') {
      p++;
      if (*p == '%') {
        if (pos < buffsz - 1) buffer[pos++] = '%';
        total_chars++;
        p++;
        continue;
      }

      int width, precision;
      format_flags_t flags;
      p = parse_format_spec(p, &width, &precision, &flags);

      char temp_buf[64];
      const char *output_str = temp_buf;

      switch (*p) {
        case 's': {
          const char *str = va_arg(args, const char*);
          if (!str) str = "(null)";

          int str_len = strlen(str);
          if (precision >= 0 && str_len > precision) {
            strncpy(temp_buf, str, precision);
            temp_buf[precision] = '\0';
            output_str = temp_buf;
          } else {
            output_str = str;
          }
          break;
        }
        case 'd':
        case 'i': {
          int value = va_arg(args, int);
          int_to_str(value, temp_buf, 10, true, false);
          break;
        }
        case 'u': {
          unsigned int value = va_arg(args, unsigned int);
          int_to_str(value, temp_buf, 10, false, false);
          break;
        }
        case 'x': {
          unsigned int value = va_arg(args, unsigned int);
          int_to_str(value, temp_buf, 16, false, false);
          break;
        }
        case 'X': {
          unsigned int value = va_arg(args, unsigned int);
          int_to_str(value, temp_buf, 16, false, true);
          break;
        }
        case 'p': {
          void *ptr = va_arg(args, void*);
          ptr_to_str(ptr, temp_buf);
          break;
        }
        case 'c': {
          int c = va_arg(args, int);
          temp_buf[0] = (char)c;
          temp_buf[1] = '\0';
          break;
        }
        case 'z': {
          if (*(p + 1) == 'u') {
            size_t value = va_arg(args, size_t);
            int_to_str(value, temp_buf, 10, false, false);
            p++;
          } else {
            temp_buf[0] = 'z';
            temp_buf[1] = '\0';
          }
          break;
        }
        default:
          temp_buf[0] = '%';
          temp_buf[1] = *p;
          temp_buf[2] = '\0';
          break;
      }

      int str_len = strlen(output_str);
      int formatted_len = (width > str_len) ? width : str_len;
      total_chars += formatted_len;

      if (pos < buffsz - 1) {
        write_formatted_to_buffer(buffer, buffsz, &pos, output_str, width, &flags);
      }

    } else {
      if (pos < buffsz - 1) buffer[pos++] = *p;
      total_chars++;
    }
    p++;
  }

  if (buffsz > 0) buffer[pos < buffsz ? pos : buffsz - 1] = '\0';

  return total_chars;
}

int snprintf(char *restrict buffer, size_t buffsz, const char *restrict format, ...) {
  if (!buffer || buffsz == 0 || !format) return -1;

  va_list args;
  va_start(args, format);
  int result = vsnprintf_impl(buffer, buffsz, format, args);
  va_end(args);

  return result;
}

int vsnprintf(char *restrict buffer, size_t buffsz, const char *restrict format, va_list vlist) {
  return vsnprintf_impl(buffer, buffsz, format, vlist);
}

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

size_t fwrite(const void *restrict buffer, size_t size, size_t nmemb, FILE *restrict stream) {
  return size * nmemb;
}

int fprintf(FILE *restrict stream, const char *restrict format, ...) {
  return 0;
}
