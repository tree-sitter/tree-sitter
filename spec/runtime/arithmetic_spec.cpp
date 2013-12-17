#include <igloo/igloo_alt.h>
#include "../fixtures/parsers/arithmetic.c"

using namespace igloo;

Describe(arithmetic) {
    It(parses_numbers) {
        ts_parse_arithmetic("5");
    };
};
