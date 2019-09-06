use super::{load_property_sheet, Error, Highlight, Highlighter, HtmlRenderer, Properties};
use regex::Regex;
use std::collections::HashMap;
use std::ffi::CStr;
use std::os::raw::c_char;
use std::process::abort;
use std::sync::atomic::AtomicUsize;
use std::{fmt, slice};
use tree_sitter::{Language, PropertySheet};

struct LanguageConfiguration {
    language: Language,
    property_sheet: PropertySheet<Properties>,
    injection_regex: Option<Regex>,
}

pub struct TSHighlighter {
    languages: HashMap<String, LanguageConfiguration>,
    attribute_strings: Vec<&'static [u8]>,
}

pub struct TSHighlightBuffer(HtmlRenderer);

#[repr(C)]
pub enum ErrorCode {
    Ok,
    UnknownScope,
    Timeout,
    InvalidLanguage,
}

#[no_mangle]
pub extern "C" fn ts_highlighter_new(
    attribute_strings: *const *const c_char,
) -> *mut TSHighlighter {
    let attribute_strings =
        unsafe { slice::from_raw_parts(attribute_strings, Highlight::Unknown as usize + 1) };
    let attribute_strings = attribute_strings
        .into_iter()
        .map(|s| {
            if s.is_null() {
                &[]
            } else {
                unsafe { CStr::from_ptr(*s).to_bytes() }
            }
        })
        .collect();
    Box::into_raw(Box::new(TSHighlighter {
        languages: HashMap::new(),
        attribute_strings,
    }))
}

#[no_mangle]
pub extern "C" fn ts_highlight_buffer_new() -> *mut TSHighlightBuffer {
    Box::into_raw(Box::new(TSHighlightBuffer(HtmlRenderer::new())))
}

#[no_mangle]
pub extern "C" fn ts_highlighter_delete(this: *mut TSHighlighter) {
    drop(unsafe { Box::from_raw(this) })
}

#[no_mangle]
pub extern "C" fn ts_highlight_buffer_delete(this: *mut TSHighlightBuffer) {
    drop(unsafe { Box::from_raw(this) })
}

#[no_mangle]
pub extern "C" fn ts_highlight_buffer_content(this: *const TSHighlightBuffer) -> *const u8 {
    let this = unwrap_ptr(this);
    this.0.html.as_slice().as_ptr()
}

#[no_mangle]
pub extern "C" fn ts_highlight_buffer_line_offsets(this: *const TSHighlightBuffer) -> *const u32 {
    let this = unwrap_ptr(this);
    this.0.line_offsets.as_slice().as_ptr()
}

#[no_mangle]
pub extern "C" fn ts_highlight_buffer_len(this: *const TSHighlightBuffer) -> u32 {
    let this = unwrap_ptr(this);
    this.0.html.len() as u32
}

#[no_mangle]
pub extern "C" fn ts_highlight_buffer_line_count(this: *const TSHighlightBuffer) -> u32 {
    let this = unwrap_ptr(this);
    this.0.line_offsets.len() as u32
}

#[no_mangle]
pub extern "C" fn ts_highlighter_add_language(
    this: *mut TSHighlighter,
    scope_name: *const c_char,
    language: Language,
    property_sheet_json: *const c_char,
    injection_regex: *const c_char,
) -> ErrorCode {
    let this = unwrap_mut_ptr(this);
    let scope_name = unsafe { CStr::from_ptr(scope_name) };
    let scope_name = unwrap(scope_name.to_str()).to_string();
    let property_sheet_json = unsafe { CStr::from_ptr(property_sheet_json) };
    let property_sheet_json = unwrap(property_sheet_json.to_str());

    let property_sheet = unwrap(load_property_sheet(language, property_sheet_json));
    let injection_regex = if injection_regex.is_null() {
        None
    } else {
        let pattern = unsafe { CStr::from_ptr(injection_regex) };
        Some(unwrap(Regex::new(unwrap(pattern.to_str()))))
    };

    this.languages.insert(
        scope_name,
        LanguageConfiguration {
            language,
            property_sheet,
            injection_regex,
        },
    );

    ErrorCode::Ok
}

#[no_mangle]
pub extern "C" fn ts_highlighter_highlight(
    this: *const TSHighlighter,
    scope_name: *const c_char,
    source_code: *const c_char,
    source_code_len: u32,
    output: *mut TSHighlightBuffer,
    cancellation_flag: *const AtomicUsize,
) -> ErrorCode {
    let this = unwrap_ptr(this);
    let output = unwrap_mut_ptr(output);
    let scope_name = unwrap(unsafe { CStr::from_ptr(scope_name).to_str() });
    let source_code =
        unsafe { slice::from_raw_parts(source_code as *const u8, source_code_len as usize) };
    let cancellation_flag = unsafe { cancellation_flag.as_ref() };
    this.highlight(source_code, scope_name, output, cancellation_flag)
}

impl TSHighlighter {
    fn highlight(
        &self,
        source_code: &[u8],
        scope_name: &str,
        output: &mut TSHighlightBuffer,
        cancellation_flag: Option<&AtomicUsize>,
    ) -> ErrorCode {
        let configuration = self.languages.get(scope_name);
        if configuration.is_none() {
            return ErrorCode::UnknownScope;
        }
        let configuration = configuration.unwrap();
        let languages = &self.languages;

        let highlighter = Highlighter::new(
            source_code,
            configuration.language,
            &configuration.property_sheet,
            |injection_string| {
                languages.values().find_map(|conf| {
                    conf.injection_regex.as_ref().and_then(|regex| {
                        if regex.is_match(injection_string) {
                            Some((conf.language, &conf.property_sheet))
                        } else {
                            None
                        }
                    })
                })
            },
            cancellation_flag,
        );

        if let Ok(highlighter) = highlighter {
            output.0.reset();
            let result = output.0.render(highlighter, source_code, &|s| {
                self.attribute_strings[s as usize]
            });
            match result {
                Err(Error::Cancelled) => {
                    return ErrorCode::Timeout;
                }
                Err(Error::InvalidLanguage) => {
                    return ErrorCode::InvalidLanguage;
                }
                Err(Error::Unknown) => {
                    return ErrorCode::Timeout;
                }
                Ok(()) => ErrorCode::Ok,
            }
        } else {
            ErrorCode::Timeout
        }
    }
}

fn unwrap_ptr<'a, T>(result: *const T) -> &'a T {
    unsafe { result.as_ref() }.unwrap_or_else(|| {
        eprintln!("{}:{} - pointer must not be null", file!(), line!());
        abort();
    })
}

fn unwrap_mut_ptr<'a, T>(result: *mut T) -> &'a mut T {
    unsafe { result.as_mut() }.unwrap_or_else(|| {
        eprintln!("{}:{} - pointer must not be null", file!(), line!());
        abort();
    })
}

fn unwrap<T, E: fmt::Display>(result: Result<T, E>) -> T {
    result.unwrap_or_else(|error| {
        eprintln!("tree-sitter highlight error: {}", error);
        abort();
    })
}
