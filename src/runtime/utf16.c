#include "runtime/utf16.h"

int utf16_iterate(const uint8_t *string, size_t length, int32_t *code_point) {
  uint16_t *units = (uint16_t *)string;
  uint16_t unit = units[0];

  if (unit < 0xd800 || unit >= 0xe000) {
    *code_point = unit;
    return 2;
  }

  if (unit < 0xdc00) {
    if (length >= 4) {
      uint16_t next_unit = units[1];
      if (next_unit >= 0xdc00 && next_unit < 0xe000) {
        *code_point = 0x10000 + ((unit - 0xd800) << 10) + (next_unit - 0xdc00);
        return 4;
      }
    }
  }

  *code_point = -1;
  return 2;
}
