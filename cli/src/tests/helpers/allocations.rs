#![cfg(test)]
#![allow(dead_code)]

use lazy_static::lazy_static;
use spin::Mutex;
use std::collections::HashMap;
use std::os::raw::{c_ulong, c_void};

#[derive(Debug, PartialEq, Eq, Hash)]
struct Allocation(*const c_void);
unsafe impl Send for Allocation {}
unsafe impl Sync for Allocation {}

#[derive(Default)]
struct AllocationRecorder {
    enabled: bool,
    allocation_count: u64,
    outstanding_allocations: HashMap<Allocation, u64>,
}

lazy_static! {
    static ref RECORDER: Mutex<AllocationRecorder> = Mutex::new(AllocationRecorder::default());
}

extern "C" {
    fn malloc(size: c_ulong) -> *mut c_void;
    fn calloc(count: c_ulong, size: c_ulong) -> *mut c_void;
    fn realloc(ptr: *mut c_void, size: c_ulong) -> *mut c_void;
    fn free(ptr: *mut c_void);
}

pub fn start_recording() {
    let mut recorder = RECORDER.lock();
    recorder.enabled = true;
    recorder.allocation_count = 0;
    recorder.outstanding_allocations.clear();
}

pub fn stop_recording() {
    let mut recorder = RECORDER.lock();
    recorder.enabled = false;

    if !recorder.outstanding_allocations.is_empty() {
        let mut allocation_indices = recorder
            .outstanding_allocations
            .iter()
            .map(|e| e.1)
            .collect::<Vec<_>>();
        allocation_indices.sort_unstable();
        panic!("Leaked allocation indices: {:?}", allocation_indices);
    }
}

pub fn record(f: impl FnOnce()) {
    start_recording();
    f();
    stop_recording();
}

fn record_alloc(ptr: *mut c_void) {
    let mut recorder = RECORDER.lock();
    if recorder.enabled {
        let count = recorder.allocation_count;
        recorder.allocation_count += 1;
        recorder
            .outstanding_allocations
            .insert(Allocation(ptr), count);
    }
}

fn record_dealloc(ptr: *mut c_void) {
    let mut recorder = RECORDER.lock();
    if recorder.enabled {
        recorder.outstanding_allocations.remove(&Allocation(ptr));
    }
}

#[no_mangle]
extern "C" fn ts_record_malloc(size: c_ulong) -> *const c_void {
    let result = unsafe { malloc(size) };
    record_alloc(result);
    result
}

#[no_mangle]
extern "C" fn ts_record_calloc(count: c_ulong, size: c_ulong) -> *const c_void {
    let result = unsafe { calloc(count, size) };
    record_alloc(result);
    result
}

#[no_mangle]
extern "C" fn ts_record_realloc(ptr: *mut c_void, size: c_ulong) -> *const c_void {
    record_dealloc(ptr);
    let result = unsafe { realloc(ptr, size) };
    record_alloc(result);
    result
}

#[no_mangle]
extern "C" fn ts_record_free(ptr: *mut c_void) {
    record_dealloc(ptr);
    unsafe { free(ptr) };
}

#[no_mangle]
extern "C" fn ts_toggle_allocation_recording(enabled: bool) -> bool {
    let mut recorder = RECORDER.lock();
    let was_enabled = recorder.enabled;
    recorder.enabled = enabled;
    was_enabled
}
