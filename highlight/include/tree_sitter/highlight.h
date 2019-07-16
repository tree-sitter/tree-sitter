#ifndef TREE_SITTER_HIGHLIGHT_H_
#define TREE_SITTER_HIGHLIGHT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef enum {
  TSHighlightOk,
  TSHighlightUnknownScope,
  TSHighlightTimeout,
  TSHighlightInvalidLanguage,
} TSHighlightError;

// The list of scopes which can be styled for syntax highlighting.
// When constructing a `TSHighlighter`, you need to construct an
// `attribute_strings` array whose elements correspond to these values.
enum TSHighlightValue {
  TSHighlightValueAttribute,
  TSHighlightValueComment,
  TSHighlightValueConstant,
  TSHighlightValueConstantBuiltin,
  TSHighlightValueConstructor,
  TSHighlightValueConstructorBuiltin,
  TSHighlightValueEmbedded,
  TSHighlightValueEscape,
  TSHighlightValueFunction,
  TSHighlightValueFunctionBuiltin,
  TSHighlightValueKeyword,
  TSHighlightValueNumber,
  TSHighlightValueOperator,
  TSHighlightValueProperty,
  TSHighlightValuePropertyBuiltin,
  TSHighlightValuePunctuation,
  TSHighlightValuePunctuationBracket,
  TSHighlightValuePunctuationDelimiter,
  TSHighlightValuePunctuationSpecial,
  TSHighlightValueString,
  TSHighlightValueStringSpecial,
  TSHighlightValueTag,
  TSHighlightValueType,
  TSHighlightValueTypeBuiltin,
  TSHighlightValueVariable,
  TSHighlightValueVariableBuiltin,
  TSHighlightValueVariableParameter,
  TSHighlightValueUnknown,
};

typedef struct TSHighlighter TSHighlighter;
typedef struct TSHighlightBuffer TSHighlightBuffer;

// Construct a `TSHighlighter` by providing a list of strings containing
// the HTML attributes that should be applied for each highlight value.
TSHighlighter *ts_highlighter_new(
  const char **attribute_strings
);

// Delete a syntax highlighter.
void ts_highlighter_delete(TSHighlighter *);

// Add a `TSLanguage` to a highlighter. The language is associated with a
// scope name, which can be used later to select a language for syntax
// highlighting. Along with the language, you must provide a JSON string
// containing the compiled PropertySheet to use for syntax highlighting
// with that language. You can also optionally provide an 'injection regex',
// which is used to detect when this language has been embedded in a document
// written in a different language.
int ts_highlighter_add_language(
  TSHighlighter *self,
  const char *scope_name,
  const TSLanguage *language,
  const char *property_sheet_json,
  const char *injection_regex
);

// Compute syntax highlighting for a given document. You must first
// create a `TSHighlightBuffer` to hold the output.
int ts_highlighter_highlight(
  const TSHighlighter *self,
  const char *scope_name,
  const char *source_code,
  uint32_t source_code_len,
  TSHighlightBuffer *output,
  const size_t *cancellation_flag
);

// TSHighlightBuffer: This struct stores the HTML output of syntax
// highlighting. It can be reused for multiple highlighting calls.
TSHighlightBuffer *ts_highlight_buffer_new();

// Delete a highlight buffer.
void ts_highlight_buffer_delete(TSHighlightBuffer *);

// Access the HTML content of a highlight buffer.
const uint8_t *ts_highlight_buffer_content(const TSHighlightBuffer *);
const uint32_t *ts_highlight_buffer_line_offsets(const TSHighlightBuffer *);
uint32_t ts_highlight_buffer_len(const TSHighlightBuffer *);
uint32_t ts_highlight_buffer_line_count(const TSHighlightBuffer *);

#ifdef __cplusplus
}
#endif

#endif  // TREE_SITTER_HIGHLIGHT_H_
