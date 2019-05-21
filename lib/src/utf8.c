// SPDX-License-Identifier: Unicode-DFS-2016
// Copyright 2016 and later: Unicode, Inc. and others.
// Copyright 2019 Matthew Krupcale <mkrupcale@matthewkrupcale.com>

#include <stdbool.h>

#include "./utf8.h"

static const uint8_t UTF8_LEAD3_T1_BITS[] = {
    0x20, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
    0x30, 0x30, 0x30, 0x30, 0x30, 0x10, 0x30, 0x30
};

static const uint8_t UTF8_LEAD4_T1_BITS[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x1E, 0x0F, 0x0F, 0x0F, 0x00, 0x00, 0x00, 0x00
};

static bool utf8_is_single(uint8_t c) {
  return (c & 0x80) == 0;
}

static bool utf8_is_valid_lead3_and_t1(uint32_t* lead, uint8_t t1, uint8_t* cu) {
  return UTF8_LEAD3_T1_BITS[*lead &= 0xF] & (1 << ((*cu = t1) >> 5));
}

static bool utf8_is_valid_lead4_and_t1(uint32_t* lead, uint8_t t1, uint8_t* cu) {
  return UTF8_LEAD4_T1_BITS[(*cu = t1) >> 4] & (1 << (*lead & 0x7));
}

static bool utf8_offset_in_range(uint8_t c, uint8_t lower, uint8_t range, uint8_t* offset) {
  return (*offset = (uint8_t)(c - lower)) <= range;
}

static uint32_t utf8_add_code_unit(uint32_t code_point, uint8_t cu) {
  return (code_point << 6) | cu;
}

ssize_t utf8_decode_next(const uint8_t *str, size_t length, uint32_t *code_point) {

  const uint8_t *str_begin = str;
  const uint8_t *str_it = str_begin;
  const uint8_t *str_end = str + length;

  if (str_it != str_end &&
      (*code_point = *str_it++, !utf8_is_single((uint8_t)*code_point))) {
    uint8_t cu = 0;
    if (str_it != str_end &&
        // fetch/validate/assemble all but last trail byte
        (*code_point >= 0xE0 ?
         (*code_point < 0xF0 ?
          // U+0800..U+FFFF except surrogates
          utf8_is_valid_lead3_and_t1(code_point, *str_it, &cu) &&
          (cu &= 0x3F, 1) :
          // U+10000..U+10FFFF
          (*code_point -= 0xF0) <= 4 &&
          utf8_is_valid_lead4_and_t1(code_point, *str_it, &cu) &&
          (*code_point = utf8_add_code_unit(*code_point, cu & 0x3F), ++str_it != str_end) &&
          utf8_offset_in_range(*str_it, 0x80, 0x3F, &cu)) &&
         // valid second-to-last trail byte
         (*code_point = utf8_add_code_unit(*code_point, cu), ++str_it != str_end) :
         // U+0080..U+07FF
         *code_point >= 0xC2 && (*code_point &= 0x1F, 1)) &&
        // last trail byte
        utf8_offset_in_range(*str_it, 0x80, 0x3F, &cu) &&
        (*code_point = utf8_add_code_unit(*code_point, cu), ++str_it, 1)) {
    } else {
      // invalid sequence
      return DECODE_NEXT_ERROR;
    }
  }
  return str_it - str_begin;
}
