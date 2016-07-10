mod ffi;

use std::ffi::CStr;
use std::marker::PhantomData;
use std::os::raw::{c_char, c_int, c_void};
use std::ptr;

#[derive(Clone, Copy)]
pub struct Symbol(ffi::TSSymbol);

#[derive(Clone, Copy)]
pub struct Language(*const ffi::TSLanguage);

pub trait Utf16Input {
    fn read(&self) -> &[u16];
    fn seek(&self, u32, Point);
}

pub trait Utf8Input {
    fn read(&self) -> &[u8];
    fn seek(&self, u32, Point);
}

pub enum LogType {
    Parse,
    Lex,
}

#[derive(Clone, Copy, PartialEq, Eq)]
pub struct Point {
    pub row: u32,
    pub column: u32,
}

#[derive(Clone, Copy, PartialEq, Eq)]
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

pub struct Tree(*mut ffi::TSTree, ffi::TSInputEncoding);

pub struct TreeCursor<'a>(ffi::TSTreeCursor, PhantomData<&'a ()>);

impl Parser {
    pub fn new() -> Parser {
        unsafe {
            let parser = ffi::ts_parser_new();
            Parser(parser)
        }
    }

    pub fn set_language(&mut self, language: Language) {
        unsafe {
            ffi::ts_parser_set_language(self.0, language.0);
        }
    }

    pub fn set_logger<F: FnMut(LogType, &str) -> ()>(&mut self, logger: &mut F) {
        unsafe extern "C" fn log<F: FnMut(LogType, &str) -> ()>(
            payload: *mut c_void,
            c_log_type: ffi::TSLogType,
            c_message: *const c_char,
        ) {
            let callback = (payload as *mut F).as_mut().unwrap();
            if let Ok(message) = CStr::from_ptr(c_message).to_str() {
                let log_type = if c_log_type == ffi::TSLogType_TSLogTypeParse {
                    LogType::Parse
                } else {
                    LogType::Lex
                };
                callback(log_type, message);
            }
        };

        let c_logger = ffi::TSLogger {
            payload: logger as *mut F as *mut c_void,
            log: Some(log::<F>),
        };

        unsafe { ffi::ts_parser_set_logger(self.0, c_logger) };
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
            Some(Tree(new_tree_ptr, ffi::TSInputEncoding_TSInputEncodingUTF8))
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
            Some(Tree(
                new_tree_ptr,
                ffi::TSInputEncoding_TSInputEncodingUTF16,
            ))
        }
    }
}

impl Drop for Parser {
    fn drop(&mut self) {
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
        unsafe { Tree(ffi::ts_tree_copy(self.0), self.1) }
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

    pub fn name(&self) -> &'static str {
        unsafe { CStr::from_ptr(ffi::ts_node_type(self.0)) }
            .to_str()
            .unwrap()
    }

    pub fn start_index(&self) -> u32 {
        unsafe { ffi::ts_node_start_byte(self.0) }
    }

    pub fn end_index(&self) -> u32 {
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

    pub fn parent(&self) -> Option<Node> {
        Self::new(unsafe { ffi::ts_node_parent(self.0) })
    }
}

impl<'a> TreeCursor<'a> {
    fn node(&'a self) -> Node<'a> {
        Node(
            unsafe { ffi::ts_tree_cursor_current_node(&self.0) },
            PhantomData,
        )
    }

    fn goto_first_child(&mut self) -> bool {
        return unsafe { ffi::ts_tree_cursor_goto_first_child(&mut self.0) };
    }

    fn goto_parent(&mut self) -> bool {
        return unsafe { ffi::ts_tree_cursor_goto_parent(&mut self.0) };
    }

    fn goto_next_sibling(&mut self) -> bool {
        return unsafe { ffi::ts_tree_cursor_goto_next_sibling(&mut self.0) };
    }

    fn goto_first_child_for_index(&mut self, index: u32) -> Option<u32> {
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

impl Into<ffi::TSPoint> for Point {
    fn into(self) -> ffi::TSPoint {
        ffi::TSPoint {
            row: self.row,
            column: self.column,
        }
    }
}

#[cfg(test)]
mod tests {
    #[test]
    fn it_works() {}
}
