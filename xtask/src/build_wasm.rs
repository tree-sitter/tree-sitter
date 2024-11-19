use std::{
    ffi::{OsStr, OsString},
    fmt::Write,
    fs,
    process::Command,
};

use anyhow::{anyhow, Result};

use crate::{bail_on_err, BuildWasm, EMSCRIPTEN_TAG};

#[derive(PartialEq, Eq)]
enum EmccSource {
    Native,
    Docker,
    Podman,
}

pub fn run_wasm(args: &BuildWasm) -> Result<()> {
    let mut emscripten_flags = vec!["-O3", "--minify", "0"];

    if args.debug {
        emscripten_flags.extend(["-s", "ASSERTIONS=1", "-s", "SAFE_HEAP=1", "-O0", "-g"]);
    }

    if args.verbose {
        emscripten_flags.extend(["-s", "VERBOSE=1", "-v"]);
    }

    let emcc_name = if cfg!(windows) { "emcc.bat" } else { "emcc" };

    // Order of preference: emscripten > docker > podman > error
    let source = if !args.docker && Command::new(emcc_name).output().is_ok() {
        EmccSource::Native
    } else if Command::new("docker")
        .arg("info")
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

    let exported_functions = concat!(
        include_str!("../../lib/src/wasm/stdlib-symbols.txt"),
        include_str!("../../lib/binding_web/exports.txt")
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
    let exported_runtime_methods = "EXPORTED_RUNTIME_METHODS=stringToUTF16,AsciiToString";

    emscripten_flags.extend([
        "-s",
        "WASM=1",
        "-s",
        "INITIAL_MEMORY=33554432",
        "-s",
        "ALLOW_MEMORY_GROWTH=1",
        "-s",
        "SUPPORT_BIG_ENDIAN=1",
        "-s",
        "MAIN_MODULE=2",
        "-s",
        "FILESYSTEM=0",
        "-s",
        "NODEJS_CATCH_EXIT=0",
        "-s",
        "NODEJS_CATCH_REJECTION=0",
        "-s",
        &exported_functions,
        "-s",
        exported_runtime_methods,
        "-fno-exceptions",
        "-std=c11",
        "-D",
        "fprintf(...)=",
        "-D",
        "NDEBUG=",
        "-D",
        "_POSIX_C_SOURCE=200112L",
        "-D",
        "_DEFAULT_SOURCE=",
        "-I",
        "lib/src",
        "-I",
        "lib/include",
        "--js-library",
        "lib/binding_web/imports.js",
        "--pre-js",
        "lib/binding_web/prefix.js",
        "--post-js",
        "lib/binding_web/binding.js",
        "--post-js",
        "lib/binding_web/suffix.js",
        "lib/src/lib.c",
        "lib/binding_web/binding.c",
        "-o",
        "target/scratch/tree-sitter.js",
    ]);

    bail_on_err(
        &command.args(emscripten_flags).spawn()?.wait_with_output()?,
        "Failed to compile the Tree-sitter WASM library",
    )?;

    fs::rename(
        "target/scratch/tree-sitter.js",
        "lib/binding_web/tree-sitter.js",
    )?;

    fs::rename(
        "target/scratch/tree-sitter.wasm",
        "lib/binding_web/tree-sitter.wasm",
    )?;

    Ok(())
}

pub fn run_wasm_stdlib() -> Result<()> {
    let export_flags = include_str!("../../lib/src/wasm/stdlib-symbols.txt")
        .lines()
        .map(|line| format!("-Wl,--export={}", &line[1..line.len() - 1]))
        .collect::<Vec<String>>();

    let mut command = Command::new("target/wasi-sdk-21.0/bin/clang-17");

    let output = command
        .args([
            "-o",
            "stdlib.wasm",
            "-Os",
            "-fPIC",
            "-Wl,--no-entry",
            "-Wl,--stack-first",
            "-Wl,-z",
            "-Wl,stack-size=65536",
            "-Wl,--import-undefined",
            "-Wl,--import-memory",
            "-Wl,--import-table",
            "-Wl,--strip-debug",
            "-Wl,--export=reset_heap",
            "-Wl,--export=__wasm_call_ctors",
            "-Wl,--export=__stack_pointer",
        ])
        .args(export_flags)
        .arg("lib/src/wasm/stdlib.c")
        .output()?;

    bail_on_err(&output, "Failed to compile the Tree-sitter WASM stdlib")?;

    let xxd = Command::new("xxd")
        .args(["-C", "-i", "stdlib.wasm"])
        .output()?;

    bail_on_err(
        &xxd,
        "Failed to run xxd on the compiled Tree-sitter WASM stdlib",
    )?;

    fs::write("lib/src/wasm/wasm-stdlib.h", xxd.stdout)?;

    fs::rename("stdlib.wasm", "target/stdlib.wasm")?;

    Ok(())
}
