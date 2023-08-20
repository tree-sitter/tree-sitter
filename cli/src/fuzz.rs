use std::path::PathBuf;

use anyhow::Context;
use rand::Rng;
use tree_sitter::Language;

use crate::{test::parse_tests, tests::load_tests};

pub fn fuzz(language: Language, dir: PathBuf) -> anyhow::Result<()> {
    let start_seed = {
        let mut rng = rand::thread_rng();
        rng.gen::<usize>()
    };

    let corpus_dir = dir.join("test").join("corpus");
    // let tests = flatten_tests(
    //     parse_tests(&corpus_dir)
    //         .with_context(|| format!("Failed to parse tests in {}", corpus_dir.display()))?,
    // );
    let tests = load_tests("", dir)

    let mut failure_count = 0;

    let log_seed = std::env::var("TREE_SITTER_LOG_SEED").is_ok();
    let dump_edits = std::env::var("TREE_SITTER_DUMP_EDITS").is_ok();

    if log_seed {
        println!("  start seed: {}", start_seed);
    }

    println!();

    Ok(())
}
