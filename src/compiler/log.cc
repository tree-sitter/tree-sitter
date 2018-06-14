#include "compiler/log.h"
#include <cassert>

static const char *SPACES = "                                                           ";

namespace tree_sitter {

thread_local unsigned _indent_level = 0;
thread_local FILE *_log_file = nullptr;

void set_log_file(FILE *file) {
  _log_file = file;
  _indent_level = 0;
}

FILE *get_log_file() {
  return _log_file;
}

void _indent_logs() {
  _indent_level++;
}

void _outdent_logs() {
  assert(_indent_level > 0);
  _indent_level--;
}

void _print_indent() {
  fwrite(SPACES, 1, _indent_level * 4, _log_file);
}

}
