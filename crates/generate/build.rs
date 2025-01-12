use std::{env, fs, path::PathBuf};

fn main() {
    // This will always be ran in CI before publishing.
    // We don't use a symlink for windows compatibility.
    fs::copy(
        concat!(env!("CARGO_WORKSPACE_DIR"), "lib/src/parser.h"),
        PathBuf::from(env::var("OUT_DIR").expect("OUT_DIR should be set")).join("parser.h"),
    )
    .expect("failed to copy parser.h template");
}
