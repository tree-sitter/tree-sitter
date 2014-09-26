#include "runtime/helpers/spy_reader.h"
#include <algorithm>

using std::string;

static const char * spy_read(void *data, size_t *bytes_read) {
  SpyReader *reader = static_cast<SpyReader *>(data);
  string result = reader->content.substr(reader->position, reader->chunk_size);
  reader->position += result.size();
  reader->strings_read.back() += result;
  *bytes_read = result.size();
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
    chunk_size(chunk_size),
    input({
        this,
        spy_read,
        spy_seek,
        nullptr,
    }) {}

void SpyReader::clear() {
  strings_read.clear();
}

SpyReader::~SpyReader() {
  delete buffer;
}
