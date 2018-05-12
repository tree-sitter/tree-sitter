#ifndef RUNTIME_TREE_H_
#define RUNTIME_TREE_H_

#ifdef __cplusplus
extern "C" {
#endif

struct TSTree {
  const Subtree *root;
  const TSLanguage *language;
};

TSTree *ts_tree_new(const Subtree *root, const TSLanguage *language);

#ifdef __cplusplus
}
#endif

#endif  // RUNTIME_TREE_H_
