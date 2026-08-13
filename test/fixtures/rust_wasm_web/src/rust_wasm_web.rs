use std::{
    alloc::{Layout, alloc_zeroed},
    cell::UnsafeCell,
    future::Future,
    marker::PhantomPinned,
    pin::Pin,
    slice, str,
    task::{Context, Poll, Waker},
};

use tree_sitter::{
    InputEdit, Language, LanguageError, Node, Parser, Point, Tree, ffi::TSLanguage,
};

type Application = Pin<Box<dyn Future<Output = ()>>>;

struct ApplicationSlot(UnsafeCell<Option<Application>>);

unsafe impl Sync for ApplicationSlot {}

static APPLICATION: ApplicationSlot = ApplicationSlot(UnsafeCell::new(None));

#[link(wasm_import_module = "env")]
unsafe extern "C" {
    fn request_parse(
        source_address: u32,
        source_length: u32,
        old_tree_address: u32,
        request_address: u32,
    );
    fn pause_worker();
}

fn send<T: Send>(value: T) -> T {
    value
}

fn assert_send_sync<T: Send + Sync>() {}

fn array_node(tree: &Tree) -> Node<'_> {
    tree.root_node()
        .named_child(0)
        .unwrap()
        .named_child(0)
        .unwrap()
        .child_by_field_name("value")
        .unwrap()
}

fn parse_on_worker(
    language_address: u32,
    source_address: u32,
    source_length: u32,
    old_tree_address: u32,
) -> Result<Tree, u32> {
    let source_bytes =
        unsafe { slice::from_raw_parts(source_address as *const u8, source_length as usize) };
    let Ok(source) = str::from_utf8(source_bytes) else {
        return Err(1);
    };

    let language = unsafe { Language::from_raw(language_address as *const TSLanguage) };
    let old_tree = if old_tree_address == 0 {
        None
    } else {
        let tree = send(unsafe { Tree::from_raw(old_tree_address as *mut _) });
        if Parser::new().set_language(&tree.language()) != Err(LanguageError::NotParseable) {
            return Err(2);
        }
        Some(tree)
    };

    let mut parser = Parser::new();
    if parser.set_language(&language).is_err() {
        return Err(3);
    }
    let mut paused = false;
    let Some(tree) = parser.parse_with_options(
        &mut |byte_offset, _| {
            if old_tree.is_some() && !paused {
                paused = true;
                unsafe { pause_worker() };
            }
            source.as_bytes().get(byte_offset..).unwrap_or_default()
        },
        old_tree.as_ref(),
        None,
    ) else {
        return Err(4);
    };
    Ok(send(tree))
}

struct ParseRequest<'a> {
    source: &'a str,
    old_tree: Option<Tree>,
    retained_tree: Option<&'a Tree>,
    requested: bool,
    result: Option<Tree>,
    _pinned: PhantomPinned,
}

impl Future for ParseRequest<'_> {
    type Output = Tree;

    fn poll(self: Pin<&mut Self>, _context: &mut Context<'_>) -> Poll<Self::Output> {
        let this = unsafe { self.get_unchecked_mut() };
        if let Some(tree) = this.result.take() {
            return Poll::Ready(tree);
        }
        if !this.requested {
            let old_tree_address = this
                .old_tree
                .take()
                .map_or(0, |tree| send(tree).into_raw() as u32);
            this.requested = true;
            let request_address = std::ptr::from_mut(this) as u32;
            unsafe {
                request_parse(
                    this.source.as_ptr() as u32,
                    this.source.len() as u32,
                    old_tree_address,
                    request_address,
                );
            }
        }
        Poll::Pending
    }
}

fn parse<'a>(
    source: &'a str,
    old_tree: Option<Tree>,
    retained_tree: Option<&'a Tree>,
) -> ParseRequest<'a> {
    ParseRequest {
        source,
        old_tree,
        retained_tree,
        requested: false,
        result: None,
        _pinned: PhantomPinned,
    }
}

async fn run() {
    let mut source = String::from("const value = []\n");
    let mut tree = parse(&source, None, None).await;
    assert_eq!(tree.root_node().to_sexp(), "(program (lexical_declaration (variable_declarator name: (identifier) value: (array))))");
    assert_eq!(array_node(&tree).named_child_count(), 0);

    for integer in 0..100 {
        let edit_start = source.find(']').unwrap();
        let insertion = if integer == 0 {
            integer.to_string()
        } else {
            format!(", {integer}")
        };
        source.insert_str(edit_start, &insertion);
        let new_end = edit_start + insertion.len();
        tree.edit(&InputEdit {
            start_byte: edit_start,
            old_end_byte: edit_start,
            new_end_byte: new_end,
            start_position: Point::new(0, edit_start),
            old_end_position: Point::new(0, edit_start),
            new_end_position: Point::new(0, new_end),
        });

        let prev_tree = tree.clone();
        tree = parse(&source, Some(tree), Some(&prev_tree)).await;
        assert_eq!(array_node(&prev_tree).named_child_count(), integer);
        assert_eq!(array_node(&tree).named_child_count(), integer + 1);
        assert!(prev_tree.changed_ranges(&tree).len() > 0);
    }
}

fn poll_application() -> bool {
    let application = unsafe { &mut *APPLICATION.0.get() };
    let future = application.as_mut().unwrap();
    let mut context = Context::from_waker(Waker::noop());
    if future.as_mut().poll(&mut context).is_ready() {
        *application = None;
        true
    } else {
        false
    }
}

/// Allocate shared memory for the separately compiled language module.
///
/// # Safety
///
/// `alignment` must be a nonzero power of two.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn allocate_language_memory(size: u32, alignment: u32) -> u32 {
    let layout = Layout::from_size_align(size as usize, alignment as usize).unwrap();
    unsafe { alloc_zeroed(layout) as u32 }
}

/// Parse JavaScript source, optionally using the given old tree.
///
/// # Safety
///
/// `language_address` must point to a valid language. `source_address` must
/// refer to `source_length` bytes that remain valid for this call. This function
/// consumes the tree at `old_tree_address`, if nonzero.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn parse_and_return(
    language_address: u32,
    source_address: u32,
    source_length: u32,
    old_tree_address: u32,
) -> u32 {
    let tree = parse_on_worker(
        language_address,
        source_address,
        source_length,
        old_tree_address,
    )
    .ok();
    tree.map_or(0, |tree| tree.into_raw() as u32)
}

/// Start the Rust application on the UI thread.
///
/// # Safety
///
/// This must be called exactly once.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn start() {
    assert_send_sync::<Tree>();
    let application = unsafe { &mut *APPLICATION.0.get() };
    assert!(application.is_none());
    *application = Some(Box::pin(run()));
    assert!(!poll_application());
}

/// Resume the Rust application with the tree returned by the worker.
///
/// # Safety
///
/// `request_address` must identify the pending `ParseRequest`, and
/// `tree_address` must be the sole owned handle for the returned tree.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn tree_ready(request_address: u32, tree_address: u32) -> u32 {
    assert_ne!(request_address, 0);
    assert_ne!(tree_address, 0);
    let request = unsafe { &mut *(request_address as *mut ParseRequest<'static>) };
    assert!(request.requested);
    assert!(request.result.is_none());
    request.result = Some(send(unsafe { Tree::from_raw(tree_address as *mut _) }));
    u32::from(poll_application())
}

/// Read the retained UI tree while the worker is incrementally parsing its clone.
///
/// # Safety
///
/// `request_address` must identify the pending incremental `ParseRequest`.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn read_tree_while_parsing(request_address: u32) {
    let request = unsafe { &*(request_address as *const ParseRequest<'static>) };
    let tree = request.retained_tree.unwrap();
    let child_count = array_node(tree).named_child_count();
    for _ in 0..10 {
        assert_eq!(array_node(tree).named_child_count(), child_count);
        assert!(!tree.root_node().to_sexp().is_empty());
    }
}
