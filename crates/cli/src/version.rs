use std::{fs, path::PathBuf, process::Command};

use clap::ValueEnum;
use log::{info, warn};
use regex::Regex;
use semver::Version as SemverVersion;
use std::cmp::Ordering;
use tree_sitter_loader::TreeSitterJSON;

#[derive(Clone, Copy, Default, ValueEnum)]
pub enum BumpLevel {
    #[default]
    Patch,
    Minor,
    Major,
}

pub struct Version {
    pub version: Option<SemverVersion>,
    pub current_dir: PathBuf,
    pub bump: Option<BumpLevel>,
}

#[derive(thiserror::Error, Debug)]
pub enum VersionError {
    #[error(transparent)]
    Json(#[from] serde_json::Error),
    #[error(transparent)]
    Io(#[from] std::io::Error),
    #[error("Failed to update one or more files:\n\n{0}")]
    Update(UpdateErrors),
}

#[derive(thiserror::Error, Debug)]
pub struct UpdateErrors(Vec<UpdateError>);

impl std::fmt::Display for UpdateErrors {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        for error in &self.0 {
            writeln!(f, "{error}\n")?;
        }
        Ok(())
    }
}

#[derive(thiserror::Error, Debug)]
pub enum UpdateError {
    #[error("Failed to update {1}:\n{0}")]
    Io(std::io::Error, PathBuf),
    #[error("Failed to run `{0}`:\n{1}")]
    Command(&'static str, String),
}

impl Version {
    #[must_use]
    pub const fn new(
        version: Option<SemverVersion>,
        current_dir: PathBuf,
        bump: Option<BumpLevel>,
    ) -> Self {
        Self {
            version,
            current_dir,
            bump,
        }
    }

    pub fn run(mut self) -> Result<(), VersionError> {
        let tree_sitter_json = self.current_dir.join("tree-sitter.json");

        let tree_sitter_json =
            serde_json::from_str::<TreeSitterJSON>(&fs::read_to_string(tree_sitter_json)?)?;

        let current_version = tree_sitter_json.metadata.version;
        self.version = match (self.version.is_some(), self.bump) {
            (false, None) => {
                info!("Current version: {current_version}");
                return Ok(());
            }
            (true, None) => self.version,
            (false, Some(bump)) => {
                let mut v = current_version.clone();
                match bump {
                    BumpLevel::Patch => v.patch += 1,
                    BumpLevel::Minor => {
                        v.minor += 1;
                        v.patch = 0;
                    }
                    BumpLevel::Major => {
                        v.major += 1;
                        v.minor = 0;
                        v.patch = 0;
                    }
                }
                Some(v)
            }
            (true, Some(_)) => unreachable!(),
        };

        let new_version = self.version.as_ref().unwrap();
        match new_version.cmp(&current_version) {
            Ordering::Less => {
                warn!("New version is lower than current!");
                warn!("Reverting version {current_version} to {new_version}");
            }
            Ordering::Greater => {
                info!("Bumping version {current_version} to {new_version}");
            }
            Ordering::Equal => {
                info!("Keeping version {current_version}");
            }
        }

        let is_multigrammar = tree_sitter_json.grammars.len() > 1;

        let mut errors = Vec::new();

        // Helper to push errors into the errors vector, returns true if an error was pushed
        let mut push_err = |result: Result<(), UpdateError>| -> bool {
            if let Err(e) = result {
                errors.push(e);
                return true;
            }
            false
        };

        push_err(self.update_treesitter_json());

        // Only update Cargo.lock if Cargo.toml was updated
        push_err(self.update_cargo_toml()).then(|| push_err(self.update_cargo_lock()));

        // Only update package-lock.json if package.json was updated
        push_err(self.update_package_json()).then(|| push_err(self.update_package_lock_json()));

        push_err(self.update_makefile(is_multigrammar));
        push_err(self.update_cmakelists_txt());
        push_err(self.update_pyproject_toml());
        push_err(self.update_zig_zon());

        if errors.is_empty() {
            Ok(())
        } else {
            Err(VersionError::Update(UpdateErrors(errors)))
        }
    }

    fn update_file_with<F>(&self, path: &PathBuf, update_fn: F) -> Result<(), UpdateError>
    where
        F: Fn(&str) -> String,
    {
        let content = fs::read_to_string(path).map_err(|e| UpdateError::Io(e, path.clone()))?;
        let updated_content = update_fn(&content);
        fs::write(path, updated_content).map_err(|e| UpdateError::Io(e, path.clone()))
    }

    fn update_treesitter_json(&self) -> Result<(), UpdateError> {
        let json_path = self.current_dir.join("tree-sitter.json");
        self.update_file_with(&json_path, |content| {
            content
                .lines()
                .map(|line| {
                    if line.contains("\"version\":") {
                        let prefix_index =
                            line.find("\"version\":").unwrap() + "\"version\":".len();
                        let start_quote =
                            line[prefix_index..].find('"').unwrap() + prefix_index + 1;
                        let end_quote =
                            line[start_quote + 1..].find('"').unwrap() + start_quote + 1;

                        format!(
                            "{}{}{}",
                            &line[..start_quote],
                            self.version.as_ref().unwrap(),
                            &line[end_quote..]
                        )
                    } else {
                        line.to_string()
                    }
                })
                .collect::<Vec<_>>()
                .join("\n")
                + "\n"
        })
    }

    fn update_cargo_toml(&self) -> Result<(), UpdateError> {
        let cargo_toml_path = self.current_dir.join("Cargo.toml");
        if !cargo_toml_path.exists() {
            return Ok(());
        }

        self.update_file_with(&cargo_toml_path, |content| {
            content
                .lines()
                .map(|line| {
                    if line.starts_with("version =") {
                        format!("version = \"{}\"", self.version.as_ref().unwrap())
                    } else {
                        line.to_string()
                    }
                })
                .collect::<Vec<_>>()
                .join("\n")
                + "\n"
        })?;

        Ok(())
    }

    fn update_cargo_lock(&self) -> Result<(), UpdateError> {
        if self.current_dir.join("Cargo.lock").exists() {
            let Ok(cmd) = Command::new("cargo")
                .arg("generate-lockfile")
                .arg("--offline")
                .current_dir(&self.current_dir)
                .output()
            else {
                return Ok(()); // cargo is not `executable`, ignore
            };

            if !cmd.status.success() {
                let stderr = String::from_utf8_lossy(&cmd.stderr);
                return Err(UpdateError::Command(
                    "cargo generate-lockfile",
                    stderr.to_string(),
                ));
            }
        }

        Ok(())
    }

    fn update_package_json(&self) -> Result<(), UpdateError> {
        let package_json_path = self.current_dir.join("package.json");
        if !package_json_path.exists() {
            return Ok(());
        }

        self.update_file_with(&package_json_path, |content| {
            content
                .lines()
                .map(|line| {
                    if line.contains("\"version\":") {
                        let prefix_index =
                            line.find("\"version\":").unwrap() + "\"version\":".len();
                        let start_quote =
                            line[prefix_index..].find('"').unwrap() + prefix_index + 1;
                        let end_quote =
                            line[start_quote + 1..].find('"').unwrap() + start_quote + 1;

                        format!(
                            "{}{}{}",
                            &line[..start_quote],
                            self.version.as_ref().unwrap(),
                            &line[end_quote..]
                        )
                    } else {
                        line.to_string()
                    }
                })
                .collect::<Vec<_>>()
                .join("\n")
                + "\n"
        })?;

        Ok(())
    }

    fn update_package_lock_json(&self) -> Result<(), UpdateError> {
        if self.current_dir.join("package-lock.json").exists() {
            let Ok(cmd) = Command::new("npm")
                .arg("install")
                .arg("--package-lock-only")
                .current_dir(&self.current_dir)
                .output()
            else {
                return Ok(()); // npm is not `executable`, ignore
            };

            if !cmd.status.success() {
                let stderr = String::from_utf8_lossy(&cmd.stderr);
                return Err(UpdateError::Command("npm install", stderr.to_string()));
            }
        }

        Ok(())
    }

    fn update_makefile(&self, is_multigrammar: bool) -> Result<(), UpdateError> {
        let makefile_path = if is_multigrammar {
            self.current_dir.join("common").join("common.mak")
        } else {
            self.current_dir.join("Makefile")
        };

        self.update_file_with(&makefile_path, |content| {
            content
                .lines()
                .map(|line| {
                    if line.starts_with("VERSION") {
                        format!("VERSION := {}", self.version.as_ref().unwrap())
                    } else {
                        line.to_string()
                    }
                })
                .collect::<Vec<_>>()
                .join("\n")
                + "\n"
        })?;

        Ok(())
    }

    fn update_cmakelists_txt(&self) -> Result<(), UpdateError> {
        let cmake_lists_path = self.current_dir.join("CMakeLists.txt");
        if !cmake_lists_path.exists() {
            return Ok(());
        }

        self.update_file_with(&cmake_lists_path, |content| {
            let re = Regex::new(r#"(\s*VERSION\s+)"[0-9]+\.[0-9]+\.[0-9]+""#)
                .expect("Failed to compile regex");
            re.replace(
                content,
                format!(r#"$1"{}""#, self.version.as_ref().unwrap()),
            )
            .to_string()
        })?;

        Ok(())
    }

    fn update_pyproject_toml(&self) -> Result<(), UpdateError> {
        let pyproject_toml_path = self.current_dir.join("pyproject.toml");
        if !pyproject_toml_path.exists() {
            return Ok(());
        }

        self.update_file_with(&pyproject_toml_path, |content| {
            content
                .lines()
                .map(|line| {
                    if line.starts_with("version =") {
                        format!("version = \"{}\"", self.version.as_ref().unwrap())
                    } else {
                        line.to_string()
                    }
                })
                .collect::<Vec<_>>()
                .join("\n")
                + "\n"
        })?;

        Ok(())
    }

    fn update_zig_zon(&self) -> Result<(), UpdateError> {
        let zig_zon_path = self.current_dir.join("build.zig.zon");
        if !zig_zon_path.exists() {
            return Ok(());
        }

        self.update_file_with(&zig_zon_path, |content| {
            let zig_version_prefix = ".version =";
            content
                .lines()
                .map(|line| {
                    if line
                        .trim_start_matches(|c: char| c.is_ascii_whitespace())
                        .starts_with(zig_version_prefix)
                    {
                        let prefix_index =
                            line.find(zig_version_prefix).unwrap() + zig_version_prefix.len();
                        let start_quote =
                            line[prefix_index..].find('"').unwrap() + prefix_index + 1;
                        let end_quote =
                            line[start_quote + 1..].find('"').unwrap() + start_quote + 1;

                        format!(
                            "{}{}{}",
                            &line[..start_quote],
                            self.version.as_ref().unwrap(),
                            &line[end_quote..]
                        )
                    } else {
                        line.to_string()
                    }
                })
                .collect::<Vec<_>>()
                .join("\n")
                + "\n"
        })?;

        Ok(())
    }
}
