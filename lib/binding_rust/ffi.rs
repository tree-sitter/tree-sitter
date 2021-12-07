#![allow(dead_code)]
#![allow(non_upper_case_globals)]
#![allow(non_camel_case_types)]

#[cfg(feature = "generate-bindings")]
include!(concat!(env!("OUT_DIR"), "/bindings.rs"));

#[cfg(not(feature = "generate-bindings"))]
include!("./bindings.rs");

extern "C" {
    pub(crate) fn dup(fd: std::os::raw::c_int) -> std::os::raw::c_int;
}
