use crate::*;

use std::{ffi, os, ptr::copy_nonoverlapping};

static mut PARENT_CACHE_CAPACITY: os::raw::c_uint = 32 as os::raw::c_int as os::raw::c_uint;

#[no_mangle]
pub(crate) unsafe extern "C" fn ts_tree_new(
    mut root: Subtree,
    mut language: *const TSLanguage,
    mut included_ranges: *const TSRange,
    mut included_range_count: os::raw::c_uint,
) -> *mut TSTree {
    let mut result: *mut TSTree = ts_malloc(::std::mem::size_of::<TSTree>()) as *mut TSTree;
    (*result).root = root;
    (*result).language = language;
    (*result).parent_cache = std::ptr::null_mut::<ParentCacheEntry>();
    (*result).parent_cache_start = 0 as os::raw::c_int as u32;
    (*result).parent_cache_size = 0 as os::raw::c_int as u32;
    (*result).included_ranges = ts_calloc(
        included_range_count as usize,
        ::std::mem::size_of::<TSRange>(),
    ) as *mut TSRange;
    copy_nonoverlapping(
        included_ranges,
        (*result).included_ranges,
        included_range_count as usize,
    );
    (*result).included_range_count = included_range_count;
    result
}

/// Create a shallow copy of the syntax tree. This is very fast.
///
/// You need to copy a syntax tree in order to use it on more than one thread at
/// a time, as syntax trees are not thread safe.
#[no_mangle]
pub unsafe extern "C" fn ts_tree_copy(mut self_0: *const TSTree) -> *mut TSTree {
    ts_subtree_retain((*self_0).root);
    ts_tree_new(
        (*self_0).root,
        (*self_0).language,
        (*self_0).included_ranges,
        (*self_0).included_range_count,
    )
}

/// Delete the syntax tree, freeing all of the memory that it used.
#[no_mangle]
pub unsafe extern "C" fn ts_tree_delete(mut self_0: *mut TSTree) {
    if self_0.is_null() {
        return;
    }
    let mut pool: SubtreePool = ts_subtree_pool_new(0 as os::raw::c_int as u32);
    ts_subtree_release(&mut pool, (*self_0).root);
    ts_subtree_pool_delete(&mut pool);
    ts_free((*self_0).included_ranges as *mut ffi::c_void);
    if !(*self_0).parent_cache.is_null() {
        ts_free((*self_0).parent_cache as *mut ffi::c_void);
    }
    ts_free(self_0 as *mut ffi::c_void);
}

/// Get the root node of the syntax tree.
#[no_mangle]
pub unsafe extern "C" fn ts_tree_root_node(mut self_0: *const TSTree) -> TSNode {
    ts_node_new(
        self_0,
        &(*self_0).root,
        ts_subtree_padding((*self_0).root),
        0 as os::raw::c_int as TSSymbol,
    )
}

/// Get the language that was used to parse the syntax tree.
#[no_mangle]
pub unsafe extern "C" fn ts_tree_language(mut self_0: *const TSTree) -> *const TSLanguage {
    (*self_0).language
}

/// Edit the syntax tree to keep it in sync with source code that has been
/// edited.
///
/// You must describe the edit both in terms of byte offsets and in terms of
/// (row, column) coordinates.
#[no_mangle]
pub unsafe extern "C" fn ts_tree_edit(mut self_0: *mut TSTree, mut edit: *const TSInputEdit) {
    let mut i: os::raw::c_uint = 0 as os::raw::c_int as os::raw::c_uint;
    while i < (*self_0).included_range_count {
        let mut range: *mut TSRange =
            &mut *(*self_0).included_ranges.offset(i as isize) as *mut TSRange;
        if (*range).end_byte >= (*edit).old_end_byte {
            if (*range).end_byte != 4_294_967_295 as os::raw::c_uint {
                (*range).end_byte = (*edit)
                    .new_end_byte
                    .wrapping_add((*range).end_byte.wrapping_sub((*edit).old_end_byte));
                (*range).end_point = point_add(
                    (*edit).new_end_point,
                    point_sub((*range).end_point, (*edit).old_end_point),
                );
                if (*range).end_byte < (*edit).new_end_byte {
                    (*range).end_byte = 4_294_967_295 as os::raw::c_uint;
                    (*range).end_point = TSPoint {
                        row: 4_294_967_295 as os::raw::c_uint,
                        column: 4_294_967_295 as os::raw::c_uint,
                    }
                }
            }
            if (*range).start_byte >= (*edit).old_end_byte {
                (*range).start_byte = (*edit)
                    .new_end_byte
                    .wrapping_add((*range).start_byte.wrapping_sub((*edit).old_end_byte));
                (*range).start_point = point_add(
                    (*edit).new_end_point,
                    point_sub((*range).start_point, (*edit).old_end_point),
                );
                if (*range).start_byte < (*edit).new_end_byte {
                    (*range).start_byte = 4_294_967_295 as os::raw::c_uint;
                    (*range).start_point = TSPoint {
                        row: 4_294_967_295 as os::raw::c_uint,
                        column: 4_294_967_295 as os::raw::c_uint,
                    }
                }
            }
        }
        i = i.wrapping_add(1)
    }
    let mut pool: SubtreePool = ts_subtree_pool_new(0 as os::raw::c_int as u32);
    (*self_0).root = ts_subtree_edit((*self_0).root, edit, &mut pool);
    (*self_0).parent_cache_start = 0 as os::raw::c_int as u32;
    (*self_0).parent_cache_size = 0 as os::raw::c_int as u32;
    ts_subtree_pool_delete(&mut pool);
}

/// Compare an old edited syntax tree to a new syntax tree representing the same
/// document, returning an array of ranges whose syntactic structure has changed.
///
/// For this to work correctly, the old syntax tree must have been edited such
/// that its ranges match up to the new tree. Generally, you'll want to call
/// this function right after calling one of the `ts_parser_parse` functions.
/// You need to pass the old tree that was passed to parse, as well as the new
/// tree that was returned from that function.
///
/// The returned array is allocated using `malloc` and the caller is responsible
/// for freeing it using `free`. The length of the array will be written to the
/// given `length` pointer.
#[no_mangle]
pub unsafe extern "C" fn ts_tree_get_changed_ranges(
    mut self_0: *const TSTree,
    mut other: *const TSTree,
    mut count: *mut u32,
) -> *mut TSRange {
    let mut cursor1 = TreeCursor {
        tree: std::ptr::null::<TSTree>(),
        stack: TreeCursorEntryArray {
            contents: std::ptr::null_mut::<TreeCursorEntry>(),
            size: 0 as os::raw::c_int as u32,
            capacity: 0 as os::raw::c_int as u32,
        },
    };
    let mut cursor2 = TreeCursor {
        tree: std::ptr::null::<TSTree>(),
        stack: TreeCursorEntryArray {
            contents: std::ptr::null_mut::<TreeCursorEntry>(),
            size: 0 as os::raw::c_int as u32,
            capacity: 0 as os::raw::c_int as u32,
        },
    };
    ts_tree_cursor_init(&mut cursor1, ts_tree_root_node(self_0));
    ts_tree_cursor_init(&mut cursor2, ts_tree_root_node(other));
    let mut included_range_differences = TSRangeArray {
        contents: std::ptr::null_mut::<TSRange>(),
        size: 0 as os::raw::c_int as u32,
        capacity: 0 as os::raw::c_int as u32,
    };
    ts_range_array_get_changed_ranges(
        (*self_0).included_ranges,
        (*self_0).included_range_count,
        (*other).included_ranges,
        (*other).included_range_count,
        &mut included_range_differences,
    );
    let mut result: *mut TSRange = std::ptr::null_mut::<TSRange>();
    *count = ts_subtree_get_changed_ranges(
        &(*self_0).root,
        &(*other).root,
        &mut cursor1,
        &mut cursor2,
        (*self_0).language,
        &included_range_differences,
        &mut result,
    );
    array__delete(&mut included_range_differences as *mut TSRangeArray as *mut VoidArray);
    array__delete(&mut cursor1.stack as *mut TreeCursorEntryArray as *mut VoidArray);
    array__delete(&mut cursor2.stack as *mut TreeCursorEntryArray as *mut VoidArray);
    result
}

#[no_mangle]
pub(crate) unsafe extern "C" fn ts_tree_get_cached_parent(
    mut self_0: *const TSTree,
    mut node: *const TSNode,
) -> TSNode {
    let mut i: u32 = 0 as os::raw::c_int as u32;
    while i < (*self_0).parent_cache_size {
        let mut index: u32 = (*self_0)
            .parent_cache_start
            .wrapping_add(i)
            .wrapping_rem(PARENT_CACHE_CAPACITY);
        let mut entry: *mut ParentCacheEntry =
            &mut *(*self_0).parent_cache.offset(index as isize) as *mut ParentCacheEntry;
        if (*entry).child == (*node).id as *const Subtree {
            return ts_node_new(
                self_0,
                (*entry).parent,
                (*entry).position,
                (*entry).alias_symbol,
            );
        }
        i = i.wrapping_add(1)
    }
    ts_node_new(
        std::ptr::null::<TSTree>(),
        std::ptr::null::<Subtree>(),
        length_zero(),
        0 as os::raw::c_int as TSSymbol,
    )
}
#[no_mangle]
pub(crate) unsafe extern "C" fn ts_tree_set_cached_parent(
    mut _self: *const TSTree,
    mut node: *const TSNode,
    mut parent: *const TSNode,
) {
    let mut self_0: *mut TSTree = _self as *mut TSTree;
    if (*self_0).parent_cache.is_null() {
        (*self_0).parent_cache = ts_calloc(
            PARENT_CACHE_CAPACITY as usize,
            ::std::mem::size_of::<ParentCacheEntry>(),
        ) as *mut ParentCacheEntry
    }
    let mut index: u32 = (*self_0)
        .parent_cache_start
        .wrapping_add((*self_0).parent_cache_size)
        .wrapping_rem(PARENT_CACHE_CAPACITY);
    *(*self_0).parent_cache.offset(index as isize) = ParentCacheEntry {
        child: (*node).id as *const Subtree,
        parent: (*parent).id as *const Subtree,
        position: Length {
            bytes: (*parent).context[0 as os::raw::c_int as usize],
            extent: TSPoint {
                row: (*parent).context[1 as os::raw::c_int as usize],
                column: (*parent).context[2 as os::raw::c_int as usize],
            },
        },
        alias_symbol: (*parent).context[3 as os::raw::c_int as usize] as TSSymbol,
    };
    if (*self_0).parent_cache_size == PARENT_CACHE_CAPACITY {
        (*self_0).parent_cache_start = (*self_0).parent_cache_start.wrapping_add(1)
    } else {
        (*self_0).parent_cache_size = (*self_0).parent_cache_size.wrapping_add(1)
    };
}
