#include "runtime/node.h"
#include "runtime/tree.h"

TSNode * ts_node_make(const TSTree *tree, TSNode *parent, size_t index, size_t start_position, const char **names) {
    if (parent) ts_node_retain(parent);
    TSNode *result = malloc(sizeof(TSNode));
    *result = (TSNode) {
        .ref_count = 1,
        .parent = parent,
        .index = index,
        .content = tree,
        .start_position = start_position,
        .names = names,
    };
    return result;
}

TSNode * ts_node_make_root(const TSTree *tree, const char **names) {
    while (ts_tree_is_wrapper(tree))
        tree = tree->children[0];
    return ts_node_make(tree, NULL, 0, 0, names);
}

void ts_node_retain(TSNode *node) {
    node->ref_count++;
}

void ts_node_release(TSNode *node) {
    node->ref_count--;
    if (node->ref_count == 0) {
        if (node->parent) ts_node_release(node->parent);
        free(node);
    }
}

size_t ts_node_pos(const TSNode *node) {
    return node->start_position + node->content->offset;
}

size_t ts_node_size(const TSNode *node) {
    return node->content->size;
}

int ts_node_eq(const TSNode *left, const TSNode *right) {
    return ts_tree_equals(left->content, right->content);
}

const char * ts_node_name(const TSNode *node) {
    return node->names[node->content->symbol];
}

const char * ts_node_string(const TSNode *node) {
    return ts_tree_string(node->content, node->names);
}

TSNode * ts_node_parent(TSNode *child) {
    return child->parent;
}

TSNode * ts_node_prev_sibling(TSNode *child) {
    return ts_node_child(child->parent, child->index - 1);
}

TSNode * ts_node_next_sibling(TSNode *child) {
    return ts_node_child(child->parent, child->index + 1);
}

TSNode * ts_node_child(TSNode *parent, size_t index) {
    size_t child_count;
    TSChildWithPosition *children = ts_tree_visible_children(parent->content, &child_count);
    if (child_count <= index)
        return NULL;
    size_t position = parent->start_position + children[index].position;
    return ts_node_make(children[index].tree, parent, index, position, parent->names);
}

TSNode * ts_node_leaf_at_pos(TSNode *parent, size_t position) {
    size_t child_count;
    TSChildWithPosition *children = ts_tree_visible_children(parent->content, &child_count);
    for (size_t i = 0; i < child_count; i++) {
        TSChildWithPosition child = children[i];
        size_t child_left = child.position + child.tree->offset;
        if (child_left > position)
            break;
        if (child_left + child.tree->size > position) {
            TSNode *node = ts_node_make(child.tree, parent, i, child.position, parent->names);
            TSNode *result = ts_node_leaf_at_pos(node, position);
            ts_node_release(node);
            return result;
        }
    }

    ts_node_retain(parent);
    return parent;
}
