mod allocator;

use std::{
    alloc::Layout,
    cell::UnsafeCell,
    future::Future,
    marker::PhantomPinned,
    pin::Pin,
    slice, str,
    task::{Context, Poll, Waker},
};

use tree_sitter::{
    InputEdit, Language, LanguageError, Parser, Point, Tree, ffi::TSLanguage,
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
}

fn send<T: Send>(value: T) -> T {
    value
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
    let Some(tree) = parser.parse(source, old_tree.as_ref()) else {
        return Err(4);
    };
    Ok(send(tree))
}

struct ParseRequest<'a> {
    source: &'a str,
    old_tree: Option<Tree>,
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
        if this.requested {
            return Poll::Pending;
        }

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
        Poll::Pending
    }
}

fn parse(source: &str, old_tree: Option<Tree>) -> ParseRequest<'_> {
    ParseRequest {
        source,
        old_tree,
        requested: false,
        result: None,
        _pinned: PhantomPinned,
    }
}

async fn run() {
    let mut source = String::from(r#"{"value": 1}"#);
    let mut tree = parse(&source, None).await;
    assert_eq!(
        tree.root_node().to_sexp(),
        "(document (object (pair key: (string (string_content)) value: (number))))"
    );

    let edit_start = 10;
    let old_end = 11;
    let replacement = r#"[1, 2, 3], "nested": {"enabled": true}"#;
    source.replace_range(edit_start..old_end, replacement);
    let new_end = edit_start + replacement.len();
    tree.edit(&InputEdit {
        start_byte: edit_start,
        old_end_byte: old_end,
        new_end_byte: new_end,
        start_position: Point::new(0, edit_start),
        old_end_position: Point::new(0, old_end),
        new_end_position: Point::new(0, new_end),
    });

    tree = parse(&source, Some(tree)).await;
    assert_eq!(
        tree.root_node().to_sexp(),
        "(document (object (pair key: (string (string_content)) value: (array (number) (number) (number))) (pair key: (string (string_content)) value: (object (pair key: (string (string_content)) value: (true))))))"
    );
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

/// Install the shared allocator for Tree-sitter's C core.
///
/// # Safety
///
/// This must be called before invoking any other export in each instance.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn initialize() {
    allocator::initialize();
}

/// Allocate shared memory for the separately compiled language module.
///
/// # Safety
///
/// `alignment` must be a nonzero power of two.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn allocate_language_memory(size: u32, alignment: u32) -> u32 {
    let layout = Layout::from_size_align(size as usize, alignment as usize).unwrap();
    unsafe { allocator::allocate_zeroed(layout) as u32 }
}

/// Allocate a source buffer that JavaScript can fill.
///
/// # Safety
///
/// The returned buffer must be passed exactly once to `parse_and_return`.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn allocate_source(size: u32) -> u32 {
    unsafe { allocator::allocate(size as usize) as u32 }
}

/// Parse source as JSON, optionally using the given old tree.
///
/// # Safety
///
/// `language_address` must point to a valid language. `source_address` must
/// refer to `source_length` bytes returned by `allocate_source`. This function
/// consumes the source allocation and the tree at `old_tree_address`, if nonzero.
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
    unsafe { allocator::deallocate(source_address as *mut u8) };
    tree.map_or(0, |tree| tree.into_raw() as u32)
}

/// Start the Rust application on the UI thread.
///
/// # Safety
///
/// This must be called exactly once after `initialize`.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn start() {
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
