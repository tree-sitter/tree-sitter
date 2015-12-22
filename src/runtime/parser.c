#include "runtime/parser.h"
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include "tree_sitter/runtime.h"
#include "tree_sitter/parser.h"
#include "runtime/tree.h"
#include "runtime/lexer.h"
#include "runtime/length.h"
#include "runtime/vector.h"
#include "runtime/language.h"

/*
 *  Debugging
 */

#define LOG(...)                                                               \
  if (self->lexer.debugger.debug_fn) {                                         \
    snprintf(self->lexer.debug_buffer, TS_DEBUG_BUFFER_SIZE, __VA_ARGS__);     \
    self->lexer.debugger.debug_fn(self->lexer.debugger.payload,                \
                                  TSDebugTypeParse, self->lexer.debug_buffer); \
  }

#define SYM_NAME(sym) self->language->symbol_names[sym]

#define BOOL_STRING(value) (value ? "true" : "false")

typedef struct {
  TSTree *reusable_subtree;
  size_t reusable_subtree_pos;
  bool is_verifying;
} LookaheadState;

/*
 *  Private
 */

static void ts_parser__breakdown_top_of_stack(TSParser *self, int head) {
  TSTree *last_child = NULL;

  do {
    Vector pop_results = ts_stack_pop(self->stack, head, 1, false);

    /*
     *  Since only one entry (not counting extra trees) is being popped from the
     *  stack, there should only be one possible array of removed trees.
     */
    StackPopResult *first_result = vector_get(&pop_results, 0);
    TSTree **removed_trees = first_result->trees;
    TSTree *parent = removed_trees[0];
    LOG("breakdown_pop sym:%s, size:%lu", SYM_NAME(parent->symbol),
        ts_tree_total_size(parent).chars);

    for (size_t i = 0; i < pop_results.size; i++) {
      StackPopResult *pop_result = vector_get(&pop_results, i);
      assert(pop_result->trees == removed_trees);
      int head_index = pop_result->head_index;

      bool merged = true;
      TSStateId state = ts_stack_top_state(self->stack, head_index);
      for (size_t j = 0; j < parent->child_count; j++) {
        last_child = parent->children[j];
        if (!last_child->options.extra) {
          TSParseAction action =
            ts_language_last_action(self->language, state, last_child->symbol);
          assert(action.type == TSParseActionTypeShift);
          state = action.data.to_state;
        }

        LOG("breakdown_push sym:%s, size:%lu", SYM_NAME(last_child->symbol),
            ts_tree_total_size(last_child).chars);
        merged =
          ts_stack_push(self->stack, pop_result->head_index, state, last_child);
      }

      for (size_t j = 1, count = pop_result->tree_count; j < count; j++)
        merged = ts_stack_push(self->stack, pop_result->head_index, state,
                               pop_result->trees[j]);

      assert((i == 0) ^ merged);
    }

    free(removed_trees);
  } while (last_child->child_count > 0);
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
  if (!subtree)
    return false;
  if (subtree->symbol == ts_builtin_sym_error)
    return false;
  if (ts_tree_is_fragile(subtree)) {
    if (subtree->context.parse_state != ts_stack_top_state(self->stack, head))
      return false;
  }

  TSStateId state = ts_stack_top_state(self->stack, head);

  if (subtree->context.lex_state != TSTREE_STATE_INDEPENDENT) {
    TSStateId lex_state = self->language->lex_states[state];
    if (subtree->context.lex_state != lex_state)
      return false;
  }

  const TSParseAction *action =
    ts_language_actions(self->language, state, subtree->symbol);
  if (action->type == TSParseActionTypeError || action->can_hide_split)
    return false;

  if (ts_tree_is_extra(subtree) && !action->extra)
    return false;

  return true;
}

/*
 *  Advance the parser's lookahead subtree. If there is a reusable subtree
 *  at the correct position in the parser's previous tree, use that. Otherwise,
 *  run the lexer.
 */
static TSTree *ts_parser__get_next_lookahead(TSParser *self, int head) {
  LookaheadState *state = vector_get(&self->lookahead_states, head);
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

    if (ts_tree_has_changes(state->reusable_subtree)) {
      if (state->is_verifying && state->reusable_subtree->child_count == 0) {
        ts_parser__breakdown_top_of_stack(self, head);
        state->is_verifying = false;
      }

      LOG("breakdown_changed sym:%s", SYM_NAME(state->reusable_subtree->symbol));
      ts_parser__breakdown_reusable_subtree(state);
      continue;
    }

    if (!ts_parser__can_reuse(self, head, state->reusable_subtree)) {
      LOG("breakdown_unreusable sym:%s", SYM_NAME(state->reusable_subtree->symbol));
      ts_parser__breakdown_reusable_subtree(state);
      continue;
    }

    TSTree *result = state->reusable_subtree;
    TSLength size = ts_tree_total_size(result);
    LOG("reuse sym:%s size:%lu extra:%d", SYM_NAME(result->symbol), size.chars,
        result->options.extra);
    ts_parser__pop_reusable_subtree(state);
    return result;
  }

  return NULL;
}

static int ts_parser__split(TSParser *self, int head) {
  int result = ts_stack_split(self->stack, head);
  assert(result == (int)self->lookahead_states.size);
  LookaheadState lookahead_state =
    *(LookaheadState *)vector_get(&self->lookahead_states, head);
  vector_push(&self->lookahead_states, &lookahead_state);
  return result;
}

static void ts_parser__remove_head(TSParser *self, int head) {
  vector_erase(&self->lookahead_states, head);
  ts_stack_remove_head(self->stack, head);
}

static TSTree *ts_parser__select_tree(void *data, TSTree *left, TSTree *right) {
  TSParser *self = data;
  int comparison = ts_tree_compare(left, right);
  if (comparison <= 0) {
    LOG("select tree:%s, over_tree:%s", SYM_NAME(left->symbol),
        SYM_NAME(right->symbol));
    return left;
  } else {
    LOG("select tree:%s, over_tree:%s", SYM_NAME(right->symbol),
        SYM_NAME(left->symbol));
    return right;
  }
}

/*
 *  Parse Actions
 */

static bool ts_parser__shift(TSParser *self, int head, TSStateId parse_state,
                             TSTree *lookahead) {
  if (ts_stack_push(self->stack, head, parse_state, lookahead)) {
    LOG("merge head:%d", head);
    vector_erase(&self->lookahead_states, head);
    return false;
  } else {
    return true;
  }
}

static bool ts_parser__shift_extra(TSParser *self, int head, TSStateId state,
                                   TSTree *lookahead) {
  TSSymbolMetadata metadata = self->language->symbol_metadata[lookahead->symbol];
  if (metadata.structural && ts_stack_head_count(self->stack) > 1)
    lookahead = ts_tree_make_copy(lookahead);
  ts_tree_set_extra(lookahead);
  return ts_parser__shift(self, head, state, lookahead);
}

static bool ts_parser__reduce(TSParser *self, int head, TSSymbol symbol,
                              int child_count, bool extra, bool fragile,
                              bool count_extra) {
  vector_clear(&self->reduce_parents);
  const TSSymbolMetadata *all_metadata = self->language->symbol_metadata;
  TSSymbolMetadata metadata = all_metadata[symbol];
  Vector pop_results = ts_stack_pop(self->stack, head, child_count, count_extra);

  int last_head_index = -1;
  size_t removed_heads = 0;
  size_t revealed_heads = 0;

  for (size_t i = 0; i < pop_results.size; i++) {
    StackPopResult *pop_result = vector_get(&pop_results, i);

    /*
     *  If the same set of trees led to a previous stack head, reuse the parent
     *  tree that was added to that head.
     */
    TSTree *parent = NULL;
    size_t trailing_extra_count = 0;
    for (size_t j = 0; j < i; j++) {
      StackPopResult *prior_result = vector_get(&pop_results, j);
      if (pop_result->trees == prior_result->trees) {
        TSTree **existing_parent = vector_get(&self->reduce_parents, j);
        parent = *existing_parent;
        trailing_extra_count = pop_result->tree_count - parent->child_count;
        break;
      }
    }

    /*
     *  Otherwise, create a new parent node for this set of trees.
     */
    if (!parent) {
      for (size_t j = pop_result->tree_count - 1; j + 1 > 0; j--) {
        if (pop_result->trees[j]->options.extra) {
          trailing_extra_count++;
        } else
          break;
      }

      parent =
        ts_tree_make_node(symbol, pop_result->tree_count - trailing_extra_count,
                          pop_result->trees, metadata);
    }
    vector_push(&self->reduce_parents, &parent);

    /*
     *  If another path led to the same stack head, add this new parent tree
     *  as an alternative for that stack head.
     */
    int new_head = pop_result->head_index - removed_heads;
    if (pop_result->head_index == last_head_index) {
      ts_stack_add_alternative(self->stack, new_head, parent);
      continue;
    } else {
      revealed_heads++;
      last_head_index = pop_result->head_index;
    }

    /*
     *  If the stack has split in the process of popping, create a duplicate of
     *  the lookahead state for this head, for the new head.
     */
    if (i > 0) {
      if (symbol == ts_builtin_sym_error) {
        ts_stack_remove_head(self->stack, new_head);
        continue;
      }

      LOG("split_during_reduce new_head:%d", new_head);
      LookaheadState *lookahead_state =
        vector_get(&self->lookahead_states, head);
      vector_push(&self->lookahead_states, lookahead_state);
    }

    /*
     *  If the parent node is extra, then do not change the state when pushing
     *  it. Otherwise, proceed to the state given in the parse table for the
     *  new parent symbol.
     */
    TSStateId state;
    TSStateId top_state = ts_stack_top_state(self->stack, new_head);

    if (parent->context.parse_state != TSTREE_STATE_ERROR)
      parent->context.parse_state = top_state;

    if (extra) {
      ts_tree_set_extra(parent);
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
    if (ts_stack_push(self->stack, new_head, state, parent)) {
      LOG("merge_during_reduce head:%d", new_head);
      vector_erase(&self->lookahead_states, new_head);
      removed_heads++;
      continue;
    }

    if (trailing_extra_count > 0) {
      for (size_t j = 0; j < trailing_extra_count; j++) {
        size_t index = pop_result->tree_count - trailing_extra_count + j;
        if (ts_stack_push(self->stack, new_head, state,
                          pop_result->trees[index])) {
          vector_erase(&self->lookahead_states, new_head);
          removed_heads++;
          continue;
        }
      }
    }
  }

  if (self->is_split || ts_stack_head_count(self->stack) > 1) {
    for (size_t i = 0, size = self->reduce_parents.size; i < size; i++) {
      TSTree **parent = vector_get(&self->reduce_parents, i);
      (*parent)->options.fragile_left = true;
      (*parent)->options.fragile_right = true;
      (*parent)->context.parse_state = TSTREE_STATE_ERROR;
    }
  }

  if (fragile) {
    for (size_t i = 0; i < self->reduce_parents.size; i++) {
      TSTree **parent = vector_get(&self->reduce_parents, i);
      ts_tree_set_fragile_left(*parent);
      ts_tree_set_fragile_right(*parent);
    }
  }

  return removed_heads < revealed_heads;
}

static void ts_parser__reduce_error(TSParser *self, int head,
                                    size_t child_count, TSTree *lookahead) {
  bool result = ts_parser__reduce(self, head, ts_builtin_sym_error, child_count,
                                  false, false, true);
  if (result) {
    TSTree **parent = vector_back(&self->reduce_parents);
    StackEntry *stack_entry = ts_stack_head(self->stack, head);
    stack_entry->position =
      ts_length_add(stack_entry->position, lookahead->padding);
    (*parent)->size = ts_length_add((*parent)->size, lookahead->padding);
    lookahead->padding = ts_length_zero();
    ts_tree_set_fragile_left(*parent);
    ts_tree_set_fragile_right(*parent);
  }
}

static bool ts_parser__handle_error(TSParser *self, int head, TSTree *lookahead) {
  size_t error_token_count = 1;
  StackEntry *entry_before_error = ts_stack_head(self->stack, head);

  for (;;) {

    /*
     *  Unwind the parse stack until a state is found in which an error is
     *  expected and the current lookahead token is expected afterwards.
     */
    int i = -1;
    for (StackEntry *entry = entry_before_error; true;
         entry = ts_stack_entry_next(entry, 0), i++) {
      TSStateId stack_state = entry ? entry->state : 0;
      TSParseAction action_on_error = ts_language_last_action(
        self->language, stack_state, ts_builtin_sym_error);

      if (action_on_error.type == TSParseActionTypeShift) {
        TSStateId state_after_error = action_on_error.data.to_state;
        TSParseAction action_after_error = ts_language_last_action(
          self->language, state_after_error, lookahead->symbol);

        if (action_after_error.type != TSParseActionTypeError) {
          LOG("recover state:%u, count:%lu", state_after_error,
              error_token_count + i);
          ts_parser__reduce_error(self, head, error_token_count + i, lookahead);
          return true;
        }
      }

      if (!entry)
        break;
    }

    /*
     *  If there is no state in the stack for which we can recover with the
     *  current lookahead token, advance to the next token.
     */
    LOG("skip token:%s", SYM_NAME(lookahead->symbol));
    ts_parser__shift(self, head, ts_stack_top_state(self->stack, head),
                     lookahead);
    lookahead = self->language->lex_fn(&self->lexer, ts_lex_state_error);
    error_token_count++;

    /*
     *  If the end of input is reached, exit.
     */
    if (lookahead->symbol == ts_builtin_sym_end) {
      LOG("fail_to_recover");
      ts_parser__reduce_error(self, head, -1, lookahead);
      return false;
    }
  }
}

static void ts_parser__start(TSParser *self, TSInput input,
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
  vector_clear(&self->lookahead_states);
  vector_push(&self->lookahead_states, &lookahead_state);
  self->finished_stack_head = -1;
}

static TSTree *ts_parser__finish(TSParser *self, int finished_stack_head) {
  Vector pop_results = ts_stack_pop(self->stack, finished_stack_head, -1, true);
  StackPopResult *pop_result = vector_get(&pop_results, 0);

  for (size_t i = 0; i < pop_result->tree_count; i++) {
    if (!pop_result->trees[i]->options.extra) {
      TSTree *root = pop_result->trees[i];
      size_t leading_extra_count = i;
      size_t trailing_extra_count = pop_result->tree_count - 1 - i;
      TSTree **new_children =
        malloc((root->child_count + leading_extra_count + trailing_extra_count) *
               sizeof(TSTree *));
      memcpy(new_children, pop_result->trees,
             leading_extra_count * sizeof(TSTree *));
      memcpy(new_children + leading_extra_count, root->children,
             root->child_count * sizeof(TSTree *));
      memcpy(new_children + leading_extra_count + root->child_count,
             pop_result->trees + leading_extra_count + 1,
             trailing_extra_count * sizeof(TSTree *));
      size_t new_count =
        root->child_count + leading_extra_count + trailing_extra_count;
      ts_tree_set_children(root, new_count, new_children);
      ts_tree_assign_parents(root);
      return root;
    }
  }

  return NULL;
}

/*
 * Continue performing parse actions for the given head until the current
 * lookahead symbol is consumed.
 */
static bool ts_parser__consume_lookahead(TSParser *self, int head,
                                         TSTree *lookahead) {
  for (;;) {
    TSStateId state = ts_stack_top_state(self->stack, head);
    const TSParseAction *next_action =
      ts_language_actions(self->language, state, lookahead->symbol);

    /*
     * If there are multiple actions for the current state and lookahead symbol,
     * split the stack so that each one can be performed. If there is a `SHIFT`
     * action, it will always appear *last* in the list of actions. Perform it
     * on the original stack head and return.
     */
    while (next_action) {
      TSParseAction action = *next_action;
      next_action++;

      int current_head;
      if (next_action->type == 0) {
        current_head = head;
        next_action = NULL;
      } else {
        current_head = ts_parser__split(self, head);
        LOG("split_action from_head:%d, new_head:%d", head, current_head);
      }

      LookaheadState *lookahead_state =
        vector_get(&self->lookahead_states, current_head);

      // TODO: Remove this by making a separate symbol for errors returned from
      // the lexer.
      if (lookahead->symbol == ts_builtin_sym_error)
        action.type = TSParseActionTypeError;

      switch (action.type) {
        case TSParseActionTypeError:
          LOG("error_sym");
          if (lookahead_state->is_verifying) {
            ts_parser__breakdown_top_of_stack(self, current_head);
            lookahead_state->is_verifying = false;
            return false;
          }

          if (ts_stack_head_count(self->stack) == 1) {
            if (!ts_parser__handle_error(self, current_head, lookahead))
              self->finished_stack_head = current_head;
            return true;
          } else {
            LOG("bail current_head:%d", current_head);
            ts_parser__remove_head(self, current_head);
            return false;
          }

        case TSParseActionTypeShift:
          if (action.extra) {
            LOG("shift_extra");
            return ts_parser__shift_extra(self, current_head, state, lookahead);
          } else {
            LOG("shift state:%u", action.data.to_state);
            lookahead_state->is_verifying = (lookahead->child_count > 0);
            return ts_parser__shift(self, current_head, action.data.to_state,
                                    lookahead);
          }

        case TSParseActionTypeReduce:
          lookahead_state->is_verifying = false;

          if (action.extra) {
            LOG("reduce_extra sym:%s", SYM_NAME(action.data.symbol));
            ts_parser__reduce(self, current_head, action.data.symbol, 1, true,
                              false, false);
          } else {
            LOG("reduce sym:%s, child_count:%u, fragile:%s",
                SYM_NAME(action.data.symbol), action.data.child_count,
                BOOL_STRING(action.fragile));
            if (!ts_parser__reduce(self, current_head, action.data.symbol,
                                   action.data.child_count, false,
                                   action.fragile, false))
              if (!next_action)
                return false;
          }
          break;

        case TSParseActionTypeAccept:
          LOG("accept");
          self->finished_stack_head = current_head;
          return true;
      }
    }
  }
}

/*
 *  Public
 */

TSParser ts_parser_make() {
  return (TSParser){
    .lexer = ts_lexer_make(),
    .stack = ts_stack_new(),
    .lookahead_states = vector_new(sizeof(LookaheadState), 4),
    .reduce_parents = vector_new(sizeof(TSTree *), 4),
    .finished_stack_head = -1,
  };
}

void ts_parser_destroy(TSParser *self) {
  ts_stack_delete(self->stack);
}

TSDebugger ts_parser_debugger(const TSParser *self) {
  return self->lexer.debugger;
}

void ts_parser_set_debugger(TSParser *self, TSDebugger debugger) {
  self->lexer.debugger = debugger;
}

TSTree *ts_parser_parse(TSParser *self, TSInput input, TSTree *previous_tree) {
  ts_parser__start(self, input, previous_tree);

  for (;;) {
    TSTree *lookahead = NULL;
    TSLength position = ts_length_zero(), last_position;

    self->is_split = ts_stack_head_count(self->stack) > 1;
    for (int head = 0; head < ts_stack_head_count(self->stack);) {
      StackEntry *entry = ts_stack_head(self->stack, head);
      last_position = position;
      position = entry ? entry->position : ts_length_zero();

      LOG("process head:%d, head_count:%d, state:%d, pos:%lu", head,
          ts_stack_head_count(self->stack),
          ts_stack_top_state(self->stack, head), position.chars);

      if (!ts_parser__can_reuse(self, head, lookahead) ||
          position.chars != last_position.chars) {
        lookahead = ts_parser__get_next_lookahead(self, head);
        if (!lookahead) {
          ts_lexer_reset(&self->lexer, position);
          TSStateId parse_state = ts_stack_top_state(self->stack, head);
          TSStateId lex_state = self->language->lex_states[parse_state];
          LOG("lex state:%d", lex_state);
          lookahead = self->language->lex_fn(&self->lexer, lex_state);
        }
      }

      LOG("lookahead sym:%s, size:%lu", SYM_NAME(lookahead->symbol),
          ts_tree_total_chars(lookahead));

      if (ts_parser__consume_lookahead(self, head, lookahead))
        head++;
    }

    if (self->finished_stack_head >= 0 && ts_stack_head_count(self->stack) == 1)
      return ts_parser__finish(self, self->finished_stack_head);
  }
}
