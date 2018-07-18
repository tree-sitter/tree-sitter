#include <assert.h>
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include "tree_sitter/runtime.h"
#include "runtime/subtree.h"
#include "runtime/lexer.h"
#include "runtime/length.h"
#include "runtime/array.h"
#include "runtime/language.h"
#include "runtime/alloc.h"
#include "runtime/stack.h"
#include "runtime/reusable_node.h"
#include "runtime/reduce_action.h"
#include "runtime/error_costs.h"
#include "runtime/tree.h"

#define LOG(...)                                                                            \
  if (self->lexer.logger.log || self->dot_graph_file) {                                     \
    snprintf(self->lexer.debug_buffer, TREE_SITTER_SERIALIZATION_BUFFER_SIZE, __VA_ARGS__); \
    ts_parser__log(self);                                                                   \
  }

#define LOG_STACK()                                                              \
  if (self->dot_graph_file) {                                                    \
    ts_stack_print_dot_graph(self->stack, self->language, self->dot_graph_file); \
    fputs("\n\n", self->dot_graph_file);                                         \
  }

#define LOG_TREE()                                                                         \
  if (self->dot_graph_file) {                                                              \
    ts_subtree_print_dot_graph(self->finished_tree, self->language, self->dot_graph_file); \
    fputs("\n", self->dot_graph_file);                                                     \
  }

#define SYM_NAME(symbol) ts_language_symbol_name(self->language, symbol)

static const unsigned MAX_VERSION_COUNT = 6;
static const unsigned MAX_SUMMARY_DEPTH = 16;
static const unsigned MAX_COST_DIFFERENCE = 16 * ERROR_COST_PER_SKIPPED_TREE;

typedef struct {
  const Subtree *token;
  const Subtree *last_external_token;
  uint32_t byte_index;
} TokenCache;

struct TSParser {
  Lexer lexer;
  Stack *stack;
  SubtreePool tree_pool;
  const TSLanguage *language;
  ReduceActionSet reduce_actions;
  const Subtree *finished_tree;
  Subtree scratch_tree;
  TokenCache token_cache;
  ReusableNode reusable_node;
  void *external_scanner_payload;
  FILE *dot_graph_file;
  unsigned accept_count;
  size_t operation_limit;
  volatile bool enabled;
  bool halt_on_error;
  const Subtree *old_tree;
};

typedef struct {
  unsigned cost;
  unsigned node_count;
  int dynamic_precedence;
  bool is_in_error;
} ErrorStatus;

typedef enum {
  ErrorComparisonTakeLeft,
  ErrorComparisonPreferLeft,
  ErrorComparisonNone,
  ErrorComparisonPreferRight,
  ErrorComparisonTakeRight,
} ErrorComparison;

typedef struct {
  const char *string;
  uint32_t length;
} TSStringInput;

// StringInput

static const char *ts_string_input_read(void *_self, uint32_t byte, TSPoint _, uint32_t *length) {
  TSStringInput *self = (TSStringInput *)_self;
  if (byte >= self->length) {
    *length = 0;
    return "";
  } else {
    *length = self->length - byte;
    return self->string + byte;
  }
}

// Parser - Private

static void ts_parser__log(TSParser *self) {
  if (self->lexer.logger.log) {
    self->lexer.logger.log(
      self->lexer.logger.payload,
      TSLogTypeParse,
      self->lexer.debug_buffer
    );
  }

  if (self->dot_graph_file) {
    fprintf(self->dot_graph_file, "graph {\nlabel=\"");
    for (char *c = &self->lexer.debug_buffer[0]; *c != 0; c++) {
      if (*c == '"') fputc('\\', self->dot_graph_file);
      fputc(*c, self->dot_graph_file);
    }
    fprintf(self->dot_graph_file, "\"\n}\n\n");
  }
}

static bool ts_parser__breakdown_top_of_stack(TSParser *self, StackVersion version) {
  bool did_break_down = false;
  bool pending = false;

  do {
    StackSliceArray pop = ts_stack_pop_pending(self->stack, version);
    if (!pop.size) break;

    did_break_down = true;
    pending = false;
    for (uint32_t i = 0; i < pop.size; i++) {
      StackSlice slice = pop.contents[i];
      TSStateId state = ts_stack_state(self->stack, slice.version);
      const Subtree *parent = *array_front(&slice.subtrees);

      for (uint32_t j = 0; j < parent->children.size; j++) {
        const Subtree *child = parent->children.contents[j];
        pending = child->children.size > 0;

        if (child->symbol == ts_builtin_sym_error) {
          state = ERROR_STATE;
        } else if (!child->extra) {
          state = ts_language_next_state(self->language, state, child->symbol);
        }

        ts_subtree_retain(child);
        ts_stack_push(self->stack, slice.version, child, pending, state);
      }

      for (uint32_t j = 1; j < slice.subtrees.size; j++) {
        const Subtree *tree = slice.subtrees.contents[j];
        ts_stack_push(self->stack, slice.version, tree, false, state);
      }

      ts_subtree_release(&self->tree_pool, parent);
      array_delete(&slice.subtrees);

      LOG("breakdown_top_of_stack tree:%s", SYM_NAME(parent->symbol));
      LOG_STACK();
    }
  } while (pending);

  return did_break_down;
}

static void ts_parser__breakdown_lookahead(TSParser *self, const Subtree **lookahead,
                                           TSStateId state, ReusableNode *reusable_node) {
  bool did_descend = false;
  const Subtree *tree = reusable_node_tree(reusable_node);
  while (tree->children.size > 0 && tree->parse_state != state) {
    LOG("state_mismatch sym:%s", SYM_NAME(tree->symbol));
    reusable_node_descend(reusable_node);
    tree = reusable_node_tree(reusable_node);
    did_descend = true;
  }

  if (did_descend) {
    ts_subtree_release(&self->tree_pool, *lookahead);
    *lookahead = tree;
    ts_subtree_retain(*lookahead);
  }
}

static ErrorComparison ts_parser__compare_versions(TSParser *self, ErrorStatus a, ErrorStatus b) {
  if (!a.is_in_error && b.is_in_error) {
    if (a.cost < b.cost) {
      return ErrorComparisonTakeLeft;
    } else {
      return ErrorComparisonPreferLeft;
    }
  }

  if (a.is_in_error && !b.is_in_error) {
    if (b.cost < a.cost) {
      return ErrorComparisonTakeRight;
    } else {
      return ErrorComparisonPreferRight;
    }
  }

  if (a.cost < b.cost) {
    if ((b.cost - a.cost) * (1 + a.node_count) > MAX_COST_DIFFERENCE) {
      return ErrorComparisonTakeLeft;
    } else {
      return ErrorComparisonPreferLeft;
    }
  }

  if (b.cost < a.cost) {
    if ((a.cost - b.cost) * (1 + b.node_count) > MAX_COST_DIFFERENCE) {
      return ErrorComparisonTakeRight;
    } else {
      return ErrorComparisonPreferRight;
    }
  }

  if (a.dynamic_precedence > b.dynamic_precedence) return ErrorComparisonPreferLeft;
  if (b.dynamic_precedence > a.dynamic_precedence) return ErrorComparisonPreferRight;
  return ErrorComparisonNone;
}

static ErrorStatus ts_parser__version_status(TSParser *self, StackVersion version) {
  unsigned cost = ts_stack_error_cost(self->stack, version);
  bool is_paused = ts_stack_is_paused(self->stack, version);
  if (is_paused) cost += ERROR_COST_PER_SKIPPED_TREE;
  return (ErrorStatus) {
    .cost = cost,
    .node_count = ts_stack_node_count_since_error(self->stack, version),
    .dynamic_precedence = ts_stack_dynamic_precedence(self->stack, version),
    .is_in_error = is_paused || ts_stack_state(self->stack, version) == ERROR_STATE
  };
}

static bool ts_parser__better_version_exists(TSParser *self, StackVersion version,
                                          bool is_in_error, unsigned cost) {
  if (self->finished_tree && self->finished_tree->error_cost <= cost) return true;

  Length position = ts_stack_position(self->stack, version);
  ErrorStatus status = {
    .cost = cost,
    .is_in_error = is_in_error,
    .dynamic_precedence = ts_stack_dynamic_precedence(self->stack, version),
    .node_count = ts_stack_node_count_since_error(self->stack, version),
  };

  for (StackVersion i = 0, n = ts_stack_version_count(self->stack); i < n; i++) {
    if (i == version ||
        !ts_stack_is_active(self->stack, i) ||
        ts_stack_position(self->stack, i).bytes < position.bytes) continue;
    ErrorStatus status_i = ts_parser__version_status(self, i);
    switch (ts_parser__compare_versions(self, status, status_i)) {
      case ErrorComparisonTakeRight:
        return true;
      case ErrorComparisonPreferRight:
        if (ts_stack_can_merge(self->stack, i, version)) return true;
      default:
        break;
    }
  }

  return false;
}

static void ts_parser__restore_external_scanner(TSParser *self, const Subtree *external_token) {
  if (external_token) {
    self->language->external_scanner.deserialize(
      self->external_scanner_payload,
      ts_external_scanner_state_data(&external_token->external_scanner_state),
      external_token->external_scanner_state.length
    );
  } else {
    self->language->external_scanner.deserialize(self->external_scanner_payload, NULL, 0);
  }
}

static bool ts_parser__can_reuse_first_leaf(TSParser *self, TSStateId state, const Subtree *tree,
                                            TableEntry *table_entry) {
  TSLexMode current_lex_mode = self->language->lex_modes[state];

  // If the token was created in a state with the same set of lookaheads, it is reusable.
  if (tree->first_leaf.lex_mode.lex_state == current_lex_mode.lex_state &&
      tree->first_leaf.lex_mode.external_lex_state == current_lex_mode.external_lex_state &&
      (tree->first_leaf.symbol != self->language->keyword_capture_token ||
       (!tree->is_keyword && tree->parse_state == state))) return true;

  // Empty tokens are not reusable in states with different lookaheads.
  if (tree->size.bytes == 0 && tree->symbol != ts_builtin_sym_end) return false;

  // If the current state allows external tokens or other tokens that conflict with this
  // token, this token is not reusable.
  return current_lex_mode.external_lex_state == 0 && table_entry->is_reusable;
}

static const Subtree *ts_parser__lex(TSParser *self, StackVersion version, TSStateId parse_state) {
  Length start_position = ts_stack_position(self->stack, version);
  const Subtree *external_token = ts_stack_last_external_token(self->stack, version);
  TSLexMode lex_mode = self->language->lex_modes[parse_state];
  const bool *valid_external_tokens = ts_language_enabled_external_tokens(
    self->language,
    lex_mode.external_lex_state
  );

  bool found_external_token = false;
  bool error_mode = parse_state == ERROR_STATE;
  bool skipped_error = false;
  int32_t first_error_character = 0;
  Length error_start_position = length_zero();
  Length error_end_position = length_zero();
  uint32_t last_byte_scanned = start_position.bytes;
  ts_lexer_reset(&self->lexer, start_position);

  for (;;) {
    Length current_position = self->lexer.current_position;

    if (valid_external_tokens) {
      LOG(
        "lex_external state:%d, row:%u, column:%u",
        lex_mode.external_lex_state,
        current_position.extent.row,
        current_position.extent.column
      );
      ts_lexer_start(&self->lexer);
      ts_parser__restore_external_scanner(self, external_token);
      if (self->language->external_scanner.scan(
        self->external_scanner_payload,
        &self->lexer.data,
        valid_external_tokens
      )) {
        if (length_is_undefined(self->lexer.token_end_position)) {
          self->lexer.data.mark_end(&self->lexer.data);
        }

        if (!error_mode || self->lexer.token_end_position.bytes > current_position.bytes) {
          found_external_token = true;
          break;
        }
      }

      if (self->lexer.current_position.bytes > last_byte_scanned) {
        last_byte_scanned = self->lexer.current_position.bytes;
      }
      ts_lexer_reset(&self->lexer, current_position);
    }

    LOG(
      "lex_internal state:%d, row:%u, column:%u",
      lex_mode.lex_state,
      current_position.extent.row,
      current_position.extent.column
    );
    ts_lexer_start(&self->lexer);
    if (self->language->lex_fn(&self->lexer.data, lex_mode.lex_state)) {
      break;
    }

    if (!error_mode) {
      error_mode = true;
      lex_mode = self->language->lex_modes[ERROR_STATE];
      valid_external_tokens = ts_language_enabled_external_tokens(
        self->language,
        lex_mode.external_lex_state
      );
      if (self->lexer.current_position.bytes > last_byte_scanned) {
        last_byte_scanned = self->lexer.current_position.bytes;
      }
      ts_lexer_reset(&self->lexer, start_position);
      continue;
    }

    if (!skipped_error) {
      LOG("skip_unrecognized_character");
      skipped_error = true;
      error_start_position = self->lexer.token_start_position;
      error_end_position = self->lexer.token_start_position;
      first_error_character = self->lexer.data.lookahead;
    }

    if (self->lexer.current_position.bytes == error_end_position.bytes) {
      if (self->lexer.data.lookahead == 0) {
        self->lexer.data.result_symbol = ts_builtin_sym_error;
        break;
      }
      self->lexer.data.advance(&self->lexer.data, false);
    }

    error_end_position = self->lexer.current_position;
  }

  if (self->lexer.current_position.bytes > last_byte_scanned) {
    last_byte_scanned = self->lexer.current_position.bytes;
  }

  Subtree *result;
  if (skipped_error) {
    Length padding = length_sub(error_start_position, start_position);
    Length size = length_sub(error_end_position, error_start_position);
    result = ts_subtree_new_error(&self->tree_pool, size, padding, first_error_character, self->language);
  } else {
    if (self->lexer.token_end_position.bytes < self->lexer.token_start_position.bytes) {
      self->lexer.token_start_position = self->lexer.token_end_position;
    }

    bool is_keyword = false;
    TSSymbol symbol = self->lexer.data.result_symbol;
    Length padding = length_sub(self->lexer.token_start_position, start_position);
    Length size = length_sub(self->lexer.token_end_position, self->lexer.token_start_position);

    if (found_external_token) {
      symbol = self->language->external_scanner.symbol_map[symbol];
    } else if (symbol == self->language->keyword_capture_token && symbol != 0) {
      uint32_t end_byte = self->lexer.token_end_position.bytes;
      ts_lexer_reset(&self->lexer, self->lexer.token_start_position);
      ts_lexer_start(&self->lexer);
      if (
        self->language->keyword_lex_fn(&self->lexer.data, 0) &&
        self->lexer.token_end_position.bytes == end_byte &&
        ts_language_has_actions(self->language, parse_state, self->lexer.data.result_symbol)
      ) {
        is_keyword = true;
        symbol = self->lexer.data.result_symbol;
      }
    }

    result = ts_subtree_new_leaf(&self->tree_pool, symbol, padding, size, self->language);
    result->is_keyword = is_keyword;

    if (found_external_token) {
      result->has_external_tokens = true;
      unsigned length = self->language->external_scanner.serialize(
        self->external_scanner_payload,
        self->lexer.debug_buffer
      );
      ts_external_scanner_state_init(&result->external_scanner_state, self->lexer.debug_buffer, length);
    }
  }

  result->bytes_scanned = last_byte_scanned - start_position.bytes + 1;
  result->parse_state = parse_state;
  result->first_leaf.lex_mode = lex_mode;

  LOG("lexed_lookahead sym:%s, size:%u", SYM_NAME(result->symbol), result->size.bytes);
  return result;
}

static const Subtree *ts_parser__get_cached_token(TSParser *self, TSStateId state,
                                                  size_t position,
                                                  const Subtree *last_external_token,
                                                  TableEntry *table_entry) {
  TokenCache *cache = &self->token_cache;
  if (
    cache->token && cache->byte_index == position &&
    ts_subtree_external_scanner_state_eq(cache->last_external_token, last_external_token)
  ) {
    ts_language_table_entry(self->language, state, cache->token->first_leaf.symbol, table_entry);
    if (ts_parser__can_reuse_first_leaf(self, state, cache->token, table_entry)) {
      ts_subtree_retain(cache->token);
      return cache->token;
    }
  }
  return NULL;
}

static void ts_parser__set_cached_token(TSParser *self, size_t byte_index,
                                        const Subtree *last_external_token,
                                        const Subtree *token) {
  TokenCache *cache = &self->token_cache;
  if (token) ts_subtree_retain(token);
  if (last_external_token) ts_subtree_retain(last_external_token);
  if (cache->token) ts_subtree_release(&self->tree_pool, cache->token);
  if (cache->last_external_token) ts_subtree_release(&self->tree_pool, cache->last_external_token);
  cache->token = token;
  cache->byte_index = byte_index;
  cache->last_external_token = last_external_token;
}

static const Subtree *ts_parser__reuse_node(TSParser *self, StackVersion version,
                                            TSStateId *state, uint32_t position,
                                            const Subtree *last_external_token,
                                            TableEntry *table_entry) {
  const Subtree *result;
  while ((result = reusable_node_tree(&self->reusable_node))) {
    uint32_t byte_offset = reusable_node_byte_offset(&self->reusable_node);
    if (byte_offset > position) {
      LOG("before_reusable_node symbol:%s", SYM_NAME(result->symbol));
      break;
    }

    if (byte_offset < position) {
      LOG("past_reusable_node symbol:%s", SYM_NAME(result->symbol));
      reusable_node_advance(&self->reusable_node);
      continue;
    }

    if (!ts_subtree_external_scanner_state_eq(self->reusable_node.last_external_token, last_external_token)) {
      LOG("reusable_node_has_different_external_scanner_state symbol:%s", SYM_NAME(result->symbol));
      reusable_node_advance(&self->reusable_node);
      continue;
    }

    const char *reason = NULL;
    if (result->has_changes) {
      reason = "has_changes";
    } else if (result->symbol == ts_builtin_sym_error) {
      reason = "is_error";
    } else if (result->is_missing) {
      reason = "is_missing";
    } else if (result->fragile_left || result->fragile_right) {
      reason = "is_fragile";
    }

    if (reason) {
      LOG("cant_reuse_node_%s tree:%s", reason, SYM_NAME(result->symbol));
      if (!reusable_node_descend(&self->reusable_node)) {
        reusable_node_advance(&self->reusable_node);
        ts_parser__breakdown_top_of_stack(self, version);
        *state = ts_stack_state(self->stack, version);
      }
      continue;
    }

    ts_language_table_entry(self->language, *state, result->first_leaf.symbol, table_entry);
    if (!ts_parser__can_reuse_first_leaf(self, *state, result, table_entry)) {
      LOG(
        "cant_reuse_node symbol:%s, first_leaf_symbol:%s",
        SYM_NAME(result->symbol),
        SYM_NAME(result->first_leaf.symbol)
      );
      reusable_node_advance_past_leaf(&self->reusable_node);
      break;
    }

    LOG("reuse_node symbol:%s", SYM_NAME(result->symbol));
    ts_subtree_retain(result);
    return result;
  }

  return NULL;
}

static bool ts_parser__select_tree(TSParser *self, const Subtree *left, const Subtree *right) {
  if (!left) return true;
  if (!right) return false;

  if (right->error_cost < left->error_cost) {
    LOG("select_smaller_error symbol:%s, over_symbol:%s",
        SYM_NAME(right->symbol), SYM_NAME(left->symbol));
    return true;
  }

  if (left->error_cost < right->error_cost) {
    LOG("select_smaller_error symbol:%s, over_symbol:%s",
        SYM_NAME(left->symbol), SYM_NAME(right->symbol));
    return false;
  }

  if (right->dynamic_precedence > left->dynamic_precedence) {
    LOG("select_higher_precedence symbol:%s, prec:%u, over_symbol:%s, other_prec:%u",
        SYM_NAME(right->symbol), right->dynamic_precedence, SYM_NAME(left->symbol),
        left->dynamic_precedence);
    return true;
  }

  if (left->dynamic_precedence > right->dynamic_precedence) {
    LOG("select_higher_precedence symbol:%s, prec:%u, over_symbol:%s, other_prec:%u",
        SYM_NAME(left->symbol), left->dynamic_precedence, SYM_NAME(right->symbol),
        right->dynamic_precedence);
    return false;
  }

  if (left->error_cost > 0) return true;

  int comparison = ts_subtree_compare(left, right);
  switch (comparison) {
    case -1:
      LOG("select_earlier symbol:%s, over_symbol:%s", SYM_NAME(left->symbol),
          SYM_NAME(right->symbol));
      return false;
      break;
    case 1:
      LOG("select_earlier symbol:%s, over_symbol:%s", SYM_NAME(right->symbol),
          SYM_NAME(left->symbol));
      return true;
    default:
      LOG("select_existing symbol:%s, over_symbol:%s", SYM_NAME(left->symbol),
          SYM_NAME(right->symbol));
      return false;
  }
}

static void ts_parser__shift(TSParser *self, StackVersion version, TSStateId state,
                             const Subtree *lookahead, bool extra) {
  const Subtree *subtree_to_push;
  if (extra != lookahead->extra) {
    Subtree *result = ts_subtree_make_mut(&self->tree_pool, lookahead);
    result->extra = extra;
    subtree_to_push = result;
  } else {
    subtree_to_push = lookahead;
  }

  bool is_pending = subtree_to_push->children.size > 0;
  ts_stack_push(self->stack, version, subtree_to_push, is_pending, state);
  if (subtree_to_push->has_external_tokens) {
    ts_stack_set_last_external_token(
      self->stack, version, ts_subtree_last_external_token(subtree_to_push)
    );
  }
}

static bool ts_parser__replace_children(TSParser *self, Subtree *tree, SubtreeArray *children) {
  self->scratch_tree = *tree;
  self->scratch_tree.children.size = 0;
  ts_subtree_set_children(&self->scratch_tree, children, self->language);
  if (ts_parser__select_tree(self, tree, &self->scratch_tree)) {
    *tree = self->scratch_tree;
    return true;
  } else {
    return false;
  }
}

static StackSliceArray ts_parser__reduce(TSParser *self, StackVersion version, TSSymbol symbol,
                                     uint32_t count, int dynamic_precedence,
                                     uint16_t alias_sequence_id, bool fragile) {
  uint32_t initial_version_count = ts_stack_version_count(self->stack);

  StackSliceArray pop = ts_stack_pop_count(self->stack, version, count);

  for (uint32_t i = 0; i < pop.size; i++) {
    StackSlice slice = pop.contents[i];

    // Extra tokens on top of the stack should not be included in this new parent
    // node. They will be re-pushed onto the stack after the parent node is
    // created and pushed.
    SubtreeArray children = slice.subtrees;
    while (children.size > 0 && children.contents[children.size - 1]->extra) {
      children.size--;
    }

    Subtree *parent = ts_subtree_new_node(&self->tree_pool,
      symbol, &children, alias_sequence_id, self->language
    );

    // This pop operation may have caused multiple stack versions to collapse
    // into one, because they all diverged from a common state. In that case,
    // choose one of the arrays of trees to be the parent node's children, and
    // delete the rest of the tree arrays.
    while (i + 1 < pop.size) {
      StackSlice next_slice = pop.contents[i + 1];
      if (next_slice.version != slice.version) break;
      i++;

      SubtreeArray children = next_slice.subtrees;
      while (children.size > 0 && children.contents[children.size - 1]->extra) {
        children.size--;
      }

      if (ts_parser__replace_children(self, parent, &children)) {
        ts_subtree_array_delete(&self->tree_pool, &slice.subtrees);
        slice = next_slice;
      } else {
        ts_subtree_array_delete(&self->tree_pool, &next_slice.subtrees);
      }
    }

    parent->dynamic_precedence += dynamic_precedence;
    parent->alias_sequence_id = alias_sequence_id;

    TSStateId state = ts_stack_state(self->stack, slice.version);
    TSStateId next_state = ts_language_next_state(self->language, state, symbol);
    if (fragile || pop.size > 1 || initial_version_count > 1) {
      parent->fragile_left = true;
      parent->fragile_right = true;
      parent->parse_state = TS_TREE_STATE_NONE;
    } else {
      parent->parse_state = state;
    }

    // Push the parent node onto the stack, along with any extra tokens that
    // were previously on top of the stack.
    ts_stack_push(self->stack, slice.version, parent, false, next_state);
    for (uint32_t j = parent->children.size; j < slice.subtrees.size; j++) {
      ts_stack_push(self->stack, slice.version, slice.subtrees.contents[j], false, next_state);
    }

    if (ts_stack_version_count(self->stack) > MAX_VERSION_COUNT) {
      i++;
      while (i < pop.size) {
        StackSlice slice = pop.contents[i];
        ts_subtree_array_delete(&self->tree_pool, &slice.subtrees);
        ts_stack_halt(self->stack, slice.version);
        i++;
      }
      while (ts_stack_version_count(self->stack) > slice.version + 1) {
        ts_stack_remove_version(self->stack, slice.version + 1);
      }
      break;
    }
  }

  for (StackVersion i = initial_version_count; i < ts_stack_version_count(self->stack); i++) {
    for (StackVersion j = initial_version_count; j < i; j++) {
      if (ts_stack_merge(self->stack, j, i)) {
        i--;
        break;
      }
    }
  }

  return pop;
}

static void ts_parser__accept(TSParser *self, StackVersion version, const Subtree *lookahead) {
  assert(lookahead->symbol == ts_builtin_sym_end);
  ts_stack_push(self->stack, version, lookahead, false, 1);

  StackSliceArray pop = ts_stack_pop_all(self->stack, version);
  for (uint32_t i = 0; i < pop.size; i++) {
    SubtreeArray trees = pop.contents[i].subtrees;

    const Subtree *root = NULL;
    for (uint32_t j = trees.size - 1; j + 1 > 0; j--) {
      const Subtree *child = trees.contents[j];
      if (!child->extra) {
        for (uint32_t k = 0; k < child->children.size; k++) {
          ts_subtree_retain(child->children.contents[k]);
        }
        array_splice(&trees, j, 1, &child->children);
        root = ts_subtree_new_node(
          &self->tree_pool, child->symbol, &trees,
          child->alias_sequence_id, self->language
        );
        ts_subtree_release(&self->tree_pool, child);
        break;
      }
    }

    assert(root && root->ref_count > 0);
    self->accept_count++;

    if (self->finished_tree) {
      if (ts_parser__select_tree(self, self->finished_tree, root)) {
        ts_subtree_release(&self->tree_pool, self->finished_tree);
        self->finished_tree = root;
      } else {
        ts_subtree_release(&self->tree_pool, root);
      }
    } else {
      self->finished_tree = root;
    }
  }

  ts_stack_remove_version(self->stack, pop.contents[0].version);
  ts_stack_halt(self->stack, version);
}

static bool ts_parser__do_all_potential_reductions(TSParser *self, StackVersion starting_version,
                                                TSSymbol lookahead_symbol) {
  uint32_t initial_version_count = ts_stack_version_count(self->stack);

  bool can_shift_lookahead_symbol = false;
  StackVersion version = starting_version;
  for (unsigned i = 0; true; i++) {
    uint32_t version_count = ts_stack_version_count(self->stack);
    if (version >= version_count) break;

    bool merged = false;
    for (StackVersion i = initial_version_count; i < version; i++) {
      if (ts_stack_merge(self->stack, i, version)) {
        merged = true;
        break;
      }
    }
    if (merged) continue;

    TSStateId state = ts_stack_state(self->stack, version);
    bool has_shift_action = false;
    array_clear(&self->reduce_actions);

    TSSymbol first_symbol, end_symbol;
    if (lookahead_symbol != 0) {
      first_symbol = lookahead_symbol;
      end_symbol = lookahead_symbol + 1;
    } else {
      first_symbol = 1;
      end_symbol = self->language->token_count;
    }

    for (TSSymbol symbol = first_symbol; symbol < end_symbol; symbol++) {
      TableEntry entry;
      ts_language_table_entry(self->language, state, symbol, &entry);
      for (uint32_t i = 0; i < entry.action_count; i++) {
        TSParseAction action = entry.actions[i];
        switch (action.type) {
          case TSParseActionTypeShift:
          case TSParseActionTypeRecover:
            if (!action.params.extra && !action.params.repetition) has_shift_action = true;
            break;
          case TSParseActionTypeReduce:
            if (action.params.child_count > 0)
              ts_reduce_action_set_add(&self->reduce_actions, (ReduceAction){
                .symbol = action.params.symbol,
                .count = action.params.child_count,
                .dynamic_precedence = action.params.dynamic_precedence,
                .alias_sequence_id = action.params.alias_sequence_id,
              });
          default:
            break;
        }
      }
    }

    for (uint32_t i = 0; i < self->reduce_actions.size; i++) {
      ReduceAction action = self->reduce_actions.contents[i];

      ts_parser__reduce(
        self, version, action.symbol, action.count,
        action.dynamic_precedence, action.alias_sequence_id,
        true
      );
    }

    if (has_shift_action) {
      can_shift_lookahead_symbol = true;
    } else if (self->reduce_actions.size > 0 && i < MAX_VERSION_COUNT) {
      ts_stack_renumber_version(self->stack, version_count, version);
      continue;
    } else if (lookahead_symbol != 0) {
      ts_stack_remove_version(self->stack, version);
    }

    if (version == starting_version) {
      version = version_count;
    } else {
      version++;
    }
  }

  return can_shift_lookahead_symbol;
}

static void ts_parser__handle_error(TSParser *self, StackVersion version,
                                    TSSymbol lookahead_symbol) {
  // Perform any reductions that could have happened in this state, regardless of the lookahead.
  uint32_t previous_version_count = ts_stack_version_count(self->stack);
  ts_parser__do_all_potential_reductions(self, version, 0);
  uint32_t version_count = ts_stack_version_count(self->stack);

  // Push a discontinuity onto the stack. Merge all of the stack versions that
  // were created in the previous step.
  bool did_insert_missing_token = false;
  for (StackVersion v = version; v < version_count;) {
    if (!did_insert_missing_token) {
      TSStateId state = ts_stack_state(self->stack, v);
      for (TSSymbol missing_symbol = 1;
           missing_symbol < self->language->token_count;
           missing_symbol++) {
        TSStateId state_after_missing_symbol = ts_language_next_state(
          self->language, state, missing_symbol
        );
        if (state_after_missing_symbol == 0) continue;

        if (ts_language_has_reduce_action(
          self->language,
          state_after_missing_symbol,
          lookahead_symbol
        )) {
          StackVersion version_with_missing_tree = ts_stack_copy_version(self->stack, v);
          const Subtree *missing_tree = ts_subtree_new_missing_leaf(
            &self->tree_pool, missing_symbol, self->language
          );
          ts_stack_push(
            self->stack, version_with_missing_tree,
            missing_tree, false,
            state_after_missing_symbol
          );

          if (ts_parser__do_all_potential_reductions(
            self, version_with_missing_tree,
            lookahead_symbol
          )) {
            LOG(
              "recover_with_missing symbol:%s, state:%u",
              SYM_NAME(missing_symbol),
              ts_stack_state(self->stack, version_with_missing_tree)
            );
            did_insert_missing_token = true;
            break;
          }
        }
      }
    }

    ts_stack_push(self->stack, v, NULL, false, ERROR_STATE);
    v = (v == version) ? previous_version_count : v + 1;
  }

  for (unsigned i = previous_version_count; i < version_count; i++) {
    assert(ts_stack_merge(self->stack, version, previous_version_count));
  }

  ts_stack_record_summary(self->stack, version, MAX_SUMMARY_DEPTH);
  LOG_STACK();
}

static void ts_parser__halt_parse(TSParser *self) {
  LOG("halting_parse");
  LOG_STACK();

  ts_lexer_advance_to_end(&self->lexer);
  Length remaining_length = length_sub(
    self->lexer.current_position,
    ts_stack_position(self->stack, 0)
  );

  Subtree *filler_node = ts_subtree_new_error(&self->tree_pool, remaining_length, length_zero(), 0, self->language);
  filler_node->visible = false;
  ts_stack_push(self->stack, 0, filler_node, false, 0);

  SubtreeArray children = array_new();
  Subtree *root_error = ts_subtree_new_error_node(&self->tree_pool, &children, self->language);
  ts_stack_push(self->stack, 0, root_error, false, 0);

  Subtree *eof = ts_subtree_new_leaf(&self->tree_pool, ts_builtin_sym_end, length_zero(), length_zero(), self->language);
  ts_parser__accept(self, 0, eof);
}

static bool ts_parser__recover_to_state(TSParser *self, StackVersion version, unsigned depth,
                                        TSStateId goal_state) {
  StackSliceArray pop = ts_stack_pop_count(self->stack, version, depth);
  StackVersion previous_version = STACK_VERSION_NONE;

  for (unsigned i = 0; i < pop.size; i++) {
    StackSlice slice = pop.contents[i];

    if (slice.version == previous_version) {
      ts_subtree_array_delete(&self->tree_pool, &slice.subtrees);
      array_erase(&pop, i--);
      continue;
    }

    if (ts_stack_state(self->stack, slice.version) != goal_state) {
      ts_stack_halt(self->stack, slice.version);
      ts_subtree_array_delete(&self->tree_pool, &slice.subtrees);
      array_erase(&pop, i--);
      continue;
    }

    SubtreeArray error_trees = ts_stack_pop_error(self->stack, slice.version);
    if (error_trees.size > 0) {
      assert(error_trees.size == 1);
      array_splice(&slice.subtrees, 0, 0, &error_trees.contents[0]->children);
      for (unsigned j = 0; j < error_trees.contents[0]->children.size; j++) {
        ts_subtree_retain(slice.subtrees.contents[j]);
      }
      ts_subtree_array_delete(&self->tree_pool, &error_trees);
    }

    SubtreeArray trailing_extras = ts_subtree_array_remove_trailing_extras(&slice.subtrees);

    if (slice.subtrees.size > 0) {
      Subtree *error = ts_subtree_new_error_node(&self->tree_pool, &slice.subtrees, self->language);
      error->extra = true;
      ts_stack_push(self->stack, slice.version, error, false, goal_state);
    } else {
      array_delete(&slice.subtrees);
    }

    for (unsigned j = 0; j < trailing_extras.size; j++) {
      const Subtree *tree = trailing_extras.contents[j];
      ts_stack_push(self->stack, slice.version, tree, false, goal_state);
    }

    previous_version = slice.version;
    array_delete(&trailing_extras);
  }

  return previous_version != STACK_VERSION_NONE;
}

static void ts_parser__recover(TSParser *self, StackVersion version, const Subtree *lookahead) {
  bool did_recover = false;
  unsigned previous_version_count = ts_stack_version_count(self->stack);
  Length position = ts_stack_position(self->stack, version);
  StackSummary *summary = ts_stack_get_summary(self->stack, version);
  unsigned node_count_since_error = ts_stack_node_count_since_error(self->stack, version);
  unsigned current_error_cost = ts_stack_error_cost(self->stack, version);

  if (summary && lookahead->symbol != ts_builtin_sym_error) {
    for (unsigned i = 0; i < summary->size; i++) {
      StackSummaryEntry entry = summary->contents[i];

      if (entry.state == ERROR_STATE) continue;
      if (entry.position.bytes == position.bytes) continue;
      unsigned depth = entry.depth;
      if (node_count_since_error > 0) depth++;

      bool would_merge = false;
      for (unsigned j = 0; j < previous_version_count; j++) {
        if (
          ts_stack_state(self->stack, j) == entry.state &&
          ts_stack_position(self->stack, j).bytes == position.bytes
        ) {
          would_merge = true;
          break;
        }
      }

      if (would_merge) continue;

      unsigned new_cost =
        current_error_cost +
        entry.depth * ERROR_COST_PER_SKIPPED_TREE +
        (position.bytes - entry.position.bytes) * ERROR_COST_PER_SKIPPED_CHAR +
        (position.extent.row - entry.position.extent.row) * ERROR_COST_PER_SKIPPED_LINE;
      if (ts_parser__better_version_exists(self, version, false, new_cost)) break;

      if (ts_language_has_actions(self->language, entry.state, lookahead->symbol)) {
        if (ts_parser__recover_to_state(self, version, depth, entry.state)) {
          did_recover = true;
          LOG("recover_to_previous state:%u, depth:%u", entry.state, depth);
          LOG_STACK();
          break;
        }
      }
    }
  }

  for (unsigned i = previous_version_count; i < ts_stack_version_count(self->stack); i++) {
    if (!ts_stack_is_active(self->stack, i)) {
      ts_stack_remove_version(self->stack, i--);
    }
  }

  if (did_recover && ts_stack_version_count(self->stack) > MAX_VERSION_COUNT) {
    ts_stack_halt(self->stack, version);
    ts_subtree_release(&self->tree_pool, lookahead);
    return;
  }

  if (lookahead->symbol == ts_builtin_sym_end) {
    LOG("recover_eof");
    SubtreeArray children = array_new();
    const Subtree *parent = ts_subtree_new_error_node(&self->tree_pool, &children, self->language);
    ts_stack_push(self->stack, version, parent, false, 1);
    ts_parser__accept(self, version, lookahead);
    return;
  }

  unsigned new_cost =
    current_error_cost + ERROR_COST_PER_SKIPPED_TREE +
    ts_subtree_total_bytes(lookahead) * ERROR_COST_PER_SKIPPED_CHAR +
    ts_subtree_total_size(lookahead).extent.row * ERROR_COST_PER_SKIPPED_LINE;

  if (ts_parser__better_version_exists(self, version, false, new_cost)) {
    ts_stack_halt(self->stack, version);
    ts_subtree_release(&self->tree_pool, lookahead);
    return;
  }

  unsigned n;
  const TSParseAction *actions = ts_language_actions(self->language, 1, lookahead->symbol, &n);
  if (n > 0 && actions[n - 1].type == TSParseActionTypeShift && actions[n - 1].params.extra) {
    Subtree *mutable_lookahead = ts_subtree_make_mut(&self->tree_pool, lookahead);
    mutable_lookahead->extra = true;
    lookahead = mutable_lookahead;
  }

  LOG("skip_token symbol:%s", SYM_NAME(lookahead->symbol));
  SubtreeArray children = array_new();
  array_reserve(&children, 1);
  array_push(&children, lookahead);
  const Subtree *error_repeat = ts_subtree_new_node(
    &self->tree_pool,
    ts_builtin_sym_error_repeat,
    &children,
    0,
    self->language
  );

  if (node_count_since_error > 0) {
    StackSliceArray pop = ts_stack_pop_count(self->stack, version, 1);
    assert(pop.size == 1);
    assert(pop.contents[0].subtrees.size == 1);
    ts_stack_renumber_version(self->stack, pop.contents[0].version, version);
    array_push(&pop.contents[0].subtrees, error_repeat);
    error_repeat = ts_subtree_new_node(
      &self->tree_pool,
      ts_builtin_sym_error_repeat,
      &pop.contents[0].subtrees,
      0,
      self->language
    );
  }

  ts_stack_push(self->stack, version, error_repeat, false, ERROR_STATE);

  if (lookahead->has_external_tokens) {
    ts_stack_set_last_external_token(
      self->stack, version, ts_subtree_last_external_token(lookahead)
    );
  }
}

static void ts_parser__advance(TSParser *self, StackVersion version, bool allow_node_reuse) {
  TSStateId state = ts_stack_state(self->stack, version);
  uint32_t position = ts_stack_position(self->stack, version).bytes;
  const Subtree *last_external_token = ts_stack_last_external_token(self->stack, version);

  bool did_reuse = true;
  const Subtree *lookahead = NULL;
  TableEntry table_entry;

  // If possible, reuse a node from the previous syntax tree.
  if (allow_node_reuse) {
    lookahead = ts_parser__reuse_node(
      self, version, &state, position, last_external_token, &table_entry
    );
  }

  // Otherwise, try to reuse the token previously returned by the lexer.
  if (!lookahead) {
    did_reuse = false;
    lookahead = ts_parser__get_cached_token(
      self, state, position, last_external_token, &table_entry
    );
  }

  // Otherwise, re-run the lexer.
  if (!lookahead) {
    lookahead = ts_parser__lex(self, version, state);
    ts_parser__set_cached_token(self, position, last_external_token, lookahead);
    ts_language_table_entry(self->language, state, lookahead->symbol, &table_entry);
  }

  for (;;) {
    StackVersion last_reduction_version = STACK_VERSION_NONE;

    for (uint32_t i = 0; i < table_entry.action_count; i++) {
      TSParseAction action = table_entry.actions[i];

      switch (action.type) {
        case TSParseActionTypeShift: {
          if (action.params.repetition) break;
          TSStateId next_state;
          if (action.params.extra) {

            // TODO remove when TREE_SITTER_LANGUAGE_VERSION 9 is out.
            if (state == ERROR_STATE) continue;

            next_state = state;
            LOG("shift_extra");
          } else {
            next_state = action.params.state;
            LOG("shift state:%u", next_state);
          }

          if (lookahead->children.size > 0) {
            ts_parser__breakdown_lookahead(self, &lookahead, state, &self->reusable_node);
            next_state = ts_language_next_state(self->language, state, lookahead->symbol);
          }

          ts_parser__shift(self, version, next_state, lookahead, action.params.extra);
          if (did_reuse) reusable_node_advance(&self->reusable_node);
          return;
        }

        case TSParseActionTypeReduce: {
          bool is_fragile = table_entry.action_count > 1;
          LOG("reduce sym:%s, child_count:%u", SYM_NAME(action.params.symbol), action.params.child_count);
          StackSliceArray reduction = ts_parser__reduce(
            self, version, action.params.symbol, action.params.child_count,
            action.params.dynamic_precedence, action.params.alias_sequence_id,
            is_fragile
          );
          StackSlice slice = *array_front(&reduction);
          last_reduction_version = slice.version;
          break;
        }

        case TSParseActionTypeAccept: {
          LOG("accept");
          ts_parser__accept(self, version, lookahead);
          return;
        }

        case TSParseActionTypeRecover: {
          if (lookahead->children.size > 0) {
            ts_parser__breakdown_lookahead(self, &lookahead, ERROR_STATE, &self->reusable_node);
          }

          ts_parser__recover(self, version, lookahead);
          if (did_reuse) reusable_node_advance(&self->reusable_node);
          return;
        }
      }
    }

    if (last_reduction_version != STACK_VERSION_NONE) {
      ts_stack_renumber_version(self->stack, last_reduction_version, version);
      LOG_STACK();
      state = ts_stack_state(self->stack, version);
      ts_language_table_entry(self->language, state, lookahead->first_leaf.symbol, &table_entry);
      continue;
    }

    if (lookahead->is_keyword && lookahead->symbol != self->language->keyword_capture_token) {
      ts_language_table_entry(self->language, state, self->language->keyword_capture_token, &table_entry);
      if (table_entry.action_count > 0) {
        LOG(
          "switch from_keyword:%s, to_word_token:%s",
          SYM_NAME(lookahead->symbol),
          SYM_NAME(self->language->keyword_capture_token)
        );

        Subtree *mutable_lookahead = ts_subtree_make_mut(&self->tree_pool, lookahead);
        mutable_lookahead->symbol = self->language->keyword_capture_token;
        mutable_lookahead->first_leaf.symbol = self->language->keyword_capture_token;
        lookahead = mutable_lookahead;
        continue;
      }
    }

    if (state == ERROR_STATE) {
      ts_parser__recover(self, version, lookahead);
      return;
    }

    if (ts_parser__breakdown_top_of_stack(self, version)) {
      continue;
    }

    LOG("detect_error");
    ts_stack_pause(self->stack, version, lookahead->first_leaf.symbol);
    ts_subtree_release(&self->tree_pool, lookahead);
    return;
  }
}

static unsigned ts_parser__condense_stack(TSParser *self) {
  bool made_changes = false;
  unsigned min_error_cost = UINT_MAX;
  for (StackVersion i = 0; i < ts_stack_version_count(self->stack); i++) {
    if (ts_stack_is_halted(self->stack, i)) {
      ts_stack_remove_version(self->stack, i);
      i--;
      continue;
    }

    ErrorStatus status_i = ts_parser__version_status(self, i);
    if (!status_i.is_in_error && status_i.cost < min_error_cost) {
      min_error_cost = status_i.cost;
    }

    for (StackVersion j = 0; j < i; j++) {
      ErrorStatus status_j = ts_parser__version_status(self, j);

      switch (ts_parser__compare_versions(self, status_j, status_i)) {
        case ErrorComparisonTakeLeft:
          made_changes = true;
          ts_stack_remove_version(self->stack, i);
          i--;
          j = i;
          break;
        case ErrorComparisonPreferLeft:
        case ErrorComparisonNone:
          if (ts_stack_merge(self->stack, j, i)) {
            made_changes = true;
            i--;
            j = i;
          }
          break;
        case ErrorComparisonPreferRight:
          made_changes = true;
          if (ts_stack_merge(self->stack, j, i)) {
            i--;
            j = i;
          } else {
            ts_stack_swap_versions(self->stack, i, j);
          }
          break;
        case ErrorComparisonTakeRight:
          made_changes = true;
          ts_stack_remove_version(self->stack, j);
          i--;
          j--;
          break;
      }
    }
  }

  while (ts_stack_version_count(self->stack) > MAX_VERSION_COUNT) {
    ts_stack_remove_version(self->stack, MAX_VERSION_COUNT);
    made_changes = true;
  }

  if (ts_stack_version_count(self->stack) > 0) {
    bool has_unpaused_version = false;
    for (StackVersion i = 0, n = ts_stack_version_count(self->stack); i < n; i++) {
      if (ts_stack_is_paused(self->stack, i)) {
        if (!has_unpaused_version && self->accept_count < MAX_VERSION_COUNT) {
          LOG("resume version:%u", i);
          min_error_cost = ts_stack_error_cost(self->stack, i);
          TSSymbol lookahead_symbol = ts_stack_resume(self->stack, i);
          ts_parser__handle_error(self, i, lookahead_symbol);
          has_unpaused_version = true;
        } else {
          ts_stack_remove_version(self->stack, i);
          i--;
          n--;
        }
      } else {
        has_unpaused_version = true;
      }
    }
  }

  if (made_changes) {
    LOG("condense");
    LOG_STACK();
  }

  return min_error_cost;
}

static bool ts_parser_has_outstanding_parse(TSParser *self) {
  return (
    self->lexer.current_position.bytes > 0 ||
    ts_stack_state(self->stack, 0) != 1
  );
}

// Parser - Public

TSParser *ts_parser_new() {
  TSParser *self = ts_calloc(1, sizeof(TSParser));
  ts_lexer_init(&self->lexer);
  array_init(&self->reduce_actions);
  array_reserve(&self->reduce_actions, 4);
  self->tree_pool = ts_subtree_pool_new(32);
  self->stack = ts_stack_new(&self->tree_pool);
  self->finished_tree = NULL;
  self->reusable_node = reusable_node_new();
  self->dot_graph_file = NULL;
  self->halt_on_error = false;
  self->enabled = true;
  self->operation_limit = SIZE_MAX;
  self->old_tree = NULL;
  ts_parser__set_cached_token(self, 0, NULL, NULL);
  return self;
}

void ts_parser_delete(TSParser *self) {
  ts_stack_delete(self->stack);
  if (self->reduce_actions.contents) {
    array_delete(&self->reduce_actions);
  }
  if (self->old_tree) {
    ts_subtree_release(&self->tree_pool, self->old_tree);
    self->old_tree = NULL;
  }
  ts_lexer_delete(&self->lexer);
  ts_parser__set_cached_token(self, 0, NULL, NULL);
  ts_subtree_pool_delete(&self->tree_pool);
  reusable_node_delete(&self->reusable_node);
  ts_parser_set_language(self, NULL);
  ts_free(self);
}

const TSLanguage *ts_parser_language(const TSParser *self) {
  return self->language;
}

bool ts_parser_set_language(TSParser *self, const TSLanguage *language) {
  if (language && language->version != TREE_SITTER_LANGUAGE_VERSION) return false;

  if (self->external_scanner_payload && self->language->external_scanner.destroy) {
    self->language->external_scanner.destroy(self->external_scanner_payload);
  }

  if (language && language->external_scanner.create) {
    self->external_scanner_payload = language->external_scanner.create();
  } else {
    self->external_scanner_payload = NULL;
  }

  self->language = language;
  return true;
}

TSLogger ts_parser_logger(const TSParser *self) {
  return self->lexer.logger;
}

void ts_parser_set_logger(TSParser *self, TSLogger logger) {
  self->lexer.logger = logger;
}

void ts_parser_print_dot_graphs(TSParser *self, FILE *file) {
  self->dot_graph_file = file;
}

void ts_parser_halt_on_error(TSParser *self, bool should_halt_on_error) {
  self->halt_on_error = should_halt_on_error;
}

bool ts_parser_enabled(const TSParser *self) {
  return self->enabled;
}

void ts_parser_set_enabled(TSParser *self, bool enabled) {
  self->enabled = enabled;
}

size_t ts_parser_operation_limit(const TSParser *self) {
  return self->operation_limit;
}

void ts_parser_set_operation_limit(TSParser *self, size_t limit) {
  self->operation_limit = limit;
}

void ts_parser_set_included_ranges(TSParser *self, const TSRange *ranges, uint32_t count) {
  ts_lexer_set_included_ranges(&self->lexer, ranges, count);
}

const TSRange *ts_parser_included_ranges(const TSParser *self, uint32_t *count) {
  return ts_lexer_included_ranges(&self->lexer, count);
}

void ts_parser_reset(TSParser *self) {
  if (self->language->external_scanner.deserialize) {
    self->language->external_scanner.deserialize(self->external_scanner_payload, NULL, 0);
  }

  if (self->old_tree) {
    ts_subtree_release(&self->tree_pool, self->old_tree);
    self->old_tree = NULL;
  }

  reusable_node_clear(&self->reusable_node);
  ts_lexer_reset(&self->lexer, length_zero());
  ts_stack_clear(self->stack);
  ts_parser__set_cached_token(self, 0, NULL, NULL);
  if (self->finished_tree) {
    ts_subtree_release(&self->tree_pool, self->finished_tree);
    self->finished_tree = NULL;
  }
  self->accept_count = 0;
}

TSTree *ts_parser_parse(TSParser *self, const TSTree *old_tree, TSInput input) {
  if (!self->language || !input.read) return NULL;

  ts_lexer_set_input(&self->lexer, input);

  if (ts_parser_has_outstanding_parse(self)) {
    LOG("resume_parsing");
  } else if (old_tree) {
    ts_subtree_retain(old_tree->root);
    self->old_tree = old_tree->root;
    reusable_node_reset(&self->reusable_node, old_tree->root);
    LOG("parse_after_edit");
  } else {
    reusable_node_clear(&self->reusable_node);
    LOG("new_parse");
  }

  uint32_t position = 0, last_position = 0, version_count = 0;
  size_t operation_count = 0;

  do {
    for (StackVersion version = 0;
         version_count = ts_stack_version_count(self->stack), version < version_count;
         version++) {
      if (operation_count > self->operation_limit || !self->enabled) return NULL;
      operation_count++;

      bool allow_node_reuse = version_count == 1;
      while (ts_stack_is_active(self->stack, version)) {
        LOG("process version:%d, version_count:%u, state:%d, row:%u, col:%u",
            version, ts_stack_version_count(self->stack),
            ts_stack_state(self->stack, version),
            ts_stack_position(self->stack, version).extent.row,
            ts_stack_position(self->stack, version).extent.column);

        ts_parser__advance(self, version, allow_node_reuse);
        LOG_STACK();

        position = ts_stack_position(self->stack, version).bytes;
        if (position > last_position || (version > 0 && position == last_position)) {
          last_position = position;
          break;
        }
      }
    }

    unsigned min_error_cost = ts_parser__condense_stack(self);
    if (self->finished_tree && self->finished_tree->error_cost < min_error_cost) {
      break;
    } else if (self->halt_on_error && min_error_cost > 0) {
      ts_parser__halt_parse(self);
      break;
    }
  } while (version_count != 0);

  ts_subtree_balance(self->finished_tree, &self->tree_pool, self->language);
  LOG("done");
  LOG_TREE();

  TSTree *result = ts_tree_new(self->finished_tree, self->language);
  self->finished_tree = NULL;
  ts_parser_reset(self);
  return result;
}

TSTree *ts_parser_parse_string(TSParser *self, const TSTree *old_tree,
                               const char *string, uint32_t length) {
  TSStringInput input = {string, length};
  return ts_parser_parse(self, old_tree, (TSInput) {
    &input,
    ts_string_input_read,
    TSInputEncodingUTF8,
  });
}
