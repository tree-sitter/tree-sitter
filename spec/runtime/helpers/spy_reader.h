#ifndef HELPERS_SPY_READER_H_
#define HELPERS_SPY_READER_H_

#include <string>
#include <vector>
#include "tree_sitter/runtime.h"

class SpyReader {
 public:
  SpyReader(std::string content, size_t chunk_size);

  std::string content;
  size_t position;
  size_t chunk_size;
  TSInput input;
  std::vector<std::string> strings_read;
};

#endif  // HELPERS_SPY_READER_H_
