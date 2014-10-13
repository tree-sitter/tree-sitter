#include <stdio.h>
#include <stdbool.h>
#include "tree_sitter/runtime.h"
#include "tree_sitter/parser.h"
#include "runtime/tree.h"
#include "runtime/lexer.h"
#include "runtime/stack.h"
#include "runtime/parser.h"
#include "runtime/length.h"

/*
 *  Private
 */

#define DEBUG_PARSE(...)                                                     \
  if (parser->debugger.debug_fn) {                                           \
    snprintf(parser->lexer.debug_buffer, TS_DEBUG_BUFFER_SIZE, __VA_ARGS__); \
    parser->debugger.debug_fn(parser->debugger.data,                         \
                              parser->lexer.debug_buffer);                   \
  }

static TSParseAction action_for(const TSLanguage *lang, TSStateId state,
                                TSSymbol sym) {
  return (lang->parse_table + (state * lang->symbol_count))[sym];
}

static size_t breakdown_right_stack(TSParser *parser, TSLength cur_position,
                                    TSStateId state) {
  TSStack *stack = &parser->right_stack;
  size_t right_subtree_start =
      parser->total_chars - ts_stack_total_tree_size(stack).chars;

  for (;;) {
    TSTree *node = ts_stack_top_node(stack);
    if (!node)
      break;

    if (right_subtree_start > cur_position.chars)
      break;

    bool can_be_used = action_for(parser->language, state, node->symbol).type !=
                       TSParseActionTypeError;
    if (right_subtree_start == cur_position.chars && can_be_used)
      break;

    size_t child_count;
    TSTree **children = ts_tree_children(node, &child_count);

    DEBUG_PARSE("pop_right %s", parser->language->symbol_names[node->symbol]);
    stack->size--;
    right_subtree_start += ts_tree_total_size(node).chars;

    for (size_t i = child_count - 1; i + 1 > 0; i--) {
      TSTree *child = children[i];

      if (right_subtree_start > cur_position.chars) {
        DEBUG_PARSE("push_right %s",
                    parser->language->symbol_names[child->symbol]);
        ts_stack_push(stack, 0, child);
        right_subtree_start -= ts_tree_total_size(child).chars;
      } else {
        break;
      }
    }

    ts_tree_release(node);
  }

  return right_subtree_start;
}

static TSLength breakdown_stack(TSParser *parser, TSInputEdit *edit) {
  ts_stack_shrink(&parser->right_stack, 0);

  if (!edit) {
    ts_stack_shrink(&parser->stack, 0);
    return ts_length_zero();
  }

  TSLength prev_size = ts_stack_total_tree_size(&parser->stack);
  parser->total_chars =
      prev_size.chars + edit->chars_inserted - edit->chars_removed;
  TSLength left_subtree_end = prev_size;
  size_t right_subtree_start = parser->total_chars;

  for (;;) {
    TSTree *node = ts_stack_top_node(&parser->stack);
    if (!node)
      break;

    size_t child_count;
    TSTree **children = ts_tree_children(node, &child_count);
    if (left_subtree_end.chars < edit->position && !children)
      break;

    DEBUG_PARSE("pop_left sym: %s",
                parser->language->symbol_names[node->symbol]);
    parser->stack.size--;
    left_subtree_end = ts_length_sub(left_subtree_end, ts_tree_total_size(node));

    size_t i = 0;
    for (; i < child_count && left_subtree_end.chars < edit->position; i++) {
      TSTree *child = children[i];
      TSStateId state = ts_stack_top_state(&parser->stack);
      TSParseAction action = action_for(parser->language, state, child->symbol);
      TSStateId next_state =
          action.type == TSParseActionTypeShift ? action.data.to_state : state;

      DEBUG_PARSE("push_left sym: %s",
                  parser->language->symbol_names[child->symbol]);
      ts_stack_push(&parser->stack, next_state, child);
      left_subtree_end =
          ts_length_add(left_subtree_end, ts_tree_total_size(child));
    }

    for (size_t j = child_count - 1; j + 1 > i; j--) {
      TSTree *child = children[j];
      right_subtree_start -= ts_tree_total_size(child).chars;
      if (right_subtree_start < edit->position + edit->chars_inserted)
        break;

      DEBUG_PARSE("push_right sym: %s",
                  parser->language->symbol_names[child->symbol]);
      ts_stack_push(&parser->right_stack, 0, child);
    }

    ts_tree_release(node);
  }

  DEBUG_PARSE("reuse_left chars:%lu", left_subtree_end.chars);
  return left_subtree_end;
}

static void lex(TSParser *parser, TSStateId lex_state) {
  TSStateId state = ts_stack_top_state(&parser->stack);
  size_t node_position =
      breakdown_right_stack(parser, parser->lexer.current_position, state);
  TSTree *node = ts_stack_top_node(&parser->right_stack);
  if (node && node_position == parser->lexer.current_position.chars) {
    ts_stack_shrink(&parser->right_stack, parser->right_stack.size - 1);
    parser->lexer.lookahead = 0;
    parser->lexer.lookahead_size = 0;

    parser->lookahead = node;
    parser->lexer.current_position =
        ts_length_add(parser->lexer.current_position, ts_tree_total_size(node));
    DEBUG_PARSE("reuse_right sym:%s",
                parser->language->symbol_names[node->symbol]);
  } else {
    parser->lookahead = parser->language->lex_fn(&parser->lexer, lex_state);
    DEBUG_PARSE("lex sym:%s",
                parser->language->symbol_names[parser->lookahead->symbol]);
  }
}

static void resize_error(TSParser *parser, TSTree *error) {
  error->size =
      ts_length_sub(ts_length_sub(parser->lexer.token_start_position,
                                  ts_stack_total_tree_size(&parser->stack)),
                    error->padding);
}

/*
 *  Parse Actions
 */

static void shift(TSParser *parser, TSStateId parse_state) {
  DEBUG_PARSE("shift state:%d", parse_state);

  if (ts_tree_is_extra(parser->lookahead))
    parse_state = ts_stack_top_state(&parser->stack);

  ts_stack_push(&parser->stack, parse_state, parser->lookahead);
  parser->lookahead = parser->next_lookahead;
  parser->next_lookahead = NULL;
}

static void shift_extra(TSParser *parser) {
  DEBUG_PARSE("shift_extra");

  ts_tree_set_extra(parser->lookahead);
  shift(parser, 0);
}

static void reduce(TSParser *parser, TSSymbol symbol, size_t child_count) {
  DEBUG_PARSE("reduce sym:%s count:%lu", parser->language->symbol_names[symbol],
              child_count);

  TSStack *stack = &parser->stack;
  parser->next_lookahead = parser->lookahead;

  /*
   *  Walk down the stack to determine which symbols will be reduced.
   *  The child node count is known ahead of time, but some children
   *  may be ubiquitous tokens, which don't count.
   */
  for (size_t i = 0; i < child_count; i++) {
    if (child_count == stack->size)
      break;
    TSTree *child = stack->entries[stack->size - 1 - i].node;
    if (ts_tree_is_extra(child))
      child_count++;
  }

  size_t start_index = stack->size - child_count;
  TSTree **children = calloc(child_count, sizeof(TSTree *));
  for (size_t i = 0; i < child_count; i++)
    children[i] = stack->entries[start_index + i].node;

  int hidden = parser->language->hidden_symbol_flags[symbol];
  parser->lookahead = ts_tree_make_node(symbol, child_count, children, hidden);
  ts_stack_shrink(stack, stack->size - child_count);
}

static void reduce_extra(TSParser *parser, TSSymbol symbol) {
  DEBUG_PARSE("reduce_extra");
  reduce(parser, symbol, 1);
  ts_tree_set_extra(parser->lookahead);
}

static int handle_error(TSParser *parser) {
  TSTree *error = parser->lookahead;
  ts_tree_retain(error);

  for (;;) {

    /*
     *  Unwind the parse stack until a state is found in which an error is
     *  expected and the current lookahead token is expected afterwards.
     */
    TS_STACK_FROM_TOP(parser->stack, entry) {
      TSStateId stack_state = entry->state;
      TSParseAction action_on_error =
          action_for(parser->language, stack_state, ts_builtin_sym_error);

      if (action_on_error.type == TSParseActionTypeShift) {
        TSStateId state_after_error = action_on_error.data.to_state;
        TSParseAction action_after_error = action_for(
            parser->language, state_after_error, parser->lookahead->symbol);

        if (action_after_error.type != TSParseActionTypeError) {
          DEBUG_PARSE("recover state:%u", state_after_error);

          ts_stack_shrink(&parser->stack, entry - parser->stack.entries + 1);
          parser->lookahead->padding = ts_length_zero();

          resize_error(parser, error);
          ts_stack_push(&parser->stack, state_after_error, error);
          ts_tree_release(error);
          return 1;
        }
      }
    }

    /*
     *  If there is no state in the stack for which we can recover with the
     *  current lookahead token, advance to the next token. If no characters
     *  were consumed, advance the lexer to the next character.
     */
    DEBUG_PARSE("lex_again");
    TSLength prev_position = parser->lexer.current_position;
    if (parser->lookahead)
      ts_tree_release(parser->lookahead);
    lex(parser, ts_lex_state_error);

    /*
     *  If the current lookahead character cannot be the start of any token,
     *  just skip it. If the end of input is reached, exit.
     */
    if (ts_length_eq(parser->lexer.current_position, prev_position))
      if (!ts_lexer_advance(&parser->lexer)) {
        DEBUG_PARSE("fail_to_recover");

        resize_error(parser, error);
        ts_stack_push(&parser->stack, 0, error);
        ts_tree_release(error);
        return 0;
      }
  }
}

static TSTree *finish(TSParser *parser) {
  DEBUG_PARSE("finish");

  if (parser->stack.size == 0)
    ts_stack_push(&parser->stack, 0,
                  ts_tree_make_error(ts_length_zero(), ts_length_zero(), 0));

  reduce(parser, ts_builtin_sym_document, parser->stack.size);
  parser->lookahead->options = 0;
  shift(parser, 0);
  return parser->stack.entries[0].node;
}

/*
 *  Public
 */

TSParser ts_parser_make() {
  return (TSParser) { .lexer = ts_lexer_make(),
                      .stack = ts_stack_make(),
                      .right_stack = ts_stack_make(),
                      .debugger = (TSDebugger) {} };
}

void ts_parser_destroy(TSParser *parser) {
  ts_stack_delete(&parser->stack);
  ts_stack_delete(&parser->right_stack);

  if (parser->lookahead)
    ts_tree_release(parser->lookahead);
  if (parser->next_lookahead)
    ts_tree_release(parser->next_lookahead);

  if (parser->debugger.release_fn)
    parser->debugger.release_fn(parser->debugger.data);
  if (parser->lexer.debugger.release_fn)
    parser->lexer.debugger.release_fn(parser->lexer.debugger.data);
}

void ts_parser_debug_parse(TSParser *parser, TSDebugger debugger) {
  TSDebugger old_debugger = parser->debugger;
  if (old_debugger.release_fn)
    old_debugger.release_fn(old_debugger.data);
  parser->debugger = debugger;
}

void ts_parser_debug_lex(TSParser *parser, TSDebugger debugger) {
  TSDebugger old_debugger = parser->lexer.debugger;
  if (old_debugger.release_fn)
    old_debugger.release_fn(old_debugger.data);
  parser->lexer.debugger = debugger;
}

const TSTree *ts_parser_parse(TSParser *parser, TSInput input,
                              TSInputEdit *edit) {
  parser->lookahead = NULL;
  parser->next_lookahead = NULL;
  TSLength position = breakdown_stack(parser, edit);

  parser->lexer.input = input;
  ts_lexer_reset(&parser->lexer, position);

  for (;;) {
    TSStateId state = ts_stack_top_state(&parser->stack);
    if (!parser->lookahead)
      lex(parser, parser->language->lex_states[state]);
    TSParseAction action =
        action_for(parser->language, state, parser->lookahead->symbol);

    switch (action.type) {
      case TSParseActionTypeShift:
        if (parser->lookahead->symbol == ts_builtin_sym_error) {
          if (!handle_error(parser))
            return finish(parser);
        } else {
          shift(parser, action.data.to_state);
        }
        break;

      case TSParseActionTypeShiftExtra:
        shift_extra(parser);
        break;

      case TSParseActionTypeReduce:
        reduce(parser, action.data.symbol, action.data.child_count);
        break;

      case TSParseActionTypeReduceExtra:
        reduce_extra(parser, action.data.symbol);
        break;

      case TSParseActionTypeAccept:
        return finish(parser);

      case TSParseActionTypeError:
        if (!handle_error(parser))
          return finish(parser);
        break;

      default:
        return NULL;
    }
  }
}
