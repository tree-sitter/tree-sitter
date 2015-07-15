#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include "tree_sitter/runtime.h"
#include "tree_sitter/parser.h"
#include "runtime/tree.h"
#include "runtime/lexer.h"
#include "runtime/stack.h"
#include "runtime/parser.h"
#include "runtime/length.h"
#include "runtime/debugger.h"

/*
 *  Debugging
 */

#define DEBUG(...)                                                           \
  if (parser->lexer.debugger.debug_fn) {                                     \
    snprintf(parser->lexer.debug_buffer, TS_DEBUG_BUFFER_SIZE, __VA_ARGS__); \
    parser->lexer.debugger.debug_fn(parser->lexer.debugger.data,             \
                                    TSDebugTypeParse,                        \
                                    parser->lexer.debug_buffer);             \
  }

#define SYM_NAME(sym) parser->language->symbol_names[sym]

/*
 *  Private
 */

static const TSParseAction ERROR_ACTIONS[2] = {
  {.type = TSParseActionTypeError},
  {.type = 0}
};

static const TSParseAction *get_actions(const TSLanguage *language, TSStateId state,
                                TSSymbol sym) {
  const TSParseAction *actions = (language->parse_table + (state * language->symbol_count))[sym];
  return actions ? actions : ERROR_ACTIONS;
}

static TSParseAction get_action(const TSLanguage *language, TSStateId state,
                                TSSymbol sym) {
  return get_actions(language, state, sym)[0];
}

static TSLength break_down_left_stack(TSParser *parser, TSInputEdit edit) {
  ts_stack_shrink(&parser->right_stack, 0);

  TSLength prev_size = ts_tree_total_size(ts_parse_stack_top_tree(parser->stack, 0));
  parser->total_chars =
      prev_size.chars + edit.chars_inserted - edit.chars_removed;
  TSLength left_subtree_end = prev_size;
  size_t right_subtree_start = parser->total_chars;

  for (;;) {
    ParseStackEntry *entry = ts_parse_stack_head(parser->stack, 0);
    if (!entry)
      break;
    TSTree *node = entry->tree;

    size_t child_count;
    TSTree **children = ts_tree_children(node, &child_count);
    if (left_subtree_end.chars < edit.position && !children && node->symbol != ts_builtin_sym_error)
      break;

    DEBUG("pop_left sym:%s, state:%u", SYM_NAME(node->symbol),
          ts_parse_stack_top_state(parser->stack, 0));
    ts_parse_stack_shrink(parser->stack, 0, 1);
    left_subtree_end = ts_length_sub(left_subtree_end, ts_tree_total_size(node));

    size_t i = 0;
    for (; i < child_count && left_subtree_end.chars < edit.position; i++) {
      TSTree *child = children[i];
      TSStateId state = ts_parse_stack_top_state(parser->stack, 0);
      TSParseAction action = get_action(parser->language, state, child->symbol);
      TSStateId next_state =
          ts_tree_is_extra(child) ? state : action.data.to_state;

      DEBUG("push_left sym:%s, state:%u", SYM_NAME(child->symbol), next_state);
      ts_parse_stack_push(parser->stack, 0, next_state, child);
      left_subtree_end =
          ts_length_add(left_subtree_end, ts_tree_total_size(child));
    }

    for (size_t j = child_count - 1; j + 1 > i; j--) {
      TSTree *child = children[j];
      right_subtree_start -= ts_tree_total_size(child).chars;
      if (right_subtree_start < edit.position + edit.chars_inserted)
        break;

      DEBUG("push_right sym:%s", SYM_NAME(child->symbol));
      ts_stack_push(&parser->right_stack, 0, child);
    }

    ts_tree_release(node);
  }

  DEBUG("reuse_left chars:%lu, state:%u", left_subtree_end.chars,
        ts_parse_stack_top_state(parser->stack, 0));
  return left_subtree_end;
}

static TSTree *break_down_right_stack(TSParser *parser) {
  TSStack *stack = &parser->right_stack;
  TSLength current_position = parser->lexer.current_position;
  TSStateId state = ts_parse_stack_top_state(parser->stack, 0);

  size_t right_subtree_start =
      parser->total_chars - ts_stack_total_tree_size(stack).chars;

  for (;;) {
    TSTree *node = ts_stack_top_node(stack);
    if (!node)
      return NULL;

    if (right_subtree_start > current_position.chars)
      return NULL;

    TSParseAction action = get_action(parser->language, state, node->symbol);
    bool is_usable = (action.type != TSParseActionTypeError) &&
                     !ts_tree_is_extra(node) &&
                     !ts_tree_is_empty(node) &&
                     !ts_tree_is_fragile_left(node) &&
                     !ts_tree_is_fragile_right(node);
    if (is_usable && right_subtree_start == current_position.chars) {
      ts_stack_shrink(&parser->right_stack, parser->right_stack.size - 1);
      return node;
    }

    size_t child_count;
    TSTree **children = ts_tree_children(node, &child_count);

    DEBUG("pop_right sym:%s", SYM_NAME(node->symbol));
    stack->size--;
    right_subtree_start += ts_tree_total_size(node).chars;

    for (size_t i = child_count - 1; i + 1 > 0; i--) {
      if (right_subtree_start <= current_position.chars)
        break;

      TSTree *child = children[i];
      DEBUG("push_right sym:%s", SYM_NAME(child->symbol));
      ts_stack_push(stack, 0, child);
      right_subtree_start -= ts_tree_total_size(child).chars;
    }

    ts_tree_release(node);
  }
}

static TSTree *get_next_node(TSParser *parser, TSStateId lex_state) {
  TSTree *node;

  if ((node = break_down_right_stack(parser))) {
    DEBUG("reuse sym:%s, is_extra:%u, size:%lu", SYM_NAME(node->symbol),
          ts_tree_is_extra(node), ts_tree_total_size(node).chars);

    parser->lexer.token_start_position =
        ts_length_add(parser->lexer.current_position, node->padding);
    parser->lexer.token_end_position = parser->lexer.current_position =
        ts_length_add(parser->lexer.token_start_position, node->size);

    parser->lexer.lookahead = 0;
    parser->lexer.lookahead_size = 0;
    parser->lexer.advance_fn(&parser->lexer, 0);
  } else {
    node = parser->language->lex_fn(&parser->lexer, lex_state);
  }

  return node;
}

/*
 *  Parse Actions
 */

static void shift(TSParser *parser, int head, TSStateId parse_state) {
  ts_parse_stack_push(parser->stack, head, parse_state, parser->lookahead);
}

static void shift_extra(TSParser *parser, int head, TSStateId state) {
  ts_tree_set_extra(parser->lookahead);
  shift(parser, head, state);
}

static TSTree * reduce_helper(TSParser *parser, int head, TSSymbol symbol, size_t child_count, bool extra, bool count_extra) {
  bool hidden = parser->language->hidden_symbol_flags[symbol];
  ParseStackPopResultList pop_results = ts_parse_stack_pop(parser->stack, head, child_count, count_extra);

  TSTree *parent = NULL;
  TSTree **last_children = NULL;
  int last_index = -1;

  for (int i = 0; i < pop_results.size; i++) {
    ParseStackPopResult pop_result = pop_results.contents[i];

    if (pop_result.trees != last_children) {
      parent = ts_tree_make_node(symbol, pop_result.tree_count, pop_result.trees, hidden);
    }

    if (pop_result.index == last_index) {
      ts_parse_stack_add_alternative(parser->stack, pop_result.index, parent);
    } else {
      TSStateId top_state = ts_parse_stack_top_state(parser->stack, pop_result.index);
      TSStateId state;

      if (extra) {
        ts_tree_set_extra(parent);
        state = top_state;
      } else {
        state = get_action(parser->language, top_state, symbol).data.to_state;
      }

      ts_parse_stack_push(parser->stack, pop_result.index, state, parent);
    }

    last_index = pop_result.index;
    last_children = pop_result.trees;
  }

  return parent;
}

static void reduce(TSParser *parser, int head, TSSymbol symbol, size_t child_count) {
  reduce_helper(parser, head, symbol, child_count, false, false);
}

static void reduce_extra(TSParser *parser, int head, TSSymbol symbol) {
  reduce_helper(parser, head, symbol, 1, true, false);
}

static void reduce_fragile(TSParser *parser, int head, TSSymbol symbol, size_t child_count) {
  TSTree *reduced = reduce_helper(parser, head, symbol, child_count, false, false);
  ts_tree_set_fragile_left(reduced);
  ts_tree_set_fragile_right(reduced);
}

static void reduce_error(TSParser *parser, int head, size_t child_count) {
  TSTree *reduced = reduce_helper(parser, head, ts_builtin_sym_error, child_count, false, true);
  reduced->size = ts_length_add(reduced->size, parser->lookahead->padding);
  parser->lookahead->padding = ts_length_zero();
  ts_tree_set_fragile_left(reduced);
  ts_tree_set_fragile_right(reduced);
}

static bool handle_error(TSParser *parser, int head) {
  size_t error_token_count = 1;
  ParseStackEntry *entry_before_error = ts_parse_stack_head(parser->stack, head);

  for (;;) {

    /*
     *  Unwind the parse stack until a state is found in which an error is
     *  expected and the current lookahead token is expected afterwards.
     */
    int i = -1;
    for (ParseStackEntry *entry = entry_before_error;
         entry != NULL;
         entry = ts_parse_stack_entry_next(entry, head), i++) {
      TSStateId stack_state = entry->state;
      TSParseAction action_on_error = get_action(
        parser->language, stack_state, ts_builtin_sym_error);

      if (action_on_error.type == TSParseActionTypeShift) {
        TSStateId state_after_error = action_on_error.data.to_state;
        TSParseAction action_after_error = get_action(
            parser->language, state_after_error, parser->lookahead->symbol);

        if (action_after_error.type != TSParseActionTypeError) {
          DEBUG("recover state:%u, count:%lu", state_after_error, error_token_count + i);
          reduce_error(parser, head, error_token_count + i);
          return true;
        }
      }
    }

    /*
     *  If there is no state in the stack for which we can recover with the
     *  current lookahead token, advance to the next token.
     */
    DEBUG("skip token:%s", SYM_NAME(parser->lookahead->symbol));
    shift(parser, head, ts_parse_stack_top_state(parser->stack, head));
    parser->lookahead = get_next_node(parser, ts_lex_state_error);
    error_token_count++;

    /*
     *  If the end of input is reached, exit.
     */
    if (parser->lookahead->symbol == ts_builtin_sym_end) {
      DEBUG("fail_to_recover");
      reduce_error(parser, head, error_token_count - 1);
      return false;
    }
  }
}

static TSTree *finish(TSParser *parser) {
  return reduce_helper(parser, 0, ts_builtin_sym_document, -1, false, true);
}

/*
 *  Public
 */

TSTree * ts_parser_select_tree(void *data, TSTree *left, TSTree *right) {
  return left;
}

TSParser ts_parser_make() {
  return (TSParser) { .lexer = ts_lexer_make(),
                      .stack = ts_parse_stack_new((TreeSelectionCallback) {NULL, ts_parser_select_tree}),
                      .right_stack = ts_stack_make() };
}

void ts_parser_destroy(TSParser *parser) {
  ts_parse_stack_delete(parser->stack);
  ts_stack_delete(&parser->right_stack);

  if (parser->lookahead)
    ts_tree_release(parser->lookahead);

  if (parser->lexer.debugger.release_fn)
    parser->lexer.debugger.release_fn(parser->lexer.debugger.data);
}

TSDebugger ts_parser_get_debugger(const TSParser *parser) {
  return parser->lexer.debugger;
}

void ts_parser_set_debugger(TSParser *parser, TSDebugger debugger) {
  if (parser->lexer.debugger.release_fn)
    parser->lexer.debugger.release_fn(parser->lexer.debugger.data);
  parser->lexer.debugger = debugger;
}

typedef enum {
  ParserNextResultNone,
  ParserNextResultAdvanced,
  ParserNextResultRemoved,
  ParserNextResultFinished
} ParserNextResult;

ParserNextResult ts_parser_next(TSParser *parser, int head_to_advance) {
  TSStateId state = ts_parse_stack_top_state(parser->stack, head_to_advance);
  const TSParseAction *next_action = get_actions(parser->language, state, parser->lookahead->symbol);
  int head, next_head = head_to_advance;

  ParserNextResult result = ParserNextResultNone;

  while (next_action) {
    TSParseAction action = *next_action;
    head = next_head;

    next_action++;
    if (next_action->type == 0) {
      next_action = NULL;
    } else {
      next_head = ts_parse_stack_split(parser->stack, head);
      DEBUG("split head:%d, created:%d", head, next_head);
    }

    DEBUG("iteration state:%d, head:%d", state, head);

    // TODO: Remove this by making a separate symbol for errors returned from
    // the lexer.
    if (parser->lookahead->symbol == ts_builtin_sym_error)
      action.type = TSParseActionTypeError;

    switch (action.type) {
      case TSParseActionTypeError:
        DEBUG("error_sym");
        if (ts_parse_stack_head_count(parser->stack) == 1) {
          if (handle_error(parser, head))
            break;
          else
            return ParserNextResultFinished;
        } else {
          DEBUG("bail head:%d", head);
          ts_parse_stack_remove_head(parser->stack, head);
          return ParserNextResultRemoved;
        }

      case TSParseActionTypeShift:
        DEBUG("shift state:%u", action.data.to_state);
        shift(parser, head, action.data.to_state);
        result = ParserNextResultAdvanced;
        break;

      case TSParseActionTypeShiftExtra:
        DEBUG("shift_extra");
        shift_extra(parser, head, state);
        result = ParserNextResultAdvanced;
        break;

      case TSParseActionTypeReduce:
        DEBUG("reduce sym:%s, count:%u", SYM_NAME(action.data.symbol), action.data.child_count);
        reduce(parser, head, action.data.symbol, action.data.child_count);
        break;

      case TSParseActionTypeReduceExtra:
        DEBUG("reduce_extra sym:%s", SYM_NAME(action.data.symbol));
        reduce_extra(parser, head, action.data.symbol);
        break;

      case TSParseActionTypeReduceFragile:
        DEBUG("reduce_fragile sym:%s, count:%u", SYM_NAME(action.data.symbol), action.data.child_count);
        reduce_fragile(parser, head, action.data.symbol, action.data.child_count);
        break;

      case TSParseActionTypeAccept:
        DEBUG("accept");
        return ParserNextResultFinished;
    }
  }

  return result;
}

const TSTree *ts_parser_parse(TSParser *parser, TSInput input,
                              TSInputEdit *edit) {
  TSLength position;
  if (edit) {
    DEBUG("edit pos:%lu, inserted:%lu, deleted:%lu", edit->position,
          edit->chars_inserted, edit->chars_removed);
    position = break_down_left_stack(parser, *edit);
  } else {
    DEBUG("new_parse");
    ts_parse_stack_clear(parser->stack);
    position = ts_length_zero();
  }

  parser->lexer.input = input;
  ts_lexer_reset(&parser->lexer, position);

  for (;;) {
    TSStateId state = ts_parse_stack_top_state(parser->stack, 0);
    parser->lookahead = get_next_node(parser, parser->language->lex_states[state]);

    DEBUG("lookahead sym:%s", SYM_NAME(parser->lookahead->symbol));
    DEBUG("head_count: %d", ts_parse_stack_head_count(parser->stack));

    int head = 0;
    while (head < ts_parse_stack_head_count(parser->stack)) {
      bool removed = false, advanced = false;

      while (!(advanced || removed)) {
        switch (ts_parser_next(parser, head)) {
          case ParserNextResultNone:
            break;
          case ParserNextResultRemoved:
            removed = true;
            break;
          case ParserNextResultAdvanced:
            advanced = true;
            break;
          case ParserNextResultFinished:
            return finish(parser);
        }
      }

      if (!removed)
        head++;
    }
  }
}
