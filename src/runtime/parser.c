#include "runtime/parser.h"
#include <assert.h>
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include "tree_sitter/runtime.h"
#include "runtime/tree.h"
#include "runtime/lexer.h"
#include "runtime/length.h"
#include "runtime/array.h"
#include "runtime/language.h"
#include "runtime/alloc.h"
#include "runtime/reduce_action.h"
#include "runtime/error_costs.h"

#define LOG(...)                                                           \
  if (self->lexer.logger.log) {                                            \
    snprintf(self->lexer.debug_buffer, TS_DEBUG_BUFFER_SIZE, __VA_ARGS__); \
    self->lexer.logger.log(self->lexer.logger.payload, TSLogTypeParse,     \
                           self->lexer.debug_buffer);                      \
  }                                                                        \
  if (self->print_debugging_graphs) {                                      \
    fprintf(stderr, "graph {\nlabel=\"");                                  \
    fprintf(stderr, __VA_ARGS__);                                          \
    fprintf(stderr, "\"\n}\n\n");                                          \
  }

#define LOG_STACK()                                                     \
  if (self->print_debugging_graphs) {                                   \
    ts_stack_print_dot_graph(self->stack, self->language->symbol_names, \
                             stderr);                                   \
    fputs("\n\n", stderr);                                              \
  }

#define LOG_TREE()                                                        \
  if (self->print_debugging_graphs) {                                     \
    ts_tree_print_dot_graph(self->finished_tree, self->language, stderr); \
    fputs("\n", stderr);                                                  \
  }

#define SYM_NAME(symbol) ts_language_symbol_name(self->language, symbol)

#define BOOL_STRING(value) (value ? "true" : "false")

typedef struct {
  Parser *parser;
  TSSymbol lookahead_symbol;
  TreeArray *trees_above_error;
  size_t tree_count_above_error;
  bool found_repair;
  ReduceAction best_repair;
  TSStateId best_repair_next_state;
  size_t best_repair_skip_count;
} ErrorRepairSession;

typedef struct {
  bool stopped_at_error;
  StackSlice slice;
} Reduction;

static void parser__push(Parser *self, StackVersion version, Tree *tree,
                         TSStateId state) {
  ts_stack_push(self->stack, version, tree, false, state);
  ts_tree_release(tree);
}

static bool parser__breakdown_top_of_stack(Parser *self, StackVersion version) {
  bool did_break_down = false;
  bool pending = false;

  do {
    StackPopResult pop = ts_stack_pop_pending(self->stack, version);
    if (!pop.slices.size)
      break;

    did_break_down = true;
    pending = false;
    for (size_t i = 0; i < pop.slices.size; i++) {
      StackSlice slice = pop.slices.contents[i];
      TSStateId state = ts_stack_top_state(self->stack, slice.version);
      Tree *parent = *array_front(&slice.trees);

      for (size_t j = 0; j < parent->child_count; j++) {
        Tree *child = parent->children[j];
        pending = child->child_count > 0;

        if (child->symbol == ts_builtin_sym_error) {
          state = ERROR_STATE;
        } else if (!child->extra) {
          const TSParseAction *action =
            ts_language_last_action(self->language, state, child->symbol);
          assert(action && (action->type == TSParseActionTypeShift ||
                            action->type == TSParseActionTypeRecover));
          state = action->params.to_state;
        }

        ts_stack_push(self->stack, slice.version, child, pending, state);
      }

      for (size_t j = 1; j < slice.trees.size; j++) {
        Tree *tree = slice.trees.contents[j];
        parser__push(self, slice.version, tree, state);
      }

      LOG("breakdown_top_of_stack tree:%s", SYM_NAME(parent->symbol));
      LOG_STACK();

      ts_stack_decrease_push_count(self->stack, slice.version,
                                   parent->child_count + 1);
      ts_tree_release(parent);
      array_delete(&slice.trees);
    }
  } while (pending);

  return did_break_down;
}

static void parser__pop_reusable_node(ReusableNode *reusable_node) {
  reusable_node->byte_index += ts_tree_total_bytes(reusable_node->tree);
  while (reusable_node->tree) {
    Tree *parent = reusable_node->tree->context.parent;
    size_t next_index = reusable_node->tree->context.index + 1;
    if (parent && parent->child_count > next_index) {
      reusable_node->tree = parent->children[next_index];
      return;
    }
    reusable_node->tree = parent;
  }
}

static bool parser__breakdown_reusable_node(ReusableNode *reusable_node) {
  if (reusable_node->tree->child_count == 0) {
    return false;
  } else {
    reusable_node->tree = reusable_node->tree->children[0];
    return true;
  }
}

static bool parser__breakdown_lookahead(Parser *self, Tree **lookahead,
                                        TSStateId state,
                                        ReusableNode *reusable_node) {
  bool result = false;
  while (reusable_node->tree->child_count > 0 &&
         (self->is_split || reusable_node->tree->parse_state != state ||
          reusable_node->tree->fragile_left ||
          reusable_node->tree->fragile_right)) {
    LOG("state_mismatch sym:%s", SYM_NAME(reusable_node->tree->symbol));
    parser__breakdown_reusable_node(reusable_node);
    result = true;
  }

  if (result) {
    LOG("lookahead sym:%s", SYM_NAME(reusable_node->tree->symbol));
    ts_tree_release(*lookahead);
    ts_tree_retain(*lookahead = reusable_node->tree);
  }

  return result;
}

static void parser__pop_reusable_node_leaf(ReusableNode *reusable_node) {
  while (reusable_node->tree->child_count > 0)
    reusable_node->tree = reusable_node->tree->children[0];
  parser__pop_reusable_node(reusable_node);
}

static bool parser__can_reuse(Parser *self, TSStateId state, Tree *tree,
                              TableEntry *table_entry) {
  if (tree->first_leaf.lex_state == self->language->lex_states[state])
    return true;
  if (!table_entry->is_reusable)
    return false;
  if (!table_entry->depends_on_lookahead)
    return true;
  return tree->child_count > 1 && tree->error_cost == 0;
}

static bool parser__condense_stack(Parser *self) {
  bool result = false;
  for (StackVersion i = 0; i < ts_stack_version_count(self->stack); i++) {
    if (ts_stack_is_halted(self->stack, i)) {
      ts_stack_remove_version(self->stack, i);
      result = true;
      i--;
      continue;
    }

    ErrorStatus error_status = ts_stack_error_status(self->stack, i);

    for (StackVersion j = 0; j < i; j++) {
      if (ts_stack_merge(self->stack, j, i)) {
        result = true;
        i--;
        break;
      }

      switch (error_status_compare(error_status,
                                   ts_stack_error_status(self->stack, j))) {
        case -1:
          ts_stack_remove_version(self->stack, j);
          result = true;
          i--;
          j--;
          break;
        case 1:
          ts_stack_remove_version(self->stack, i);
          result = true;
          i--;
          break;
      }
    }
  }
  return result;
}

static Tree *parser__lex(Parser *self, TSStateId parse_state) {
  TSStateId start_state = self->language->lex_states[parse_state];
  TSStateId current_state = start_state;
  Length start_position = self->lexer.current_position;
  LOG("lex state:%d", start_state);

  bool skipped_error = false;
  int32_t first_error_character = 0;
  Length error_start_position, error_end_position;

  ts_lexer_start(&self->lexer, start_state);

  while (!self->language->lex_fn(&self->lexer.data, current_state)) {
    if (current_state != ERROR_STATE) {
      LOG("retry_in_error_mode");
      current_state = ERROR_STATE;
      ts_lexer_reset(&self->lexer, start_position);
      ts_lexer_start(&self->lexer, current_state);
      continue;
    }

    if (!skipped_error) {
      error_start_position = self->lexer.token_start_position;
      first_error_character = self->lexer.data.lookahead;
    }

    if (self->lexer.current_position.bytes == error_end_position.bytes) {
      if (self->lexer.data.lookahead == 0) {
        self->lexer.data.result_symbol = ts_builtin_sym_error;
        break;
      }
      self->lexer.data.advance(&self->lexer, ERROR_STATE, false);
    }

    skipped_error = true;
    error_end_position = self->lexer.current_position;
  }

  Tree *result;

  if (skipped_error) {
    Length padding = length_sub(error_start_position, start_position);
    Length size = length_sub(error_end_position, error_start_position);
    ts_lexer_reset(&self->lexer, error_end_position);
    result = ts_tree_make_error(size, padding, first_error_character);
  } else {
    TSSymbol symbol = self->lexer.data.result_symbol;
    Length padding =
      length_sub(self->lexer.token_start_position, start_position);
    Length size = length_sub(self->lexer.current_position,
                                  self->lexer.token_start_position);
    result =
      ts_tree_make_leaf(symbol, padding, size,
                        ts_language_symbol_metadata(self->language, symbol));
  }

  if (!result)
    return NULL;

  result->parse_state = parse_state;
  result->first_leaf.lex_state = start_state;
  return result;
}

static void parser__clear_cached_token(Parser *self) {
  ts_tree_release(self->cached_token);
  self->cached_token = NULL;
}

static Tree *parser__get_lookahead(Parser *self, StackVersion version,
                                     ReusableNode *reusable_node) {
  Length position = ts_stack_top_position(self->stack, version);

  while (reusable_node->tree) {
    if (reusable_node->byte_index > position.bytes) {
      LOG("before_reusable sym:%s, pos:%lu",
          SYM_NAME(reusable_node->tree->symbol), reusable_node->byte_index);
      break;
    }

    if (reusable_node->byte_index < position.bytes) {
      LOG("past_reusable sym:%s, pos:%lu",
          SYM_NAME(reusable_node->tree->symbol), reusable_node->byte_index);
      parser__pop_reusable_node(reusable_node);
      continue;
    }

    if (reusable_node->tree->has_changes) {
      LOG("cant_reuse_changed tree:%s, size:%lu",
          SYM_NAME(reusable_node->tree->symbol),
          reusable_node->tree->size.bytes);
      if (!parser__breakdown_reusable_node(reusable_node)) {
        parser__pop_reusable_node(reusable_node);
        parser__breakdown_top_of_stack(self, version);
      }
      continue;
    }

    if (reusable_node->tree->symbol == ts_builtin_sym_error) {
      LOG("cant_reuse_error tree:%s, size:%lu",
          SYM_NAME(reusable_node->tree->symbol),
          reusable_node->tree->size.bytes);
      if (!parser__breakdown_reusable_node(reusable_node)) {
        parser__pop_reusable_node(reusable_node);
        parser__breakdown_top_of_stack(self, version);
      }
      continue;
    }

    Tree *result = reusable_node->tree;
    ts_tree_retain(result);
    return result;
  }

  if (self->cached_token && position.bytes == self->cached_token_byte_index) {
    ts_tree_retain(self->cached_token);
    return self->cached_token;
  }

  ts_lexer_reset(&self->lexer, position);
  TSStateId parse_state = ts_stack_top_state(self->stack, version);
  return parser__lex(self, parse_state);
}

static bool parser__select_tree(Parser *self, Tree *left, Tree *right) {
  if (!left)
    return true;
  if (!right)
    return false;
  if (right->error_cost < left->error_cost) {
    LOG("select_smaller_error symbol:%s, over_symbol:%s",
        SYM_NAME(right->symbol), SYM_NAME(left->symbol));
    return true;
  }
  if (left->error_cost < right->error_cost) {
    LOG("select_smaller_error symbol:%s, over_symbol:%s",
        SYM_NAME(left->symbol), SYM_NAME(right->symbol));
    return false;
  }

  int comparison = ts_tree_compare(left, right);
  switch (comparison) {
    case -1:
      LOG("select_earlier symbol:%s, over_symbol:%s", SYM_NAME(left->symbol),
          SYM_NAME(right->symbol));
      return false;
      break;
    case 1:
      LOG("select_earlier symbol:%s, over_symbol:%s", SYM_NAME(right->symbol),
          SYM_NAME(left->symbol));
      return true;
    default:
      LOG("select_existing symbol:%s, over_symbol:%s", SYM_NAME(left->symbol),
          SYM_NAME(right->symbol));
      return false;
  }
}

static bool parser__better_version_exists(Parser *self, StackVersion version,
                                          ErrorStatus my_error_status) {
  if (self->finished_tree &&
      self->finished_tree->error_cost <= my_error_status.cost)
    return true;

  for (StackVersion i = 0, n = ts_stack_version_count(self->stack); i < n; i++) {
    if (i == version || ts_stack_is_halted(self->stack, i))
      continue;

    switch (error_status_compare(my_error_status,
                                 ts_stack_error_status(self->stack, i))) {
      case -1:
        LOG("halt_other version:%u", i);
        ts_stack_halt(self->stack, i);
        break;
      case 1:
        return true;
    }
  }

  return false;
}

static void parser__shift(Parser *self, StackVersion version, TSStateId state,
                          Tree *lookahead, bool extra) {
  if (extra != lookahead->extra) {
    TSSymbolMetadata metadata =
      ts_language_symbol_metadata(self->language, lookahead->symbol);
    if (metadata.structural && ts_stack_version_count(self->stack) > 1) {
      lookahead = ts_tree_make_copy(lookahead);
    } else {
      ts_tree_retain(lookahead);
    }
    lookahead->extra = extra;
  } else {
    ts_tree_retain(lookahead);
  }

  bool is_pending = lookahead->child_count > 0;
  ts_stack_push(self->stack, version, lookahead, is_pending, state);
  ts_tree_release(lookahead);
}

static bool parser__switch_children(Parser *self, Tree *tree,
                                    Tree **children, size_t count) {
  self->scratch_tree.symbol = tree->symbol;
  self->scratch_tree.child_count = 0;
  ts_tree_set_children(&self->scratch_tree, count, children);
  if (parser__select_tree(self, tree, &self->scratch_tree)) {
    tree->size = self->scratch_tree.size;
    tree->padding = self->scratch_tree.padding;
    tree->error_cost = self->scratch_tree.error_cost;
    tree->children = self->scratch_tree.children;
    tree->child_count = self->scratch_tree.child_count;
    tree->named_child_count = self->scratch_tree.named_child_count;
    tree->visible_child_count = self->scratch_tree.visible_child_count;
    return true;
  } else {
    return false;
  }
}

static Reduction parser__reduce(Parser *self, StackVersion version,
                                TSSymbol symbol, unsigned count, bool fragile,
                                bool allow_skipping) {
  size_t initial_version_count = ts_stack_version_count(self->stack);
  StackPopResult pop = ts_stack_pop_count(self->stack, version, count);
  if (pop.stopped_at_error) {
    return (Reduction){ true, pop.slices.contents[0] };
  }

  const TSLanguage *language = self->language;
  TSSymbolMetadata metadata = ts_language_symbol_metadata(language, symbol);

  for (size_t i = 0; i < pop.slices.size; i++) {
    StackSlice slice = pop.slices.contents[i];

    size_t child_count = slice.trees.size;
    while (child_count > 0 && slice.trees.contents[child_count - 1]->extra)
      child_count--;

    Tree *parent =
      ts_tree_make_node(symbol, child_count, slice.trees.contents, metadata);

    while (i + 1 < pop.slices.size) {
      StackSlice next_slice = pop.slices.contents[i + 1];
      if (next_slice.version != slice.version)
        break;
      i++;

      size_t child_count = next_slice.trees.size;
      while (child_count > 0 && next_slice.trees.contents[child_count - 1]->extra)
        child_count--;

      if (parser__switch_children(self, parent, next_slice.trees.contents,
                                  child_count)) {
        ts_tree_array_delete(&slice.trees);
        slice = next_slice;
      } else {
        ts_tree_array_delete(&next_slice.trees);
      }
    }

    TSStateId state = ts_stack_top_state(self->stack, slice.version);
    if (fragile || self->is_split || pop.slices.size > 1 ||
        initial_version_count > 1) {
      parent->fragile_left = true;
      parent->fragile_right = true;
      parent->parse_state = TS_TREE_STATE_NONE;
    } else {
      parent->parse_state = state;
    }

    const TSParseAction *action =
      ts_language_last_action(language, state, symbol);
    assert(action->type == TSParseActionTypeShift ||
           action->type == TSParseActionTypeRecover);

    if (action->type == TSParseActionTypeRecover && child_count > 1 &&
        allow_skipping) {
      StackVersion other_version =
        ts_stack_duplicate_version(self->stack, slice.version);

      ts_stack_push(self->stack, other_version, parent, false, ERROR_STATE);
      for (size_t j = parent->child_count; j < slice.trees.size; j++) {
        Tree *tree = slice.trees.contents[j];
        ts_stack_push(self->stack, other_version, tree, false, ERROR_STATE);
      }

      ErrorStatus error_status =
        ts_stack_error_status(self->stack, other_version);
      if (parser__better_version_exists(self, version, error_status))
        ts_stack_remove_version(self->stack, other_version);
    }

    parser__push(self, slice.version, parent, action->params.to_state);
    for (size_t j = parent->child_count; j < slice.trees.size; j++) {
      Tree *tree = slice.trees.contents[j];
      parser__push(self, slice.version, tree, action->params.to_state);
    }
  }

  for (StackVersion i = initial_version_count;
       i < ts_stack_version_count(self->stack); i++) {
    for (StackVersion j = initial_version_count; j < i; j++) {
      if (ts_stack_merge(self->stack, j, i)) {
        i--;
        break;
      }
    }
  }

  return (Reduction){ false, pop.slices.contents[0] };
}

static inline const TSParseAction *parser__reductions_after_sequence(
  Parser *self, TSStateId start_state, const TreeArray *trees_below,
  size_t tree_count_below, const TreeArray *trees_above,
  TSSymbol lookahead_symbol, size_t *count) {
  TSStateId state = start_state;
  size_t child_count = 0;
  *count = 0;

  for (size_t i = 0; i < trees_below->size; i++) {
    if (child_count == tree_count_below)
      break;
    Tree *tree = trees_below->contents[trees_below->size - 1 - i];
    const TSParseAction *action =
      ts_language_last_action(self->language, state, tree->symbol);
    if (!action || action->type != TSParseActionTypeShift)
      return NULL;
    if (action->extra || tree->extra)
      continue;
    child_count++;
    state = action->params.to_state;
  }

  for (size_t i = 0; i < trees_above->size; i++) {
    Tree *tree = trees_above->contents[i];
    const TSParseAction *action =
      ts_language_last_action(self->language, state, tree->symbol);
    if (!action || action->type != TSParseActionTypeShift)
      return NULL;
    if (action->extra || tree->extra)
      continue;
    child_count++;
    state = action->params.to_state;
  }

  const TSParseAction *actions =
    ts_language_actions(self->language, state, lookahead_symbol, count);

  if (*count > 0 && actions[*count - 1].type != TSParseActionTypeReduce) {
    (*count)--;
  }

  while (*count > 0 && actions[0].params.child_count < child_count) {
    actions++;
    (*count)--;
  }

  while (*count > 0 && actions[*count - 1].params.child_count > child_count) {
    (*count)--;
  }

  return actions;
}

static StackIterateAction parser__error_repair_callback(
  void *payload, TSStateId state, TreeArray *trees, size_t tree_count,
  bool is_done, bool is_pending) {

  ErrorRepairSession *session = (ErrorRepairSession *)payload;
  Parser *self = session->parser;
  TSSymbol lookahead_symbol = session->lookahead_symbol;
  ReduceActionSet *repairs = &self->reduce_actions;
  TreeArray *trees_above_error = session->trees_above_error;
  size_t tree_count_above_error = session->tree_count_above_error;

  StackIterateAction result = StackIterateNone;

  size_t last_repair_count = -1;
  size_t repair_reduction_count = -1;
  const TSParseAction *repair_reductions = NULL;

  for (size_t i = 0; i < repairs->size; i++) {
    ReduceAction *repair = &repairs->contents[i];
    size_t count_needed_below_error = repair->count - tree_count_above_error;
    if (count_needed_below_error > tree_count)
      break;

    size_t skip_count = tree_count - count_needed_below_error;
    if (session->found_repair && skip_count >= session->best_repair_skip_count) {
      array_erase(repairs, i--);
      continue;
    }

    const TSParseAction *repair_symbol_action =
      ts_language_last_action(self->language, state, repair->symbol);
    if (!repair_symbol_action ||
        repair_symbol_action->type != TSParseActionTypeShift)
      continue;

    TSStateId state_after_repair = repair_symbol_action->params.to_state;
    if (!ts_language_last_action(self->language, state_after_repair,
                                 lookahead_symbol))
      continue;

    if (count_needed_below_error != last_repair_count) {
      last_repair_count = count_needed_below_error;
      repair_reductions = parser__reductions_after_sequence(
        self, state, trees, count_needed_below_error, trees_above_error,
        lookahead_symbol, &repair_reduction_count);
    }

    for (size_t j = 0; j < repair_reduction_count; j++) {
      if (repair_reductions[j].params.symbol == repair->symbol) {
        result |= StackIteratePop;
        session->found_repair = true;
        session->best_repair = *repair;
        session->best_repair_skip_count = skip_count;
        session->best_repair_next_state = state_after_repair;
        array_erase(repairs, i--);
        break;
      }
    }
  }

  if (repairs->size == 0)
    result |= StackIterateStop;

  return result;
}

static bool parser__repair_error(Parser *self, StackSlice slice,
                                         TSSymbol lookahead_symbol,
                                         const TSParseAction *actions,
                                         size_t action_count) {
  LOG("repair_error");
  ErrorRepairSession session = {
    .parser = self,
    .lookahead_symbol = lookahead_symbol,
    .found_repair = false,
    .trees_above_error = &slice.trees,
    .tree_count_above_error = ts_tree_array_essential_count(&slice.trees),
  };

  array_clear(&self->reduce_actions);
  for (size_t i = 0; i < action_count; i++) {
    if (actions[i].type == TSParseActionTypeReduce) {
      TSSymbol symbol = actions[i].params.symbol;
      size_t child_count = actions[i].params.child_count;
      if ((child_count > session.tree_count_above_error) ||
          (child_count == session.tree_count_above_error &&
           !ts_language_symbol_metadata(self->language, symbol).visible))
        array_push(&self->reduce_actions, ((ReduceAction){symbol, child_count }));
    }
  }

  StackPopResult pop = ts_stack_iterate(
    self->stack, slice.version, parser__error_repair_callback, &session);

  if (!session.found_repair) {
    LOG("no_repair_found");
    ts_stack_remove_version(self->stack, slice.version);
    ts_tree_array_delete(&slice.trees);
    return false;
  }

  ReduceAction repair = session.best_repair;
  TSStateId next_state = session.best_repair_next_state;
  size_t skip_count = session.best_repair_skip_count;
  size_t count_below = repair.count - session.tree_count_above_error;
  TSSymbol symbol = repair.symbol;

  StackSlice new_slice = array_pop(&pop.slices);
  TreeArray children = new_slice.trees;
  ts_stack_renumber_version(self->stack, new_slice.version, slice.version);

  for (size_t i = pop.slices.size - 1; i + 1 > 0; i--) {
    StackSlice other_slice = pop.slices.contents[i];
    ts_tree_array_delete(&other_slice.trees);
    if (other_slice.version != pop.slices.contents[i + 1].version)
      ts_stack_remove_version(self->stack, other_slice.version);
  }

  TreeArray skipped_children = array_new();
  array_grow(&skipped_children, skip_count);
  for (size_t i = count_below; i < children.size; i++)
    array_push(&skipped_children, children.contents[i]);

  Tree *error = ts_tree_make_error_node(&skipped_children);
  children.size = count_below;
  array_push(&children, error);

  for (size_t i = 0; i < slice.trees.size; i++)
    array_push(&children, slice.trees.contents[i]);
  array_delete(&slice.trees);

  Tree *parent =
    ts_tree_make_node(symbol, children.size, children.contents,
                      ts_language_symbol_metadata(self->language, symbol));
  parser__push(self, slice.version, parent, next_state);
  ts_stack_decrease_push_count(self->stack, slice.version, error->child_count);

  ErrorStatus error_status = ts_stack_error_status(self->stack, slice.version);
  if (parser__better_version_exists(self, slice.version, error_status)) {
    LOG("no_better_repair_found");
    ts_stack_halt(self->stack, slice.version);
    return false;
  } else {
    LOG("repair_found sym:%s, child_count:%lu, cost:%u", SYM_NAME(symbol),
        repair.count, parent->error_cost);
    return true;
  }
}

static void parser__start(Parser *self, TSInput input, Tree *previous_tree) {
  if (previous_tree) {
    LOG("parse_after_edit");
  } else {
    LOG("new_parse");
  }

  ts_lexer_set_input(&self->lexer, input);
  ts_stack_clear(self->stack);
  self->reusable_node = (ReusableNode){ previous_tree, 0 };
  self->cached_token = NULL;
  self->finished_tree = NULL;
}

static void parser__accept(Parser *self, StackVersion version,
                           Tree *lookahead) {
  lookahead->extra = true;
  assert(lookahead->symbol == ts_builtin_sym_end);
  ts_stack_push(self->stack, version, lookahead, false, 1);
  StackPopResult pop = ts_stack_pop_all(self->stack, version);

  for (size_t i = 0; i < pop.slices.size; i++) {
    StackSlice slice = pop.slices.contents[i];
    TreeArray trees = slice.trees;

    Tree *root = NULL;
    if (trees.size == 1) {
      root = trees.contents[0];
      array_delete(&trees);
    } else {
      for (size_t j = trees.size - 1; j + 1 > 0; j--) {
        Tree *child = trees.contents[j];
        if (!child->extra) {
          root = ts_tree_make_copy(child);
          root->child_count = 0;
          for (size_t k = 0; k < child->child_count; k++)
            ts_tree_retain(child->children[k]);
          array_splice(&trees, j, 1, child->child_count, child->children);
          ts_tree_set_children(root, trees.size, trees.contents);
          ts_tree_release(child);
          break;
        }
      }
    }

    if (parser__select_tree(self, self->finished_tree, root)) {
      ts_tree_release(self->finished_tree);
      assert(root->ref_count > 0);
      self->finished_tree = root;
    } else {
      ts_tree_release(root);
    }
  }

  ts_stack_remove_version(self->stack, pop.slices.contents[0].version);
  ts_stack_halt(self->stack, version);
}

static bool parser__do_potential_reductions(
  Parser *self, StackVersion version) {
  bool has_shift_action = false;
  TSStateId state = ts_stack_top_state(self->stack, version);
  size_t previous_version_count = ts_stack_version_count(self->stack);

  array_clear(&self->reduce_actions);
  for (TSSymbol symbol = 0; symbol < self->language->symbol_count; symbol++) {
    TableEntry entry;
    ts_language_table_entry(self->language, state, symbol, &entry);
    for (size_t i = 0; i < entry.action_count; i++) {
      TSParseAction action = entry.actions[i];
      if (action.extra)
        continue;
      switch (action.type) {
        case TSParseActionTypeShift:
        case TSParseActionTypeRecover:
          has_shift_action = true;
          break;
        case TSParseActionTypeReduce:
          if (action.params.child_count > 0)
            ts_reduce_action_set_add(&self->reduce_actions, (ReduceAction){
              .symbol = action.params.symbol,
              .count = action.params.child_count,
            });
        default:
          break;
      }
    }
  }

  bool did_reduce = false;
  for (size_t i = 0; i < self->reduce_actions.size; i++) {
    ReduceAction action = self->reduce_actions.contents[i];
    Reduction reduction =
      parser__reduce(self, version, action.symbol, action.count, true, false);
    if (reduction.stopped_at_error) {
      ts_tree_array_delete(&reduction.slice.trees);
      ts_stack_remove_version(self->stack, reduction.slice.version);
      continue;
    } else {
      did_reduce = true;
    }
  }

  if (did_reduce) {
    if (has_shift_action) {
      return true;
    } else {
      ts_stack_renumber_version(self->stack, previous_version_count, version);
      return false;
    }
  } else {
    return true;
  }
}

typedef struct {
  Parser *parser;
  TSSymbol lookahead_symbol;
} SkipPrecedingTokensSession;

static StackIterateAction parser__repair_consumed_error_callback(
  void *payload, TSStateId state, TreeArray *trees, size_t tree_count,
  bool is_done, bool is_pending) {
  if (tree_count > 0 && state != ERROR_STATE) {
    SkipPrecedingTokensSession *session = payload;
    Parser *self = session->parser;
    TSSymbol lookahead_symbol = session->lookahead_symbol;
    const TSParseAction *action =
      ts_language_last_action(self->language, state, lookahead_symbol);
    if (action && action->type == TSParseActionTypeReduce) {
      return StackIteratePop | StackIterateStop;
    }
  }
  return StackIterateNone;
}

static void parser__repair_consumed_error(Parser *self, StackVersion version,
                                          TSSymbol lookahead_symbol) {
  SkipPrecedingTokensSession session = { self, lookahead_symbol };
  StackPopResult pop = ts_stack_iterate(
    self->stack, version, parser__repair_consumed_error_callback, &session);

  StackVersion last_slice_version = STACK_VERSION_NONE;
  for (size_t i = 0; i < pop.slices.size; i++) {
    StackSlice slice = pop.slices.contents[i];
    if (slice.version == last_slice_version) {
      ts_tree_array_delete(&slice.trees);
      continue;
    }

    last_slice_version = slice.version;
    Tree *error = ts_tree_make_error_node(&slice.trees);
    error->extra = true;
    TSStateId state = ts_stack_top_state(self->stack, slice.version);
    parser__push(self, slice.version, error, state);
  }
}

static void parser__handle_error(Parser *self, StackVersion version,
                                 TSSymbol lookahead_symbol) {
  ErrorStatus error_status = ts_stack_error_status(self->stack, version);
  error_status.count++;
  if (parser__better_version_exists(self, version, error_status)) {
    ts_stack_halt(self->stack, version);
    LOG("bail_on_error");
    return;
  }

  LOG("handle_error");
  parser__repair_consumed_error(self, version, lookahead_symbol);

  size_t previous_version_count = ts_stack_version_count(self->stack);
  for (StackVersion v = version; v < ts_stack_version_count(self->stack);) {
    if (parser__do_potential_reductions(self, v)) {
      if (v == version) {
        v = previous_version_count;
      } else {
        v++;
      }
    }
  }

  ts_stack_push(self->stack, version, NULL, false, ERROR_STATE);
  while (ts_stack_version_count(self->stack) > previous_version_count) {
    ts_stack_push(self->stack, previous_version_count, NULL, false, ERROR_STATE);
    assert(ts_stack_merge(self->stack, version, previous_version_count));
  }
}

static void parser__recover(Parser *self, StackVersion version, TSStateId state,
                            Tree *lookahead) {
  if (lookahead->symbol == ts_builtin_sym_end) {
    LOG("recover_eof");
    TreeArray children = array_new();
    Tree *parent = ts_tree_make_error_node(&children);
    parser__push(self, version, parent, 1);
    parser__accept(self, version, lookahead);
  }

  LOG("recover state:%u", state);

  StackVersion new_version = ts_stack_duplicate_version(self->stack, version);

  parser__shift(
    self, new_version, ERROR_STATE, lookahead,
    ts_language_symbol_metadata(self->language, lookahead->symbol).extra);
  ErrorStatus error_status = ts_stack_error_status(self->stack, new_version);
  if (parser__better_version_exists(self, version, error_status)) {
    ts_stack_remove_version(self->stack, new_version);
    LOG("bail_on_recovery");
  }

  parser__shift(self, version, state, lookahead, false);
}

static void parser__advance(Parser *self, StackVersion version,
                            ReusableNode *reusable_node) {
  bool validated_lookahead = false;
  Tree *lookahead = parser__get_lookahead(self, version, reusable_node);

  for (;;) {
    TSStateId state = ts_stack_top_state(self->stack, version);

    TableEntry table_entry;
    ts_language_table_entry(self->language, state, lookahead->first_leaf.symbol,
                            &table_entry);

    if (!validated_lookahead) {
      if (!parser__can_reuse(self, state, lookahead, &table_entry)) {
        if (lookahead == reusable_node->tree)
          parser__pop_reusable_node_leaf(reusable_node);
        else
          parser__clear_cached_token(self);

        ts_tree_release(lookahead);
        lookahead = parser__get_lookahead(self, version, reusable_node);
        continue;
      }

      validated_lookahead = true;
      LOG("lookahead sym:%s, size:%lu", SYM_NAME(lookahead->symbol),
          lookahead->size.bytes);
    }

    bool reduction_stopped_at_error = false;
    StackVersion last_reduction_version = STACK_VERSION_NONE;

    for (size_t i = 0; i < table_entry.action_count; i++) {
      TSParseAction action = table_entry.actions[i];

      switch (action.type) {
        case TSParseActionTypeShift: {
          if (lookahead->child_count > 0) {
            if (parser__breakdown_lookahead(self, &lookahead, state,
                                            reusable_node)) {
              if (!parser__can_reuse(self, state, lookahead, &table_entry)) {
                parser__pop_reusable_node(reusable_node);
                ts_tree_release(lookahead);
                lookahead = parser__get_lookahead(self, version, reusable_node);
              }
            }

            action = *ts_language_last_action(self->language, state,
                                              lookahead->symbol);
          }

          TSStateId next_state;
          if (action.extra) {
            next_state = state;
            LOG("shift_extra");
          } else {
            next_state = action.params.to_state;
            LOG("shift state:%u", next_state);
          }

          parser__shift(self, version, next_state, lookahead, action.extra);

          if (lookahead == reusable_node->tree)
            parser__pop_reusable_node(reusable_node);

          ts_tree_release(lookahead);
          return;
        }

        case TSParseActionTypeReduce: {
          if (reduction_stopped_at_error)
            continue;

          LOG("reduce sym:%s, child_count:%u", SYM_NAME(action.params.symbol),
              action.params.child_count);

          Reduction reduction =
            parser__reduce(self, version, action.params.symbol, action.params.child_count,
                           (i < table_entry.action_count - 1), true);

          if (reduction.stopped_at_error) {
            reduction_stopped_at_error = true;
            if (parser__repair_error(
              self, reduction.slice, lookahead->first_leaf.symbol,
              table_entry.actions, table_entry.action_count)) {
              last_reduction_version = reduction.slice.version;
            }
          } else {
            last_reduction_version = reduction.slice.version;
          }

          break;
        }

        case TSParseActionTypeAccept: {
          if (ts_stack_error_status(self->stack, version).count > 0)
            continue;

          LOG("accept");
          parser__accept(self, version, lookahead);

          ts_tree_release(lookahead);
          return;
        }

        case TSParseActionTypeRecover: {
          while (lookahead->child_count > 0) {
            parser__breakdown_reusable_node(reusable_node);
            ts_tree_release(lookahead);
            lookahead = reusable_node->tree;
            ts_tree_retain(lookahead);
          }
          action =
            *ts_language_last_action(self->language, state, lookahead->symbol);

          parser__recover(self, version, action.params.to_state, lookahead);

          if (lookahead == reusable_node->tree)
            parser__pop_reusable_node(reusable_node);

          ts_tree_release(lookahead);
          return;
        }
      }
    }

    if (last_reduction_version != STACK_VERSION_NONE) {
      ts_stack_renumber_version(self->stack, last_reduction_version, version);
      LOG_STACK();
      continue;
    }

    if (parser__breakdown_top_of_stack(self, version)) {
      continue;
    }

    if (state == ERROR_STATE) {
      parser__push(self, version, lookahead, ERROR_STATE);
      return;
    }

    parser__handle_error(self, version, lookahead->first_leaf.symbol);

    if (ts_stack_is_halted(self->stack, version)) {
      ts_tree_release(lookahead);
      return;
    }
  }
}

bool parser_init(Parser *self) {
  ts_lexer_init(&self->lexer);
  array_init(&self->reduce_actions);
  array_init(&self->tree_path1);
  array_init(&self->tree_path2);
  array_grow(&self->reduce_actions, 4);
  self->stack = ts_stack_new();
  self->finished_tree = NULL;
  return true;
}

void parser_destroy(Parser *self) {
  if (self->stack)
    ts_stack_delete(self->stack);
  if (self->reduce_actions.contents)
    array_delete(&self->reduce_actions);
  if (self->tree_path1.contents)
    array_delete(&self->tree_path1);
  if (self->tree_path2.contents)
    array_delete(&self->tree_path2);
}

Tree *parser_parse(Parser *self, TSInput input, Tree *old_tree) {
  parser__start(self, input, old_tree);

  StackVersion version = STACK_VERSION_NONE;
  size_t position = 0, last_position = 0;
  ReusableNode reusable_node;

  do {
    for (version = 0; version < ts_stack_version_count(self->stack); version++) {
      reusable_node = self->reusable_node;
      last_position = position;

      while (!ts_stack_is_halted(self->stack, version)) {
        position = ts_stack_top_position(self->stack, version).chars;
        if (position > last_position ||
            (version > 0 && position == last_position))
          break;

        LOG("process version:%d, version_count:%lu, state:%d, row:%lu, col:%lu",
            version, ts_stack_version_count(self->stack),
            ts_stack_top_state(self->stack, version),
            ts_stack_top_position(self->stack, version).extent.row + 1,
            ts_stack_top_position(self->stack, version).extent.column + 1);

        parser__advance(self, version, &reusable_node);
        LOG_STACK();
      }
    }

    self->reusable_node = reusable_node;

    if (parser__condense_stack(self)) {
      LOG("condense");
      LOG_STACK();
    }

    self->is_split = (version > 1);
  } while (version != 0);

  LOG("done");
  LOG_TREE();
  ts_stack_clear(self->stack);
  parser__clear_cached_token(self);
  ts_tree_assign_parents(self->finished_tree, &self->tree_path1);
  return self->finished_tree;
}
