#include "helpers/spy_input.h"
#include "helpers/point_helpers.h"
#include "runtime/point.h"
#include <string.h>
#include <algorithm>
#include <assert.h>

using std::pair;
using std::string;
using std::vector;

SpyInput::SpyInput(string content, size_t chars_per_chunk) :
  buffer(nullptr),
  chars_per_chunk(chars_per_chunk),
  content(content),
  encoding(TSInputEncodingUTF8),
  ranges_read({}) {}

SpyInput::~SpyInput() {
  delete[] buffer;
}

static TSPoint operator+(TSPoint a, TSPoint b) {
  if (b.row > 0) {
    return TSPoint {a.row + b.row, b.column};
  } else {
    return TSPoint {a.row, a.column + b.column};
  }
}

static void add_byte_range(vector<pair<uint32_t, uint32_t>> *ranges,
                           uint32_t start, uint32_t count) {
  uint32_t end = start + count;
  for (auto &range : *ranges) {
    if (range.first <= start && start <= range.second) {
      if (start < range.first) range.first = start;
      if (end > range.second) range.second = end;
      return;
    }
  }
  ranges->push_back({start, end});
}

const char *SpyInput::read(void *payload, uint32_t byte_offset,
                           TSPoint position, uint32_t *bytes_read) {
  auto spy = static_cast<SpyInput *>(payload);

  unsigned end_byte = byte_offset + spy->chars_per_chunk;
  if (end_byte > spy->content.size()) {
    end_byte = spy->content.size();
  }

  *bytes_read = end_byte - byte_offset;
  add_byte_range(&spy->ranges_read, byte_offset, *bytes_read);

  /*
   * This class stores its entire `content` in a contiguous buffer, but we want
   * to ensure that the code under test cannot accidentally read more than
   * `*bytes_read` bytes past the returned pointer. To make sure that this type
   * of error does not fly, we allocate a separate buffer for each request and
   * return a reference to that buffer, rather than a pointer into the main
   * content. The temporary buffer only fits `*bytes_read` bytes so valgrind
   * can detect code reading too many bytes from the buffer.
   */
  delete[] spy->buffer;
  if (*bytes_read) {
    spy->buffer = new char[*bytes_read]();
    memcpy(spy->buffer, spy->content.data() + byte_offset, *bytes_read);
  } else {
    spy->buffer = nullptr;
  }

  return spy->buffer;
}

vector<string> SpyInput::strings_read() const {
  vector<string> result;
  for (auto &range : ranges_read) {
    result.push_back(content.substr(range.first, range.second - range.first));
  }
  return result;
}

TSInput SpyInput::input() {
  TSInput result;
  result.payload = this;
  result.encoding = encoding;
  result.read = read;
  return result;
}

TSInputEdit SpyInput::replace(size_t start_byte, size_t bytes_removed, string text) {
  auto swap = swap_substr(start_byte, bytes_removed, text);
  size_t bytes_added = text.size();
  undo_stack.push_back(SpyInputEdit{start_byte, bytes_added, swap.first});
  TSInputEdit result = {};
  result.start_byte = start_byte;
  result.old_end_byte = start_byte + bytes_removed;
  result.new_end_byte = start_byte + bytes_added;
  result.start_point = swap.second;
  result.old_end_point = result.start_point + extent_for_string(swap.first);
  result.new_end_point = result.start_point + extent_for_string(text);
  return result;
}

bool SpyInput::can_undo() const {
  return !undo_stack.empty();
}

TSInputEdit SpyInput::undo() {
  SpyInputEdit entry = undo_stack.back();
  undo_stack.pop_back();
  auto swap = swap_substr(entry.start_byte, entry.bytes_removed, entry.text_inserted);
  TSInputEdit result;
  result.start_byte = entry.start_byte;
  result.old_end_byte = entry.start_byte + entry.bytes_removed;
  result.new_end_byte = entry.start_byte + entry.text_inserted.size();
  result.start_point = swap.second;
  result.old_end_point = result.start_point + extent_for_string(swap.first);
  result.new_end_point = result.start_point + extent_for_string(entry.text_inserted);
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
  ranges_read.clear();
}
