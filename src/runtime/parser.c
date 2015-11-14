#include "runtime/parser.h"
#include <stdio.h>
#include <stdbool.h>
#include "tree_sitter/runtime.h"
#include "tree_sitter/parser.h"
#include "runtime/tree.h"
#include "runtime/lexer.h"
#include "runtime/length.h"

/*
 *  Debugging
 */

#define DEBUG(...)                                                             \
  if (self->lexer.debugger.debug_fn) {                                         \
    snprintf(self->lexer.debug_buffer, TS_DEBUG_BUFFER_SIZE, __VA_ARGS__);     \
    self->lexer.debugger.debug_fn(self->lexer.debugger.payload,                \
                                  TSDebugTypeParse, self->lexer.debug_buffer); \
  }

#define SYM_NAME(sym) self->language->symbol_names[sym]

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
static bool ts_parser__breakdown_reusable_subtree(TSParser *self) {
  do {
    if (self->reusable_subtree->symbol == ts_builtin_sym_error)
      return false;
    if (self->reusable_subtree->child_count == 0)
      return false;
    self->reusable_subtree = self->reusable_subtree->children[0];
  } while (ts_tree_is_fragile(self->reusable_subtree));
  return true;
}

/*
 *  Replace the parser's reusable_subtree with its largest right neighbor, or
 *  NULL if no right neighbor exists.
 */
static void ts_parser__pop_reusable_subtree(TSParser *self) {
  self->reusable_subtree_pos += ts_tree_total_size(self->reusable_subtree).chars;

  while (self->reusable_subtree) {
    TSTree *parent = self->reusable_subtree->context.parent;
    size_t next_index = self->reusable_subtree->context.index + 1;
    if (parent && parent->child_count > next_index) {
      self->reusable_subtree = parent->children[next_index];
      return;
    }
    self->reusable_subtree = parent;
  }
}

/*
 *  Advance the parser's lookahead subtree. If there is a reusable subtree
 *  at the correct position in the parser's previous tree, use that. Otherwise,
 *  run the lexer.
 */
static void ts_parser__get_next_lookahead(TSParser *self) {
  while (self->reusable_subtree) {
    if (self->reusable_subtree_pos > self->lexer.current_position.chars) {
      break;
    }

    if (self->reusable_subtree_pos < self->lexer.current_position.chars) {
      DEBUG("past_reuse sym:%s", SYM_NAME(self->reusable_subtree->symbol));
      ts_parser__pop_reusable_subtree(self);
      continue;
    }

    if (ts_tree_has_changes(self->reusable_subtree) ||
        ts_tree_is_fragile(self->reusable_subtree) ||
        ts_tree_is_extra(self->reusable_subtree)) {
      DEBUG("breakdown sym:%s", SYM_NAME(self->reusable_subtree->symbol));
      if (!ts_parser__breakdown_reusable_subtree(self))
        ts_parser__pop_reusable_subtree(self);
      continue;
    }

    TSStateId top_state = ts_stack_top_state(self->stack, 0);
    TSSymbol symbol = self->reusable_subtree->symbol;
    if (ts_language__last_action(self->language, top_state, symbol).type ==
        TSParseActionTypeError) {
      DEBUG("cant_reuse sym:%s", SYM_NAME(self->reusable_subtree->symbol));
      ts_parser__pop_reusable_subtree(self);
      continue;
    }

    self->lookahead = self->reusable_subtree;
    TSLength size = ts_tree_total_size(self->lookahead);
    DEBUG("reuse sym:%s size:%lu extra:%d", SYM_NAME(self->lookahead->symbol),
          size.chars, self->lookahead->options.extra);
    ts_lexer_reset(&self->lexer,
                   ts_length_add(self->lexer.current_position, size));
    ts_parser__pop_reusable_subtree(self);
    return;
  }

  TSLength position = self->lexer.current_position;
  for (size_t i = 0, count = ts_stack_head_count(self->stack); i < count; i++) {
    if (i > 0) {
      ts_lexer_reset(&self->lexer, position);
      ts_tree_release(self->lookahead);
    }

    TSStateId parse_state = ts_stack_top_state(self->stack, i);
    TSStateId lex_state = self->language->lex_states[parse_state];
    DEBUG("lex state:%d", lex_state);
    self->lookahead = self->language->lex_fn(&self->lexer, lex_state);

    if (self->lookahead->symbol != ts_builtin_sym_error)
      break;
  }
}

/*
 *  Parse Actions
 */

static ConsumeResult ts_parser__shift(TSParser *self, int head,
                                      TSStateId parse_state) {
  if (ts_stack_push(self->stack, head, parse_state, self->lookahead))
    return ConsumeResultRemoved;
  else
    return ConsumeResultShifted;
}

static bool ts_parser__shift_extra(TSParser *self, int head, TSStateId state) {
  ts_tree_set_extra(self->lookahead);
  return ts_parser__shift(self, head, state);
}

static TSTree *ts_parser__reduce(TSParser *self, int head, TSSymbol symbol,
                                 size_t child_count, bool extra,
                                 bool count_extra) {
  TSNodeType node_type = self->language->node_types[symbol];
  StackPopResultList pop_results =
    ts_stack_pop(self->stack, head, child_count, count_extra);

  TSTree *parent = NULL;
  TSTree **last_children = NULL;
  int last_index = -1;

  for (int i = 0; i < pop_results.size; i++) {
    StackPopResult pop_result = pop_results.contents[i];

    if (pop_result.trees != last_children) {
      parent = ts_tree_make_node(symbol, pop_result.tree_count,
                                 pop_result.trees, node_type);
    }

    if (pop_result.index == last_index) {
      ts_stack_add_alternative(self->stack, pop_result.index, parent);
    } else {
      TSStateId top_state = ts_stack_top_state(self->stack, pop_result.index);
      TSStateId state;

      if (extra) {
        ts_tree_set_extra(parent);
        state = top_state;
      } else {
        state = ts_language__last_action(self->language, top_state, symbol)
                  .data.to_state;
      }

      ts_stack_push(self->stack, pop_result.index, state, parent);
    }

    last_index = pop_result.index;
    last_children = pop_result.trees;
  }

  return parent;
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
  TSTree *reduced = ts_parser__reduce(self, head, ts_builtin_sym_error,
                                      child_count, false, true);
  reduced->size = ts_length_add(reduced->size, self->lookahead->padding);
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
          DEBUG("recover state:%u, count:%lu", state_after_error,
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
    DEBUG("skip token:%s", SYM_NAME(self->lookahead->symbol));
    ts_parser__shift(self, head, ts_stack_top_state(self->stack, head));
    self->lookahead = self->language->lex_fn(&self->lexer, ts_lex_state_error);
    error_token_count++;

    /*
     *  If the end of input is reached, exit.
     */
    if (self->lookahead->symbol == ts_builtin_sym_end) {
      DEBUG("fail_to_recover");
      ts_parser__reduce_error(self, head, error_token_count - 1);
      return false;
    }
  }
}

static void ts_parser__start(TSParser *self, TSInput input,
                             TSTree *previous_tree) {
  if (previous_tree) {
    DEBUG("parse_after_edit");
  } else {
    DEBUG("new_parse");
  }

  self->lexer.input = input;
  ts_lexer_reset(&self->lexer, ts_length_zero());
  ts_stack_clear(self->stack);

  self->reusable_subtree = previous_tree;
  self->reusable_subtree_pos = 0;
  self->lookahead = NULL;
}

static TSTree *ts_parser__finish(TSParser *self) {
  StackPopResult pop_result = ts_stack_pop(self->stack, 0, -1, true).contents[0];

  TSTree **trees = pop_result.trees;
  size_t extra_count = pop_result.tree_count - 1;
  TSTree *root = trees[extra_count];

  ts_tree_prepend_children(root, extra_count, trees);
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
        DEBUG("action current_head:%d, state:%d", current_head, state);
      } else {
        current_head = ts_stack_split(self->stack, head);
        DEBUG("split_action from_head:%d, current_head:%d, state:%d", head,
              current_head, state);
      }

      // TODO: Remove this by making a separate symbol for errors returned from
      // the lexer.
      if (self->lookahead->symbol == ts_builtin_sym_error)
        action.type = TSParseActionTypeError;

      switch (action.type) {
        case TSParseActionTypeError:
          DEBUG("error_sym");
          if (ts_stack_head_count(self->stack) == 1) {
            if (ts_parser__handle_error(self, current_head))
              break;
            else
              return ConsumeResultFinished;
          } else {
            DEBUG("bail current_head:%d", current_head);
            ts_stack_remove_head(self->stack, current_head);
            return ConsumeResultRemoved;
          }

        case TSParseActionTypeShift:
          DEBUG("shift state:%u", action.data.to_state);
          return ts_parser__shift(self, current_head, action.data.to_state);

        case TSParseActionTypeShiftExtra:
          DEBUG("shift_extra");
          return ts_parser__shift_extra(self, current_head, state);

        case TSParseActionTypeReduce:
          DEBUG("reduce sym:%s, child_count:%u", SYM_NAME(action.data.symbol),
                action.data.child_count);
          ts_parser__reduce(self, current_head, action.data.symbol,
                            action.data.child_count, false, false);
          break;

        case TSParseActionTypeReduceExtra:
          DEBUG("reduce_extra sym:%s", SYM_NAME(action.data.symbol));
          ts_parser__reduce(self, current_head, action.data.symbol, 1, true,
                            false);
          break;

        case TSParseActionTypeReduceFragile:
          DEBUG("reduce_fragile sym:%s, count:%u", SYM_NAME(action.data.symbol),
                action.data.child_count);
          ts_parser__reduce_fragile(self, current_head, action.data.symbol,
                                    action.data.child_count);
          break;

        case TSParseActionTypeAccept:
          DEBUG("accept");
          return ConsumeResultFinished;
      }
    }
  }
}

static int ts_tree__compare(TSTree *left, TSTree *right) {
  if (left->symbol < right->symbol) return -1;
  if (right->symbol < left->symbol) return 1;
  if (left->child_count < right->child_count) return -1;
  if (right->child_count < left->child_count) return 1;
  for (size_t i = 0; i < left->child_count; i++) {
    TSTree *left_child = left->children[i];
    TSTree *right_child = right->children[i];
    switch (ts_tree__compare(left_child, right_child)) {
      case -1:
        return -1;
      case 1:
        return 1;
      default:
        break;
    }
  }
  return 0;
}

static TSTree *ts_parser__select_tree(void *data, TSTree *left, TSTree *right) {
  if (ts_tree__compare(left, right) <= 0)
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
    ts_parser__get_next_lookahead(self);

    DEBUG("lookahead sym:%s, pos:%lu, head_count:%d",
          SYM_NAME(self->lookahead->symbol), self->lexer.current_position.chars,
          ts_stack_head_count(self->stack));

    for (int head = 0; head < ts_stack_head_count(self->stack);) {
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
  }
}
