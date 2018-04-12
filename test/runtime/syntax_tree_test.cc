#include "test_helper.h"
#include "helpers/record_alloc.h"
#include "runtime/alloc.h"
#include "runtime/syntax_tree.h"
#include "helpers/random_helpers.h"

ostream &operator<<(ostream &stream, const TSNode2 &node) {
  stream << "{index: " << node.index << ", symbol: " << ts_node2_symbol(&node) << "}";
  return stream;
}

static TSLanguage test_language() {
  static const char *symbol_names[] = {
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine",
    "ten"
  };

  static const TSSymbolMetadata symbol_metadata[] = {
    (TSSymbolMetadata){true, true},
    (TSSymbolMetadata){true, true},
    (TSSymbolMetadata){true, true},
    (TSSymbolMetadata){true, true},
    (TSSymbolMetadata){true, true},
    (TSSymbolMetadata){true, true},
    (TSSymbolMetadata){true, true},
    (TSSymbolMetadata){true, true},
    (TSSymbolMetadata){true, true},
    (TSSymbolMetadata){true, true},
  };

  TSLanguage result;
  result.symbol_names = symbol_names;
  result.symbol_metadata = symbol_metadata;
  return result;
};

START_TEST

describe("SyntaxTree", [&]() {
  TSLanguage language = test_language();

  before_each([&]() {
    TREE_BRANCHING_FACTOR = 3;
    record_alloc::start();
  });

  after_each([&]() {
    TREE_BRANCHING_FACTOR = DEFAULT_TREE_BRANCHING_FACTOR;
    AssertThat(record_alloc::outstanding_allocation_indices(), IsEmpty());
  });

  it("can push individual elements", [&]() {
    TreeBuilder builder = ts_tree_builder_new();

    ts_tree_builder_push_node(&builder, SyntaxNode{.symbol = 1, .child_count = 0});
    ts_tree_builder_push_node(&builder, SyntaxNode{.symbol = 2, .child_count = 0});
    ts_tree_builder_push_node(&builder, SyntaxNode{.symbol = 3, .child_count = 2});
    ts_tree_builder_push_node(&builder, SyntaxNode{.symbol = 4, .child_count = 0});
    ts_tree_builder_push_node(&builder, SyntaxNode{.symbol = 5, .child_count = 2});
    ts_tree_builder_push_node(&builder, SyntaxNode{.symbol = 6, .child_count = 0});
    ts_tree_builder_push_node(&builder, SyntaxNode{.symbol = 7, .child_count = 0});
    ts_tree_builder_push_node(&builder, SyntaxNode{.symbol = 8, .child_count = 3});

    SyntaxTree *tree = ts_tree_builder_build(&builder, &language);

    TSNode2 root = ts_syntax_tree_root_node(tree);
    AssertThat(ts_node2_symbol(&root), Equals(8u));
    AssertThat(ts_node2_child_count(&root), Equals(3u));

    TSNode2 child1 = ts_node2_child(&root, 0);
    AssertThat(ts_node2_symbol(&child1), Equals(5u));
    AssertThat(ts_node2_child_count(&child1), Equals(2u));

    TSNode2 child2 = ts_node2_child(&root, 1);
    AssertThat(ts_node2_symbol(&child2), Equals(6u));
    AssertThat(ts_node2_child_count(&child2), Equals(0u));

    TSNode2 child3 = ts_node2_child(&root, 2);
    AssertThat(ts_node2_symbol(&child3), Equals(7u));
    AssertThat(ts_node2_child_count(&child3), Equals(0u));

    AssertThat(ts_node2_parent(&child1), Equals(root));
    AssertThat(ts_node2_parent(&child2), Equals(root));
    AssertThat(ts_node2_parent(&child3), Equals(root));

    ts_syntax_tree_delete(tree);
  });

/*
  it("can push slices of other lists", [&]() {
    ParentInfoList list1 = parent_info_list_new();
    ParentInfoList list2 = parent_info_list_new();

    for (unsigned i = 0; i < 12; i++) {
      parent_info_list_push_value(&list1, ParentInfo{.index = i});
    }

    ParentInfoIter iter1 = parent_info_list_begin(&list1);
    ParentInfoIter iter2 = parent_info_list_end(&list1);
    parent_info_iter_inc(&iter1, 1);
    parent_info_iter_dec(&iter2, 1);
    parent_info_list_push_range(&list2, iter1, iter2);
    parent_info_list_push_value(&list2, ParentInfo{.index = 100});

    AssertThat(get_all(&list2), Equals<vector<ParentInfo>>({
      ParentInfo{.index = 1},
      ParentInfo{.index = 2},
      ParentInfo{.index = 3},
      ParentInfo{.index = 4},
      ParentInfo{.index = 5},
      ParentInfo{.index = 6},
      ParentInfo{.index = 7},
      ParentInfo{.index = 8},
      ParentInfo{.index = 9},
      ParentInfo{.index = 10},
      ParentInfo{.index = 100},
    }));

    parent_info_list_delete(&list1);
    parent_info_list_delete(&list2);
  });

  it("handles random reads and writes", [&]() {
    ParentInfoList list1 = parent_info_list_new();
    vector<ParentInfo> reference_list1;

    // populate an initial list
    for (unsigned i = 0; i < 50; i++) {
      ParentInfo info = {.index = random_unsigned(50)};
      parent_info_list_push_value(&list1, info);
      reference_list1.push_back(info);
    }

    AssertThat(get_all(&list1), Equals(reference_list1));

    for (unsigned i = 0; i < 10; i++) {
      ParentInfoList list2 = parent_info_list_new();
      vector<ParentInfo> reference_list2;
      ParentInfoIter iter = parent_info_list_begin(&list1);
      ParentInfoIter end = parent_info_list_end(&list1);
      auto reference_iter = reference_list1.begin();
      auto reference_end = reference_list1.end();

      // create a new list that reuses portions of the old list
      while (!parent_info_iter_eq(&iter, &end)) {
        auto next_reference_iter = reference_iter;
        auto next_iter = iter;

        // Reuse some entries from the old list
        if (random_unsigned(2)) {
          unsigned count_to_reuse = 1 + random_unsigned(min(16, reference_end - reference_iter));

          parent_info_iter_inc(&next_iter, count_to_reuse);
          next_reference_iter += count_to_reuse;

          parent_info_list_push_range(&list2, iter, next_iter);
          reference_list2.insert(reference_list2.end(), reference_iter, next_reference_iter);
        }

        // Insert some new entries and skip some others
        else {
          unsigned count_to_skip = 1 + random_unsigned(min(16, reference_end - reference_iter));
          unsigned count_to_insert = random_unsigned(16);

          parent_info_iter_inc(&next_iter, count_to_skip);
          next_reference_iter += count_to_skip;

          for (unsigned j = 0; j < count_to_insert; j++) {
            ParentInfo info = {.index = random_unsigned(50)};
            parent_info_list_push_value(&list2, info);
            reference_list2.push_back(info);
          }
        }

        iter = next_iter;
        reference_iter = next_reference_iter;
      }

      AssertThat(get_all(&list1), Equals(reference_list1));
      AssertThat(get_all(&list2), Equals(reference_list2));

      parent_info_list_delete(&list1);
      list1 = list2;
      reference_list1 = reference_list2;
    }

    parent_info_list_delete(&list1);
  });
*/
});

END_TEST

bool operator==(const TSNode2 &left, const TSNode2 &right) {
  return (
    left.index == right.index &&
    ts_node2_symbol(&left) == ts_node2_symbol(&right)
  );
}
