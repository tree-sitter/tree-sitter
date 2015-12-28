#include "runtime/helpers/spy_input.h"
#include "runtime/helpers/encoding_helpers.h"
#include <string.h>
#include <algorithm>
#include <assert.h>

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
  delete buffer;
}

const char * SpyInput::read(void *payload, size_t *bytes_read) {
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

int SpyInput::seek(void *payload, size_t character, size_t byte) {
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
  result.seek_fn = seek;
  result.read_fn = read;
  return result;
}

TSInputEdit SpyInput::replace(size_t start_char, size_t chars_removed, string text) {
  string text_removed = swap_substr(start_char, chars_removed, text);
  size_t chars_inserted = string_char_count(encoding, text);
  undo_stack.push_back(SpyInputEdit{start_char, chars_inserted, text_removed});
  return {start_char, chars_inserted, chars_removed};
}

TSInputEdit SpyInput::undo() {
  SpyInputEdit entry = undo_stack.back();
  undo_stack.pop_back();
  swap_substr(entry.position, entry.chars_removed, entry.text_inserted);
  size_t chars_inserted = string_char_count(encoding, entry.text_inserted);
  return TSInputEdit{entry.position, chars_inserted, entry.chars_removed};
}

string SpyInput::swap_substr(size_t start_char, size_t chars_removed, string text) {
  long start_byte = string_byte_for_character(encoding, content, 0, start_char);
  assert(start_byte >= 0);

  long bytes_removed = string_byte_for_character(encoding, content, start_byte, chars_removed);
  if (bytes_removed < 0)
    bytes_removed = content.size() - start_byte;

  string text_removed = content.substr(start_byte, bytes_removed);
  content.erase(start_byte, bytes_removed);
  content.insert(start_byte, text);

  return text_removed;
}

void SpyInput::clear() {
  strings_read.clear();
}
