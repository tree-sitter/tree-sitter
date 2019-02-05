#![allow(dead_code)]
#![allow(non_upper_case_globals)]
#![allow(non_camel_case_types)]

include!("./bindings.rs");

extern "C" {
    pub(crate) fn dup(fd: std::os::raw::c_int) -> std::os::raw::c_int;
}
