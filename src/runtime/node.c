#include "runtime/node.h"
#include "tree_sitter/parser.h"
#include "runtime/tree.h"

TSNode * ts_node_make(const TSTree *tree, TSNode *parent, size_t index, size_t start_position, TSParserConfig *config) {
    if (parent) ts_node_retain(parent);
    TSNode *result = malloc(sizeof(TSNode));
    *result = (TSNode) {
        .ref_count = 1,
        .parent = parent,
        .index = index,
        .content = tree,
        .start_position = start_position,
        .config = config
    };
    return result;
}

TSNode * ts_node_make_root(const TSTree *tree, TSParserConfig *config) {
    while (ts_tree_is_wrapper(tree))
        tree = tree->children[0];
    return ts_node_make(tree, NULL, 0, 0, config);
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
    return node->config->symbol_names[node->content->symbol];
}

const char * ts_node_string(const TSNode *node) {
    return ts_tree_string(node->content, node->config->symbol_names);
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
    return ts_node_make(children[index].tree, parent, index, position, parent->config);
}

TSNode * ts_node_leaf_at_pos(TSNode *parent, size_t child_index) {
    return NULL;
}
