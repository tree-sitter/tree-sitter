#ifndef HELPERS_SPY_READER_H_
#define HELPERS_SPY_READER_H_

#include <string>
#include <vector>
#include "tree_sitter/runtime.h"

class SpyReader {
 public:
  SpyReader(std::string content, size_t chars_per_chunk);
  ~SpyReader();

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

#endif  // HELPERS_SPY_READER_H_
