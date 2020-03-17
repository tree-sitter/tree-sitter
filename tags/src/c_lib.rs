use super::{Error, TagKind, TagsConfiguration, TagsContext};
use std::collections::HashMap;
use std::ffi::CStr;
use std::process::abort;
use std::{fmt, slice, str};
use tree_sitter::Language;

#[repr(C)]
enum TSTagsError {
    Ok,
    UnknownScope,
    Timeout,
    InvalidLanguage,
    InvalidUtf8,
    InvalidRegex,
    InvalidQuery,
}

#[repr(C)]
enum TSTagKind {
    Function,
    Method,
    Class,
    Module,
    Call,
}

#[repr(C)]
struct TSPoint {
    row: u32,
    column: u32,
}

#[repr(C)]
struct TSTag {
    kind: TSTagKind,
    start_byte: u32,
    end_byte: u32,
    name_start_byte: u32,
    name_end_byte: u32,
    line_start_byte: u32,
    line_end_byte: u32,
    start_point: TSPoint,
    end_point: TSPoint,
    docs: *const u8,
    docs_length: u32,
}

struct TSTagger {
    languages: HashMap<String, TagsConfiguration>,
}

struct TSTagsBuffer {
    context: TagsContext,
    tags: Vec<TSTag>,
    docs: Vec<u8>,
}

#[no_mangle]
unsafe extern "C" fn ts_tagger_add_language(
    this: *mut TSTagger,
    scope_name: *const i8,
    language: Language,
    tags_query: *const u8,
    locals_query: *const u8,
    tags_query_len: u32,
    locals_query_len: u32,
) -> TSTagsError {
    let tagger = unwrap_mut_ptr(this);
    let scope_name = unwrap(CStr::from_ptr(scope_name).to_str());
    let tags_query = slice::from_raw_parts(tags_query, tags_query_len as usize);
    let locals_query = slice::from_raw_parts(locals_query, locals_query_len as usize);
    let tags_query = match str::from_utf8(tags_query) {
        Ok(e) => e,
        Err(_) => return TSTagsError::InvalidUtf8,
    };
    let locals_query = match str::from_utf8(locals_query) {
        Ok(e) => e,
        Err(_) => return TSTagsError::InvalidUtf8,
    };
    match TagsConfiguration::new(language, tags_query, locals_query) {
        Ok(c) => {
            tagger.languages.insert(scope_name.to_string(), c);
            TSTagsError::Ok
        }
        Err(Error::Query(_)) => TSTagsError::InvalidQuery,
        Err(Error::Regex(_)) => TSTagsError::InvalidRegex,
    }
}

#[no_mangle]
unsafe extern "C" fn ts_tagger_tag(
    this: *mut TSTagger,
    scope_name: *const i8,
    source_code: *const u8,
    source_code_len: u32,
    output: *mut TSTagsBuffer,
    cancellation_flag: *const usize,
) -> TSTagsError {
    let tagger = unwrap_mut_ptr(this);
    let buffer = unwrap_mut_ptr(output);
    let scope_name = unwrap(CStr::from_ptr(scope_name).to_str());
    if let Some(config) = tagger.languages.get(scope_name) {
        let source_code = slice::from_raw_parts(source_code, source_code_len as usize);
        for tag in buffer.context.generate_tags(config, source_code) {
            let prev_docs_len = buffer.docs.len();
            if let Some(docs) = tag.docs {
                buffer.docs.extend_from_slice(docs.as_bytes());
            }
            let docs = &buffer.docs[prev_docs_len..];
            buffer.tags.push(TSTag {
                kind: match tag.kind {
                    TagKind::Function => TSTagKind::Function,
                    TagKind::Method => TSTagKind::Method,
                    TagKind::Class => TSTagKind::Class,
                    TagKind::Module => TSTagKind::Module,
                    TagKind::Call => TSTagKind::Call,
                },
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
                docs: docs.as_ptr(),
                docs_length: docs.len() as u32,
            });
        }
        TSTagsError::Ok
    } else {
        TSTagsError::UnknownScope
    }
}

#[no_mangle]
extern "C" fn ts_tags_buffer_new() -> *mut TSTagsBuffer {
    Box::into_raw(Box::new(TSTagsBuffer {
        context: TagsContext::new(),
        tags: Vec::new(),
        docs: Vec::new(),
    }))
}

#[no_mangle]
extern "C" fn ts_tags_buffer_delete(this: *mut TSTagsBuffer) {
    drop(unsafe { Box::from_raw(this) })
}

#[no_mangle]
extern "C" fn ts_tags_buffer_line_offsets(this: *const TSTagsBuffer) -> *const TSTag {
    let buffer = unwrap_ptr(this);
    buffer.tags.as_ptr()
}

#[no_mangle]
extern "C" fn ts_tags_buffer_len(this: *const TSTagsBuffer) -> u32 {
    let buffer = unwrap_ptr(this);
    buffer.tags.len() as u32
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
        eprintln!("tree-sitter tag error: {}", error);
        abort();
    })
}
