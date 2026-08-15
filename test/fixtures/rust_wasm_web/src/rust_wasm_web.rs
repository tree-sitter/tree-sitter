use std::{
    alloc::{Layout, alloc_zeroed},
    cell::UnsafeCell,
    future::Future,
    marker::PhantomPinned,
    pin::Pin,
    slice, str,
    sync::{
        LazyLock,
        atomic::{AtomicUsize, Ordering},
    },
    task::{Context, Poll, Waker},
};
use tree_sitter::{
    InputEdit, Language, LanguageError, Parser, Point, Query, QueryCursor, StreamingIterator, Tree,
    ffi::TSLanguage,
};

type Application = Pin<Box<dyn Future<Output = ()>>>;

const JAVASCRIPT: u32 = 0;
const PYTHON: u32 = 1;
const RUBY: u32 = 2;

struct ApplicationSlot(UnsafeCell<Option<Application>>);

unsafe impl Sync for ApplicationSlot {}

static APPLICATION: ApplicationSlot = ApplicationSlot(UnsafeCell::new(None));
static JAVASCRIPT_QUERY_INITIALIZATIONS: AtomicUsize = AtomicUsize::new(0);
static WORKER_QUERY_CAPTURE_COUNT: AtomicUsize = AtomicUsize::new(0);
static JAVASCRIPT_QUERY: LazyLock<Query> = LazyLock::new(|| {
    JAVASCRIPT_QUERY_INITIALIZATIONS.fetch_add(1, Ordering::SeqCst);
    Query::new(
        &Language::from(tree_sitter_javascript::LANGUAGE),
        "(number) @number",
    )
    .unwrap()
});

#[link(wasm_import_module = "env")]
unsafe extern "C" {
    fn request_parse(
        language_id: u32,
        source_address: u32,
        source_length: u32,
        old_tree_address: u32,
        request_address: u32,
    );
    fn log(message_address: u32, message_length: u32);
    fn notify_parsing_started();
}

fn log_progress(message: &str) {
    unsafe { log(message.as_ptr() as u32, message.len() as u32) }
}

fn javascript_query_capture_count(tree: &Tree, source: &str) -> usize {
    let mut cursor = QueryCursor::new();
    let mut captures = cursor.captures(&JAVASCRIPT_QUERY, tree.root_node(), source.as_bytes());
    let mut count = 0;
    while captures.next().is_some() {
        count += 1;
    }
    count
}

fn assert_javascript_query(tree: &Tree, source: &str, expected_count: usize) {
    assert_eq!(JAVASCRIPT_QUERY_INITIALIZATIONS.load(Ordering::SeqCst), 1);
    assert_eq!(
        WORKER_QUERY_CAPTURE_COUNT.load(Ordering::Acquire),
        expected_count
    );
    assert_eq!(javascript_query_capture_count(tree, source), expected_count);
}

struct ParseRequest<'a> {
    language_id: u32,
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
        if !this.requested {
            let old_tree_address = this
                .old_tree
                .take()
                .map_or(0, |tree| tree.into_raw() as u32);
            this.requested = true;
            let request_address = std::ptr::from_mut(this) as u32;
            unsafe {
                request_parse(
                    this.language_id,
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

fn spawn_parse<'a>(language_id: u32, source: &'a str, old_tree: Option<Tree>) -> ParseRequest<'a> {
    ParseRequest {
        language_id,
        source,
        old_tree,
        requested: false,
        result: None,
        _pinned: PhantomPinned,
    }
}

async fn run() {
    let mut source = String::from("const value = []\n");
    let mut tree = spawn_parse(JAVASCRIPT, &source, None).await;
    let language = tree.language();
    assert_eq!(language.name(), Some("javascript"));
    assert!(!language.is_parseable());
    assert!(!tree.root_node().language().is_parseable());
    assert_eq!(
        Parser::new().set_language(&language),
        Err(LanguageError::NotParseable)
    );
    assert_eq!(
        tree.root_node().to_sexp(),
        "(program (lexical_declaration (variable_declarator name: (identifier) value: (array))))"
    );
    assert_javascript_query(&tree, &source, 0);
    log_progress("parsed javascript");

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
        if integer == 0 {
            assert_eq!(
                Parser::new().set_language(&prev_tree.language()),
                Err(LanguageError::NotParseable)
            );
        }
        tree = spawn_parse(JAVASCRIPT, &source, Some(tree)).await;
        let array_node = tree
            .root_node()
            .named_child(0)
            .unwrap()
            .named_child(0)
            .unwrap()
            .child_by_field_name("value")
            .unwrap();
        assert_eq!(array_node.named_child_count(), integer + 1);
        assert!(prev_tree.changed_ranges(&tree).len() > 0);
        assert_javascript_query(&tree, &source, integer + 1);
        log_progress(&format!("incrementally reparsed ({} / 100)", integer + 1));
    }

    let python_source = String::from("def answer():\n  return 42\n");
    let python_tree = spawn_parse(PYTHON, &python_source, None).await;
    assert_eq!(
        python_tree.root_node().to_sexp(),
        "(module (function_definition name: (identifier) parameters: (parameters) body: (block (return_statement (integer)))))"
    );
    log_progress("parsed python");

    // Ruby's scanner uses wide-character classification for suffixed constants
    // and unquoted heredoc delimiters.
    let ruby_source = String::from("Éclair!\nvalue = <<~ÉTÉ\n  héllo\nÉTÉ\n");
    let ruby_tree = spawn_parse(RUBY, &ruby_source, None).await;
    assert_eq!(
        ruby_tree.root_node().to_sexp(),
        "(program (call method: (constant)) (assignment left: (identifier) right: (heredoc_beginning)) (heredoc_body (heredoc_content) (heredoc_end)))"
    );
    log_progress("parsed ruby");
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

#[unsafe(no_mangle)]
pub unsafe extern "C" fn allocate_language_memory(size: u32, alignment: u32) -> u32 {
    let layout = Layout::from_size_align(size as usize, alignment as usize).unwrap();
    unsafe { alloc_zeroed(layout) as u32 }
}

#[unsafe(no_mangle)]
pub unsafe extern "C" fn run_parse(
    language_address: u32,
    source_address: u32,
    source_length: u32,
    old_tree_address: u32,
) -> u32 {
    let tree = run_parse_internal(
        language_address,
        source_address,
        source_length,
        old_tree_address,
    )
    .ok();
    tree.map_or(0, |tree| tree.into_raw() as u32)
}

fn run_parse_internal(
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

    let old_tree = if old_tree_address == 0 {
        None
    } else {
        Some(unsafe { Tree::from_raw(old_tree_address as *mut _) })
    };

    let mut parser = Parser::new();
    if let Some(tree) = old_tree.as_ref() {
        if parser.set_language(&tree.language()).is_err() {
            return Err(2);
        }
    } else {
        let language = if language_address == JAVASCRIPT {
            Language::from(tree_sitter_javascript::LANGUAGE)
        } else {
            unsafe { Language::from_raw(language_address as *const TSLanguage) }
        };
        if parser.set_language(&language).is_err() {
            return Err(3);
        }
    }
    let mut paused = false;
    let Some(tree) = parser.parse_with_options(
        &mut |byte_offset, _| {
            if old_tree.is_some() && !paused {
                paused = true;
                unsafe { notify_parsing_started() };
            }
            source.as_bytes().get(byte_offset..).unwrap_or_default()
        },
        old_tree.as_ref(),
        None,
    ) else {
        return Err(4);
    };
    if language_address == JAVASCRIPT {
        WORKER_QUERY_CAPTURE_COUNT.store(
            javascript_query_capture_count(&tree, source),
            Ordering::Release,
        );
    }
    Ok(tree)
}

#[unsafe(no_mangle)]
pub unsafe extern "C" fn start() {
    let application = unsafe { &mut *APPLICATION.0.get() };
    assert!(application.is_none());
    *application = Some(Box::pin(run()));
    assert!(!poll_application());
}

#[unsafe(no_mangle)]
pub unsafe extern "C" fn tree_ready(request_address: u32, tree_address: u32) -> u32 {
    assert_ne!(request_address, 0);
    assert_ne!(tree_address, 0);
    let request = unsafe { &mut *(request_address as *mut ParseRequest<'static>) };
    assert!(request.requested);
    assert!(request.result.is_none());
    request.result = Some(unsafe { Tree::from_raw(tree_address as *mut _) });
    u32::from(poll_application())
}
