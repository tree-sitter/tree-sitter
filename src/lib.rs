mod ffi;

use std::fmt;
use std::ffi::CStr;
use std::marker::PhantomData;
use std::os::raw::{c_char, c_int, c_void};
use std::ptr;

pub type Language = *const ffi::TSLanguage;

pub trait Utf16Input {
    fn read(&mut self) -> &[u16];
    fn seek(&mut self, u32, Point);
}

pub trait Utf8Input {
    fn read(&mut self) -> &[u8];
    fn seek(&mut self, u32, Point);
}

#[derive(Debug, PartialEq, Eq)]
pub enum LogType {
    Parse,
    Lex,
}

type Logger<'a> = Box<FnMut(LogType, &str) + 'a>;

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
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

pub struct Node<'a>(ffi::TSNode, PhantomData<&'a ()>);

pub struct Parser(*mut ffi::TSParser);

pub struct Tree(*mut ffi::TSTree);

pub struct TreeCursor<'a>(ffi::TSTreeCursor, PhantomData<&'a ()>);

struct FlatInput<'a> {
    bytes: &'a [u8],
    offset: usize,
}

impl Parser {
    pub fn new() -> Parser {
        unsafe {
            let parser = ffi::ts_parser_new();
            Parser(parser)
        }
    }

    pub fn set_language(&mut self, language: Language) -> Result<(), String> {
        unsafe {
            let version = ffi::ts_language_version(language) as usize;
            if version == ffi::TREE_SITTER_LANGUAGE_VERSION {
                ffi::ts_parser_set_language(self.0, language);
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
            c_logger = ffi::TSLogger { payload: ptr::null_mut(), log: None };
        }

        unsafe { ffi::ts_parser_set_logger(self.0, c_logger) };
    }

    pub fn parse_str(&mut self, input: &str, old_tree: Option<Tree>) -> Option<Tree> {
        let mut input = FlatInput { bytes: input.as_bytes(), offset: 0};
        self.parse_utf8(&mut input, old_tree)
    }

    pub fn parse_utf8<T: Utf8Input>(
        &mut self,
        input: &mut T,
        old_tree: Option<Tree>,
    ) -> Option<Tree> {
        unsafe extern "C" fn read<T: Utf8Input>(
            payload: *mut c_void,
            bytes_read: *mut u32,
        ) -> *const c_char {
            let input = (payload as *mut T).as_mut().unwrap();
            let result = input.read();
            *bytes_read = result.len() as u32;
            return result.as_ptr() as *const c_char;
        };

        unsafe extern "C" fn seek<T: Utf8Input>(
            payload: *mut c_void,
            byte: u32,
            position: ffi::TSPoint,
        ) -> c_int {
            let input = (payload as *mut T).as_mut().unwrap();
            input.seek(
                byte,
                Point {
                    row: position.row,
                    column: position.column,
                },
            );
            return 1;
        };

        let c_input = ffi::TSInput {
            payload: input as *mut T as *mut c_void,
            read: Some(read::<T>),
            seek: Some(seek::<T>),
            encoding: ffi::TSInputEncoding_TSInputEncodingUTF8,
        };

        let old_tree_ptr = old_tree.map_or(ptr::null_mut(), |t| t.0);

        let new_tree_ptr = unsafe { ffi::ts_parser_parse(self.0, old_tree_ptr, c_input) };
        if new_tree_ptr.is_null() {
            None
        } else {
            Some(Tree(new_tree_ptr))
        }
    }

    pub fn parse_utf16<T: Utf16Input>(
        &mut self,
        input: &mut T,
        old_tree: Option<Tree>,
    ) -> Option<Tree> {
        unsafe extern "C" fn read<T: Utf16Input>(
            payload: *mut c_void,
            bytes_read: *mut u32,
        ) -> *const c_char {
            let input = (payload as *mut T).as_mut().unwrap();
            let result = input.read();
            *bytes_read = result.len() as u32 * 2;
            return result.as_ptr() as *const c_char;
        };

        unsafe extern "C" fn seek<T: Utf16Input>(
            payload: *mut c_void,
            byte: u32,
            position: ffi::TSPoint,
        ) -> c_int {
            let input = (payload as *mut T).as_mut().unwrap();
            input.seek(
                byte / 2,
                Point {
                    row: position.row,
                    column: position.column / 2,
                },
            );
            return 1;
        };

        let c_input = ffi::TSInput {
            payload: input as *mut T as *mut c_void,
            read: Some(read::<T>),
            seek: Some(seek::<T>),
            encoding: ffi::TSInputEncoding_TSInputEncodingUTF8,
        };

        let old_tree_ptr = old_tree.map_or(ptr::null_mut(), |t| t.0);

        let new_tree_ptr = unsafe { ffi::ts_parser_parse(self.0, old_tree_ptr, c_input) };
        if new_tree_ptr.is_null() {
            None
        } else {
            Some(Tree(new_tree_ptr))
        }
    }
}

impl Drop for Parser {
    fn drop(&mut self) {
        self.set_logger(None);
        unsafe { ffi::ts_parser_delete(self.0) }
    }
}

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
        TreeCursor(unsafe { ffi::ts_tree_cursor_new(self.0) }, PhantomData)
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

impl<'a> Node<'a> {
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
        unsafe { CStr::from_ptr(ffi::ts_node_type(self.0)) }.to_str().unwrap()
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

    pub fn child(&self, i: u32) -> Option<Node> {
        Self::new(unsafe { ffi::ts_node_child(self.0, i) })
    }

    pub fn child_count(&self) -> u32 {
        unsafe { ffi::ts_node_child_count(self.0) }
    }

    pub fn named_child(&self, i: u32) -> Option<Node> {
        Self::new(unsafe { ffi::ts_node_named_child(self.0, i) })
    }

    pub fn named_child_count(&self) -> u32 {
        unsafe { ffi::ts_node_named_child_count(self.0) }
    }

    pub fn parent(&self) -> Option<Node> {
        Self::new(unsafe { ffi::ts_node_parent(self.0) })
    }

    pub fn next_sibling(&self) -> Option<Node> {
        Self::new(unsafe { ffi::ts_node_next_sibling(self.0) })
    }

    pub fn prev_sibling(&self) -> Option<Node> {
        Self::new(unsafe { ffi::ts_node_prev_sibling(self.0) })
    }

    pub fn next_named_sibling(&self) -> Option<Node> {
        Self::new(unsafe { ffi::ts_node_next_named_sibling(self.0) })
    }

    pub fn prev_named_sibling(&self) -> Option<Node> {
        Self::new(unsafe { ffi::ts_node_prev_named_sibling(self.0) })
    }

    pub fn to_sexp(&self) -> String {
        extern "C" { fn free(pointer: *mut c_void); }

        let c_string = unsafe { ffi::ts_node_string(self.0) };
        let result = unsafe { CStr::from_ptr(c_string) }.to_str().unwrap().to_string();
        unsafe { free(c_string as *mut c_void) };
        result
    }
}

impl<'a> PartialEq for Node<'a> {
    fn eq(&self, other: &Self) -> bool {
        self.0.id == other.0.id
    }
}

impl<'a> fmt::Debug for Node<'a> {
    fn fmt(&self, f: &mut fmt::Formatter) -> Result<(), fmt::Error> {
        write!(f, "{{Node {} {} - {}}}", self.kind(), self.start_position(), self.end_position())
    }
}

impl<'a> TreeCursor<'a> {
    pub fn node(&'a self) -> Node<'a> {
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

impl<'a> Utf8Input for FlatInput<'a> {
    fn read(&mut self) -> &[u8] {
        let result = &self.bytes[self.offset..];
        self.offset = self.bytes.len();
        result
    }

    fn seek(&mut self, offset: u32, _position: Point) {
        self.offset = offset as usize;
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    fn rust() -> Language { unsafe { tree_sitter_rust() } }
    extern "C" { fn tree_sitter_rust() -> Language; }

    #[test]
    fn test_basic_parsing() {
        let mut parser = Parser::new();
        parser.set_language(rust()).unwrap();

        let tree = parser.parse_str("
            struct Stuff {}
            fn main() {}
        ", None).unwrap();

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

        parser.parse_str("
            struct Stuff {}
            fn main() {}
        ", None).unwrap();

        assert!(messages.contains(&(LogType::Parse, "reduce sym:struct_item, child_count:3".to_string())));
        assert!(messages.contains(&(LogType::Lex, "skip character:' '".to_string())));
    }

    #[test]
    fn test_tree_cursor() {
        let mut parser = Parser::new();
        parser.set_language(rust()).unwrap();

        let tree = parser.parse_str("
            struct Stuff {
                a: A;
                b: Option<B>,
            }
        ", None).unwrap();

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
    fn test_custom_utf8_input() {
        struct LineBasedInput {
            lines: &'static [&'static str],
            row: usize,
            column: usize,
        }

        impl Utf8Input for LineBasedInput {
            fn read(&mut self) -> &[u8] {
                if self.row < self.lines.len() {
                    let result = &self.lines[self.row].as_bytes()[self.column..];
                    self.row += 1;
                    self.column = 0;
                    result
                } else {
                    &[]
                }
            }

            fn seek(&mut self, _byte: u32, position: Point) {
                self.row = position.row as usize;
                self.column = position.column as usize;
            }
        }

        let mut parser = Parser::new();
        parser.set_language(rust()).unwrap();

        let mut input = LineBasedInput {
            lines: &[
                "pub fn main() {",
                "}",
            ],
            row: 0,
            column: 0
        };

        let tree = parser.parse_utf8(&mut input, None).unwrap();
        let root = tree.root_node();
        assert_eq!(root.kind(), "source_file");
        assert_eq!(root.has_error(), false);

        let child = root.child(0).unwrap();
        assert_eq!(child.kind(), "function_item");
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
}
