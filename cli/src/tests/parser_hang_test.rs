use pretty_assertions::assert_eq;
use tree_sitter::Parser;

use crate::{
    generate::generate_parser_for_grammar,
    tests::helpers::fixtures::{fixtures_dir, get_test_language},
};

#[test]
fn test_grammar_that_should_hang_and_not_segfault() {
    use std::sync::mpsc;

    let (tx, rx) = mpsc::channel();

    std::thread::spawn(move || {
        let (parser_name, parser_code) = generate_parser_for_grammar(
            r#"
            {
                "name": "get_col_should_hang_not_crash",
                "rules": {
                    "source_file": {
                        "type": "SEQ",
                        "members": [ { "type": "SYMBOL", "name": "test" } ]
                    }
                },
                "extras": [ { "type": "PATTERN", "value": "\\s" } ],
                "externals": [ { "type": "SYMBOL", "name": "test" } ]
            }
            "#,
        )
        .unwrap();

        let mut parser = Parser::new();
        parser
            .set_language(get_test_language(
                &parser_name,
                &parser_code,
                Some(
                    fixtures_dir()
                        .join("test_grammars")
                        .join("get_col_should_hang_not_crash")
                        .as_path(),
                ),
            ))
            .unwrap();

        let code_that_should_hang = "\nHello";

        parser.parse(code_that_should_hang, None).unwrap();

        // Won't be reached
        let _ = tx.send(());
    });

    // Ok signifies that it did not hang
    // RecvTimeoutError::Disconnected signifies that the parser thread exited unexpectedly (crashed)
    assert_eq!(
        rx.recv_timeout(std::time::Duration::from_secs(5)),
        Err(mpsc::RecvTimeoutError::Timeout)
    );
}
