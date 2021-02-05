// In all dev builds, the tree-sitter library is built with the `allocation-tracking`
// feature enabled. This causes the library to link against a set of externally
// defined C functions like `ts_record_malloc` and `ts_record_free`. In tests, these
// are defined to actually keep track of outstanding allocations. But when not running
// tests, the symbols still need to be defined. This file provides pass-through
// implementations of all of these functions.

use std::os::raw::c_void;

extern "C" {
    fn malloc(size: usize) -> *mut c_void;
    fn calloc(count: usize, size: usize) -> *mut c_void;
    fn realloc(ptr: *mut c_void, size: usize) -> *mut c_void;
    fn free(ptr: *mut c_void);
}

#[no_mangle]
unsafe extern "C" fn ts_record_malloc(size: usize) -> *const c_void {
    malloc(size)
}

#[no_mangle]
unsafe extern "C" fn ts_record_calloc(count: usize, size: usize) -> *const c_void {
    calloc(count, size)
}

#[no_mangle]
unsafe extern "C" fn ts_record_realloc(ptr: *mut c_void, size: usize) -> *const c_void {
    realloc(ptr, size)
}

#[no_mangle]
unsafe extern "C" fn ts_record_free(ptr: *mut c_void) {
    free(ptr)
}

#[no_mangle]
extern "C" fn ts_toggle_allocation_recording(_: bool) -> bool {
    false
}
