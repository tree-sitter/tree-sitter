use std::{cmp::Ordering, path::Path};

use anyhow::{anyhow, Context, Result};
use indoc::indoc;
use semver::{BuildMetadata, Prerelease, Version};

use crate::{create_commit, BumpVersion};

pub fn get_latest_tag() -> Result<String> {
    let output = std::process::Command::new("git")
        .args(["tag", "-l"])
        .output()?;
    if !output.status.success() {
        anyhow::bail!(
            "Failed to list tags: {}",
            String::from_utf8_lossy(&output.stderr)
        );
    }

    let mut tags = String::from_utf8(output.stdout)?
        .lines()
        .filter_map(|tag| Version::parse(tag.strip_prefix('v').unwrap_or(tag)).ok())
        .collect::<Vec<Version>>();

    tags.sort_by(
        |a, b| match (a.pre != Prerelease::EMPTY, b.pre != Prerelease::EMPTY) {
            (true, true) | (false, false) => a.cmp(b),
            (true, false) => Ordering::Less,
            (false, true) => Ordering::Greater,
        },
    );

    tags.last()
        .map(std::string::ToString::to_string)
        .ok_or_else(|| anyhow!("No tags found"))
}

pub fn run(args: BumpVersion) -> Result<()> {
    let latest_tag = get_latest_tag()?;
    let current_version = Version::parse(&latest_tag)?;

    let output = std::process::Command::new("git")
        .args(["rev-parse", &format!("v{latest_tag}")])
        .output()?;
    if !output.status.success() {
        anyhow::bail!(
            "Failed to get tag SHA: {}",
            String::from_utf8_lossy(&output.stderr)
        );
    }
    let latest_tag_sha = String::from_utf8(output.stdout)?.trim().to_string();

    let workspace_toml_version = Version::parse(&fetch_workspace_version()?)?;

    if current_version.major != workspace_toml_version.major
        && current_version.minor != workspace_toml_version.minor
    {
        eprintln!(
            indoc! {"
            Seems like the workspace Cargo.toml ({}) version does not match up with the latest git tag ({}).
            Please ensure you don't change that yourself, this subcommand will handle this for you.
        "},
            workspace_toml_version, latest_tag
        );
        return Ok(());
    }

    let output = std::process::Command::new("git")
        .args(["rev-list", &format!("{latest_tag_sha}..HEAD")])
        .output()?;
    if !output.status.success() {
        anyhow::bail!(
            "Failed to get commits: {}",
            String::from_utf8_lossy(&output.stderr)
        );
    }
    let commits = String::from_utf8(output.stdout)?
        .lines()
        .map(|s| s.to_string())
        .collect::<Vec<_>>();

    let mut should_increment_patch = false;
    let mut should_increment_minor = false;

    for commit_sha in commits {
        let output = std::process::Command::new("git")
            .args(["log", "-1", "--format=%s", &commit_sha])
            .output()?;
        if !output.status.success() {
            continue;
        }
        let message = String::from_utf8(output.stdout)?.trim().to_string();

        let output = std::process::Command::new("git")
            .args([
                "diff-tree",
                "--no-commit-id",
                "--name-only",
                "-r",
                &commit_sha,
            ])
            .output()?;
        if !output.status.success() {
            continue;
        }

        let mut source_code_changed = false;
        for path in String::from_utf8(output.stdout)?.lines() {
            let path = Path::new(path);
            if path.extension().is_some_and(|ext| {
                ext.eq_ignore_ascii_case("rs")
                    || ext.eq_ignore_ascii_case("js")
                    || ext.eq_ignore_ascii_case("c")
            }) {
                source_code_changed = true;
                break;
            }
        }

        if source_code_changed {
            should_increment_patch = true;

            let Some((prefix, _)) = message.split_once(':') else {
                continue;
            };

            let convention = if prefix.contains('(') {
                prefix.split_once('(').unwrap().0
            } else {
                prefix
            };

            if ["feat", "feat!"].contains(&convention) || prefix.ends_with('!') {
                should_increment_minor = true;
            }
        }
    }

    let next_version = if let Some(version) = args.version {
        version
    } else {
        let mut next_version = current_version.clone();
        if should_increment_minor {
            next_version.minor += 1;
            next_version.patch = 0;
            next_version.pre = Prerelease::EMPTY;
            next_version.build = BuildMetadata::EMPTY;
        } else if should_increment_patch {
            next_version.patch += 1;
            next_version.pre = Prerelease::EMPTY;
            next_version.build = BuildMetadata::EMPTY;
        } else {
            return Err(anyhow!(format!(
                "No source code changed since {current_version}"
            )));
        }
        next_version
    };
    if next_version <= current_version {
        return Err(anyhow!(format!(
            "Next version {next_version} must be greater than current version {current_version}"
        )));
    }

    println!("Bumping from {current_version} to {next_version}");
    update_crates(&current_version, &next_version)?;
    update_makefile(&next_version)?;
    update_cmake(&next_version)?;
    update_npm(&next_version)?;
    update_zig(&next_version)?;
    tag_next_version(&next_version)?;

    Ok(())
}

fn tag_next_version(next_version: &Version) -> Result<()> {
    let commit_sha = create_commit(
        &format!("{next_version}"),
        &[
            "Cargo.lock",
            "Cargo.toml",
            "Makefile",
            "build.zig.zon",
            "crates/cli/Cargo.toml",
            "crates/cli/npm/package.json",
            "crates/config/Cargo.toml",
            "crates/highlight/Cargo.toml",
            "crates/loader/Cargo.toml",
            "crates/tags/Cargo.toml",
            "lib/CMakeLists.txt",
            "lib/Cargo.toml",
            "lib/binding_web/package.json",
        ],
    )?;

    // Create tag
    let output = std::process::Command::new("git")
        .args([
            "tag",
            "-a",
            &format!("v{next_version}"),
            "-m",
            &format!("v{next_version}"),
            &commit_sha,
        ])
        .output()?;
    if !output.status.success() {
        anyhow::bail!(
            "Failed to create tag: {}",
            String::from_utf8_lossy(&output.stderr)
        );
    }

    println!("Tagged commit {commit_sha} with tag v{next_version}");

    Ok(())
}

fn update_makefile(next_version: &Version) -> Result<()> {
    let makefile = std::fs::read_to_string("Makefile")?;
    let makefile = makefile
        .lines()
        .map(|line| {
            if line.starts_with("VERSION") {
                format!("VERSION := {next_version}")
            } else {
                line.to_string()
            }
        })
        .collect::<Vec<_>>()
        .join("\n")
        + "\n";

    std::fs::write("Makefile", makefile)?;

    Ok(())
}

fn update_cmake(next_version: &Version) -> Result<()> {
    let cmake = std::fs::read_to_string("lib/CMakeLists.txt")?;
    let cmake = cmake
        .lines()
        .map(|line| {
            if line.contains(" VERSION") {
                let start_quote = line.find('"').unwrap();
                let end_quote = line.rfind('"').unwrap();
                format!(
                    "{}{next_version}{}",
                    &line[..=start_quote],
                    &line[end_quote..]
                )
            } else {
                line.to_string()
            }
        })
        .collect::<Vec<_>>()
        .join("\n")
        + "\n";

    std::fs::write("lib/CMakeLists.txt", cmake)?;

    Ok(())
}

fn update_crates(current_version: &Version, next_version: &Version) -> Result<()> {
    let mut cmd = std::process::Command::new("cargo");
    cmd.arg("workspaces").arg("version");

    if next_version.minor > current_version.minor {
        cmd.arg("minor");
    } else {
        cmd.arg("patch");
    }

    cmd.arg("--no-git-commit")
        .arg("--yes")
        .arg("--force")
        .arg("tree-sitter{,-cli,-config,-generate,-loader,-highlight,-tags}")
        .arg("--ignore-changes")
        .arg("crates/language/*");

    let status = cmd.status()?;

    if !status.success() {
        return Err(anyhow!("Failed to update crates"));
    }

    Ok(())
}

fn update_npm(next_version: &Version) -> Result<()> {
    for path in [
        "lib/binding_web/package.json",
        "crates/cli/npm/package.json",
    ] {
        let package_json = serde_json::from_str::<serde_json::Value>(
            &std::fs::read_to_string(path).with_context(|| format!("Failed to read {path}"))?,
        )?;

        let mut package_json = package_json
            .as_object()
            .ok_or_else(|| anyhow!("Invalid package.json"))?
            .clone();
        package_json.insert(
            "version".to_string(),
            serde_json::Value::String(next_version.to_string()),
        );

        let package_json = serde_json::to_string_pretty(&package_json)? + "\n";

        std::fs::write(path, package_json)?;
    }

    Ok(())
}

fn update_zig(next_version: &Version) -> Result<()> {
    let zig = std::fs::read_to_string("build.zig.zon")?
        .lines()
        .map(|line| {
            if line.starts_with("    .version") {
                format!("    .version = \"{next_version}\",")
            } else {
                line.to_string()
            }
        })
        .collect::<Vec<_>>()
        .join("\n")
        + "\n";

    std::fs::write("build.zig.zon", zig)?;

    Ok(())
}

/// read Cargo.toml and get the version
fn fetch_workspace_version() -> Result<String> {
    std::fs::read_to_string("Cargo.toml")?
        .lines()
        .find(|line| line.starts_with("version = "))
        .and_then(|line| {
            line.split_terminator('"')
                .next_back()
                .map(|s| s.to_string())
        })
        .ok_or_else(|| anyhow!("No version found in Cargo.toml"))
}
