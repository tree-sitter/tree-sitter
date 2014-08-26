#include <stdio.h>
#include "tree_sitter/runtime.h"
#include "tree_sitter/parser.h"
#include "runtime/tree.h"
#include "runtime/lexer.h"
#include "runtime/stack.h"
#include "runtime/parser.h"

static const TSParseAction *actions_for_state(const TSLanguage *language,
                                              TSStateId state) {
  return language->parse_table + (state * language->symbol_count);
}

static size_t breakdown_stack(TSParser *parser, TSInputEdit *edit) {
  if (!edit)
    return 0;

  TSStack *stack = &parser->stack;
  size_t position = 0;

  for (;;) {
    TSTree *node = ts_stack_top_node(stack);
    if (!node)
      break;

    position = ts_stack_right_position(stack);
    size_t child_count;
    TSTree **children = ts_tree_children(node, &child_count);
    if (position <= edit->position && !children)
      break;

    stack->size--;
    position -= ts_tree_total_size(node);

    for (size_t i = 0; i < child_count && position < edit->position; i++) {
      TSTree *child = children[i];
      TSStateId state = ts_stack_top_state(stack);
      TSStateId next_state = actions_for_state(
          parser->language, state)[child->symbol].data.to_state;
      ts_stack_push(stack, next_state, child);
      ts_tree_retain(child);
      position += ts_tree_total_size(child);
    }

    ts_tree_release(node);
  }

  return position;
}

static TSSymbol *expected_symbols(TSParser *parser, size_t *count) {
  *count = 0;
  const TSParseAction *actions =
      actions_for_state(parser->language, ts_stack_top_state(&parser->stack));
  for (size_t i = 0; i < parser->language->symbol_count; i++)
    if (actions[i].type != TSParseActionTypeError)
      (*count)++;

  size_t n = 0;
  TSSymbol *result = malloc(*count * sizeof(*result));
  for (TSSymbol i = 0; i < parser->language->symbol_count; i++)
    if (actions[i].type != TSParseActionTypeError)
      result[n++] = i;

  return result;
}

static void shift(TSParser *parser, TSStateId parse_state) {
  if (ts_tree_is_extra(parser->lookahead))
    parse_state = ts_stack_top_state(&parser->stack);
  ts_stack_push(&parser->stack, parse_state, parser->lookahead);
  parser->lookahead = parser->next_lookahead;
  parser->next_lookahead = NULL;
}

static void shift_extra(TSParser *parser) {
  ts_tree_set_extra(parser->lookahead);
  shift(parser, 0);
}

static void reduce(TSParser *parser, TSSymbol symbol, size_t child_count) {
  TSStack *stack = &parser->stack;
  parser->next_lookahead = parser->lookahead;

  // Walk down the stack to determine which symbols will be reduced.
  // The child node count is known ahead of time, but some children
  // may be ubiquitous tokens, which don't count.
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

static int reduce_extra(TSParser *parser, TSSymbol symbol) {
  TSTree *top_node = ts_stack_top_node(&parser->stack);
  if (top_node->symbol == symbol && !ts_tree_is_extra(top_node)) {
    reduce(parser, symbol, 1);
    ts_tree_set_extra(parser->lookahead);
    return 1;
  } else {
    return 0;
  }
}

static int handle_error(TSParser *parser) {
  size_t count = 0;
  const TSSymbol *inputs = expected_symbols(parser, &count);
  TSTree *error = ts_tree_make_error(ts_lexer_lookahead_char(&parser->lexer),
                                     count, inputs, 0, 0);

  for (;;) {
    ts_tree_release(parser->lookahead);
    size_t position = ts_lexer_position(&parser->lexer);
    parser->lookahead =
        parser->language->lex_fn(&parser->lexer, ts_lex_state_error);

    int at_end = 0;
    if (ts_lexer_position(&parser->lexer) == position)
      at_end = !ts_lexer_advance(&parser->lexer);

    if (at_end || parser->lookahead->symbol == ts_builtin_sym_end) {
      ts_stack_push(&parser->stack, 0, error);
      return 0;
    }

    /*
     *  Unwind the stack, looking for a state in which this token
     *  may appear after an error.
     */
    for (size_t j = 0; j < parser->stack.size; j++) {
      size_t i = parser->stack.size - 1 - j;
      TSStateId stack_state = parser->stack.entries[i].state;
      TSParseAction action_on_error = actions_for_state(
          parser->language, stack_state)[ts_builtin_sym_error];
      if (action_on_error.type == TSParseActionTypeShift) {
        TSStateId state_after_error = action_on_error.data.to_state;
        if (actions_for_state(parser->language,
                              state_after_error)[parser->lookahead->symbol]
                .type != TSParseActionTypeError) {
          ts_stack_shrink(&parser->stack, i + 1);
          ts_stack_push(&parser->stack, state_after_error, error);
          return 1;
        }
      }
    }
  }
}

static TSTree *get_root(TSParser *parser) {
  if (parser->stack.size == 0)
    return NULL;

  reduce(parser, ts_builtin_sym_document, parser->stack.size);
  parser->lookahead->options = 0;
  shift(parser, 0);
  return parser->stack.entries[0].node;
}

static TSParseAction next_action(TSParser *parser) {
  TSStateId state = ts_stack_top_state(&parser->stack);
  if (!parser->lookahead)
    parser->lookahead = parser->language->lex_fn(
        &parser->lexer, parser->language->lex_states[state]);
  return actions_for_state(parser->language, state)[parser->lookahead->symbol];
}

TSParser ts_parser_make(const TSLanguage *language) {
  return (TSParser) { .lexer = ts_lexer_make(),
                      .stack = ts_stack_make(),
                      .debug = 0,
                      .language = language, };
}

void ts_parser_destroy(TSParser *parser) {
  if (parser->lookahead)
    ts_tree_release(parser->lookahead);
  if (parser->next_lookahead)
    ts_tree_release(parser->next_lookahead);
  ts_stack_delete(&parser->stack);
}

#define DEBUG_PARSE(...)          \
  if (parser->debug) {            \
    fprintf(stderr, __VA_ARGS__); \
    fprintf(stderr, "\n");        \
  }

const TSTree *ts_parser_parse(TSParser *parser, TSInput input,
                              TSInputEdit *edit) {
  if (!edit)
    ts_stack_shrink(&parser->stack, 0);

  parser->lookahead = NULL;
  parser->next_lookahead = NULL;
  parser->lexer = ts_lexer_make();
  parser->lexer.input = input;

  input.seek_fn(input.data, breakdown_stack(parser, edit));
  ts_lexer_advance(&parser->lexer);

  for (;;) {
    TSParseAction action = next_action(parser);
    DEBUG_PARSE("LOOKAHEAD %s",
                parser->language->symbol_names[parser->lookahead->symbol]);

    switch (action.type) {
      case TSParseActionTypeShift:
        DEBUG_PARSE("SHIFT %d", action.data.to_state);
        shift(parser, action.data.to_state);
        break;

      case TSParseActionTypeShiftExtra:
        DEBUG_PARSE("SHIFT EXTRA");
        shift_extra(parser);
        break;

      case TSParseActionTypeReduce:
        DEBUG_PARSE("REDUCE %s %d",
                    parser->language->symbol_names[action.data.symbol],
                    action.data.child_count);
        reduce(parser, action.data.symbol, action.data.child_count);
        break;

      case TSParseActionTypeReduceExtra:
        if (!reduce_extra(parser, action.data.symbol)) {
          DEBUG_PARSE("ERROR");
          if (!handle_error(parser))
            return get_root(parser);
        }
        DEBUG_PARSE("REDUCE EXTRA");
        break;

      case TSParseActionTypeAccept:
        DEBUG_PARSE("ACCEPT");
        return get_root(parser);

      case TSParseActionTypeError:
        if (!handle_error(parser))
          return get_root(parser);
        break;

      default:
        return NULL;
    }
  }
}
