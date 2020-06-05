use std::{
    cmp::Ordering,
    ffi::CStr,
    fmt,
    io::{self, ErrorKind, Write},
    os::raw::{c_char, c_int, c_uint},
};

pub(crate) trait WrappingOffsetFromExt<T: Sized> {
    fn wrapping_offset_from_(self, origin: *const T) -> isize;
}

impl<T: Sized> WrappingOffsetFromExt<T> for *const T {
    #[inline]
    fn wrapping_offset_from_(self, origin: *const T) -> isize {
        let pointee_size = std::mem::size_of::<T>();
        assert!(0 < pointee_size && pointee_size <= isize::max_value() as usize);

        let d = isize::wrapping_sub(self as _, origin as _);
        d.wrapping_div(pointee_size as _)
    }
}

impl<T: Sized> WrappingOffsetFromExt<T> for *mut T {
    fn wrapping_offset_from_(self, origin: *const T) -> isize {
        (self as *const T).wrapping_offset_from_(origin)
    }
}

/// Simple replacement for libc::strcmp
///
/// Safety: both `a` and `b` must point to valid C strings, and no alive unique reference must
/// point to the underlying memory.
pub(crate) unsafe fn strcmp(s1: *const c_char, s2: *const c_char) -> c_int {
    let s1 = CStr::from_ptr(s1);
    let s2 = CStr::from_ptr(s2);

    match s1.cmp(s2) {
        Ordering::Less => -1,
        Ordering::Equal => 0,
        Ordering::Greater => 1,
    }
}

/// Simple replacement for libc::strncmp
///
/// Safety: both `a` and `b` must point to valid C strings, and no alive unique reference must
/// point to the underlying memory. Neither `a + n` or `b + n` can overflow.
pub(crate) unsafe fn strncmp(mut s1: *const c_char, mut s2: *const c_char, mut n: usize) -> c_int {
    while n > 0 {
        let a = *s1;
        let b = *s2;

        match a.cmp(&b) {
            Ordering::Less => return -1,
            Ordering::Greater => return 1,
            Ordering::Equal => {}
        }

        if a == 0 {
            return 0;
        }

        s1 = s1.add(1);
        s2 = s2.add(1);
        n -= 1;
    }

    0
}

#[derive(Debug)]
pub struct WriteCounter<W> {
    inner: W,
    count: usize,
}

impl<W: Write> WriteCounter<W> {
    pub(crate) fn new(write: W) -> Self {
        Self {
            inner: write,
            count: 0,
        }
    }
}

impl<W> WriteCounter<W> {
    pub fn count(&self) -> usize {
        self.count
    }
}

impl<W> Write for WriteCounter<W>
where
    W: Write,
{
    fn write(&mut self, buf: &[u8]) -> std::io::Result<usize> {
        match self.inner.write(buf) {
            Ok(count) => {
                self.count += count;
                Ok(count)
            }
            err => err,
        }
    }

    fn flush(&mut self) -> std::io::Result<()> {
        self.inner.flush()
    }
}

struct VoidWriter;

impl Write for VoidWriter {
    fn write(&mut self, buf: &[u8]) -> io::Result<usize> {
        Ok(buf.len())
    }

    fn flush(&mut self) -> io::Result<()> {
        Ok(())
    }
}

macro_rules! try_fmt_write_zero {
    ($counter:expr, $args:expr) => {
        match $counter.write_fmt($args) {
            Ok(()) => Ok(()),
            Err(err) if matches!(err.kind(), ErrorKind::WriteZero) => return Ok($counter.count()),
            Err(err) => Err(err),
        }
    };
}

pub(crate) unsafe fn snwrite(
    string: *mut c_char,
    size: usize,
    args: fmt::Arguments,
) -> io::Result<usize> {
    if size == 0 {
        snwrite_inner(WriteCounter::new(VoidWriter), args)
    } else {
        snwrite_inner(
            WriteCounter::new(std::slice::from_raw_parts_mut(string as *mut u8, size)),
            args,
        )
    }
}

fn snwrite_inner<W>(mut counter: WriteCounter<W>, args: fmt::Arguments) -> io::Result<usize>
where
    W: Write,
{
    try_fmt_write_zero!(counter, args)?;
    try_fmt_write_zero!(counter, format_args!("\0"))?;

    Ok(counter.count() - 1)
}

#[macro_export]
macro_rules! snwrite {
    ($string:expr, $size:expr, $($arg:tt)*) => {
        snwrite($string, $size, ::std::format_args!($($arg)*))
    }
}

#[repr(transparent)]
#[cfg_attr(feature = "capi", derive(Clone, Copy))]
pub struct File(
    #[cfg(feature = "capi")] crate::capi::CFile,
    #[cfg(not(feature = "capi"))] Option<Box<std::io::BufWriter<std::fs::File>>>,
);

impl File {
    pub(crate) fn empty() -> Self {
        #[cfg(feature = "capi")]
        {
            Self(crate::capi::CFile::new(std::ptr::null_mut()))
        }

        #[cfg(not(feature = "capi"))]
        {
            Self(None)
        }
    }

    pub(crate) fn is_valid(&self) -> bool {
        #[cfg(feature = "capi")]
        {
            !self.0.is_null()
        }

        #[cfg(not(feature = "capi"))]
        {
            self.0.is_some()
        }
    }

    pub(crate) fn close(&mut self) {
        if !self.is_valid() {
            return;
        }

        #[cfg(feature = "capi")]
        {
            if self.0.close() != 0 {
                panic!("cannot close libc file stream");
            }
        }

        #[cfg(not(feature = "capi"))]
        {
            self.0 = None;
        }
    }
}

impl Write for File {
    fn write(&mut self, buf: &[u8]) -> io::Result<usize> {
        #[cfg(feature = "capi")]
        {
            self.0.write(buf)
        }

        #[cfg(not(feature = "capi"))]
        {
            self.0.as_mut().unwrap().write(buf)
        }
    }

    fn flush(&mut self) -> io::Result<()> {
        #[cfg(feature = "capi")]
        {
            self.0.flush()
        }

        #[cfg(not(feature = "capi"))]
        {
            self.0.as_mut().unwrap().flush()
        }
    }
}

#[cfg(feature = "capi")]
impl<T> From<T> for File
where
    T: Into<crate::capi::CFile>,
{
    fn from(file: T) -> Self {
        Self(file.into())
    }
}

#[cfg(not(feature = "capi"))]
impl From<std::io::BufWriter<std::fs::File>> for File {
    fn from(file: std::io::BufWriter<std::fs::File>) -> Self {
        Self(Some(Box::new(file)))
    }
}

// Credits: (musl libc library)[https://www.musl-libc.org/]
pub(crate) fn iswspace(wc: c_uint) -> c_int {
    const SPACES: [c_uint; 21] = [
        b' ' as _, b'\t' as _, b'\n' as _, b'\r' as _, 11, 12, 0x0085, 0x2000, 0x2001, 0x2002,
        0x2003, 0x2004, 0x2005, 0x2006, 0x2008, 0x2009, 0x200a, 0x2028, 0x2029, 0x205f, 0x3000,
    ];

    (wc != 0 && SPACES.contains(&wc)) as c_int
}

// Credits: (musl libc library)[https://www.musl-libc.org/]
pub(crate) fn iswdigit(wc: c_uint) -> c_int {
    (wc.wrapping_sub(b'0' as c_uint) < 10) as c_int
}

// Credits: (musl libc library)[https://www.musl-libc.org/]
pub(crate) fn iswalpha(wc: c_uint) -> c_int {
    const TABLE: [c_uint; 3904] = include!("./alpha.data");

    if wc < 0x20000 {
        ((TABLE[(TABLE[(wc >> 8) as usize].wrapping_mul(32) + ((wc & 255) >> 3)) as usize]
            >> (wc & 7))
            & 1) as c_int
    } else if wc < 0x2fffe {
        1
    } else {
        0
    }
}

// Credits: (musl libc library)[https://www.musl-libc.org/]
pub(crate) fn iswalnum(wc: c_uint) -> c_int {
    (iswdigit(wc) != 0 || iswalpha(wc) != 0) as c_int
}
