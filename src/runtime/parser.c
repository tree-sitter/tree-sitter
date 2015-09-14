#include <stdio.h>
#include <stdbool.h>
#include "tree_sitter/runtime.h"
#include "tree_sitter/parser.h"
#include "runtime/tree.h"
#include "runtime/lexer.h"
#include "runtime/parser.h"
#include "runtime/length.h"
#include "runtime/debugger.h"

/*
 *  Debugging
 */

#define DEBUG(...)                                                           \
  if (parser->lexer.debugger.debug_fn) {                                     \
    snprintf(parser->lexer.debug_buffer, TS_DEBUG_BUFFER_SIZE, __VA_ARGS__); \
    parser->lexer.debugger.debug_fn(parser->lexer.debugger.payload,          \
                                    TSDebugTypeParse,                        \
                                    parser->lexer.debug_buffer);             \
  }

#define SYM_NAME(sym) parser->language->symbol_names[sym]

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

static TSParseAction ts_language__action(const TSLanguage *language,
                                         TSStateId state, TSSymbol sym) {
  return ts_language__actions(language, state, sym)[0];
}

/*
 *  Replace parser's reusable_subtree with its first non-fragile descendant.
 *  Return true if a suitable descendant is found, false otherwise.
 */
static bool ts_parser__breakdown_reusable_subtree(TSParser *parser) {
  do {
    if (parser->reusable_subtree->symbol == ts_builtin_sym_error)
      return false;
    if (parser->reusable_subtree->child_count == 0)
      return false;
    parser->reusable_subtree = parser->reusable_subtree->children[0];
  } while (ts_tree_is_fragile(parser->reusable_subtree));
  return true;
}

/*
 *  Replace the parser's reusable_subtree with its largest right neighbor, or
 *  NULL if no right neighbor exists.
 */
static void ts_parser__pop_reusable_subtree(TSParser *parser) {
  parser->reusable_subtree_pos +=
    ts_tree_total_size(parser->reusable_subtree).chars;

  while (parser->reusable_subtree) {
    TSTree *parent = parser->reusable_subtree->context.parent;
    size_t next_index = parser->reusable_subtree->context.index + 1;
    if (parent && parent->child_count > next_index) {
      parser->reusable_subtree = parent->children[next_index];
      return;
    }
    parser->reusable_subtree = parent;
  }
}

/*
 *  Advance the parser's lookahead subtree. If there is a reusable subtree
 *  at the correct position in the parser's previous tree, use that. Otherwise,
 *  run the lexer.
 */
static void ts_parser__get_next_lookahead(TSParser *parser, bool error_mode) {
  while (!error_mode && parser->reusable_subtree) {
    if (parser->reusable_subtree_pos > parser->lexer.current_position.chars) {
      break;
    }

    if (parser->reusable_subtree_pos < parser->lexer.current_position.chars) {
      DEBUG("past_reuse sym:%s", SYM_NAME(parser->reusable_subtree->symbol));
      ts_parser__pop_reusable_subtree(parser);
      continue;
    }

    if (ts_tree_has_changes(parser->reusable_subtree) ||
        ts_tree_is_fragile(parser->reusable_subtree) ||
        ts_tree_is_extra(parser->reusable_subtree)) {
      DEBUG("breakdown sym:%s", SYM_NAME(parser->reusable_subtree->symbol));
      if (!ts_parser__breakdown_reusable_subtree(parser)) {
        DEBUG("cant_reuse sym:%s", SYM_NAME(parser->reusable_subtree->symbol));
        ts_parser__pop_reusable_subtree(parser);
      }
      continue;
    }

    TSStateId top_state = ts_parse_stack_top_state(parser->stack, 0);
    TSSymbol symbol = parser->reusable_subtree->symbol;
    if (ts_language__action(parser->language, top_state, symbol).type ==
        TSParseActionTypeError) {
      ts_parser__pop_reusable_subtree(parser);
      continue;
    }

    parser->lookahead = parser->reusable_subtree;
    TSLength size = ts_tree_total_size(parser->lookahead);
    DEBUG("reuse sym:%s size:%lu extra:%d", SYM_NAME(parser->lookahead->symbol),
          size.chars, parser->lookahead->options.extra);
    ts_lexer_reset(&parser->lexer,
                   ts_length_add(parser->lexer.current_position, size));
    ts_parser__pop_reusable_subtree(parser);
    return;
  }

  TSStateId lex_state =
    error_mode
      ? ts_lex_state_error
      : parser->language->lex_states[ts_parse_stack_top_state(parser->stack, 0)];

  parser->lookahead = parser->language->lex_fn(&parser->lexer, lex_state);
}

/*
 *  Parse Actions
 */

static void ts_parser__shift(TSParser *parser, int head, TSStateId parse_state) {
  ts_parse_stack_push(parser->stack, head, parse_state, parser->lookahead);
}

static void ts_parser__shift_extra(TSParser *parser, int head, TSStateId state) {
  ts_tree_set_extra(parser->lookahead);
  ts_parser__shift(parser, head, state);
}

static TSTree *ts_parser__reduce(TSParser *parser, int head, TSSymbol symbol,
                                 size_t child_count, bool extra,
                                 bool count_extra) {
  TSNodeType node_type = parser->language->node_types[symbol];
  ParseStackPopResultList pop_results =
    ts_parse_stack_pop(parser->stack, head, child_count, count_extra);

  TSTree *parent = NULL;
  TSTree **last_children = NULL;
  int last_index = -1;

  for (int i = 0; i < pop_results.size; i++) {
    ParseStackPopResult pop_result = pop_results.contents[i];

    if (pop_result.trees != last_children) {
      parent = ts_tree_make_node(symbol, pop_result.tree_count,
                                 pop_result.trees, node_type);
    }

    if (pop_result.index == last_index) {
      ts_parse_stack_add_alternative(parser->stack, pop_result.index, parent);
    } else {
      TSStateId top_state =
        ts_parse_stack_top_state(parser->stack, pop_result.index);
      TSStateId state;

      if (extra) {
        ts_tree_set_extra(parent);
        state = top_state;
      } else {
        state = ts_language__action(parser->language, top_state, symbol)
                  .data.to_state;
      }

      ts_parse_stack_push(parser->stack, pop_result.index, state, parent);
    }

    last_index = pop_result.index;
    last_children = pop_result.trees;
  }

  return parent;
}

static void ts_parser__reduce_fragile(TSParser *parser, int head,
                                      TSSymbol symbol, size_t child_count) {
  TSTree *reduced =
    ts_parser__reduce(parser, head, symbol, child_count, false, false);
  ts_tree_set_fragile_left(reduced);
  ts_tree_set_fragile_right(reduced);
}

static void ts_parser__reduce_error(TSParser *parser, int head,
                                    size_t child_count) {
  TSTree *reduced = ts_parser__reduce(parser, head, ts_builtin_sym_error,
                                      child_count, false, true);
  reduced->size = ts_length_add(reduced->size, parser->lookahead->padding);
  parser->lookahead->padding = ts_length_zero();
  ts_tree_set_fragile_left(reduced);
  ts_tree_set_fragile_right(reduced);
}

static bool ts_parser__handle_error(TSParser *parser, int head) {
  size_t error_token_count = 1;
  ParseStackEntry *entry_before_error = ts_parse_stack_head(parser->stack, head);

  for (;;) {

    /*
     *  Unwind the parse stack until a state is found in which an error is
     *  expected and the current lookahead token is expected afterwards.
     */
    int i = -1;
    for (ParseStackEntry *entry = entry_before_error; entry != NULL;
         entry = ts_parse_stack_entry_next(entry, head), i++) {
      TSStateId stack_state = entry->state;
      TSParseAction action_on_error = ts_language__action(
        parser->language, stack_state, ts_builtin_sym_error);

      if (action_on_error.type == TSParseActionTypeShift) {
        TSStateId state_after_error = action_on_error.data.to_state;
        TSParseAction action_after_error = ts_language__action(
          parser->language, state_after_error, parser->lookahead->symbol);

        if (action_after_error.type != TSParseActionTypeError) {
          DEBUG("recover state:%u, count:%lu", state_after_error,
                error_token_count + i);
          ts_parser__reduce_error(parser, head, error_token_count + i);
          return true;
        }
      }
    }

    /*
     *  If there is no state in the stack for which we can recover with the
     *  current lookahead token, advance to the next token.
     */
    DEBUG("skip token:%s", SYM_NAME(parser->lookahead->symbol));
    ts_parser__shift(parser, head,
                     ts_parse_stack_top_state(parser->stack, head));
    ts_parser__get_next_lookahead(parser, true);
    error_token_count++;

    /*
     *  If the end of input is reached, exit.
     */
    if (parser->lookahead->symbol == ts_builtin_sym_end) {
      DEBUG("fail_to_recover");
      ts_parser__reduce_error(parser, head, error_token_count - 1);
      return false;
    }
  }
}

static void ts_parser__start(TSParser *parser, TSInput input) {
  parser->lexer.input = input;
  ts_lexer_reset(&parser->lexer, ts_length_zero());

  parser->previous_tree = ts_parse_stack_top_tree(parser->stack, 0);
  if (parser->previous_tree) {
    DEBUG("parse_after_edit");
    ts_tree_retain(parser->previous_tree);
  } else {
    DEBUG("new_parse");
  }
  parser->reusable_subtree = parser->previous_tree;
  parser->reusable_subtree_pos = 0;
  parser->lookahead = NULL;
  parser->is_verifying = false;
  ts_parse_stack_clear(parser->stack);
}

static TSTree *ts_parser__finish(TSParser *parser) {
  ParseStackPopResult pop_result =
    ts_parse_stack_pop(parser->stack, 0, -1, true).contents[0];

  TSTree **trees = pop_result.trees;
  size_t extra_count = pop_result.tree_count - 1;
  TSTree *root = trees[extra_count];

  ts_tree_prepend_children(root, extra_count, trees);
  ts_parse_stack_push(parser->stack, 0, 0, root);
  return root;
}

typedef enum {
  ParserNextResultNone,
  ParserNextResultAdvanced,
  ParserNextResultRemoved,
  ParserNextResultFinished
} ParserNextResult;

static ParserNextResult ts_parser__next(TSParser *parser, int head_to_advance) {
  TSStateId state = ts_parse_stack_top_state(parser->stack, head_to_advance);
  const TSParseAction *next_action =
    ts_language__actions(parser->language, state, parser->lookahead->symbol);
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
          if (ts_parser__handle_error(parser, head))
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
        ts_parser__shift(parser, head, action.data.to_state);
        result = ParserNextResultAdvanced;
        break;

      case TSParseActionTypeShiftExtra:
        DEBUG("shift_extra");
        ts_parser__shift_extra(parser, head, state);
        result = ParserNextResultAdvanced;
        break;

      case TSParseActionTypeReduce:
        DEBUG("reduce sym:%s, count:%u", SYM_NAME(action.data.symbol),
              action.data.child_count);
        ts_parser__reduce(parser, head, action.data.symbol,
                          action.data.child_count, false, false);
        break;

      case TSParseActionTypeReduceExtra:
        DEBUG("reduce_extra sym:%s", SYM_NAME(action.data.symbol));
        ts_parser__reduce(parser, head, action.data.symbol, 1, true, false);
        break;

      case TSParseActionTypeReduceFragile:
        DEBUG("reduce_fragile sym:%s, count:%u", SYM_NAME(action.data.symbol),
              action.data.child_count);
        ts_parser__reduce_fragile(parser, head, action.data.symbol,
                                  action.data.child_count);
        break;

      case TSParseActionTypeAccept:
        DEBUG("accept");
        return ParserNextResultFinished;
    }
  }

  return result;
}

static TSTree *ts_parser__select_tree(void *data, TSTree *left, TSTree *right) {
  return left;
}

/*
 *  Public
 */

TSParser ts_parser_make() {
  return (TSParser){
    .lexer = ts_lexer_make(),
    .stack = ts_parse_stack_new((TreeSelectionCallback){
      NULL, ts_parser__select_tree,
    }),
    .lookahead = NULL,
    .is_verifying = false,
  };
}

void ts_parser_destroy(TSParser *parser) {
  ts_parse_stack_delete(parser->stack);
  if (parser->lookahead)
    ts_tree_release(parser->lookahead);
}

TSDebugger ts_parser_debugger(const TSParser *parser) {
  return parser->lexer.debugger;
}

void ts_parser_set_debugger(TSParser *parser, TSDebugger debugger) {
  parser->lexer.debugger = debugger;
}

TSTree *ts_parser_parse(TSParser *parser, TSInput input) {
  ts_parser__start(parser, input);

  for (;;) {
    ts_parser__get_next_lookahead(parser, false);

    DEBUG("lookahead sym:%s", SYM_NAME(parser->lookahead->symbol));
    DEBUG("head_count: %d", ts_parse_stack_head_count(parser->stack));

    int head = 0;
    while (head < ts_parse_stack_head_count(parser->stack)) {
      bool removed = false, advanced = false;

      while (!(advanced || removed)) {
        switch (ts_parser__next(parser, head)) {
          case ParserNextResultNone:
            break;
          case ParserNextResultRemoved:
            removed = true;
            break;
          case ParserNextResultAdvanced:
            advanced = true;
            break;
          case ParserNextResultFinished:
            return ts_parser__finish(parser);
        }
      }

      if (!removed)
        head++;
    }
  }
}
