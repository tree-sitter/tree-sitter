//! C allocation functions backed by Rust's application-selected global allocator.
//!
//! This is intentionally a Tree-sitter compatibility shim rather than a
//! general-purpose implementation of the WebAssembly C allocation ABI.
//! Tree-sitter and its supported external scanners only allocate types whose
//! alignment is at most eight bytes.

use alloc::alloc::{Layout, alloc, alloc_zeroed, dealloc, realloc as rust_realloc};
use core::{ffi::c_void, mem, ptr};

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
