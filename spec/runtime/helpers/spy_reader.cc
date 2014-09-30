#include "runtime/helpers/spy_reader.h"
#include <string.h>
#include <algorithm>

using std::string;

static const char * spy_read(void *data, size_t *bytes_read) {
  SpyReader *reader = static_cast<SpyReader *>(data);
  string result = reader->content.substr(reader->position, reader->chunk_size);
  reader->position += result.size();
  reader->strings_read.back() += result;
  *bytes_read = result.size();
  memset(reader->buffer, 0, reader->chunk_size);
  memcpy(reader->buffer, result.data(), result.size());
  return reader->buffer;
}

static int spy_seek(void *data, TSLength position) {
  SpyReader *reader = static_cast<SpyReader *>(data);
  reader->strings_read.push_back("");
  reader->position = position.bytes;
  return 0;
}

SpyReader::SpyReader(string content, size_t chunk_size) :
    buffer(new char[chunk_size]),
    content(content),
    position(0),
    chunk_size(chunk_size) {}

void SpyReader::clear() {
  strings_read.clear();
}

TSInput SpyReader::input() {
  TSInput result;
  result.data = this;
  result.seek_fn = spy_seek;
  result.read_fn = spy_read;
  result.release_fn = nullptr;
  return result;
}

SpyReader::~SpyReader() {
  delete buffer;
}
