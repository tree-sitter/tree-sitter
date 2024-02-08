pub(super) mod allocations;
pub(super) mod edits;
pub(super) mod fixtures;
pub(super) mod query_helpers;
pub(super) mod random;
pub(super) mod scope_sequence;

use lazy_static::lazy_static;
use rand::Rng;
use std::env;

lazy_static! {
    pub static ref LOG_ENABLED: bool = env::var("TREE_SITTER_LOG").is_ok();
    pub static ref LOG_GRAPH_ENABLED: bool = env::var("TREE_SITTER_LOG_GRAPHS").is_ok();
    pub static ref LANGUAGE_FILTER: Option<String> = env::var("TREE_SITTER_LANGUAGE").ok();
    pub static ref EXAMPLE_FILTER: Option<String> = env::var("TREE_SITTER_EXAMPLE").ok();
}

lazy_static! {
    pub static ref START_SEED: usize = new_seed();
    pub static ref EDIT_COUNT: usize = int_env_var("TREE_SITTER_EDITS").unwrap_or(3);
    pub static ref ITERATION_COUNT: usize = int_env_var("TREE_SITTER_ITERATIONS").unwrap_or(10);
}

fn int_env_var(name: &'static str) -> Option<usize> {
    env::var(name).ok().and_then(|e| e.parse().ok())
}

pub fn new_seed() -> usize {
    int_env_var("TREE_SITTER_SEED").unwrap_or_else(|| {
        let mut rng = rand::thread_rng();
        rng.gen::<usize>()
    })
}
