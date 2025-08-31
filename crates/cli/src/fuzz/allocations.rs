use std::{
    collections::HashMap,
    os::raw::c_void,
    sync::{
        atomic::{AtomicBool, AtomicUsize, Ordering::SeqCst},
        Mutex,
    },
};

#[ctor::ctor]
unsafe fn initialize_allocation_recording() {
    tree_sitter::set_allocator::<RecordingAllocator>();
}

#[derive(Debug, PartialEq, Eq, Hash)]
struct Allocation(*const c_void);
unsafe impl Send for Allocation {}
unsafe impl Sync for Allocation {}

#[derive(Default)]
struct AllocationRecorder {
    enabled: AtomicBool,
    allocation_count: AtomicUsize,
    outstanding_allocations: Mutex<HashMap<Allocation, usize>>,
}

thread_local! {
    static RECORDER: AllocationRecorder = AllocationRecorder::default();
}

unsafe extern "C" {
    unsafe fn malloc(size: usize) -> *mut c_void;
    unsafe fn calloc(count: usize, size: usize) -> *mut c_void;
    unsafe fn realloc(ptr: *mut c_void, size: usize) -> *mut c_void;
    unsafe fn free(ptr: *mut c_void);
}

pub fn record<T>(f: impl FnOnce() -> T) -> Result<T, String> {
    RECORDER.with(|recorder| {
        recorder.enabled.store(true, SeqCst);
        recorder.allocation_count.store(0, SeqCst);
        recorder.outstanding_allocations.lock().unwrap().clear();
    });

    let value = f();

    let outstanding_allocation_indices = RECORDER.with(|recorder| {
        recorder.enabled.store(false, SeqCst);
        recorder.allocation_count.store(0, SeqCst);
        recorder
            .outstanding_allocations
            .lock()
            .unwrap()
            .drain()
            .map(|e| e.1)
            .collect::<Vec<_>>()
    });
    if !outstanding_allocation_indices.is_empty() {
        return Err(format!(
            "Leaked allocation indices: {outstanding_allocation_indices:?}",
        ));
    }
    Ok(value)
}

struct RecordingAllocator;

impl RecordingAllocator {
    fn record_alloc(ptr: *mut c_void) {
        RECORDER.with(|recorder| {
            if recorder.enabled.load(SeqCst) {
                let count = recorder.allocation_count.fetch_add(1, SeqCst);
                recorder
                    .outstanding_allocations
                    .lock()
                    .unwrap()
                    .insert(Allocation(ptr), count);
            }
        });
    }

    fn record_dealloc(ptr: *mut c_void) {
        RECORDER.with(|recorder| {
            if recorder.enabled.load(SeqCst) {
                recorder
                    .outstanding_allocations
                    .lock()
                    .unwrap()
                    .remove(&Allocation(ptr));
            }
        });
    }
}

unsafe impl tree_sitter::Allocator for RecordingAllocator {
    unsafe extern "C" fn malloc(size: usize) -> *mut c_void {
        let result = malloc(size);
        Self::record_alloc(result);
        result
    }

    unsafe extern "C" fn calloc(count: usize, size: usize) -> *mut c_void {
        let result = calloc(count, size);
        Self::record_alloc(result);
        result
    }

    unsafe extern "C" fn realloc(ptr: *mut c_void, size: usize) -> *mut c_void {
        let result = realloc(ptr, size);
        if ptr.is_null() {
            Self::record_alloc(result);
        } else if !core::ptr::eq(ptr, result) {
            Self::record_dealloc(ptr);
            Self::record_alloc(result);
        }
        result
    }

    unsafe extern "C" fn free(ptr: *mut c_void) {
        Self::record_dealloc(ptr);
        free(ptr);
    }
}
