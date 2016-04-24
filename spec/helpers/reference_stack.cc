#include "helpers/reference_stack.h"
#include <vector>

using std::vector;

struct PotentialSlice {
  StackVersion head_index;
  vector<TSTree *> trees;
};

ReferenceStack::ReferenceStack() {
  clear();
}

ReferenceStack::~ReferenceStack() {
  clear();
}

void ReferenceStack::clear() {
  for (Version &version : versions) {
    while (!version.empty()) {
      ts_tree_release(version.top().tree);
      version.pop();
    }
  }

  Version initial_version;
  initial_version.push(Node{{0, ts_length_zero()}, NULL, false});

  versions = {initial_version};
  version_ids = {initial_version.top().id};
}

int ReferenceStack::head_count() const {
  return version_ids.size();
}

TSStateId ReferenceStack::top_state(int head_index) const {
  return version_ids[head_index].state;
}

TSLength ReferenceStack::top_position(int head_index) const {
  return version_ids[head_index].position;
}

StackVersion ReferenceStack::push(int head_index, TSTree *tree, bool is_verifying, TSStateId state) {
  NodeId id = version_ids[head_index];
  NodeId new_id = {state, ts_length_add(id.position, ts_tree_total_size(tree))};

  StackVersion i = -1, existing_id = -1;
  for (Version &version : versions) {
    i++;
    Node top = version.top();
    if (top.id == new_id) {
      existing_id = i;
    } else if (top.id == id) {
      ts_tree_retain(tree);
      version.push(Node{new_id, tree, false});
    }
  }

  if (existing_id != -1) {
    version_ids.erase(version_ids.begin() + head_index);
    return existing_id;
  } else {
    version_ids[head_index] = new_id;
    return head_index;
  }
}

StackPopResult ReferenceStack::pop_count(int head_index, int goal_count) {
  NodeId id = version_ids[head_index];

  vector<Version> new_versions;
  vector<PotentialSlice> potential_slices;

  for (const Version &version : versions)
    if (version.top().id == id) {
      PotentialSlice potential_slice;
      Version new_version = version;
      size_t tree_count = 0;

      while (!new_version.empty()) {
        TSTree *tree = new_version.top().tree;
        if (tree->symbol == ts_builtin_sym_error)
          return StackPopResult{
            StackPopResult::StackPopStoppedAtError,
            finalize_slices({potential_slice}),
          };
        if (!tree->extra)
          tree_count++;

        potential_slice.trees.insert(potential_slice.trees.begin(), tree);
        new_version.pop();

        if (tree_count == goal_count) {
          potential_slice.head_index = find_or_add_node_id(new_version.top().id);
          new_versions.push_back(new_version);
          potential_slices.push_back(potential_slice);
          break;
        }
      }
    }

  for (auto i = potential_slices.begin(); i != potential_slices.end();) {
    bool merged = false;
    for (auto j = potential_slices.begin(); j < i; ++j) {
      if (i->head_index == j->head_index) {
        merged = true;
        j->trees = merge_trees(j->trees, i->trees);
        potential_slices.erase(i);
        break;
      }
    }
    if (!merged) ++i;
  }

  versions.insert(versions.end(), new_versions.begin(), new_versions.end());

  return StackPopResult{
    StackPopResult::StackPopSucceeded,
    finalize_slices(potential_slices),
  };
}

// Private

int ReferenceStack::find_or_add_node_id(NodeId id) {
  for (int i = 0; i < version_ids.size(); i++)
    if (version_ids[i] == id)
      return i;
  version_ids.push_back(id);
  return version_ids.size() - 1;
}

vector<TSTree *> ReferenceStack::merge_trees(vector<TSTree *> left, vector<TSTree *> right) const {
  return left;
}

StackSliceArray ReferenceStack::finalize_slices(const vector<PotentialSlice> &potential_slices) const {
  StackSliceArray result = array_new();
  for (const PotentialSlice &potential_slice : potential_slices) {
    StackSlice slice{array_new(), potential_slice.head_index};
    for (TSTree *tree : potential_slice.trees) {
      ts_tree_retain(tree);
      array_push(&slice.trees, tree);
    }
    array_push(&result, slice);
  }
  return result;
}
