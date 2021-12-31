pub(super) mod allocations;
pub(super) mod edits;
pub(super) mod fixtures;
pub(super) mod query_helpers;
pub(super) mod random;
pub(super) mod scope_sequence;

use lazy_static::lazy_static;
use std::{env, time, usize};

lazy_static! {
    pub static ref SEED: usize = {
        let seed = env::var("TREE_SITTER_TEST_SEED")
            .map(|s| usize::from_str_radix(&s, 10).unwrap())
            .unwrap_or(
                time::SystemTime::now()
                    .duration_since(time::UNIX_EPOCH)
                    .unwrap()
                    .as_secs() as usize,
            );
        eprintln!("\n\nRandom seed: {}\n", seed);
        seed
    };
    pub static ref LOG_ENABLED: bool = env::var("TREE_SITTER_TEST_ENABLE_LOG").is_ok();
    pub static ref LOG_GRAPH_ENABLED: bool = env::var("TREE_SITTER_TEST_ENABLE_LOG_GRAPHS").is_ok();
    pub static ref LANGUAGE_FILTER: Option<String> =
        env::var("TREE_SITTER_TEST_LANGUAGE_FILTER").ok();
    pub static ref EXAMPLE_FILTER: Option<String> =
        env::var("TREE_SITTER_TEST_EXAMPLE_FILTER").ok();
    pub static ref TRIAL_FILTER: Option<usize> = env::var("TREE_SITTER_TEST_TRIAL_FILTER")
        .map(|s| usize::from_str_radix(&s, 10).unwrap())
        .ok();
}
