fn main() {
    println!(
        "cargo:rustc-env=BUILD_TARGET={}",
        std::env::var("TARGET").unwrap()
    );
    println!(
        "cargo:rustc-env=BUILD_HOST={}",
        std::env::var("HOST").unwrap()
    );
}
