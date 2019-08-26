// SPDX-License-Identifier: Unicode-DFS-2016
// Copyright 2016 and later: Unicode, Inc. and others.
// Copyright 2019 Matthew Krupcale <mkrupcale@matthewkrupcale.com>

#include "./utf16.h"

static const uint32_t SURROGATE_BASE = 0xD800;
static const uint32_t BMP_PRIVATE_BASE = 0xE000;

// SURROGATE_BASE + 0x3FF + 1
static const uint32_t LOW_OFFSET = 0xDC00;
// 0x10000 - (SURROGATE_BASE << 10) - LOW_OFFSET
static const uint32_t SURROGATE_OFFSET = -0x35FDC00;

static uint32_t utf16_decode_surrogates(uint16_t low, uint16_t high) {
  return ((uint32_t)(high) << 10) + low + SURROGATE_OFFSET;
}

ssize_t utf16_decode_next(const uint8_t *str, size_t length, uint32_t *code_point) {
  const uint16_t *str_it = (const uint16_t *)str;
  size_t str_size = length / 2;

  if (str_size == 0)
    return 0;

  uint16_t code_unit = *str_it++;

  if (code_unit < SURROGATE_BASE || code_unit >= BMP_PRIVATE_BASE) {
    *code_point = code_unit;
    return 2;
  }

  // expect surrogate pair: high and then low
  if (code_unit < LOW_OFFSET && str_size > 1) {
    uint16_t high = code_unit;
    uint16_t low = *str_it;
    if (low >= LOW_OFFSET && low < BMP_PRIVATE_BASE) {
      *code_point = utf16_decode_surrogates(low, high);
      return 4;
    }
  }

  // invalid sequence
  return DECODE_NEXT_ERROR;
}
