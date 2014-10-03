#include "runtime/helpers/spy_reader.h"
#include <string.h>
#include <algorithm>
#include "utf8proc.h"

using std::string;

static long position_for_char_index(const char *str, size_t len, size_t goal_index) {
  size_t index = 0, position = 0;
  int32_t dest_char;

  while (index < goal_index) {
    if (position >= len)
      return -1;
    position += utf8proc_iterate(
        (uint8_t *)str + position,
        len - position,
        &dest_char);
    index++;
  }

  return position;
}

static const char * spy_read(void *data, size_t *bytes_read) {
  SpyReader *reader = static_cast<SpyReader *>(data);
  return reader->read(bytes_read);
}

static int spy_seek(void *data, TSLength position) {
  SpyReader *reader = static_cast<SpyReader *>(data);
  return reader->seek(position.bytes);
}

SpyReader::SpyReader(string content, size_t chunk_size) :
    buffer(new char[chunk_size]),
    content(content),
    position(0),
    chunk_size(chunk_size) {}

SpyReader::~SpyReader() {
  delete buffer;
}

const char * SpyReader::read(size_t *bytes_read) {
  string result = content.substr(position, chunk_size);
  position += result.size();
  strings_read.back() += result;
  *bytes_read = result.size();
  memset(buffer, 0, chunk_size);
  memcpy(buffer, result.data(), result.size());
  return buffer;
}

int SpyReader::seek(size_t pos) {
  strings_read.push_back("");
  position = pos;
  return 0;
}

TSInput SpyReader::input() {
  TSInput result;
  result.data = this;
  result.seek_fn = spy_seek;
  result.read_fn = spy_read;
  result.release_fn = nullptr;
  return result;
}

bool SpyReader::insert(size_t char_index, string text) {
  long pos = position_for_char_index(content.data(), content.size(), char_index);
  if (pos < 0) return false;
  content.insert(pos, text);
  return true;
}

bool SpyReader::erase(size_t char_index, size_t len) {
  long pos = position_for_char_index(content.data(), content.size(), char_index);
  if (pos < 0) return false;
  content.erase(pos, len);
  return true;
}

void SpyReader::clear() {
  strings_read.clear();
}
