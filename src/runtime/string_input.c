#include "tree_sitter/runtime.h"
#include "runtime/string_input.h"
#include <string.h>

static const char *ts_string_input__read(void *payload, uint32_t byte_offset,
                                         TSPoint _, uint32_t *bytes_read) {
  TSStringInput *input = (TSStringInput *)payload;
  if (byte_offset >= input->length) {
    *bytes_read = 0;
    return "";
  } else {
    *bytes_read = input->length - byte_offset;
    return input->string + byte_offset;
  }
}

void ts_string_input_init(TSStringInput *self, const char *string, uint32_t length) {
  self->string = string;
  self->length = length;
}

TSInput ts_string_input_get(TSStringInput *self) {
  return (TSInput) {
    .payload = self,
    .read = ts_string_input__read,
    .encoding = TSInputEncodingUTF8,
  };
}
