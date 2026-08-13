use std::{
    alloc::{GlobalAlloc, Layout},
    cell::UnsafeCell,
    ffi::c_void,
    ptr,
    slice,
    str,
    sync::atomic::{AtomicBool, AtomicU32, Ordering},
};

use dlmalloc::Dlmalloc;
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
const C_ALIGNMENT: usize = 2 * size_of::<usize>();

static TREE_SLOT: AtomicU32 = AtomicU32::new(0);

struct SharedDlmalloc {
    locked: AtomicBool,
    allocator: UnsafeCell<Dlmalloc>,
}

unsafe impl Sync for SharedDlmalloc {}

impl SharedDlmalloc {
    const fn new() -> Self {
        Self {
            locked: AtomicBool::new(false),
            allocator: UnsafeCell::new(Dlmalloc::new()),
        }
    }

    fn with_lock<T>(&self, operation: impl FnOnce(&mut Dlmalloc) -> T) -> T {
        while self.locked.swap(true, Ordering::Acquire) {
            std::hint::spin_loop();
        }

        struct LockGuard<'a>(&'a AtomicBool);

        impl Drop for LockGuard<'_> {
            fn drop(&mut self) {
                self.0.store(false, Ordering::Release);
            }
        }

        let _guard = LockGuard(&self.locked);
        operation(unsafe { &mut *self.allocator.get() })
    }
}

unsafe impl GlobalAlloc for SharedDlmalloc {
    unsafe fn alloc(&self, layout: Layout) -> *mut u8 {
        self.with_lock(|allocator| unsafe { allocator.malloc(layout.size(), layout.align()) })
    }

    unsafe fn alloc_zeroed(&self, layout: Layout) -> *mut u8 {
        self.with_lock(|allocator| unsafe { allocator.calloc(layout.size(), layout.align()) })
    }

    unsafe fn dealloc(&self, ptr: *mut u8, layout: Layout) {
        self.with_lock(|allocator| unsafe {
            allocator.free(ptr, layout.size(), layout.align());
        });
    }

    unsafe fn realloc(&self, ptr: *mut u8, layout: Layout, new_size: usize) -> *mut u8 {
        self.with_lock(|allocator| unsafe {
            allocator.realloc(ptr, layout.size(), layout.align(), new_size)
        })
    }
}

#[global_allocator]
static ALLOCATOR: SharedDlmalloc = SharedDlmalloc::new();

fn send<T: Send>(value: T) -> T {
    value
}

unsafe extern "C" fn c_malloc(size: usize) -> *mut c_void {
    ALLOCATOR.with_lock(|allocator| unsafe { allocator.c_malloc(size).cast() })
}

unsafe extern "C" fn c_calloc(count: usize, size: usize) -> *mut c_void {
    let Some(payload_size) = count.checked_mul(size) else {
        return ptr::null_mut();
    };
    ALLOCATOR.with_lock(|allocator| unsafe {
        allocator.calloc(payload_size, C_ALIGNMENT).cast()
    })
}

unsafe extern "C" fn c_realloc(ptr: *mut c_void, size: usize) -> *mut c_void {
    ALLOCATOR.with_lock(|allocator| unsafe { allocator.c_realloc(ptr.cast(), size).cast() })
}

unsafe extern "C" fn c_free(ptr: *mut c_void) {
    ALLOCATOR.with_lock(|allocator| unsafe {
        allocator.c_free(ptr.cast());
    });
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
            Some(c_malloc),
            Some(c_calloc),
            Some(c_realloc),
            Some(c_free),
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
    unsafe { ALLOCATOR.alloc_zeroed(layout) as u32 }
}

/// Allocate a source buffer that JavaScript can fill.
///
/// # Safety
///
/// The returned buffer must be passed exactly once to `reparse_and_publish`.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn allocate_source(size: u32) -> u32 {
    unsafe { c_malloc(size as usize) as u32 }
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
        unsafe { c_free(source_ptr) };
        return 1;
    };
    if source != UPDATED_SOURCE {
        unsafe { c_free(source_ptr) };
        return 2;
    }

    let language = unsafe { Language::from_raw(language_address as *const TSLanguage) };
    let Some(tree) = take() else {
        unsafe { c_free(source_ptr) };
        return 3;
    };
    let tree_language = Language::clone(&tree.language());
    if Parser::new().set_language(&tree_language) != Err(LanguageError::NotParseable) {
        unsafe { c_free(source_ptr) };
        return 4;
    }
    drop(tree_language);

    let mut parser = Parser::new();
    if parser.set_language(&language).is_err() {
        unsafe { c_free(source_ptr) };
        return 5;
    }
    let new_tree = parser.parse(source, Some(&tree));
    unsafe { c_free(source_ptr) };
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
