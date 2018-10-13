mod ffi;

#[macro_use]
extern crate serde_derive;
extern crate serde_json;

use std::collections::HashMap;
use std::ffi::CStr;
use std::fmt;
use std::io::{self, Read, Seek};
use std::marker::PhantomData;
use std::os::raw::{c_char, c_void};
use std::ptr;
use std::str;

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
    pub row: u32,
    pub column: u32,
}

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub struct InputEdit {
    pub start_byte: u32,
    pub old_end_byte: u32,
    pub new_end_byte: u32,
    pub start_position: Point,
    pub old_end_position: Point,
    pub new_end_position: Point,
}

struct PropertyTransition {
    state_id: u32,
    child_index: Option<u32>,
}

struct PropertyState {
    transitions: HashMap<u16, Vec<PropertyTransition>>,
    property_set_id: u32,
    default_next_state_id: u32,
}

pub struct PropertySheet {
    states: Vec<PropertyState>,
    property_sets: Vec<HashMap<String, String>>,
}

pub struct Node<'a>(ffi::TSNode, PhantomData<&'a ()>);

pub struct Parser(*mut ffi::TSParser);

pub struct Tree(*mut ffi::TSTree);

pub struct TreeCursor<'a>(ffi::TSTreeCursor, PhantomData<&'a ()>);

pub struct TreePropertyCursor<'a> {
    cursor: TreeCursor<'a>,
    state_stack: Vec<u32>,
    child_index_stack: Vec<u32>,
    property_sheet: &'a PropertySheet,
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

    pub fn parse_str(&mut self, input: &str, old_tree: Option<&Tree>) -> Option<Tree> {
        let bytes = input.as_bytes();
        self.parse_utf8(&mut |offset, _| &bytes[(offset as usize)..], old_tree)
    }

    pub fn parse_utf8<'a, T: FnMut(u32, Point) -> &'a [u8]>(
        &mut self,
        input: &mut T,
        old_tree: Option<&Tree>,
    ) -> Option<Tree> {
        self.parse_utf8_ptr(
            &mut |byte, position| {
                let slice = input(byte, position);
                (slice.as_ptr(), slice.len())
            },
            old_tree,
        )
    }

    pub fn parse_utf16<'a, T: 'a + FnMut(u32, Point) -> &'a [u16]>(
        &mut self,
        input: &mut T,
        old_tree: Option<&Tree>,
    ) -> Option<Tree> {
        self.parse_utf16_ptr(
            &mut |byte, position| {
                let slice = input(byte, position);
                (slice.as_ptr(), slice.len())
            },
            old_tree,
        )
    }

    pub fn parse_utf8_io(
        &mut self,
        mut input: impl Read + Seek,
        old_tree: Option<&Tree>,
    ) -> io::Result<Option<Tree>> {
        let mut error = None;
        let mut current_offset = 0;
        let mut buffer = [0; 10 * 1024];
        let result = self.parse_utf8_ptr(
            &mut |byte, _| {
                if byte as u64 != current_offset {
                    current_offset = byte as u64;
                    if let Err(e) = input.seek(io::SeekFrom::Start(current_offset)) {
                        error = Some(e);
                        return (ptr::null(), 0);
                    }
                }

                match input.read(&mut buffer) {
                    Err(e) => {
                        error = Some(e);
                        (ptr::null(), 0)
                    }
                    Ok(length) => (buffer.as_ptr(), length),
                }
            },
            old_tree,
        );

        match error {
            Some(e) => Err(e),
            None => Ok(result),
        }
    }

    pub fn reset(&mut self) {
        unsafe { ffi::ts_parser_reset(self.0) }
    }

    pub fn set_operation_limit(&mut self, limit: usize) {
        unsafe { ffi::ts_parser_set_operation_limit(self.0, limit) }
    }

    fn parse_utf8_ptr<T: FnMut(u32, Point) -> (*const u8, usize)>(
        &mut self,
        input: &mut T,
        old_tree: Option<&Tree>,
    ) -> Option<Tree> {
        unsafe extern "C" fn read<T: FnMut(u32, Point) -> (*const u8, usize)>(
            payload: *mut c_void,
            byte_offset: u32,
            position: ffi::TSPoint,
            bytes_read: *mut u32,
        ) -> *const c_char {
            let input = (payload as *mut T).as_mut().unwrap();
            let (ptr, length) = (*input)(byte_offset, position.into());
            *bytes_read = length as u32;
            return ptr as *const c_char;
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

    fn parse_utf16_ptr<T: FnMut(u32, Point) -> (*const u16, usize)>(
        &mut self,
        input: &mut T,
        old_tree: Option<&Tree>,
    ) -> Option<Tree> {
        unsafe extern "C" fn read<T: FnMut(u32, Point) -> (*const u16, usize)>(
            payload: *mut c_void,
            byte_offset: u32,
            position: ffi::TSPoint,
            bytes_read: *mut u32,
        ) -> *const c_char {
            let input = (payload as *mut T).as_mut().unwrap();
            let (ptr, length) = (*input)(
                byte_offset,
                Point {
                    row: position.row,
                    column: position.column / 2,
                },
            );
            *bytes_read = length as u32 * 2;
            ptr as *const c_char
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
}

impl Drop for Parser {
    fn drop(&mut self) {
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
        let edit = ffi::TSInputEdit {
            start_byte: edit.start_byte,
            old_end_byte: edit.old_end_byte,
            new_end_byte: edit.new_end_byte,
            start_point: edit.start_position.into(),
            old_end_point: edit.old_end_position.into(),
            new_end_point: edit.new_end_position.into(),
        };
        unsafe { ffi::ts_tree_edit(self.0, &edit) };
    }

    pub fn walk(&self) -> TreeCursor {
        self.root_node().walk()
    }

    pub fn walk_with_properties<'a>(
        &'a self,
        property_sheet: &'a PropertySheet,
    ) -> TreePropertyCursor<'a> {
        TreePropertyCursor::new(self, property_sheet)
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

    pub fn start_byte(&self) -> u32 {
        unsafe { ffi::ts_node_start_byte(self.0) }
    }

    pub fn end_byte(&self) -> u32 {
        unsafe { ffi::ts_node_end_byte(self.0) }
    }

    pub fn start_position(&self) -> Point {
        let result = unsafe { ffi::ts_node_start_point(self.0) };
        Point {
            row: result.row,
            column: result.column,
        }
    }

    pub fn end_position(&self) -> Point {
        let result = unsafe { ffi::ts_node_end_point(self.0) };
        Point {
            row: result.row,
            column: result.column,
        }
    }

    pub fn child(&self, i: u32) -> Option<Self> {
        Self::new(unsafe { ffi::ts_node_child(self.0, i) })
    }

    pub fn child_count(&self) -> u32 {
        unsafe { ffi::ts_node_child_count(self.0) }
    }

    pub fn named_child<'a>(&'a self, i: u32) -> Option<Self> {
        Self::new(unsafe { ffi::ts_node_named_child(self.0, i) })
    }

    pub fn named_child_count(&self) -> u32 {
        unsafe { ffi::ts_node_named_child_count(self.0) }
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

    pub fn to_sexp(&self) -> String {
        extern "C" {
            fn free(pointer: *mut c_void);
        }

        let c_string = unsafe { ffi::ts_node_string(self.0) };
        let result = unsafe { CStr::from_ptr(c_string) }
            .to_str()
            .unwrap()
            .to_string();
        unsafe { free(c_string as *mut c_void) };
        result
    }

    pub fn utf8_text<'a>(&self, source: &'a str) -> Result<&'a str, str::Utf8Error> {
        str::from_utf8(&source.as_bytes()[self.start_byte() as usize..self.end_byte() as usize])
    }

    pub fn utf16_text<'a>(&self, source: &'a [u16]) -> &'a [u16] {
        &source[self.start_byte() as usize..self.end_byte() as usize]
    }

    pub fn walk(&self) -> TreeCursor<'tree> {
        TreeCursor(unsafe { ffi::ts_tree_cursor_new(self.0) }, PhantomData)
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

    pub fn goto_first_child_for_index(&mut self, index: u32) -> Option<u32> {
        let result = unsafe { ffi::ts_tree_cursor_goto_first_child_for_byte(&mut self.0, index) };
        if result < 0 {
            None
        } else {
            Some(result as u32)
        }
    }
}

impl<'a> Drop for TreeCursor<'a> {
    fn drop(&mut self) {
        unsafe { ffi::ts_tree_cursor_delete(&mut self.0) }
    }
}

impl<'a> TreePropertyCursor<'a> {
    fn new(tree: &'a Tree, property_sheet: &'a PropertySheet) -> Self {
        Self {
            cursor: tree.root_node().walk(),
            child_index_stack: vec![0],
            state_stack: vec![0],
            property_sheet,
        }
    }

    pub fn node(&self) -> Node<'a> {
        self.cursor.node()
    }

    pub fn node_properties(&self) -> &'a HashMap<String, String> {
        &self.property_sheet.property_sets[self.current_state().property_set_id as usize]
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

    fn next_state(&self, state: &PropertyState, node_kind_id: u16, node_child_index: u32) -> u32 {
        state
            .transitions
            .get(&node_kind_id)
            .and_then(|transitions| {
                for transition in transitions.iter() {
                    if transition.child_index == Some(node_child_index) || transition.child_index == None {
                        return Some(transition.state_id);
                    }
                }
                None
            })
            .unwrap_or(state.default_next_state_id)
    }

    fn current_state(&self) -> &PropertyState {
        &self.property_sheet.states[*self.state_stack.last().unwrap() as usize]
    }
}

impl Point {
    pub fn new(row: u32, column: u32) -> Self {
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
            row: self.row,
            column: self.column,
        }
    }
}

impl From<ffi::TSPoint> for Point {
    fn from(point: ffi::TSPoint) -> Self {
        Self {
            row: point.row,
            column: point.column,
        }
    }
}

impl PropertySheet {
    pub fn new(language: Language, json: &str) -> Result<Self, serde_json::Error> {
        #[derive(Deserialize, Debug)]
        struct PropertyTransitionJSON {
            #[serde(rename = "type")]
            kind: String,
            named: bool,
            index: Option<u32>,
            state_id: u32,
        }

        #[derive(Deserialize, Debug)]
        struct PropertyStateJSON {
            transitions: Vec<PropertyTransitionJSON>,
            property_set_id: u32,
            default_next_state_id: u32,
        }

        #[derive(Deserialize, Debug)]
        struct PropertySheetJSON {
            states: Vec<PropertyStateJSON>,
            property_sets: Vec<HashMap<String, String>>,
        }

        let input: PropertySheetJSON = serde_json::from_str(json)?;
        Ok(PropertySheet {
            property_sets: input.property_sets,
            states: input
                .states
                .iter()
                .map(|state| {
                    let mut transitions = HashMap::new();
                    let node_kind_count = language.node_kind_count();
                    for transition in state.transitions.iter() {
                        for i in 0..node_kind_count {
                            let i = i as u16;
                            if language.node_kind_is_named(i) == transition.named
                                && transition.kind == language.node_kind_for_id(i)
                            {
                                let entry = transitions.entry(i).or_insert(Vec::new());
                                entry.push(PropertyTransition {
                                    child_index: transition.index,
                                    state_id: transition.state_id,
                                });
                            }
                        }
                    }
                    PropertyState {
                        transitions,
                        default_next_state_id: state.default_next_state_id,
                        property_set_id: state.property_set_id,
                    }
                })
                .collect(),
        })
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use std::thread;

    fn rust() -> Language {
        unsafe { tree_sitter_rust() }
    }
    extern "C" {
        fn tree_sitter_rust() -> Language;
    }

    #[test]
    fn test_basic_parsing() {
        let mut parser = Parser::new();
        parser.set_language(rust()).unwrap();

        let tree = parser
            .parse_str(
                "
            struct Stuff {}
            fn main() {}
        ",
                None,
            )
            .unwrap();

        let root_node = tree.root_node();
        assert_eq!(root_node.kind(), "source_file");

        assert_eq!(
            root_node.to_sexp(),
            "(source_file (struct_item (type_identifier) (field_declaration_list)) (function_item (identifier) (parameters) (block)))"
        );

        let struct_node = root_node.child(0).unwrap();
        assert_eq!(struct_node.kind(), "struct_item");
    }

    #[test]
    fn test_logging() {
        let mut parser = Parser::new();
        parser.set_language(rust()).unwrap();

        let mut messages = Vec::new();
        parser.set_logger(Some(Box::new(|log_type, message| {
            messages.push((log_type, message.to_string()));
        })));

        parser
            .parse_str(
                "
            struct Stuff {}
            fn main() {}
        ",
                None,
            )
            .unwrap();

        assert!(messages.contains(&(
            LogType::Parse,
            "reduce sym:struct_item, child_count:3".to_string()
        )));
        assert!(messages.contains(&(LogType::Lex, "skip character:' '".to_string())));
    }

    #[test]
    fn test_tree_cursor() {
        let mut parser = Parser::new();
        parser.set_language(rust()).unwrap();

        let tree = parser
            .parse_str(
                "
                    struct Stuff {
                        a: A;
                        b: Option<B>,
                    }
                ",
                None,
            )
            .unwrap();

        let mut cursor = tree.walk();
        assert_eq!(cursor.node().kind(), "source_file");

        assert!(cursor.goto_first_child());
        assert_eq!(cursor.node().kind(), "struct_item");

        assert!(cursor.goto_first_child());
        assert_eq!(cursor.node().kind(), "struct");
        assert_eq!(cursor.node().is_named(), false);

        assert!(cursor.goto_next_sibling());
        assert_eq!(cursor.node().kind(), "type_identifier");
        assert_eq!(cursor.node().is_named(), true);

        assert!(cursor.goto_next_sibling());
        assert_eq!(cursor.node().kind(), "field_declaration_list");
        assert_eq!(cursor.node().is_named(), true);
    }

    #[test]
    fn test_tree_property_matching() {
        let mut parser = Parser::new();
        parser.set_language(rust()).unwrap();
        let tree = parser.parse_str("fn f1() { f2(); }", None).unwrap();

        let property_sheet = PropertySheet::new(
            rust(),
            r##"
            {
                "states": [
                    {
                        "transitions": [
                            {"type": "call_expression", "named": true, "state_id": 1},
                            {"type": "function_item", "named": true, "state_id": 2}
                        ],
                        "default_next_state_id": 0,
                        "property_set_id": 0
                    },
                    {
                        "transitions": [
                            {"type": "identifier", "named": true, "state_id": 3}
                        ],
                        "default_next_state_id": 0,
                        "property_set_id": 0
                    },
                    {
                        "transitions": [
                            {"type": "identifier", "named": true, "state_id": 4}
                        ],
                        "default_next_state_id": 0,
                        "property_set_id": 0
                    },
                    {
                        "transitions": [],
                        "default_next_state_id": 0,
                        "property_set_id": 1
                    },
                    {
                        "transitions": [],
                        "default_next_state_id": 0,
                        "property_set_id": 2
                    }
                ],
                "property_sets": [
                    {},
                    {"reference": "function"},
                    {"define": "function"}
                ]
            }
        "##,
        )
        .unwrap();

        let mut cursor = tree.walk_with_properties(&property_sheet);
        assert_eq!(cursor.node().kind(), "source_file");
        assert_eq!(*cursor.node_properties(), HashMap::new());

        assert!(cursor.goto_first_child());
        assert_eq!(cursor.node().kind(), "function_item");
        assert_eq!(*cursor.node_properties(), HashMap::new());

        assert!(cursor.goto_first_child());
        assert_eq!(cursor.node().kind(), "fn");
        assert_eq!(*cursor.node_properties(), HashMap::new());
        assert!(!cursor.goto_first_child());

        assert!(cursor.goto_next_sibling());
        assert_eq!(cursor.node().kind(), "identifier");
        assert_eq!(cursor.node_properties()["define"], "function");
        assert!(!cursor.goto_first_child());

        assert!(cursor.goto_next_sibling());
        assert_eq!(cursor.node().kind(), "parameters");
        assert_eq!(*cursor.node_properties(), HashMap::new());

        assert!(cursor.goto_first_child());
        assert_eq!(cursor.node().kind(), "(");
        assert!(cursor.goto_next_sibling());
        assert_eq!(cursor.node().kind(), ")");
        assert_eq!(*cursor.node_properties(), HashMap::new());

        assert!(cursor.goto_parent());
        assert!(cursor.goto_next_sibling());
        assert_eq!(cursor.node().kind(), "block");
        assert_eq!(*cursor.node_properties(), HashMap::new());

        assert!(cursor.goto_first_child());
        assert!(cursor.goto_next_sibling());
        assert_eq!(cursor.node().kind(), "call_expression");
        assert_eq!(*cursor.node_properties(), HashMap::new());

        assert!(cursor.goto_first_child());
        assert_eq!(cursor.node().kind(), "identifier");
        assert_eq!(cursor.node_properties()["reference"], "function");
    }

    #[test]
    fn test_custom_utf8_input() {
        let mut parser = Parser::new();
        parser.set_language(rust()).unwrap();

        let lines = &["pub fn foo() {", "  1", "}"];

        let tree = parser
            .parse_utf8(
                &mut |_, position| {
                    let row = position.row as usize;
                    let column = position.column as usize;
                    if row < lines.len() {
                        if column < lines[row].as_bytes().len() {
                            &lines[row].as_bytes()[column..]
                        } else {
                            "\n".as_bytes()
                        }
                    } else {
                        &[]
                    }
                },
                None,
            )
            .unwrap();

        let root = tree.root_node();
        assert_eq!(root.to_sexp(), "(source_file (function_item (visibility_modifier) (identifier) (parameters) (block (integer_literal))))");
        assert_eq!(root.kind(), "source_file");
        assert_eq!(root.has_error(), false);
        assert_eq!(root.child(0).unwrap().kind(), "function_item");
    }

    #[test]
    fn test_custom_utf16_input() {
        let mut parser = Parser::new();
        parser.set_language(rust()).unwrap();

        parser.set_logger(Some(Box::new(|t, message| {
            println!("log: {:?} {}", t, message);
        })));

        let lines: Vec<Vec<u16>> = ["pub fn foo() {", "  1", "}"]
            .iter()
            .map(|s| s.encode_utf16().collect())
            .collect();

        let tree = parser
            .parse_utf16(
                &mut |_, position| {
                    let row = position.row as usize;
                    let column = position.column as usize;
                    if row < lines.len() {
                        if column < lines[row].len() {
                            &lines[row][column..]
                        } else {
                            &[10]
                        }
                    } else {
                        &[]
                    }
                },
                None,
            )
            .unwrap();

        let root = tree.root_node();
        assert_eq!(root.to_sexp(), "(source_file (function_item (visibility_modifier) (identifier) (parameters) (block (integer_literal))))");
        assert_eq!(root.kind(), "source_file");
        assert_eq!(root.has_error(), false);
        assert_eq!(root.child(0).unwrap().kind(), "function_item");
    }

    #[test]
    fn test_node_equality() {
        let mut parser = Parser::new();
        parser.set_language(rust()).unwrap();
        let tree = parser.parse_str("struct A {}", None).unwrap();
        let node1 = tree.root_node();
        let node2 = tree.root_node();
        assert_eq!(node1, node2);
        assert_eq!(node1.child(0).unwrap(), node2.child(0).unwrap());
        assert_ne!(node1.child(0).unwrap(), node2);
    }

    #[test]
    fn test_editing() {
        let mut parser = Parser::new();
        parser.set_language(rust()).unwrap();

        let mut input_bytes = "fn test(a: A, c: C) {}".as_bytes();
        let mut input_bytes_read = Vec::new();

        let mut tree = parser
            .parse_utf8(
                &mut |offset, _| {
                    let offset = offset as usize;
                    if offset < input_bytes.len() {
                        let result = &input_bytes[offset..offset + 1];
                        input_bytes_read.extend(result.iter());
                        result
                    } else {
                        &[]
                    }
                },
                None,
            )
            .unwrap();

        let parameters_sexp = tree
            .root_node()
            .named_child(0)
            .unwrap()
            .named_child(1)
            .unwrap()
            .to_sexp();
        assert_eq!(
            parameters_sexp,
            "(parameters (parameter (identifier) (type_identifier)) (parameter (identifier) (type_identifier)))"
        );

        input_bytes_read.clear();
        input_bytes = "fn test(a: A, b: B, c: C) {}".as_bytes();
        tree.edit(&InputEdit {
            start_byte: 14,
            old_end_byte: 14,
            new_end_byte: 20,
            start_position: Point::new(0, 14),
            old_end_position: Point::new(0, 14),
            new_end_position: Point::new(0, 20),
        });

        let tree = parser
            .parse_utf8(
                &mut |offset, _| {
                    let offset = offset as usize;
                    if offset < input_bytes.len() {
                        let result = &input_bytes[offset..offset + 1];
                        input_bytes_read.extend(result.iter());
                        result
                    } else {
                        &[]
                    }
                },
                Some(&tree),
            )
            .unwrap();

        let parameters_sexp = tree
            .root_node()
            .named_child(0)
            .unwrap()
            .named_child(1)
            .unwrap()
            .to_sexp();
        assert_eq!(
            parameters_sexp,
            "(parameters (parameter (identifier) (type_identifier)) (parameter (identifier) (type_identifier)) (parameter (identifier) (type_identifier)))"
        );

        let retokenized_content = String::from_utf8(input_bytes_read).unwrap();
        assert!(retokenized_content.contains("b: B"));
        assert!(!retokenized_content.contains("a: A"));
        assert!(!retokenized_content.contains("c: C"));
        assert!(!retokenized_content.contains("{}"));
    }

    #[test]
    fn test_parallel_parsing() {
        // Parse this source file so that each thread has a non-trivial amount of
        // work to do.
        let this_file_source = include_str!("lib.rs");

        let mut parser = Parser::new();
        parser.set_language(rust()).unwrap();
        let tree = parser.parse_str(this_file_source, None).unwrap();

        let mut parse_threads = Vec::new();
        for thread_id in 1..5 {
            let mut tree_clone = tree.clone();
            parse_threads.push(thread::spawn(move || {
                // For each thread, prepend a different number of declarations to the
                // source code.
                let mut prepend_line_count = 0;
                let mut prepended_source = String::new();
                for _ in 0..thread_id {
                    prepend_line_count += 2;
                    prepended_source += "struct X {}\n\n";
                }

                tree_clone.edit(&InputEdit {
                    start_byte: 0,
                    old_end_byte: 0,
                    new_end_byte: prepended_source.len() as u32,
                    start_position: Point::new(0, 0),
                    old_end_position: Point::new(0, 0),
                    new_end_position: Point::new(prepend_line_count, 0),
                });
                prepended_source += this_file_source;

                // Reparse using the old tree as a starting point.
                let mut parser = Parser::new();
                parser.set_language(rust()).unwrap();
                parser
                    .parse_str(&prepended_source, Some(&tree_clone))
                    .unwrap()
            }));
        }

        // Check that the trees have the expected relationship to one another.
        let trees = parse_threads
            .into_iter()
            .map(|thread| thread.join().unwrap());
        let child_count_differences = trees
            .map(|t| t.root_node().child_count() - tree.root_node().child_count())
            .collect::<Vec<_>>();

        assert_eq!(child_count_differences, &[1, 2, 3, 4]);
    }
}
