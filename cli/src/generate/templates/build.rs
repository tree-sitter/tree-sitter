fn main() {
    let src_dir = std::path::Path::new("src");

    let mut c_config = cc::Build::new();
    c_config.include(src_dir);
    let parser_path = src_dir.join("parser.c");
    c_config.file(&parser_path);

    // NOTE: if your language uses an external scanner, uncomment this block:

    /*
    let scanner_path = src_dir.join("scanner.c");
    c_config.file(&scanner_path);
    println!("cargo:rerun-if-changed={}", scanner_path.to_str().unwrap());
    */

    c_config.compile("tree-sitter-PARSER_NAME");
    println!("cargo:rerun-if-changed={}", parser_path.to_str().unwrap());
}
