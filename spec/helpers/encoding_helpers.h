#ifndef HELPERS_ENCODING_HELPERS_H_
#define HELPERS_ENCODING_HELPERS_H_

#include <string>
#include "tree_sitter/runtime.h"

size_t string_char_count(TSInputEncoding, const std::string &);
size_t utf8_char_count(const std::string &);
size_t utf16_char_count(const std::string &);

long string_byte_for_character(TSInputEncoding, const std::string &, size_t byte_offset, size_t character);
long utf8_byte_for_character(const std::string &, size_t byte_offset, size_t character);
long utf16_byte_for_character(const std::string &, size_t byte_offset, size_t character);

#endif  // HELPERS_ENCODING_HELPERS_H_
