use crate::*;

use std::os;

#[derive(Copy, Clone)]
#[repr(C)]
pub struct ReusableNode {
    pub stack: StackEntryArray,
    pub last_external_token: Subtree,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct StackEntryArray {
    pub contents: *mut StackEntry,
    pub size: u32,
    pub capacity: u32,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct StackEntry {
    pub tree: Subtree,
    pub child_index: u32,
    pub byte_offset: u32,
}

#[inline]
pub(crate) unsafe extern "C" fn reusable_node_new() -> ReusableNode {
    ReusableNode {
        stack: StackEntryArray {
            contents: std::ptr::null_mut::<StackEntry>(),
            size: 0 as os::raw::c_int as u32,
            capacity: 0 as os::raw::c_int as u32,
        },
        last_external_token: Subtree {
            ptr: std::ptr::null::<SubtreeHeapData>(),
        },
    }
}
#[inline]
pub(crate) unsafe extern "C" fn reusable_node_clear(mut self_0: *mut ReusableNode) {
    (*self_0).stack.size = 0 as os::raw::c_int as u32;
    (*self_0).last_external_token = Subtree {
        ptr: std::ptr::null::<SubtreeHeapData>(),
    };
}
#[inline]
pub(crate) unsafe extern "C" fn reusable_node_reset(
    mut self_0: *mut ReusableNode,
    mut tree: Subtree,
) {
    reusable_node_clear(self_0);
    array__grow(
        &mut (*self_0).stack as *mut StackEntryArray as *mut VoidArray,
        1 as os::raw::c_int as usize,
        ::std::mem::size_of::<StackEntry>(),
    );
    let fresh5 = (*self_0).stack.size;
    (*self_0).stack.size = (*self_0).stack.size.wrapping_add(1);
    *(*self_0).stack.contents.offset(fresh5 as isize) = StackEntry {
        tree,
        child_index: 0 as os::raw::c_int as u32,
        byte_offset: 0 as os::raw::c_int as u32,
    };
}
#[inline]
pub(crate) unsafe extern "C" fn reusable_node_tree(mut self_0: *mut ReusableNode) -> Subtree {
    if (*self_0).stack.size > 0 as os::raw::c_int as os::raw::c_uint {
        (*(*self_0)
            .stack
            .contents
            .offset((*self_0).stack.size.wrapping_sub(1) as isize))
        .tree
    } else {
        Subtree {
            ptr: std::ptr::null::<SubtreeHeapData>(),
        }
    }
}
#[inline]
pub(crate) unsafe extern "C" fn reusable_node_byte_offset(mut self_0: *mut ReusableNode) -> u32 {
    if (*self_0).stack.size > 0 as os::raw::c_int as os::raw::c_uint {
        (*(*self_0)
            .stack
            .contents
            .offset((*self_0).stack.size.wrapping_sub(1) as isize))
        .byte_offset
    } else {
        4_294_967_295 as os::raw::c_uint
    }
}
#[inline]
pub(crate) unsafe extern "C" fn reusable_node_delete(mut self_0: *mut ReusableNode) {
    array__delete(&mut (*self_0).stack as *mut StackEntryArray as *mut VoidArray);
}
#[inline]
pub(crate) unsafe extern "C" fn reusable_node_advance(mut self_0: *mut ReusableNode) {
    assert!(
        (*self_0)
            .stack
            .size
            .wrapping_sub(1 as os::raw::c_int as os::raw::c_uint)
            < (*self_0).stack.size
    );
    let mut last_entry: StackEntry = *(&mut *(*self_0)
        .stack
        .contents
        .offset((*self_0).stack.size.wrapping_sub(1) as isize)
        as *mut StackEntry);
    let mut byte_offset: u32 = last_entry
        .byte_offset
        .wrapping_add(ts_subtree_total_bytes(last_entry.tree));
    if ts_subtree_has_external_tokens(last_entry.tree) {
        (*self_0).last_external_token = ts_subtree_last_external_token(last_entry.tree)
    }
    let mut tree: Subtree = Subtree {
        data: SubtreeInlineData {
            is_inline_visible_named_extra_has_changes_is_missing_is_keyword: [0; 1],
            symbol: 0,
            padding_bytes: 0,
            size_bytes: 0,
            padding_columns: 0,
            padding_rows_lookahead_bytes: [0; 1],
            parse_state: 0,
        },
    };
    let mut next_index: u32 = 0;
    loop {
        (*self_0).stack.size = (*self_0).stack.size.wrapping_sub(1);
        let mut popped_entry: StackEntry = *(*self_0)
            .stack
            .contents
            .offset((*self_0).stack.size as isize);
        next_index = popped_entry.child_index.wrapping_add(1);
        if (*self_0).stack.size == 0 as os::raw::c_int as os::raw::c_uint {
            return;
        }
        assert!(
            (*self_0)
                .stack
                .size
                .wrapping_sub(1 as os::raw::c_int as os::raw::c_uint)
                < (*self_0).stack.size
        );
        tree = (*(&mut *(*self_0)
            .stack
            .contents
            .offset((*self_0).stack.size.wrapping_sub(1) as isize)
            as *mut StackEntry))
            .tree;
        if ts_subtree_child_count(tree) > next_index {
            break;
        }
    }
    array__grow(
        &mut (*self_0).stack as *mut StackEntryArray as *mut VoidArray,
        1 as os::raw::c_int as usize,
        ::std::mem::size_of::<StackEntry>(),
    );
    let fresh6 = (*self_0).stack.size;
    (*self_0).stack.size = (*self_0).stack.size.wrapping_add(1);
    *(*self_0).stack.contents.offset(fresh6 as isize) = StackEntry {
        tree: *(*tree.ptr)
            .c2rust_unnamed
            .c2rust_unnamed
            .children
            .offset(next_index as isize),
        child_index: next_index,
        byte_offset,
    };
}
#[inline]
pub(crate) unsafe extern "C" fn reusable_node_descend(mut self_0: *mut ReusableNode) -> bool {
    assert!(
        (*self_0)
            .stack
            .size
            .wrapping_sub(1 as os::raw::c_int as os::raw::c_uint)
            < (*self_0).stack.size
    );
    let mut last_entry: StackEntry = *(&mut *(*self_0)
        .stack
        .contents
        .offset((*self_0).stack.size.wrapping_sub(1) as isize)
        as *mut StackEntry);
    if ts_subtree_child_count(last_entry.tree) > 0 as os::raw::c_int as os::raw::c_uint {
        array__grow(
            &mut (*self_0).stack as *mut StackEntryArray as *mut VoidArray,
            1 as os::raw::c_int as usize,
            ::std::mem::size_of::<StackEntry>(),
        );
        let fresh7 = (*self_0).stack.size;
        (*self_0).stack.size = (*self_0).stack.size.wrapping_add(1);
        *(*self_0).stack.contents.offset(fresh7 as isize) = StackEntry {
            tree: *(*last_entry.tree.ptr)
                .c2rust_unnamed
                .c2rust_unnamed
                .children
                .offset(0 as os::raw::c_int as isize),
            child_index: 0 as os::raw::c_int as u32,
            byte_offset: last_entry.byte_offset,
        };
        true
    } else {
        false
    }
}
#[inline]
pub(crate) unsafe extern "C" fn reusable_node_advance_past_leaf(mut self_0: *mut ReusableNode) {
    while reusable_node_descend(self_0) {}
    reusable_node_advance(self_0);
}
