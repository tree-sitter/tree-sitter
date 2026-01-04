#![cfg(all(target_arch = "wasm32", target_os = "unknown"))]

use std::alloc::Layout;
use std::mem::{align_of, size_of};
use std::ptr;

// C `malloc` must return a pointer suitably aligned for any object type.
// We use a conservative alignment that is at least pointer-sized and typically 16.

const MALLOC_ALIGN: usize = {
    let a = align_of::<u128>();
    if a > align_of::<usize>() {
        a
    } else {
        align_of::<usize>()
    }
};

const fn align_up(value: usize, align: usize) -> usize {
    // `align` is expected to be a power of two.
    (value + (align - 1)) & !(align - 1)
}

// Pad the header so that (raw_ptr + HEADER_SIZE) is still MALLOC_ALIGN-aligned.

const HEADER_SIZE: usize = align_up(size_of::<usize>(), MALLOC_ALIGN);

const HEADER_ALIGN: usize = MALLOC_ALIGN;

#[unsafe(no_mangle)]
pub extern "C" fn malloc(size: usize) -> *mut u8 {
    if size == 0 {
        return ptr::null_mut();
    }

    let total_size = match size.checked_add(HEADER_SIZE) {
        Some(v) => v,
        None => return ptr::null_mut(),
    };

    let layout = match Layout::from_size_align(total_size, HEADER_ALIGN) {
        Ok(l) => l,
        Err(_) => return ptr::null_mut(),
    };

    unsafe {
        let raw_ptr = std::alloc::alloc(layout);
        if raw_ptr.is_null() {
            return ptr::null_mut();
        }

        (raw_ptr as *mut usize).write(size);
        raw_ptr.add(HEADER_SIZE)
    }
}

#[unsafe(no_mangle)]
pub extern "C" fn calloc(nitems: usize, size: usize) -> *mut u8 {
    let total = match nitems.checked_mul(size) {
        Some(v) => v,
        None => return ptr::null_mut(),
    };

    let ptr = malloc(total);
    if ptr.is_null() {
        return ptr;
    }

    unsafe {
        ptr::write_bytes(ptr, 0, total);
    }

    ptr
}

#[unsafe(no_mangle)]
pub extern "C" fn free(ptr: *mut u8) {
    if ptr.is_null() {
        return;
    }

    unsafe {
        let header_ptr = ptr.sub(HEADER_SIZE);
        let size = header_ptr.cast::<usize>().read();
        let total_size = match size.checked_add(HEADER_SIZE) {
            Some(v) => v,
            None => return,
        };

        if let Ok(layout) = Layout::from_size_align(total_size, HEADER_ALIGN) {
            std::alloc::dealloc(header_ptr, layout);
        }
    }
}

#[unsafe(no_mangle)]
pub extern "C" fn realloc(ptr: *mut u8, size: usize) -> *mut u8 {
    if ptr.is_null() {
        return malloc(size);
    }

    if size == 0 {
        free(ptr);
        return ptr::null_mut();
    }

    unsafe {
        let header_ptr = ptr.sub(HEADER_SIZE);
        let old_size = header_ptr.cast::<usize>().read();
        let old_total = match old_size.checked_add(HEADER_SIZE) {
            Some(v) => v,
            None => return ptr::null_mut(),
        };
        let new_total = match size.checked_add(HEADER_SIZE) {
            Some(v) => v,
            None => return ptr::null_mut(),
        };

        let old_layout = match Layout::from_size_align(old_total, HEADER_ALIGN) {
            Ok(l) => l,
            Err(_) => return ptr::null_mut(),
        };

        let new_header_ptr = std::alloc::realloc(header_ptr, old_layout, new_total);
        if new_header_ptr.is_null() {
            return ptr::null_mut();
        }

        new_header_ptr.cast::<usize>().write(size);
        new_header_ptr.add(HEADER_SIZE)
    }
}
