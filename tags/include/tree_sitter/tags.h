#ifndef TREE_SITTER_TAGS_H_
#define TREE_SITTER_TAGS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "tree_sitter/api.h"

typedef enum {
  TSTagsOk,
  TSTagsUnknownScope,
  TSTagsTimeout,
  TSTagsInvalidLanguage,
  TSTagsInvalidUtf8,
  TSTagsInvalidRegex,
  TSTagsInvalidQuery,
  TSTagsInvalidCapture,
} TSTagsError;

typedef struct {
  uint32_t start_byte;
  uint32_t end_byte;
  uint32_t name_start_byte;
  uint32_t name_end_byte;
  uint32_t line_start_byte;
  uint32_t line_end_byte;
  TSPoint start_point;
  TSPoint end_point;
  uint32_t utf16_start_column;
  uint32_t utf16_end_column;
  uint32_t docs_start_byte;
  uint32_t docs_end_byte;
  uint32_t syntax_type_id;
  bool is_definition;
} TSTag;

typedef struct TSTagger TSTagger;
typedef struct TSTagsBuffer TSTagsBuffer;

// Construct a tagger.
TSTagger *ts_tagger_new();

// Delete a tagger.
void ts_tagger_delete(TSTagger *);

// Add a `TSLanguage` to a tagger. The language is associated with a scope name,
// which can be used later to select a language for tagging. Along with the language,
// you must provide two tree query strings, one for matching tags themselves, and one
// specifying local variable definitions.
TSTagsError ts_tagger_add_language(
  TSTagger *self,
  const char *scope_name,
  const TSLanguage *language,
  const char *tags_query,
  const char *locals_query,
  uint32_t tags_query_len,
  uint32_t locals_query_len
);

// Compute syntax highlighting for a given document. You must first
// create a `TSTagsBuffer` to hold the output.
TSTagsError ts_tagger_tag(
  const TSTagger *self,
  const char *scope_name,
  const char *source_code,
  uint32_t source_code_len,
  TSTagsBuffer *output,
  const size_t *cancellation_flag
);

// A tags buffer stores the results produced by a tagging call. It can be reused
// for multiple calls.
TSTagsBuffer *ts_tags_buffer_new();

// Delete a tags buffer.
void ts_tags_buffer_delete(TSTagsBuffer *);

// Access the tags within a tag buffer.
const TSTag *ts_tags_buffer_tags(const TSTagsBuffer *);
uint32_t ts_tags_buffer_tags_len(const TSTagsBuffer *);

// Access the string containing all of the docs
const char *ts_tags_buffer_docs(const TSTagsBuffer *);
uint32_t ts_tags_buffer_docs_len(const TSTagsBuffer *);

// Get the syntax kinds for a scope.
const char **ts_tagger_syntax_kinds_for_scope_name(const TSTagger *, const char *scope_name, uint32_t *len);

// Determine whether a parse error was encountered while tagging.
bool ts_tags_buffer_found_parse_error(const TSTagsBuffer*);

#ifdef __cplusplus
}
#endif

#endif  // TREE_SITTER_TAGS_H_
