fn main() {
    if std::env::var("TARGET")
        .unwrap_or_default()
        .starts_with("wasm32-unknown")
    {
        let manifest_dir = std::env::var("CARGO_MANIFEST_DIR").unwrap();
        let wasm_headers = std::path::Path::new(&manifest_dir).join("wasm/include");
        let wasm_src = std::path::Path::new(&manifest_dir).join("wasm/src");

        println!("cargo::metadata=wasm-headers={}", wasm_headers.display());
        println!("cargo::metadata=wasm-src={}", wasm_src.display());
    }
}
