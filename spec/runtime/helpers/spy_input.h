#ifndef HELPERS_spy_input_H_
#define HELPERS_spy_input_H_

#include <string>
#include <vector>
#include "tree_sitter/runtime.h"

class SpyInput {
 public:
  SpyInput(std::string content, size_t chars_per_chunk);
  ~SpyInput();

  void clear();
  TSInput input();
  bool insert(size_t position, std::string text);
  bool erase(size_t position, size_t len);
  const char * read(size_t *len);
  int seek(size_t position);

  std::string content;
  size_t chars_per_chunk;
  size_t buffer_size;
  char *buffer;
  size_t byte_offset;
  std::vector<std::string> strings_read;
};

#endif  // HELPERS_spy_input_H_
