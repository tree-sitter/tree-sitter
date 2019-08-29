mod ffi;
mod util;

#[macro_use]
extern crate serde_derive;
extern crate regex;
extern crate serde;
extern crate serde_json;

#[cfg(unix)]
use std::os::unix::io::AsRawFd;

use regex::Regex;
use serde::de::DeserializeOwned;
use std::collections::HashMap;
use std::ffi::CStr;
use std::marker::PhantomData;
use std::os::raw::{c_char, c_void};
use std::sync::atomic::AtomicUsize;
use std::{fmt, ptr, str, u16};

pub const LANGUAGE_VERSION: usize = ffi::TREE_SITTER_LANGUAGE_VERSION;
pub const PARSER_HEADER: &'static str = include_str!("../include/tree_sitter/parser.h");

#[derive(Clone, Copy, PartialEq, Eq)]
#[repr(transparent)]
pub struct Language(*const ffi::TSLanguage);

#[derive(Debug, PartialEq, Eq)]
pub struct LanguageError {
    version: usize,
}

#[derive(Debug, PartialEq, Eq)]
pub enum LogType {
    Parse,
    Lex,
}

type Logger<'a> = Box<dyn FnMut(LogType, &str) + 'a>;

#[derive(Clone, Copy, Debug, PartialEq, Eq, PartialOrd, Ord)]
pub struct Point {
    pub row: usize,
    pub column: usize,
}

#[derive(Clone, Copy, Debug, PartialEq, Eq, PartialOrd, Ord)]
pub struct Range {
    pub start_byte: usize,
    pub end_byte: usize,
    pub start_point: Point,
    pub end_point: Point,
}

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub struct InputEdit {
    pub start_byte: usize,
    pub old_end_byte: usize,
    pub new_end_byte: usize,
    pub start_position: Point,
    pub old_end_position: Point,
    pub new_end_position: Point,
}

struct PropertyTransition {
    state_id: u16,
    child_index: Option<u16>,
    text_regex_index: Option<u16>,
    node_kind_id: Option<u16>,
}

struct PropertyState {
    field_transitions: HashMap<u16, Vec<PropertyTransition>>,
    kind_transitions: HashMap<u16, Vec<PropertyTransition>>,
    property_set_id: usize,
    default_next_state_id: usize,
}

#[derive(Debug)]
pub enum PropertySheetError {
    InvalidJSON(serde_json::Error),
    InvalidRegex(regex::Error),
}

pub struct PropertySheet<P = HashMap<String, String>> {
    states: Vec<PropertyState>,
    property_sets: Vec<P>,
    text_regexes: Vec<Regex>,
}

#[derive(Clone, Debug, Deserialize, Serialize, Hash, PartialEq, Eq)]
pub struct PropertyTransitionJSON {
    #[serde(rename = "type")]
    #[serde(skip_serializing_if = "Option::is_none")]
    pub kind: Option<String>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub named: Option<bool>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub index: Option<usize>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub field: Option<String>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub text: Option<String>,
    pub state_id: usize,
}

#[derive(Debug, Default, Deserialize, Serialize, PartialEq, Eq)]
pub struct PropertyStateJSON {
    pub id: Option<usize>,
    pub property_set_id: usize,
    pub transitions: Vec<PropertyTransitionJSON>,
    pub default_next_state_id: usize,
}

#[derive(Debug, Deserialize, Serialize)]
pub struct PropertySheetJSON<P> {
    pub states: Vec<PropertyStateJSON>,
    pub property_sets: Vec<P>,
}

#[derive(Clone, Copy)]
pub struct Node<'a>(ffi::TSNode, PhantomData<&'a ()>);

pub struct Parser(*mut ffi::TSParser);

pub struct Tree(*mut ffi::TSTree);

pub struct TreeCursor<'a>(ffi::TSTreeCursor, PhantomData<&'a ()>);

pub struct TreePropertyCursor<'a, P> {
    cursor: TreeCursor<'a>,
    state_stack: Vec<usize>,
    child_index_stack: Vec<usize>,
    property_sheet: &'a PropertySheet<P>,
    source: &'a [u8],
}

impl Language {
    pub fn version(&self) -> usize {
        unsafe { ffi::ts_language_version(self.0) as usize }
    }

    pub fn node_kind_count(&self) -> usize {
        unsafe { ffi::ts_language_symbol_count(self.0) as usize }
    }

    pub fn node_kind_for_id(&self, id: u16) -> &'static str {
        unsafe { CStr::from_ptr(ffi::ts_language_symbol_name(self.0, id)) }
            .to_str()
            .unwrap()
    }

    pub fn node_kind_is_named(&self, id: u16) -> bool {
        unsafe { ffi::ts_language_symbol_type(self.0, id) == ffi::TSSymbolType_TSSymbolTypeRegular }
    }

    pub fn field_count(&self) -> usize {
        unsafe { ffi::ts_language_field_count(self.0) as usize }
    }

    pub fn field_name_for_id(&self, field_id: u16) -> &'static str {
        unsafe { CStr::from_ptr(ffi::ts_language_field_name_for_id(self.0, field_id)) }
            .to_str()
            .unwrap()
    }

    pub fn field_id_for_name(&self, field_name: impl AsRef<[u8]>) -> Option<u16> {
        let field_name = field_name.as_ref();
        let id = unsafe {
            ffi::ts_language_field_id_for_name(
                self.0,
                field_name.as_ptr() as *const c_char,
                field_name.len() as u32,
            )
        };
        if id == 0 {
            None
        } else {
            Some(id)
        }
    }
}

impl fmt::Display for LanguageError {
    fn fmt(&self, f: &mut fmt::Formatter) -> Result<(), fmt::Error> {
        write!(
            f,
            "Incompatible language version {}. Expected minimum {}, maximum {}",
            self.version,
            ffi::TREE_SITTER_MIN_COMPATIBLE_LANGUAGE_VERSION,
            ffi::TREE_SITTER_LANGUAGE_VERSION
        )
    }
}

unsafe impl Send for Language {}

unsafe impl Sync for Language {}

impl Parser {
    pub fn new() -> Parser {
        unsafe {
            let parser = ffi::ts_parser_new();
            Parser(parser)
        }
    }

    pub fn set_language(&mut self, language: Language) -> Result<(), LanguageError> {
        let version = language.version();
        if version < ffi::TREE_SITTER_MIN_COMPATIBLE_LANGUAGE_VERSION
            || version > ffi::TREE_SITTER_LANGUAGE_VERSION
        {
            Err(LanguageError { version })
        } else {
            unsafe {
                ffi::ts_parser_set_language(self.0, language.0);
            }
            Ok(())
        }
    }

    pub fn language(&self) -> Option<Language> {
        let ptr = unsafe { ffi::ts_parser_language(self.0) };
        if ptr.is_null() {
            None
        } else {
            Some(Language(ptr))
        }
    }

    pub fn logger(&self) -> Option<&Logger> {
        let logger = unsafe { ffi::ts_parser_logger(self.0) };
        unsafe { (logger.payload as *mut Logger).as_ref() }
    }

    pub fn set_logger(&mut self, logger: Option<Logger>) {
        let prev_logger = unsafe { ffi::ts_parser_logger(self.0) };
        if !prev_logger.payload.is_null() {
            unsafe { Box::from_raw(prev_logger.payload as *mut Logger) };
        }

        let c_logger;
        if let Some(logger) = logger {
            let container = Box::new(logger);

            unsafe extern "C" fn log(
                payload: *mut c_void,
                c_log_type: ffi::TSLogType,
                c_message: *const c_char,
            ) {
                let callback = (payload as *mut Logger).as_mut().unwrap();
                if let Ok(message) = CStr::from_ptr(c_message).to_str() {
                    let log_type = if c_log_type == ffi::TSLogType_TSLogTypeParse {
                        LogType::Parse
                    } else {
                        LogType::Lex
                    };
                    callback(log_type, message);
                }
            };

            let raw_container = Box::into_raw(container);

            c_logger = ffi::TSLogger {
                payload: raw_container as *mut c_void,
                log: Some(log),
            };
        } else {
            c_logger = ffi::TSLogger {
                payload: ptr::null_mut(),
                log: None,
            };
        }

        unsafe { ffi::ts_parser_set_logger(self.0, c_logger) };
    }

    #[cfg(unix)]
    pub fn print_dot_graphs(&mut self, file: &impl AsRawFd) {
        let fd = file.as_raw_fd();
        unsafe { ffi::ts_parser_print_dot_graphs(self.0, ffi::dup(fd)) }
    }

    pub fn stop_printing_dot_graphs(&mut self) {
        unsafe { ffi::ts_parser_print_dot_graphs(self.0, -1) }
    }

    /// Parse a slice of UTF8 text.
    ///
    /// # Arguments:
    /// * `text` The UTF8-encoded text to parse.
    /// * `old_tree` A previous syntax tree parsed from the same document.
    ///   If the text of the document has changed since `old_tree` was
    ///   created, then you must edit `old_tree` to match the new text using
    ///   [Tree::edit].
    ///
    /// Returns a [Tree] if parsing succeeded, or `None` if:
    ///  * The parser has not yet had a language assigned with [Parser::set_language]
    ///  * The timeout set with [Parser::set_timeout_micros] expired
    ///  * The cancellation flag set with [Parser::set_cancellation_flag] was flipped
    pub fn parse(&mut self, text: impl AsRef<[u8]>, old_tree: Option<&Tree>) -> Option<Tree> {
        let bytes = text.as_ref();
        let len = bytes.len();
        self.parse_with(
            &mut |i, _| if i < len { &bytes[i..] } else { &[] },
            old_tree,
        )
    }

    /// Parse a slice UTF16 text.
    ///
    /// # Arguments:
    /// * `text` The UTF16-encoded text to parse.
    /// * `old_tree` A previous syntax tree parsed from the same document.
    ///   If the text of the document has changed since `old_tree` was
    ///   created, then you must edit `old_tree` to match the new text using
    ///   [Tree::edit].
    pub fn parse_utf16(
        &mut self,
        input: impl AsRef<[u16]>,
        old_tree: Option<&Tree>,
    ) -> Option<Tree> {
        let code_points = input.as_ref();
        let len = code_points.len();
        self.parse_utf16_with(
            &mut |i, _| if i < len { &code_points[i..] } else { &[] },
            old_tree,
        )
    }

    /// Parse UTF8 text provided in chunks by a callback.
    ///
    /// # Arguments:
    /// * `callback` A function that takes a byte offset and position and
    ///   returns a slice of UTF8-encoded text starting at that byte offset
    ///   and position. The slices can be of any length. If the given position
    ///   is at the end of the text, the callback should return an empty slice.
    /// * `old_tree` A previous syntax tree parsed from the same document.
    ///   If the text of the document has changed since `old_tree` was
    ///   created, then you must edit `old_tree` to match the new text using
    ///   [Tree::edit].
    pub fn parse_with<'a, T: AsRef<[u8]>, F: FnMut(usize, Point) -> T>(
        &mut self,
        callback: &mut F,
        old_tree: Option<&Tree>,
    ) -> Option<Tree> {
        // A pointer to this payload is passed on every call to the `read` C function.
        // The payload contains two things:
        // 1. A reference to the rust `callback`.
        // 2. The text that was returned from the previous call to `callback`.
        //    This allows the callback to return owned values like vectors.
        let mut payload: (&mut F, Option<T>) = (callback, None);

        // This C function is passed to Tree-sitter as the input callback.
        unsafe extern "C" fn read<'a, T: AsRef<[u8]>, F: FnMut(usize, Point) -> T>(
            payload: *mut c_void,
            byte_offset: u32,
            position: ffi::TSPoint,
            bytes_read: *mut u32,
        ) -> *const c_char {
            let (callback, text) = (payload as *mut (&mut F, Option<T>)).as_mut().unwrap();
            *text = Some(callback(byte_offset as usize, position.into()));
            let slice = text.as_ref().unwrap().as_ref();
            *bytes_read = slice.len() as u32;
            return slice.as_ptr() as *const c_char;
        };

        let c_input = ffi::TSInput {
            payload: &mut payload as *mut (&mut F, Option<T>) as *mut c_void,
            read: Some(read::<T, F>),
            encoding: ffi::TSInputEncoding_TSInputEncodingUTF8,
        };

        let c_old_tree = old_tree.map_or(ptr::null_mut(), |t| t.0);
        let c_new_tree = unsafe { ffi::ts_parser_parse(self.0, c_old_tree, c_input) };
        if c_new_tree.is_null() {
            None
        } else {
            Some(Tree(c_new_tree))
        }
    }

    /// Parse UTF16 text provided in chunks by a callback.
    ///
    /// # Arguments:
    /// * `callback` A function that takes a code point offset and position and
    ///   returns a slice of UTF16-encoded text starting at that byte offset
    ///   and position. The slices can be of any length. If the given position
    ///   is at the end of the text, the callback should return an empty slice.
    /// * `old_tree` A previous syntax tree parsed from the same document.
    ///   If the text of the document has changed since `old_tree` was
    ///   created, then you must edit `old_tree` to match the new text using
    ///   [Tree::edit].
    pub fn parse_utf16_with<'a, T: AsRef<[u16]>, F: FnMut(usize, Point) -> T>(
        &mut self,
        callback: &mut F,
        old_tree: Option<&Tree>,
    ) -> Option<Tree> {
        // A pointer to this payload is passed on every call to the `read` C function.
        // The payload contains two things:
        // 1. A reference to the rust `callback`.
        // 2. The text that was returned from the previous call to `callback`.
        //    This allows the callback to return owned values like vectors.
        let mut payload: (&mut F, Option<T>) = (callback, None);

        // This C function is passed to Tree-sitter as the input callback.
        unsafe extern "C" fn read<'a, T: AsRef<[u16]>, F: FnMut(usize, Point) -> T>(
            payload: *mut c_void,
            byte_offset: u32,
            position: ffi::TSPoint,
            bytes_read: *mut u32,
        ) -> *const c_char {
            let (callback, text) = (payload as *mut (&mut F, Option<T>)).as_mut().unwrap();
            *text = Some(callback(
                (byte_offset / 2) as usize,
                Point {
                    row: position.row as usize,
                    column: position.column as usize / 2,
                },
            ));
            let slice = text.as_ref().unwrap().as_ref();
            *bytes_read = slice.len() as u32 * 2;
            slice.as_ptr() as *const c_char
        };

        let c_input = ffi::TSInput {
            payload: &mut payload as *mut (&mut F, Option<T>) as *mut c_void,
            read: Some(read::<T, F>),
            encoding: ffi::TSInputEncoding_TSInputEncodingUTF16,
        };

        let c_old_tree = old_tree.map_or(ptr::null_mut(), |t| t.0);
        let c_new_tree = unsafe { ffi::ts_parser_parse(self.0, c_old_tree, c_input) };
        if c_new_tree.is_null() {
            None
        } else {
            Some(Tree(c_new_tree))
        }
    }

    pub fn reset(&mut self) {
        unsafe { ffi::ts_parser_reset(self.0) }
    }

    pub fn timeout_micros(&self) -> u64 {
        unsafe { ffi::ts_parser_timeout_micros(self.0) }
    }

    pub fn set_timeout_micros(&mut self, timeout_micros: u64) {
        unsafe { ffi::ts_parser_set_timeout_micros(self.0, timeout_micros) }
    }

    pub fn set_included_ranges(&mut self, ranges: &[Range]) {
        let ts_ranges: Vec<ffi::TSRange> =
            ranges.iter().cloned().map(|range| range.into()).collect();
        unsafe {
            ffi::ts_parser_set_included_ranges(self.0, ts_ranges.as_ptr(), ts_ranges.len() as u32)
        };
    }

    pub unsafe fn cancellation_flag(&self) -> Option<&AtomicUsize> {
        (ffi::ts_parser_cancellation_flag(self.0) as *const AtomicUsize).as_ref()
    }

    pub unsafe fn set_cancellation_flag(&self, flag: Option<&AtomicUsize>) {
        if let Some(flag) = flag {
            ffi::ts_parser_set_cancellation_flag(
                self.0,
                flag as *const AtomicUsize as *const usize,
            );
        } else {
            ffi::ts_parser_set_cancellation_flag(self.0, ptr::null());
        }
    }
}

impl Drop for Parser {
    fn drop(&mut self) {
        self.stop_printing_dot_graphs();
        self.set_logger(None);
        unsafe { ffi::ts_parser_delete(self.0) }
    }
}

unsafe impl Send for Parser {}

impl Tree {
    pub fn root_node(&self) -> Node {
        Node::new(unsafe { ffi::ts_tree_root_node(self.0) }).unwrap()
    }

    pub fn language(&self) -> Language {
        Language(unsafe { ffi::ts_tree_language(self.0) })
    }

    pub fn edit(&mut self, edit: &InputEdit) {
        let edit = edit.into();
        unsafe { ffi::ts_tree_edit(self.0, &edit) };
    }

    pub fn walk(&self) -> TreeCursor {
        self.root_node().walk()
    }

    pub fn walk_with_properties<'a, P>(
        &'a self,
        property_sheet: &'a PropertySheet<P>,
        source: &'a [u8],
    ) -> TreePropertyCursor<'a, P> {
        TreePropertyCursor::new(self, property_sheet, source)
    }

    pub fn changed_ranges(&self, other: &Tree) -> impl ExactSizeIterator<Item = Range> {
        let mut count = 0;
        unsafe {
            let ptr =
                ffi::ts_tree_get_changed_ranges(self.0, other.0, &mut count as *mut _ as *mut u32);
            util::CBufferIter::new(ptr, count).map(|r| r.into())
        }
    }
}

unsafe impl Send for Tree {}

impl fmt::Debug for Tree {
    fn fmt(&self, f: &mut fmt::Formatter) -> Result<(), fmt::Error> {
        write!(f, "{{Tree {:?}}}", self.root_node())
    }
}

impl Drop for Tree {
    fn drop(&mut self) {
        unsafe { ffi::ts_tree_delete(self.0) }
    }
}

impl Clone for Tree {
    fn clone(&self) -> Tree {
        unsafe { Tree(ffi::ts_tree_copy(self.0)) }
    }
}

impl<'tree> Node<'tree> {
    fn new(node: ffi::TSNode) -> Option<Self> {
        if node.id.is_null() {
            None
        } else {
            Some(Node(node, PhantomData))
        }
    }

    pub fn kind_id(&self) -> u16 {
        unsafe { ffi::ts_node_symbol(self.0) }
    }

    pub fn kind(&self) -> &'static str {
        unsafe { CStr::from_ptr(ffi::ts_node_type(self.0)) }
            .to_str()
            .unwrap()
    }

    pub fn is_named(&self) -> bool {
        unsafe { ffi::ts_node_is_named(self.0) }
    }

    pub fn is_extra(&self) -> bool {
        unsafe { ffi::ts_node_is_extra(self.0) }
    }

    pub fn has_changes(&self) -> bool {
        unsafe { ffi::ts_node_has_changes(self.0) }
    }

    pub fn has_error(&self) -> bool {
        unsafe { ffi::ts_node_has_error(self.0) }
    }

    pub fn is_error(&self) -> bool {
        self.kind_id() == u16::MAX
    }

    pub fn is_missing(&self) -> bool {
        unsafe { ffi::ts_node_is_missing(self.0) }
    }

    pub fn start_byte(&self) -> usize {
        unsafe { ffi::ts_node_start_byte(self.0) as usize }
    }

    pub fn end_byte(&self) -> usize {
        unsafe { ffi::ts_node_end_byte(self.0) as usize }
    }

    pub fn range(&self) -> Range {
        Range {
            start_byte: self.start_byte(),
            end_byte: self.end_byte(),
            start_point: self.start_position(),
            end_point: self.end_position(),
        }
    }

    pub fn start_position(&self) -> Point {
        let result = unsafe { ffi::ts_node_start_point(self.0) };
        result.into()
    }

    pub fn end_position(&self) -> Point {
        let result = unsafe { ffi::ts_node_end_point(self.0) };
        result.into()
    }

    pub fn child(&self, i: usize) -> Option<Self> {
        Self::new(unsafe { ffi::ts_node_child(self.0, i as u32) })
    }

    pub fn child_by_field_name(&self, field_name: impl AsRef<[u8]>) -> Option<Self> {
        let field_name = field_name.as_ref();
        Self::new(unsafe {
            ffi::ts_node_child_by_field_name(
                self.0,
                field_name.as_ptr() as *const c_char,
                field_name.len() as u32,
            )
        })
    }

    pub fn child_by_field_id(&self, field_id: u16) -> Option<Self> {
        Self::new(unsafe { ffi::ts_node_child_by_field_id(self.0, field_id) })
    }

    pub fn child_count(&self) -> usize {
        unsafe { ffi::ts_node_child_count(self.0) as usize }
    }

    pub fn children(&self) -> impl ExactSizeIterator<Item = Node<'tree>> {
        let me = self.clone();
        (0..self.child_count())
            .into_iter()
            .map(move |i| me.child(i).unwrap())
    }

    pub fn named_child<'a>(&'a self, i: usize) -> Option<Self> {
        Self::new(unsafe { ffi::ts_node_named_child(self.0, i as u32) })
    }

    pub fn named_child_count(&self) -> usize {
        unsafe { ffi::ts_node_named_child_count(self.0) as usize }
    }

    pub fn parent(&self) -> Option<Self> {
        Self::new(unsafe { ffi::ts_node_parent(self.0) })
    }

    pub fn next_sibling(&self) -> Option<Self> {
        Self::new(unsafe { ffi::ts_node_next_sibling(self.0) })
    }

    pub fn prev_sibling(&self) -> Option<Self> {
        Self::new(unsafe { ffi::ts_node_prev_sibling(self.0) })
    }

    pub fn next_named_sibling(&self) -> Option<Self> {
        Self::new(unsafe { ffi::ts_node_next_named_sibling(self.0) })
    }

    pub fn prev_named_sibling(&self) -> Option<Self> {
        Self::new(unsafe { ffi::ts_node_prev_named_sibling(self.0) })
    }

    pub fn descendant_for_byte_range(&self, start: usize, end: usize) -> Option<Self> {
        Self::new(unsafe {
            ffi::ts_node_descendant_for_byte_range(self.0, start as u32, end as u32)
        })
    }

    pub fn named_descendant_for_byte_range(&self, start: usize, end: usize) -> Option<Self> {
        Self::new(unsafe {
            ffi::ts_node_named_descendant_for_byte_range(self.0, start as u32, end as u32)
        })
    }

    pub fn descendant_for_point_range(&self, start: Point, end: Point) -> Option<Self> {
        Self::new(unsafe {
            ffi::ts_node_descendant_for_point_range(self.0, start.into(), end.into())
        })
    }

    pub fn named_descendant_for_point_range(&self, start: Point, end: Point) -> Option<Self> {
        Self::new(unsafe {
            ffi::ts_node_named_descendant_for_point_range(self.0, start.into(), end.into())
        })
    }

    pub fn to_sexp(&self) -> String {
        let c_string = unsafe { ffi::ts_node_string(self.0) };
        let result = unsafe { CStr::from_ptr(c_string) }
            .to_str()
            .unwrap()
            .to_string();
        unsafe { util::free_ptr(c_string as *mut c_void) };
        result
    }

    pub fn utf8_text<'a>(&self, source: &'a [u8]) -> Result<&'a str, str::Utf8Error> {
        str::from_utf8(&source[self.start_byte()..self.end_byte()])
    }

    pub fn utf16_text<'a>(&self, source: &'a [u16]) -> &'a [u16] {
        &source.as_ref()[self.start_byte()..self.end_byte()]
    }

    pub fn walk(&self) -> TreeCursor<'tree> {
        TreeCursor(unsafe { ffi::ts_tree_cursor_new(self.0) }, PhantomData)
    }

    pub fn edit(&mut self, edit: &InputEdit) {
        let edit = edit.into();
        unsafe { ffi::ts_node_edit(&mut self.0 as *mut ffi::TSNode, &edit) }
    }
}

impl<'a> PartialEq for Node<'a> {
    fn eq(&self, other: &Self) -> bool {
        self.0.id == other.0.id
    }
}

impl<'a> fmt::Debug for Node<'a> {
    fn fmt(&self, f: &mut fmt::Formatter) -> Result<(), fmt::Error> {
        write!(
            f,
            "{{Node {} {} - {}}}",
            self.kind(),
            self.start_position(),
            self.end_position()
        )
    }
}

impl<'a> TreeCursor<'a> {
    pub fn node(&self) -> Node<'a> {
        Node(
            unsafe { ffi::ts_tree_cursor_current_node(&self.0) },
            PhantomData,
        )
    }

    pub fn field_id(&self) -> Option<u16> {
        unsafe {
            let id = ffi::ts_tree_cursor_current_field_id(&self.0);
            if id == 0 {
                None
            } else {
                Some(id)
            }
        }
    }

    pub fn field_name(&self) -> Option<&str> {
        unsafe {
            let ptr = ffi::ts_tree_cursor_current_field_name(&self.0);
            if ptr.is_null() {
                None
            } else {
                Some(CStr::from_ptr(ptr).to_str().unwrap())
            }
        }
    }

    pub fn goto_first_child(&mut self) -> bool {
        return unsafe { ffi::ts_tree_cursor_goto_first_child(&mut self.0) };
    }

    pub fn goto_parent(&mut self) -> bool {
        return unsafe { ffi::ts_tree_cursor_goto_parent(&mut self.0) };
    }

    pub fn goto_next_sibling(&mut self) -> bool {
        return unsafe { ffi::ts_tree_cursor_goto_next_sibling(&mut self.0) };
    }

    pub fn goto_first_child_for_index(&mut self, index: usize) -> Option<usize> {
        let result =
            unsafe { ffi::ts_tree_cursor_goto_first_child_for_byte(&mut self.0, index as u32) };
        if result < 0 {
            None
        } else {
            Some(result as usize)
        }
    }

    pub fn reset(&mut self, node: Node<'a>) {
        unsafe { ffi::ts_tree_cursor_reset(&mut self.0, node.0) };
    }
}

impl<'a> Drop for TreeCursor<'a> {
    fn drop(&mut self) {
        unsafe { ffi::ts_tree_cursor_delete(&mut self.0) }
    }
}

impl<'a, P> TreePropertyCursor<'a, P> {
    fn new(tree: &'a Tree, property_sheet: &'a PropertySheet<P>, source: &'a [u8]) -> Self {
        let mut result = Self {
            cursor: tree.root_node().walk(),
            child_index_stack: vec![0],
            state_stack: vec![0],
            property_sheet,
            source,
        };
        let state = result.next_state(0);
        result.state_stack.push(state);
        result
    }

    pub fn node(&self) -> Node<'a> {
        self.cursor.node()
    }

    pub fn node_properties(&self) -> &'a P {
        &self.property_sheet.property_sets[self.current_state().property_set_id]
    }

    pub fn goto_first_child(&mut self) -> bool {
        if self.cursor.goto_first_child() {
            let next_state_id = self.next_state(0);
            self.state_stack.push(next_state_id);
            self.child_index_stack.push(0);
            true
        } else {
            false
        }
    }

    pub fn goto_next_sibling(&mut self) -> bool {
        if self.cursor.goto_next_sibling() {
            let child_index = self.child_index_stack.pop().unwrap() + 1;
            self.state_stack.pop();
            let next_state_id = self.next_state(child_index);
            self.state_stack.push(next_state_id);
            self.child_index_stack.push(child_index);
            true
        } else {
            false
        }
    }

    pub fn goto_parent(&mut self) -> bool {
        if self.cursor.goto_parent() {
            self.state_stack.pop();
            self.child_index_stack.pop();
            true
        } else {
            false
        }
    }

    pub fn source(&self) -> &'a [u8] {
        &self.source
    }

    fn next_state(&self, node_child_index: usize) -> usize {
        let current_state = self.current_state();
        let default_state = self.default_state();

        for state in [current_state, default_state].iter() {
            let node_field_id = self.cursor.field_id();
            let node_kind_id = self.cursor.node().kind_id();
            let transitions = node_field_id
                .and_then(|field_id| state.field_transitions.get(&field_id))
                .or_else(|| state.kind_transitions.get(&node_kind_id));

            if let Some(transitions) = transitions {
                for transition in transitions.iter() {
                    if transition
                        .node_kind_id
                        .map_or(false, |id| id != node_kind_id)
                    {
                        continue;
                    }

                    if let Some(text_regex_index) = transition.text_regex_index {
                        let node = self.cursor.node();
                        let text = &self.source[node.start_byte()..node.end_byte()];
                        if let Ok(text) = str::from_utf8(text) {
                            if !self.property_sheet.text_regexes[text_regex_index as usize]
                                .is_match(text)
                            {
                                continue;
                            }
                        }
                    }

                    if let Some(child_index) = transition.child_index {
                        if child_index != node_child_index as u16 {
                            continue;
                        }
                    }

                    return transition.state_id as usize;
                }
            }

            if current_state as *const PropertyState == default_state as *const PropertyState {
                break;
            }
        }

        current_state.default_next_state_id
    }

    fn current_state(&self) -> &PropertyState {
        &self.property_sheet.states[*self.state_stack.last().unwrap()]
    }

    fn default_state(&self) -> &PropertyState {
        &self.property_sheet.states.first().unwrap()
    }
}

impl Point {
    pub fn new(row: usize, column: usize) -> Self {
        Point { row, column }
    }
}

impl fmt::Display for Point {
    fn fmt(&self, f: &mut fmt::Formatter) -> Result<(), fmt::Error> {
        write!(f, "({}, {})", self.row, self.column)
    }
}

impl Into<ffi::TSPoint> for Point {
    fn into(self) -> ffi::TSPoint {
        ffi::TSPoint {
            row: self.row as u32,
            column: self.column as u32,
        }
    }
}

impl From<ffi::TSPoint> for Point {
    fn from(point: ffi::TSPoint) -> Self {
        Self {
            row: point.row as usize,
            column: point.column as usize,
        }
    }
}

impl Into<ffi::TSRange> for Range {
    fn into(self) -> ffi::TSRange {
        ffi::TSRange {
            start_byte: self.start_byte as u32,
            end_byte: self.end_byte as u32,
            start_point: self.start_point.into(),
            end_point: self.end_point.into(),
        }
    }
}

impl From<ffi::TSRange> for Range {
    fn from(range: ffi::TSRange) -> Self {
        Self {
            start_byte: range.start_byte as usize,
            end_byte: range.end_byte as usize,
            start_point: range.start_point.into(),
            end_point: range.end_point.into(),
        }
    }
}

impl<'a> Into<ffi::TSInputEdit> for &'a InputEdit {
    fn into(self) -> ffi::TSInputEdit {
        ffi::TSInputEdit {
            start_byte: self.start_byte as u32,
            old_end_byte: self.old_end_byte as u32,
            new_end_byte: self.new_end_byte as u32,
            start_point: self.start_position.into(),
            old_end_point: self.old_end_position.into(),
            new_end_point: self.new_end_position.into(),
        }
    }
}

impl<P> PropertySheet<P> {
    pub fn new(language: Language, json: &str) -> Result<Self, PropertySheetError>
    where
        P: DeserializeOwned,
    {
        let input: PropertySheetJSON<P> =
            serde_json::from_str(json).map_err(PropertySheetError::InvalidJSON)?;
        let mut states = Vec::new();
        let mut text_regexes = Vec::new();
        let mut text_regex_patterns = Vec::new();

        for state in input.states.iter() {
            let node_kind_count = language.node_kind_count();
            let mut kind_transitions = HashMap::new();
            let mut field_transitions = HashMap::new();

            for transition in state.transitions.iter() {
                let field_id = transition
                    .field
                    .as_ref()
                    .and_then(|field| language.field_id_for_name(&field));
                if let Some(field_id) = field_id {
                    field_transitions.entry(field_id).or_insert(Vec::new());
                }
            }

            for transition in state.transitions.iter() {
                let text_regex_index = if let Some(regex_pattern) = transition.text.as_ref() {
                    if let Some(index) =
                        text_regex_patterns.iter().position(|r| *r == regex_pattern)
                    {
                        Some(index as u16)
                    } else {
                        text_regex_patterns.push(regex_pattern);
                        text_regexes.push(
                            Regex::new(&regex_pattern).map_err(PropertySheetError::InvalidRegex)?,
                        );
                        Some(text_regexes.len() as u16 - 1)
                    }
                } else {
                    None
                };

                let state_id = transition.state_id as u16;
                let child_index = transition.index.map(|i| i as u16);
                let field_id = transition
                    .field
                    .as_ref()
                    .and_then(|field| language.field_id_for_name(&field));

                if let Some(kind) = transition.kind.as_ref() {
                    for kind_id in 0..(node_kind_count as u16) {
                        if kind != language.node_kind_for_id(kind_id)
                            || transition.named != Some(language.node_kind_is_named(kind_id))
                        {
                            continue;
                        }

                        if let Some(field_id) = field_id {
                            field_transitions
                                .entry(field_id)
                                .or_insert(Vec::new())
                                .push(PropertyTransition {
                                    node_kind_id: Some(kind_id),
                                    state_id,
                                    child_index,
                                    text_regex_index,
                                });
                        } else {
                            for (_, entries) in field_transitions.iter_mut() {
                                entries.push(PropertyTransition {
                                    node_kind_id: Some(kind_id),
                                    state_id,
                                    child_index,
                                    text_regex_index,
                                });
                            }

                            kind_transitions.entry(kind_id).or_insert(Vec::new()).push(
                                PropertyTransition {
                                    node_kind_id: None,
                                    state_id,
                                    child_index,
                                    text_regex_index,
                                },
                            );
                        }
                    }
                } else if let Some(field_id) = field_id {
                    field_transitions
                        .entry(field_id)
                        .or_insert(Vec::new())
                        .push(PropertyTransition {
                            node_kind_id: None,
                            state_id,
                            child_index,
                            text_regex_index,
                        });
                }
            }
            states.push(PropertyState {
                field_transitions,
                kind_transitions,
                default_next_state_id: state.default_next_state_id,
                property_set_id: state.property_set_id,
            });
        }
        Ok(Self {
            property_sets: input.property_sets,
            states,
            text_regexes,
        })
    }

    pub fn map<F, T, E>(self, mut f: F) -> Result<PropertySheet<T>, E>
    where
        F: FnMut(P) -> Result<T, E>,
    {
        let mut property_sets = Vec::with_capacity(self.property_sets.len());
        for set in self.property_sets {
            property_sets.push(f(set)?);
        }
        Ok(PropertySheet {
            states: self.states,
            text_regexes: self.text_regexes,
            property_sets,
        })
    }
}

impl fmt::Display for PropertySheetError {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        match self {
            PropertySheetError::InvalidJSON(e) => write!(f, "Invalid JSON: {}", e),
            PropertySheetError::InvalidRegex(e) => write!(f, "Invalid Regex: {}", e),
        }
    }
}

impl std::error::Error for PropertySheetError {
    fn source(&self) -> Option<&(dyn std::error::Error + 'static)> {
        match self {
            PropertySheetError::InvalidJSON(e) => Some(e),
            PropertySheetError::InvalidRegex(e) => Some(e),
        }
    }
}
