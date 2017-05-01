#include "helpers/encoding_helpers.h"
#include "runtime/utf16.h"
#include <assert.h>
#include "utf8proc.h"

static inline int string_iterate(TSInputEncoding encoding, const uint8_t *string, size_t length, int32_t *code_point) {
  if (encoding == TSInputEncodingUTF8) {
    int32_t character_size = utf8proc_iterate(string, length, code_point);
    if (character_size < 0) {
      return 1;
    } else {
      return character_size;
    }
  } else {
    return utf16_iterate(string, length, code_point);
  }
}

size_t string_char_count(TSInputEncoding encoding, const std::string &input) {
  const char *string = input.data();
  size_t size = input.size();
  size_t character = 0, byte = 0;

  while (byte < size) {
    int32_t code_point;
    byte += string_iterate(encoding, (uint8_t *)string + byte, size - byte, &code_point);
    character++;
  }

  return character;
}

long string_byte_for_character(TSInputEncoding encoding, const std::string &input, size_t byte_offset, size_t goal_character) {
  const char *string = input.data() + byte_offset;
  size_t size = input.size() - byte_offset;
  size_t character = 0, byte = 0;

  while (character < goal_character) {
    if (byte >= size)
      return -1;

    int32_t code_point;
    byte += string_iterate(encoding, (uint8_t *)string + byte, size - byte, &code_point);
    character++;
  }

  return byte;
}

size_t utf8_char_count(const std::string &input) {
  return string_char_count(TSInputEncodingUTF8, input);
}

size_t utf16_char_count(const std::string &input) {
  return string_char_count(TSInputEncodingUTF16, input);
}

long utf8_byte_for_character(const std::string &input, size_t byte_offset, size_t goal_character) {
  return string_byte_for_character(TSInputEncodingUTF8, input, byte_offset, goal_character);
}

long utf16_byte_for_character(const std::string &input, size_t byte_offset, size_t goal_character) {
  return string_byte_for_character(TSInputEncodingUTF16, input, byte_offset, goal_character);
}
