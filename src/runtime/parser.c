#include "runtime/parser.h"
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include "tree_sitter/runtime.h"
#include "tree_sitter/parser.h"
#include "runtime/tree.h"
#include "runtime/lexer.h"
#include "runtime/length.h"
#include "runtime/array.h"
#include "runtime/language.h"
#include "runtime/alloc.h"

/*
 *  Debugging
 */

#define LOG(...)                                                               \
  if (self->lexer.debugger.debug_fn) {                                         \
    snprintf(self->lexer.debug_buffer, TS_DEBUG_BUFFER_SIZE, __VA_ARGS__);     \
    self->lexer.debugger.debug_fn(self->lexer.debugger.payload,                \
                                  TSDebugTypeParse, self->lexer.debug_buffer); \
  }

#define LOG_ACTION(...)                   \
  LOG(__VA_ARGS__);                       \
  if (self->print_debugging_graphs) {     \
    fprintf(stderr, "graph {\nlabel=\""); \
    fprintf(stderr, __VA_ARGS__);         \
    fprintf(stderr, "\"\n}\n\n");         \
  }

#define LOG_STACK()                                                  \
  if (self->print_debugging_graphs) {                                \
    char *graph_string =                                             \
      ts_stack_dot_graph(self->stack, self->language->symbol_names); \
    fputs(graph_string, stderr);                                     \
    fputs("\n\n", stderr);                                           \
    ts_free(graph_string);                                           \
  }

#define SYM_NAME(symbol) ts_language_symbol_name(self->language, symbol)

#define BOOL_STRING(value) (value ? "true" : "false")

struct LookaheadState {
  TSTree *reusable_subtree;
  size_t reusable_subtree_pos;
  bool is_verifying;
};

struct ErrorRepair {
  TSParseAction action;
  TSStateId next_state;
  size_t in_progress_state_count;
};

typedef struct {
  ErrorRepairArray *repairs;
  size_t count_above_error;
  int best_repair_index;
  TSParser *parser;
  TSSymbol lookahead_symbol;
} ErrorRepairSession;

typedef enum {
  ParseActionFailed,
  ParseActionUpdated,
  ParseActionRemoved,
} ParseActionResult;

typedef struct {
  enum {
    ReduceFailed,
    ReduceSucceeded,
    ReduceMerged,
    ReduceStoppedAtError,
  } status;

  StackSlice partial_slice;
} ReduceResult;

typedef enum {
  RepairFailed,
  RepairSucceeded,
  RepairMerged,
  RepairNoneFound,
} RepairResult;

/*
 *  Private
 */

static StackSlice ts_parser__pop_one(TSParser *self, int head_index, int count) {
  StackPopResult pop = ts_stack_pop_count(self->stack, head_index, count);
  if (pop.status != StackPopSucceeded)
    return (StackSlice){
      .head_index = -1,
      .trees = array_new(),
    };
  assert(pop.slices.size > 0);
  assert(pop.slices.contents[0].head_index == head_index);
  for (size_t i = pop.slices.size - 1; i > 0; i--) {
    ts_tree_array_delete(&pop.slices.contents[i].trees);
    ts_stack_remove_head(self->stack, pop.slices.contents[i].head_index);
  }
  return pop.slices.contents[0];
}

static ParseActionResult ts_parser__breakdown_top_of_stack(TSParser *self,
                                                           int head) {
  TSTree *last_child = NULL;

  do {
    StackPopResult pop = ts_stack_pop_count(self->stack, head, 1);
    if (!pop.slices.size)
      return ParseActionFailed;
    assert(pop.slices.size > 0);

    /*
     *  Since only one entry (not counting extra trees) is being popped from the
     *  stack, there should only be one possible array of removed trees.
     */

    for (size_t i = 0; i < pop.slices.size; i++) {
      StackSlice slice = pop.slices.contents[i];
      TreeArray removed_trees = slice.trees;
      TSTree *parent = *array_front(&removed_trees);
      int head_index = slice.head_index;
      LOG("breakdown_pop sym:%s, size:%lu", SYM_NAME(parent->symbol),
          ts_tree_total_size(parent).chars);

      StackPushResult last_push = StackPushContinued;
      TSStateId state = ts_stack_top_state(self->stack, head_index);
      for (size_t j = 0; j < parent->child_count; j++) {
        last_child = parent->children[j];
        if (last_child->symbol == ts_builtin_sym_error) {
          state = ts_parse_state_error;
        } else if (!last_child->extra) {
          TSParseAction action =
            ts_language_last_action(self->language, state, last_child->symbol);
          assert(action.type == TSParseActionTypeShift);
          state = action.data.to_state;
        }

        LOG("breakdown_push sym:%s, size:%lu", SYM_NAME(last_child->symbol),
            ts_tree_total_size(last_child).chars);

        last_push = ts_stack_push(self->stack, head_index, last_child, state);
        if (last_push == StackPushFailed)
          goto error;
      }

      for (size_t j = 1, count = slice.trees.size; j < count; j++) {
        TSTree *tree = slice.trees.contents[j];
        last_push = ts_stack_push(self->stack, head_index, tree, state);
        if (last_push == StackPushFailed)
          goto error;
      }

      if (i == 0)
        assert(last_push != StackPushMerged);
      else
        assert(last_push == StackPushMerged);

      for (size_t j = 0, count = removed_trees.size; j < count; j++)
        ts_tree_release(removed_trees.contents[j]);
      array_delete(&removed_trees);
    }
  } while (last_child && last_child->child_count > 0);

  return ParseActionUpdated;

error:
  return ParseActionFailed;
}

static void ts_parser__pop_reusable_subtree(LookaheadState *state);

/*
 *  Replace the parser's reusable_subtree with its first non-fragile descendant.
 *  Return true if a suitable descendant is found, false otherwise.
 */
static void ts_parser__breakdown_reusable_subtree(LookaheadState *state) {
  do {
    if (state->reusable_subtree->symbol == ts_builtin_sym_error) {
      ts_parser__pop_reusable_subtree(state);
      return;
    }

    if (state->reusable_subtree->child_count == 0) {
      ts_parser__pop_reusable_subtree(state);
      return;
    }

    state->reusable_subtree = state->reusable_subtree->children[0];
  } while (ts_tree_is_fragile(state->reusable_subtree));
}

/*
 *  Replace the parser's reusable_subtree with its largest right neighbor, or
 *  NULL if no right neighbor exists.
 */
static void ts_parser__pop_reusable_subtree(LookaheadState *state) {
  state->reusable_subtree_pos += ts_tree_total_chars(state->reusable_subtree);

  while (state->reusable_subtree) {
    TSTree *parent = state->reusable_subtree->context.parent;
    size_t next_index = state->reusable_subtree->context.index + 1;
    if (parent && parent->child_count > next_index) {
      state->reusable_subtree = parent->children[next_index];
      return;
    }
    state->reusable_subtree = parent;
  }
}

static bool ts_parser__can_reuse(TSParser *self, int head, TSTree *subtree) {
  if (subtree->symbol == ts_builtin_sym_error)
    return false;
  if (ts_tree_is_fragile(subtree)) {
    if (subtree->parse_state != ts_stack_top_state(self->stack, head))
      return false;
  }

  TSStateId state = ts_stack_top_state(self->stack, head);

  if (subtree->lex_state != TS_TREE_STATE_INDEPENDENT) {
    TSStateId lex_state = self->language->lex_states[state];
    if (subtree->lex_state != lex_state)
      return false;
  }

  const TSParseAction action =
    ts_language_last_action(self->language, state, subtree->symbol);
  if (action.type == TSParseActionTypeError || action.can_hide_split)
    return false;

  if (subtree->extra && !action.extra)
    return false;

  return true;
}

/*
 *  Advance the parser's lookahead subtree. If there is a reusable subtree
 *  at the correct position in the parser's previous tree, use that. Otherwise,
 *  run the lexer.
 */
static TSTree *ts_parser__get_next_lookahead(TSParser *self, int head) {
  LookaheadState *state = array_get(&self->lookahead_states, head);
  TSLength position = ts_stack_top_position(self->stack, head);

  while (state->reusable_subtree) {
    if (state->reusable_subtree_pos > position.chars) {
      break;
    }

    if (state->reusable_subtree_pos < position.chars) {
      LOG("past_reusable sym:%s", SYM_NAME(state->reusable_subtree->symbol));
      ts_parser__pop_reusable_subtree(state);
      continue;
    }

    if (state->reusable_subtree->has_changes) {
      if (state->is_verifying && state->reusable_subtree->child_count == 0) {
        ts_parser__breakdown_top_of_stack(self, head);
        state->is_verifying = false;
      }

      LOG("breakdown_changed sym:%s", SYM_NAME(state->reusable_subtree->symbol));
      ts_parser__breakdown_reusable_subtree(state);
      continue;
    }

    if (!ts_parser__can_reuse(self, head, state->reusable_subtree)) {
      LOG("breakdown_unreusable sym:%s",
          SYM_NAME(state->reusable_subtree->symbol));
      ts_parser__breakdown_reusable_subtree(state);
      continue;
    }

    TSTree *result = state->reusable_subtree;
    TSLength size = ts_tree_total_size(result);
    LOG("reuse sym:%s size:%lu extra:%d", SYM_NAME(result->symbol), size.chars,
        result->extra);
    ts_parser__pop_reusable_subtree(state);
    ts_tree_retain(result);
    return result;
  }

  ts_lexer_reset(&self->lexer, position);
  TSStateId parse_state = ts_stack_top_state(self->stack, head);
  TSStateId lex_state = self->language->lex_states[parse_state];
  LOG("lex state:%d", lex_state);
  return self->language->lex_fn(&self->lexer, lex_state, false);
}

static int ts_parser__split(TSParser *self, int head) {
  int result = ts_stack_split(self->stack, head);
  assert(result == (int)self->lookahead_states.size);
  LookaheadState lookahead_state = *array_get(&self->lookahead_states, head);
  array_push(&self->lookahead_states, lookahead_state);
  return result;
}

static void ts_parser__remove_head(TSParser *self, int head) {
  assert(self->lookahead_states.size == ts_stack_head_count(self->stack));
  array_erase(&self->lookahead_states, head);
  ts_stack_remove_head(self->stack, head);
}

static int ts_parser__select_tree(void *data, TSTree *left, TSTree *right) {
  if (!left || left->symbol == ts_builtin_sym_error)
    return 1;
  if (!right || right->symbol == ts_builtin_sym_error)
    return -1;

  TSParser *self = data;
  int comparison = ts_tree_compare(left, right);
  switch (comparison) {
    case -1:
      LOG_ACTION("select tree:%s, over_tree:%s", SYM_NAME(left->symbol),
                 SYM_NAME(right->symbol));
      break;
    case 1:
      LOG_ACTION("select tree:%s, over_tree:%s", SYM_NAME(right->symbol),
                 SYM_NAME(left->symbol));
      break;
  }

  return comparison;
}

/*
 *  Parse Actions
 */

static ParseActionResult ts_parser__shift(TSParser *self, int head,
                                          TSStateId parse_state,
                                          TSTree *lookahead) {
  switch (ts_stack_push(self->stack, head, lookahead, parse_state)) {
    case StackPushFailed:
      return ParseActionFailed;
    case StackPushMerged:
      LOG("merge head:%d", head);
      array_erase(&self->lookahead_states, head);
      return ParseActionRemoved;
    default:
      return ParseActionUpdated;
  }
}

static ParseActionResult ts_parser__shift_extra(TSParser *self, int head,
                                                TSStateId state,
                                                TSTree *lookahead) {
  TSSymbolMetadata metadata = self->language->symbol_metadata[lookahead->symbol];
  if (metadata.structural && ts_stack_head_count(self->stack) > 1) {
    TSTree *copy = ts_tree_make_copy(lookahead);
    if (!copy)
      return ParseActionFailed;
    copy->extra = true;
    ParseActionResult result = ts_parser__shift(self, head, state, copy);
    ts_tree_release(copy);
    return result;
  } else {
    lookahead->extra = true;
    return ts_parser__shift(self, head, state, lookahead);
  }
}

static ReduceResult ts_parser__reduce(TSParser *self, int head, TSSymbol symbol,
                                      int child_count, bool extra, bool fragile) {
  TSSymbolMetadata metadata =
    ts_language_symbol_metadata(self->language, symbol);
  LookaheadState lookahead_state = *array_get(&self->lookahead_states, head);
  StackPopResult pop = ts_stack_pop_count(self->stack, head, child_count);
  if (!pop.slices.size)
    goto error;
  if (pop.status == StackPopStoppedAtError)
    return (ReduceResult){
      .status = ReduceStoppedAtError, .partial_slice = pop.slices.contents[0],
    };

  size_t removed_heads = 0;

  for (size_t i = 0; i < pop.slices.size; i++) {
    StackSlice slice = pop.slices.contents[i];

    size_t trailing_extra_count = 0;
    for (size_t j = slice.trees.size - 1; j + 1 > 0; j--) {
      if (slice.trees.contents[j]->extra)
        trailing_extra_count++;
      else
        break;
    }

    size_t popped_child_count = slice.trees.size - trailing_extra_count;
    TSTree *parent = ts_tree_make_node(symbol, popped_child_count,
                                       slice.trees.contents, metadata);
    if (!parent) {
      ts_tree_array_delete(&slice.trees);
      goto error;
    }

    if (fragile || self->is_split || ts_stack_head_count(self->stack) > 1) {
      parent->fragile_left = true;
      parent->fragile_right = true;
      parent->parse_state = TS_TREE_STATE_ERROR;
    }

    int new_head = slice.head_index - removed_heads;

    if (i > 0) {
      if (symbol == ts_builtin_sym_error) {
        removed_heads++;
        ts_stack_remove_head(self->stack, new_head);
        continue;
      }

      LOG("split_during_reduce new_head:%d", new_head);
      if (!array_push(&self->lookahead_states, lookahead_state))
        goto error;
    }

    /*
     *  If the parent node is extra, then do not change the state when pushing
     *  it. Otherwise, proceed to the state given in the parse table for the
     *  new parent symbol.
     */
    TSStateId state;
    TSStateId top_state = ts_stack_top_state(self->stack, new_head);
    if (parent->parse_state != TS_TREE_STATE_ERROR)
      parent->parse_state = top_state;
    if (extra) {
      parent->extra = true;
      state = top_state;
    } else {
      TSParseAction action =
        ts_language_last_action(self->language, top_state, symbol);
      if (child_count == -1) {
        state = 0;
      } else {
        assert(action.type == TSParseActionTypeShift);
        state = action.data.to_state;
      }
    }

    StackPushResult push = ts_stack_push(self->stack, new_head, parent, state);
    ts_tree_release(parent);
    switch (push) {
      case StackPushFailed:
        goto error;
      case StackPushMerged:
        LOG("merge_during_reduce head:%d", new_head);
        array_erase(&self->lookahead_states, new_head);
        removed_heads++;
        continue;
      case StackPushContinued:
        break;
    }

    if (trailing_extra_count > 0) {
      for (size_t j = 0; j < trailing_extra_count; j++) {
        size_t index = slice.trees.size - trailing_extra_count + j;
        TSTree *tree = slice.trees.contents[index];
        StackPushResult push = ts_stack_push(self->stack, new_head, tree, state);
        ts_tree_release(tree);
        switch (push) {
          case StackPushFailed:
            goto error;
          case StackPushMerged:
            array_erase(&self->lookahead_states, new_head);
            removed_heads++;
            break;
          case StackPushContinued:
            break;
        }
      }
    }
  }

  if (removed_heads < pop.slices.size)
    return (ReduceResult){.status = ReduceSucceeded };
  else
    return (ReduceResult){.status = ReduceMerged };

error:
  return (ReduceResult){.status = ReduceFailed };
}

static StackIterateAction ts_parser__error_repair_callback(void *payload,
                                                           TSStateId state,
                                                           size_t tree_count,
                                                           bool is_done) {
  ErrorRepairSession *session = (ErrorRepairSession *)payload;
  const TSParser *self = session->parser;
  size_t count_above_error = session->count_above_error;
  TSSymbol lookahead_symbol = session->lookahead_symbol;

  if (session->best_repair_index >= 0)
    return StackIterateAbort;

  for (size_t i = 0; i < session->repairs->size; i++) {
    ErrorRepair *repair = &session->repairs->contents[i];
    TSSymbol symbol = repair->action.data.symbol;
    size_t child_count = repair->action.data.child_count;

    if (tree_count + count_above_error >= child_count &&
        repair->in_progress_state_count > 0) {
      TSParseAction new_action =
        ts_language_last_action(self->language, state, symbol);
      if (new_action.type == TSParseActionTypeShift) {
        repair->next_state = new_action.data.to_state;
        if (ts_language_has_action(self->language, repair->next_state,
                                   lookahead_symbol)) {
          session->best_repair_index = i;
          return StackIteratePop;
        }
      }
    }

    if (ts_language_symbol_is_in_progress(self->language, state, symbol))
      repair->in_progress_state_count++;
  }

  return StackIterateContinue;
}

static RepairResult ts_parser__repair_error(TSParser *self, int head_index,
                                            StackSlice partial_slice,
                                            TSTree *lookahead,
                                            const TSParseAction *actions,
                                            size_t action_count) {
  ErrorRepairSession session = {
    .count_above_error = 0,
    .best_repair_index = -1,
    .repairs = &self->error_repairs,
    .lookahead_symbol = lookahead->symbol,
    .parser = self,
  };

  for (size_t i = 0; i < partial_slice.trees.size; i++)
    if (!partial_slice.trees.contents[i]->extra)
      session.count_above_error++;

  array_clear(&self->error_repairs);
  for (size_t i = 0; i < action_count; i++)
    if (actions[i].type == TSParseActionTypeReduce &&
        actions[i].data.child_count > session.count_above_error)
      array_push(&self->error_repairs,
                 ((ErrorRepair){
                   .action = actions[i], .in_progress_state_count = 0,
                 }));

  StackPopResult result = ts_stack_pop_until(
    self->stack, head_index, ts_parser__error_repair_callback, &session);
  if (!result.slices.size) {
    ts_tree_array_delete(&partial_slice.trees);
    return RepairNoneFound;
  }

  ErrorRepair repair = self->error_repairs.contents[session.best_repair_index];
  size_t count_needed_below =
    repair.action.data.child_count - session.count_above_error;
  TreeArray children_below = result.slices.contents[0].trees;
  size_t count_skipped_below = children_below.size - count_needed_below;
  TSSymbol symbol = repair.action.data.symbol;

  LOG_ACTION(
    "repair_found sym:%s, child_count:%d, match_count:%lu, skipped:%lu",
    SYM_NAME(symbol), repair.action.data.child_count,
    repair.in_progress_state_count, count_skipped_below);

  if (count_skipped_below > 1) {
    TreeArray skipped_children = array_new();
    if (!array_grow(&skipped_children, count_skipped_below))
      goto error;
    for (size_t i = count_needed_below; i < children_below.size; i++)
      array_push(&skipped_children, children_below.contents[i]);
    TSTree *error = ts_tree_make_node(
      ts_builtin_sym_error, skipped_children.size, skipped_children.contents,
      ts_language_symbol_metadata(self->language, ts_builtin_sym_error));
    error->extra = true;
    children_below.size = count_needed_below;
    array_push(&children_below, error);
  }

  for (size_t i = 0; i < partial_slice.trees.size; i++)
    array_push(&children_below, partial_slice.trees.contents[i]);
  array_delete(&partial_slice);
  TSTree *parent =
    ts_tree_make_node(symbol, children_below.size, children_below.contents,
                      ts_language_symbol_metadata(self->language, symbol));

  StackPushResult push_result =
    ts_stack_push(self->stack, head_index, parent, repair.next_state);
  ts_tree_release(parent);
  switch (push_result) {
    case StackPushFailed:
      return RepairFailed;
    case StackPushMerged:
      array_erase(&self->lookahead_states, head_index);
      return RepairMerged;
    default:
      return RepairSucceeded;
  }

error:
  return RepairFailed;
}

static ParseActionResult ts_parser__start(TSParser *self, TSInput input,
                                          TSTree *previous_tree) {
  if (previous_tree) {
    LOG("parse_after_edit");
  } else {
    LOG("new_parse");
  }

  ts_lexer_set_input(&self->lexer, input);
  ts_stack_clear(self->stack);
  ts_stack_set_tree_selection_callback(self->stack, self,
                                       ts_parser__select_tree);

  LookaheadState lookahead_state = {
    .reusable_subtree = previous_tree,
    .reusable_subtree_pos = 0,
    .is_verifying = false,
  };
  array_clear(&self->lookahead_states);
  array_push(&self->lookahead_states, lookahead_state);
  self->finished_tree = NULL;
  return ParseActionUpdated;
}

static ParseActionResult ts_parser__accept(TSParser *self, int head) {
  StackPopResult pop = ts_stack_pop_count(self->stack, head, -1);
  if (!pop.slices.size)
    goto error;

  for (size_t j = 0; j < pop.slices.size; j++) {
    StackSlice slice = pop.slices.contents[j];
    TreeArray trees = slice.trees;

    for (size_t i = trees.size - 1; i + 1 > 0; i--) {
      if (!trees.contents[i]->extra) {
        TSTree *root = trees.contents[i];
        if (!array_splice(&trees, i, 1, root->child_count, root->children))
          goto error;
        ts_tree_set_children(root, trees.size, trees.contents);
        if (!trees.size)
          array_delete(&trees);

        ts_parser__remove_head(self, slice.head_index);
        int comparison = ts_parser__select_tree(self, self->finished_tree, root);
        if (comparison > 0) {
          ts_tree_release(self->finished_tree);
          self->finished_tree = root;
        } else {
          ts_tree_release(root);
        }

        break;
      }
    }
  }

  return ParseActionRemoved;

error:
  if (pop.slices.size) {
    StackSlice slice = *array_front(&pop.slices);
    for (size_t i = 0; i < slice.trees.size; i++)
      ts_tree_release(slice.trees.contents[i]);
    array_delete(&slice.trees);
  }
  return ParseActionFailed;
}

static ParseActionResult ts_parser__handle_error(TSParser *self, int head,
                                                 TSTree *lookahead) {
  TSTree *next_lookahead = self->language->lex_fn(&self->lexer, 0, true);
  lookahead->size = ts_length_add(lookahead->size, next_lookahead->padding);
  next_lookahead->padding = ts_length_zero();

  if (!ts_parser__shift(self, head, ts_parse_state_error, lookahead))
    goto error;

  while (
    ts_language_symbol_metadata(self->language, next_lookahead->symbol).extra) {
    if (!ts_parser__shift_extra(self, head, ts_parse_state_error, next_lookahead))
      goto error;
    ts_tree_release(next_lookahead);
    next_lookahead = self->language->lex_fn(&self->lexer, 0, true);
  }

  if (next_lookahead->symbol == ts_builtin_sym_end) {
    StackSlice result = ts_parser__pop_one(self, head, -1);
    TSTree *error = ts_tree_make_node(
      ts_builtin_sym_error, result.trees.size, result.trees.contents,
      ts_language_symbol_metadata(self->language, ts_builtin_sym_error));
    TreeArray children = array_new();
    if (!array_push(&children, error))
      goto error;
    TSTree *parent = ts_tree_make_node(
      ts_builtin_sym_start, children.size, children.contents,
      ts_language_symbol_metadata(self->language, ts_builtin_sym_start));
    ts_stack_push(self->stack, head, parent, 0);
    ts_tree_release(parent);
    ts_tree_release(next_lookahead);
    return ts_parser__accept(self, head);
  }

  TSParseAction action = ts_language_last_action(
    self->language, ts_parse_state_error, next_lookahead->symbol);
  assert(action.type == TSParseActionTypeShift);

  LOG("resume_without_context state:%d", action.data.to_state);
  ParseActionResult result =
    ts_parser__shift(self, head, action.data.to_state, next_lookahead);
  ts_tree_release(next_lookahead);
  return result;

error:
  ts_tree_release(next_lookahead);
  return ParseActionFailed;
}

/*
 * Continue performing parse actions for the given head until the current
 * lookahead symbol is consumed.
 */

static ParseActionResult ts_parser__consume_lookahead(TSParser *self, int head,
                                                      TSTree *lookahead) {
  for (;;) {
    TSStateId state = ts_stack_top_state(self->stack, head);
    size_t action_count;
    const TSParseAction *actions = ts_language_actions(
      self->language, state, lookahead->symbol, &action_count);

    /*
     * If there are multiple actions for the current state and lookahead symbol,
     * split the stack so that each one can be performed. If there is a `SHIFT`
     * action, it will always appear *last* in the list of actions. Perform it
     * on the original stack head and return.
     */
    bool repaired_error = false;
    size_t child_count_above_error = -1;
    for (size_t i = 0; i < action_count; i++) {
      TSParseAction action = actions[i];

      bool should_skip = repaired_error &&
        action.type == TSParseActionTypeReduce &&
        action.data.child_count > child_count_above_error;

      int current_head;
      if (i == action_count - 1) {
        if (should_skip)
          action.type = TSParseActionTypeError;
        current_head = head;
      } else {
        if (should_skip)
          continue;
        current_head = ts_parser__split(self, head);
        LOG_ACTION("split_action from_head:%d, new_head:%d", head, current_head);
      }

      LOG_STACK();

      LookaheadState *lookahead_state =
        array_get(&self->lookahead_states, current_head);

      switch (action.type) {
        case TSParseActionTypeError:
          if (lookahead_state->is_verifying) {
            ts_parser__breakdown_top_of_stack(self, current_head);
            lookahead_state->is_verifying = false;
            return ParseActionRemoved;
          }

          if (ts_stack_head_count(self->stack) == 1) {
            LOG_ACTION("handle_error %s", SYM_NAME(lookahead->symbol));
            return ts_parser__handle_error(self, current_head, lookahead);
          } else {
            LOG_ACTION("bail current_head:%d", current_head);
            ts_parser__remove_head(self, current_head);
            return ParseActionRemoved;
          }

        case TSParseActionTypeShift:
          if (action.extra) {
            LOG_ACTION("shift_extra");
            return ts_parser__shift_extra(self, current_head, state, lookahead);
          } else {
            LOG_ACTION("shift state:%u", action.data.to_state);
            lookahead_state->is_verifying = (lookahead->child_count > 0);
            TSStateId state = action.data.to_state;
            return ts_parser__shift(self, current_head, state, lookahead);
          }

        case TSParseActionTypeReduce:
          lookahead_state->is_verifying = false;

          if (action.extra) {
            LOG_ACTION("reduce_extra sym:%s", SYM_NAME(action.data.symbol));
            ts_parser__reduce(self, current_head, action.data.symbol, 1, true,
                              false);
          } else {
            LOG_ACTION("reduce sym:%s, child_count:%u, fragile:%s",
                       SYM_NAME(action.data.symbol), action.data.child_count,
                       BOOL_STRING(action.fragile));
            assert(self->lookahead_states.size ==
                   ts_stack_head_count(self->stack));
            ReduceResult result =
              ts_parser__reduce(self, current_head, action.data.symbol,
                                action.data.child_count, false, action.fragile);
            switch (result.status) {
              case ReduceFailed:
                return ParseActionFailed;
              case ReduceMerged:
                if (current_head == head)
                  return ParseActionRemoved;
                break;
              case ReduceSucceeded:
                break;
              case ReduceStoppedAtError:
                repaired_error = true;
                child_count_above_error = 0;
                for (size_t j = 0; j < result.partial_slice.trees.size; j++)
                  if (!result.partial_slice.trees.contents[j]->extra)
                    child_count_above_error++;

                LOG_ACTION("repair head:%d", current_head);
                switch (ts_parser__repair_error(self, current_head,
                                                result.partial_slice, lookahead,
                                                actions, action_count)) {
                  case RepairFailed:
                    return ParseActionFailed;
                  case RepairNoneFound:
                    LOG_ACTION("repair_failed");
                    if (ts_stack_head_count(self->stack) == 1) {
                      LOG_ACTION("handle_error %s", SYM_NAME(lookahead->symbol));
                      return ts_parser__handle_error(self, current_head,
                                                     lookahead);
                    } else {
                      LOG_ACTION("bail head:%d, count:%d", current_head,
                                 ts_stack_head_count(self->stack));
                      ts_parser__remove_head(self, current_head);
                      if (current_head == head)
                        return ParseActionRemoved;
                      break;
                    }
                  case RepairMerged:
                    if (current_head == head)
                      return ParseActionRemoved;
                    break;
                  default:
                    break;
                }
                break;
            }
          }
          break;

        case TSParseActionTypeAccept:
          LOG_ACTION("accept");
          return ts_parser__accept(self, current_head);
      }
    }
  }
}

/*
 *  Public
 */

bool ts_parser_init(TSParser *self) {
  ts_lexer_init(&self->lexer);
  self->finished_tree = NULL;
  self->stack = NULL;
  array_init(&self->lookahead_states);
  array_init(&self->error_repairs);

  self->stack = ts_stack_new();
  if (!self->stack)
    goto error;

  if (!array_grow(&self->lookahead_states, 4))
    goto error;

  if (!array_grow(&self->error_repairs, 4))
    goto error;

  return true;

error:
  if (self->stack) {
    ts_stack_delete(self->stack);
    self->stack = NULL;
  }
  if (self->lookahead_states.contents)
    array_delete(&self->lookahead_states);
  if (self->error_repairs.contents)
    array_delete(&self->error_repairs);
  return false;
}

void ts_parser_destroy(TSParser *self) {
  if (self->stack)
    ts_stack_delete(self->stack);
  if (self->lookahead_states.contents)
    array_delete(&self->lookahead_states);
  if (self->error_repairs.contents)
    array_delete(&self->error_repairs);
}

TSDebugger ts_parser_debugger(const TSParser *self) {
  return self->lexer.debugger;
}

void ts_parser_set_debugger(TSParser *self, TSDebugger debugger) {
  self->lexer.debugger = debugger;
}

TSTree *ts_parser_parse(TSParser *self, TSInput input, TSTree *previous_tree) {
  ts_parser__start(self, input, previous_tree);
  size_t max_position = 0;

  for (;;) {
    TSTree *lookahead = NULL;
    size_t last_position, position = 0;

    self->is_split = ts_stack_head_count(self->stack) > 1;

    for (int head = 0; head < ts_stack_head_count(self->stack);) {
      for (bool removed = false; !removed;) {
        last_position = position;
        size_t new_position = ts_stack_top_position(self->stack, head).chars;

        if (new_position > max_position) {
          max_position = new_position;
          head++;
          break;
        } else if (new_position == max_position && head > 0) {
          head++;
          break;
        }

        position = new_position;

        LOG_ACTION("process head:%d, head_count:%d, state:%d, pos:%lu", head,
                   ts_stack_head_count(self->stack),
                   ts_stack_top_state(self->stack, head), position);

        if (!lookahead || (position != last_position) ||
            !ts_parser__can_reuse(self, head, lookahead)) {
          ts_tree_release(lookahead);
          lookahead = ts_parser__get_next_lookahead(self, head);
          if (!lookahead)
            return NULL;
        }

        LOG_ACTION("lookahead sym:%s, size:%lu", SYM_NAME(lookahead->symbol),
                   ts_tree_total_chars(lookahead));

        switch (ts_parser__consume_lookahead(self, head, lookahead)) {
          case ParseActionFailed:
            ts_tree_release(lookahead);
            goto error;
          case ParseActionRemoved:
            removed = true;
            break;
          case ParseActionUpdated:
            break;
        }
      }
    }

    ts_tree_release(lookahead);

    if (ts_stack_head_count(self->stack) == 0) {
      ts_stack_clear(self->stack);
      ts_tree_assign_parents(self->finished_tree);
      return self->finished_tree;
    }
  }

error:
  return NULL;
}
