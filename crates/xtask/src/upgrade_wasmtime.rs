use std::process::Command;

use anyhow::{Context, Result};
use semver::Version;

use crate::{create_commit, UpgradeWasmtime};

const WASMTIME_RELEASE_URL: &str = "https://github.com/bytecodealliance/wasmtime/releases/download";

fn update_cargo(version: &Version) -> Result<()> {
    let file = std::fs::read_to_string("lib/Cargo.toml")?;
    let mut old_lines = file.lines();
    let mut new_lines = Vec::with_capacity(old_lines.size_hint().0);

    while let Some(line) = old_lines.next() {
        new_lines.push(line.to_string());
        if line == "[dependencies.wasmtime-c-api]" {
            let _ = old_lines.next();
            new_lines.push(format!("version = \"{version}\""));
        }
    }

    std::fs::write("lib/Cargo.toml", new_lines.join("\n") + "\n")?;

    Command::new("cargo")
        .arg("update")
        .status()
        .map(|_| ())
        .with_context(|| "Failed to execute cargo update")
}

fn zig_fetch(lines: &mut Vec<String>, version: &Version, url_suffix: &str) -> Result<()> {
    let url = &format!("{WASMTIME_RELEASE_URL}/v{version}/wasmtime-v{version}-{url_suffix}");
    println!("  Fetching {url}");
    lines.push(format!("            .url = \"{url}\","));

    let output = Command::new("zig")
        .arg("fetch")
        .arg(url)
        .output()
        .with_context(|| format!("Failed to execute zig fetch {url}"))?;

    let hash = String::from_utf8_lossy(&output.stdout);
    lines.push(format!("            .hash = \"{}\",", hash.trim_end()));

    Ok(())
}

fn update_zig(version: &Version) -> Result<()> {
    let file = std::fs::read_to_string("build.zig.zon")?;
    let mut old_lines = file.lines();
    let new_lines = &mut Vec::with_capacity(old_lines.size_hint().0);

    macro_rules! match_wasmtime_zig_dep {
        ($line:ident, {$($platform:literal => [$($arch:literal),*]),*,}) => {
            match $line {
                $($(concat!("        .wasmtime_c_api_", $arch, "_", $platform, " = .{") => {
                    let (_, _) = (old_lines.next(), old_lines.next());
                    let suffix = if $platform == "windows" || $platform == "mingw" {
                        concat!($arch, "-", $platform, "-c-api.zip")
                    } else {
                        concat!($arch, "-", $platform, "-c-api.tar.xz")
                    };
                    zig_fetch(new_lines, version, suffix)?;
                })*)*
                _ => {}
            }
        };
    }

    while let Some(line) = old_lines.next() {
        new_lines.push(line.to_string());
        match_wasmtime_zig_dep!(line, {
            "android" => ["aarch64", "x86_64"],
            "linux"   => ["aarch64", "armv7", "i686", "riscv64gc", "s390x", "x86_64"],
            "macos"   => ["aarch64", "x86_64"],
            "mingw"   => ["x86_64"],
            "musl"    => ["aarch64", "x86_64"],
            "windows" => ["aarch64", "i686", "x86_64"],
        });
    }

    std::fs::write("build.zig.zon", new_lines.join("\n") + "\n")?;

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
