#[path = "../build.rs"]
mod cli_build;

fn main() {
    if let Some(git_sha) = cli_build::read_git_sha() {
        println!("cargo:rustc-env=BUILD_SHA={git_sha}");
    }
}
