mod ffi;

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
use std::fmt;
use std::marker::PhantomData;
use std::os::raw::{c_char, c_void};
use std::ptr;
use std::slice;
use std::str;
use std::u16;

pub const PARSER_HEADER: &'static str = include_str!("../include/tree_sitter/parser.h");

#[derive(Clone, Copy)]
#[repr(transparent)]
pub struct Language(*const ffi::TSLanguage);

#[derive(Debug, PartialEq, Eq)]
pub enum LogType {
    Parse,
    Lex,
}

type Logger<'a> = Box<FnMut(LogType, &str) + 'a>;

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
    state_id: usize,
    child_index: Option<usize>,
    text_regex_index: Option<usize>,
}

struct PropertyState {
    transitions: HashMap<u16, Vec<PropertyTransition>>,
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

#[derive(Debug, Deserialize, Serialize, Hash, PartialEq, Eq)]
pub struct PropertyTransitionJSON {
    #[serde(rename = "type")]
    pub kind: String,
    pub named: bool,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub index: Option<usize>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub text: Option<String>,
    pub state_id: usize,
}

#[derive(Debug, Deserialize, Serialize, PartialEq, Eq)]
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

    pub fn set_language(&mut self, language: Language) -> Result<(), String> {
        unsafe {
            let version = ffi::ts_language_version(language.0) as usize;
            if version == ffi::TREE_SITTER_LANGUAGE_VERSION {
                ffi::ts_parser_set_language(self.0, language.0);
                Ok(())
            } else {
                Err(format!(
                    "Incompatible language version {}. Expected {}.",
                    version,
                    ffi::TREE_SITTER_LANGUAGE_VERSION
                ))
            }
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

    pub fn parse(&mut self, input: impl AsRef<[u8]>, old_tree: Option<&Tree>) -> Option<Tree> {
        let bytes = input.as_ref();
        let len = bytes.len();
        self.parse_with(&mut |i, _| if i < len { &bytes[i..] } else { &[] }, old_tree)
    }

    pub fn parse_utf16(
        &mut self,
        input: impl AsRef<[u16]>,
        old_tree: Option<&Tree>,
    ) -> Option<Tree> {
        let code_points = input.as_ref();
        let len = code_points.len();
        self.parse_utf16_with(&mut |i, _| if i < len { &code_points[i..] } else { &[] }, old_tree)
    }

    pub fn parse_with<'a, T: FnMut(usize, Point) -> &'a [u8]>(
        &mut self,
        input: &mut T,
        old_tree: Option<&Tree>,
    ) -> Option<Tree> {
        unsafe extern "C" fn read<'a, T: FnMut(usize, Point) -> &'a [u8]>(
            payload: *mut c_void,
            byte_offset: u32,
            position: ffi::TSPoint,
            bytes_read: *mut u32,
        ) -> *const c_char {
            let input = (payload as *mut T).as_mut().unwrap();
            let slice = input(byte_offset as usize, position.into());
            *bytes_read = slice.len() as u32;
            return slice.as_ptr() as *const c_char;
        };

        let c_input = ffi::TSInput {
            payload: input as *mut T as *mut c_void,
            read: Some(read::<T>),
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

    pub fn parse_utf16_with<'a, T: 'a + FnMut(usize, Point) -> &'a [u16]>(
        &mut self,
        input: &mut T,
        old_tree: Option<&Tree>,
    ) -> Option<Tree> {
        unsafe extern "C" fn read<'a, T: FnMut(usize, Point) -> &'a [u16]>(
            payload: *mut c_void,
            byte_offset: u32,
            position: ffi::TSPoint,
            bytes_read: *mut u32,
        ) -> *const c_char {
            let input = (payload as *mut T).as_mut().unwrap();
            let slice = input(
                (byte_offset / 2) as usize,
                Point {
                    row: position.row as usize,
                    column: position.column as usize / 2,
                },
            );
            *bytes_read = slice.len() as u32 * 2;
            slice.as_ptr() as *const c_char
        };

        let c_input = ffi::TSInput {
            payload: input as *mut T as *mut c_void,
            read: Some(read::<T>),
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

    pub fn set_operation_limit(&mut self, limit: usize) {
        unsafe { ffi::ts_parser_set_operation_limit(self.0, limit) }
    }

    pub fn set_included_ranges(&mut self, ranges: &[Range]) {
        let ts_ranges: Vec<ffi::TSRange> =
            ranges.iter().cloned().map(|range| range.into()).collect();
        unsafe {
            ffi::ts_parser_set_included_ranges(self.0, ts_ranges.as_ptr(), ts_ranges.len() as u32)
        };
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

    pub fn changed_ranges(&self, other: &Tree) -> Vec<Range> {
        unsafe {
            let mut count = 0;
            let ptr =
                ffi::ts_tree_get_changed_ranges(self.0, other.0, &mut count as *mut _ as *mut u32);
            let ranges = slice::from_raw_parts(ptr, count);
            let result = ranges.into_iter().map(|r| r.clone().into()).collect();
            free_ptr(ptr as *mut c_void);
            result
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

    pub fn child_count(&self) -> usize {
        unsafe { ffi::ts_node_child_count(self.0) as usize }
    }

    pub fn children<'a>(&'a self) -> impl Iterator<Item = Node<'tree>> + 'a {
        (0..self.child_count())
            .into_iter()
            .map(move |i| self.child(i).unwrap())
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
        unsafe { free_ptr(c_string as *mut c_void) };
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
        let state = result.next_state(&result.current_state(), result.cursor.node().kind_id(), 0);
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
            let child_index = 0;
            let next_state_id = {
                let state = &self.current_state();
                let kind_id = self.cursor.node().kind_id();
                self.next_state(state, kind_id, child_index)
            };
            self.state_stack.push(next_state_id);
            self.child_index_stack.push(child_index);
            true
        } else {
            false
        }
    }

    pub fn goto_next_sibling(&mut self) -> bool {
        if self.cursor.goto_next_sibling() {
            let child_index = self.child_index_stack.pop().unwrap() + 1;
            self.state_stack.pop();
            let next_state_id = {
                let state = &self.current_state();
                let kind_id = self.cursor.node().kind_id();
                self.next_state(state, kind_id, child_index)
            };
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

    fn next_state(
        &self,
        state: &PropertyState,
        node_kind_id: u16,
        node_child_index: usize,
    ) -> usize {
        state
            .transitions
            .get(&node_kind_id)
            .and_then(|transitions| {
                for transition in transitions.iter() {
                    if let Some(text_regex_index) = transition.text_regex_index {
                        let node = self.cursor.node();
                        let text = &self.source[node.start_byte()..node.end_byte()];
                        if let Ok(text) = str::from_utf8(text) {
                            if !self.property_sheet.text_regexes[text_regex_index].is_match(text) {
                                continue;
                            }
                        }
                    }

                    if let Some(child_index) = transition.child_index {
                        if child_index != node_child_index {
                            continue;
                        }
                    }

                    return Some(transition.state_id);
                }
                None
            })
            .unwrap_or(state.default_next_state_id)
    }

    fn current_state(&self) -> &PropertyState {
        &self.property_sheet.states[*self.state_stack.last().unwrap()]
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
            let mut transitions = HashMap::new();
            let node_kind_count = language.node_kind_count();
            for transition in state.transitions.iter() {
                let text_regex_index = if let Some(regex_pattern) = transition.text.as_ref() {
                    if let Some(index) =
                        text_regex_patterns.iter().position(|r| *r == regex_pattern)
                    {
                        Some(index)
                    } else {
                        text_regex_patterns.push(regex_pattern);
                        text_regexes.push(
                            Regex::new(&regex_pattern).map_err(PropertySheetError::InvalidRegex)?,
                        );
                        Some(text_regexes.len() - 1)
                    }
                } else {
                    None
                };

                for i in 0..(node_kind_count as u16) {
                    if transition.kind == language.node_kind_for_id(i)
                        && transition.named == language.node_kind_is_named(i)
                    {
                        let entry = transitions.entry(i).or_insert(Vec::new());
                        entry.push(PropertyTransition {
                            child_index: transition.index,
                            state_id: transition.state_id,
                            text_regex_index,
                        });
                    }
                }
            }
            states.push(PropertyState {
                transitions,
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

extern "C" {
    #[link_name = "rust_tree_sitter_free"]
    fn free_ptr(ptr: *mut c_void);
}
