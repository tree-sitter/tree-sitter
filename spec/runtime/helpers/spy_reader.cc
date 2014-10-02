#include "runtime/helpers/spy_reader.h"
#include <string.h>
#include <algorithm>
#include "utf8proc.h"

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

long position_for_char_index(string str, size_t goal_index) {
  size_t index = 0, position = 0;
  int32_t dest_char;

  while (index < goal_index) {
    if (position >= str.size())
      return -1;
    position += utf8proc_iterate(
        (uint8_t *)(str.data() + position),
        str.size() - position,
        &dest_char);
    index++;
  }

  return position;
}

bool SpyReader::insert(size_t char_index, string text) {
  long pos = position_for_char_index(content, char_index);
  if (pos < 0) return false;
  content.insert(pos, text);
  return true;
}

bool SpyReader::erase(size_t char_index, size_t len) {
  long pos = position_for_char_index(content, char_index);
  if (pos < 0) return false;
  content.erase(pos, len);
  return true;
}

SpyReader::~SpyReader() {
  delete buffer;
}
