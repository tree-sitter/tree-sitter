use std::{cmp::Ordering, path::Path};

use git2::{DiffOptions, Repository};
use indoc::indoc;
use semver::{BuildMetadata, Prerelease, Version};
use toml::Value;

pub fn get_latest_tag(repo: &Repository) -> Result<String, Box<dyn std::error::Error>> {
    let mut tags = repo
        .tag_names(None)?
        .into_iter()
        .filter_map(|tag| tag.map(String::from))
        .filter_map(|tag| Version::parse(tag.strip_prefix('v').unwrap_or(&tag)).ok())
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
        .ok_or_else(|| "No tags found".into())
}

pub fn bump_versions() -> Result<(), Box<dyn std::error::Error>> {
    let repo = Repository::open(".")?;
    let latest_tag = get_latest_tag(&repo)?;
    let latest_tag_sha = repo.revparse_single(&format!("v{latest_tag}"))?.id();

    let workspace_toml_version = fetch_workspace_version()?;

    if latest_tag != workspace_toml_version {
        eprintln!(
            indoc! {"
            Seems like the workspace Cargo.toml ({}) version does not match up with the latest git tag ({}).
            Please ensure you don't change that yourself, this subcommand will handle this for you.
        "},
            workspace_toml_version, latest_tag
        );
        return Ok(());
    }

    let mut revwalk = repo.revwalk()?;
    revwalk.push_range(format!("{latest_tag_sha}..HEAD").as_str())?;
    let mut diff_options = DiffOptions::new();

    let current_version = Version::parse(&latest_tag)?;
    let mut should_increment_patch = false;
    let mut should_increment_minor = false;

    for oid in revwalk {
        let oid = oid?;
        let commit = repo.find_commit(oid)?;
        let message = commit.message().unwrap();
        let message = message.trim();

        let diff = {
            let parent = commit.parent(0).unwrap();
            let parent_tree = parent.tree().unwrap();
            let commit_tree = commit.tree().unwrap();
            repo.diff_tree_to_tree(
                Some(&parent_tree),
                Some(&commit_tree),
                Some(&mut diff_options),
            )?
        };

        let mut source_code_changed = false;
        diff.foreach(
            &mut |delta, _| {
                let path = delta.new_file().path().unwrap().to_str().unwrap();
                if path.ends_with("rs") || path.ends_with("js") || path.ends_with('c') {
                    source_code_changed = true;
                }
                true
            },
            None,
            None,
            None,
        )?;

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

    let mut version = current_version.clone();
    if should_increment_minor {
        version.minor += 1;
        version.patch = 0;
        version.pre = Prerelease::EMPTY;
        version.build = BuildMetadata::EMPTY;
    } else if should_increment_patch {
        version.patch += 1;
        version.pre = Prerelease::EMPTY;
        version.build = BuildMetadata::EMPTY;
    } else {
        return Err(format!("No source code changed since {current_version}").into());
    }

    println!("Bumping from {current_version} to {version}");
    update_crates(&current_version, &version)?;
    update_makefile(&version)?;
    update_npm(&version)?;
    update_zig(&version)?;
    tag_next_version(&repo, &version)?;

    Ok(())
}

fn tag_next_version(
    repo: &Repository,
    next_version: &Version,
) -> Result<(), Box<dyn std::error::Error>> {
    // first add the manifests

    let mut index = repo.index()?;

    for file in [
        "Cargo.toml",
        "Cargo.lock",
        "cli/Cargo.toml",
        "cli/config/Cargo.toml",
        "cli/loader/Cargo.toml",
        "lib/Cargo.toml",
        "highlight/Cargo.toml",
        "tags/Cargo.toml",
        "cli/npm/package.json",
        "lib/binding_web/package.json",
        "Makefile",
        "build.zig.zon",
    ] {
        index.add_path(Path::new(file))?;
    }

    index.write()?;

    let tree_id = index.write_tree()?;
    let tree = repo.find_tree(tree_id)?;
    let signature = repo.signature()?;
    let parent_commit = repo.revparse_single("HEAD")?.peel_to_commit()?;

    let commit_id = repo.commit(
        Some("HEAD"),
        &signature,
        &signature,
        &format!("{next_version}"),
        &tree,
        &[&parent_commit],
    )?;

    let tag = repo.tag(
        &format!("v{next_version}"),
        &repo.find_object(commit_id, None)?,
        &signature,
        &format!("v{next_version}"),
        false,
    )?;

    println!("Tagged commit {commit_id} with tag {tag}");

    Ok(())
}

fn update_makefile(next_version: &Version) -> Result<(), Box<dyn std::error::Error>> {
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

fn update_crates(
    current_version: &Version,
    next_version: &Version,
) -> Result<(), Box<dyn std::error::Error>> {
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
        .arg("*");

    let status = cmd.status()?;

    if !status.success() {
        return Err("Failed to update crates".into());
    }

    Ok(())
}

fn update_npm(next_version: &Version) -> Result<(), Box<dyn std::error::Error>> {
    for path in ["lib/binding_web/package.json", "cli/npm/package.json"] {
        let package_json =
            serde_json::from_str::<serde_json::Value>(&std::fs::read_to_string(path)?)?;

        let mut package_json = package_json
            .as_object()
            .ok_or("Invalid package.json")?
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

fn update_zig(next_version: &Version) -> Result<(), Box<dyn std::error::Error>> {
    let zig = std::fs::read_to_string("build.zig.zon")?;

    let zig = zig
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
fn fetch_workspace_version() -> Result<String, Box<dyn std::error::Error>> {
    let cargo_toml = toml::from_str::<Value>(&std::fs::read_to_string("Cargo.toml")?)?;

    Ok(cargo_toml["workspace"]["package"]["version"]
        .as_str()
        .unwrap()
        .trim_matches('"')
        .to_string())
}
