use std::alloc::{Layout, alloc_zeroed};

use tree_sitter::{Language, LanguageError, Parser, Tree, ffi::TSLanguage};

fn send<T: Send>(value: T) -> T {
    value
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

/// Parse source code and return an owned `Tree` handle.
///
/// # Safety
///
/// `language_address` must point to a valid `TSLanguage` in this instance's
/// shared WebAssembly memory.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn parse(language_address: u32) -> u32 {
    let language = unsafe { Language::from_raw(language_address as *const TSLanguage) };
    if !language.is_parseable() {
        return 0;
    }

    let mut parser = Parser::new();
    if parser.set_language(&language).is_err() {
        return 0;
    }

    let Some(tree) = parser.parse(r#"{"value": 1}"#, None) else {
        return 0;
    };
    if tree.root_node().kind() != "document" || tree.language().is_parseable() {
        return 0;
    }
    let tree_copy = tree.clone();
    if tree_copy.root_node().kind() != "document" {
        return 0;
    }
    drop(tree_copy);

    send(tree).into_raw() as u32
}

/// Inspect an owned `Tree` and return its ownership to the caller.
///
/// # Safety
///
/// `tree_address` must be the sole owned handle for a valid `TSTree` in this
/// instance's shared WebAssembly memory. The caller must not use it until this
/// function returns it.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn inspect(tree_address: u32) -> u32 {
    let tree = unsafe { Tree::from_raw(tree_address as *mut _) };
    let tree = send(tree);
    if tree.root_node().kind() != "document" || tree.language().is_parseable() {
        return 0;
    }
    send(tree).into_raw() as u32
}

/// Reuse and delete a transferred `Tree`.
///
/// # Safety
///
/// `language_address` must point to a valid `TSLanguage`. `tree_address` must
/// be the sole owned handle for a valid `TSTree`; this function consumes it.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn reuse_and_delete(language_address: u32, tree_address: u32) -> u32 {
    let language = unsafe { Language::from_raw(language_address as *const TSLanguage) };
    let tree = unsafe { Tree::from_raw(tree_address as *mut _) };

    let tree_language = Language::clone(&tree.language());
    if Parser::new().set_language(&tree_language) != Err(LanguageError::NotParseable) {
        return 1;
    }
    drop(tree_language);

    let mut parser = Parser::new();
    if parser.set_language(&language).is_err() {
        return 2;
    }

    let Some(new_tree) = parser.parse(r#"{"value": 2}"#, Some(&tree)) else {
        return 3;
    };
    if new_tree.root_node().kind() != "document" || new_tree.language().is_parseable() {
        return 4;
    }

    drop(new_tree);
    drop(tree);
    0
}
