#include "test_helper.h"
#include "compiler/util/string_helpers.h"

using util::escape_char;

START_TEST

describe("escape_char", []() {
  it("returns ascii characters as strings", [&]() {
    AssertThat(escape_char('x'), Equals("'x'"));
  });

  it("escapes special characters with backslashes", [&]() {
    AssertThat(escape_char('\\'), Equals("'\\\\'"));
    AssertThat(escape_char('\n'), Equals("'\\n'"));
    AssertThat(escape_char('\t'), Equals("'\\t'"));
    AssertThat(escape_char('\r'), Equals("'\\r'"));
    AssertThat(escape_char('\''), Equals("'\\''"));
  });

  it("prints non-ascii characters as numbers", [&]() {
    AssertThat(escape_char(256), Equals("256"));
  });
});

END_TEST
