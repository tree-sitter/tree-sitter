use spin::Mutex;
use std::{
    collections::HashMap,
    os::raw::{c_ulong, c_void},
};

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

thread_local! {
    static RECORDER: Mutex<AllocationRecorder> = Default::default();
}

extern "C" {
    fn malloc(size: c_ulong) -> *mut c_void;
    fn calloc(count: c_ulong, size: c_ulong) -> *mut c_void;
    fn realloc(ptr: *mut c_void, size: c_ulong) -> *mut c_void;
    fn free(ptr: *mut c_void);
}

pub fn record<T>(f: impl FnOnce() -> T) -> T {
    RECORDER.with(|recorder| {
        let mut recorder = recorder.lock();
        recorder.enabled = true;
        recorder.allocation_count = 0;
        recorder.outstanding_allocations.clear();
    });

    let value = f();

    let outstanding_allocation_indices = RECORDER.with(|recorder| {
        let mut recorder = recorder.lock();
        recorder.enabled = false;
        recorder.allocation_count = 0;
        recorder
            .outstanding_allocations
            .drain()
            .map(|e| e.1)
            .collect::<Vec<_>>()
    });
    if !outstanding_allocation_indices.is_empty() {
        panic!(
            "Leaked allocation indices: {:?}",
            outstanding_allocation_indices
        );
    }
    value
}

fn record_alloc(ptr: *mut c_void) {
    RECORDER.with(|recorder| {
        let mut recorder = recorder.lock();
        if recorder.enabled {
            let count = recorder.allocation_count;
            recorder.allocation_count += 1;
            recorder
                .outstanding_allocations
                .insert(Allocation(ptr), count);
        }
    });
}

fn record_dealloc(ptr: *mut c_void) {
    RECORDER.with(|recorder| {
        let mut recorder = recorder.lock();
        if recorder.enabled {
            recorder.outstanding_allocations.remove(&Allocation(ptr));
        }
    });
}

#[no_mangle]
pub extern "C" fn ts_record_malloc(size: c_ulong) -> *const c_void {
    let result = unsafe { malloc(size) };
    record_alloc(result);
    result
}

#[no_mangle]
pub extern "C" fn ts_record_calloc(count: c_ulong, size: c_ulong) -> *const c_void {
    let result = unsafe { calloc(count, size) };
    record_alloc(result);
    result
}

#[no_mangle]
pub extern "C" fn ts_record_realloc(ptr: *mut c_void, size: c_ulong) -> *const c_void {
    record_dealloc(ptr);
    let result = unsafe { realloc(ptr, size) };
    record_alloc(result);
    result
}

// This needs to be unsafe because it's reexported as crate::util::free_ptr, which is mapped to
// libc's `free` function when the allocation-tracking feature is disabled.  Since `free` is
// unsafe, this function needs to be too.
#[no_mangle]
pub unsafe extern "C" fn ts_record_free(ptr: *mut c_void) {
    record_dealloc(ptr);
    free(ptr);
}

#[no_mangle]
pub extern "C" fn ts_toggle_allocation_recording(enabled: bool) -> bool {
    RECORDER.with(|recorder| {
        let mut recorder = recorder.lock();
        let was_enabled = recorder.enabled;
        recorder.enabled = enabled;
        was_enabled
    })
}
