//
//  zipper.c
//  jsitter
//
//  Created by Andrey Zaytsev on 12.06.19.
//

#include "tree_sitter/api.h"
#include "./alloc.h"
#include "./language.h"
#include "./tree.h"

typedef struct _TSZipper {
    const struct _TSZipper *parent;
    const TSSymbol *parent_alias_sequence;
    Subtree subtree;
    uint32_t byte_offset;
    uint32_t child_index;
    uint32_t structural_child_index;
} _TSZipper;

bool __is_visible(_TSZipper *zip) {
    if (ts_subtree_visible(zip->subtree)) {
        return true;
    } else {
        bool extra = ts_subtree_extra(zip->subtree);
        if (!extra && zip->parent_alias_sequence) {
            return zip->parent_alias_sequence[zip->structural_child_index];
        } else {
            return false;
        }
    }
}

bool __ts_zipper_right(const _TSZipper *zip, _TSZipper *result) {
    if (!zip->parent) {
        return false;
    }
    Subtree parent_subtree = zip->parent->subtree;
    if (zip->child_index == parent_subtree.ptr->child_count - 1) {
        return false;
    }
    const Subtree sibling = parent_subtree.ptr->children[zip->child_index + 1];
    
    bool extra = ts_subtree_extra(zip->subtree);
    uint32_t structural_child_index;
    if (!extra && zip->parent_alias_sequence) {
        structural_child_index = zip->structural_child_index + 1;
    } else {
        structural_child_index = zip->structural_child_index;
    }
    
    *result = (_TSZipper) {
        .parent = zip->parent,
        .parent_alias_sequence = zip->parent_alias_sequence,
        .subtree = sibling,
        .byte_offset = ts_subtree_size(zip->subtree).bytes + ts_subtree_padding(sibling).bytes,
        .child_index = zip->child_index + 1,
        .structural_child_index = structural_child_index
    };
    return true;
}

bool _ts_zipper_right(const _TSZipper *zip, _TSZipper *result) {
    while (__ts_zipper_right(zip, result)) {
        if (__is_visible(result)) {
            return true;
        }
        zip = result;
    }
    return false;
}

bool _ts_zipper_down(const _TSZipper *zip, _TSZipper *result, TSLanguage *lang) {
    if (ts_subtree_child_count(zip->subtree) == 0) {
        return false;
    } else {
        Subtree child = zip->subtree.ptr->children[0];
        const TSSymbol *alias_sequence = ts_language_alias_sequence(lang, zip->subtree.ptr->production_id);
        *result = (_TSZipper) {
            .parent = zip,
            .parent_alias_sequence = alias_sequence,
            .subtree = child,
            .byte_offset = zip->byte_offset,
            .child_index = 0,
            .structural_child_index = 0
        };
        if (__is_visible(result)) {
            return true;
        } else {
            uint32_t visible_child_count = ts_subtree_visible_child_count(child);
            if (visible_child_count > 0) {
                _TSZipper *z = (_TSZipper *)malloc(sizeof(_TSZipper));
                *z = *result;
                return _ts_zipper_down(z, result, lang);
            } else {
                return _ts_zipper_right(result, result);
            }
        }
    }
}

void _ts_zipper_new(Subtree tree, _TSZipper *result) {
    *result = (_TSZipper) {
        .parent = NULL,
        .parent_alias_sequence = NULL,
        .subtree = tree,
        .byte_offset = 0,
        .child_index = 0,
        .structural_child_index = 0
    };
}

void ts_zipper_new(TSTree *tree, TSZipper *result) {
    return _ts_zipper_new(tree->root, (_TSZipper *)result);
}

bool ts_zipper_right(const TSZipper *zip, TSZipper *result) {
    return _ts_zipper_right((_TSZipper *)zip, (_TSZipper *)result);
}

bool ts_zipper_down(const TSZipper *zip, TSZipper *result, TSLanguage *lang) {
    return _ts_zipper_down((_TSZipper *)zip, (_TSZipper *)result, lang);
}



TSSymbol ts_zipper_node_type(const TSZipper *zip) {
    _TSZipper *z = (_TSZipper *)zip;
    return ts_subtree_symbol(z->subtree);
}

uint32_t ts_zipper_start_byte(const TSZipper *zip) {
    return zip->byte_offset;
}

uint32_t ts_zipper_end_byte(const TSZipper *zip) {
    _TSZipper *z = (_TSZipper *) zip;
    return z->byte_offset + ts_subtree_size(z->subtree).bytes;
}

TSZipper *ts_zipper_up(const TSZipper *zip) {
    return (TSZipper *)(((_TSZipper *)zip)->parent);
}


