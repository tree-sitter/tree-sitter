use crate::{
    util::{snwrite, WrappingOffsetFromExt},
    *,
};

use std::{
    alloc::{self, Layout},
    convert::TryInto,
    ffi::{self, CStr},
    io::Write,
    mem::{align_of, size_of},
    os,
    ptr::{self, copy_nonoverlapping},
};

#[derive(Copy, Clone)]
#[repr(C)]
pub struct Edit {
    pub start: Length,
    pub old_end: Length,
    pub new_end: Length,
}

static mut empty_state: ExternalScannerState = ExternalScannerState {
    c2rust_unnamed: ExternalScannerStateData {
        short_data: [
            0 as os::raw::c_int as os::raw::c_char,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
        ],
    },
    length: 0 as os::raw::c_int as u32,
};

// ExternalScannerState
#[no_mangle]
pub(crate) unsafe extern "C" fn ts_external_scanner_state_init(
    mut self_0: *mut ExternalScannerState,
    mut data: *const os::raw::c_char,
    mut length: os::raw::c_uint,
) {
    (*self_0).length = length;
    if length as os::raw::c_ulong
        > ::std::mem::size_of::<[os::raw::c_char; 24]>() as os::raw::c_ulong
    {
        (*self_0).c2rust_unnamed.long_data = ts_malloc(length as usize) as *mut os::raw::c_char;
        copy_nonoverlapping(data, (*self_0).c2rust_unnamed.long_data, length as usize);
    } else {
        copy_nonoverlapping(
            data,
            (*self_0).c2rust_unnamed.short_data.as_mut_ptr(),
            length as usize,
        );
    };
}
#[no_mangle]
pub(crate) unsafe extern "C" fn ts_external_scanner_state_copy(
    mut self_0: *const ExternalScannerState,
) -> ExternalScannerState {
    let mut result: ExternalScannerState = *self_0;
    if (*self_0).length as os::raw::c_ulong
        > ::std::mem::size_of::<[os::raw::c_char; 24]>() as os::raw::c_ulong
    {
        result.c2rust_unnamed.long_data =
            ts_malloc((*self_0).length as usize) as *mut os::raw::c_char;
        copy_nonoverlapping(
            (*self_0).c2rust_unnamed.long_data,
            result.c2rust_unnamed.long_data,
            (*self_0).length as usize,
        );
    }
    result
}
#[no_mangle]
pub(crate) unsafe extern "C" fn ts_external_scanner_state_delete(
    mut self_0: *mut ExternalScannerState,
) {
    if (*self_0).length as os::raw::c_ulong
        > ::std::mem::size_of::<[os::raw::c_char; 24]>() as os::raw::c_ulong
    {
        ts_free((*self_0).c2rust_unnamed.long_data as *mut ffi::c_void);
    };
}
#[no_mangle]
pub(crate) unsafe extern "C" fn ts_external_scanner_state_data(
    mut self_0: *const ExternalScannerState,
) -> *const os::raw::c_char {
    if (*self_0).length as os::raw::c_ulong
        > ::std::mem::size_of::<[os::raw::c_char; 24]>() as os::raw::c_ulong
    {
        (*self_0).c2rust_unnamed.long_data
    } else {
        (*self_0).c2rust_unnamed.short_data.as_ptr()
    }
}
#[no_mangle]
pub(crate) unsafe extern "C" fn ts_external_scanner_state_eq(
    mut a: *const ExternalScannerState,
    mut b: *const ExternalScannerState,
) -> bool {
    a == b
        || (*a).length == (*b).length
            && std::slice::from_raw_parts(ts_external_scanner_state_data(a), (*a).length as usize)
                == std::slice::from_raw_parts(
                    ts_external_scanner_state_data(b),
                    (*a).length as usize,
                )
}
// SubtreeArray
#[no_mangle]
pub(crate) unsafe extern "C" fn ts_subtree_array_copy(
    mut self_0: SubtreeArray,
    mut dest: *mut SubtreeArray,
) {
    (*dest).size = self_0.size;
    (*dest).capacity = self_0.capacity;
    (*dest).contents = self_0.contents;
    if self_0.capacity > 0 as os::raw::c_int as os::raw::c_uint {
        (*dest).contents =
            ts_calloc(self_0.capacity as usize, ::std::mem::size_of::<Subtree>()) as *mut Subtree;
        copy_nonoverlapping(self_0.contents, (*dest).contents, self_0.size as usize);
        let mut i: u32 = 0 as os::raw::c_int as u32;
        while i < self_0.size {
            ts_subtree_retain(*(*dest).contents.offset(i as isize));
            i = i.wrapping_add(1)
        }
    };
}
#[no_mangle]
pub(crate) unsafe extern "C" fn ts_subtree_array_delete(
    mut pool: *mut SubtreePool,
    mut self_0: *mut SubtreeArray,
) {
    let mut i: u32 = 0 as os::raw::c_int as u32;
    while i < (*self_0).size {
        ts_subtree_release(pool, *(*self_0).contents.offset(i as isize));
        i = i.wrapping_add(1)
    }
    array__delete(self_0 as *mut VoidArray);
}
#[no_mangle]
pub(crate) unsafe extern "C" fn ts_subtree_array_remove_trailing_extras(
    mut self_0: *mut SubtreeArray,
) -> SubtreeArray {
    let mut result = SubtreeArray {
        contents: std::ptr::null_mut::<Subtree>(),
        size: 0 as os::raw::c_int as u32,
        capacity: 0 as os::raw::c_int as u32,
    };
    let mut i: u32 = (*self_0).size.wrapping_sub(1);
    while i.wrapping_add(1) > 0 as os::raw::c_int as os::raw::c_uint {
        let mut child: Subtree = *(*self_0).contents.offset(i as isize);
        if !ts_subtree_extra(child) {
            break;
        }
        array__grow(
            &mut result as *mut SubtreeArray as *mut VoidArray,
            1 as os::raw::c_int as usize,
            ::std::mem::size_of::<Subtree>(),
        );
        let fresh4 = result.size;
        result.size = result.size.wrapping_add(1);
        *result.contents.offset(fresh4 as isize) = child;
        i = i.wrapping_sub(1)
    }
    (*self_0).size = i.wrapping_add(1);
    ts_subtree_array_reverse(&mut result);
    result
}
#[no_mangle]
pub(crate) unsafe extern "C" fn ts_subtree_array_reverse(mut self_0: *mut SubtreeArray) {
    let mut i: u32 = 0 as os::raw::c_int as u32;
    let mut limit: u32 = (*self_0).size.wrapping_div(2);
    while i < limit {
        let mut reverse_index: usize = (*self_0).size.wrapping_sub(1).wrapping_sub(i) as usize;
        let mut swap: Subtree = *(*self_0).contents.offset(i as isize);
        *(*self_0).contents.offset(i as isize) = *(*self_0).contents.add(reverse_index);
        *(*self_0).contents.add(reverse_index) = swap;
        i = i.wrapping_add(1)
    }
}
// SubtreePool
#[no_mangle]
pub(crate) unsafe extern "C" fn ts_subtree_pool_new(mut capacity: u32) -> SubtreePool {
    let mut self_0 = SubtreePool {
        free_trees: MutableSubtreeArray {
            contents: std::ptr::null_mut::<MutableSubtree>(),
            size: 0 as os::raw::c_int as u32,
            capacity: 0 as os::raw::c_int as u32,
        },
        tree_stack: MutableSubtreeArray {
            contents: std::ptr::null_mut::<MutableSubtree>(),
            size: 0 as os::raw::c_int as u32,
            capacity: 0 as os::raw::c_int as u32,
        },
    };
    array__reserve(
        &mut self_0.free_trees as *mut MutableSubtreeArray as *mut VoidArray,
        ::std::mem::size_of::<MutableSubtree>(),
        capacity,
    );
    self_0
}
#[no_mangle]
pub(crate) unsafe extern "C" fn ts_subtree_pool_delete(mut self_0: *mut SubtreePool) {
    if !(*self_0).free_trees.contents.is_null() {
        let mut i: os::raw::c_uint = 0 as os::raw::c_int as os::raw::c_uint;
        while i < (*self_0).free_trees.size {
            ts_free((*(*self_0).free_trees.contents.offset(i as isize)).ptr as *mut ffi::c_void);
            i = i.wrapping_add(1)
        }
        array__delete(&mut (*self_0).free_trees as *mut MutableSubtreeArray as *mut VoidArray);
    }
    if !(*self_0).tree_stack.contents.is_null() {
        array__delete(&mut (*self_0).tree_stack as *mut MutableSubtreeArray as *mut VoidArray);
    };
}
unsafe extern "C" fn ts_subtree_pool_allocate(
    mut self_0: *mut SubtreePool,
) -> *mut SubtreeHeapData {
    if (*self_0).free_trees.size > 0 as os::raw::c_int as os::raw::c_uint {
        (*self_0).free_trees.size = (*self_0).free_trees.size.wrapping_sub(1);
        (*(*self_0)
            .free_trees
            .contents
            .offset((*self_0).free_trees.size as isize))
        .ptr
    } else {
        ts_malloc(::std::mem::size_of::<SubtreeHeapData>()) as *mut SubtreeHeapData
    }
}
unsafe extern "C" fn ts_subtree_pool_free(
    mut self_0: *mut SubtreePool,
    mut tree: *mut SubtreeHeapData,
) {
    if (*self_0).free_trees.capacity > 0 as os::raw::c_int as os::raw::c_uint
        && (*self_0).free_trees.size.wrapping_add(1) <= 32 as os::raw::c_int as os::raw::c_uint
    {
        array__grow(
            &mut (*self_0).free_trees as *mut MutableSubtreeArray as *mut VoidArray,
            1 as os::raw::c_int as usize,
            ::std::mem::size_of::<MutableSubtree>(),
        );
        let fresh5 = (*self_0).free_trees.size;
        (*self_0).free_trees.size = (*self_0).free_trees.size.wrapping_add(1);
        *(*self_0).free_trees.contents.offset(fresh5 as isize) = MutableSubtree { ptr: tree }
    } else {
        ts_free(tree as *mut ffi::c_void);
    };
}
// Subtree
#[inline]
unsafe extern "C" fn ts_subtree_can_inline(
    mut padding: Length,
    mut size: Length,
    mut lookahead_bytes: u32,
) -> bool {
    padding.bytes < 255 as os::raw::c_int as os::raw::c_uint
        && padding.extent.row < 16 as os::raw::c_int as os::raw::c_uint
        && padding.extent.column < 255 as os::raw::c_int as os::raw::c_uint
        && size.extent.row == 0 as os::raw::c_int as os::raw::c_uint
        && size.extent.column < 255 as os::raw::c_int as os::raw::c_uint
        && lookahead_bytes < 16 as os::raw::c_int as os::raw::c_uint
}
#[no_mangle]
pub(crate) unsafe extern "C" fn ts_subtree_new_leaf(
    mut pool: *mut SubtreePool,
    mut symbol: TSSymbol,
    mut padding: Length,
    mut size: Length,
    mut lookahead_bytes: u32,
    mut parse_state: TSStateId,
    mut has_external_tokens: bool,
    mut is_keyword: bool,
    mut language: *const TSLanguage,
) -> Subtree {
    let mut metadata: TSSymbolMetadata = ts_language_symbol_metadata(language, symbol);
    let mut extra: bool = symbol as os::raw::c_int == 0 as os::raw::c_int;
    let mut is_inline: bool = symbol as os::raw::c_int <= 255 as os::raw::c_int
        && !has_external_tokens
        && ts_subtree_can_inline(padding, size, lookahead_bytes) as os::raw::c_int != 0;
    if is_inline {
        Subtree {
            data: {
                let mut init = SubtreeInlineData {
                    is_inline_visible_named_extra_has_changes_is_missing_is_keyword: [0; 1],
                    padding_rows_lookahead_bytes: [0; 1],
                    symbol: symbol as u8,
                    padding_bytes: padding.bytes as u8,
                    size_bytes: size.bytes as u8,
                    padding_columns: padding.extent.column as u8,
                    parse_state,
                };
                init.set_is_inline(true);
                init.set_visible(metadata.visible());
                init.set_named(metadata.named());
                init.set_extra(extra);
                init.set_has_changes(false);
                init.set_is_missing(false);
                init.set_is_keyword(is_keyword);
                init.set_padding_rows(padding.extent.row as u8);
                init.set_lookahead_bytes(lookahead_bytes as u8);
                init
            },
        }
    } else {
        let mut data: *mut SubtreeHeapData = ts_subtree_pool_allocate(pool);
        *data = {
            let data_content = SubtreeHeapDataContentData {
                children: ptr::null_mut(),
                visible_child_count: 0,
                named_child_count: 0,
                node_count: 0,
                repeat_depth: 0,
                dynamic_precedence: 0,
                production_id: 0,
                first_leaf: SubtreeHeapDataContentDataFirstLeaf {
                    symbol: 0 as os::raw::c_int as TSSymbol,
                    parse_state: 0 as os::raw::c_int as TSStateId,
                },
            };
            let mut init = SubtreeHeapData {
                visible_named_extra_fragile_left_fragile_right_has_changes_has_external_tokens_is_missing_is_keyword: [0; 2],
                c2rust_padding: [0; 2],
                ref_count: 1 as os::raw::c_int as u32,
                padding,
                size,
                lookahead_bytes,
                error_cost: 0 as os::raw::c_int as u32,
                child_count: 0 as os::raw::c_int as u32,
                symbol,
                parse_state,
                c2rust_unnamed: SubtreeHeapDataContent{
                    c2rust_unnamed: data_content
                },
            };
            init.set_visible(metadata.visible());
            init.set_named(metadata.named());
            init.set_extra(extra);
            init.set_fragile_left(false);
            init.set_fragile_right(false);
            init.set_has_changes(false);
            init.set_has_external_tokens(has_external_tokens);
            init.set_is_missing(false);
            init.set_is_keyword(is_keyword);
            init
        };
        Subtree { ptr: data }
    }
}
#[no_mangle]
pub(crate) unsafe extern "C" fn ts_subtree_set_symbol(
    mut self_0: *mut MutableSubtree,
    mut symbol: TSSymbol,
    mut language: *const TSLanguage,
) {
    let mut metadata: TSSymbolMetadata = ts_language_symbol_metadata(language, symbol);
    if (*self_0).data.is_inline() {
        assert!((symbol as os::raw::c_int) < 255 as os::raw::c_int);
        (*self_0).data.symbol = symbol as u8;
        (*self_0).data.set_named(metadata.named());
        (*self_0).data.set_visible(metadata.visible())
    } else {
        (*(*self_0).ptr).symbol = symbol;
        (*(*self_0).ptr).set_named(metadata.named());
        (*(*self_0).ptr).set_visible(metadata.visible())
    };
}
#[no_mangle]
pub(crate) unsafe extern "C" fn ts_subtree_new_error(
    mut pool: *mut SubtreePool,
    mut lookahead_char: i32,
    mut padding: Length,
    mut size: Length,
    mut bytes_scanned: u32,
    mut parse_state: TSStateId,
    mut language: *const TSLanguage,
) -> Subtree {
    let mut result: Subtree = ts_subtree_new_leaf(
        pool,
        -(1 as os::raw::c_int) as TSSymbol,
        padding,
        size,
        bytes_scanned,
        parse_state,
        false,
        false,
        language,
    );
    let mut data: *mut SubtreeHeapData = result.ptr as *mut SubtreeHeapData;
    (*data).set_fragile_left(true);
    (*data).set_fragile_right(true);
    (*data).c2rust_unnamed.lookahead_char = lookahead_char;
    result
}
#[no_mangle]
pub(crate) unsafe extern "C" fn ts_subtree_make_mut(
    mut pool: *mut SubtreePool,
    mut self_0: Subtree,
) -> MutableSubtree {
    if self_0.data.is_inline() {
        return MutableSubtree { data: self_0.data };
    }
    if (*self_0.ptr).ref_count == 1 as os::raw::c_int as os::raw::c_uint {
        return ts_subtree_to_mut_unsafe(self_0);
    }
    let mut result: *mut SubtreeHeapData = ts_subtree_pool_allocate(pool);
    copy_nonoverlapping(self_0.ptr, result, 1);
    if (*result).child_count > 0 as os::raw::c_int as os::raw::c_uint {
        (*result).c2rust_unnamed.c2rust_unnamed.children = ts_calloc(
            (*self_0.ptr).child_count as usize,
            ::std::mem::size_of::<Subtree>(),
        ) as *mut Subtree;
        copy_nonoverlapping(
            (*self_0.ptr).c2rust_unnamed.c2rust_unnamed.children,
            (*result).c2rust_unnamed.c2rust_unnamed.children,
            (*result).child_count as usize,
        );
        let mut i: u32 = 0 as os::raw::c_int as u32;
        while i < (*result).child_count {
            ts_subtree_retain(
                *(*result)
                    .c2rust_unnamed
                    .c2rust_unnamed
                    .children
                    .offset(i as isize),
            );
            i = i.wrapping_add(1)
        }
    } else if (*result).has_external_tokens() {
        (*result).c2rust_unnamed.external_scanner_state =
            ts_external_scanner_state_copy(&(*self_0.ptr).c2rust_unnamed.external_scanner_state)
    }
    ::std::ptr::write_volatile(
        &mut (*result).ref_count as *mut u32,
        1 as os::raw::c_int as u32,
    );
    ts_subtree_release(pool, self_0);
    MutableSubtree { ptr: result }
}
unsafe extern "C" fn ts_subtree__compress(
    mut self_0: MutableSubtree,
    mut count: os::raw::c_uint,
    mut language: *const TSLanguage,
    mut stack: *mut MutableSubtreeArray,
) {
    let mut initial_stack_size: os::raw::c_uint = (*stack).size;
    let mut tree: MutableSubtree = self_0;
    let mut symbol: TSSymbol = (*tree.ptr).symbol;
    let mut i: os::raw::c_uint = 0 as os::raw::c_int as os::raw::c_uint;
    while i < count {
        if (*tree.ptr).ref_count > 1 as os::raw::c_int as os::raw::c_uint
            || (*tree.ptr).child_count < 2 as os::raw::c_int as os::raw::c_uint
        {
            break;
        }
        let mut child: MutableSubtree = ts_subtree_to_mut_unsafe(
            *(*tree.ptr)
                .c2rust_unnamed
                .c2rust_unnamed
                .children
                .offset(0 as os::raw::c_int as isize),
        );
        if child.data.is_inline() as os::raw::c_int != 0
            || (*child.ptr).child_count < 2 as os::raw::c_int as os::raw::c_uint
            || (*child.ptr).ref_count > 1 as os::raw::c_int as os::raw::c_uint
            || (*child.ptr).symbol as os::raw::c_int != symbol as os::raw::c_int
        {
            break;
        }
        let mut grandchild: MutableSubtree = ts_subtree_to_mut_unsafe(
            *(*child.ptr)
                .c2rust_unnamed
                .c2rust_unnamed
                .children
                .offset(0 as os::raw::c_int as isize),
        );
        if grandchild.data.is_inline() as os::raw::c_int != 0
            || (*grandchild.ptr).child_count < 2 as os::raw::c_int as os::raw::c_uint
            || (*grandchild.ptr).ref_count > 1 as os::raw::c_int as os::raw::c_uint
            || (*grandchild.ptr).symbol as os::raw::c_int != symbol as os::raw::c_int
        {
            break;
        }
        *(*tree.ptr)
            .c2rust_unnamed
            .c2rust_unnamed
            .children
            .offset(0 as os::raw::c_int as isize) = ts_subtree_from_mut(grandchild);
        *(*child.ptr)
            .c2rust_unnamed
            .c2rust_unnamed
            .children
            .offset(0 as os::raw::c_int as isize) = *(*grandchild.ptr)
            .c2rust_unnamed
            .c2rust_unnamed
            .children
            .offset((*grandchild.ptr).child_count.wrapping_sub(1) as isize);
        *(*grandchild.ptr)
            .c2rust_unnamed
            .c2rust_unnamed
            .children
            .offset((*grandchild.ptr).child_count.wrapping_sub(1) as isize) =
            ts_subtree_from_mut(child);
        array__grow(
            stack as *mut VoidArray,
            1 as os::raw::c_int as usize,
            ::std::mem::size_of::<MutableSubtree>(),
        );
        let fresh6 = (*stack).size;
        (*stack).size = (*stack).size.wrapping_add(1);
        *(*stack).contents.offset(fresh6 as isize) = tree;
        tree = grandchild;
        i = i.wrapping_add(1)
    }
    while (*stack).size > initial_stack_size {
        (*stack).size = (*stack).size.wrapping_sub(1);
        tree = *(*stack).contents.offset((*stack).size as isize);
        let mut child_0: MutableSubtree = ts_subtree_to_mut_unsafe(
            *(*tree.ptr)
                .c2rust_unnamed
                .c2rust_unnamed
                .children
                .offset(0 as os::raw::c_int as isize),
        );
        let mut grandchild_0: MutableSubtree = ts_subtree_to_mut_unsafe(
            *(*child_0.ptr)
                .c2rust_unnamed
                .c2rust_unnamed
                .children
                .offset((*child_0.ptr).child_count.wrapping_sub(1) as isize),
        );
        ts_subtree_set_children(
            grandchild_0,
            (*grandchild_0.ptr).c2rust_unnamed.c2rust_unnamed.children,
            (*grandchild_0.ptr).child_count,
            language,
        );
        ts_subtree_set_children(
            child_0,
            (*child_0.ptr).c2rust_unnamed.c2rust_unnamed.children,
            (*child_0.ptr).child_count,
            language,
        );
        ts_subtree_set_children(
            tree,
            (*tree.ptr).c2rust_unnamed.c2rust_unnamed.children,
            (*tree.ptr).child_count,
            language,
        );
    }
}
#[no_mangle]
pub(crate) unsafe extern "C" fn ts_subtree_balance(
    mut self_0: Subtree,
    mut pool: *mut SubtreePool,
    mut language: *const TSLanguage,
) {
    (*pool).tree_stack.size = 0 as os::raw::c_int as u32;
    if ts_subtree_child_count(self_0) > 0 as os::raw::c_int as os::raw::c_uint
        && (*self_0.ptr).ref_count == 1 as os::raw::c_int as os::raw::c_uint
    {
        array__grow(
            &mut (*pool).tree_stack as *mut MutableSubtreeArray as *mut VoidArray,
            1 as os::raw::c_int as usize,
            ::std::mem::size_of::<MutableSubtree>(),
        );
        let fresh7 = (*pool).tree_stack.size;
        (*pool).tree_stack.size = (*pool).tree_stack.size.wrapping_add(1);
        *(*pool).tree_stack.contents.offset(fresh7 as isize) = ts_subtree_to_mut_unsafe(self_0)
    }
    while (*pool).tree_stack.size > 0 as os::raw::c_int as os::raw::c_uint {
        (*pool).tree_stack.size = (*pool).tree_stack.size.wrapping_sub(1);
        let mut tree: MutableSubtree = *(*pool)
            .tree_stack
            .contents
            .offset((*pool).tree_stack.size as isize);
        if (*tree.ptr).c2rust_unnamed.c2rust_unnamed.repeat_depth
            > 0 as os::raw::c_int as os::raw::c_uint
        {
            let mut child1: Subtree = *(*tree.ptr)
                .c2rust_unnamed
                .c2rust_unnamed
                .children
                .offset(0 as os::raw::c_int as isize);
            let mut child2: Subtree = *(*tree.ptr)
                .c2rust_unnamed
                .c2rust_unnamed
                .children
                .offset((*tree.ptr).child_count.wrapping_sub(1) as isize);
            let mut repeat_delta: os::raw::c_long = ts_subtree_repeat_depth(child1)
                as os::raw::c_long
                - ts_subtree_repeat_depth(child2) as os::raw::c_long;
            if repeat_delta > 0 as os::raw::c_int as os::raw::c_long {
                let mut n: os::raw::c_uint = repeat_delta as os::raw::c_uint;
                let mut i: os::raw::c_uint = n.wrapping_div(2);
                while i > 0 as os::raw::c_int as os::raw::c_uint {
                    ts_subtree__compress(tree, i, language, &mut (*pool).tree_stack);
                    n = n.wrapping_sub(i);
                    i = i.wrapping_div(2)
                }
            }
        }
        let mut i_0: u32 = 0 as os::raw::c_int as u32;
        while i_0 < (*tree.ptr).child_count {
            let mut child: Subtree = *(*tree.ptr)
                .c2rust_unnamed
                .c2rust_unnamed
                .children
                .offset(i_0 as isize);
            if ts_subtree_child_count(child) > 0 as os::raw::c_int as os::raw::c_uint
                && (*child.ptr).ref_count == 1 as os::raw::c_int as os::raw::c_uint
            {
                array__grow(
                    &mut (*pool).tree_stack as *mut MutableSubtreeArray as *mut VoidArray,
                    1 as os::raw::c_int as usize,
                    ::std::mem::size_of::<MutableSubtree>(),
                );
                let fresh8 = (*pool).tree_stack.size;
                (*pool).tree_stack.size = (*pool).tree_stack.size.wrapping_add(1);
                *(*pool).tree_stack.contents.offset(fresh8 as isize) =
                    ts_subtree_to_mut_unsafe(child)
            }
            i_0 = i_0.wrapping_add(1)
        }
    }
}
#[no_mangle]
pub(crate) unsafe extern "C" fn ts_subtree_set_children(
    mut self_0: MutableSubtree,
    mut children: *mut Subtree,
    mut child_count: u32,
    mut language: *const TSLanguage,
) {
    assert!(!self_0.data.is_inline());
    if (*self_0.ptr).child_count > 0 as os::raw::c_int as os::raw::c_uint
        && children != (*self_0.ptr).c2rust_unnamed.c2rust_unnamed.children
    {
        ts_free((*self_0.ptr).c2rust_unnamed.c2rust_unnamed.children as *mut ffi::c_void);
    }
    (*self_0.ptr).child_count = child_count;
    (*self_0.ptr).c2rust_unnamed.c2rust_unnamed.children = children;
    (*self_0.ptr)
        .c2rust_unnamed
        .c2rust_unnamed
        .named_child_count = 0 as os::raw::c_int as u32;
    (*self_0.ptr)
        .c2rust_unnamed
        .c2rust_unnamed
        .visible_child_count = 0 as os::raw::c_int as u32;
    (*self_0.ptr).error_cost = 0 as os::raw::c_int as u32;
    (*self_0.ptr).c2rust_unnamed.c2rust_unnamed.repeat_depth = 0 as os::raw::c_int as u32;
    (*self_0.ptr).c2rust_unnamed.c2rust_unnamed.node_count = 1 as os::raw::c_int as u32;
    (*self_0.ptr).set_has_external_tokens(false);
    (*self_0.ptr)
        .c2rust_unnamed
        .c2rust_unnamed
        .dynamic_precedence = 0 as os::raw::c_int;
    let mut non_extra_index: u32 = 0 as os::raw::c_int as u32;
    let mut alias_sequence: *const TSSymbol = ts_language_alias_sequence(
        language,
        (*self_0.ptr).c2rust_unnamed.c2rust_unnamed.production_id as u32,
    );
    let mut lookahead_end_byte: u32 = 0 as os::raw::c_int as u32;
    let mut i: u32 = 0 as os::raw::c_int as u32;
    while i < (*self_0.ptr).child_count {
        let mut child: Subtree = *(*self_0.ptr)
            .c2rust_unnamed
            .c2rust_unnamed
            .children
            .offset(i as isize);
        if i == 0 as os::raw::c_int as os::raw::c_uint {
            (*self_0.ptr).padding = ts_subtree_padding(child);
            (*self_0.ptr).size = ts_subtree_size(child)
        } else {
            (*self_0.ptr).size = length_add((*self_0.ptr).size, ts_subtree_total_size(child))
        }
        let mut child_lookahead_end_byte: u32 = (*self_0.ptr)
            .padding
            .bytes
            .wrapping_add((*self_0.ptr).size.bytes)
            .wrapping_add(ts_subtree_lookahead_bytes(child));
        if child_lookahead_end_byte > lookahead_end_byte {
            lookahead_end_byte = child_lookahead_end_byte
        }
        if ts_subtree_symbol(child) as os::raw::c_int
            != -(1 as os::raw::c_int) as TSSymbol as os::raw::c_int - 1 as os::raw::c_int
        {
            (*self_0.ptr).error_cost = ((*self_0.ptr).error_cost as os::raw::c_uint)
                .wrapping_add(ts_subtree_error_cost(child))
                as u32 as u32
        }
        (*self_0.ptr)
            .c2rust_unnamed
            .c2rust_unnamed
            .dynamic_precedence += ts_subtree_dynamic_precedence(child);
        (*self_0.ptr).c2rust_unnamed.c2rust_unnamed.node_count =
            ((*self_0.ptr).c2rust_unnamed.c2rust_unnamed.node_count as os::raw::c_uint)
                .wrapping_add(ts_subtree_node_count(child)) as u32 as u32;
        if !alias_sequence.is_null()
            && *alias_sequence.offset(non_extra_index as isize) as os::raw::c_int
                != 0 as os::raw::c_int
            && !ts_subtree_extra(child)
        {
            (*self_0.ptr)
                .c2rust_unnamed
                .c2rust_unnamed
                .visible_child_count = (*self_0.ptr)
                .c2rust_unnamed
                .c2rust_unnamed
                .visible_child_count
                .wrapping_add(1);
            if ts_language_symbol_metadata(
                language,
                *alias_sequence.offset(non_extra_index as isize),
            )
            .named()
            {
                (*self_0.ptr)
                    .c2rust_unnamed
                    .c2rust_unnamed
                    .named_child_count = (*self_0.ptr)
                    .c2rust_unnamed
                    .c2rust_unnamed
                    .named_child_count
                    .wrapping_add(1)
            }
        } else if ts_subtree_visible(child) {
            (*self_0.ptr)
                .c2rust_unnamed
                .c2rust_unnamed
                .visible_child_count = (*self_0.ptr)
                .c2rust_unnamed
                .c2rust_unnamed
                .visible_child_count
                .wrapping_add(1);
            if ts_subtree_named(child) {
                (*self_0.ptr)
                    .c2rust_unnamed
                    .c2rust_unnamed
                    .named_child_count = (*self_0.ptr)
                    .c2rust_unnamed
                    .c2rust_unnamed
                    .named_child_count
                    .wrapping_add(1)
            }
        } else if ts_subtree_child_count(child) > 0 as os::raw::c_int as os::raw::c_uint {
            (*self_0.ptr)
                .c2rust_unnamed
                .c2rust_unnamed
                .visible_child_count = ((*self_0.ptr)
                .c2rust_unnamed
                .c2rust_unnamed
                .visible_child_count as os::raw::c_uint)
                .wrapping_add(
                    (*child.ptr)
                        .c2rust_unnamed
                        .c2rust_unnamed
                        .visible_child_count,
                ) as u32 as u32;
            (*self_0.ptr)
                .c2rust_unnamed
                .c2rust_unnamed
                .named_child_count = ((*self_0.ptr)
                .c2rust_unnamed
                .c2rust_unnamed
                .named_child_count as os::raw::c_uint)
                .wrapping_add((*child.ptr).c2rust_unnamed.c2rust_unnamed.named_child_count)
                as u32 as u32
        }
        if ts_subtree_has_external_tokens(child) {
            (*self_0.ptr).set_has_external_tokens(true)
        }
        if ts_subtree_is_error(child) {
            (*self_0.ptr).set_fragile_right(true);
            (*self_0.ptr).set_fragile_left((*self_0.ptr).fragile_right());
            (*self_0.ptr).parse_state = TS_TREE_STATE_NONE
        }
        if !ts_subtree_extra(child) {
            non_extra_index = non_extra_index.wrapping_add(1)
        }
        i = i.wrapping_add(1)
    }
    (*self_0.ptr).lookahead_bytes = lookahead_end_byte
        .wrapping_sub((*self_0.ptr).size.bytes)
        .wrapping_sub((*self_0.ptr).padding.bytes);
    if (*self_0.ptr).symbol as os::raw::c_int
        == -(1 as os::raw::c_int) as TSSymbol as os::raw::c_int
        || (*self_0.ptr).symbol as os::raw::c_int
            == -(1 as os::raw::c_int) as TSSymbol as os::raw::c_int - 1 as os::raw::c_int
    {
        (*self_0.ptr).error_cost = ((*self_0.ptr).error_cost as os::raw::c_uint).wrapping_add(
            (500 as os::raw::c_int as os::raw::c_uint)
                .wrapping_add(
                    (1 as os::raw::c_int as os::raw::c_uint).wrapping_mul((*self_0.ptr).size.bytes),
                )
                .wrapping_add(
                    (30 as os::raw::c_int as os::raw::c_uint)
                        .wrapping_mul((*self_0.ptr).size.extent.row),
                ),
        ) as u32 as u32;
        let mut i_0: u32 = 0 as os::raw::c_int as u32;
        while i_0 < (*self_0.ptr).child_count {
            let mut child_0: Subtree = *(*self_0.ptr)
                .c2rust_unnamed
                .c2rust_unnamed
                .children
                .offset(i_0 as isize);
            let mut grandchild_count: u32 = ts_subtree_child_count(child_0);
            if !(ts_subtree_extra(child_0)
                || ts_subtree_is_error(child_0) as os::raw::c_int != 0
                    && grandchild_count == 0 as os::raw::c_int as os::raw::c_uint)
            {
                if ts_subtree_visible(child_0) {
                    (*self_0.ptr).error_cost = ((*self_0.ptr).error_cost as os::raw::c_uint)
                        .wrapping_add(100) as u32
                        as u32
                } else if grandchild_count > 0 as os::raw::c_int as os::raw::c_uint {
                    (*self_0.ptr).error_cost = ((*self_0.ptr).error_cost as os::raw::c_uint)
                        .wrapping_add(
                            (100 as os::raw::c_int as os::raw::c_uint).wrapping_mul(
                                (*child_0.ptr)
                                    .c2rust_unnamed
                                    .c2rust_unnamed
                                    .visible_child_count,
                            ),
                        ) as u32 as u32
                }
            }
            i_0 = i_0.wrapping_add(1)
        }
    }
    if (*self_0.ptr).child_count > 0 as os::raw::c_int as os::raw::c_uint {
        let mut first_child: Subtree = *(*self_0.ptr)
            .c2rust_unnamed
            .c2rust_unnamed
            .children
            .offset(0 as os::raw::c_int as isize);
        let mut last_child: Subtree = *(*self_0.ptr)
            .c2rust_unnamed
            .c2rust_unnamed
            .children
            .offset((*self_0.ptr).child_count.wrapping_sub(1) as isize);
        (*self_0.ptr)
            .c2rust_unnamed
            .c2rust_unnamed
            .first_leaf
            .symbol = ts_subtree_leaf_symbol(first_child);
        (*self_0.ptr)
            .c2rust_unnamed
            .c2rust_unnamed
            .first_leaf
            .parse_state = ts_subtree_leaf_parse_state(first_child);
        if ts_subtree_fragile_left(first_child) {
            (*self_0.ptr).set_fragile_left(true)
        }
        if ts_subtree_fragile_right(last_child) {
            (*self_0.ptr).set_fragile_right(true)
        }
        if (*self_0.ptr).child_count >= 2 as os::raw::c_int as os::raw::c_uint
            && !(*self_0.ptr).visible()
            && !(*self_0.ptr).named()
            && ts_subtree_symbol(first_child) as os::raw::c_int
                == (*self_0.ptr).symbol as os::raw::c_int
        {
            if ts_subtree_repeat_depth(first_child) > ts_subtree_repeat_depth(last_child) {
                (*self_0.ptr).c2rust_unnamed.c2rust_unnamed.repeat_depth =
                    ts_subtree_repeat_depth(first_child).wrapping_add(1)
            } else {
                (*self_0.ptr).c2rust_unnamed.c2rust_unnamed.repeat_depth =
                    ts_subtree_repeat_depth(last_child).wrapping_add(1)
            }
        }
    };
}
#[no_mangle]
pub(crate) unsafe extern "C" fn ts_subtree_new_node(
    mut pool: *mut SubtreePool,
    mut symbol: TSSymbol,
    mut children: *mut SubtreeArray,
    mut production_id: os::raw::c_uint,
    mut language: *const TSLanguage,
) -> MutableSubtree {
    let mut metadata: TSSymbolMetadata = ts_language_symbol_metadata(language, symbol);
    let mut fragile: bool = symbol as os::raw::c_int
        == -(1 as os::raw::c_int) as TSSymbol as os::raw::c_int
        || symbol as os::raw::c_int
            == -(1 as os::raw::c_int) as TSSymbol as os::raw::c_int - 1 as os::raw::c_int;
    let mut data: *mut SubtreeHeapData = ts_subtree_pool_allocate(pool);
    *data = {
        let data_content = SubtreeHeapDataContent {
            c2rust_unnamed: SubtreeHeapDataContentData {
                children: ptr::null_mut(),
                visible_child_count: 0,
                named_child_count: 0,
                node_count: 0,
                repeat_depth: 0,
                dynamic_precedence: 0,
                production_id: production_id as u16,
                first_leaf: SubtreeHeapDataContentDataFirstLeaf {
                    symbol: 0,
                    parse_state: 0,
                },
            },
        };
        let mut init = SubtreeHeapData{
            visible_named_extra_fragile_left_fragile_right_has_changes_has_external_tokens_is_missing_is_keyword: [0; 2],
            c2rust_padding: [0; 2],
            ref_count: 1 as os::raw::c_int as u32,
            padding: Length{
                bytes: 0,
                extent: TSPoint{row: 0, column: 0,},
            },
            size: Length{
                bytes: 0,
                extent: TSPoint{row: 0, column: 0,},
            },
            lookahead_bytes: 0,
            error_cost: 0,
            child_count: 0,
            symbol,
            parse_state: 0,
            c2rust_unnamed: data_content,
        };
        init.set_visible(metadata.visible());
        init.set_named(metadata.named());
        init.set_extra(false);
        init.set_fragile_left(fragile);
        init.set_fragile_right(fragile);
        init.set_has_changes(false);
        init.set_has_external_tokens(false);
        init.set_is_missing(false);
        init.set_is_keyword(false);
        init
    };
    let mut result: MutableSubtree = MutableSubtree { ptr: data };
    ts_subtree_set_children(result, (*children).contents, (*children).size, language);
    result
}
#[no_mangle]
pub(crate) unsafe extern "C" fn ts_subtree_new_error_node(
    mut pool: *mut SubtreePool,
    mut children: *mut SubtreeArray,
    mut extra: bool,
    mut language: *const TSLanguage,
) -> Subtree {
    let mut result: MutableSubtree = ts_subtree_new_node(
        pool,
        -(1 as os::raw::c_int) as TSSymbol,
        children,
        0 as os::raw::c_int as os::raw::c_uint,
        language,
    );
    (*result.ptr).set_extra(extra);
    ts_subtree_from_mut(result)
}
#[no_mangle]
pub(crate) unsafe extern "C" fn ts_subtree_new_missing_leaf(
    mut pool: *mut SubtreePool,
    mut symbol: TSSymbol,
    mut padding: Length,
    mut language: *const TSLanguage,
) -> Subtree {
    let mut result: Subtree = ts_subtree_new_leaf(
        pool,
        symbol,
        padding,
        length_zero(),
        0 as os::raw::c_int as u32,
        0 as os::raw::c_int as TSStateId,
        false,
        false,
        language,
    );
    if result.data.is_inline() {
        result.data.set_is_missing(true)
    } else {
        let fresh9 = &mut *(result.ptr as *mut SubtreeHeapData);
        (*fresh9).set_is_missing(true)
    }
    result
}
#[no_mangle]
pub(crate) unsafe extern "C" fn ts_subtree_retain(mut self_0: Subtree) {
    if self_0.data.is_inline() {
        return;
    }
    assert!((*self_0.ptr).ref_count > 0 as os::raw::c_int as os::raw::c_uint);
    atomic_inc(&(*self_0.ptr).ref_count as *const u32 as *mut u32);
    assert!((*self_0.ptr).ref_count != 0 as os::raw::c_int as os::raw::c_uint);
}
#[no_mangle]
pub(crate) unsafe extern "C" fn ts_subtree_release(
    mut pool: *mut SubtreePool,
    mut self_0: Subtree,
) {
    if self_0.data.is_inline() {
        return;
    }
    (*pool).tree_stack.size = 0 as os::raw::c_int as u32;
    assert!((*self_0.ptr).ref_count > 0 as os::raw::c_int as os::raw::c_uint);
    if atomic_dec(&(*self_0.ptr).ref_count as *const u32 as *mut u32)
        == 0 as os::raw::c_int as os::raw::c_uint
    {
        array__grow(
            &mut (*pool).tree_stack as *mut MutableSubtreeArray as *mut VoidArray,
            1 as os::raw::c_int as usize,
            ::std::mem::size_of::<MutableSubtree>(),
        );
        let fresh10 = (*pool).tree_stack.size;
        (*pool).tree_stack.size = (*pool).tree_stack.size.wrapping_add(1);
        *(*pool).tree_stack.contents.offset(fresh10 as isize) = ts_subtree_to_mut_unsafe(self_0)
    }
    while (*pool).tree_stack.size > 0 as os::raw::c_int as os::raw::c_uint {
        (*pool).tree_stack.size = (*pool).tree_stack.size.wrapping_sub(1);
        let mut tree: MutableSubtree = *(*pool)
            .tree_stack
            .contents
            .offset((*pool).tree_stack.size as isize);
        if (*tree.ptr).child_count > 0 as os::raw::c_int as os::raw::c_uint {
            let mut i: u32 = 0 as os::raw::c_int as u32;
            while i < (*tree.ptr).child_count {
                let mut child: Subtree = *(*tree.ptr)
                    .c2rust_unnamed
                    .c2rust_unnamed
                    .children
                    .offset(i as isize);
                if !child.data.is_inline() {
                    assert!((*child.ptr).ref_count > 0 as os::raw::c_int as os::raw::c_uint);
                    if atomic_dec(&(*child.ptr).ref_count as *const u32 as *mut u32)
                        == 0 as os::raw::c_int as os::raw::c_uint
                    {
                        array__grow(
                            &mut (*pool).tree_stack as *mut MutableSubtreeArray as *mut VoidArray,
                            1 as os::raw::c_int as usize,
                            ::std::mem::size_of::<MutableSubtree>(),
                        );
                        let fresh11 = (*pool).tree_stack.size;
                        (*pool).tree_stack.size = (*pool).tree_stack.size.wrapping_add(1);
                        *(*pool).tree_stack.contents.offset(fresh11 as isize) =
                            ts_subtree_to_mut_unsafe(child)
                    }
                }
                i = i.wrapping_add(1)
            }
            ts_free((*tree.ptr).c2rust_unnamed.c2rust_unnamed.children as *mut ffi::c_void);
        } else if (*tree.ptr).has_external_tokens() {
            ts_external_scanner_state_delete(
                &mut (*tree.ptr).c2rust_unnamed.external_scanner_state,
            );
        }
        ts_subtree_pool_free(pool, tree.ptr);
    }
}
#[no_mangle]
pub(crate) unsafe extern "C" fn ts_subtree_eq(mut self_0: Subtree, mut other: Subtree) -> bool {
    if self_0.data.is_inline() as os::raw::c_int != 0
        || other.data.is_inline() as os::raw::c_int != 0
    {
        return std::slice::from_raw_parts(
            &mut self_0 as *mut Subtree as *const u8,
            ::std::mem::size_of::<SubtreeInlineData>(),
        ) == std::slice::from_raw_parts(
            &mut other as *mut Subtree as *const u8,
            ::std::mem::size_of::<SubtreeInlineData>(),
        );
    }
    if !self_0.ptr.is_null() {
        if other.ptr.is_null() {
            return false;
        }
    } else {
        return other.ptr.is_null();
    }
    if (*self_0.ptr).symbol as os::raw::c_int != (*other.ptr).symbol as os::raw::c_int {
        return false;
    }
    if (*self_0.ptr).visible() as os::raw::c_int != (*other.ptr).visible() as os::raw::c_int {
        return false;
    }
    if (*self_0.ptr).named() as os::raw::c_int != (*other.ptr).named() as os::raw::c_int {
        return false;
    }
    if (*self_0.ptr).padding.bytes != (*other.ptr).padding.bytes {
        return false;
    }
    if (*self_0.ptr).size.bytes != (*other.ptr).size.bytes {
        return false;
    }
    if (*self_0.ptr).symbol as os::raw::c_int
        == -(1 as os::raw::c_int) as TSSymbol as os::raw::c_int
    {
        return (*self_0.ptr).c2rust_unnamed.lookahead_char
            == (*other.ptr).c2rust_unnamed.lookahead_char;
    }
    if (*self_0.ptr).child_count != (*other.ptr).child_count {
        return false;
    }
    if (*self_0.ptr).child_count > 0 as os::raw::c_int as os::raw::c_uint {
        if (*self_0.ptr)
            .c2rust_unnamed
            .c2rust_unnamed
            .visible_child_count
            != (*other.ptr)
                .c2rust_unnamed
                .c2rust_unnamed
                .visible_child_count
        {
            return false;
        }
        if (*self_0.ptr)
            .c2rust_unnamed
            .c2rust_unnamed
            .named_child_count
            != (*other.ptr).c2rust_unnamed.c2rust_unnamed.named_child_count
        {
            return false;
        }
        let mut i: u32 = 0 as os::raw::c_int as u32;
        while i < (*self_0.ptr).child_count {
            if !ts_subtree_eq(
                *(*self_0.ptr)
                    .c2rust_unnamed
                    .c2rust_unnamed
                    .children
                    .offset(i as isize),
                *(*other.ptr)
                    .c2rust_unnamed
                    .c2rust_unnamed
                    .children
                    .offset(i as isize),
            ) {
                return false;
            }
            i = i.wrapping_add(1)
        }
    }
    true
}
#[no_mangle]
pub(crate) unsafe extern "C" fn ts_subtree_compare(
    mut left: Subtree,
    mut right: Subtree,
) -> os::raw::c_int {
    if (ts_subtree_symbol(left) as os::raw::c_int) < ts_subtree_symbol(right) as os::raw::c_int {
        return -(1 as os::raw::c_int);
    }
    if (ts_subtree_symbol(right) as os::raw::c_int) < ts_subtree_symbol(left) as os::raw::c_int {
        return 1 as os::raw::c_int;
    }
    if ts_subtree_child_count(left) < ts_subtree_child_count(right) {
        return -(1 as os::raw::c_int);
    }
    if ts_subtree_child_count(right) < ts_subtree_child_count(left) {
        return 1 as os::raw::c_int;
    }
    let mut i: u32 = 0 as os::raw::c_int as u32;
    let mut n: u32 = ts_subtree_child_count(left);
    while i < n {
        let mut left_child: Subtree = *(*left.ptr)
            .c2rust_unnamed
            .c2rust_unnamed
            .children
            .offset(i as isize);
        let mut right_child: Subtree = *(*right.ptr)
            .c2rust_unnamed
            .c2rust_unnamed
            .children
            .offset(i as isize);
        match ts_subtree_compare(left_child, right_child) {
            -1 => return -(1 as os::raw::c_int),
            1 => return 1 as os::raw::c_int,
            _ => {}
        }
        i = i.wrapping_add(1)
    }
    0 as os::raw::c_int
}
#[inline]
unsafe extern "C" fn ts_subtree_set_has_changes(mut self_0: *mut MutableSubtree) {
    if (*self_0).data.is_inline() {
        (*self_0).data.set_has_changes(true)
    } else {
        (*(*self_0).ptr).set_has_changes(true)
    };
}
#[no_mangle]
pub(crate) unsafe extern "C" fn ts_subtree_edit(
    mut self_0: Subtree,
    mut edit: *const TSInputEdit,
    mut pool: *mut SubtreePool,
) -> Subtree {
    #[derive(Copy, Clone)]
    #[repr(C)]
    struct LocStackEntry {
        pub tree: *mut Subtree,
        pub edit: Edit,
    }

    #[derive(Copy, Clone)]
    #[repr(C)]
    struct StackEntryArray {
        pub contents: *mut LocStackEntry,
        pub size: u32,
        pub capacity: u32,
    }

    let mut stack = StackEntryArray {
        contents: std::ptr::null_mut::<LocStackEntry>(),
        size: 0 as os::raw::c_int as u32,
        capacity: 0 as os::raw::c_int as u32,
    };
    array__grow(
        &mut stack as *mut StackEntryArray as *mut VoidArray,
        1 as os::raw::c_int as usize,
        ::std::mem::size_of::<LocStackEntry>(),
    );
    let fresh12 = stack.size;
    stack.size = stack.size.wrapping_add(1);
    *stack.contents.offset(fresh12 as isize) = LocStackEntry {
        tree: &mut self_0,
        edit: Edit {
            start: Length {
                bytes: (*edit).start_byte,
                extent: (*edit).start_point,
            },
            old_end: Length {
                bytes: (*edit).old_end_byte,
                extent: (*edit).old_end_point,
            },
            new_end: Length {
                bytes: (*edit).new_end_byte,
                extent: (*edit).new_end_point,
            },
        },
    };
    while stack.size != 0 {
        stack.size = stack.size.wrapping_sub(1);
        let mut entry: LocStackEntry = *stack.contents.offset(stack.size as isize);
        let mut edit_0: Edit = entry.edit;
        let mut is_noop: bool = edit_0.old_end.bytes == edit_0.start.bytes
            && edit_0.new_end.bytes == edit_0.start.bytes;
        let mut is_pure_insertion: bool = edit_0.old_end.bytes == edit_0.start.bytes;
        let mut size: Length = ts_subtree_size(*entry.tree);
        let mut padding: Length = ts_subtree_padding(*entry.tree);
        let mut lookahead_bytes: u32 = ts_subtree_lookahead_bytes(*entry.tree);
        let mut end_byte: u32 = padding
            .bytes
            .wrapping_add(size.bytes)
            .wrapping_add(lookahead_bytes);
        if edit_0.start.bytes > end_byte
            || is_noop as os::raw::c_int != 0 && edit_0.start.bytes == end_byte
        {
            continue;
        }
        // If the edit is entirely within the space before this subtree, then shift this
        // subtree over according to the edit without changing its size.
        if edit_0.old_end.bytes <= padding.bytes {
            padding = length_add(edit_0.new_end, length_sub(padding, edit_0.old_end))
        } else if edit_0.start.bytes < padding.bytes {
            size = length_sub(size, length_sub(edit_0.old_end, padding));
            padding = edit_0.new_end
        } else if edit_0.start.bytes == padding.bytes && is_pure_insertion as os::raw::c_int != 0 {
            padding = edit_0.new_end
        } else {
            // If the edit starts in the space before this subtree and extends into this subtree,
            // shrink the subtree's content to compensate for the change in the space before it.
            // If the edit is a pure insertion right at the start of the subtree,
            // shift the subtree over according to the insertion.
            // If the edit is within this subtree, resize the subtree to reflect the edit.
            let mut total_bytes: u32 = padding.bytes.wrapping_add(size.bytes);
            if edit_0.start.bytes < total_bytes
                || edit_0.start.bytes == total_bytes && is_pure_insertion as os::raw::c_int != 0
            {
                size = length_add(
                    length_sub(edit_0.new_end, padding),
                    length_sub(size, length_sub(edit_0.old_end, padding)),
                )
            }
        }
        let mut result: MutableSubtree = ts_subtree_make_mut(pool, *entry.tree);
        if result.data.is_inline() {
            if ts_subtree_can_inline(padding, size, lookahead_bytes) {
                result.data.padding_bytes = padding.bytes as u8;
                result.data.set_padding_rows(padding.extent.row as u8);
                result.data.padding_columns = padding.extent.column as u8;
                result.data.size_bytes = size.bytes as u8
            } else {
                let mut data: *mut SubtreeHeapData = ts_subtree_pool_allocate(pool);
                ::std::ptr::write_volatile(
                    &mut (*data).ref_count as *mut u32,
                    1 as os::raw::c_int as u32,
                );
                (*data).padding = padding;
                (*data).size = size;
                (*data).lookahead_bytes = lookahead_bytes;
                (*data).error_cost = 0 as os::raw::c_int as u32;
                (*data).child_count = 0 as os::raw::c_int as u32;
                (*data).symbol = result.data.symbol as TSSymbol;
                (*data).parse_state = result.data.parse_state;
                (*data).set_visible(result.data.visible());
                (*data).set_named(result.data.named());
                (*data).set_extra(result.data.extra());
                (*data).set_fragile_left(false);
                (*data).set_fragile_right(false);
                (*data).set_has_changes(false);
                (*data).set_has_external_tokens(false);
                (*data).set_is_missing(result.data.is_missing());
                (*data).set_is_keyword(result.data.is_keyword());
                result.ptr = data
            }
        } else {
            (*result.ptr).padding = padding;
            (*result.ptr).size = size
        }
        ts_subtree_set_has_changes(&mut result);
        *entry.tree = ts_subtree_from_mut(result);
        let mut child_left: Length = Length {
            bytes: 0,
            extent: TSPoint { row: 0, column: 0 },
        };
        let mut child_right: Length = length_zero();
        let mut i: u32 = 0 as os::raw::c_int as u32;
        let mut n: u32 = ts_subtree_child_count(*entry.tree);
        while i < n {
            let mut child: *mut Subtree = &mut *(*result.ptr)
                .c2rust_unnamed
                .c2rust_unnamed
                .children
                .offset(i as isize) as *mut Subtree;
            let mut child_size: Length = ts_subtree_total_size(*child);
            child_left = child_right;
            child_right = length_add(child_left, child_size);
            // If this child ends before the edit, it is not affected.
            if child_right
                .bytes
                .wrapping_add(ts_subtree_lookahead_bytes(*child))
                >= edit_0.start.bytes
            {
                // If this child starts after the edit, then we're done processing children.
                if child_left.bytes > edit_0.old_end.bytes
                    || child_left.bytes == edit_0.old_end.bytes
                        && child_size.bytes > 0 as os::raw::c_int as os::raw::c_uint
                        && i > 0 as os::raw::c_int as os::raw::c_uint
                {
                    break;
                }
                // Transform edit into the child's coordinate space.
                let mut child_edit = Edit {
                    start: length_sub(edit_0.start, child_left),
                    old_end: length_sub(edit_0.old_end, child_left),
                    new_end: length_sub(edit_0.new_end, child_left),
                };
                // Clamp child_edit to the child's bounds.
                if edit_0.start.bytes < child_left.bytes {
                    child_edit.start = length_zero()
                }
                if edit_0.old_end.bytes < child_left.bytes {
                    child_edit.old_end = length_zero()
                }
                if edit_0.new_end.bytes < child_left.bytes {
                    child_edit.new_end = length_zero()
                }
                if edit_0.old_end.bytes > child_right.bytes {
                    child_edit.old_end = child_size
                }
                // Interpret all inserted text as applying to the *first* child that touches the edit.
                // Subsequent children are only never have any text inserted into them; they are only
                // shrunk to compensate for the edit.
                if child_right.bytes > edit_0.start.bytes
                    || child_right.bytes == edit_0.start.bytes
                        && is_pure_insertion as os::raw::c_int != 0
                {
                    edit_0.new_end = edit_0.start
                } else {
                    // Children that occur before the edit are not reshaped by the edit.
                    child_edit.old_end = child_edit.start;
                    child_edit.new_end = child_edit.start
                }
                // Queue processing of this child's subtree.
                array__grow(
                    &mut stack as *mut StackEntryArray as *mut VoidArray,
                    1 as os::raw::c_int as usize,
                    ::std::mem::size_of::<LocStackEntry>(),
                );
                let fresh13 = stack.size;
                stack.size = stack.size.wrapping_add(1);
                *stack.contents.offset(fresh13 as isize) = LocStackEntry {
                    tree: child,
                    edit: child_edit,
                }
            }
            i = i.wrapping_add(1)
        }
    }
    array__delete(&mut stack as *mut StackEntryArray as *mut VoidArray);
    self_0
}
#[no_mangle]
pub(crate) unsafe extern "C" fn ts_subtree_last_external_token(mut tree: Subtree) -> Subtree {
    if !ts_subtree_has_external_tokens(tree) {
        return Subtree {
            ptr: std::ptr::null::<SubtreeHeapData>(),
        };
    }
    while (*tree.ptr).child_count > 0 as os::raw::c_int as os::raw::c_uint {
        let mut i: u32 = (*tree.ptr).child_count.wrapping_sub(1);
        while i.wrapping_add(1) > 0 as os::raw::c_int as os::raw::c_uint {
            let mut child: Subtree = *(*tree.ptr)
                .c2rust_unnamed
                .c2rust_unnamed
                .children
                .offset(i as isize);
            if ts_subtree_has_external_tokens(child) {
                tree = child;
                break;
            } else {
                i = i.wrapping_sub(1)
            }
        }
    }
    tree
}
unsafe extern "C" fn ts_subtree__write_char_to_string(
    mut s: *mut os::raw::c_char,
    mut n: usize,
    mut c: i32,
) -> usize {
    if c == -(1 as os::raw::c_int) {
        snwrite!(s, n, "INVALID").unwrap_or(std::usize::MAX)
    } else if c == '\u{0}' as i32 {
        snwrite!(s, n, "\'\\0\'").unwrap_or(std::usize::MAX)
    } else if c == '\n' as i32 {
        snwrite!(s, n, "\'\\n\'").unwrap_or(std::usize::MAX)
    } else if c == '\t' as i32 {
        snwrite!(s, n, "\'\\t\'").unwrap_or(std::usize::MAX)
    } else if c == '\r' as i32 {
        snwrite!(s, n, "\'\\r\'").unwrap_or(std::usize::MAX)
    } else if (0 as os::raw::c_int) < c
        && c < 128 as os::raw::c_int
        && ((c as u8).is_ascii_graphic() || c == ' ' as i32)
    {
        snwrite!(s, n, "\'{}\'", c as u8 as char).unwrap_or(std::usize::MAX)
    } else {
        snwrite!(s, n, "{}", c).unwrap_or(std::usize::MAX)
    }
}

unsafe extern "C" fn ts_subtree__write_dot_string<W>(f: &mut W, mut string: *const os::raw::c_char)
where
    W: Write,
{
    let mut c: *const os::raw::c_char = string;
    while *c != 0 {
        if *c as os::raw::c_int == '\"' as i32 {
            f.write_all(b"\\\"").unwrap();
        } else if *c as os::raw::c_int == '\n' as i32 {
            f.write_all(b"\\n").unwrap();
        } else {
            f.write_all(&[(*c).try_into().unwrap()]).unwrap();
        }
        c = c.offset(1)
    }
}
static mut ROOT_FIELD: *const os::raw::c_char =
    b"__ROOT__\x00" as *const u8 as *const os::raw::c_char;
unsafe extern "C" fn ts_subtree__write_to_string(
    mut self_0: Subtree,
    mut string: *mut os::raw::c_char,
    mut limit: usize,
    mut language: *const TSLanguage,
    mut include_all: bool,
    mut alias_symbol: TSSymbol,
    mut alias_is_named: bool,
    mut field_name: *const os::raw::c_char,
) -> usize {
    if self_0.ptr.is_null() {
        return snwrite!(string, limit as usize, "(NULL)").unwrap_or(std::usize::MAX);
    }
    let mut cursor: *mut os::raw::c_char = string;
    let mut writer: *mut *mut os::raw::c_char = if limit > 0 { &mut cursor } else { &mut string };
    let mut is_root: bool = field_name == ROOT_FIELD;
    let mut is_visible: bool = include_all as os::raw::c_int != 0
        || ts_subtree_missing(self_0) as os::raw::c_int != 0
        || (if alias_symbol as os::raw::c_int != 0 {
            alias_is_named as os::raw::c_int
        } else {
            (ts_subtree_visible(self_0) as os::raw::c_int != 0
                && ts_subtree_named(self_0) as os::raw::c_int != 0) as os::raw::c_int
        }) != 0;
    if is_visible {
        if !is_root {
            cursor = cursor.add(snwrite!(*writer, limit as usize, " ",).unwrap());
            if !field_name.is_null() {
                cursor = cursor.add(
                    snwrite!(
                        *writer,
                        limit as usize,
                        "{}: ",
                        CStr::from_ptr(field_name).to_string_lossy()
                    )
                    .unwrap(),
                )
            }
        }
        if ts_subtree_is_error(self_0) as os::raw::c_int != 0
            && ts_subtree_child_count(self_0) == 0 as os::raw::c_int as os::raw::c_uint
            && (*self_0.ptr).size.bytes > 0 as os::raw::c_int as os::raw::c_uint
        {
            cursor = cursor.add(snwrite!(*writer, limit as usize, "(UNEXPECTED ").unwrap());
            cursor = cursor.add(ts_subtree__write_char_to_string(
                *writer,
                limit,
                (*self_0.ptr).c2rust_unnamed.lookahead_char,
            ))
        } else {
            let mut symbol: TSSymbol = if alias_symbol as os::raw::c_int != 0 {
                alias_symbol as os::raw::c_int
            } else {
                ts_subtree_symbol(self_0) as os::raw::c_int
            } as TSSymbol;
            let mut symbol_name: *const os::raw::c_char = ts_language_symbol_name(language, symbol);
            if ts_subtree_missing(self_0) {
                cursor = cursor.add(snwrite!(*writer, limit as usize, "(MISSING ",).unwrap());
                if alias_is_named as os::raw::c_int != 0
                    || ts_subtree_named(self_0) as os::raw::c_int != 0
                {
                    cursor = cursor.add(
                        snwrite!(
                            *writer,
                            limit as usize,
                            "{}",
                            CStr::from_ptr(symbol_name).to_string_lossy(),
                        )
                        .unwrap(),
                    )
                } else {
                    cursor = cursor.add(
                        snwrite!(
                            *writer,
                            limit as usize,
                            "\"{}\"",
                            CStr::from_ptr(symbol_name).to_string_lossy(),
                        )
                        .unwrap(),
                    )
                }
            } else {
                cursor = cursor.add(
                    snwrite!(
                        *writer,
                        limit as usize,
                        "({}",
                        CStr::from_ptr(symbol_name).to_string_lossy(),
                    )
                    .unwrap(),
                )
            }
        }
    } else if is_root {
        let mut symbol_0: TSSymbol = ts_subtree_symbol(self_0);
        let mut symbol_name_0: *const os::raw::c_char = ts_language_symbol_name(language, symbol_0);
        cursor = cursor.add(
            snwrite!(
                *writer,
                limit as usize,
                "(\"{}\")",
                CStr::from_ptr(symbol_name_0).to_string_lossy(),
            )
            .unwrap(),
        )
    }
    if ts_subtree_child_count(self_0) != 0 {
        let mut alias_sequence: *const TSSymbol = ts_language_alias_sequence(
            language,
            (*self_0.ptr).c2rust_unnamed.c2rust_unnamed.production_id as u32,
        );
        let mut field_map: *const TSFieldMapEntry = std::ptr::null::<TSFieldMapEntry>();
        let mut field_map_end: *const TSFieldMapEntry = std::ptr::null::<TSFieldMapEntry>();
        ts_language_field_map(
            language,
            (*self_0.ptr).c2rust_unnamed.c2rust_unnamed.production_id as u32,
            &mut field_map,
            &mut field_map_end,
        );
        let mut structural_child_index: u32 = 0 as os::raw::c_int as u32;
        let mut i: u32 = 0 as os::raw::c_int as u32;
        while i < (*self_0.ptr).child_count {
            let mut child: Subtree = *(*self_0.ptr)
                .c2rust_unnamed
                .c2rust_unnamed
                .children
                .offset(i as isize);
            if ts_subtree_extra(child) {
                cursor = cursor.add(ts_subtree__write_to_string(
                    child,
                    *writer,
                    limit,
                    language,
                    include_all,
                    0 as os::raw::c_int as TSSymbol,
                    false,
                    ptr::null(),
                ))
            } else {
                let mut alias_symbol_0: TSSymbol = if !alias_sequence.is_null() {
                    *alias_sequence.offset(structural_child_index as isize) as os::raw::c_int
                } else {
                    0 as os::raw::c_int
                } as TSSymbol;
                let mut alias_is_named_0: bool = if alias_symbol_0 as os::raw::c_int != 0 {
                    ts_language_symbol_metadata(language, alias_symbol_0).named() as os::raw::c_int
                } else {
                    0 as os::raw::c_int
                } != 0;
                let mut child_field_name: *const os::raw::c_char =
                    if is_visible as os::raw::c_int != 0 {
                        ptr::null()
                    } else {
                        field_name
                    };
                let mut i_0: *const TSFieldMapEntry = field_map;
                while i_0 < field_map_end {
                    if !(*i_0).inherited
                        && (*i_0).child_index as os::raw::c_uint == structural_child_index
                    {
                        child_field_name =
                            *(*language).field_names.offset((*i_0).field_id as isize);
                        break;
                    } else {
                        i_0 = i_0.offset(1)
                    }
                }
                cursor = cursor.add(ts_subtree__write_to_string(
                    child,
                    *writer,
                    limit,
                    language,
                    include_all,
                    alias_symbol_0,
                    alias_is_named_0,
                    child_field_name,
                ));
                structural_child_index = structural_child_index.wrapping_add(1)
            }
            i = i.wrapping_add(1)
        }
    }
    if is_visible {
        cursor = cursor.add(snwrite!(*writer, limit as usize, ")",).unwrap())
    }
    cursor.wrapping_offset_from_(string) as os::raw::c_long as usize
}
#[no_mangle]
pub(crate) unsafe extern "C" fn ts_subtree_string(
    mut self_0: Subtree,
    mut language: *const TSLanguage,
    mut include_all: bool,
) -> *mut os::raw::c_char {
    let mut scratch_string: [os::raw::c_char; 1] = [0; 1];
    let mut size: usize = ts_subtree__write_to_string(
        self_0,
        scratch_string.as_mut_ptr(),
        0 as os::raw::c_int as usize,
        language,
        include_all,
        0 as os::raw::c_int as TSSymbol,
        false,
        ROOT_FIELD,
    )
    .wrapping_add(1);
    let mut result = alloc::alloc(
        Layout::from_size_align(
            size_of::<os::raw::c_char>() * size as usize,
            align_of::<os::raw::c_char>(),
        )
        .unwrap(),
    ) as *mut os::raw::c_char;
    ts_subtree__write_to_string(
        self_0,
        result,
        size,
        language,
        include_all,
        0 as os::raw::c_int as TSSymbol,
        false,
        ROOT_FIELD,
    );
    result
}
pub(crate) unsafe fn ts_subtree__print_dot_graph<W>(
    mut self_0: *const Subtree,
    mut start_offset: u32,
    mut language: *const TSLanguage,
    mut alias_symbol: TSSymbol,
    mut f: &mut W,
) where
    W: Write,
{
    let mut subtree_symbol: TSSymbol = ts_subtree_symbol(*self_0);
    let mut symbol: TSSymbol = if alias_symbol as os::raw::c_int != 0 {
        alias_symbol as os::raw::c_int
    } else {
        subtree_symbol as os::raw::c_int
    } as TSSymbol;
    let mut end_offset: u32 = start_offset.wrapping_add(ts_subtree_total_bytes(*self_0));
    write!(f, "tree_{:x} [label=\"", self_0 as usize).unwrap();
    ts_subtree__write_dot_string(f, ts_language_symbol_name(language, symbol));
    write!(f, "\"").unwrap();
    if ts_subtree_child_count(*self_0) == 0 as os::raw::c_int as os::raw::c_uint {
        write!(f, ", shape=plaintext").unwrap();
    }
    if ts_subtree_extra(*self_0) {
        write!(f, ", fontcolor=gray").unwrap();
    }
    write!(f,
            ", tooltip=\"range: {} - {}\nstate: {}\nerror-cost: {}\nhas-changes: {}\nrepeat-depth: {}\nlookahead-bytes: {}"
                , start_offset, end_offset,
            ts_subtree_parse_state(*self_0) as os::raw::c_int,
            ts_subtree_error_cost(*self_0),
            ts_subtree_has_changes(*self_0) as os::raw::c_int,
            ts_subtree_repeat_depth(*self_0),
            ts_subtree_lookahead_bytes(*self_0)).unwrap();
    if ts_subtree_is_error(*self_0) as os::raw::c_int != 0
        && ts_subtree_child_count(*self_0) == 0 as os::raw::c_int as os::raw::c_uint
    {
        write!(
            f,
            "\ncharacter: \'{}\'",
            (*(*self_0).ptr).c2rust_unnamed.lookahead_char as u8 as char,
        )
        .unwrap();
    }
    writeln!(f, "\"]").unwrap();
    let mut child_start_offset: u32 = start_offset;
    let mut child_info_offset: u32 = ((*language).max_alias_sequence_length as os::raw::c_int
        * ts_subtree_production_id(*self_0) as os::raw::c_int)
        as u32;
    let mut i: u32 = 0 as os::raw::c_int as u32;
    let mut n: u32 = ts_subtree_child_count(*self_0);
    while i < n {
        let mut child: *const Subtree = &mut *(*(*self_0).ptr)
            .c2rust_unnamed
            .c2rust_unnamed
            .children
            .offset(i as isize) as *mut Subtree;
        let mut alias_symbol_0: TSSymbol = 0 as os::raw::c_int as TSSymbol;
        if !ts_subtree_extra(*child) && child_info_offset != 0 {
            alias_symbol_0 = *(*language)
                .alias_sequences
                .offset(child_info_offset as isize);
            child_info_offset = child_info_offset.wrapping_add(1)
        }
        ts_subtree__print_dot_graph(child, child_start_offset, language, alias_symbol_0, f);
        writeln!(
            f,
            "tree_{:x} -> tree_{:x} [tooltip={}]",
            self_0 as usize, child as usize, i,
        )
        .unwrap();
        child_start_offset = (child_start_offset as os::raw::c_uint)
            .wrapping_add(ts_subtree_total_bytes(*child)) as u32
            as u32;
        i = i.wrapping_add(1)
    }
}
pub(crate) unsafe fn ts_subtree_print_dot_graph<W>(
    mut self_0: Subtree,
    mut language: *const TSLanguage,
    mut f: &mut W,
) where
    W: Write,
{
    writeln!(f, "digraph tree {{").unwrap();
    writeln!(f, "edge [arrowhead=none]").unwrap();
    ts_subtree__print_dot_graph(
        &self_0,
        0 as os::raw::c_int as u32,
        language,
        0 as os::raw::c_int as TSSymbol,
        f,
    );
    writeln!(f, "}}").unwrap();
}
#[no_mangle]
pub(crate) unsafe extern "C" fn ts_subtree_external_scanner_state_eq(
    mut self_0: Subtree,
    mut other: Subtree,
) -> bool {
    let mut state1: *const ExternalScannerState = &empty_state;
    let mut state2: *const ExternalScannerState = &empty_state;
    if !self_0.ptr.is_null()
        && ts_subtree_has_external_tokens(self_0) as os::raw::c_int != 0
        && (*self_0.ptr).child_count == 0
    {
        state1 = &(*self_0.ptr).c2rust_unnamed.external_scanner_state
    }
    if !other.ptr.is_null()
        && ts_subtree_has_external_tokens(other) as os::raw::c_int != 0
        && (*other.ptr).child_count == 0
    {
        state2 = &(*other.ptr).c2rust_unnamed.external_scanner_state
    }
    ts_external_scanner_state_eq(state1, state2)
}
