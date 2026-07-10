use std::{
    future::Future,
    pin::Pin,
    ptr,
    task::{Context, Poll, RawWaker, RawWakerVTable, Waker},
};

use tree_sitter::Parser;

use super::helpers::fixtures::get_language;

#[test]
fn test_node_across_async_boundaries() {
    let mut parser = Parser::new();
    let language = get_language("bash");
    parser.set_language(&language).unwrap();
    let tree = parser.parse("#", None).unwrap();
    let root = tree.root_node();

    let (result, yields) = simple_async_executor(async {
        let root_ref = &root;

        // Test node captured by value
        let fut_by_value = async {
            yield_once().await;
            root.child(0).unwrap().kind()
        };

        // Test node captured by reference
        let fut_by_ref = async {
            yield_once().await;
            root_ref.child(0).unwrap().kind()
        };

        let result1 = fut_by_value.await;
        let result2 = fut_by_ref.await;

        assert_eq!(result1, result2);
        result1
    });

    assert_eq!(result, "comment");
    assert_eq!(yields, 2);
}

#[test]
fn test_cursor_across_async_boundaries() {
    let mut parser = Parser::new();
    let language = get_language("c");
    parser.set_language(&language).unwrap();
    let tree = parser.parse("#", None).unwrap();
    let mut cursor = tree.walk();

    let ((), yields) = simple_async_executor(async {
        cursor.goto_first_child();

        // Test cursor usage across yield point
        yield_once().await;
        cursor.goto_first_child();

        // Test cursor in async block
        let cursor_ref = &mut cursor;
        let fut = async {
            yield_once().await;
            cursor_ref.goto_first_child();
        };
        fut.await;
    });

    assert_eq!(yields, 2);
}

#[test]
fn test_node_and_cursor_together() {
    let mut parser = Parser::new();
    let language = get_language("javascript");
    parser.set_language(&language).unwrap();
    let tree = parser.parse("#", None).unwrap();
    let root = tree.root_node();
    let mut cursor = tree.walk();

    let ((), yields) = simple_async_executor(async {
        cursor.goto_first_child();

        let fut = async {
            yield_once().await;
            let _ = root.to_sexp();
            cursor.goto_first_child();
        };

        yield_once().await;
        fut.await;
    });

    assert_eq!(yields, 2);
}

fn simple_async_executor<F>(future: F) -> (F::Output, u32)
where
    F: Future,
{
    let waker = noop_waker();
    let mut cx = Context::from_waker(&waker);
    let mut yields = 0;
    let mut future = Box::pin(future);

    loop {
        match future.as_mut().poll(&mut cx) {
            Poll::Ready(result) => return (result, yields),
            Poll::Pending => yields += 1,
        }
    }
}

async fn yield_once() {
    struct YieldOnce {
        yielded: bool,
    }

    impl Future for YieldOnce {
        type Output = ();

        fn poll(mut self: Pin<&mut Self>, cx: &mut Context<'_>) -> Poll<()> {
            if self.yielded {
                Poll::Ready(())
            } else {
                self.yielded = true;
                cx.waker().wake_by_ref();
                Poll::Pending
            }
        }
    }

    YieldOnce { yielded: false }.await;
}

const fn noop_waker() -> Waker {
    const VTABLE: RawWakerVTable = RawWakerVTable::new(
        // Cloning just returns a new no-op raw waker
        |_| RAW,
        // `wake` does nothing
        |_| {},
        // `wake_by_ref` does nothing
        |_| {},
        // Dropping does nothing as we don't allocate anything
        |_| {},
    );
    const RAW: RawWaker = RawWaker::new(ptr::null(), &VTABLE);
    unsafe { Waker::from_raw(RAW) }
}
