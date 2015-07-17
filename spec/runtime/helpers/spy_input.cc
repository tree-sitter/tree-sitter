#include "runtime/helpers/spy_input.h"
#include <string.h>
#include <algorithm>
#include "utf8proc.h"

using std::string;

static long byte_for_character(const char *str, size_t len, size_t goal_character) {
  size_t character = 0, byte = 0;
  int32_t dest_char;

  while (character < goal_character) {
    if (byte >= len)
      return -1;
    byte += utf8proc_iterate(
        (uint8_t *)str + byte,
        len - byte,
        &dest_char);
    character++;
  }

  return byte;
}

static const char * spy_read(void *data, size_t *bytes_read) {
  SpyInput *reader = static_cast<SpyInput *>(data);
  return reader->read(bytes_read);
}

static int spy_seek(void *data, TSLength byte_offset) {
  SpyInput *reader = static_cast<SpyInput *>(data);
  return reader->seek(byte_offset.bytes);
}

SpyInput::SpyInput(string content, size_t chars_per_chunk) :
    content(content),
    chars_per_chunk(chars_per_chunk),
    buffer_size(4 * chars_per_chunk),
    buffer(new char[buffer_size]),
    byte_offset(0),
    strings_read({ "" }) {}

SpyInput::~SpyInput() {
  delete buffer;
}

const char * SpyInput::read(size_t *bytes_read) {
  if (byte_offset > content.size()) {
    *bytes_read = 0;
    return "";
  }

  const char *start = content.data() + byte_offset;
  long byte_count = byte_for_character(start, content.size() - byte_offset, chars_per_chunk);
  if (byte_count < 0)
    byte_count = content.size() - byte_offset;

  *bytes_read = byte_count;
  byte_offset += byte_count;
  strings_read.back() += string(start, byte_count);

  /*
   * This class stores its entire `content` in a contiguous buffer, but we want
   * to ensure that the code under test cannot accidentally read more than
   * `*bytes_read` bytes past the returned pointer. To make sure that this type
   * of error does not fly, we copy the chunk into a zeroed-out buffer and
   * return a reference to that buffer, rather than a pointer into the main
   * content.
   */
  memset(buffer, 0, buffer_size);
  memcpy(buffer, start, byte_count);
  return buffer;
}

int SpyInput::seek(size_t pos) {
  strings_read.push_back("");
  byte_offset = pos;
  return 0;
}

TSInput SpyInput::input() {
  TSInput result;
  result.data = this;
  result.seek_fn = spy_seek;
  result.read_fn = spy_read;
  result.release_fn = nullptr;
  return result;
}

bool SpyInput::insert(size_t char_index, string text) {
  long pos = byte_for_character(content.data(), content.size(), char_index);
  if (pos < 0) return false;
  content.insert(pos, text);
  return true;
}

bool SpyInput::erase(size_t char_index, size_t len) {
  long pos = byte_for_character(content.data(), content.size(), char_index);
  if (pos < 0) return false;
  content.erase(pos, len);
  return true;
}

void SpyInput::clear() {
  strings_read.clear();
}
