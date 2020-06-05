use crate::*;

use std::{ffi, os, ptr};

#[derive(Copy, Clone)]
#[repr(C)]
pub struct TreeCursorEntryArray {
    pub contents: *mut TreeCursorEntry,
    pub size: u32,
    pub capacity: u32,
}

#[derive(Copy, Clone)]
#[repr(C)]
pub struct TreeCursor {
    pub tree: *const TSTree,
    pub stack: TreeCursorEntryArray,
}

#[derive(Copy, Clone)]
#[repr(C)]
pub struct CursorChildIterator {
    pub parent: Subtree,
    pub tree: *const TSTree,
    pub position: Length,
    pub child_index: u32,
    pub structural_child_index: u32,
    pub alias_sequence: *const TSSymbol,
}

// CursorChildIterator
#[inline]
unsafe extern "C" fn ts_tree_cursor_iterate_children(
    mut self_0: *const TreeCursor,
) -> CursorChildIterator {
    assert!(
        (*self_0)
            .stack
            .size
            .wrapping_sub(1 as os::raw::c_int as os::raw::c_uint)
            < (*self_0).stack.size
    );
    let mut last_entry: *mut TreeCursorEntry = &mut *(*self_0)
        .stack
        .contents
        .offset((*self_0).stack.size.wrapping_sub(1) as isize)
        as *mut TreeCursorEntry;
    if ts_subtree_child_count(*(*last_entry).subtree) == 0 as os::raw::c_int as os::raw::c_uint {
        return CursorChildIterator {
            parent: Subtree {
                ptr: std::ptr::null::<SubtreeHeapData>(),
            },
            tree: (*self_0).tree,
            position: length_zero(),
            child_index: 0 as os::raw::c_int as u32,
            structural_child_index: 0 as os::raw::c_int as u32,
            alias_sequence: std::ptr::null::<TSSymbol>(),
        };
    }
    let mut alias_sequence: *const TSSymbol = ts_language_alias_sequence(
        (*(*self_0).tree).language,
        (*(*(*last_entry).subtree).ptr)
            .c2rust_unnamed
            .c2rust_unnamed
            .production_id as u32,
    );
    CursorChildIterator {
        parent: *(*last_entry).subtree,
        tree: (*self_0).tree,
        position: (*last_entry).position,
        child_index: 0 as os::raw::c_int as u32,
        structural_child_index: 0 as os::raw::c_int as u32,
        alias_sequence,
    }
}
#[inline]
unsafe extern "C" fn ts_tree_cursor_child_iterator_next(
    mut self_0: *mut CursorChildIterator,
    mut result: *mut TreeCursorEntry,
    mut visible: *mut bool,
) -> bool {
    if (*self_0).parent.ptr.is_null()
        || (*self_0).child_index == (*(*self_0).parent.ptr).child_count
    {
        return false;
    }
    let mut child: *const Subtree = &mut *(*(*self_0).parent.ptr)
        .c2rust_unnamed
        .c2rust_unnamed
        .children
        .offset((*self_0).child_index as isize) as *mut Subtree;
    *result = TreeCursorEntry {
        subtree: child,
        position: (*self_0).position,
        child_index: (*self_0).child_index,
        structural_child_index: (*self_0).structural_child_index,
    };
    *visible = ts_subtree_visible(*child);
    let mut extra: bool = ts_subtree_extra(*child);
    if !extra && !(*self_0).alias_sequence.is_null() {
        *visible = (*visible as os::raw::c_int
            | *(*self_0)
                .alias_sequence
                .offset((*self_0).structural_child_index as isize) as os::raw::c_int)
            != 0;
        (*self_0).structural_child_index = (*self_0).structural_child_index.wrapping_add(1)
    }
    (*self_0).position = length_add((*self_0).position, ts_subtree_size(*child));
    (*self_0).child_index = (*self_0).child_index.wrapping_add(1);
    if (*self_0).child_index < (*(*self_0).parent.ptr).child_count {
        let mut next_child: Subtree = *(*(*self_0).parent.ptr)
            .c2rust_unnamed
            .c2rust_unnamed
            .children
            .offset((*self_0).child_index as isize);
        (*self_0).position = length_add((*self_0).position, ts_subtree_padding(next_child))
    }
    true
}

/// Create a new tree cursor starting from the given node.
///
/// A tree cursor allows you to walk a syntax tree more efficiently than is
/// possible using the `TSNode` functions. It is a mutable object that is always
/// on a certain syntax node, and can be moved imperatively to different nodes.
#[no_mangle]
pub unsafe extern "C" fn ts_tree_cursor_new(mut node: TSNode) -> TSTreeCursor {
    let mut self_0 = TSTreeCursor {
        tree: ptr::null(),
        id: ptr::null(),
        context: [0 as os::raw::c_int as u32, 0 as os::raw::c_int as u32],
    };
    ts_tree_cursor_init(&mut self_0 as *mut TSTreeCursor as *mut TreeCursor, node);
    self_0
}

/// Re-initialize a tree cursor to start at a different node.
#[no_mangle]
pub unsafe extern "C" fn ts_tree_cursor_reset(mut _self: *mut TSTreeCursor, mut node: TSNode) {
    ts_tree_cursor_init(_self as *mut TreeCursor, node);
}
#[no_mangle]
pub(crate) unsafe extern "C" fn ts_tree_cursor_init(mut self_0: *mut TreeCursor, mut node: TSNode) {
    (*self_0).tree = node.tree;
    (*self_0).stack.size = 0 as os::raw::c_int as u32;
    array__grow(
        &mut (*self_0).stack as *mut TreeCursorEntryArray as *mut VoidArray,
        1 as os::raw::c_int as usize,
        ::std::mem::size_of::<TreeCursorEntry>(),
    );
    let fresh0 = (*self_0).stack.size;
    (*self_0).stack.size = (*self_0).stack.size.wrapping_add(1);
    *(*self_0).stack.contents.offset(fresh0 as isize) = TreeCursorEntry {
        subtree: node.id as *const Subtree,
        position: Length {
            bytes: ts_node_start_byte(node),
            extent: ts_node_start_point(node),
        },
        child_index: 0 as os::raw::c_int as u32,
        structural_child_index: 0 as os::raw::c_int as u32,
    };
}

/// Delete a tree cursor, freeing all of the memory that it used.
#[no_mangle]
pub unsafe extern "C" fn ts_tree_cursor_delete(mut _self: *mut TSTreeCursor) {
    let mut self_0: *mut TreeCursor = _self as *mut TreeCursor;
    array__delete(&mut (*self_0).stack as *mut TreeCursorEntryArray as *mut VoidArray);
}

/// Move the cursor to the first child of its current node.
///
/// This returns `true` if the cursor successfully moved, and returns `false`
/// if there were no children.
#[no_mangle]
pub unsafe extern "C" fn ts_tree_cursor_goto_first_child(mut _self: *mut TSTreeCursor) -> bool {
    let mut self_0: *mut TreeCursor = _self as *mut TreeCursor;
    let mut did_descend: bool = false;
    loop {
        did_descend = false;
        let mut visible: bool = false;
        let mut entry: TreeCursorEntry = TreeCursorEntry {
            subtree: std::ptr::null::<Subtree>(),
            position: Length {
                bytes: 0,
                extent: TSPoint { row: 0, column: 0 },
            },
            child_index: 0,
            structural_child_index: 0,
        };
        let mut iterator: CursorChildIterator = ts_tree_cursor_iterate_children(self_0);
        while ts_tree_cursor_child_iterator_next(&mut iterator, &mut entry, &mut visible) {
            if visible {
                array__grow(
                    &mut (*self_0).stack as *mut TreeCursorEntryArray as *mut VoidArray,
                    1 as os::raw::c_int as usize,
                    ::std::mem::size_of::<TreeCursorEntry>(),
                );
                let fresh1 = (*self_0).stack.size;
                (*self_0).stack.size = (*self_0).stack.size.wrapping_add(1);
                *(*self_0).stack.contents.offset(fresh1 as isize) = entry;
                return true;
            }
            if ts_subtree_visible_child_count(*entry.subtree)
                <= 0 as os::raw::c_int as os::raw::c_uint
            {
                continue;
            }
            array__grow(
                &mut (*self_0).stack as *mut TreeCursorEntryArray as *mut VoidArray,
                1 as os::raw::c_int as usize,
                ::std::mem::size_of::<TreeCursorEntry>(),
            );
            let fresh2 = (*self_0).stack.size;
            (*self_0).stack.size = (*self_0).stack.size.wrapping_add(1);
            *(*self_0).stack.contents.offset(fresh2 as isize) = entry;
            did_descend = true;
            break;
        }
        if !did_descend {
            break;
        }
    }
    false
}

/// Move the cursor to the first child of its current node that extends beyond
/// the given byte offset.
///
/// This returns the index of the child node if one was found, and returns -1
/// if no such child was found.
#[no_mangle]
pub unsafe extern "C" fn ts_tree_cursor_goto_first_child_for_byte(
    mut _self: *mut TSTreeCursor,
    mut goal_byte: u32,
) -> i64 {
    let mut self_0: *mut TreeCursor = _self as *mut TreeCursor;
    let mut initial_size: u32 = (*self_0).stack.size;
    let mut visible_child_index: u32 = 0 as os::raw::c_int as u32;
    let mut did_descend: bool = false;
    loop {
        did_descend = false;
        let mut visible: bool = false;
        let mut entry: TreeCursorEntry = TreeCursorEntry {
            subtree: std::ptr::null::<Subtree>(),
            position: Length {
                bytes: 0,
                extent: TSPoint { row: 0, column: 0 },
            },
            child_index: 0,
            structural_child_index: 0,
        };
        let mut iterator: CursorChildIterator = ts_tree_cursor_iterate_children(self_0);
        while ts_tree_cursor_child_iterator_next(&mut iterator, &mut entry, &mut visible) {
            let mut end_byte: u32 = entry
                .position
                .bytes
                .wrapping_add(ts_subtree_size(*entry.subtree).bytes);
            let mut at_goal: bool = end_byte > goal_byte;
            let mut visible_child_count: u32 = ts_subtree_visible_child_count(*entry.subtree);
            if at_goal {
                if visible {
                    array__grow(
                        &mut (*self_0).stack as *mut TreeCursorEntryArray as *mut VoidArray,
                        1 as os::raw::c_int as usize,
                        ::std::mem::size_of::<TreeCursorEntry>(),
                    );
                    let fresh3 = (*self_0).stack.size;
                    (*self_0).stack.size = (*self_0).stack.size.wrapping_add(1);
                    *(*self_0).stack.contents.offset(fresh3 as isize) = entry;
                    return visible_child_index as i64;
                }
                if visible_child_count <= 0 as os::raw::c_int as os::raw::c_uint {
                    continue;
                }
                array__grow(
                    &mut (*self_0).stack as *mut TreeCursorEntryArray as *mut VoidArray,
                    1 as os::raw::c_int as usize,
                    ::std::mem::size_of::<TreeCursorEntry>(),
                );
                let fresh4 = (*self_0).stack.size;
                (*self_0).stack.size = (*self_0).stack.size.wrapping_add(1);
                *(*self_0).stack.contents.offset(fresh4 as isize) = entry;
                did_descend = true;
                break;
            } else if visible {
                visible_child_index = visible_child_index.wrapping_add(1)
            } else {
                visible_child_index = (visible_child_index as os::raw::c_uint)
                    .wrapping_add(visible_child_count) as u32
                    as u32
            }
        }
        if !did_descend {
            break;
        }
    }
    if (*self_0).stack.size > initial_size
        && ts_tree_cursor_goto_next_sibling(self_0 as *mut TSTreeCursor) as os::raw::c_int != 0
    {
        return visible_child_index as i64;
    }
    (*self_0).stack.size = initial_size;
    -(1 as os::raw::c_int) as i64
}

/// Move the cursor to the next sibling of its current node.
///
/// This returns `true` if the cursor successfully moved, and returns `false`
/// if there was no next sibling node.
#[no_mangle]
pub unsafe extern "C" fn ts_tree_cursor_goto_next_sibling(mut _self: *mut TSTreeCursor) -> bool {
    let mut self_0: *mut TreeCursor = _self as *mut TreeCursor;
    let mut initial_size: u32 = (*self_0).stack.size;
    while (*self_0).stack.size > 1 as os::raw::c_int as os::raw::c_uint {
        (*self_0).stack.size = (*self_0).stack.size.wrapping_sub(1);
        let mut entry: TreeCursorEntry = *(*self_0)
            .stack
            .contents
            .offset((*self_0).stack.size as isize);
        let mut iterator: CursorChildIterator = ts_tree_cursor_iterate_children(self_0);
        iterator.child_index = entry.child_index;
        iterator.structural_child_index = entry.structural_child_index;
        iterator.position = entry.position;
        let mut visible: bool = false;
        ts_tree_cursor_child_iterator_next(&mut iterator, &mut entry, &mut visible);
        if visible as os::raw::c_int != 0 && (*self_0).stack.size.wrapping_add(1) < initial_size {
            break;
        }
        while ts_tree_cursor_child_iterator_next(&mut iterator, &mut entry, &mut visible) {
            if visible {
                array__grow(
                    &mut (*self_0).stack as *mut TreeCursorEntryArray as *mut VoidArray,
                    1 as os::raw::c_int as usize,
                    ::std::mem::size_of::<TreeCursorEntry>(),
                );
                let fresh5 = (*self_0).stack.size;
                (*self_0).stack.size = (*self_0).stack.size.wrapping_add(1);
                *(*self_0).stack.contents.offset(fresh5 as isize) = entry;
                return true;
            }
            if ts_subtree_visible_child_count(*entry.subtree) != 0 {
                array__grow(
                    &mut (*self_0).stack as *mut TreeCursorEntryArray as *mut VoidArray,
                    1 as os::raw::c_int as usize,
                    ::std::mem::size_of::<TreeCursorEntry>(),
                );
                let fresh6 = (*self_0).stack.size;
                (*self_0).stack.size = (*self_0).stack.size.wrapping_add(1);
                *(*self_0).stack.contents.offset(fresh6 as isize) = entry;
                ts_tree_cursor_goto_first_child(_self);
                return true;
            }
        }
    }
    (*self_0).stack.size = initial_size;
    false
}

/// Move the cursor to the parent of its current node.
///
/// This returns `true` if the cursor successfully moved, and returns `false`
/// if there was no parent node (the cursor was already on the root node).
#[no_mangle]
pub unsafe extern "C" fn ts_tree_cursor_goto_parent(mut _self: *mut TSTreeCursor) -> bool {
    let mut self_0: *mut TreeCursor = _self as *mut TreeCursor;
    let mut i: os::raw::c_uint = (*self_0).stack.size.wrapping_sub(2);
    while i.wrapping_add(1) > 0 as os::raw::c_int as os::raw::c_uint {
        let mut entry: *mut TreeCursorEntry =
            &mut *(*self_0).stack.contents.offset(i as isize) as *mut TreeCursorEntry;
        let mut is_aliased: bool = false;
        if i > 0 as os::raw::c_int as os::raw::c_uint {
            let mut parent_entry: *mut TreeCursorEntry =
                &mut *(*self_0).stack.contents.offset(i.wrapping_sub(1) as isize)
                    as *mut TreeCursorEntry;
            let mut alias_sequence: *const TSSymbol = ts_language_alias_sequence(
                (*(*self_0).tree).language,
                (*(*(*parent_entry).subtree).ptr)
                    .c2rust_unnamed
                    .c2rust_unnamed
                    .production_id as u32,
            );
            is_aliased = !alias_sequence.is_null()
                && *alias_sequence.offset((*entry).structural_child_index as isize)
                    as os::raw::c_int
                    != 0
        }
        if ts_subtree_visible(*(*entry).subtree) as os::raw::c_int != 0
            || is_aliased as os::raw::c_int != 0
        {
            (*self_0).stack.size = i.wrapping_add(1);
            return true;
        }
        i = i.wrapping_sub(1)
    }
    false
}

/// Get the tree cursor's current node.
#[no_mangle]
pub unsafe extern "C" fn ts_tree_cursor_current_node(mut _self: *const TSTreeCursor) -> TSNode {
    let mut self_0: *const TreeCursor = _self as *const TreeCursor;
    assert!(
        (*self_0)
            .stack
            .size
            .wrapping_sub(1 as os::raw::c_int as os::raw::c_uint)
            < (*self_0).stack.size
    );
    let mut last_entry: *mut TreeCursorEntry = &mut *(*self_0)
        .stack
        .contents
        .offset((*self_0).stack.size.wrapping_sub(1) as isize)
        as *mut TreeCursorEntry;
    let mut alias_symbol: TSSymbol = 0 as os::raw::c_int as TSSymbol;
    if (*self_0).stack.size > 1 as os::raw::c_int as os::raw::c_uint {
        let mut parent_entry: *mut TreeCursorEntry = &mut *(*self_0)
            .stack
            .contents
            .offset((*self_0).stack.size.wrapping_sub(2) as isize)
            as *mut TreeCursorEntry;
        let mut alias_sequence: *const TSSymbol = ts_language_alias_sequence(
            (*(*self_0).tree).language,
            (*(*(*parent_entry).subtree).ptr)
                .c2rust_unnamed
                .c2rust_unnamed
                .production_id as u32,
        );
        if !alias_sequence.is_null() && !ts_subtree_extra(*(*last_entry).subtree) {
            alias_symbol = *alias_sequence.offset((*last_entry).structural_child_index as isize)
        }
    }
    ts_node_new(
        (*self_0).tree,
        (*last_entry).subtree,
        (*last_entry).position,
        alias_symbol,
    )
}
#[no_mangle]
pub(crate) unsafe extern "C" fn ts_tree_cursor_current_status(
    mut _self: *const TSTreeCursor,
    mut can_have_later_siblings: *mut bool,
    mut can_have_later_siblings_with_this_field: *mut bool,
) -> TSFieldId {
    let mut self_0: *const TreeCursor = _self as *const TreeCursor;
    let mut result: TSFieldId = 0 as os::raw::c_int as TSFieldId;
    *can_have_later_siblings = false;
    *can_have_later_siblings_with_this_field = false;
    // Walk up the tree, visiting the current node and its invisible ancestors,
    // because fields can refer to nodes through invisible *wrapper* nodes,
    let mut i: os::raw::c_uint = (*self_0).stack.size.wrapping_sub(1);
    while i > 0 as os::raw::c_int as os::raw::c_uint {
        let mut entry: *mut TreeCursorEntry =
            &mut *(*self_0).stack.contents.offset(i as isize) as *mut TreeCursorEntry;
        let mut parent_entry: *mut TreeCursorEntry =
            &mut *(*self_0).stack.contents.offset(i.wrapping_sub(1) as isize)
                as *mut TreeCursorEntry;
        // Stop walking up when a visible ancestor is found.
        if i != (*self_0).stack.size.wrapping_sub(1) {
            if ts_subtree_visible(*(*entry).subtree) {
                break;
            }
            let mut alias_sequence: *const TSSymbol = ts_language_alias_sequence(
                (*(*self_0).tree).language,
                (*(*(*parent_entry).subtree).ptr)
                    .c2rust_unnamed
                    .c2rust_unnamed
                    .production_id as u32,
            );
            if !alias_sequence.is_null()
                && *alias_sequence.offset((*entry).structural_child_index as isize)
                    as os::raw::c_int
                    != 0
            {
                break;
            }
        }
        if ts_subtree_child_count(*(*parent_entry).subtree) > (*entry).child_index.wrapping_add(1) {
            *can_have_later_siblings = true
        }
        if ts_subtree_extra(*(*entry).subtree) {
            break;
        }
        let mut field_map: *const TSFieldMapEntry = std::ptr::null::<TSFieldMapEntry>();
        let mut field_map_end: *const TSFieldMapEntry = std::ptr::null::<TSFieldMapEntry>();
        ts_language_field_map(
            (*(*self_0).tree).language,
            (*(*(*parent_entry).subtree).ptr)
                .c2rust_unnamed
                .c2rust_unnamed
                .production_id as u32,
            &mut field_map,
            &mut field_map_end,
        );
        // Look for a field name associated with the current node.
        if result == 0 {
            let mut i_0: *const TSFieldMapEntry = field_map;
            while i_0 < field_map_end {
                if !(*i_0).inherited
                    && (*i_0).child_index as os::raw::c_uint == (*entry).structural_child_index
                {
                    result = (*i_0).field_id;
                    *can_have_later_siblings_with_this_field = false;
                    break;
                } else {
                    i_0 = i_0.offset(1)
                }
            }
        }
        // Determine if there other later siblings with the same field name.
        if result != 0 {
            let mut i_1: *const TSFieldMapEntry = field_map;
            while i_1 < field_map_end {
                if (*i_1).field_id as os::raw::c_int == result as os::raw::c_int
                    && (*i_1).child_index as os::raw::c_uint > (*entry).structural_child_index
                {
                    *can_have_later_siblings_with_this_field = true;
                    break;
                } else {
                    i_1 = i_1.offset(1)
                }
            }
        }
        i = i.wrapping_sub(1)
    }
    result
}

/// Get the field name of the tree cursor's current node.
///
/// This returns zero if the current node doesn't have a field.
/// See also `ts_node_child_by_field_id`, `ts_language_field_id_for_name`.
#[no_mangle]
pub unsafe extern "C" fn ts_tree_cursor_current_field_id(
    mut _self: *const TSTreeCursor,
) -> TSFieldId {
    let mut self_0: *const TreeCursor = _self as *const TreeCursor;
    // Walk up the tree, visiting the current node and its invisible ancestors.
    let mut i: os::raw::c_uint = (*self_0).stack.size.wrapping_sub(1);
    while i > 0 as os::raw::c_int as os::raw::c_uint {
        let mut entry: *mut TreeCursorEntry =
            &mut *(*self_0).stack.contents.offset(i as isize) as *mut TreeCursorEntry;
        let mut parent_entry: *mut TreeCursorEntry =
            &mut *(*self_0).stack.contents.offset(i.wrapping_sub(1) as isize)
                as *mut TreeCursorEntry;
        // Stop walking up when another visible node is found.
        if i != (*self_0).stack.size.wrapping_sub(1) {
            if ts_subtree_visible(*(*entry).subtree) {
                break;
            }
            let mut alias_sequence: *const TSSymbol = ts_language_alias_sequence(
                (*(*self_0).tree).language,
                (*(*(*parent_entry).subtree).ptr)
                    .c2rust_unnamed
                    .c2rust_unnamed
                    .production_id as u32,
            );
            if !alias_sequence.is_null()
                && *alias_sequence.offset((*entry).structural_child_index as isize)
                    as os::raw::c_int
                    != 0
            {
                break;
            }
        }
        if ts_subtree_extra(*(*entry).subtree) {
            break;
        }
        let mut field_map: *const TSFieldMapEntry = std::ptr::null::<TSFieldMapEntry>();
        let mut field_map_end: *const TSFieldMapEntry = std::ptr::null::<TSFieldMapEntry>();
        ts_language_field_map(
            (*(*self_0).tree).language,
            (*(*(*parent_entry).subtree).ptr)
                .c2rust_unnamed
                .c2rust_unnamed
                .production_id as u32,
            &mut field_map,
            &mut field_map_end,
        );
        let mut i_0: *const TSFieldMapEntry = field_map;
        while i_0 < field_map_end {
            if !(*i_0).inherited
                && (*i_0).child_index as os::raw::c_uint == (*entry).structural_child_index
            {
                return (*i_0).field_id;
            }
            i_0 = i_0.offset(1)
        }
        i = i.wrapping_sub(1)
    }
    0 as os::raw::c_int as TSFieldId
}

/// Get the field name of the tree cursor's current node.
///
/// This returns `NULL` if the current node doesn't have a field.
/// See also `ts_node_child_by_field_name`.
#[no_mangle]
pub unsafe extern "C" fn ts_tree_cursor_current_field_name(
    mut _self: *const TSTreeCursor,
) -> *const os::raw::c_char {
    let mut id: TSFieldId = ts_tree_cursor_current_field_id(_self);
    if id != 0 {
        let mut self_0: *const TreeCursor = _self as *const TreeCursor;
        *(*(*(*self_0).tree).language)
            .field_names
            .offset(id as isize)
    } else {
        ptr::null()
    }
}

#[no_mangle]
pub(crate) unsafe extern "C" fn ts_tree_cursor_copy(
    mut _cursor: *const TSTreeCursor,
) -> TSTreeCursor {
    let mut cursor: *const TreeCursor = _cursor as *const TreeCursor;
    let mut res = TSTreeCursor {
        tree: ptr::null(),
        id: ptr::null(),
        context: [0 as os::raw::c_int as u32, 0 as os::raw::c_int as u32],
    };
    let mut copy: *mut TreeCursor = &mut res as *mut TSTreeCursor as *mut TreeCursor;
    (*copy).tree = (*cursor).tree;
    array__splice(
        &mut (*copy).stack as *mut TreeCursorEntryArray as *mut VoidArray,
        ::std::mem::size_of::<TreeCursorEntry>(),
        (*copy).stack.size,
        0 as os::raw::c_int as u32,
        (*cursor).stack.size,
        (*cursor).stack.contents as *const ffi::c_void,
    );
    res
}
