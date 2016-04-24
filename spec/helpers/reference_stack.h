#ifndef HELPERS_REFERENCE_STACK_H_
#define HELPERS_REFERENCE_STACK_H_

#include "runtime/stack.h"
#include <vector>
#include <stack>

struct PotentialSlice;

class ReferenceStack {
 public:
  ReferenceStack();
  ~ReferenceStack();

  int head_count() const;
  TSStateId top_state(int head_index) const;
  TSLength top_position(int head_index) const;

  StackVersion push(int head_index, TSTree *tree, bool is_verifying, TSStateId state);
  StackPopResult pop_count(int head_index, int count);
  StackPopResult pop_until(int head_index, StackIterateCallback, void *);

  void remove_head(int head_index);
  void clear();

 private:
  struct NodeId {
    TSStateId state;
    TSLength position;

    bool operator==(const NodeId &other) const {
      return state == other.state && ts_length_eq(position, other.position);
    }
  };

  struct Node {
    NodeId id;
    TSTree *tree;
    bool is_verifying;
  };

  typedef std::stack<Node> Version;

  int find_or_add_node_id(NodeId id);
  std::vector<TSTree *> merge_trees(std::vector<TSTree *>, std::vector<TSTree *>) const;
  StackSliceArray finalize_slices(const std::vector<PotentialSlice> &) const;

  std::vector<Version> versions;
  std::vector<NodeId> version_ids;
  void *tree_selection_payload;
};

#endif  // HELPERS_REFERENCE_STACK_H_
