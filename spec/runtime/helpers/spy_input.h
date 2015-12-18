#ifndef HELPERS_spy_input_H_
#define HELPERS_spy_input_H_

#include <string>
#include <vector>
#include "tree_sitter/runtime.h"

struct SpyInputEdit {
  size_t position;
  size_t chars_removed;
  std::string text_inserted;
};

class SpyInput {
  size_t chars_per_chunk;
  size_t buffer_size;
  char *buffer;
  size_t byte_offset;
  std::vector<SpyInputEdit> undo_stack;

  static const char * read(void *, size_t *);
  static int seek(void *, size_t, size_t);
  std::string swap_substr(size_t, size_t, std::string);

 public:
  SpyInput(std::string content, size_t chars_per_chunk);
  ~SpyInput();

  TSInput input();
  void clear();
  TSInputEdit replace(size_t start_char, size_t chars_removed, std::string text);
  TSInputEdit undo();

  static size_t char_count(const std::string &);

  std::string content;
  std::vector<std::string> strings_read;
};

#endif  // HELPERS_spy_input_H_
