lazy_static! {
    pub static ref ROOT_DIR: PathBuf = PathBuf::from(env!("CARGO_MANIFEST_DIR")).parent().unwrap().to_owned();
    pub static ref FIXTURES_DIR: PathBuf = ROOT_DIR.join("test").join("fixtures");
    pub static ref HEADER_DIR: PathBuf = ROOT_DIR.join("lib").join("include");
    pub static ref GRAMMARS_DIR: PathBuf = ROOT_DIR.join("test").join("fixtures").join("grammars");
    pub static ref SCRATCH_BASE_DIR: PathBuf = {
        let result = ROOT_DIR.join("target").join("scratch");
        fs::create_dir_all(&result).unwrap();
        result
    };
    pub static ref WASM_DIR: PathBuf = ROOT_DIR.join("target").join("release");
    pub static ref SCRATCH_DIR: PathBuf = {
        // https://doc.rust-lang.org/reference/conditional-compilation.html
        let vendor = if cfg!(target_vendor = "apple") {
            "apple"
        } else if cfg!(target_vendor = "fortanix") {
            "fortanix"
        } else if cfg!(target_vendor = "pc") {
            "pc"
        } else {
            "unknown"
        };
        let env = if cfg!(target_env = "gnu") {
            "gnu"
        } else if cfg!(target_env = "msvc") {
            "msvc"
        } else if cfg!(target_env = "musl") {
            "musl"
        } else if cfg!(target_env = "sgx") {
            "sgx"
        } else {
            "unknown"
        };
        let endian = if cfg!(target_endian = "little") {
            "little"
        } else if cfg!(target_endian = "big") {
            "big"
        } else {
            "unknown"
        };

        let machine = format!("{}-{}-{vendor}-{env}-{endian}", std::env::consts::ARCH, std::env::consts::OS);
        let result = SCRATCH_BASE_DIR.join(machine);
        fs::create_dir_all(&result).unwrap();
        result
    };
}
