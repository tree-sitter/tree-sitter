lazy_static! {
    static ref ROOT_DIR: PathBuf = PathBuf::from(env!("CARGO_MANIFEST_DIR")).parent().unwrap().to_owned();
    static ref FIXTURES_DIR: PathBuf = ROOT_DIR.join("test").join("fixtures");
    static ref HEADER_DIR: PathBuf = ROOT_DIR.join("lib").join("include");
    static ref GRAMMARS_DIR: PathBuf = ROOT_DIR.join("test").join("fixtures").join("grammars");
    static ref SCRATCH_DIR: PathBuf = {
        let result = ROOT_DIR.join("target").join("scratch");
        fs::create_dir_all(&result).unwrap();
        result
    };
}
