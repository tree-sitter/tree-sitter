#include "runtime/parser.h"
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "tree_sitter/runtime.h"
#include "tree_sitter/parser.h"
#include "runtime/tree.h"
#include "runtime/lexer.h"
#include "runtime/length.h"
#include "runtime/vector.h"

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

typedef struct {
  TSTree *reusable_subtree;
  size_t reusable_subtree_pos;
  TSLength position;
} HeadState;

typedef enum {
  ConsumeResultShifted,
  ConsumeResultRemoved,
  ConsumeResultFinished
} ConsumeResult;

/*
 *  Private
 */

static const TSParseAction ERROR_ACTIONS[2] = {
  {.type = TSParseActionTypeError }, {.type = 0 }
};

static const TSParseAction *ts_language__actions(const TSLanguage *language,
                                                 TSStateId state, TSSymbol sym) {
  const TSParseAction *actions =
    (language->parse_table + (state * language->symbol_count))[sym];
  return actions ? actions : ERROR_ACTIONS;
}

static TSParseAction ts_language__last_action(const TSLanguage *language,
                                              TSStateId state, TSSymbol sym) {
  const TSParseAction *action = ts_language__actions(language, state, sym);
  while ((action + 1)->type)
    action++;
  return *action;
}

/*
 *  Replace the parser's reusable_subtree with its first non-fragile descendant.
 *  Return true if a suitable descendant is found, false otherwise.
 */
static bool ts_parser__breakdown_reusable_subtree(HeadState *state) {
  do {
    if (state->reusable_subtree->symbol == ts_builtin_sym_error)
      return false;
    if (state->reusable_subtree->child_count == 0)
      return false;
    state->reusable_subtree = state->reusable_subtree->children[0];
  } while (ts_tree_is_fragile(state->reusable_subtree));
  return true;
}

/*
 *  Replace the parser's reusable_subtree with its largest right neighbor, or
 *  NULL if no right neighbor exists.
 */
static void ts_parser__pop_reusable_subtree(HeadState *state) {
  state->reusable_subtree_pos +=
    ts_tree_total_size(state->reusable_subtree).chars;

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
  TSStateId state = ts_stack_top_state(self->stack, head);
  const TSParseAction *action =
    ts_language__actions(self->language, state, subtree->symbol);
  return action->type != TSParseActionTypeError;
}

/*
 *  Advance the parser's lookahead subtree. If there is a reusable subtree
 *  at the correct position in the parser's previous tree, use that. Otherwise,
 *  run the lexer.
 */
static TSTree *ts_parser__get_next_lookahead(TSParser *self, int head) {
  HeadState *state = vector_get(&self->head_states, head);

  while (state->reusable_subtree) {
    if (state->reusable_subtree_pos > state->position.chars) {
      break;
    }

    if (state->reusable_subtree_pos < state->position.chars) {
      LOG("past_reuse sym:%s", SYM_NAME(state->reusable_subtree->symbol));
      ts_parser__pop_reusable_subtree(state);
      continue;
    }

    if (ts_tree_has_changes(state->reusable_subtree) ||
        ts_tree_is_fragile(state->reusable_subtree) ||
        ts_tree_is_extra(state->reusable_subtree) ||
        (state->reusable_subtree->child_count > 0 &&
         !ts_parser__can_reuse(self, head, state->reusable_subtree))) {
      LOG("breakdown sym:%s", SYM_NAME(state->reusable_subtree->symbol));
      if (!ts_parser__breakdown_reusable_subtree(state))
        ts_parser__pop_reusable_subtree(state);
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
  assert(result == (int)self->head_states.size);
  HeadState head_state = *(HeadState *)vector_get(&self->head_states, head);
  vector_push(&self->head_states, &head_state);
  return result;
}

static void ts_parser__remove_head(TSParser *self, int head) {
  vector_erase(&self->head_states, head);
  ts_stack_remove_head(self->stack, head);
}

/*
 *  Parse Actions
 */

static ConsumeResult ts_parser__shift(TSParser *self, int head,
                                      TSStateId parse_state) {
  HeadState *head_state = vector_get(&self->head_states, head);
  head_state->position =
    ts_length_add(head_state->position, ts_tree_total_size(self->lookahead));
  if (ts_stack_push(self->stack, head, parse_state, self->lookahead)) {
    LOG("merge head:%d", head);
    vector_erase(&self->head_states, head);
    return ConsumeResultRemoved;
  } else {
    return ConsumeResultShifted;
  }
}

static bool ts_parser__shift_extra(TSParser *self, int head, TSStateId state) {
  ts_tree_set_extra(self->lookahead);
  return ts_parser__shift(self, head, state);
}

static TSTree *ts_parser__reduce(TSParser *self, int head, TSSymbol symbol,
                                 int child_count, bool extra, bool count_extra) {
  vector_clear(&self->reduce_parents);
  TSNodeType node_type = self->language->node_types[symbol];
  Vector pop_results = ts_stack_pop(self->stack, head, child_count, count_extra);

  int last_head_index = -1;
  int removed_heads = 0;

  for (size_t i = 0; i < pop_results.size; i++) {
    StackPopResult *pop_result = vector_get(&pop_results, i);

    /*
     *  If the same set of trees led to a previous stack head, reuse the parent
     *  tree that was added to that head.
     */
    TSTree *parent = NULL;
    for (size_t j = 0; j < i; j++) {
      StackPopResult *prior_result = vector_get(&pop_results, j);
      if (pop_result->trees == prior_result->trees) {
        TSTree **existing_parent = vector_get(&self->reduce_parents, j);
        parent = *existing_parent;
        break;
      }
    }

    /*
     *  Otherwise, create a new parent node for this set of trees.
     */
    if (!parent)
      parent = ts_tree_make_node(symbol, pop_result->tree_count,
                                 pop_result->trees, node_type);
    vector_push(&self->reduce_parents, &parent);

    /*
     *  If another path led to the same stack head, add this new parent tree
     *  as an alternative for that stack head.
     */
    int new_head = pop_result->head_index - removed_heads;
    if (pop_result->head_index == last_head_index) {
      ts_stack_add_alternative(self->stack, new_head, parent);
      continue;
    }

    /*
     *  If the stack has split in the process of popping, create a duplicate of
     *  the lookahead state for this head, for the new head.
     */
    if (i > 0) {
      LOG("split_during_reduce new_head:%d", new_head);
      HeadState *head_state = vector_get(&self->head_states, head);
      vector_push(&self->head_states, head_state);
    }

    /*
     *  If the parent node is extra, then do not change the state when pushing
     *  it. Otherwise, proceed to the state given in the parse table for the
     *  new parent symbol.
     */
    TSStateId state;
    TSStateId top_state = ts_stack_top_state(self->stack, new_head);
    if (extra) {
      ts_tree_set_extra(parent);
      state = top_state;
    } else {
      TSParseAction action =
        ts_language__last_action(self->language, top_state, symbol);
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
      vector_erase(&self->head_states, new_head);
      removed_heads++;
    }

    last_head_index = pop_result->head_index;
  }

  TSTree **last_parent = vector_back(&self->reduce_parents);
  return *last_parent;
}

static void ts_parser__reduce_fragile(TSParser *self, int head, TSSymbol symbol,
                                      size_t child_count) {
  TSTree *reduced =
    ts_parser__reduce(self, head, symbol, child_count, false, false);
  ts_tree_set_fragile_left(reduced);
  ts_tree_set_fragile_right(reduced);
}

static void ts_parser__reduce_error(TSParser *self, int head,
                                    size_t child_count) {
  HeadState *head_state = vector_get(&self->head_states, head);
  TSTree *reduced = ts_parser__reduce(self, head, ts_builtin_sym_error,
                                      child_count, false, true);
  reduced->size = ts_length_add(reduced->size, self->lookahead->padding);
  head_state->position =
    ts_length_add(head_state->position, self->lookahead->padding);
  self->lookahead->padding = ts_length_zero();
  ts_tree_set_fragile_left(reduced);
  ts_tree_set_fragile_right(reduced);
}

static bool ts_parser__handle_error(TSParser *self, int head) {
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
      TSParseAction action_on_error = ts_language__last_action(
        self->language, stack_state, ts_builtin_sym_error);

      if (action_on_error.type == TSParseActionTypeShift) {
        TSStateId state_after_error = action_on_error.data.to_state;
        TSParseAction action_after_error = ts_language__last_action(
          self->language, state_after_error, self->lookahead->symbol);

        if (action_after_error.type != TSParseActionTypeError) {
          LOG("recover state:%u, count:%lu", state_after_error,
              error_token_count + i);
          ts_parser__reduce_error(self, head, error_token_count + i);
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
    LOG("skip token:%s", SYM_NAME(self->lookahead->symbol));
    ts_parser__shift(self, head, ts_stack_top_state(self->stack, head));
    self->lookahead = self->language->lex_fn(&self->lexer, ts_lex_state_error);
    error_token_count++;

    /*
     *  If the end of input is reached, exit.
     */
    if (self->lookahead->symbol == ts_builtin_sym_end) {
      LOG("fail_to_recover");
      ts_parser__reduce_error(self, head, -1);
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

  self->lexer.input = input;
  ts_lexer_reset(&self->lexer, ts_length_zero());
  ts_stack_clear(self->stack);

  HeadState head_state = {
    .position = ts_length_zero(),
    .reusable_subtree = previous_tree,
    .reusable_subtree_pos = 0,
  };
  vector_clear(&self->head_states);
  vector_push(&self->head_states, &head_state);

  self->lookahead = NULL;
}

static TSTree *ts_parser__finish(TSParser *self) {
  Vector pop_results = ts_stack_pop(self->stack, 0, -1, true);
  StackPopResult *pop_result = vector_get(&pop_results, 0);

  TSTree **trees = pop_result->trees;
  size_t extra_count = pop_result->tree_count - 1;
  TSTree *root = trees[extra_count];

  ts_tree_prepend_children(root, extra_count, trees);
  ts_tree_assign_parents(root);
  return root;
}

/*
 * Continue performing parse actions for the given head until the current
 * lookahead symbol is consumed.
 */
static ConsumeResult ts_parser__consume_lookahead(TSParser *self, int head) {
  for (;;) {
    TSStateId state = ts_stack_top_state(self->stack, head);
    const TSParseAction *next_action =
      ts_language__actions(self->language, state, self->lookahead->symbol);

    /*
     * If there are multiple actions for the current state and lookahead symbol,
     * split the stack so that each one can be performed. If there is a `SHIFT`
     * action, it will always appear *last* in the list of actions. Perform it
     * on the original stack head and return.
     */
    while (next_action->type != 0) {
      TSParseAction action = *next_action;
      next_action++;

      int current_head;
      if (next_action->type == 0) {
        current_head = head;
      } else {
        current_head = ts_parser__split(self, head);
        LOG("split_action from_head:%d, new_head:%d", head, current_head);
      }

      // TODO: Remove this by making a separate symbol for errors returned from
      // the lexer.
      if (self->lookahead->symbol == ts_builtin_sym_error)
        action.type = TSParseActionTypeError;

      switch (action.type) {
        case TSParseActionTypeError:
          LOG("error_sym");
          if (ts_stack_head_count(self->stack) == 1) {
            if (ts_parser__handle_error(self, current_head))
              break;
            else
              return ConsumeResultFinished;
          } else {
            LOG("bail current_head:%d", current_head);
            ts_parser__remove_head(self, current_head);
            return ConsumeResultRemoved;
          }

        case TSParseActionTypeShift:
          LOG("shift state:%u", action.data.to_state);
          return ts_parser__shift(self, current_head, action.data.to_state);

        case TSParseActionTypeShiftExtra:
          LOG("shift_extra");
          return ts_parser__shift_extra(self, current_head, state);

        case TSParseActionTypeReduce:
          LOG("reduce sym:%s, child_count:%u", SYM_NAME(action.data.symbol),
              action.data.child_count);
          ts_parser__reduce(self, current_head, action.data.symbol,
                            action.data.child_count, false, false);
          break;

        case TSParseActionTypeReduceExtra:
          LOG("reduce_extra sym:%s", SYM_NAME(action.data.symbol));
          ts_parser__reduce(self, current_head, action.data.symbol, 1, true,
                            false);
          break;

        case TSParseActionTypeReduceFragile:
          LOG("reduce_fragile sym:%s, count:%u", SYM_NAME(action.data.symbol),
              action.data.child_count);
          ts_parser__reduce_fragile(self, current_head, action.data.symbol,
                                    action.data.child_count);
          break;

        case TSParseActionTypeAccept:
          LOG("accept");
          return ConsumeResultFinished;
      }
    }
  }
}

static TSTree *ts_parser__select_tree(void *data, TSTree *left, TSTree *right) {
  if (ts_tree_compare(left, right) <= 0)
    return left;
  else
    return right;
}

/*
 *  Public
 */

TSParser ts_parser_make() {
  return (TSParser){
    .lexer = ts_lexer_make(),
    .stack = ts_stack_new((TreeSelectionCallback){
      NULL, ts_parser__select_tree,
    }),
    .head_states = vector_new(sizeof(HeadState), 4),
    .reduce_parents = vector_new(sizeof(TSTree *), 4),
    .lookahead = NULL,
  };
}

void ts_parser_destroy(TSParser *self) {
  ts_stack_delete(self->stack);
  if (self->lookahead)
    ts_tree_release(self->lookahead);
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
    for (int head = 0; head < ts_stack_head_count(self->stack);) {
      HeadState *state = vector_get(&self->head_states, head);

      LOG("process head:%d, head_count:%d, state:%d, pos:%lu", head,
          ts_stack_head_count(self->stack),
          ts_stack_top_state(self->stack, head), state->position.chars);

      TSTree *reused_lookahead = ts_parser__get_next_lookahead(self, head);
      if (reused_lookahead &&
          ts_parser__can_reuse(self, head, reused_lookahead)) {
        self->lookahead = reused_lookahead;
      } else if (!(self->lookahead &&
                   ts_parser__can_reuse(self, head, self->lookahead))) {
        ts_lexer_reset(&self->lexer, state->position);
        TSStateId parse_state = ts_stack_top_state(self->stack, head);
        TSStateId lex_state = self->language->lex_states[parse_state];
        self->lookahead = self->language->lex_fn(&self->lexer, lex_state);
      }

      LOG("lookahead sym:%s, size:%lu", SYM_NAME(self->lookahead->symbol),
          ts_tree_total_size(self->lookahead).chars);

      switch (ts_parser__consume_lookahead(self, head)) {
        case ConsumeResultRemoved:
          break;
        case ConsumeResultShifted:
          head++;
          break;
        case ConsumeResultFinished:
          return ts_parser__finish(self);
      }
    }

    self->lookahead = NULL;
  }
}
