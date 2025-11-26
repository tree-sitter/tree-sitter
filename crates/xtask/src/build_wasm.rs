use std::{
    collections::HashSet,
    ffi::{OsStr, OsString},
    fmt::Write,
    fs,
    path::{Path, PathBuf},
    process::Command,
    time::Duration,
};

use anyhow::{anyhow, Result};
use etcetera::BaseStrategy as _;
use indoc::indoc;
use notify::{
    event::{AccessKind, AccessMode},
    EventKind, RecursiveMode,
};
use notify_debouncer_full::new_debouncer;
use tree_sitter_loader::{IoError, LoaderError, WasiSDKClangError};

use crate::{
    bail_on_err, embed_sources::embed_sources_in_map, watch_wasm, BuildWasm, EMSCRIPTEN_TAG,
};

#[derive(PartialEq, Eq)]
enum EmccSource {
    Native,
    Docker,
    Podman,
}

const EXPORTED_RUNTIME_METHODS: [&str; 20] = [
    "AsciiToString",
    "stringToUTF8",
    "UTF8ToString",
    "lengthBytesUTF8",
    "stringToUTF16",
    "loadWebAssemblyModule",
    "getValue",
    "setValue",
    "HEAPF32",
    "HEAPF64",
    "HEAP_DATA_VIEW",
    "HEAP8",
    "HEAPU8",
    "HEAP16",
    "HEAPU16",
    "HEAP32",
    "HEAPU32",
    "HEAP64",
    "HEAPU64",
    "LE_HEAP_STORE_I64",
];

const WASI_SDK_VERSION: &str = include_str!("../../loader/wasi-sdk-version").trim_ascii();

pub fn run_wasm(args: &BuildWasm) -> Result<()> {
    let mut emscripten_flags = if args.debug {
        vec!["-O0", "--minify", "0"]
    } else {
        vec!["-O3", "--minify", "0"]
    };

    if args.debug {
        emscripten_flags.extend(["-s", "ASSERTIONS=1", "-s", "SAFE_HEAP=1", "-g"]);
    }

    if args.verbose {
        emscripten_flags.extend(["-s", "VERBOSE=1", "-v"]);
    }

    let emcc_name = if cfg!(windows) { "emcc.bat" } else { "emcc" };

    // Order of preference: emscripten > docker > podman > error
    let source = if !args.docker && Command::new(emcc_name).output().is_ok() {
        EmccSource::Native
    } else if Command::new("docker")
        .output()
        .is_ok_and(|out| out.status.success())
    {
        EmccSource::Docker
    } else if Command::new("podman")
        .arg("--version")
        .output()
        .is_ok_and(|out| out.status.success())
    {
        EmccSource::Podman
    } else {
        return Err(anyhow!(
            "You must have either emcc, docker, or podman on your PATH to run this command"
        ));
    };

    let mut command = match source {
        EmccSource::Native => Command::new(emcc_name),
        EmccSource::Docker | EmccSource::Podman => {
            let mut command = match source {
                EmccSource::Docker => Command::new("docker"),
                EmccSource::Podman => Command::new("podman"),
                _ => unreachable!(),
            };
            command.args(["run", "--rm"]);

            // Mount the root directory as a volume, which is the repo root
            let mut volume_string = OsString::from(std::env::current_dir().unwrap());
            volume_string.push(":/src:Z");
            command.args([OsStr::new("--volume"), &volume_string]);

            // In case `docker` is an alias to `podman`, ensure that podman
            // mounts the current directory as writable by the container
            // user which has the same uid as the host user. Setting the
            // podman-specific variable is more reliable than attempting to
            // detect whether `docker` is an alias for `podman`.
            // see https://docs.podman.io/en/latest/markdown/podman-run.1.html#userns-mode
            command.env("PODMAN_USERNS", "keep-id");

            // Get the current user id so that files created in the docker container will have
            // the same owner.
            #[cfg(unix)]
            {
                #[link(name = "c")]
                extern "C" {
                    fn getuid() -> u32;
                }
                // don't need to set user for podman since PODMAN_USERNS=keep-id is already set
                if source == EmccSource::Docker {
                    let user_id = unsafe { getuid() };
                    command.args(["--user", &user_id.to_string()]);
                }
            };

            // Run `emcc` in a container using the `emscripten-slim` image
            command.args([EMSCRIPTEN_TAG, "emcc"]);
            command
        }
    };

    fs::create_dir_all("target/scratch").unwrap();

    let exported_functions = format!(
        "{}{}",
        fs::read_to_string("lib/src/wasm/stdlib-symbols.txt")?,
        fs::read_to_string("lib/binding_web/lib/exports.txt")?
    )
    .replace('"', "")
    .lines()
    .fold(String::new(), |mut output, line| {
        let _ = write!(output, "_{line}");
        output
    })
    .trim_end_matches(',')
    .to_string();

    let exported_functions = format!("EXPORTED_FUNCTIONS={exported_functions}");
    let exported_runtime_methods = format!(
        "EXPORTED_RUNTIME_METHODS={}",
        EXPORTED_RUNTIME_METHODS.join(",")
    );

    // Clean up old files from prior runs
    for file in [
        "web-tree-sitter.mjs",
        "web-tree-sitter.cjs",
        "web-tree-sitter.wasm",
        "web-tree-sitter.wasm.map",
    ] {
        fs::remove_file(PathBuf::from("lib/binding_web/lib").join(file)).ok();
    }

    if !args.cjs {
        emscripten_flags.extend(["-s", "EXPORT_ES6=1"]);
    }

    macro_rules! binding_file {
        ($ext:literal) => {
            concat!("lib/binding_web/lib/web-tree-sitter", $ext)
        };
    }

    #[rustfmt::skip]
    emscripten_flags.extend([
        "-gsource-map=inline",
        "-fno-exceptions",
        "-std=c11",
        "-s", "WASM=1",
        "-s", "MODULARIZE=1",
        "-s", "INITIAL_MEMORY=33554432",
        "-s", "ALLOW_MEMORY_GROWTH=1",
        "-s", "SUPPORT_BIG_ENDIAN=1",
        "-s", "WASM_BIGINT=1",
        "-s", "MAIN_MODULE=2",
        "-s", "FILESYSTEM=0",
        "-s", "NODEJS_CATCH_EXIT=0",
        "-s", "NODEJS_CATCH_REJECTION=0",
        "-s", &exported_functions,
        "-s", &exported_runtime_methods,
        "-D", "fprintf(...)=",
        "-D", "printf(...)=",
        "-D", "NDEBUG=",
        "-D", "_POSIX_C_SOURCE=200112L",
        "-D", "_DEFAULT_SOURCE=",
        "-D", "_DARWIN_C_SOURCE=",
        "-I", "lib/src",
        "-I", "lib/include",
        "--js-library", "lib/binding_web/lib/imports.js",
        "--pre-js",     "lib/binding_web/lib/prefix.js",
        "-o",           if args.cjs { binding_file!(".cjs") } else { binding_file!(".mjs") },
        "lib/src/lib.c",
        "lib/binding_web/lib/tree-sitter.c",
    ]);
    if args.emit_tsd {
        emscripten_flags.extend(["--emit-tsd", "web-tree-sitter.d.ts"]);
    }

    let command = command.args(&emscripten_flags);

    if args.watch {
        watch_wasm!(|| build_wasm(command, args.emit_tsd));
    } else {
        build_wasm(command, args.emit_tsd)?;
    }

    Ok(())
}

fn build_wasm(cmd: &mut Command, edit_tsd: bool) -> Result<()> {
    bail_on_err(
        &cmd.spawn()?.wait_with_output()?,
        "Failed to compile the Tree-sitter Wasm library",
    )?;

    if edit_tsd {
        let file = "lib/binding_web/lib/web-tree-sitter.d.ts";
        let content = fs::read_to_string(file)?
            .replace("Automatically generated", "Automatically @generated")
            .replace(
                "AsciiToString(ptr: any): string",
                "AsciiToString(ptr: number): string",
            )
            .replace(
                "stringToUTF8(str: any, outPtr: any, maxBytesToWrite: any): any",
                "stringToUTF8(str: string, outPtr: number, maxBytesToWrite: number): number",
            )
            .replace(
                "UTF8ToString(ptr: number, maxBytesToRead?: number | undefined): string",
                "UTF8ToString(ptr: number, maxBytesToRead?: number): string",
            )
            .replace(
                "lengthBytesUTF8(str: any): number",
                "lengthBytesUTF8(str: string): number",
            )
            .replace(
                "stringToUTF16(str: any, outPtr: any, maxBytesToWrite: any): number",
                "stringToUTF16(str: string, outPtr: number, maxBytesToWrite: number): number",
            )
            .replace(
                concat!(
                    "loadWebAssemblyModule(binary: any, flags: any, libName?: string | ",
                    "undefined, localScope?: any | undefined, handle?: number | undefined): any"
                ),
                concat!(
                    "loadWebAssemblyModule(binary: Uint8Array | WebAssembly.Module, flags: Record<string, boolean>,",
                    " libName?: string, localScope?: Record<string, unknown>, handle?: number):",
                    " Promise<Record<string, () => number>>"
                ),
            )
            .replace(
                "getValue(ptr: number, type?: string): any",
                "getValue(ptr: number, type?: string): number",
            )
            .replace("HEAPF32: any", "HEAPF32: Float32Array")
            .replace("HEAPF64: any", "HEAPF64: Float64Array")
            .replace("HEAP_DATA_VIEW: any", "HEAP_DATA_VIEW: DataView")
            .replace("HEAP8: any", "HEAP8: Int8Array")
            .replace("HEAPU8: any", "HEAPU8: Uint8Array")
            .replace("HEAP16: any", "HEAP16: Int16Array")
            .replace("HEAPU16: any", "HEAPU16: Uint16Array")
            .replace("HEAP32: any", "HEAP32: Int32Array")
            .replace("HEAPU32: any", "HEAPU32: Uint32Array")
            .replace("HEAP64: any", "HEAP64: BigInt64Array")
            .replace("HEAPU64: any", "HEAPU64: BigUint64Array")
            .replace("BigInt;", "bigint;")
            .replace("BigInt)", "bigint)")
            .replace(
                "WasmModule & typeof RuntimeExports;",
                indoc! {"
                WasmModule & typeof RuntimeExports & {
                  currentParseCallback: ((index: number, position: {row: number, column: number}) => string | undefined) | null;
                  currentLogCallback: ((message: string, isLex: boolean) => void) | null;
                  currentProgressCallback: ((state: {currentOffset: number, hasError: boolean}) => void) | null;
                  currentQueryProgressCallback: ((state: {currentOffset: number}) => void) | null;
                };
                "},
            )
            .replace(
                "MainModuleFactory (options?: unknown): Promise<MainModule>",
                "MainModuleFactory(options?: Partial<EmscriptenModule>): Promise<MainModule>",
            );
        fs::write(file, content)?;
    }

    // Post-process the source map to embed source content for optimized builds
    let map_path = Path::new("lib")
        .join("binding_web")
        .join("lib")
        .join("web-tree-sitter.wasm.map");
    if map_path.exists() {
        if let Err(e) = embed_sources_in_map(&map_path) {
            eprintln!("Warning: Failed to embed sources in source map: {e}");
        }
    }

    Ok(())
}

/// This ensures that the wasi-sdk is available, downloading and extracting it if necessary,
/// and returns the path to the `clang` executable.
///
/// If `TREE_SITTER_WASI_SDK_PATH` is set, it will use that path to look for the clang executable.
///
/// Note that this is just a minimially modified version of
/// `tree_sitter_loader::ensure_wasi_sdk_exists`. In the loader, this functionality is implemented
/// as a private method of `Loader`. Rather than add this to the public API, we just
/// re-implement it. Any fixes and/or modifications made to the loader's copy should be reflected
/// here.
pub fn ensure_wasi_sdk_exists() -> Result<PathBuf> {
    let possible_executables = if cfg!(windows) {
        vec![
            "clang.exe",
            "wasm32-unknown-wasi-clang.exe",
            "wasm32-wasi-clang.exe",
        ]
    } else {
        vec!["clang", "wasm32-unknown-wasi-clang", "wasm32-wasi-clang"]
    };

    if let Ok(wasi_sdk_path) = std::env::var("TREE_SITTER_WASI_SDK_PATH") {
        let wasi_sdk_dir = PathBuf::from(wasi_sdk_path);

        for exe in &possible_executables {
            let clang_exe = wasi_sdk_dir.join("bin").join(exe);
            if clang_exe.exists() {
                return Ok(clang_exe);
            }
        }

        Err(LoaderError::WasiSDKClang(WasiSDKClangError {
            wasi_sdk_dir: wasi_sdk_dir.to_string_lossy().to_string(),
            possible_executables: possible_executables.clone(),
            download: false,
        }))?;
    }

    let cache_dir = etcetera::choose_base_strategy()?
        .cache_dir()
        .join("tree-sitter");
    fs::create_dir_all(&cache_dir).map_err(|error| {
        LoaderError::IO(IoError {
            error,
            path: Some(cache_dir.to_string_lossy().to_string()),
        })
    })?;

    let wasi_sdk_dir = cache_dir.join("wasi-sdk");

    for exe in &possible_executables {
        let clang_exe = wasi_sdk_dir.join("bin").join(exe);
        if clang_exe.exists() {
            return Ok(clang_exe);
        }
    }

    fs::create_dir_all(&wasi_sdk_dir).map_err(|error| {
        LoaderError::IO(IoError {
            error,
            path: Some(wasi_sdk_dir.to_string_lossy().to_string()),
        })
    })?;

    let arch_os = if cfg!(target_os = "macos") {
        if cfg!(target_arch = "aarch64") {
            "arm64-macos"
        } else {
            "x86_64-macos"
        }
    } else if cfg!(target_os = "windows") {
        if cfg!(target_arch = "aarch64") {
            "arm64-windows"
        } else {
            "x86_64-windows"
        }
    } else if cfg!(target_os = "linux") {
        if cfg!(target_arch = "aarch64") {
            "arm64-linux"
        } else {
            "x86_64-linux"
        }
    } else {
        Err(LoaderError::WasiSDKPlatform)?
    };

    let sdk_filename = format!("wasi-sdk-{WASI_SDK_VERSION}-{arch_os}.tar.gz");
    let wasi_sdk_major_version = WASI_SDK_VERSION
        .trim_end_matches(char::is_numeric) // trim minor version...
        .trim_end_matches('.'); // ...and '.' separator
    let sdk_url = format!(
        "https://github.com/WebAssembly/wasi-sdk/releases/download/wasi-sdk-{wasi_sdk_major_version}/{sdk_filename}",
    );

    eprintln!("Downloading wasi-sdk from {sdk_url}...");
    let temp_tar_path = cache_dir.join(sdk_filename);

    let status = Command::new("curl")
        .arg("-f")
        .arg("-L")
        .arg("-o")
        .arg(&temp_tar_path)
        .arg(&sdk_url)
        .status()
        .map_err(|e| LoaderError::Curl(sdk_url.clone(), e))?;

    if !status.success() {
        Err(LoaderError::WasiSDKDownload(sdk_url))?;
    }

    eprintln!("Extracting wasi-sdk to {}...", wasi_sdk_dir.display());
    extract_tar_gz_with_strip(&temp_tar_path, &wasi_sdk_dir)?;

    fs::remove_file(temp_tar_path).ok();
    for exe in &possible_executables {
        let clang_exe = wasi_sdk_dir.join("bin").join(exe);
        if clang_exe.exists() {
            return Ok(clang_exe);
        }
    }

    Err(LoaderError::WasiSDKClang(WasiSDKClangError {
        wasi_sdk_dir: wasi_sdk_dir.to_string_lossy().to_string(),
        possible_executables,
        download: true,
    }))?
}

/// Extracts a tar.gz archive with `tar`, stripping the first path component.
fn extract_tar_gz_with_strip(archive_path: &Path, destination: &Path) -> Result<()> {
    let status = Command::new("tar")
        .arg("-xzf")
        .arg(archive_path)
        .arg("--strip-components=1")
        .arg("-C")
        .arg(destination)
        .status()
        .map_err(|e| LoaderError::Tar(archive_path.to_string_lossy().to_string(), e))?;

    if !status.success() {
        Err(LoaderError::Extraction(
            archive_path.to_string_lossy().to_string(),
            destination.to_string_lossy().to_string(),
        ))?;
    }

    Ok(())
}

pub fn run_wasm_stdlib() -> Result<()> {
    let export_flags = include_str!("../../../lib/src/wasm/stdlib-symbols.txt")
        .lines()
        .map(|line| format!("-Wl,--export={}", &line[1..line.len() - 2]))
        .collect::<Vec<String>>();

    let clang_exe = ensure_wasi_sdk_exists()?;

    let output = Command::new(&clang_exe)
        .args([
            "-o",
            "stdlib.wasm",
            "-Os",
            "-fPIC",
            "-DTREE_SITTER_FEATURE_WASM",
            "-Wl,--no-entry",
            "-Wl,--stack-first",
            "-Wl,-z",
            "-Wl,stack-size=65536",
            "-Wl,--import-undefined",
            "-Wl,--import-memory",
            "-Wl,--import-table",
            "-Wl,--strip-debug",
            "-Wl,--export=__wasm_call_ctors",
            "-Wl,--export=__stack_pointer",
            "-Wl,--export=reset_heap",
        ])
        .args(&export_flags)
        .arg("crates/language/wasm/src/stdlib.c")
        .output()?;

    bail_on_err(&output, "Failed to compile the Tree-sitter Wasm stdlib")?;

    let xxd = Command::new("xxd")
        .args(["-C", "-i", "stdlib.wasm"])
        .output()?;

    bail_on_err(
        &xxd,
        "Failed to run xxd on the compiled Tree-sitter Wasm stdlib",
    )?;

    fs::write("lib/src/wasm/wasm-stdlib.h", xxd.stdout)?;

    fs::rename("stdlib.wasm", "target/stdlib.wasm")?;

    Ok(())
}
