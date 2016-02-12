#include "runtime/string_input.h"
#include "runtime/alloc.h"
#include <string.h>

typedef struct {
  const char *string;
  size_t position;
  size_t length;
} TSStringInput;

const char *ts_string_input_read(void *payload, size_t *bytes_read) {
  TSStringInput *input = (TSStringInput *)payload;
  if (input->position >= input->length) {
    *bytes_read = 0;
    return "";
  }
  size_t previous_position = input->position;
  input->position = input->length;
  *bytes_read = input->position - previous_position;
  return input->string + previous_position;
}

int ts_string_input_seek(void *payload, size_t character, size_t byte) {
  TSStringInput *input = (TSStringInput *)payload;
  input->position = byte;
  return (byte < input->length);
}

TSInput ts_string_input_make(const char *string) {
  TSStringInput *input = ts_malloc(sizeof(TSStringInput));
  if (!input)
    goto error;

  input->string = string;
  input->position = 0;
  input->length = strlen(string);
  return (TSInput){
    .payload = input,
    .read_fn = ts_string_input_read,
    .seek_fn = ts_string_input_seek,
    .encoding = TSInputEncodingUTF8,
  };

error:
  return (TSInput){NULL, NULL, NULL, TSInputEncodingUTF8};
}
