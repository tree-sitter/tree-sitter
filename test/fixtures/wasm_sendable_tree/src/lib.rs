mod allocator;

use std::{
    alloc::Layout,
    cell::UnsafeCell,
    future::Future,
    pin::Pin,
    slice, str,
    sync::atomic::{AtomicU32, Ordering},
    task::{Context, Poll, Waker},
};

use tree_sitter::{
    InputEdit, Language, LanguageError, Parser, Point, Tree, ffi::TSLanguage,
};

static TREE_SLOT: AtomicU32 = AtomicU32::new(0);

type Application = Pin<Box<dyn Future<Output = ()>>>;

struct ApplicationSlot(UnsafeCell<Option<Application>>);

unsafe impl Sync for ApplicationSlot {}

static APPLICATION: ApplicationSlot = ApplicationSlot(UnsafeCell::new(None));

#[link(wasm_import_module = "env")]
unsafe extern "C" {
    fn request_parse(source_address: u32, source_length: u32, has_old_tree: u32);
}

fn send<T: Send>(value: T) -> T {
    value
}

fn publish(tree: Tree) -> Result<(), Tree> {
    let tree_address = send(tree).into_raw() as u32;
    match TREE_SLOT.compare_exchange(0, tree_address, Ordering::Release, Ordering::Relaxed) {
        Ok(_) => Ok(()),
        Err(_) => Err(unsafe { Tree::from_raw(tree_address as *mut _) }),
    }
}

fn take() -> Option<Tree> {
    let tree_address = TREE_SLOT.swap(0, Ordering::Acquire);
    (tree_address != 0).then(|| unsafe { Tree::from_raw(tree_address as *mut _) })
}

fn parse_on_worker(
    language_address: u32,
    source_address: u32,
    source_length: u32,
    has_old_tree: bool,
) -> u32 {
    let source_bytes =
        unsafe { slice::from_raw_parts(source_address as *const u8, source_length as usize) };
    let Ok(source) = str::from_utf8(source_bytes) else {
        return 1;
    };

    let language = unsafe { Language::from_raw(language_address as *const TSLanguage) };
    let old_tree = if has_old_tree {
        let Some(tree) = take() else {
            return 2;
        };
        if Parser::new().set_language(&tree.language()) != Err(LanguageError::NotParseable) {
            return 3;
        }
        Some(tree)
    } else {
        None
    };

    let mut parser = Parser::new();
    if parser.set_language(&language).is_err() {
        return 4;
    }
    let Some(tree) = parser.parse(source, old_tree.as_ref()) else {
        return 5;
    };
    if publish(tree).is_err() {
        return 6;
    }
    0
}

struct ParseRequest<'a> {
    source: &'a str,
    old_tree: Option<Tree>,
    requested: bool,
}

impl Future for ParseRequest<'_> {
    type Output = Tree;

    fn poll(mut self: Pin<&mut Self>, _context: &mut Context<'_>) -> Poll<Self::Output> {
        if self.requested {
            return take().map_or(Poll::Pending, Poll::Ready);
        }

        let has_old_tree = self.old_tree.is_some();
        if let Some(tree) = self.old_tree.take() {
            publish(tree).unwrap();
        }
        unsafe {
            request_parse(
                self.source.as_ptr() as u32,
                self.source.len() as u32,
                u32::from(has_old_tree),
            );
        }
        self.requested = true;
        Poll::Pending
    }
}

fn parse(source: &str, old_tree: Option<Tree>) -> ParseRequest<'_> {
    ParseRequest {
        source,
        old_tree,
        requested: false,
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
/// The returned buffer must be passed exactly once to `parse_and_publish`.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn allocate_source(size: u32) -> u32 {
    unsafe { allocator::allocate(size as usize) as u32 }
}

/// Parse source as JSON, optionally using the tree in the shared slot.
///
/// # Safety
///
/// `language_address` must point to a valid language. `source_address` must
/// refer to `source_length` bytes returned by `allocate_source`. This function
/// consumes the source allocation and, when `has_old_tree` is nonzero, the tree
/// in the shared slot.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn parse_and_publish(
    language_address: u32,
    source_address: u32,
    source_length: u32,
    has_old_tree: u32,
) -> u32 {
    let result = parse_on_worker(
        language_address,
        source_address,
        source_length,
        has_old_tree != 0,
    );
    unsafe { allocator::deallocate(source_address as *mut u8) };
    result
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

/// Resume the Rust application after the worker has returned a tree.
///
/// # Safety
///
/// The shared tree slot must contain the tree produced by the worker.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn tree_ready() -> u32 {
    u32::from(poll_application())
}
