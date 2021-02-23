use std::os::raw::c_void;

#[cfg(not(feature = "allocation-tracking"))]
extern "C" {
    /// Normally, use `free(1)` to free memory allocated from C.
    #[link_name = "free"]
    pub fn free_ptr(ptr: *mut c_void);
}

/// When the `allocation-tracking` feature is enabled, the C library is compiled with
/// the `TREE_SITTER_TEST` macro, so all calls to `malloc`, `free`, etc are linked
/// against wrapper functions called `ts_record_malloc`, `ts_record_free`, etc.
/// When freeing buffers allocated from C, use the wrapper `free` function.
#[cfg(feature = "allocation-tracking")]
pub use crate::allocations::ts_record_free as free_ptr;

/// A raw pointer and a length, exposed as an iterator.
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
