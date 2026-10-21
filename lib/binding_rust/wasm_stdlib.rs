//! Provides Tree-sitter's C standard-library subset in Rust Wasm applications.
//!
//! Allocation uses the application's Rust global allocator, while Tree-sitter's
//! vendored C functions are compiled into the same Wasm module. Side-module
//! loaders can use the function-table addresses exposed here to link scanners.

use alloc::alloc::{Layout, alloc, alloc_zeroed, dealloc, realloc as rust_realloc};
#[cfg(feature = "js-loader")]
use core::ffi::{c_char, c_int};
use core::{ffi::c_void, mem, ptr};

#[cfg(feature = "js-loader")]
pub(super) mod memory_import;

#[cfg(feature = "js-loader")]
unsafe extern "C" {
    fn iswalnum(character: u32) -> c_int;
    fn iswalpha(character: u32) -> c_int;
    fn iswblank(character: u32) -> c_int;
    fn iswdigit(character: u32) -> c_int;
    fn iswlower(character: u32) -> c_int;
    fn iswpunct(character: u32) -> c_int;
    fn iswspace(character: u32) -> c_int;
    fn iswupper(character: u32) -> c_int;
    fn iswxdigit(character: u32) -> c_int;

    fn memchr(source: *const c_void, character: c_int, count: usize) -> *mut c_void;
    fn memcmp(left: *const c_void, right: *const c_void, count: usize) -> c_int;
    fn memcpy(destination: *mut c_void, source: *const c_void, count: usize) -> *mut c_void;
    fn memmove(destination: *mut c_void, source: *const c_void, count: usize) -> *mut c_void;
    fn memset(destination: *mut c_void, character: c_int, count: usize) -> *mut c_void;

    fn strcmp(left: *const c_char, right: *const c_char) -> c_int;
    fn strlen(source: *const c_char) -> usize;
    fn strncat(destination: *mut c_char, source: *const c_char, count: usize) -> *mut c_char;
    fn strncmp(left: *const c_char, right: *const c_char, count: usize) -> c_int;
    fn strncpy(destination: *mut c_char, source: *const c_char, count: usize) -> *mut c_char;

    fn towlower(character: u32) -> u32;
    fn towupper(character: u32) -> u32;
}

// Tree-sitter and its supported external scanners only allocate values whose
// alignment is at most eight bytes; this is not a general-purpose C allocator.
const C_ALIGNMENT: usize = 8;

#[repr(C, align(8))]
struct Header {
    payload_size: usize,
}

const HEADER_SIZE: usize = mem::size_of::<Header>();

const _: () = assert!(HEADER_SIZE == C_ALIGNMENT);

fn layout(payload_size: usize) -> Option<Layout> {
    let allocation_size = HEADER_SIZE.checked_add(payload_size)?;
    Layout::from_size_align(allocation_size, C_ALIGNMENT).ok()
}

unsafe fn header_from_payload(payload: *mut c_void) -> *mut Header {
    unsafe { payload.cast::<u8>().sub(HEADER_SIZE).cast() }
}

#[unsafe(no_mangle)]
unsafe extern "C" fn malloc(size: usize) -> *mut c_void {
    let Some(layout) = layout(size).filter(|_| size != 0) else {
        return ptr::null_mut();
    };
    let header = unsafe { alloc(layout).cast::<Header>() };
    if header.is_null() {
        return ptr::null_mut();
    }
    unsafe {
        header.write(Header { payload_size: size });
        header.add(1).cast()
    }
}

#[unsafe(no_mangle)]
unsafe extern "C" fn calloc(count: usize, size: usize) -> *mut c_void {
    let Some(payload_size) = count.checked_mul(size) else {
        return ptr::null_mut();
    };
    let Some(layout) = layout(payload_size).filter(|_| payload_size != 0) else {
        return ptr::null_mut();
    };
    let header = unsafe { alloc_zeroed(layout).cast::<Header>() };
    if header.is_null() {
        return ptr::null_mut();
    }
    unsafe {
        header.write(Header { payload_size });
        header.add(1).cast()
    }
}

#[unsafe(no_mangle)]
unsafe extern "C" fn realloc(payload: *mut c_void, new_size: usize) -> *mut c_void {
    if payload.is_null() {
        return unsafe { malloc(new_size) };
    }
    if new_size == 0 {
        unsafe { free(payload) };
        return ptr::null_mut();
    }

    let old_header = unsafe { header_from_payload(payload) };
    let old_size = unsafe { (*old_header).payload_size };
    let Some(old_layout) = layout(old_size) else {
        return ptr::null_mut();
    };
    let Some(new_layout) = layout(new_size) else {
        return ptr::null_mut();
    };
    let new_header =
        unsafe { rust_realloc(old_header.cast(), old_layout, new_layout.size()).cast::<Header>() };
    if new_header.is_null() {
        return ptr::null_mut();
    }
    unsafe {
        (*new_header).payload_size = new_size;
        new_header.add(1).cast()
    }
}

#[unsafe(no_mangle)]
unsafe extern "C" fn free(payload: *mut c_void) {
    if payload.is_null() {
        return;
    }
    let header = unsafe { header_from_payload(payload) };
    let payload_size = unsafe { (*header).payload_size };
    let allocation_layout = layout(payload_size).unwrap();
    unsafe { dealloc(header.cast(), allocation_layout) };
}

#[unsafe(no_mangle)]
extern "C" fn abort() -> ! {
    core::arch::wasm32::unreachable()
}

/// Returns scanner imports and their indices in this module's Wasm function table.
///
/// The four allocation functions use Rust's global allocator; the remaining
/// functions are Tree-sitter's vendored C standard-library subset.
#[cfg(feature = "js-loader")]
pub(crate) fn wasm_stdlib_functions() -> Vec<(&'static str, usize)> {
    vec![
        ("calloc", calloc as *const () as usize),
        ("free", free as *const () as usize),
        ("iswalnum", iswalnum as *const () as usize),
        ("iswalpha", iswalpha as *const () as usize),
        ("iswblank", iswblank as *const () as usize),
        ("iswdigit", iswdigit as *const () as usize),
        ("iswlower", iswlower as *const () as usize),
        ("iswpunct", iswpunct as *const () as usize),
        ("iswspace", iswspace as *const () as usize),
        ("iswupper", iswupper as *const () as usize),
        ("iswxdigit", iswxdigit as *const () as usize),
        ("malloc", malloc as *const () as usize),
        ("memchr", memchr as *const () as usize),
        ("memcmp", memcmp as *const () as usize),
        ("memcpy", memcpy as *const () as usize),
        ("memmove", memmove as *const () as usize),
        ("memset", memset as *const () as usize),
        ("realloc", realloc as *const () as usize),
        ("strcmp", strcmp as *const () as usize),
        ("strlen", strlen as *const () as usize),
        ("strncat", strncat as *const () as usize),
        ("strncmp", strncmp as *const () as usize),
        ("strncpy", strncpy as *const () as usize),
        ("towlower", towlower as *const () as usize),
        ("towupper", towupper as *const () as usize),
    ]
}
