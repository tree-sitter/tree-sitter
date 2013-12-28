#include "spec_helper.h"
#include "../fixtures/parsers/arithmetic.c"

START_TEST

describe("arithmetic", []() {
    it("parses_numbers", [&]() {
        ts_parse_arithmetic("5");
    });
});

END_TEST