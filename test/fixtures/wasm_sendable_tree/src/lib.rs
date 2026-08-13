use std::{
    alloc::{Layout, alloc, alloc_zeroed, dealloc, realloc},
    ffi::c_void,
    slice,
    str,
    sync::atomic::{AtomicU32, Ordering},
};

use tree_sitter::{
    InputEdit, Language, LanguageError, Parser, Point, Tree,
    ffi::TSLanguage,
    set_allocator,
};

const INITIAL_SOURCE: &str = r#"{"value": 1}"#;
const UPDATED_SOURCE: &str = r#"{"value": [1, 2, 3], "nested": {"enabled": true}}"#;
const EDIT_START_BYTE: usize = 10;
const EDIT_OLD_END_BYTE: usize = 11;
const EDIT_NEW_END_BYTE: usize = 48;
const C_ALIGNMENT: usize = 16;

static TREE_SLOT: AtomicU32 = AtomicU32::new(0);

#[repr(C, align(16))]
struct AllocationHeader {
    payload_size: usize,
}

fn send<T: Send>(value: T) -> T {
    value
}

fn allocation_layout(payload_size: usize) -> Option<Layout> {
    Layout::from_size_align(size_of::<AllocationHeader>().checked_add(payload_size)?, C_ALIGNMENT)
        .ok()
}

unsafe extern "C" fn rust_malloc(size: usize) -> *mut c_void {
    let Some(layout) = allocation_layout(size) else {
        return std::ptr::null_mut();
    };
    let allocation = unsafe { alloc(layout) };
    if allocation.is_null() {
        return std::ptr::null_mut();
    }
    unsafe {
        allocation
            .cast::<AllocationHeader>()
            .write(AllocationHeader { payload_size: size });
    }
    unsafe { allocation.add(size_of::<AllocationHeader>()).cast() }
}

unsafe extern "C" fn rust_calloc(count: usize, size: usize) -> *mut c_void {
    let Some(payload_size) = count.checked_mul(size) else {
        return std::ptr::null_mut();
    };
    let Some(layout) = allocation_layout(payload_size) else {
        return std::ptr::null_mut();
    };
    let allocation = unsafe { alloc_zeroed(layout) };
    if allocation.is_null() {
        return std::ptr::null_mut();
    }
    unsafe {
        allocation
            .cast::<AllocationHeader>()
            .write(AllocationHeader { payload_size });
    }
    unsafe { allocation.add(size_of::<AllocationHeader>()).cast() }
}

unsafe fn allocation_header(ptr: *mut c_void) -> *mut AllocationHeader {
    unsafe {
        ptr.cast::<u8>()
            .sub(size_of::<AllocationHeader>())
            .cast()
    }
}

unsafe extern "C" fn rust_realloc(ptr: *mut c_void, size: usize) -> *mut c_void {
    if ptr.is_null() {
        return unsafe { rust_malloc(size) };
    }
    if size == 0 {
        unsafe { rust_free(ptr) };
        return std::ptr::null_mut();
    }

    let header = unsafe { allocation_header(ptr) };
    let old_size = unsafe { (*header).payload_size };
    let old_layout = allocation_layout(old_size).unwrap();
    let Some(new_layout) = allocation_layout(size) else {
        return std::ptr::null_mut();
    };
    let allocation = unsafe { realloc(header.cast(), old_layout, new_layout.size()) };
    if allocation.is_null() {
        return std::ptr::null_mut();
    }
    unsafe {
        allocation
            .cast::<AllocationHeader>()
            .write(AllocationHeader { payload_size: size });
    }
    unsafe { allocation.add(size_of::<AllocationHeader>()).cast() }
}

unsafe extern "C" fn rust_free(ptr: *mut c_void) {
    if ptr.is_null() {
        return;
    }
    let header = unsafe { allocation_header(ptr) };
    let layout = allocation_layout(unsafe { (*header).payload_size }).unwrap();
    unsafe { dealloc(header.cast(), layout) };
}

fn publish(tree: Tree) -> Result<(), Tree> {
    let tree_address = send(tree).into_raw() as u32;
    match TREE_SLOT.compare_exchange(0, tree_address, Ordering::Release, Ordering::Relaxed) {
        Ok(_) => Ok(()),
        Err(_) => Err(unsafe { Tree::from_raw(tree_address as *mut _) }),
    }
}

fn take() -> Option<Tree> {
    let tree_address = TREE_SLOT.swap(0, Ordering::Acquire);
    (tree_address != 0).then(|| unsafe { Tree::from_raw(tree_address as *mut _) })
}

/// Install Rust's atomics-aware allocator for Tree-sitter's C core.
///
/// # Safety
///
/// This must be called before invoking any other export in each instance.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn initialize() {
    unsafe {
        set_allocator(
            Some(rust_malloc),
            Some(rust_calloc),
            Some(rust_realloc),
            Some(rust_free),
        );
    }
}

/// Allocate shared memory for the separately compiled language module.
///
/// # Safety
///
/// `alignment` must be a nonzero power of two.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn allocate_language_memory(size: u32, alignment: u32) -> u32 {
    let layout = Layout::from_size_align(size as usize, alignment as usize).unwrap();
    unsafe { alloc_zeroed(layout) as u32 }
}

/// Allocate a source buffer that JavaScript can fill.
///
/// # Safety
///
/// The returned buffer must be passed exactly once to `reparse_and_publish`.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn allocate_source(size: u32) -> u32 {
    unsafe { rust_malloc(size as usize) as u32 }
}

/// Parse the initial source and publish its tree into shared memory.
///
/// # Safety
///
/// `language_address` must point to a valid `TSLanguage` in this instance's
/// shared WebAssembly memory.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn parse_and_publish(language_address: u32) -> u32 {
    let language = unsafe { Language::from_raw(language_address as *const TSLanguage) };
    let mut parser = Parser::new();
    if parser.set_language(&language).is_err() {
        return 1;
    }

    let Some(tree) = parser.parse(INITIAL_SOURCE, None) else {
        return 2;
    };
    if tree.root_node().kind() != "document" || tree.language().is_parseable() {
        return 3;
    }
    if publish(tree).is_err() {
        return 4;
    }
    0
}

/// Take the initial tree, edit it on the UI thread, and publish it back.
///
/// # Safety
///
/// The shared tree slot must contain the sole owned handle for a valid tree.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn edit_and_publish() -> u32 {
    let Some(mut tree) = take() else {
        return 1;
    };
    if tree.root_node().kind() != "document" || tree.language().is_parseable() {
        return 2;
    }

    tree.edit(&InputEdit {
        start_byte: EDIT_START_BYTE,
        old_end_byte: EDIT_OLD_END_BYTE,
        new_end_byte: EDIT_NEW_END_BYTE,
        start_position: Point::new(0, EDIT_START_BYTE),
        old_end_position: Point::new(0, EDIT_OLD_END_BYTE),
        new_end_position: Point::new(0, EDIT_NEW_END_BYTE),
    });
    if tree.root_node().end_byte() != UPDATED_SOURCE.len() || !tree.root_node().has_changes() {
        return 3;
    }
    if publish(tree).is_err() {
        return 4;
    }
    0
}

/// Take the edited tree, incrementally reparse source, and publish the new tree.
///
/// # Safety
///
/// `language_address` must point to a valid language. `source_address` must
/// refer to `source_length` bytes returned by `allocate_source`. This function
/// consumes both that allocation and the tree in the shared slot.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn reparse_and_publish(
    language_address: u32,
    source_address: u32,
    source_length: u32,
) -> u32 {
    let source_ptr = source_address as *mut c_void;
    let source_bytes =
        unsafe { slice::from_raw_parts(source_address as *const u8, source_length as usize) };
    let Ok(source) = str::from_utf8(source_bytes) else {
        unsafe { rust_free(source_ptr) };
        return 1;
    };
    if source != UPDATED_SOURCE {
        unsafe { rust_free(source_ptr) };
        return 2;
    }

    let language = unsafe { Language::from_raw(language_address as *const TSLanguage) };
    let Some(tree) = take() else {
        unsafe { rust_free(source_ptr) };
        return 3;
    };
    let tree_language = Language::clone(&tree.language());
    if Parser::new().set_language(&tree_language) != Err(LanguageError::NotParseable) {
        unsafe { rust_free(source_ptr) };
        return 4;
    }
    drop(tree_language);

    let mut parser = Parser::new();
    if parser.set_language(&language).is_err() {
        unsafe { rust_free(source_ptr) };
        return 5;
    }
    let new_tree = parser.parse(source, Some(&tree));
    unsafe { rust_free(source_ptr) };
    let Some(new_tree) = new_tree else {
        return 6;
    };
    drop(tree);

    if publish(new_tree).is_err() {
        return 7;
    }
    0
}

/// Inspect the materially reshaped tree on the UI thread and publish it back.
///
/// # Safety
///
/// The shared tree slot must contain the sole owned handle for the reparsed
/// tree.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn inspect_new_tree_and_publish() -> u32 {
    let Some(tree) = take() else {
        return 1;
    };
    let root = tree.root_node();
    let Some(object) = root.named_child(0) else {
        return 2;
    };
    let Some(first_pair) = object.named_child(0) else {
        return 3;
    };
    let Some(second_pair) = object.named_child(1) else {
        return 4;
    };
    let Some(first_value) = first_pair.child_by_field_name("value") else {
        return 5;
    };
    let Some(second_value) = second_pair.child_by_field_name("value") else {
        return 6;
    };
    if root.kind() != "document"
        || root.has_error()
        || object.kind() != "object"
        || object.named_child_count() != 2
        || first_value.kind() != "array"
        || first_value.named_child_count() != 3
        || second_value.kind() != "object"
        || tree.language().is_parseable()
    {
        return 7;
    }
    if publish(tree).is_err() {
        return 8;
    }
    0
}

/// Take and delete the final tree on the parsing worker.
///
/// # Safety
///
/// The shared tree slot must contain the sole owned handle for the final tree.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn delete_tree() -> u32 {
    let Some(tree) = take() else {
        return 1;
    };
    drop(tree);
    0
}
