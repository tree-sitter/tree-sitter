use std::os::raw::c_void;

type Free = unsafe extern "C" fn(ptr: *mut c_void);

pub struct CBufferIter<T> {
    ptr: *mut T,
    count: usize,
    free: Free,
    i: usize,
}

impl<T> CBufferIter<T> {
    pub unsafe fn new(ptr: *mut T, count: usize, free: Free) -> Self {
        Self { ptr, count, free, i: 0 }
    }
}

impl<T: Copy> Iterator for CBufferIter<T> {
    type Item = T;

    fn next(&mut self) -> Option<Self::Item> {
        let i = self.i;
        self.i += 1;
        if i >= self.count {
            None
        } else {
            Some(unsafe { *self.ptr.offset(i as isize) })
        }
    }
}

impl<T> Drop for CBufferIter<T> {
    fn drop(&mut self) {
        let free = self.free;
        unsafe { free(self.ptr as *mut c_void); }
    }
}
