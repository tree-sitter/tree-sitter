#include "helpers/spy_input.h"
#include "helpers/encoding_helpers.h"
#include <string.h>
#include <algorithm>
#include <assert.h>

using std::pair;
using std::string;

static const size_t UTF8_MAX_CHAR_SIZE = 4;

SpyInput::SpyInput(string content, size_t chars_per_chunk) :
  chars_per_chunk(chars_per_chunk),
  buffer_size(UTF8_MAX_CHAR_SIZE * chars_per_chunk),
  buffer(new char[buffer_size]),
  byte_offset(0),
  content(content),
  encoding(TSInputEncodingUTF8),
  strings_read({""}) {}

SpyInput::~SpyInput() {
  delete[] buffer;
}

const char * SpyInput::read(void *payload, uint32_t *bytes_read) {
  auto spy = static_cast<SpyInput *>(payload);

  if (spy->byte_offset > spy->content.size()) {
    *bytes_read = 0;
    return "";
  }

  long byte_count = string_byte_for_character(spy->encoding, spy->content, spy->byte_offset, spy->chars_per_chunk);
  if (byte_count < 0)
    byte_count = spy->content.size() - spy->byte_offset;

  string result = spy->content.substr(spy->byte_offset, byte_count);
  *bytes_read = byte_count;
  spy->strings_read.back() += result;
  spy->byte_offset += byte_count;

  /*
   * This class stores its entire `content` in a contiguous buffer, but we want
   * to ensure that the code under test cannot accidentally read more than
   * `*bytes_read` bytes past the returned pointer. To make sure that this type
   * of error does not fly, we copy the chunk into a zeroed-out buffer and
   * return a reference to that buffer, rather than a pointer into the main
   * content.
   */
  memset(spy->buffer, 0, spy->buffer_size);
  memcpy(spy->buffer, result.data(), byte_count);
  return spy->buffer;
}

int SpyInput::seek(void *payload, uint32_t character, uint32_t byte) {
  auto spy = static_cast<SpyInput *>(payload);
  if (spy->strings_read.size() == 0 || spy->strings_read.back().size() > 0)
    spy->strings_read.push_back("");
  spy->byte_offset = byte;
  return 0;
}

TSInput SpyInput::input() {
  TSInput result;
  result.payload = this;
  result.encoding = encoding;
  result.seek = seek;
  result.read = read;
  return result;
}

static TSPoint get_extent(string text) {
  TSPoint result = {0, 0};
  for (auto i = text.begin(); i != text.end(); i++) {
    if (*i == '\n') {
      result.row++;
      result.column = 0;
    } else {
      result.column++;
    }
  }
  return result;
}

TSInputEdit SpyInput::replace(size_t start_byte, size_t bytes_removed, string text) {
  auto swap = swap_substr(start_byte, bytes_removed, text);
  size_t bytes_added = text.size();
  undo_stack.push_back(SpyInputEdit{start_byte, bytes_added, swap.first});
  TSInputEdit result = {};
  result.start_byte = start_byte;
  result.bytes_added = bytes_added;
  result.bytes_removed = bytes_removed;
  result.start_point = swap.second;
  result.extent_removed = get_extent(swap.first);
  result.extent_added = get_extent(text);
  return result;
}

TSInputEdit SpyInput::undo() {
  SpyInputEdit entry = undo_stack.back();
  undo_stack.pop_back();
  auto swap = swap_substr(entry.start_byte, entry.bytes_removed, entry.text_inserted);
  TSInputEdit result;
  result.start_byte = entry.start_byte;
  result.bytes_removed = entry.bytes_removed;
  result.bytes_added = entry.text_inserted.size();
  result.start_point = swap.second;
  result.extent_removed = get_extent(swap.first);
  result.extent_added = get_extent(entry.text_inserted);
  return result;
}

pair<string, TSPoint> SpyInput::swap_substr(size_t start_byte, size_t bytes_removed, string text) {
  TSPoint start_position = {0, 0};
  for (auto i = content.begin(), n = content.begin() + start_byte; i < n; i++) {
    if (*i == '\n') {
      start_position.row++;
      start_position.column = 0;
    } else {
      start_position.column++;
    }
  }

  string text_removed = content.substr(start_byte, bytes_removed);
  content.erase(start_byte, bytes_removed);
  content.insert(start_byte, text);

  return {text_removed, start_position};
}

void SpyInput::clear() {
  strings_read.clear();
}
