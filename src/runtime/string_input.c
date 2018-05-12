#include "tree_sitter/runtime.h"
#include "runtime/string_input.h"
#include <string.h>

static const char *ts_string_input__read(void *payload, uint32_t *bytes_read) {
  TSStringInput *input = (TSStringInput *)payload;
  if (input->position >= input->length) {
    *bytes_read = 0;
    return "";
  }
  uint32_t previous_position = input->position;
  input->position = input->length;
  *bytes_read = input->position - previous_position;
  return input->string + previous_position;
}

static int ts_string_input__seek(void *payload, uint32_t byte, TSPoint _) {
  TSStringInput *input = (TSStringInput *)payload;
  input->position = byte;
  return (byte < input->length);
}

void ts_string_input_init(TSStringInput *self, const char *string, uint32_t length) {
  self->string = string;
  self->position = 0;
  self->length = length;
  self->input = (TSInput) {
    .payload = self,
    .read = ts_string_input__read,
    .seek = ts_string_input__seek,
    .encoding = TSInputEncodingUTF8,
  };
}
