#include "runtime/node.h"
#include "tree_sitter/parser.h"
#include "runtime/tree.h"

TSNode * ts_node_make(TSTree *tree, TSNode *parent, size_t position, TSParserConfig *config) {
    if (parent) ts_node_retain(parent);
    TSNode *result = malloc(sizeof(TSNode));
    *result = (TSNode) {
        .ref_count = 1,
        .parent = parent,
        .content = tree,
        .position = position,
        .config = config
    };
    return result;
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
    return node->position;
}

size_t ts_node_size(const TSNode *node) {
    return node->content->size;
}

const char * ts_node_name(const TSNode *node) {
    return node->config->symbol_names[node->content->symbol];
}

TSTree * ts_tree_child(const TSTree *tree, size_t goal_index, size_t *offset, size_t *children_seen) {
    *offset = 0;
    *children_seen = 0;
    size_t child_count;
    TSTree **children = ts_tree_children(tree, &child_count);

    if (!children) {
        *offset = tree->offset + tree->size;
    }

    for (size_t i = 0; i < child_count; i++) {
        size_t delta_index = 0, delta_offset = 0;
        TSTree *child = children[i];
        TSTree *result = NULL;

        if (ts_tree_is_visible(child)) {
            delta_offset = child->offset;
            if (*children_seen == goal_index) {
                result = child;
            } else {
                delta_index = 1;
                delta_offset += child->size;
            }
        } else {
            result = ts_tree_child(child, (goal_index - *children_seen), &delta_offset, &delta_index);
        }

        *offset += delta_offset;
        *children_seen += delta_index;

        if (result) {
            return result;
        }
    }

    return NULL;
}

const char * ts_node_string(const TSNode *node) {
    return ts_tree_string(node->content, node->config->symbol_names);
}

TSNode * ts_node_child(TSNode *parent, size_t goal_index) {
    size_t offset, index;
    TSTree *child = ts_tree_child(parent->content, goal_index, &offset, &index);
    if (child)
        return ts_node_make(child, parent, offset, parent->config);
    else
        return NULL;
}

TSNode * ts_node_leaf_at_pos(TSNode *parent, size_t child_index) {
    return NULL;
}
