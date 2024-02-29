use std::cmp::Ordering;
use std::path::Path;

use git2::{DiffOptions, Repository};
use indoc::indoc;
use semver::{BuildMetadata, Prerelease, Version};
use toml::Value;

fn increment_patch(v: &mut Version) {
    v.patch += 1;
    v.pre = Prerelease::EMPTY;
    v.build = BuildMetadata::EMPTY;
}

fn increment_minor(v: &mut Version) {
    v.minor += 1;
    v.patch = 0;
    v.pre = Prerelease::EMPTY;
    v.build = BuildMetadata::EMPTY;
}

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
    let mut next_version = None;

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

        let mut update = false;
        diff.foreach(
            &mut |delta, _| {
                let path = delta.new_file().path().unwrap().to_str().unwrap();
                if path.ends_with("rs") || path.ends_with("js") || path.ends_with('c') {
                    update = true;
                }
                true
            },
            None,
            None,
            None,
        )?;

        if update {
            let Some((prefix, _)) = message.split_once(':') else {
                continue;
            };

            let convention = if prefix.contains('(') {
                prefix.split_once('(').unwrap().0
            } else {
                prefix
            };

            match convention {
                "feat" | "feat!" => {
                    let mut cur_version = current_version.clone();
                    increment_minor(&mut cur_version);
                    if let Some(ref ver) = next_version {
                        if cur_version > *ver {
                            next_version = Some(cur_version);
                        }
                    } else {
                        next_version = Some(cur_version);
                    }
                }
                "fix" | "refactor" if prefix.ends_with('!') => {
                    let mut cur_version = current_version.clone();
                    increment_minor(&mut cur_version);
                    if let Some(ref ver) = next_version {
                        if cur_version > *ver {
                            next_version = Some(cur_version);
                        }
                    } else {
                        next_version = Some(cur_version);
                    }
                }
                "fix" | "refactor" => {
                    let mut cur_version = current_version.clone();
                    increment_patch(&mut cur_version);
                    if let Some(ref ver) = next_version {
                        if cur_version > *ver {
                            next_version = Some(cur_version);
                        }
                    } else {
                        next_version = Some(cur_version);
                    }
                }
                _ => {}
            }
        }
    }

    if let Some(ref next_version) = next_version {
        println!("Bumping from {current_version} to {next_version}");

        update_crates(&current_version, next_version)?;

        update_makefile(next_version)?;

        update_npm(next_version)?;

        tag_next_version(&repo, next_version)?;
    }

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
        "cli/Cargo.toml",
        "cli/config/Cargo.toml",
        "cli/loader/Cargo.toml",
        "lib/Cargo.toml",
        "highlight/Cargo.toml",
        "tags/Cargo.toml",
        "cli/npm/package.json",
        "lib/binding_web/package.json",
        "Makefile",
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

    cmd.arg("--no-git-commit").arg("--yes");

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

/// read Cargo.toml and get the version
fn fetch_workspace_version() -> Result<String, Box<dyn std::error::Error>> {
    let cargo_toml = toml::from_str::<Value>(&std::fs::read_to_string("Cargo.toml")?)?;

    Ok(cargo_toml["workspace"]["package"]["version"]
        .as_str()
        .unwrap()
        .trim_matches('"')
        .to_string())
}
