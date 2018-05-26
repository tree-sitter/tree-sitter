#ifndef COMPILER_LOG_H_
#define COMPILER_LOG_H_

#include <stdio.h>

namespace tree_sitter {

void set_log_file(FILE *);
FILE *get_log_file();
void _indent_logs();
void _outdent_logs();
void _print_indent();

#define LOG_START(...) \
  do {                 \
    LOG(__VA_ARGS__);  \
    _indent_logs();    \
  } while (0)

#define LOG_END(...) \
  do {               \
    _outdent_logs(); \
  } while (0)

#define LOG(...)               \
  LOG_IF(true, __VA_ARGS__)

#define LOG_IF(condition, ...) \
  do {                         \
    FILE *f = get_log_file();  \
    if (f && condition) {      \
      _print_indent();         \
      fprintf(f, __VA_ARGS__); \
      fputs("\n", f);          \
    }                          \
  } while (0)

}  // namespace tree_sitter

#endif  // COMPILER_LOG_H_
