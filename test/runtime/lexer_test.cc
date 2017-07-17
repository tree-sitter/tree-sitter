#include "test_helper.h"
#include "runtime/utf16.h"

START_TEST

describe("Lexer", [&]() {
    it("handles truncated UTF16 data", [&]() {
      uint8_t *content = new uint8_t[1];
      *content = 'A';

      int32_t code_point = 0;
      utf16_iterate(content, 1, &code_point);

      delete[] content;
    });
});

END_TEST
