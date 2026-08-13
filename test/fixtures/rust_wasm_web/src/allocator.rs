use std::{
    alloc::{GlobalAlloc, Layout},
    cell::UnsafeCell,
    ffi::c_void,
    ptr,
    sync::atomic::{AtomicBool, Ordering},
};

use dlmalloc::Dlmalloc;

const C_ALIGNMENT: usize = 2 * size_of::<usize>();

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

#[unsafe(no_mangle)]
pub unsafe extern "C" fn malloc(size: usize) -> *mut c_void {
    ALLOCATOR.with_lock(|allocator| unsafe { allocator.c_malloc(size).cast() })
}

#[unsafe(no_mangle)]
pub unsafe extern "C" fn calloc(count: usize, size: usize) -> *mut c_void {
    let Some(payload_size) = count.checked_mul(size) else {
        return ptr::null_mut();
    };
    ALLOCATOR.with_lock(|allocator| unsafe {
        allocator.calloc(payload_size, C_ALIGNMENT).cast()
    })
}

#[unsafe(no_mangle)]
pub unsafe extern "C" fn realloc(ptr: *mut c_void, size: usize) -> *mut c_void {
    ALLOCATOR.with_lock(|allocator| unsafe { allocator.c_realloc(ptr.cast(), size).cast() })
}

#[unsafe(no_mangle)]
pub unsafe extern "C" fn free(ptr: *mut c_void) {
    ALLOCATOR.with_lock(|allocator| unsafe {
        allocator.c_free(ptr.cast());
    });
}

pub fn initialize() {
    unsafe {
        tree_sitter::set_allocator(
            Some(malloc),
            Some(calloc),
            Some(realloc),
            Some(free),
        );
    }
}

pub unsafe fn allocate(size: usize) -> *mut u8 {
    unsafe { malloc(size).cast() }
}

pub unsafe fn allocate_zeroed(layout: Layout) -> *mut u8 {
    unsafe { ALLOCATOR.alloc_zeroed(layout) }
}

pub unsafe fn deallocate(ptr: *mut u8) {
    unsafe { free(ptr.cast()) };
}
