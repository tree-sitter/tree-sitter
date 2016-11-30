#include <stdbool.h>

void *ts_language_external_scanner_example_external_scanner_create() {
  puts("HELLO FROM EXTERNAL SCANNER");
  return 0;
}

bool ts_language_external_scanner_example_external_scanner_scan() {
  return true;
}

void ts_language_external_scanner_example_external_scanner_destroy() {
}
