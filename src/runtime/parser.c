#include <stdio.h>
#include "tree_sitter/runtime.h"
#include "tree_sitter/parser.h"
#include "runtime/tree.h"
#include "runtime/lexer.h"
#include "runtime/stack.h"
#include "runtime/parser.h"

#define DEBUG_PARSE(...)                   \
  if (parser->debug) {                     \
    fprintf(stderr, "PARSE " __VA_ARGS__); \
    fprintf(stderr, "\n");                 \
  }

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

static TSTree *build_error_node(TSParser *parser) {
  unsigned char lookahead = ts_lexer_lookahead_char(&parser->lexer);
  return ts_tree_make_error(0, 0, lookahead);
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

static int reduce_extra(TSParser *parser, TSSymbol symbol) {
  TSTree *last_node = NULL;
  TS_STACK_FROM_TOP(parser->stack, entry, i) {
    if (!ts_tree_is_extra(entry->node)) {
      last_node = entry->node;
      break;
    }
  }

  if (last_node && last_node->symbol == symbol) {
    reduce(parser, symbol, 1);
    ts_tree_set_extra(parser->lookahead);
    return 1;
  } else {
    return 0;
  }
}

static void lex(TSParser *parser, TSStateId lex_state) {
  if (parser->lookahead)
    ts_tree_release(parser->lookahead);
  parser->lookahead = parser->language->lex_fn(&parser->lexer, lex_state);
}

static int handle_error(TSParser *parser) {
  TSTree *error = parser->lookahead;
  ts_tree_retain(error);
  size_t last_token_end = parser->lexer.token_end_position;

  for (;;) {

    /*
     *  Unwind the parse stack until a state is found in which an error is
     *  expected and the current lookahead token is expected afterwards.
     */
    size_t error_start = last_token_end;
    TS_STACK_FROM_TOP(parser->stack, entry, i) {
      TSStateId state = entry->state;
      TSParseAction action_on_error =
          actions_for_state(parser->language, state)[ts_builtin_sym_error];

      if (action_on_error.type == TSParseActionTypeShift) {
        TSStateId state_after_error = action_on_error.data.to_state;
        TSParseAction action_after_error = actions_for_state(
            parser->language, state_after_error)[parser->lookahead->symbol];

        if (action_after_error.type != TSParseActionTypeError) {
          DEBUG_PARSE("RECOVER %u", state_after_error);
          error->size += ts_lexer_position(&parser->lexer) - 1 - error_start;
          ts_stack_shrink(&parser->stack, i + 1);
          ts_stack_push(&parser->stack, state_after_error, error);
          ts_tree_release(error);
          return 1;
        }
      }

      TSTree *removed_tree = entry->node;
      error_start -= ts_tree_total_size(removed_tree);
    }

    /*
     *  If there is no state in the stack for which we can recover with the
     *  current lookahead token, advance to the next token. If no characters
     *  were consumed, advance the lexer to the next character.
     */
    size_t prev_position = ts_lexer_position(&parser->lexer);
    lex(parser, ts_lex_state_error);
    parser->lookahead->padding = 0;
    if (ts_lexer_position(&parser->lexer) == prev_position)
      if (!ts_lexer_advance(&parser->lexer)) {
        DEBUG_PARSE("FAIL TO RECOVER");
        ts_stack_push(&parser->stack, 0, error);
        ts_tree_release(error);
        return 0;
      }
  }
}

static TSTree *get_root(TSParser *parser) {
  if (parser->stack.size == 0)
    ts_stack_push(&parser->stack, 0, build_error_node(parser));

  reduce(parser, ts_builtin_sym_document, parser->stack.size);
  parser->lookahead->options = 0;
  shift(parser, 0);
  return parser->stack.entries[0].node;
}

static TSParseAction next_action(TSParser *parser) {
  TSStateId state = ts_stack_top_state(&parser->stack);
  if (!parser->lookahead)
    lex(parser, parser->language->lex_states[state]);
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
        if (parser->lookahead->symbol == ts_builtin_sym_error) {
          if (!handle_error(parser))
            return get_root(parser);
        } else {
          DEBUG_PARSE("SHIFT %d", action.data.to_state);
          shift(parser, action.data.to_state);
        }
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
        DEBUG_PARSE("ERROR");
        if (!handle_error(parser))
          return get_root(parser);
        break;

      default:
        return NULL;
    }
  }
}
