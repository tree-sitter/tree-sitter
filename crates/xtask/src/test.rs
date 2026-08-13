use std::{
    env,
    path::Path,
    process::{Command, Stdio},
};

use anyhow::{Result, anyhow};
use regex::Regex;

use crate::{Test, bail_on_err, build_wasm::ensure_wasi_sdk_exists};

pub fn run(args: &Test) -> Result<()> {
    let test_flags = if args.address_sanitizer {
        unsafe { env::set_var("CFLAGS", "-fsanitize=undefined,address") };

        // When the Tree-sitter C library is compiled with the address sanitizer, the address
        // sanitizer runtime library needs to be linked into the final test executable. When
        // using Xcode clang, the Rust linker doesn't know where to find that library, so we
        // need to specify linker flags directly.
        let output = Command::new("cc").arg("-print-runtime-dir").output()?;
        bail_on_err(&output, "Failed to get clang runtime dir")?;
        let runtime_dir = String::from_utf8(output.stdout)?;
        if runtime_dir.contains("/Xcode.app/") {
            unsafe {
                env::set_var(
                    "RUSTFLAGS",
                    format!(
                        "-C link-arg=-L{runtime_dir} -C link-arg=-lclang_rt.asan_osx_dynamic -C link-arg=-Wl,-rpath,{runtime_dir}"
                    ),
                );
            };
        }

        // Specify a `--target` explicitly. This is required for address sanitizer support.
        let output = Command::new("rustup")
            .arg("show")
            .arg("active-toolchain")
            .output()?;
        bail_on_err(&output, "Failed to get active Rust toolchain")?;
        let toolchain = String::from_utf8(output.stdout)?;
        let re = Regex::new(r"(stable|beta|nightly)-([_a-z0-9-]+).*")?;
        let captures = re
            .captures(&toolchain)
            .ok_or_else(|| anyhow!("Failed to parse toolchain '{toolchain}'"))?;
        let current_target = captures.get(2).unwrap().as_str();
        format!("--target={current_target}")
    } else {
        String::new()
    };
    if let Some(language) = &args.language {
        unsafe {
            env::set_var("TREE_SITTER_LANGUAGE", language);
        }
    }
    if let Some(example) = &args.example {
        unsafe {
            env::set_var("TREE_SITTER_EXAMPLE_INCLUDE", example);
        }
    }
    if let Some(seed) = args.seed {
        unsafe {
            env::set_var("TREE_SITTER_SEED", seed.to_string());
        }
    }
    if let Some(iterations) = args.iterations {
        unsafe {
            env::set_var("TREE_SITTER_ITERATIONS", iterations.to_string());
        }
    }
    if args.debug {
        unsafe {
            env::set_var("TREE_SITTER_LOG", "1");
        }
    }
    if args.debug_graph {
        unsafe {
            env::set_var("TREE_SITTER_LOG_GRAPHS", "1");
        }
    }

    if args.g {
        let mut cargo_cmd = Command::new("cargo");
        cargo_cmd
            .arg("test")
            .arg("--all")
            .arg(&test_flags)
            .arg("--no-run")
            .arg("--message-format=json");

        let cargo_cmd = cargo_cmd.stdout(Stdio::piped()).spawn()?;

        let jq_cmd = Command::new("jq")
            .arg("-rs")
            .arg(r#"map(select(.target.name == "tree_sitter_cli" and .executable))[0].executable"#)
            .stdin(cargo_cmd.stdout.unwrap())
            .output()?;

        let test_binary = String::from_utf8(jq_cmd.stdout)?;

        let mut lldb_cmd = Command::new("lldb");
        lldb_cmd.arg(test_binary.trim()).arg("--").args(&args.args);
        bail_on_err(
            &lldb_cmd.spawn()?.wait_with_output()?,
            &format!("Failed to run {lldb_cmd:?}"),
        )?;
    } else {
        let mut cargo_cmd = Command::new("cargo");
        cargo_cmd.arg("test").arg("--all");
        if args.wasm {
            cargo_cmd.arg("--features").arg("wasm");
        }
        if !test_flags.is_empty() {
            cargo_cmd.arg(&test_flags);
        }
        cargo_cmd.args(&args.args);

        if args.nocapture {
            #[cfg(not(target_os = "windows"))]
            cargo_cmd.arg("--");

            cargo_cmd.arg("--nocapture");
        }
        bail_on_err(
            &cargo_cmd.spawn()?.wait_with_output()?,
            &format!("Failed to run {cargo_cmd:?}"),
        )?;
    }

    Ok(())
}

pub fn run_wasm() -> Result<()> {
    std::env::set_current_dir("lib/binding_web")?;

    let node_modules_dir = Path::new("node_modules");
    let npm = if cfg!(target_os = "windows") {
        "npm.cmd"
    } else {
        "npm"
    };

    if !node_modules_dir.join("chai").exists() || !node_modules_dir.join("mocha").exists() {
        println!("Installing test dependencies...");
        let output = Command::new(npm).arg("install").output()?;
        bail_on_err(&output, "Failed to install test dependencies")?;
    }

    let child = Command::new(npm).arg("test").spawn()?;
    let output = child.wait_with_output()?;
    bail_on_err(&output, &format!("Failed to run `{npm} test`"))?;

    // Display test results
    let output = String::from_utf8_lossy(&output.stdout);
    for line in output.lines() {
        println!("{line}");
    }

    Ok(())
}

pub fn run_rust_wasm_web() -> Result<()> {
    let clang = ensure_wasi_sdk_exists()?;
    let manifest_path = Path::new("test/fixtures/rust_wasm_web/Cargo.toml");
    let grammar_path = Path::new("test/fixtures/grammars/javascript/grammar.js");
    let target_dir = Path::new("target/rust-wasm-web-test");
    let target = "wasm32-unknown-unknown";
    std::fs::create_dir_all(target_dir)?;

    let mut generate = Command::new("cargo");
    generate.args([
        "run",
        "-p",
        "tree-sitter-cli",
        "--",
        "generate",
        "--abi",
        "15",
        grammar_path.to_str().unwrap(),
    ]);
    bail_on_err(
        &generate.output()?,
        "Failed to generate the Rust Wasm web test language",
    )?;

    let language_dir = grammar_path.parent().unwrap();
    let language_path = env::current_dir()?.join(target_dir.join("tree-sitter-javascript.wasm"));
    let scanner_shim =
        env::current_dir()?.join("test/fixtures/rust_wasm_web/src/javascript_scanner_shim.c");
    let mut compile_language = Command::new(&clang);
    compile_language.current_dir(language_dir).args([
        "--target=wasm32-wasip1",
        "-matomics",
        "-mbulk-memory",
        "-o",
        language_path.to_str().unwrap(),
        "-fPIC",
        "-shared",
        "--no-wasm-opt",
        "-Os",
        "-Wl,--export=tree_sitter_javascript",
        "-Wl,--allow-undefined",
        "-Wl,--no-entry",
        "-Wl,--shared-memory",
        "-Wl,--max-memory=268435456",
        "-nostdlib",
        "-fno-exceptions",
        "-fvisibility=hidden",
        "src/parser.c",
        "src/scanner.c",
        scanner_shim.to_str().unwrap(),
    ]);
    bail_on_err(
        &compile_language.output()?,
        "Failed to compile the Rust Wasm web test language",
    )?;

    let mut cargo = Command::new("cargo");
    let nightly_toolchain =
        env::var("TREE_SITTER_NIGHTLY_TOOLCHAIN").unwrap_or_else(|_| "nightly".to_string());
    cargo
        .args([
            &format!("+{nightly_toolchain}"),
            "build",
            "-Z",
            "build-std=std,panic_abort",
            "--locked",
            "--manifest-path",
            manifest_path.to_str().unwrap(),
            "--target",
            target,
            "--target-dir",
            target_dir.to_str().unwrap(),
        ])
        .env("CC_wasm32_unknown_unknown", clang)
        .env("CFLAGS_wasm32_unknown_unknown", "-matomics -mbulk-memory")
        .env(
            "RUSTFLAGS",
            "-D warnings -A unstable-features -C target-feature=+atomics,+bulk-memory,+mutable-globals -C link-arg=--import-memory -C link-arg=--shared-memory -C link-arg=--max-memory=268435456 -C link-arg=--export-table -C link-arg=--growable-table -C link-arg=--export=__stack_pointer",
        );
    bail_on_err(&cargo.output()?, "Failed to compile the Rust Wasm web test")?;

    let runtime_path = target_dir
        .join(target)
        .join("debug")
        .join("rust_wasm_web_test.wasm");
    let node = env::var_os("EMSDK_NODE").unwrap_or_else(|| "node".into());
    let mut command = Command::new(node);
    command.args([
        "test/fixtures/rust_wasm_web/run.mjs",
        runtime_path.to_str().unwrap(),
        language_path.to_str().unwrap(),
    ]);
    bail_on_err(&command.output()?, "Failed to run the Rust Wasm web test")?;
    println!("Rust Wasm web test passed");
    Ok(())
}
