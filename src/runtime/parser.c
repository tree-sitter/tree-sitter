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

typedef struct {
  TSSymbol symbol;
  TSStateId next_state;
  size_t depth;
  size_t skipped_subtree_count;
  size_t in_progress_state_count;
} ErrorRepair;

typedef enum {
  UpdatedStackHead,
  RemovedStackHead,
  FailedToUpdateStackHead,
} ParseActionResult;

/*
 *  Private
 */

static StackPopResult ts_parser__pop_one(TSParser *self, int head_index, int count) {
  StackPopResultArray results = ts_stack_pop(self->stack, head_index, count, true);
  assert(results.size > 0);
  assert(results.contents[0].head_index == head_index);
  for (size_t i = 1; i < results.size; i++) {
    ts_tree_array_clear(&results.contents[i].trees);
    array_delete(&results.contents[i].trees);
    ts_stack_remove_head(self->stack, results.contents[i].head_index);
  }
  return results.contents[0];
}

static ParseActionResult ts_parser__breakdown_top_of_stack(TSParser *self,
                                                           int head) {
  TSTree *last_child = NULL;

  do {
    StackPopResultArray pop_results = ts_stack_pop(self->stack, head, 1, false);
    if (!pop_results.size)
      return FailedToUpdateStackHead;
    assert(pop_results.size > 0);

    /*
     *  Since only one entry (not counting extra trees) is being popped from the
     *  stack, there should only be one possible array of removed trees.
     */

    for (size_t i = 0; i < pop_results.size; i++) {
      StackPopResult pop_result = pop_results.contents[i];
      TreeArray removed_trees = pop_result.trees;
      TSTree *parent = *array_front(&removed_trees);
      int head_index = pop_result.head_index;
      LOG("breakdown_pop sym:%s, size:%lu", SYM_NAME(parent->symbol),
          ts_tree_total_size(parent).chars);

      StackPushResult last_push = StackPushResultContinued;
      TSStateId state = ts_stack_top_state(self->stack, head_index);
      for (size_t j = 0; j < parent->child_count; j++) {
        last_child = parent->children[j];
        if (!last_child->extra) {
          TSParseAction action =
            ts_language_last_action(self->language, state, last_child->symbol);
          assert(action.type == TSParseActionTypeShift);
          state = action.data.to_state;
        }

        LOG("breakdown_push sym:%s, size:%lu", SYM_NAME(last_child->symbol),
            ts_tree_total_size(last_child).chars);

        last_push = ts_stack_push(self->stack, head_index, last_child, state);
        if (last_push == StackPushResultFailed)
          goto error;
      }

      for (size_t j = 1, count = pop_result.trees.size; j < count; j++) {
        TSTree *tree = pop_result.trees.contents[j];
        last_push = ts_stack_push(self->stack, head_index, tree, state);
        if (last_push == StackPushResultFailed)
          goto error;
      }

      if (i == 0)
        assert(last_push != StackPushResultMerged);
      else
        assert(last_push == StackPushResultMerged);

      for (size_t j = 0, count = removed_trees.size; j < count; j++)
        ts_tree_release(removed_trees.contents[j]);
      array_delete(&removed_trees);
    }
  } while (last_child && last_child->child_count > 0);

  return UpdatedStackHead;

error:
  return FailedToUpdateStackHead;
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
    case StackPushResultFailed:
      return FailedToUpdateStackHead;
    case StackPushResultMerged:
      LOG("merge head:%d", head);
      array_erase(&self->lookahead_states, head);
      return RemovedStackHead;
    default:
      return UpdatedStackHead;
  }
}

static ParseActionResult ts_parser__shift_extra(TSParser *self, int head,
                                                TSStateId state,
                                                TSTree *lookahead) {
  TSSymbolMetadata metadata = self->language->symbol_metadata[lookahead->symbol];
  if (metadata.structural && ts_stack_head_count(self->stack) > 1) {
    TSTree *copy = ts_tree_make_copy(lookahead);
    if (!copy)
      return FailedToUpdateStackHead;
    copy->extra = true;
    ParseActionResult result = ts_parser__shift(self, head, state, copy);
    ts_tree_release(copy);
    return result;
  } else {
    lookahead->extra = true;
    return ts_parser__shift(self, head, state, lookahead);
  }
}

typedef enum {
  ReduceSucceeded,
  ReduceMerged,
  ReduceFailed,
  ReduceStoppedAtError,
} ReduceResult;

static ReduceResult ts_parser__reduce(TSParser *self, int head, TSSymbol symbol,
                                      int child_count, bool extra, bool fragile) {
  array_clear(&self->reduce_parents);
  TSSymbolMetadata metadata = ts_language_symbol_metadata(self->language, symbol);
  StackPopResultArray pop_results =
    ts_stack_pop(self->stack, head, child_count, false);
  if (!pop_results.size)
    return ReduceFailed;
  if (pop_results.contents[0].trees.size &&
      pop_results.contents[0].trees.contents[0]->symbol == ts_builtin_sym_error) {
    if (self->partial_pop.size) {
      ts_tree_array_clear(&self->partial_pop);
      array_delete(&self->partial_pop);
    }
    self->partial_pop = pop_results.contents[0].trees;
    for (size_t i = 1; i < pop_results.size; i++) {
      ts_tree_array_clear(&pop_results.contents[i].trees);
      array_delete(&pop_results.contents[i].trees);
    }
    return ReduceStoppedAtError;
  }

  size_t removed_heads = 0;

  for (size_t i = 0; i < pop_results.size; i++) {
    StackPopResult pop_result = pop_results.contents[i];

    /*
     *  If the same set of trees led to a previous stack head, reuse the parent
     *  tree that was added to that head. Otherwise, create a new parent node
     *  for this set of trees.
     */
    TSTree *parent = NULL;
    size_t trailing_extra_count = 0;
    for (size_t j = pop_result.trees.size - 1; j + 1 > 0; j--) {
      if (pop_result.trees.contents[j]->extra)
        trailing_extra_count++;
      else
        break;
    }

    size_t popped_child_count = pop_result.trees.size - trailing_extra_count;
    parent = ts_tree_make_node(symbol, popped_child_count,
                               pop_result.trees.contents, metadata);
    if (!parent) {
      for (size_t i = 0; i < pop_result.trees.size; i++)
        ts_tree_release(pop_result.trees.contents[i]);
      array_delete(&pop_result.trees);
      goto error;
    }

    if (!array_push(&self->reduce_parents, parent))
      goto error;

    int new_head = pop_result.head_index - removed_heads;

    if (i > 0) {
      if (symbol == ts_builtin_sym_error) {
        removed_heads++;
        ts_stack_remove_head(self->stack, new_head);
        continue;
      }

      /*
       *  If the stack has split in the process of popping, create a duplicate
       * of
       *  the lookahead state for this head, for the new head.
       */
      LOG("split_during_reduce new_head:%d", new_head);
      LookaheadState lookahead_state = *array_get(&self->lookahead_states, head);
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

    /*
     *  If the given state already existed at a different head of the stack,
     *  then remove the lookahead state for the head.
     */
    switch (ts_stack_push(self->stack, new_head, parent, state)) {
      case StackPushResultFailed:
        ts_tree_release(parent);
        goto error;
      case StackPushResultMerged:
        LOG("merge_during_reduce head:%d", new_head);
        array_erase(&self->lookahead_states, new_head);
        removed_heads++;
        continue;
      case StackPushResultContinued:
        break;
    }

    if (trailing_extra_count > 0) {
      for (size_t j = 0; j < trailing_extra_count; j++) {
        size_t index = pop_result.trees.size - trailing_extra_count + j;
        TSTree *tree = pop_result.trees.contents[index];
        switch (ts_stack_push(self->stack, new_head, tree, state)) {
          case StackPushResultFailed:
            return ReduceFailed;
          case StackPushResultMerged:
            array_erase(&self->lookahead_states, new_head);
            removed_heads++;
            break;
          case StackPushResultContinued:
            break;
        }
        ts_tree_release(tree);
      }
    }
  }

  for (size_t i = 0; i < self->reduce_parents.size; i++) {
    TSTree **parent = array_get(&self->reduce_parents, i);

    if (fragile || self->is_split || ts_stack_head_count(self->stack) > 1) {
      (*parent)->fragile_left = true;
      (*parent)->fragile_right = true;
      (*parent)->parse_state = TS_TREE_STATE_ERROR;
    }

    ts_tree_release(*parent);
  }

  if (removed_heads < pop_results.size)
    return ReduceSucceeded;
  else
    return ReduceMerged;

error:
  return ReduceFailed;
}

static ParseActionResult ts_parser__handle_error(TSParser *self, int head,
                                                 TSTree *lookahead) {
  TSTree *next_lookahead = self->language->lex_fn(&self->lexer, 0, true);
  lookahead->size = ts_length_add(lookahead->size, next_lookahead->padding);
  next_lookahead->padding = ts_length_zero();

  if (ts_parser__shift(self, head, ts_parse_state_error, lookahead) ==
      FailedToUpdateStackHead)
    goto error;

  while (ts_language_symbol_metadata(self->language,next_lookahead->symbol).extra) {
    if (ts_parser__shift_extra(self, head, ts_parse_state_error,
                               next_lookahead) == FailedToUpdateStackHead)
      goto error;
    ts_tree_release(next_lookahead);
    next_lookahead = self->language->lex_fn(&self->lexer, 0, true);
  }

  if (next_lookahead->symbol == ts_builtin_sym_end) {
    StackPopResult result = ts_parser__pop_one(self, head, -1);
    TSTree *parent = ts_tree_make_node(ts_builtin_sym_start, result.trees.size,
      result.trees.contents, ts_language_symbol_metadata(self->language, ts_builtin_sym_start));
    ts_stack_push(self->stack, head, parent, 0);
    ts_tree_release(parent);
    ts_tree_release(next_lookahead);
    return RemovedStackHead;
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
  return FailedToUpdateStackHead;
}

static bool ts_parser__error_repair_is_better(ErrorRepair old, ErrorRepair new) {
  if (new.in_progress_state_count > old.in_progress_state_count)
    return true;
  if (new.in_progress_state_count < old.in_progress_state_count)
    return false;
  return new.skipped_subtree_count < old.skipped_subtree_count;
}

static ParseActionResult ts_parser__repair_error(TSParser *self, int head_index,
                                                 TSTree *lookahead,
                                                 const TSParseAction *actions,
                                                 size_t action_count) {
  StackEntry *entry_below = ts_stack_head(self->stack, head_index);
  while (entry_below && entry_below->state == ts_parse_state_error)
    entry_below = ts_stack_entry_next(entry_below, 0);
  bool has_repair = false;
  ErrorRepair best_repair;

  // Count how many non-extra trees were already popped, not counting the error.
  size_t count_above_error = 0;
  for (size_t i = 1; i < self->partial_pop.size; i++)
    if (!self->partial_pop.contents[i]->extra)
      count_above_error++;

  // Compare all of the reduce actions that extend back to the error. Find the
  // one that best fits the nodes *below* the error on the stack.
  for (size_t i = 0; i < action_count; i++) {
    TSParseAction action = actions[i];
    if (action.type != TSParseActionTypeReduce ||
        action.data.child_count <= count_above_error)
      continue;

    StackEntry *entry = entry_below;
    size_t depth = 0;
    size_t child_count = 0;
    size_t in_progress_state_count = 0;

    // Move down the stack until a state is reached in which the reduced symbol
    // is expected, and the current lookahead symbol is expected to follow it.
    for (;;) {
      TSStateId state = entry ? entry->state : 0;
      if (ts_language_symbol_is_in_progress(self->language, state, action.data.symbol))
        in_progress_state_count++;

      if (child_count + count_above_error >= action.data.child_count &&
          in_progress_state_count > 0) {
        TSParseAction entry_action =
          ts_language_last_action(self->language, state, action.data.symbol);
        if (entry_action.type == TSParseActionTypeShift) {
          TSStateId next_state = entry_action.data.to_state;
          TSParseAction next_action = ts_language_last_action(
            self->language, next_state, lookahead->symbol);

          if (next_action.type != TSParseActionTypeError) {
            ErrorRepair repair = {
              .symbol = action.data.symbol,
              .next_state = next_state,
              .depth = depth,
              .skipped_subtree_count = child_count + count_above_error - action.data.child_count,
              .in_progress_state_count = in_progress_state_count,
            };

            LOG_ACTION("REPAIR_GOOD sym:%s, in_progress:%lu, skipped:%lu!",
              SYM_NAME(action.data.symbol),
              in_progress_state_count,
              repair.skipped_subtree_count);

            if (!has_repair ||
                ts_parser__error_repair_is_better(best_repair, repair)) {
              has_repair = true;
              best_repair = repair;
              break;
            }
          }
        }
      }

      if (entry) {
        if (entry->state != ts_parse_state_error)
          child_count++;
        depth++;
        entry = ts_stack_entry_next(entry, 0);
      } else {
        break;
      }
    }
  }

  if (!has_repair) {
    ts_tree_array_clear(&self->partial_pop);
    array_delete(&self->partial_pop);
    ts_parser__remove_head(self, head_index);
    return RemovedStackHead;
  }

  // Pop any trees that were skipped. Make a new extra error node that contains
  // them and the error leaf node.
  StackPopResult pop_result = ts_parser__pop_one(self, head_index, best_repair.skipped_subtree_count);
  array_push(&pop_result.trees, *array_front(&self->partial_pop));
  TSTree *error = ts_tree_make_node(
    ts_builtin_sym_error,
    pop_result.trees.size,
    pop_result.trees.contents,
    ts_language_symbol_metadata(self->language, ts_builtin_sym_error));

  // Pop any additional trees that are needed for the chosen reduce action. Make
  // a new wrapper node of the chosen symbol that contains them, the error node,
  // and the trees that were popped above the error node.
  pop_result = ts_parser__pop_one(self, head_index, best_repair.depth - (error->child_count - 1));
  array_push(&pop_result.trees, error);
  for (size_t i = 1; i < self->partial_pop.size; i++)
    array_push(&pop_result.trees, self->partial_pop.contents[i]);
  array_delete(&self->partial_pop);
  TSTree *parent = ts_tree_make_node(
    best_repair.symbol,
    pop_result.trees.size,
    pop_result.trees.contents,
    ts_language_symbol_metadata(self->language, best_repair.symbol));

  StackPushResult push_result = ts_stack_push(self->stack, head_index, parent, best_repair.next_state);
  ts_tree_release(parent);
  switch (push_result) {
    case StackPushResultFailed:
      return FailedToUpdateStackHead;
    case StackPushResultMerged:
      return RemovedStackHead;
    default:
      return UpdatedStackHead;
  }
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
  return UpdatedStackHead;
}

static ParseActionResult ts_parser__accept(TSParser *self, int head) {
  StackPopResultArray pop_results = ts_stack_pop(self->stack, head, -1, true);
  if (!pop_results.size)
    goto error;

  for (size_t j = 0; j < pop_results.size; j++) {
    StackPopResult pop_result = pop_results.contents[j];
    TreeArray trees = pop_result.trees;

    for (size_t i = trees.size - 1; i + 1 > 0; i--) {
      if (!trees.contents[i]->extra) {
        TSTree *root = trees.contents[i];
        if (!array_splice(&trees, i, 1, root->child_count, root->children))
          goto error;
        ts_tree_set_children(root, trees.size, trees.contents);
        if (!trees.size)
          array_delete(&trees);

        ts_parser__remove_head(self, pop_result.head_index);
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

  return RemovedStackHead;

error:
  if (pop_results.size) {
    StackPopResult pop_result = *array_front(&pop_results);
    for (size_t i = 0; i < pop_result.trees.size; i++)
      ts_tree_release(pop_result.trees.contents[i]);
    array_delete(&pop_result.trees);
  }
  return FailedToUpdateStackHead;
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
    for (size_t i = 0; i < action_count; i++) {
      TSParseAction action = actions[i];

      int current_head;
      if (i == action_count - 1) {
        if (repaired_error && action.type == TSParseActionTypeReduce)
          action.type = TSParseActionTypeError;
        current_head = head;
      } else {
        if (repaired_error)
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
            return RemovedStackHead;
          }

          if (ts_stack_head_count(self->stack) == 1) {
            LOG_ACTION("error_sym");
            switch (ts_parser__handle_error(self, current_head, lookahead)) {
              case FailedToUpdateStackHead:
                return FailedToUpdateStackHead;
              case UpdatedStackHead:
                return UpdatedStackHead;
              case RemovedStackHead:
                return ts_parser__accept(self, current_head);
            }
          } else {
            LOG_ACTION("bail current_head:%d", current_head);
            ts_parser__remove_head(self, current_head);
            return RemovedStackHead;
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
            switch (ts_parser__reduce(self, current_head, action.data.symbol,
                                      action.data.child_count, false,
                                      action.fragile)) {
              case ReduceFailed:
                return FailedToUpdateStackHead;
              case ReduceMerged:
                if (current_head == head)
                  return RemovedStackHead;
                break;
              case ReduceSucceeded:
                break;
              case ReduceStoppedAtError:
                repaired_error = true;
                LOG_ACTION("repair head:%d", current_head);
                switch (ts_parser__repair_error(self, current_head, lookahead,
                                                actions, action_count)) {
                  case FailedToUpdateStackHead:
                    return FailedToUpdateStackHead;
                  case RemovedStackHead:
                    LOG_ACTION("repair_failed");
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
  array_init(&self->reduce_parents);

  self->stack = ts_stack_new();
  if (!self->stack)
    goto error;

  if (!array_grow(&self->lookahead_states, 4))
    goto error;

  if (!array_grow(&self->reduce_parents, 4))
    goto error;

  return true;

error:
  if (self->stack) {
    ts_stack_delete(self->stack);
    self->stack = NULL;
  }
  if (self->lookahead_states.contents)
    array_delete(&self->lookahead_states);
  if (self->reduce_parents.contents)
    array_delete(&self->reduce_parents);
  return false;
}

void ts_parser_destroy(TSParser *self) {
  if (self->stack)
    ts_stack_delete(self->stack);
  if (self->lookahead_states.contents)
    array_delete(&self->lookahead_states);
  if (self->reduce_parents.contents)
    array_delete(&self->reduce_parents);
  ts_tree_array_clear(&self->partial_pop);
  if (self->partial_pop.contents)
    array_delete(&self->partial_pop);
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
          case FailedToUpdateStackHead:
            ts_tree_release(lookahead);
            goto error;
          case RemovedStackHead:
            removed = true;
            break;
          case UpdatedStackHead:
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
