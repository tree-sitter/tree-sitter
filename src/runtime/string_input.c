#include "runtime/string_input.h"
#include <string.h>

typedef struct {
  const char *string;
  size_t position;
  size_t length;
} TSStringInput;

const char *ts_string_input_read(void *d, size_t *bytes_read) {
  TSStringInput *data = (TSStringInput *)d;
  if (data->position >= data->length) {
    *bytes_read = 0;
    return "";
  }
  size_t previous_position = data->position;
  data->position = data->length;
  *bytes_read = data->position - previous_position;
  return data->string + previous_position;
}

int ts_string_input_seek(void *d, TSLength position) {
  TSStringInput *data = (TSStringInput *)d;
  data->position = position.bytes;
  return (position.bytes < data->length);
}

TSInput ts_string_input_make(const char *string) {
  TSStringInput *data = malloc(sizeof(TSStringInput));
  data->string = string;
  data->position = 0;
  data->length = strlen(string);
  return (TSInput){.data = (void *)data,
                   .read_fn = ts_string_input_read,
                   .seek_fn = ts_string_input_seek,
                   .release_fn = free };
}
