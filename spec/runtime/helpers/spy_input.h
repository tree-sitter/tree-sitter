#ifndef HELPERS_spy_input_H_
#define HELPERS_spy_input_H_

#include <string>
#include <vector>
#include "tree_sitter/runtime.h"

class SpyInput {
  size_t chars_per_chunk;
  size_t buffer_size;
  char *buffer;
  size_t byte_offset;

  static const char * read(void *, size_t *);
  static int seek(void *, TSLength);

 public:
  SpyInput(std::string content, size_t chars_per_chunk);
  ~SpyInput();

  TSInput input();
  void clear();
  bool insert(size_t position, std::string text);
  bool erase(size_t position, size_t len);

  std::string content;
  std::vector<std::string> strings_read;
};

#endif  // HELPERS_spy_input_H_
