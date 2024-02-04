use super::{Error, TagsConfiguration, TagsContext};
use std::collections::HashMap;
use std::ffi::CStr;
use std::os::raw::c_char;
use std::process::abort;
use std::sync::atomic::AtomicUsize;
use std::{fmt, slice, str};
use tree_sitter::Language;

const BUFFER_TAGS_RESERVE_CAPACITY: usize = 100;
const BUFFER_DOCS_RESERVE_CAPACITY: usize = 1024;

#[repr(C)]
#[derive(Debug, PartialEq, Eq)]
pub enum TSTagsError {
    Ok,
    UnknownScope,
    Timeout,
    InvalidLanguage,
    InvalidUtf8,
    InvalidRegex,
    InvalidQuery,
    InvalidCapture,
    Unknown,
}

#[repr(C)]
pub struct TSPoint {
    row: u32,
    column: u32,
}

#[repr(C)]
pub struct TSTag {
    pub start_byte: u32,
    pub end_byte: u32,
    pub name_start_byte: u32,
    pub name_end_byte: u32,
    pub line_start_byte: u32,
    pub line_end_byte: u32,
    pub start_point: TSPoint,
    pub end_point: TSPoint,
    pub utf16_start_colum: u32,
    pub utf16_end_colum: u32,
    pub docs_start_byte: u32,
    pub docs_end_byte: u32,
    pub syntax_type_id: u32,
    pub is_definition: bool,
}

pub struct TSTagger {
    languages: HashMap<String, TagsConfiguration>,
}

pub struct TSTagsBuffer {
    context: TagsContext,
    tags: Vec<TSTag>,
    docs: Vec<u8>,
    errors_present: bool,
}

#[no_mangle]
pub extern "C" fn ts_tagger_new() -> *mut TSTagger {
    Box::into_raw(Box::new(TSTagger {
        languages: HashMap::new(),
    }))
}

/// Delete a [`TSTagger`].
///
/// # Safety
///
/// `this` must be non-null and a valid pointer to a [`TSTagger`] instance.
#[no_mangle]
pub unsafe extern "C" fn ts_tagger_delete(this: *mut TSTagger) {
    drop(Box::from_raw(this));
}

/// Add a language to a [`TSTagger`].
///
/// Returns a [`TSTagsError`] indicating whether the operation was successful or not.
///
/// # Safety
///
/// `this` must be non-null and a valid pointer to a [`TSTagger`] instance.
/// `scope_name` must be non-null and a valid pointer to a null-terminated string.
/// `tags_query` and `locals_query` must be non-null and valid pointers to strings.
///
/// The caller must ensure that the lengths of `tags_query` and `locals_query` are correct.
#[no_mangle]
pub unsafe extern "C" fn ts_tagger_add_language(
    this: *mut TSTagger,
    scope_name: *const c_char,
    language: Language,
    tags_query: *const u8,
    locals_query: *const u8,
    tags_query_len: u32,
    locals_query_len: u32,
) -> TSTagsError {
    let tagger = unwrap_mut_ptr(this);
    let scope_name = unwrap(CStr::from_ptr(scope_name).to_str());
    let tags_query = slice::from_raw_parts(tags_query, tags_query_len as usize);
    let locals_query = if !locals_query.is_null() {
        slice::from_raw_parts(locals_query, locals_query_len as usize)
    } else {
        &[]
    };
    let Ok(tags_query) = str::from_utf8(tags_query) else {
        return TSTagsError::InvalidUtf8;
    };
    let Ok(locals_query) = str::from_utf8(locals_query) else {
        return TSTagsError::InvalidUtf8;
    };

    match TagsConfiguration::new(language, tags_query, locals_query) {
        Ok(c) => {
            tagger.languages.insert(scope_name.to_string(), c);
            TSTagsError::Ok
        }
        Err(Error::Query(_)) => TSTagsError::InvalidQuery,
        Err(Error::Regex(_)) => TSTagsError::InvalidRegex,
        Err(Error::Cancelled) => TSTagsError::Timeout,
        Err(Error::InvalidLanguage) => TSTagsError::InvalidLanguage,
        Err(Error::InvalidCapture(_)) => TSTagsError::InvalidCapture,
    }
}

/// Tags some source code.
///
/// Returns a [`TSTagsError`] indicating whether the operation was successful or not.
///
/// # Safety
///
/// `this` must be a non-null valid pointer to a [`TSTagger`] instance.
/// `scope_name` must be a non-null valid pointer to a null-terminated string.
/// `source_code` must be a non-null valid pointer to a slice of bytes.
/// `output` must be a non-null valid pointer to a [`TSTagsBuffer`] instance.
/// `cancellation_flag` must be a non-null valid pointer to an [`AtomicUsize`] instance.
#[no_mangle]
pub unsafe extern "C" fn ts_tagger_tag(
    this: *mut TSTagger,
    scope_name: *const c_char,
    source_code: *const u8,
    source_code_len: u32,
    output: *mut TSTagsBuffer,
    cancellation_flag: *const AtomicUsize,
) -> TSTagsError {
    let tagger = unwrap_mut_ptr(this);
    let buffer = unwrap_mut_ptr(output);
    let scope_name = unwrap(CStr::from_ptr(scope_name).to_str());

    if let Some(config) = tagger.languages.get(scope_name) {
        shrink_and_clear(&mut buffer.tags, BUFFER_TAGS_RESERVE_CAPACITY);
        shrink_and_clear(&mut buffer.docs, BUFFER_DOCS_RESERVE_CAPACITY);

        let source_code = slice::from_raw_parts(source_code, source_code_len as usize);
        let cancellation_flag = cancellation_flag.as_ref();

        let tags = match buffer
            .context
            .generate_tags(config, source_code, cancellation_flag)
        {
            Ok((tags, found_error)) => {
                buffer.errors_present = found_error;
                tags
            }
            Err(e) => {
                return match e {
                    Error::InvalidLanguage => TSTagsError::InvalidLanguage,
                    _ => TSTagsError::Timeout,
                }
            }
        };

        for tag in tags {
            let Ok(tag) = tag else {
                buffer.tags.clear();
                buffer.docs.clear();
                return TSTagsError::Timeout;
            };

            let prev_docs_len = buffer.docs.len();
            if let Some(docs) = tag.docs {
                buffer.docs.extend_from_slice(docs.as_bytes());
            }
            buffer.tags.push(TSTag {
                start_byte: tag.range.start as u32,
                end_byte: tag.range.end as u32,
                name_start_byte: tag.name_range.start as u32,
                name_end_byte: tag.name_range.end as u32,
                line_start_byte: tag.line_range.start as u32,
                line_end_byte: tag.line_range.end as u32,
                start_point: TSPoint {
                    row: tag.span.start.row as u32,
                    column: tag.span.start.column as u32,
                },
                end_point: TSPoint {
                    row: tag.span.end.row as u32,
                    column: tag.span.end.column as u32,
                },
                utf16_start_colum: tag.utf16_column_range.start as u32,
                utf16_end_colum: tag.utf16_column_range.end as u32,
                docs_start_byte: prev_docs_len as u32,
                docs_end_byte: buffer.docs.len() as u32,
                syntax_type_id: tag.syntax_type_id,
                is_definition: tag.is_definition,
            });
        }

        TSTagsError::Ok
    } else {
        TSTagsError::UnknownScope
    }
}

#[no_mangle]
pub extern "C" fn ts_tags_buffer_new() -> *mut TSTagsBuffer {
    Box::into_raw(Box::new(TSTagsBuffer {
        context: TagsContext::new(),
        tags: Vec::with_capacity(BUFFER_TAGS_RESERVE_CAPACITY),
        docs: Vec::with_capacity(BUFFER_DOCS_RESERVE_CAPACITY),
        errors_present: false,
    }))
}

/// Delete a [`TSTagsBuffer`].
///
/// # Safety
///
/// `this` must be non-null and a valid pointer to a [`TSTagsBuffer`] instance created by
/// [`ts_tags_buffer_new`].
#[no_mangle]
pub unsafe extern "C" fn ts_tags_buffer_delete(this: *mut TSTagsBuffer) {
    drop(Box::from_raw(this));
}

/// Get the tags from a [`TSTagsBuffer`].
///
/// # Safety
///
/// `this` must be non-null and a valid pointer to a [`TSTagsBuffer`] instance created by
/// [`ts_tags_buffer_new`].
///
/// The caller must ensure that the returned pointer is not used after the [`TSTagsBuffer`]
/// is deleted with [`ts_tags_buffer_delete`], else the data will point to garbage.
#[no_mangle]
pub unsafe extern "C" fn ts_tags_buffer_tags(this: *const TSTagsBuffer) -> *const TSTag {
    unwrap_ptr(this).tags.as_ptr()
}

/// Get the number of tags in a [`TSTagsBuffer`].
///
/// # Safety
///
/// `this` must be non-null and a valid pointer to a [`TSTagsBuffer`] instance.
#[no_mangle]
pub unsafe extern "C" fn ts_tags_buffer_tags_len(this: *const TSTagsBuffer) -> u32 {
    unwrap_ptr(this).tags.len() as u32
}

/// Get the documentation strings from a [`TSTagsBuffer`].
///
/// # Safety
///
/// `this` must be non-null and a valid pointer to a [`TSTagsBuffer`] instance created by
/// [`ts_tags_buffer_new`].
///
/// The caller must ensure that the returned pointer is not used after the [`TSTagsBuffer`]
/// is deleted with [`ts_tags_buffer_delete`], else the data will point to garbage.
///
/// The returned pointer points to a C-style string.
/// To get the length of the string, use [`ts_tags_buffer_docs_len`].
#[no_mangle]
pub unsafe extern "C" fn ts_tags_buffer_docs(this: *const TSTagsBuffer) -> *const c_char {
    unwrap_ptr(this).docs.as_ptr().cast::<c_char>()
}

/// Get the length of the documentation strings in a [`TSTagsBuffer`].
///
/// # Safety
///
/// `this` must be non-null and a valid pointer to a [`TSTagsBuffer`] instance created by
/// [`ts_tags_buffer_new`].
#[no_mangle]
pub unsafe extern "C" fn ts_tags_buffer_docs_len(this: *const TSTagsBuffer) -> u32 {
    unwrap_ptr(this).docs.len() as u32
}

/// Get whether or not a [`TSTagsBuffer`] contains any parse errors.
///
/// # Safety
///
/// `this` must be non-null and a valid pointer to a [`TSTagsBuffer`] instance created by
/// [`ts_tags_buffer_new`].
#[no_mangle]
pub unsafe extern "C" fn ts_tags_buffer_found_parse_error(this: *const TSTagsBuffer) -> bool {
    unwrap_ptr(this).errors_present
}

/// Get the syntax kinds for a given scope name.
///
/// Returns a pointer to a null-terminated array of null-terminated strings.
///
/// # Safety
///
/// `this` must be non-null and a valid pointer to a [`TSTagger`] instance created by
/// [`ts_tagger_new`].
/// `scope_name` must be non-null and a valid pointer to a null-terminated string.
/// `len` must be non-null and a valid pointer to a `u32`.
///
/// The caller must ensure that the returned pointer is not used after the [`TSTagger`]
/// is deleted with [`ts_tagger_delete`], else the data will point to garbage.
///
/// The returned pointer points to a C-style string array.
#[no_mangle]
pub unsafe extern "C" fn ts_tagger_syntax_kinds_for_scope_name(
    this: *mut TSTagger,
    scope_name: *const c_char,
    len: *mut u32,
) -> *const *const c_char {
    let tagger = unwrap_mut_ptr(this);
    let scope_name = unwrap(CStr::from_ptr(scope_name).to_str());
    let len = unwrap_mut_ptr(len);

    *len = 0;
    if let Some(config) = tagger.languages.get(scope_name) {
        *len = config.c_syntax_type_names.len() as u32;
        return config.c_syntax_type_names.as_ptr().cast::<*const c_char>();
    }
    std::ptr::null()
}

unsafe fn unwrap_ptr<'a, T>(result: *const T) -> &'a T {
    result.as_ref().unwrap_or_else(|| {
        eprintln!("{}:{} - pointer must not be null", file!(), line!());
        abort();
    })
}

unsafe fn unwrap_mut_ptr<'a, T>(result: *mut T) -> &'a mut T {
    result.as_mut().unwrap_or_else(|| {
        eprintln!("{}:{} - pointer must not be null", file!(), line!());
        abort();
    })
}

fn unwrap<T, E: fmt::Display>(result: Result<T, E>) -> T {
    result.unwrap_or_else(|error| {
        eprintln!("tree-sitter tag error: {error}");
        abort();
    })
}

fn shrink_and_clear<T>(vec: &mut Vec<T>, capacity: usize) {
    if vec.len() > capacity {
        vec.truncate(capacity);
        vec.shrink_to_fit();
    }
    vec.clear();
}
