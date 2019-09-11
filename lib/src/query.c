#include "tree_sitter/api.h"
#include "./alloc.h"
#include "./array.h"
#include "./bits.h"
#include "./point.h"
#include "utf8proc.h"
#include <wctype.h>

/*
 * Stream - A sequence of unicode characters derived from a UTF8 string.
 * This struct is used in parsing query S-expressions.
 */
typedef struct {
  const char *input;
  const char *end;
  int32_t next;
  uint8_t next_size;
} Stream;

/*
 * QueryStep - A step in the process of matching a query. Each node within
 * a query S-expression maps to one of these steps. An entire pattern is
 * represented as a sequence of these steps.
 */
typedef struct {
  TSSymbol symbol;
  TSFieldId field;
  uint16_t capture_id;
  uint8_t depth;
  bool field_is_multiple;
} QueryStep;

/*
 * CaptureSlice - The name of a capture, represented as a slice of a
 * shared string.
 */
typedef struct {
  uint32_t offset;
  uint32_t length;
} CaptureSlice;

/*
 * PatternSlice - The set of steps needed to match a particular pattern,
 * represented as a slice of a shared array.
 */
typedef struct {
  uint16_t step_index;
  uint16_t pattern_index;
} PatternSlice;

/*
 * QueryState - The state of an in-progress match of a particular pattern
 * in a query. While executing, a `TSQueryCursor` must keep track of a number
 * of possible in-progress matches. Each of those possible matches is
 * represented as one of these states.
 */
typedef struct {
  uint16_t step_index;
  uint16_t pattern_index;
  uint16_t start_depth;
  uint16_t capture_list_id;
  uint16_t capture_count;
} QueryState;

/*
 * CaptureListPool - A collection of *lists* of captures. Each QueryState
 * needs to maintain its own list of captures. They are all represented as
 * slices of one shared array. The CaptureListPool keeps track of which
 * parts of the shared array are currently in use by a QueryState.
 */
typedef struct {
  Array(TSQueryCapture) list;
  uint32_t usage_map;
} CaptureListPool;

/*
 * TSQuery - A tree query, compiled from a string of S-expressions. The query
 * itself is immutable. The mutable state used in the process of executing the
 * query is stored in a `TSQueryCursor`.
 */
struct TSQuery {
  Array(QueryStep) steps;
  Array(char) capture_data;
  Array(CaptureSlice) capture_names;
  Array(PatternSlice) pattern_map;
  const TSLanguage *language;
  uint16_t max_capture_count;
  uint16_t wildcard_root_pattern_count;
};

/*
 * TSQueryCursor - A stateful struct used to execute a query on a tree.
 */
struct TSQueryCursor {
  const TSQuery *query;
  TSTreeCursor cursor;
  Array(QueryState) states;
  Array(QueryState) finished_states;
  CaptureListPool capture_list_pool;
  bool ascending;
  uint32_t depth;
  uint32_t start_byte;
  uint32_t end_byte;
  TSPoint start_point;
  TSPoint end_point;
};

static const TSQueryError PARENT_DONE = -1;
static const uint8_t PATTERN_DONE_MARKER = UINT8_MAX;
static const uint16_t NONE = UINT16_MAX;
static const TSSymbol WILDCARD_SYMBOL = 0;
static const uint16_t MAX_STATE_COUNT = 32;

#ifdef DEBUG_QUERY
#define LOG printf
#else
#define LOG(...)
#endif

/**********
 * Stream
 **********/

static bool stream_advance(Stream *self) {
  if (self->input >= self->end) return false;
  self->input += self->next_size;
  int size = utf8proc_iterate(
    (const uint8_t *)self->input,
    self->end - self->input,
    &self->next
  );
  if (size <= 0) return false;
  self->next_size = size;
  return true;
}

static void stream_reset(Stream *self, const char *input) {
  self->input = input;
  self->next_size = 0;
  stream_advance(self);
}

static Stream stream_new(const char *string, uint32_t length) {
  Stream self = {
    .next = 0,
    .input = string,
    .end = string + length,
  };
  stream_advance(&self);
  return self;
}

static void stream_skip_whitespace(Stream *stream) {
  for (;;) {
    if (iswspace(stream->next)) {
      stream_advance(stream);
    } else if (stream->next == ';') {
      stream_advance(stream);
      while (stream->next && stream->next != '\n') {
        if (!stream_advance(stream)) break;
      }
    } else {
      break;
    }
  }
}

static bool stream_is_ident_start(Stream *stream) {
  return iswalpha(stream->next) || stream->next == '_' || stream->next == '-';
}

static void stream_scan_identifier(Stream *stream) {
  do {
    stream_advance(stream);
  } while (
    iswalnum(stream->next) ||
    stream->next == '_' ||
    stream->next == '-' ||
    stream->next == '.'
  );
}

/******************
 * CaptureListPool
 ******************/

static CaptureListPool capture_list_pool_new() {
  return (CaptureListPool) {
    .list = array_new(),
    .usage_map = UINT32_MAX,
  };
}

static void capture_list_pool_reset(CaptureListPool *self, uint16_t list_size) {
  self->usage_map = UINT32_MAX;
  uint32_t total_size = MAX_STATE_COUNT * list_size;
  array_reserve(&self->list, total_size);
  self->list.size = total_size;
}

static void capture_list_pool_delete(CaptureListPool *self) {
  array_delete(&self->list);
}

static TSQueryCapture *capture_list_pool_get(CaptureListPool *self, uint16_t id) {
  return &self->list.contents[id * (self->list.size / MAX_STATE_COUNT)];
}

static inline uint32_t capture_list_bitmask_for_id(uint16_t id) {
  // An id of zero corresponds to the highest-order bit in the bitmask.
  return (1u << (31 - id));
}

static uint16_t capture_list_pool_acquire(CaptureListPool *self) {
  // In the usage_map bitmask, ones represent free lists, and zeros represent
  // lists that are in use. A free list can quickly be found by counting
  // the leading zeros in the usage map.
  uint16_t id = count_leading_zeros(self->usage_map);
  if (id == 32) return NONE;
  self->usage_map &= ~capture_list_bitmask_for_id(id);
  return id;
}

static void capture_list_pool_release(CaptureListPool *self, uint16_t id) {
  self->usage_map |= capture_list_bitmask_for_id(id);
}

/*********
 * Query
 *********/

static TSSymbol ts_query_intern_node_name(
  const TSQuery *self,
  const char *name,
  uint32_t length,
  TSSymbolType symbol_type
) {
  uint32_t symbol_count = ts_language_symbol_count(self->language);
  for (TSSymbol i = 0; i < symbol_count; i++) {
    if (ts_language_symbol_type(self->language, i) != symbol_type) continue;
    const char *symbol_name = ts_language_symbol_name(self->language, i);
    if (!strncmp(symbol_name, name, length) && !symbol_name[length]) return i;
  }
  return 0;
}

static uint16_t ts_query_intern_capture_name(
  TSQuery *self,
  const char *name,
  uint32_t length
) {
  int id = ts_query_capture_id_for_name(self, name, length);
  if (id >= 0) {
    return (uint16_t)id;
  }

  CaptureSlice capture = {
    .offset = self->capture_data.size,
    .length = length,
  };
  array_grow_by(&self->capture_data, length + 1);
  memcpy(&self->capture_data.contents[capture.offset], name, length);
  self->capture_data.contents[self->capture_data.size - 1] = 0;
  array_push(&self->capture_names, capture);
  return self->capture_names.size - 1;
}

// The `pattern_map` contains a mapping from TSSymbol values to indices in the
// `steps` array. For a given syntax node, the `pattern_map` makes it possible
// to quickly find the starting steps of all of the patterns whose root matches
// that node. It is represented as an array of `(symbol, step index)` pairs,
// sorted by symbol. Lookups use a binary search so that their cost scales
// logarithmically with the number of patterns in the query.
static inline bool ts_query__pattern_map_search(
  const TSQuery *self,
  TSSymbol needle,
  uint32_t *result
) {
  uint32_t base_index = self->wildcard_root_pattern_count;
  uint32_t size = self->pattern_map.size - base_index;
  if (size == 0) {
    *result = base_index;
    return false;
  }
  while (size > 1) {
    uint32_t half_size = size / 2;
    uint32_t mid_index = base_index + half_size;
    TSSymbol mid_symbol = self->steps.contents[
      self->pattern_map.contents[mid_index].step_index
    ].symbol;
    if (needle > mid_symbol) base_index = mid_index;
    size -= half_size;
  }

  TSSymbol symbol = self->steps.contents[
    self->pattern_map.contents[base_index].step_index
  ].symbol;

  if (needle > symbol) {
    base_index++;
    if (base_index < self->pattern_map.size) {
      symbol = self->steps.contents[
        self->pattern_map.contents[base_index].step_index
      ].symbol;
    }
  }

  *result = base_index;
  return needle == symbol;
}

// Insert a new pattern's start index into the pattern map, maintaining
// the pattern map's ordering invariant.
static inline void ts_query__pattern_map_insert(
  TSQuery *self,
  TSSymbol symbol,
  uint32_t start_step_index
) {
  uint32_t index;
  ts_query__pattern_map_search(self, symbol, &index);
  array_insert(&self->pattern_map, index, ((PatternSlice) {
    .step_index = start_step_index,
    .pattern_index = self->pattern_map.size,
  }));
}

// Read one S-expression pattern from the stream, and incorporate it into
// the query's internal state machine representation. For nested patterns,
// this function calls itself recursively.
static TSQueryError ts_query_parse_pattern(
  TSQuery *self,
  Stream *stream,
  uint32_t depth,
  uint32_t *capture_count
) {
  uint16_t starting_step_index = self->steps.size;

  if (stream->next == 0) return TSQueryErrorSyntax;

  // Finish the parent S-expression
  if (stream->next == ')') {
    return PARENT_DONE;
  }

  // Parse a parenthesized node expression
  else if (stream->next == '(') {
    stream_advance(stream);
    stream_skip_whitespace(stream);
    TSSymbol symbol;

    // Parse the wildcard symbol
    if (stream->next == '*') {
      symbol = WILDCARD_SYMBOL;
      stream_advance(stream);
    }

    // Parse a normal node name
    else if (stream_is_ident_start(stream)) {
      const char *node_name = stream->input;
      stream_scan_identifier(stream);
      uint32_t length = stream->input - node_name;
      symbol = ts_query_intern_node_name(
        self,
        node_name,
        length,
        TSSymbolTypeRegular
      );
      if (!symbol) {
        stream_reset(stream, node_name);
        return TSQueryErrorNodeType;
      }
    } else {
      return TSQueryErrorSyntax;
    }

    // Add a step for the node.
    array_push(&self->steps, ((QueryStep) {
      .depth = depth,
      .symbol = symbol,
      .field = 0,
      .capture_id = NONE,
    }));

    // Parse the child patterns
    stream_skip_whitespace(stream);
    for (;;) {
      TSQueryError e = ts_query_parse_pattern(self, stream, depth + 1, capture_count);
      if (e == PARENT_DONE) {
        stream_advance(stream);
        break;
      } else if (e) {
        return e;
      }
    }
  }

  // Parse a double-quoted anonymous leaf node expression
  else if (stream->next == '"') {
    stream_advance(stream);

    // Parse the string content
    const char *string_content = stream->input;
    while (stream->next && stream->next != '"') stream_advance(stream);
    uint32_t length = stream->input - string_content;

    // Add a step for the node
    TSSymbol symbol = ts_query_intern_node_name(
      self,
      string_content,
      length,
      TSSymbolTypeAnonymous
    );
    if (!symbol) {
      stream_reset(stream, string_content);
      return TSQueryErrorNodeType;
    }
    array_push(&self->steps, ((QueryStep) {
      .depth = depth,
      .symbol = symbol,
      .field = 0,
      .capture_id = NONE,
    }));

    if (stream->next != '"') return TSQueryErrorSyntax;
    stream_advance(stream);
  }

  // Parse a field-prefixed pattern
  else if (stream_is_ident_start(stream)) {
    // Parse the field name
    const char *field_name = stream->input;
    stream_scan_identifier(stream);
    uint32_t length = stream->input - field_name;
    stream_skip_whitespace(stream);

    if (stream->next != ':') {
      stream_reset(stream, field_name);
      return TSQueryErrorSyntax;
    }
    stream_advance(stream);
    stream_skip_whitespace(stream);

    // Parse the pattern
    uint32_t step_index = self->steps.size;
    TSQueryError e = ts_query_parse_pattern(self, stream, depth, capture_count);
    if (e == PARENT_DONE) return TSQueryErrorSyntax;
    if (e) return e;

    // Add the field name to the first step of the pattern
    TSFieldId field_id = ts_language_field_id_for_name(
      self->language,
      field_name,
      length
    );
    if (!field_id) {
      stream->input = field_name;
      return TSQueryErrorField;
    }
    self->steps.contents[step_index].field = field_id;
  }

  // Parse a wildcard pattern
  else if (stream->next == '*') {
    stream_advance(stream);
    stream_skip_whitespace(stream);

    // Add a step that matches any kind of node
    array_push(&self->steps, ((QueryStep) {
      .depth = depth,
      .symbol = WILDCARD_SYMBOL,
      .field = 0,
    }));
  }

  // No match
  else {
    return TSQueryErrorSyntax;
  }

  stream_skip_whitespace(stream);

  // Parse an '@'-suffixed capture pattern
  if (stream->next == '@') {
    stream_advance(stream);
    stream_skip_whitespace(stream);

    // Parse the capture name
    if (!stream_is_ident_start(stream)) return TSQueryErrorSyntax;
    const char *capture_name = stream->input;
    stream_scan_identifier(stream);
    uint32_t length = stream->input - capture_name;

    // Add the capture id to the first step of the pattern
    uint16_t capture_id = ts_query_intern_capture_name(
      self,
      capture_name,
      length
    );
    self->steps.contents[starting_step_index].capture_id = capture_id;
    (*capture_count)++;

    stream_skip_whitespace(stream);
  }

  return 0;
}

TSQuery *ts_query_new(
  const TSLanguage *language,
  const char *source,
  uint32_t source_len,
  uint32_t *error_offset,
  TSQueryError *error_type
) {
  TSQuery *self = ts_malloc(sizeof(TSQuery));
  *self = (TSQuery) {
    .steps = array_new(),
    .pattern_map = array_new(),
    .wildcard_root_pattern_count = 0,
    .max_capture_count = 0,
    .language = language,
  };

  // Parse all of the S-expressions in the given string.
  Stream stream = stream_new(source, source_len);
  stream_skip_whitespace(&stream);
  uint32_t start_step_index;
  for (;;) {
    start_step_index = self->steps.size;
    uint32_t capture_count = 0;
    *error_type = ts_query_parse_pattern(self, &stream, 0, &capture_count);
    array_push(&self->steps, ((QueryStep) { .depth = PATTERN_DONE_MARKER }));

    // If any pattern could not be parsed, then report the error information
    // and terminate.
    if (*error_type) {
      *error_offset = stream.input - source;
      ts_query_delete(self);
      return NULL;
    }

    // Maintain a map that can look up patterns for a given root symbol.
    ts_query__pattern_map_insert(
      self,
      self->steps.contents[start_step_index].symbol,
      start_step_index
    );
    if (self->steps.contents[start_step_index].symbol == WILDCARD_SYMBOL) {
      self->wildcard_root_pattern_count++;
    }

    if (capture_count > self->max_capture_count) {
      self->max_capture_count = capture_count;
    }

    if (stream.input == stream.end) break;
  }

  return self;
}

void ts_query_delete(TSQuery *self) {
  if (self) {
    array_delete(&self->steps);
    array_delete(&self->pattern_map);
    array_delete(&self->capture_data);
    array_delete(&self->capture_names);
    ts_free(self);
  }
}

uint32_t ts_query_capture_count(const TSQuery *self) {
  return self->capture_names.size;
}

const char *ts_query_capture_name_for_id(
  const TSQuery *self,
  uint32_t index,
  uint32_t *length
) {
  CaptureSlice name = self->capture_names.contents[index];
  *length = name.length;
  return &self->capture_data.contents[name.offset];
}

int ts_query_capture_id_for_name(
  const TSQuery *self,
  const char *name,
  uint32_t length
) {
  for (unsigned i = 0; i < self->capture_names.size; i++) {
    CaptureSlice existing = self->capture_names.contents[i];
    if (
      existing.length == length &&
      !strncmp(&self->capture_data.contents[existing.offset], name, length)
    ) return i;
  }
  return -1;
}

/***************
 * QueryCursor
 ***************/

TSQueryCursor *ts_query_cursor_new() {
  TSQueryCursor *self = ts_malloc(sizeof(TSQueryCursor));
  *self = (TSQueryCursor) {
    .ascending = false,
    .states = array_new(),
    .finished_states = array_new(),
    .capture_list_pool = capture_list_pool_new(),
    .start_byte = 0,
    .end_byte = UINT32_MAX,
    .start_point = {0, 0},
    .end_point = POINT_MAX,
  };
  return self;
}

void ts_query_cursor_delete(TSQueryCursor *self) {
  array_delete(&self->states);
  array_delete(&self->finished_states);
  ts_tree_cursor_delete(&self->cursor);
  capture_list_pool_delete(&self->capture_list_pool);
  ts_free(self);
}

void ts_query_cursor_exec(
  TSQueryCursor *self,
  const TSQuery *query,
  TSNode node
) {
  array_clear(&self->states);
  array_clear(&self->finished_states);
  ts_tree_cursor_reset(&self->cursor, node);
  capture_list_pool_reset(&self->capture_list_pool, query->max_capture_count);
  self->depth = 0;
  self->ascending = false;
  self->query = query;
}

void ts_query_cursor_set_byte_range(
  TSQueryCursor *self,
  uint32_t start_byte,
  uint32_t end_byte
) {
  if (end_byte == 0) {
    start_byte = 0;
    end_byte = UINT32_MAX;
  }
  self->start_byte = start_byte;
  self->end_byte = end_byte;
}

void ts_query_cursor_set_point_range(
  TSQueryCursor *self,
  TSPoint start_point,
  TSPoint end_point
) {
  if (end_point.row == 0 && end_point.column == 0) {
    start_point = POINT_ZERO;
    end_point = POINT_MAX;
  }
  self->start_point = start_point;
  self->end_point = end_point;
}

static QueryState *ts_query_cursor_copy_state(
  TSQueryCursor *self,
  QueryState *state
) {
  uint32_t new_list_id = capture_list_pool_acquire(&self->capture_list_pool);
  if (new_list_id == NONE) return NULL;
  array_push(&self->states, *state);
  QueryState *new_state = array_back(&self->states);
  new_state->capture_list_id = new_list_id;
  TSQueryCapture *old_captures = capture_list_pool_get(
    &self->capture_list_pool,
    state->capture_list_id
  );
  TSQueryCapture *new_captures = capture_list_pool_get(
    &self->capture_list_pool,
    new_list_id
  );
  memcpy(new_captures, old_captures, state->capture_count * sizeof(TSQueryCapture));
  return new_state;
}

bool ts_query_cursor_next(TSQueryCursor *self) {
  if (self->finished_states.size > 0) {
    QueryState state = array_pop(&self->finished_states);
    capture_list_pool_release(&self->capture_list_pool, state.capture_list_id);
  }

  while (self->finished_states.size == 0) {
    if (self->ascending) {
      // Remove any states that were started within this node and are still
      // not complete.
      uint32_t deleted_count = 0;
      for (unsigned i = 0, n = self->states.size; i < n; i++) {
        QueryState *state = &self->states.contents[i];
        QueryStep *step = &self->query->steps.contents[state->step_index];

        if (state->start_depth + step->depth > self->depth) {
          LOG(
            "fail state with pattern: %u, step: %u\n",
            state->pattern_index,
            state->step_index
          );

          capture_list_pool_release(
            &self->capture_list_pool,
            state->capture_list_id
          );
          deleted_count++;
        } else if (deleted_count > 0) {
          self->states.contents[i - deleted_count] = *state;
        }
      }

      if (deleted_count) {
        LOG("failed %u of %u states\n", deleted_count, self->states.size);
      }

      self->states.size -= deleted_count;

      if (ts_tree_cursor_goto_next_sibling(&self->cursor)) {
        self->ascending = false;
      } else if (ts_tree_cursor_goto_parent(&self->cursor)) {
        self->depth--;
      } else {
        return false;
      }
    } else {
      TSFieldId field_id = NONE;
      bool field_occurs_in_later_sibling = false;
      TSNode node = ts_tree_cursor_current_node(&self->cursor);
      TSSymbol symbol = ts_node_symbol(node);

      // If this node is before the selected range, then avoid
      // descending into it.
      if (
        ts_node_end_byte(node) <= self->start_byte ||
        point_lte(ts_node_end_point(node), self->start_point)
      ) {
        if (!ts_tree_cursor_goto_next_sibling(&self->cursor)) {
          self->ascending = true;
        }
        continue;
      }

      // If this node is after the selected range, then stop walking.
      if (
        self->end_byte <= ts_node_start_byte(node) ||
        point_lte(self->end_point, ts_node_start_point(node))
      ) return false;

      LOG("enter node %s\n", ts_node_type(node));

      // Add new states for any patterns whose root node is a wildcard.
      for (unsigned i = 0; i < self->query->wildcard_root_pattern_count; i++) {
        PatternSlice *slice = &self->query->pattern_map.contents[i];
        QueryStep *step = &self->query->steps.contents[slice->step_index];

        // Check that the node matches the criteria for the first step
        // of the pattern.
        if (step->field) {
          if (field_id == NONE) {
            field_id = ts_tree_cursor_current_field_id_ext(
              &self->cursor,
              &field_occurs_in_later_sibling
            );
          }
          if (field_id != step->field) continue;
        }

        // Add a new state at the start of this pattern.
        uint32_t capture_list_id = capture_list_pool_acquire(
          &self->capture_list_pool
        );
        if (capture_list_id == NONE) break;
        array_push(&self->states, ((QueryState)  {
          .step_index = slice->step_index,
          .pattern_index = slice->pattern_index,
          .capture_list_id = capture_list_id,
        }));
      }

      // Add new states for any patterns whose root node matches this node.
      unsigned i;
      if (ts_query__pattern_map_search(self->query, symbol, &i)) {
        PatternSlice *slice = &self->query->pattern_map.contents[i];
        QueryStep *step = &self->query->steps.contents[slice->step_index];
        do {
          if (step->field) {
            if (field_id == NONE) {
              field_id = ts_tree_cursor_current_field_id_ext(
                &self->cursor,
                &field_occurs_in_later_sibling
              );
            }
            if (field_id != step->field) continue;
          }

          LOG("start pattern %u\n", slice->pattern_index);

          // If the node matches the first step of the pattern, then add
          // a new in-progress state. First, acquire a list to hold the
          // pattern's captures.
          uint32_t capture_list_id = capture_list_pool_acquire(
            &self->capture_list_pool
          );
          if (capture_list_id == NONE) break;

          array_push(&self->states, ((QueryState) {
            .pattern_index = slice->pattern_index,
            .step_index = slice->step_index,
            .start_depth = self->depth,
            .capture_list_id = capture_list_id,
            .capture_count = 0,
          }));

          i++;
          if (i == self->query->pattern_map.size) break;
          slice = &self->query->pattern_map.contents[i];
          step = &self->query->steps.contents[slice->step_index];
        } while (step->symbol == symbol);
      }

      // Update all of the in-progress states with current node.
      for (unsigned i = 0, n = self->states.size; i < n; i++) {
        QueryState *state = &self->states.contents[i];
        QueryStep *step = &self->query->steps.contents[state->step_index];

        // Check that the node matches all of the criteria for the next
        // step of the pattern.
        if (state->start_depth + step->depth != self->depth) continue;
        if (step->symbol && step->symbol != symbol) continue;
        if (step->field) {
          // Only compute the current field if it is needed for the current
          // step of some in-progress pattern.
          if (field_id == NONE) {
            field_id = ts_tree_cursor_current_field_id_ext(
              &self->cursor,
              &field_occurs_in_later_sibling
            );
          }
          if (field_id != step->field) continue;
        }

        // Some patterns can match their root node in multiple ways,
        // capturing different children. If this pattern step could match
        // later children within the same parent, then this query state
        // cannot simply be updated in place. It must be split into two
        // states: one that captures this node, and one which skips over
        // this node, to preserve the possibility of capturing later
        // siblings.
        QueryState *next_state = state;
        if (step->depth > 0 && (!step->field || field_occurs_in_later_sibling)) {
          QueryState *copy = ts_query_cursor_copy_state(self, state);
          if (copy) next_state = copy;
        }

        LOG("advance state for pattern %u\n", next_state->pattern_index);

        // Record captures
        if (step->capture_id != NONE) {
          LOG("capture id %u\n", step->capture_id);

          TSQueryCapture *capture_list = capture_list_pool_get(
            &self->capture_list_pool,
            next_state->capture_list_id
          );
          capture_list[next_state->capture_count++] = (TSQueryCapture) {
            node,
            step->capture_id
          };
        }

        // If the pattern is now done, then populate the query cursor's
        // finished state.
        next_state->step_index++;
        QueryStep *next_step = step + 1;
        if (next_step->depth == PATTERN_DONE_MARKER) {
          LOG("finish pattern %u\n", next_state->pattern_index);

          array_push(&self->finished_states, *next_state);
          if (next_state == state) {
            array_erase(&self->states, i);
            i--;
            n--;
          } else {
            array_pop(&self->states);
          }
        }
      }

      if (ts_tree_cursor_goto_first_child(&self->cursor)) {
        self->depth++;
      } else {
        self->ascending = true;
      }
    }
  }

  return true;
}

uint32_t ts_query_cursor_matched_pattern_index(const TSQueryCursor *self) {
  if (self->finished_states.size > 0) {
    QueryState *state = array_back(&self->finished_states);
    return state->pattern_index;
  }
  return 0;
}

const TSQueryCapture *ts_query_cursor_matched_captures(
  const TSQueryCursor *self,
  uint32_t *count
) {
  if (self->finished_states.size > 0) {
    QueryState *state = array_back(&self->finished_states);
    *count = state->capture_count;
    return capture_list_pool_get(
      (CaptureListPool *)&self->capture_list_pool,
      state->capture_list_id
    );
  }
  return NULL;
}

#undef LOG
