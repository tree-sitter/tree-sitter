#include "test_helper.h"
#include "helpers/tree_helpers.h"
#include "helpers/point_helpers.h"
#include "runtime/subtree.h"
#include "runtime/length.h"

void assert_consistent(Subtree tree) {
  if (ts_subtree_child_count(tree) == 0) return;
  AssertThat(tree.ptr->children[0].ptr->padding, Equals<Length>(tree.ptr->padding));

  Length total_children_size = length_zero();
  for (size_t i = 0; i < tree.ptr->child_count; i++) {
    Subtree child = tree.ptr->children[i];
    assert_consistent(child);
    total_children_size = length_add(total_children_size, ts_subtree_total_size(child));
  }

  AssertThat(total_children_size, Equals<Length>(ts_subtree_total_size(tree)));
};

START_TEST

describe("Subtree", []() {
  enum {
    symbol1 = 1,
    symbol2,
    symbol3,
    symbol4,
    symbol5,
    symbol6,
    symbol7,
    symbol8,
    symbol9,
  };

  TSSymbolMetadata metadata_list[30] = {};

  TSLanguage language;
  language.symbol_metadata = metadata_list;

  SubtreePool pool;

  before_each([&]() {
    pool = ts_subtree_pool_new(10);
  });

  after_each([&]() {
    ts_subtree_pool_delete(&pool);
  });

  auto new_leaf = [&](TSSymbol symbol, Length padding, Length size, uint32_t bytes_scanned) {
    return ts_subtree_new_leaf(
      &pool, symbol, padding, size, bytes_scanned, 0, false, false, &language
    );
  };

  auto new_node = [&](TSSymbol symbol, vector<Subtree> children) {
    return ts_subtree_from_mut(ts_subtree_new_node(
      &pool, symbol, tree_array(children), 0, &language
    ));
  };

  describe("new_node", [&]() {
    Subtree tree1, tree2;

    before_each([&]() {
      tree1 = new_leaf(symbol1, {2, {0, 1}}, {5, {0, 4}}, 0);
      tree2 = new_leaf(symbol2, {1, {0, 1}}, {3, {0, 3}}, 0);
    });

    after_each([&]() {
      ts_subtree_release(&pool, tree1);
      ts_subtree_release(&pool, tree2);
    });

    it("computes its size and padding based on its child nodes", [&]() {
      ts_subtree_retain(tree1);
      ts_subtree_retain(tree2);
      Subtree parent = new_node(symbol3, {tree1, tree2});

      AssertThat(
        ts_subtree_size(parent),
        Equals<Length>(
          ts_subtree_size(tree1) + ts_subtree_padding(tree2) + ts_subtree_size(tree2)
        ));
      AssertThat(ts_subtree_padding(parent), Equals<Length>(ts_subtree_padding(tree1)));
      ts_subtree_release(&pool, parent);
    });

    describe("when the first node is fragile on the left side", [&]() {
      it("records that it is fragile on the left side", [&]() {
        MutableSubtree mutable_tree1 = ts_subtree_to_mut_unsafe(tree1);
        mutable_tree1.ptr->fragile_left = true;
        mutable_tree1.ptr->extra = true;

        ts_subtree_retain(tree1);
        ts_subtree_retain(tree2);
        Subtree parent = new_node(symbol3, {tree1, tree2});

        AssertThat(ts_subtree_fragile_left(parent), IsTrue());
        AssertThat(ts_subtree_fragile_right(parent), IsFalse());
        ts_subtree_release(&pool, parent);
      });
    });

    describe("when the last node is fragile on the right side", [&]() {
      it("records that it is fragile on the right side", [&]() {
        MutableSubtree mutable_tree2 = ts_subtree_to_mut_unsafe(tree2);
        mutable_tree2.ptr->fragile_right = true;
        mutable_tree2.ptr->extra = true;

        ts_subtree_retain(tree1);
        ts_subtree_retain(tree2);
        Subtree parent = new_node(symbol3, {tree1, tree2});

        AssertThat(ts_subtree_fragile_left(parent), IsFalse());
        AssertThat(ts_subtree_fragile_right(parent), IsTrue());
        ts_subtree_release(&pool, parent);
      });
    });

    describe("when the outer nodes aren't fragile on their outer side", [&]() {
      it("records that it is not fragile", [&]() {
        MutableSubtree mutable_tree1 = ts_subtree_to_mut_unsafe(tree1);
        MutableSubtree mutable_tree2 = ts_subtree_to_mut_unsafe(tree2);
        mutable_tree1.ptr->fragile_right = true;
        mutable_tree2.ptr->fragile_left = true;

        ts_subtree_retain(tree1);
        ts_subtree_retain(tree2);
        Subtree parent = new_node(symbol3, {tree1, tree2});

        AssertThat(ts_subtree_fragile_left(parent), IsFalse());
        AssertThat(ts_subtree_fragile_right(parent), IsFalse());
        ts_subtree_release(&pool, parent);
      });
    });
  });

  describe("edit", [&]() {
    Subtree tree;

    before_each([&]() {
      tree = new_node(symbol1, {
        new_leaf(symbol2, {2, {0, 2}}, {3, {0, 3}}, 0),
        new_leaf(symbol3, {2, {0, 2}}, {3, {0, 3}}, 0),
        new_leaf(symbol4, {2, {0, 2}}, {3, {0, 3}}, 0),
      });

      AssertThat(tree.ptr->padding, Equals<Length>({2, {0, 2}}));
      AssertThat(tree.ptr->size, Equals<Length>({13, {0, 13}}));
    });

    after_each([&]() {
      ts_subtree_release(&pool, tree);
    });

    it("does not mutate the argument", [&]() {
      TSInputEdit edit;
      edit.start_byte = 1;
      edit.old_end_byte = 1;
      edit.new_end_byte = 2;
      edit.start_point = {0, 1};
      edit.old_end_point = {0, 1};
      edit.new_end_point = {0, 2};

      ts_subtree_retain(tree);
      Subtree new_tree = ts_subtree_edit(tree, &edit, &pool);
      assert_consistent(tree);
      assert_consistent(new_tree);

      AssertThat(ts_subtree_has_changes(tree), IsFalse());
      AssertThat(ts_subtree_padding(tree), Equals<Length>({2, {0, 2}}));
      AssertThat(ts_subtree_size(tree), Equals<Length>({13, {0, 13}}));

      AssertThat(ts_subtree_has_changes(tree.ptr->children[0]), IsFalse());
      AssertThat(ts_subtree_padding(tree.ptr->children[0]), Equals<Length>({2, {0, 2}}));
      AssertThat(ts_subtree_size(tree.ptr->children[0]), Equals<Length>({3, {0, 3}}));

      AssertThat(ts_subtree_has_changes(tree.ptr->children[1]), IsFalse());
      AssertThat(ts_subtree_padding(tree.ptr->children[1]), Equals<Length>({2, {0, 2}}));
      AssertThat(ts_subtree_size(tree.ptr->children[1]), Equals<Length>({3, {0, 3}}));

      ts_subtree_release(&pool, new_tree);
    });

    describe("edits within a tree's padding", [&]() {
      it("resizes the padding of the tree and its leftmost descendants", [&]() {
        TSInputEdit edit;
        edit.start_byte = 1;
        edit.old_end_byte = 1;
        edit.new_end_byte = 2;
        edit.start_point = {0, 1};
        edit.old_end_point = {0, 1};
        edit.new_end_point = {0, 2};

        tree = ts_subtree_edit(tree, &edit, &pool);
        assert_consistent(tree);

        AssertThat(ts_subtree_has_changes(tree), IsTrue());
        AssertThat(ts_subtree_padding(tree), Equals<Length>({3, {0, 3}}));
        AssertThat(ts_subtree_size(tree), Equals<Length>({13, {0, 13}}));

        AssertThat(ts_subtree_has_changes(tree.ptr->children[0]), IsTrue());
        AssertThat(ts_subtree_padding(tree.ptr->children[0]), Equals<Length>({3, {0, 3}}));
        AssertThat(ts_subtree_size(tree.ptr->children[0]), Equals<Length>({3, {0, 3}}));

        AssertThat(ts_subtree_has_changes(tree.ptr->children[1]), IsFalse());
        AssertThat(ts_subtree_padding(tree.ptr->children[1]), Equals<Length>({2, {0, 2}}));
        AssertThat(ts_subtree_size(tree.ptr->children[1]), Equals<Length>({3, {0, 3}}));
      });
    });

    describe("edits that start in a tree's padding but extend into its content", [&]() {
      it("shrinks the content to compensate for the expanded padding", [&]() {
        TSInputEdit edit;
        edit.start_byte = 1;
        edit.old_end_byte = 4;
        edit.new_end_byte = 5;
        edit.start_point = {0, 1};
        edit.old_end_point = {0, 4};
        edit.new_end_point = {0, 5};

        tree = ts_subtree_edit(tree, &edit, &pool);
        assert_consistent(tree);

        AssertThat(ts_subtree_has_changes(tree), IsTrue());
        AssertThat(ts_subtree_padding(tree), Equals<Length>({5, {0, 5}}));
        AssertThat(ts_subtree_size(tree), Equals<Length>({11, {0, 11}}));

        AssertThat(ts_subtree_has_changes(tree.ptr->children[0]), IsTrue());
        AssertThat(ts_subtree_padding(tree.ptr->children[0]), Equals<Length>({5, {0, 5}}));
        AssertThat(ts_subtree_size(tree.ptr->children[0]), Equals<Length>({1, {0, 1}}));
      });
    });

    describe("insertions at the edge of a tree's padding", [&]() {
      it("expands the tree's padding", [&]() {
        TSInputEdit edit;
        edit.start_byte = 2;
        edit.old_end_byte = 2;
        edit.new_end_byte = 4;
        edit.start_point = {0, 2};
        edit.old_end_point = {0, 2};
        edit.new_end_point = {0, 4};

        tree = ts_subtree_edit(tree, &edit, &pool);
        assert_consistent(tree);

        AssertThat(ts_subtree_has_changes(tree), IsTrue());
        AssertThat(ts_subtree_padding(tree), Equals<Length>({4, {0, 4}}));
        AssertThat(ts_subtree_size(tree), Equals<Length>({13, {0, 13}}));

        AssertThat(ts_subtree_has_changes(tree.ptr->children[0]), IsTrue());
        AssertThat(ts_subtree_padding(tree.ptr->children[0]), Equals<Length>({4, {0, 4}}));
        AssertThat(ts_subtree_size(tree.ptr->children[0]), Equals<Length>({3, {0, 3}}));

        AssertThat(ts_subtree_has_changes(tree.ptr->children[1]), IsFalse());
      });
    });

    describe("replacements starting at the edge of a tree's padding", [&]() {
      it("resizes the content and not the padding", [&]() {
        TSInputEdit edit;
        edit.start_byte = 2;
        edit.old_end_byte = 4;
        edit.new_end_byte = 7;
        edit.start_point = {0, 2};
        edit.old_end_point = {0, 4};
        edit.new_end_point = {0, 7};

        tree = ts_subtree_edit(tree, &edit, &pool);
        assert_consistent(tree);

        AssertThat(ts_subtree_has_changes(tree), IsTrue());
        AssertThat(ts_subtree_padding(tree), Equals<Length>({2, {0, 2}}));
        AssertThat(ts_subtree_size(tree), Equals<Length>({16, {0, 16}}));

        AssertThat(ts_subtree_has_changes(tree.ptr->children[0]), IsTrue());
        AssertThat(ts_subtree_padding(tree.ptr->children[0]), Equals<Length>({2, {0, 2}}));
        AssertThat(ts_subtree_size(tree.ptr->children[0]), Equals<Length>({6, {0, 6}}));

        AssertThat(ts_subtree_has_changes(tree.ptr->children[1]), IsFalse());
      });
    });

    describe("deletions that span more than one child node", [&]() {
      it("shrinks subsequent child nodes", [&]() {
        TSInputEdit edit;
        edit.start_byte = 1;
        edit.old_end_byte = 11;
        edit.new_end_byte = 4;
        edit.start_point = {0, 1};
        edit.old_end_point = {0, 11};
        edit.new_end_point = {0, 4};

        tree = ts_subtree_edit(tree, &edit, &pool);
        assert_consistent(tree);

        AssertThat(ts_subtree_has_changes(tree), IsTrue());
        AssertThat(ts_subtree_padding(tree), Equals<Length>({4, {0, 4}}));
        AssertThat(ts_subtree_size(tree), Equals<Length>({4, {0, 4}}));

        AssertThat(ts_subtree_has_changes(tree.ptr->children[0]), IsTrue());
        AssertThat(ts_subtree_padding(tree.ptr->children[0]), Equals<Length>({4, {0, 4}}));
        AssertThat(ts_subtree_size(tree.ptr->children[0]), Equals<Length>({0, {0, 0}}));

        AssertThat(ts_subtree_has_changes(tree.ptr->children[1]), IsTrue());
        AssertThat(ts_subtree_padding(tree.ptr->children[1]), Equals<Length>({0, {0, 0}}));
        AssertThat(ts_subtree_size(tree.ptr->children[1]), Equals<Length>({0, {0, 0}}));

        AssertThat(ts_subtree_has_changes(tree.ptr->children[2]), IsTrue());
        AssertThat(ts_subtree_padding(tree.ptr->children[2]), Equals<Length>({1, {0, 1}}));
        AssertThat(ts_subtree_size(tree.ptr->children[2]), Equals<Length>({3, {0, 3}}));
      });
    });

    describe("edits within a tree's range of scanned bytes", [&]() {
      it("marks preceding trees as changed", [&]() {
        MutableSubtree mutable_child = ts_subtree_to_mut_unsafe(tree.ptr->children[0]);
        mutable_child.ptr->bytes_scanned = 7;

        TSInputEdit edit;
        edit.start_byte = 6;
        edit.old_end_byte = 7;
        edit.new_end_byte = 7;
        edit.start_point = {0, 6};
        edit.old_end_point = {0, 7};
        edit.new_end_point = {0, 7};

        tree = ts_subtree_edit(tree, &edit, &pool);
        assert_consistent(tree);

        AssertThat(ts_subtree_has_changes(tree.ptr->children[0]), IsTrue());
      });
    });

    describe("insertions at the end of the tree", [&]() {
      it("extends the tree's content", [&]() {
        TSInputEdit edit;
        edit.start_byte = 15;
        edit.old_end_byte = 15;
        edit.new_end_byte = 16;
        edit.start_point = {0, 15};
        edit.old_end_point = {0, 15};
        edit.new_end_point = {0, 16};

        tree = ts_subtree_edit(tree, &edit, &pool);
        assert_consistent(tree);

        AssertThat(ts_subtree_size(tree).bytes, Equals(14u));
        AssertThat(ts_subtree_has_changes(tree.ptr->children[2]), IsTrue());
        AssertThat(ts_subtree_size(tree.ptr->children[2]).bytes, Equals(4u));
      });
    });

    describe("edits beyond the end of the tree", [&]() {
      it("does not change the tree", [&]() {
        TSInputEdit edit;
        edit.start_byte = 15;
        edit.old_end_byte = 16;
        edit.new_end_byte = 17;
        edit.start_point = {0, 15};
        edit.old_end_point = {0, 16};
        edit.new_end_point = {0, 17};

        tree = ts_subtree_edit(tree, &edit, &pool);
        assert_consistent(tree);

        AssertThat(ts_subtree_size(tree).bytes, Equals(13u));
        AssertThat(ts_subtree_size(tree.ptr->children[2]).bytes, Equals(3u));
      });
    });
  });

  describe("eq", [&]() {
    Subtree leaf;

    before_each([&]() {
      leaf = new_leaf(symbol1, {2, {1, 1}}, {5, {1, 4}}, 0);
    });

    after_each([&]() {
      ts_subtree_release(&pool, leaf);
    });

    it("returns true for identical trees", [&]() {
      Subtree leaf_copy = new_leaf(symbol1, {2, {1, 1}}, {5, {1, 4}}, 0);
      AssertThat(ts_subtree_eq(leaf, leaf_copy), IsTrue());

      Subtree parent = new_node(symbol2, {leaf, leaf_copy});
      ts_subtree_retain(leaf);
      ts_subtree_retain(leaf_copy);

      Subtree parent_copy = new_node(symbol2, {leaf, leaf_copy});
      ts_subtree_retain(leaf);
      ts_subtree_retain(leaf_copy);

      AssertThat(ts_subtree_eq(parent, parent_copy), IsTrue());

      ts_subtree_release(&pool, leaf_copy);
      ts_subtree_release(&pool, parent);
      ts_subtree_release(&pool, parent_copy);
    });

    it("returns false for trees with different symbols", [&]() {
      Subtree different_leaf = new_leaf(
        ts_subtree_symbol(leaf) + 1,
        ts_subtree_padding(leaf),
        ts_subtree_size(leaf),
        ts_subtree_bytes_scanned(leaf)
      );

      AssertThat(ts_subtree_eq(leaf, different_leaf), IsFalse());
      ts_subtree_release(&pool, different_leaf);
    });

    it("returns false for trees with different options", [&]() {
      Subtree different_leaf = new_leaf(
        ts_subtree_symbol(leaf),
        ts_subtree_padding(leaf),
        ts_subtree_size(leaf),
        ts_subtree_bytes_scanned(leaf)
      );
      ts_subtree_to_mut_unsafe(different_leaf).ptr->visible = !ts_subtree_visible(leaf);
      AssertThat(ts_subtree_eq(leaf, different_leaf), IsFalse());
      ts_subtree_release(&pool, different_leaf);
    });

    it("returns false for trees with different paddings or sizes", [&]() {
      Subtree different_leaf = new_leaf(
        ts_subtree_symbol(leaf),
        {},
        ts_subtree_size(leaf),
        ts_subtree_bytes_scanned(leaf)
      );
      AssertThat(ts_subtree_eq(leaf, different_leaf), IsFalse());
      ts_subtree_release(&pool, different_leaf);

      different_leaf = new_leaf(symbol1, ts_subtree_padding(leaf), {}, ts_subtree_bytes_scanned(leaf));
      AssertThat(ts_subtree_eq(leaf, different_leaf), IsFalse());
      ts_subtree_release(&pool, different_leaf);
    });

    it("returns false for trees with different children", [&]() {
      Subtree leaf2 = new_leaf(symbol2, {1, {0, 1}}, {3, {0, 3}}, 0);
      Subtree parent = new_node(symbol2, {leaf, leaf2});
      ts_subtree_retain(leaf);
      ts_subtree_retain(leaf2);

      Subtree different_parent = new_node(symbol2, {leaf2, leaf});
      ts_subtree_retain(leaf2);
      ts_subtree_retain(leaf);

      AssertThat(ts_subtree_eq(different_parent, parent), IsFalse());
      AssertThat(ts_subtree_eq(parent, different_parent), IsFalse());

      ts_subtree_release(&pool, leaf2);
      ts_subtree_release(&pool, parent);
      ts_subtree_release(&pool, different_parent);
    });
  });

  describe("last_external_token", [&]() {
    Length padding = {1, {0, 1}};
    Length size = {2, {0, 2}};

    auto make_external = [](Subtree tree) {
      ts_external_scanner_state_init(
        &ts_subtree_to_mut_unsafe(tree).ptr->external_scanner_state,
        NULL, 0
      );
      return tree;
    };

    it("returns the last serialized external token state in the given tree", [&]() {
      Subtree tree1, tree2, tree3, tree4, tree5, tree6, tree7, tree8, tree9;

      tree1 = new_node(symbol1, {
        (tree2 = new_node(symbol2, {
          (tree3 = make_external(ts_subtree_new_leaf(&pool, symbol3, padding, size, 0, 0, true, false, &language))),
          (tree4 = new_leaf(symbol4, padding, size, 0)),
          (tree5 = new_leaf(symbol5, padding, size, 0)),
        })),
        (tree6 = new_node(symbol6, {
          (tree7 = new_node(symbol7, {
            (tree8 = new_leaf(symbol8, padding, size, 0)),
          })),
          (tree9 = new_leaf(symbol9, padding, size, 0)),
        })),
      });

      auto token = ts_subtree_last_external_token(tree1);
      AssertThat(token.ptr, Equals(tree3.ptr));

      ts_subtree_release(&pool, tree1);
    });
  });
});

END_TEST
