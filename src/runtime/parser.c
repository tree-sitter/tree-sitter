#include "runtime/parser.h"
#include <assert.h>
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include "tree_sitter/runtime.h"
#include "tree_sitter/parser.h"
#include "runtime/tree.h"
#include "runtime/lexer.h"
#include "runtime/length.h"
#include "runtime/array.h"
#include "runtime/language.h"
#include "runtime/alloc.h"
#include "runtime/reduce_action.h"

#define LOG(...)                                                               \
  if (self->lexer.debugger.debug_fn) {                                         \
    snprintf(self->lexer.debug_buffer, TS_DEBUG_BUFFER_SIZE, __VA_ARGS__);     \
    self->lexer.debugger.debug_fn(self->lexer.debugger.payload,                \
                                  TSDebugTypeParse, self->lexer.debug_buffer); \
  }                                                                            \
  if (self->print_debugging_graphs) {                                          \
    fprintf(stderr, "graph {\nlabel=\"");                                      \
    fprintf(stderr, __VA_ARGS__);                                              \
    fprintf(stderr, "\"\n}\n\n");                                              \
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

#define CHECK(expr) \
  if (!(expr)) {    \
    goto error;     \
  }

static const unsigned ERROR_COST_THRESHOLD = 3;

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
  enum {
    ReduceFailed,
    ReduceSucceeded,
    ReduceStoppedAtError,
  } status;

  StackSlice slice;
} Reduction;

typedef enum {
  RepairFailed,
  RepairSucceeded,
  RepairNoneFound,
} RepairResult;

typedef enum {
  BreakdownFailed,
  BreakdownPerformed,
  BreakdownAborted,
} BreakdownResult;

static bool parser__push(Parser *self, StackVersion version, TSTree *tree,
                         TSStateId state) {
  bool result = ts_stack_push(self->stack, version, tree, false, state);
  ts_tree_release(tree);
  return result;
}

static BreakdownResult parser__breakdown_top_of_stack(Parser *self,
                                                      StackVersion version) {
  bool did_break_down = false;
  bool pending = false;

  do {
    StackPopResult pop = ts_stack_pop_pending(self->stack, version);
    CHECK(pop.status);
    if (!pop.slices.size)
      break;

    did_break_down = true;
    pending = false;
    for (size_t i = 0; i < pop.slices.size; i++) {
      StackSlice slice = pop.slices.contents[i];
      TSStateId state = ts_stack_top_state(self->stack, slice.version);
      TSTree *parent = *array_front(&slice.trees);

      for (size_t j = 0; j < parent->child_count; j++) {
        TSTree *child = parent->children[j];
        pending = child->child_count > 0;

        if (child->symbol == ts_builtin_sym_error) {
          state = TS_STATE_ERROR;
        } else if (!child->extra) {
          const TSParseAction *action =
            ts_language_last_action(self->language, state, child->symbol);
          assert(action && (action->type == TSParseActionTypeShift ||
                            action->type == TSParseActionTypeRecover));
          state = action->to_state;
        }

        CHECK(ts_stack_push(self->stack, slice.version, child, pending, state));
      }

      for (size_t j = 1; j < slice.trees.size; j++) {
        TSTree *tree = slice.trees.contents[j];
        CHECK(parser__push(self, slice.version, tree, state));
      }

      LOG("breakdown_top_of_stack tree:%s", SYM_NAME(parent->symbol));
      LOG_STACK();

      ts_tree_release(parent);
      array_delete(&slice.trees);
    }
  } while (pending);

  return did_break_down ? BreakdownPerformed : BreakdownAborted;

error:
  return BreakdownFailed;
}

static void parser__pop_reusable_node(ReusableNode *reusable_node) {
  reusable_node->char_index += ts_tree_total_chars(reusable_node->tree);
  while (reusable_node->tree) {
    TSTree *parent = reusable_node->tree->context.parent;
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

static bool parser__breakdown_lookahead(Parser *self, TSTree **lookahead,
                                        TSStateId state,
                                        ReusableNode *reusable_node) {
  bool result = false;
  while (reusable_node->tree->child_count > 0 &&
         (reusable_node->tree->parse_state != state ||
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

static bool parser__can_reuse(Parser *self, TSStateId state, TSTree *tree,
                              TableEntry *table_entry) {
  if (tree->first_leaf.lex_state == self->language->lex_states[state])
    return true;
  if (!table_entry->is_reusable)
    return false;
  if (!table_entry->depends_on_lookahead)
    return true;
  return tree->child_count > 1 && tree->error_size == 0;
}

static bool parser__condense_stack(Parser *self) {
  bool result = false;
  for (StackVersion i = 0; i < ts_stack_version_count(self->stack); i++) {
    if (ts_stack_is_halted(self->stack, i)) {
      result = true;
      ts_stack_remove_version(self->stack, i);
      i--;
      continue;
    }

    bool did_merge = false;
    for (size_t j = 0; j < i; j++) {

      if (ts_stack_merge(self->stack, j, i)) {
        did_merge = true;
        break;
      }
    }

    if (did_merge) {
      result = true;
      i--;
      continue;
    }
  }
  return result;
}

static TSTree *parser__lex(Parser *self, TSStateId parse_state, bool error_mode) {
  TSStateId state = self->language->lex_states[parse_state];
  LOG("lex state:%d", state);

  TSLength position = self->lexer.current_position;

  ts_lexer_start(&self->lexer, state);
  if (!self->language->lex_fn(&self->lexer, state, error_mode)) {
    ts_lexer_reset(&self->lexer, position);
    ts_lexer_start(&self->lexer, state);
    assert(self->language->lex_fn(&self->lexer, TS_STATE_ERROR, true));
  }

  TSLexerResult lex_result;
  ts_lexer_finish(&self->lexer, &lex_result);

  TSTree *result;
  if (lex_result.symbol == ts_builtin_sym_error) {
    result = ts_tree_make_error(lex_result.size, lex_result.padding,
                                lex_result.first_unexpected_character);
  } else {
    result = ts_tree_make_leaf(
      lex_result.symbol, lex_result.padding, lex_result.size,
      ts_language_symbol_metadata(self->language, lex_result.symbol));
    if (!result)
      return NULL;
    result->parse_state = parse_state;
  }

  result->first_leaf.lex_state = state;

  return result;
}

static void parser__clear_cached_token(Parser *self) {
  ts_tree_release(self->cached_token);
  self->cached_token = NULL;
}

static TSTree *parser__get_lookahead(Parser *self, StackVersion version,
                                     ReusableNode *reusable_node) {
  TSLength position = ts_stack_top_position(self->stack, version);

  while (reusable_node->tree) {
    if (reusable_node->char_index > position.chars) {
      LOG("before_reusable sym:%s, pos:%lu",
          SYM_NAME(reusable_node->tree->symbol), reusable_node->char_index);
      break;
    }

    if (reusable_node->char_index < position.chars) {
      LOG("past_reusable sym:%s, pos:%lu",
          SYM_NAME(reusable_node->tree->symbol), reusable_node->char_index);
      parser__pop_reusable_node(reusable_node);
      continue;
    }

    if (reusable_node->tree->has_changes) {
      LOG("cant_reuse_changed tree:%s, size:%lu",
          SYM_NAME(reusable_node->tree->symbol),
          reusable_node->tree->size.chars);
      if (!parser__breakdown_reusable_node(reusable_node)) {
        parser__pop_reusable_node(reusable_node);
        CHECK(parser__breakdown_top_of_stack(self, version));
      }
      continue;
    }

    if (reusable_node->tree->symbol == ts_builtin_sym_error) {
      LOG("cant_reuse_error tree:%s, size:%lu",
          SYM_NAME(reusable_node->tree->symbol),
          reusable_node->tree->size.chars);
      if (!parser__breakdown_reusable_node(reusable_node)) {
        parser__pop_reusable_node(reusable_node);
        CHECK(parser__breakdown_top_of_stack(self, version));
      }
      continue;
    }

    TSTree *result = reusable_node->tree;
    ts_tree_retain(result);
    return result;
  }

  if (self->cached_token && position.chars == self->cached_token_char_index) {
    ts_tree_retain(self->cached_token);
    return self->cached_token;
  }

  ts_lexer_reset(&self->lexer, position);
  TSStateId parse_state = ts_stack_top_state(self->stack, version);
  bool error_mode = parse_state == TS_STATE_ERROR;
  return parser__lex(self, parse_state, error_mode);

error:
  return NULL;
}

static bool parser__select_tree(Parser *self, TSTree *left, TSTree *right) {
  if (!left)
    return true;
  if (!right)
    return false;
  if (right->error_size < left->error_size) {
    LOG("select_smaller_error symbol:%s, over_symbol:%s",
        SYM_NAME(right->symbol), SYM_NAME(left->symbol));
    return true;
  }
  if (left->error_size < right->error_size) {
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
                                          unsigned my_error_count,
                                          unsigned my_error_cost) {
  if (self->finished_tree && self->finished_tree->error_size <= my_error_cost)
    return true;

  for (StackVersion i = 0, n = ts_stack_version_count(self->stack); i < n; i++) {
    if (i == version || ts_stack_is_halted(self->stack, i))
      continue;

    unsigned error_cost = ts_stack_error_cost(self->stack, i);
    unsigned error_count = ts_stack_error_count(self->stack, i);

    if ((error_count > my_error_count + 1) ||
        (error_count > my_error_count && error_cost >= my_error_cost) ||
        (my_error_count == 0 && error_cost > my_error_cost) ||
        (error_count == my_error_count &&
         error_cost >= my_error_cost + ERROR_COST_THRESHOLD)) {
      LOG("halt_other version:%u", i);
      ts_stack_halt(self->stack, i);
      continue;
    }

    if ((my_error_count > error_count + 1) ||
        (my_error_count > error_count && my_error_cost >= error_cost) ||
        (error_count == 0 && my_error_cost > error_cost) ||
        (my_error_count == error_count &&
         my_error_cost >= error_cost + ERROR_COST_THRESHOLD)) {
      return true;
    }
  }

  return false;
}

static bool parser__shift(Parser *self, StackVersion version, TSStateId state,
                          TSTree *lookahead, bool extra) {
  if (extra != lookahead->extra) {
    TSSymbolMetadata metadata =
      ts_language_symbol_metadata(self->language, lookahead->symbol);
    if (metadata.structural && ts_stack_version_count(self->stack) > 1) {
      CHECK(lookahead = ts_tree_make_copy(lookahead));
    } else {
      ts_tree_retain(lookahead);
    }
    lookahead->extra = extra;
  } else {
    ts_tree_retain(lookahead);
  }

  bool is_pending = lookahead->child_count > 0;
  CHECK(ts_stack_push(self->stack, version, lookahead, is_pending, state));
  ts_tree_release(lookahead);
  return true;

error:
  ts_tree_release(lookahead);
  return false;
}

static bool parser__switch_children(Parser *self, TSTree *tree,
                                    TSTree **children, size_t count) {
  self->scratch_tree.symbol = tree->symbol;
  self->scratch_tree.child_count = 0;
  ts_tree_set_children(&self->scratch_tree, count, children);
  if (parser__select_tree(self, tree, &self->scratch_tree)) {
    tree->size = self->scratch_tree.size;
    tree->padding = self->scratch_tree.padding;
    tree->error_size = self->scratch_tree.error_size;
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
                                TSSymbol symbol, unsigned count, bool extra,
                                bool fragile, bool allow_skipping) {
  size_t initial_version_count = ts_stack_version_count(self->stack);
  StackPopResult pop = ts_stack_pop_count(self->stack, version, count);
  switch (pop.status) {
    case StackPopFailed:
      goto error;
    case StackPopStoppedAtError:
      return (Reduction){ ReduceStoppedAtError, pop.slices.contents[0] };
    default:
      break;
  }

  const TSLanguage *language = self->language;
  TSSymbolMetadata metadata = ts_language_symbol_metadata(language, symbol);

  for (size_t i = 0; i < pop.slices.size; i++) {
    StackSlice slice = pop.slices.contents[i];

    size_t child_count = slice.trees.size;
    while (child_count > 0 && slice.trees.contents[child_count - 1]->extra)
      child_count--;

    TSTree *parent =
      ts_tree_make_node(symbol, child_count, slice.trees.contents, metadata);
    if (!parent) {
      ts_tree_array_delete(&slice.trees);
      goto error;
    }

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

    TSStateId new_state;
    if (extra) {
      parent->extra = true;
      new_state = state;
    } else {
      const TSParseAction *action =
        ts_language_last_action(language, state, symbol);
      assert(action->type == TSParseActionTypeShift ||
             action->type == TSParseActionTypeRecover);
      new_state = action->to_state;

      if (action->type == TSParseActionTypeRecover && child_count > 1 &&
          allow_skipping) {
        unsigned error_count = ts_stack_error_count(self->stack, slice.version);
        unsigned error_cost =
          ts_stack_error_cost(self->stack, slice.version) + 1;
        if (!parser__better_version_exists(self, slice.version, error_count,
                                           error_cost)) {
          StackVersion other_version =
            ts_stack_duplicate_version(self->stack, slice.version);
          CHECK(other_version != STACK_VERSION_NONE);

          CHECK(ts_stack_push(self->stack, other_version, parent, false,
                              TS_STATE_ERROR));
          for (size_t j = parent->child_count; j < slice.trees.size; j++) {
            TSTree *tree = slice.trees.contents[j];
            CHECK(ts_stack_push(self->stack, other_version, tree, false,
                                TS_STATE_ERROR));
          }
        }
      }
    }

    CHECK(parser__push(self, slice.version, parent, new_state));
    for (size_t j = parent->child_count; j < slice.trees.size; j++) {
      TSTree *tree = slice.trees.contents[j];
      CHECK(parser__push(self, slice.version, tree, new_state));
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

  return (Reduction){ ReduceSucceeded, pop.slices.contents[0] };

error:
  return (Reduction){ ReduceFailed, {} };
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
    TSTree *tree = trees_below->contents[trees_below->size - 1 - i];
    const TSParseAction *action =
      ts_language_last_action(self->language, state, tree->symbol);
    if (!action || action->type != TSParseActionTypeShift)
      return NULL;
    if (action->extra || tree->extra)
      continue;
    child_count++;
    state = action->to_state;
  }

  for (size_t i = 0; i < trees_above->size; i++) {
    TSTree *tree = trees_above->contents[i];
    const TSParseAction *action =
      ts_language_last_action(self->language, state, tree->symbol);
    if (!action || action->type != TSParseActionTypeShift)
      return NULL;
    if (action->extra || tree->extra)
      continue;
    child_count++;
    state = action->to_state;
  }

  const TSParseAction *actions =
    ts_language_actions(self->language, state, lookahead_symbol, count);

  if (*count > 0 && actions[*count - 1].type != TSParseActionTypeReduce) {
    (*count)--;
  }

  while (*count > 0 && actions[0].child_count < child_count) {
    actions++;
    (*count)--;
  }

  while (*count > 0 && actions[*count - 1].child_count > child_count) {
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

    TSStateId state_after_repair = repair_symbol_action->to_state;
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
      if (repair_reductions[j].symbol == repair->symbol) {
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

static RepairResult parser__repair_error(Parser *self, StackSlice slice,
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
      TSSymbol symbol = actions[i].symbol;
      size_t child_count = actions[i].child_count;
      if ((child_count > session.tree_count_above_error) ||
          (child_count == session.tree_count_above_error &&
           !ts_language_symbol_metadata(self->language, symbol).visible))
        CHECK(array_push(
          &self->reduce_actions,
          ((ReduceAction){.symbol = symbol, .count = child_count })));
    }
  }

  StackPopResult pop = ts_stack_iterate(
    self->stack, slice.version, parser__error_repair_callback, &session);
  CHECK(pop.status);

  if (!session.found_repair) {
    LOG("no_repair_found");
    ts_stack_remove_version(self->stack, slice.version);
    ts_tree_array_delete(&slice.trees);
    return RepairNoneFound;
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
  CHECK(array_grow(&skipped_children, skip_count));
  for (size_t i = count_below; i < children.size; i++)
    array_push(&skipped_children, children.contents[i]);

  TSTree *error = ts_tree_make_error_node(&skipped_children);
  CHECK(error);
  children.size = count_below;
  array_push(&children, error);

  for (size_t i = 0; i < slice.trees.size; i++)
    array_push(&children, slice.trees.contents[i]);
  array_delete(&slice.trees);

  TSTree *parent =
    ts_tree_make_node(symbol, children.size, children.contents,
                      ts_language_symbol_metadata(self->language, symbol));
  CHECK(parent);
  CHECK(parser__push(self, slice.version, parent, next_state));

  unsigned error_cost = ts_stack_error_cost(self->stack, slice.version);
  unsigned error_count = ts_stack_error_count(self->stack, slice.version);
  if (parser__better_version_exists(self, slice.version, error_count,
                                    error_cost)) {
    LOG("no_better_repair_found");
    ts_stack_halt(self->stack, slice.version);
    return RepairNoneFound;
  } else {
    LOG("repair_found sym:%s, child_count:%lu, skipped:%lu", SYM_NAME(symbol),
        repair.count, parent->error_size);
    return RepairSucceeded;
  }

error:
  ts_tree_array_delete(&slice.trees);
  return RepairFailed;
}

static void parser__start(Parser *self, TSInput input, TSTree *previous_tree) {
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

static bool parser__accept(Parser *self, StackVersion version) {
  StackPopResult pop = ts_stack_pop_all(self->stack, version);
  CHECK(pop.status);
  CHECK(pop.slices.size);

  for (size_t i = 0; i < pop.slices.size; i++) {
    StackSlice slice = pop.slices.contents[i];
    TreeArray trees = slice.trees;

    TSTree *root = NULL;
    if (trees.size == 1) {
      root = trees.contents[0];
      array_delete(&trees);
    } else {
      for (size_t j = trees.size - 1; j + 1 > 0; j--) {
        TSTree *child = trees.contents[j];
        if (!child->extra) {
          root = ts_tree_make_copy(child);
          root->child_count = 0;
          for (size_t k = 0; k < child->child_count; k++)
            ts_tree_retain(child->children[k]);
          CHECK(array_splice(&trees, j, 1, child->child_count, child->children));
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

  return true;

error:
  return false;
}

typedef enum {
  PotentialReductionsFailed,
  PotentialReductionsContinue,
  PotentialReductionsDone,
} PotentialReductionStatus;

static PotentialReductionStatus parser__do_potential_reductions(
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
          if (action.child_count > 0)
            CHECK(ts_reduce_action_set_add(
              &self->reduce_actions,
              (ReduceAction){
                .symbol = action.symbol, .count = action.child_count,
              }));
        default:
          break;
      }
    }
  }

  bool did_reduce = false;
  for (size_t i = 0; i < self->reduce_actions.size; i++) {
    ReduceAction action = self->reduce_actions.contents[i];
    Reduction reduction = parser__reduce(self, version, action.symbol,
                                         action.count, false, true, false);
    switch (reduction.status) {
      case ReduceFailed:
        goto error;
      case ReduceStoppedAtError:
        ts_tree_array_delete(&reduction.slice.trees);
        ts_stack_remove_version(self->stack, reduction.slice.version);
        continue;
      default:
        did_reduce = true;
        break;
    }
  }

  if (did_reduce) {
    if (has_shift_action) {
      return PotentialReductionsDone;
    } else {
      ts_stack_renumber_version(self->stack, previous_version_count, version);
      return PotentialReductionsContinue;
    }
  } else {
    return PotentialReductionsDone;
  }

error:
  return PotentialReductionsFailed;
}

typedef struct {
  Parser *parser;
  TSSymbol lookahead_symbol;
} SkipPrecedingTokensSession;

static StackIterateAction parser__repair_consumed_error_callback(
  void *payload, TSStateId state, TreeArray *trees, size_t tree_count,
  bool is_done, bool is_pending) {
  if (tree_count > 0 && state != TS_STATE_ERROR) {
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

static bool parser__repair_consumed_error(Parser *self, StackVersion version,
                                          TSSymbol lookahead_symbol) {
  SkipPrecedingTokensSession session = { self, lookahead_symbol };
  StackPopResult pop = ts_stack_iterate(
    self->stack, version, parser__repair_consumed_error_callback, &session);
  CHECK(pop.status);

  StackVersion last_slice_version = STACK_VERSION_NONE;
  for (size_t i = 0; i < pop.slices.size; i++) {
    StackSlice slice = pop.slices.contents[i];
    if (slice.version == last_slice_version) {
      ts_tree_array_delete(&slice.trees);
      continue;
    }

    last_slice_version = slice.version;
    TSTree *error = ts_tree_make_error_node(&slice.trees);
    CHECK(error);
    error->extra = true;
    TSStateId state = ts_stack_top_state(self->stack, slice.version);
    parser__push(self, slice.version, error, state);
  }

  return true;
error:
  return false;
}

static bool parser__handle_error(Parser *self, StackVersion version,
                                 TSSymbol lookahead_symbol) {
  unsigned error_cost = ts_stack_error_cost(self->stack, version);
  unsigned error_count = ts_stack_error_count(self->stack, version) + 1;
  if (parser__better_version_exists(self, version, error_count, error_cost)) {
    ts_stack_halt(self->stack, version);
    LOG("bail_on_error");
    return true;
  }

  LOG("handle_error");
  CHECK(parser__repair_consumed_error(self, version, lookahead_symbol));

  size_t previous_version_count = ts_stack_version_count(self->stack);
  for (StackVersion v = version; v < ts_stack_version_count(self->stack);) {
    switch (parser__do_potential_reductions(self, v)) {
      case PotentialReductionsFailed:
        goto error;
      case PotentialReductionsContinue:
        break;
      case PotentialReductionsDone:
        if (v == version) {
          v = previous_version_count;
        } else {
          v++;
        }
        break;
    }
  }

  CHECK(ts_stack_push(self->stack, version, NULL, false, TS_STATE_ERROR));
  while (ts_stack_version_count(self->stack) > previous_version_count) {
    CHECK(ts_stack_push(self->stack, previous_version_count, NULL, false,
                        TS_STATE_ERROR));
    assert(ts_stack_merge(self->stack, version, previous_version_count));
  }

  return true;

error:
  return false;
}

static bool parser__recover(Parser *self, StackVersion version, TSStateId state,
                            TSTree *lookahead) {
  if (lookahead->symbol == ts_builtin_sym_end) {
    LOG("recover_eof");
    TreeArray children = array_new();
    TSTree *parent = ts_tree_make_error_node(&children);
    CHECK(parser__push(self, version, parent, 1));
    return parser__accept(self, version);
  }

  unsigned error_cost = ts_stack_error_cost(self->stack, version);
  unsigned error_count = ts_stack_error_count(self->stack, version);
  if (parser__better_version_exists(self, version, error_count, error_cost)) {
    ts_stack_halt(self->stack, version);
    LOG("bail_on_recovery");
    return true;
  }

  LOG("recover state:%u", state);

  StackVersion new_version = ts_stack_duplicate_version(self->stack, version);
  CHECK(new_version != STACK_VERSION_NONE);
  CHECK(parser__shift(
    self, new_version, TS_STATE_ERROR, lookahead,
    ts_language_symbol_metadata(self->language, lookahead->symbol).extra));

  CHECK(parser__shift(self, version, state, lookahead, false));
  return true;

error:
  return false;
}

static bool parser__advance(Parser *self, StackVersion version,
                            ReusableNode *reusable_node) {
  bool validated_lookahead = false;
  TSTree *lookahead = parser__get_lookahead(self, version, reusable_node);
  CHECK(lookahead);

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
        CHECK(lookahead);
        continue;
      }

      validated_lookahead = true;
      LOG("lookahead sym:%s, size:%lu", SYM_NAME(lookahead->symbol),
          lookahead->size.chars);
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
                CHECK(lookahead);
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
            next_state = action.to_state;
            LOG("shift state:%u", next_state);
          }

          CHECK(
            parser__shift(self, version, next_state, lookahead, action.extra));

          if (lookahead == reusable_node->tree)
            parser__pop_reusable_node(reusable_node);

          ts_tree_release(lookahead);
          return true;
        }

        case TSParseActionTypeReduce: {
          if (reduction_stopped_at_error)
            continue;

          if (action.extra) {
            LOG("reduce_extra");
          } else {
            LOG("reduce sym:%s, child_count:%u", SYM_NAME(action.symbol),
                action.child_count);
          }

          Reduction reduction = parser__reduce(
            self, version, action.symbol, action.child_count, action.extra,
            (i < table_entry.action_count - 1), true);

          switch (reduction.status) {
            case ReduceFailed:
              goto error;
            case ReduceSucceeded:
              last_reduction_version = reduction.slice.version;
              break;
            case ReduceStoppedAtError: {
              reduction_stopped_at_error = true;
              switch (parser__repair_error(
                self, reduction.slice, lookahead->first_leaf.symbol,
                table_entry.actions, table_entry.action_count)) {
                case RepairFailed:
                  goto error;
                case RepairNoneFound:
                  break;
                case RepairSucceeded:
                  last_reduction_version = reduction.slice.version;
                  break;
              }
              break;
            }
          }
          break;
        }

        case TSParseActionTypeAccept: {
          if (ts_stack_error_count(self->stack, version) > 0)
            continue;

          LOG("accept");
          CHECK(parser__accept(self, version));

          ts_tree_release(lookahead);
          return true;
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

          CHECK(parser__recover(self, version, action.to_state, lookahead));

          if (lookahead == reusable_node->tree)
            parser__pop_reusable_node(reusable_node);

          ts_tree_release(lookahead);
          return true;
        }
      }
    }

    if (last_reduction_version != STACK_VERSION_NONE) {
      ts_stack_renumber_version(self->stack, last_reduction_version, version);
      LOG_STACK();
      continue;
    }

    switch (parser__breakdown_top_of_stack(self, version)) {
      case BreakdownFailed:
        goto error;
      case BreakdownPerformed:
        continue;
      case BreakdownAborted:
        break;
    }

    if (state == TS_STATE_ERROR) {
      return parser__push(self, version, lookahead, TS_STATE_ERROR);
    }

    CHECK(parser__handle_error(self, version, lookahead->symbol));

    if (ts_stack_is_halted(self->stack, version)) {
      ts_tree_release(lookahead);
      return true;
    }
  }

error:
  if (lookahead)
    ts_tree_release(lookahead);
  return false;
}

bool parser_init(Parser *self) {
  ts_lexer_init(&self->lexer);
  self->finished_tree = NULL;
  self->stack = NULL;
  array_init(&self->reduce_actions);

  self->stack = ts_stack_new();
  if (!self->stack)
    goto error;

  if (!array_grow(&self->reduce_actions, 4))
    goto error;

  return true;

error:
  if (self->stack) {
    ts_stack_delete(self->stack);
    self->stack = NULL;
  }
  if (self->reduce_actions.contents)
    array_delete(&self->reduce_actions);
  return false;
}

void parser_destroy(Parser *self) {
  if (self->stack)
    ts_stack_delete(self->stack);
  if (self->reduce_actions.contents)
    array_delete(&self->reduce_actions);
}

TSTree *parser_parse(Parser *self, TSInput input, TSTree *old_tree) {
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
            ts_stack_top_position(self->stack, version).rows + 1,
            ts_stack_top_position(self->stack, version).columns + 1);

        CHECK(parser__advance(self, version, &reusable_node));
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
  ts_tree_assign_parents(self->finished_tree);
  return self->finished_tree;

error:
  return NULL;
}
