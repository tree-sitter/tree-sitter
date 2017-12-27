#include "runtime/string_input.h"
#include "runtime/alloc.h"
#include <string.h>

typedef struct {
  const char *string;
  uint32_t position;
  uint32_t length;
} TSStringInput;

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

static int ts_string_input__seek(void *payload, uint32_t byte) {
  TSStringInput *input = (TSStringInput *)payload;
  input->position = byte;
  return (byte < input->length);
}

TSInput ts_string_input_make(const char *string) {
  return ts_string_input_make_with_length(string, strlen(string));
}

TSInput ts_string_input_make_with_length(const char *string, uint32_t length) {
  TSStringInput *input = ts_malloc(sizeof(TSStringInput));
  input->string = string;
  input->position = 0;
  input->length = length;
  return (TSInput){
    .payload = input,
    .read = ts_string_input__read,
    .seek = ts_string_input__seek,
    .encoding = TSInputEncodingUTF8,
  };
}
