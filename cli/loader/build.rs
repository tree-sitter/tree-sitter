pub const EMSCRIPTEN_VERSION: &str = include_str!("emscripten-version");

fn main() {
    println!(
        "cargo:rustc-env=BUILD_TARGET={}",
        std::env::var("TARGET").unwrap()
    );

    println!("cargo:rustc-env=EMSCRIPTEN_VERSION={EMSCRIPTEN_VERSION}");
}
