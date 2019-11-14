use std::os::raw::c_void;

extern "C" {
    /// In *Release* builds, the C library links directly against `malloc` and `free`.
    ///
    /// When freeing memory that was allocated by C code, use `free` directly.
    #[cfg(not(debug_assertions))]
    #[link_name = "free"]
    pub fn free_ptr(ptr: *mut c_void);

    /// In *Test* builds, the C library is compiled with the `TREE_SITTER_TEST` macro,
    /// so all calls to `malloc`, `free`, etc are linked against wrapper functions
    /// called `ts_record_malloc`, `ts_record_free`, etc. These symbols are defined
    /// in the `tree_sitter_cli::tests::helpers::allocations` module.
    ///
    /// When freeing memory that was allocated by C code, use the `free` function
    /// from that module.
    #[cfg(debug_assertions)]
    #[link_name = "ts_record_free"]
    pub fn free_ptr(ptr: *mut c_void);

    /// In *Debug* builds, the C library is compiled the same as in test builds: using
    /// the wrapper functions. This prevents the C library from having to be recompiled
    /// constantly when switching between running tests and compiling with RLS.
    ///
    /// But we don't want to actually record allocations when running the library in
    /// debug mode, so we define symbols like `ts_record_malloc` to just delegate to
    /// the normal `malloc` functions.
    #[cfg(all(debug_assertions, not(test)))]
    fn malloc(size: usize) -> *mut c_void;
    #[cfg(all(debug_assertions, not(test)))]
    fn calloc(count: usize, size: usize) -> *mut c_void;
    #[cfg(all(debug_assertions, not(test)))]
    fn realloc(ptr: *mut c_void, size: usize) -> *mut c_void;
    #[cfg(all(debug_assertions, not(test)))]
    fn free(ptr: *mut c_void);
}

#[cfg(all(debug_assertions, not(test)))]
#[no_mangle]
unsafe extern "C" fn ts_record_malloc(size: usize) -> *const c_void {
    malloc(size)
}

#[cfg(all(debug_assertions, not(test)))]
#[no_mangle]
unsafe extern "C" fn ts_record_calloc(count: usize, size: usize) -> *const c_void {
    calloc(count, size)
}

#[cfg(all(debug_assertions, not(test)))]
#[no_mangle]
unsafe extern "C" fn ts_record_realloc(ptr: *mut c_void, size: usize) -> *const c_void {
    realloc(ptr, size)
}

#[cfg(all(debug_assertions, not(test)))]
#[no_mangle]
unsafe extern "C" fn ts_record_free(ptr: *mut c_void) {
    free(ptr)
}

#[cfg(all(debug_assertions, not(test)))]
#[no_mangle]
extern "C" fn ts_toggle_allocation_recording(_: bool) -> bool {
    false
}

pub struct CBufferIter<T> {
    ptr: *mut T,
    count: usize,
    i: usize,
}

impl<T> CBufferIter<T> {
    pub unsafe fn new(ptr: *mut T, count: usize) -> Self {
        Self { ptr, count, i: 0 }
    }
}

impl<T: Copy> Iterator for CBufferIter<T> {
    type Item = T;

    fn next(&mut self) -> Option<Self::Item> {
        let i = self.i;
        if i >= self.count {
            None
        } else {
            self.i += 1;
            Some(unsafe { *self.ptr.offset(i as isize) })
        }
    }

    fn size_hint(&self) -> (usize, Option<usize>) {
        let remaining = self.count - self.i;
        (remaining, Some(remaining))
    }
}

impl<T: Copy> ExactSizeIterator for CBufferIter<T> {}

impl<T> Drop for CBufferIter<T> {
    fn drop(&mut self) {
        unsafe {
            free_ptr(self.ptr as *mut c_void);
        }
    }
}
