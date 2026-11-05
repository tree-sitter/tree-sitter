use std::process::Command;

use anyhow::{Context, Result};
use semver::Version;

use crate::{UpgradeWasmtime, bail_on_err, create_commit};

const WASMTIME_RELEASE_URL: &str = "https://github.com/bytecodealliance/wasmtime/releases/download";

fn update_cargo(version: &Version) -> Result<()> {
    let file = std::fs::read_to_string("lib/Cargo.toml")?;
    let mut in_wasmtime_dependency = false;
    let mut updated = false;
    let mut new_lines = Vec::with_capacity(file.lines().size_hint().0);

    for line in file.lines() {
        if line.starts_with('[') {
            in_wasmtime_dependency = line == "[dependencies.wasmtime-c-api]";
        }

        if in_wasmtime_dependency
            && let Some((key, _)) = line.split_once('=')
            && key.trim() == "version"
        {
            new_lines.push(format!("{key}= \"{version}\""));
            updated = true;
        } else {
            new_lines.push(line.to_string());
        }
    }

    if !updated {
        anyhow::bail!("Failed to find wasmtime-c-api version in lib/Cargo.toml");
    }

    std::fs::write("lib/Cargo.toml", new_lines.join("\n") + "\n")?;

    let output = Command::new("cargo")
        .arg("update")
        .spawn()?
        .wait_with_output()?;
    bail_on_err(&output, "Failed to run cargo update")?;

    Ok(())
}

const WASMTIME_PLATFORMS: &[(&str, &[&str])] = &[
    ("android", &["aarch64", "x86_64"]),
    (
        "linux",
        &["aarch64", "armv7", "i686", "riscv64gc", "s390x", "x86_64"],
    ),
    ("macos", &["aarch64", "x86_64"]),
    ("mingw", &["x86_64"]),
    ("musl", &["aarch64", "x86_64"]),
    ("windows", &["aarch64", "i686", "x86_64"]),
];

fn update_zig(version: &Version) -> Result<()> {
    for (platform, arches) in WASMTIME_PLATFORMS {
        let ext = if matches!(*platform, "windows" | "mingw") {
            "zip"
        } else {
            "tar.xz"
        };
        for arch in *arches {
            let name = format!("wasmtime_c_api_{arch}_{platform}");
            let url = format!(
                "{WASMTIME_RELEASE_URL}/v{version}/wasmtime-v{version}-{arch}-{platform}-c-api.{ext}"
            );
            println!("  Fetching {url}");

            // `--save` makes zig fetch into the project-local package directory and update
            // `.url` and `.hash` in place (keeping `.lazy`).
            let output = Command::new("zig")
                .arg("fetch")
                .arg(format!("--save-exact={name}"))
                .arg(&url)
                .output()
                .with_context(|| format!("Failed to execute zig fetch {url}"))?;
            bail_on_err(&output, &format!("`zig fetch {url}` failed"))?;
        }
    }

    Ok(())
}

pub fn run(args: &UpgradeWasmtime) -> Result<()> {
    println!("Upgrading wasmtime for Rust");
    update_cargo(&args.version)?;

    println!("Upgrading wasmtime for Zig");
    update_zig(&args.version)?;

    create_commit(
        &format!("build(deps): bump wasmtime-c-api to v{}", args.version),
        &["lib/Cargo.toml", "Cargo.lock", "build.zig.zon"],
    )?;

    Ok(())
}
