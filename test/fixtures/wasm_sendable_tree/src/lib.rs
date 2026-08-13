mod allocator;

use std::{
    alloc::Layout,
    slice, str,
    sync::atomic::{AtomicU32, Ordering},
};

use tree_sitter::{
    InputEdit, Language, LanguageError, Parser, Point, Tree, ffi::TSLanguage,
};

const UPDATED_SOURCE: &str = r#"{"value": [1, 2, 3], "nested": {"enabled": true}}"#;
const EDIT_START_BYTE: usize = 10;
const EDIT_OLD_END_BYTE: usize = 11;
const EDIT_NEW_END_BYTE: usize = 48;

static TREE_SLOT: AtomicU32 = AtomicU32::new(0);

fn send<T: Send>(value: T) -> T {
    value
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

fn parse(
    language_address: u32,
    source_address: u32,
    source_length: u32,
    has_old_tree: bool,
) -> u32 {
    let source_bytes =
        unsafe { slice::from_raw_parts(source_address as *const u8, source_length as usize) };
    let Ok(source) = str::from_utf8(source_bytes) else {
        return 1;
    };

    let language = unsafe { Language::from_raw(language_address as *const TSLanguage) };
    let old_tree = if has_old_tree {
        let Some(tree) = take() else {
            return 2;
        };
        if Parser::new().set_language(&tree.language()) != Err(LanguageError::NotParseable) {
            return 3;
        }
        Some(tree)
    } else {
        None
    };

    let mut parser = Parser::new();
    if parser.set_language(&language).is_err() {
        return 4;
    }
    let Some(tree) = parser.parse(source, old_tree.as_ref()) else {
        return 5;
    };
    if publish(tree).is_err() {
        return 6;
    }
    0
}

/// Install the shared allocator for Tree-sitter's C core.
///
/// # Safety
///
/// This must be called before invoking any other export in each instance.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn initialize() {
    allocator::initialize();
}

/// Allocate shared memory for the separately compiled language module.
///
/// # Safety
///
/// `alignment` must be a nonzero power of two.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn allocate_language_memory(size: u32, alignment: u32) -> u32 {
    let layout = Layout::from_size_align(size as usize, alignment as usize).unwrap();
    unsafe { allocator::allocate_zeroed(layout) as u32 }
}

/// Allocate a source buffer that JavaScript can fill.
///
/// # Safety
///
/// The returned buffer must be passed exactly once to `parse_and_publish`.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn allocate_source(size: u32) -> u32 {
    unsafe { allocator::allocate(size as usize) as u32 }
}

/// Parse source as JSON, optionally using the tree in the shared slot.
///
/// # Safety
///
/// `language_address` must point to a valid language. `source_address` must
/// refer to `source_length` bytes returned by `allocate_source`. This function
/// consumes the source allocation and, when `has_old_tree` is nonzero, the tree
/// in the shared slot.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn parse_and_publish(
    language_address: u32,
    source_address: u32,
    source_length: u32,
    has_old_tree: u32,
) -> u32 {
    let result = parse(
        language_address,
        source_address,
        source_length,
        has_old_tree != 0,
    );
    unsafe { allocator::deallocate(source_address as *mut u8) };
    result
}

/// Inspect the initial tree on the UI thread.
///
/// # Safety
///
/// The shared tree slot must contain the sole owned handle for the initial tree.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn inspect_initial_tree() -> u32 {
    let Some(tree) = take() else {
        return 1;
    };
    let root = tree.root_node();
    let Some(object) = root.named_child(0) else {
        return 2;
    };
    let Some(pair) = object.named_child(0) else {
        return 3;
    };
    let Some(value) = pair.child_by_field_name("value") else {
        return 4;
    };
    if root.kind() != "document"
        || root.has_error()
        || object.kind() != "object"
        || object.named_child_count() != 1
        || value.kind() != "number"
        || tree.language().is_parseable()
    {
        return 5;
    }
    if publish(tree).is_err() {
        return 6;
    }
    0
}

/// Edit the initial tree on the UI thread.
///
/// # Safety
///
/// The shared tree slot must contain the sole owned handle for the initial tree.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn edit_tree() -> u32 {
    let Some(mut tree) = take() else {
        return 1;
    };
    tree.edit(&InputEdit {
        start_byte: EDIT_START_BYTE,
        old_end_byte: EDIT_OLD_END_BYTE,
        new_end_byte: EDIT_NEW_END_BYTE,
        start_position: Point::new(0, EDIT_START_BYTE),
        old_end_position: Point::new(0, EDIT_OLD_END_BYTE),
        new_end_position: Point::new(0, EDIT_NEW_END_BYTE),
    });
    if tree.root_node().end_byte() != UPDATED_SOURCE.len() || !tree.root_node().has_changes() {
        return 2;
    }
    if publish(tree).is_err() {
        return 3;
    }
    0
}

/// Inspect and delete the reparsed tree on the UI thread.
///
/// # Safety
///
/// The shared tree slot must contain the sole owned handle for the reparsed tree.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn inspect_new_tree() -> u32 {
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
    0
}
