#![cfg_attr(not(any(test, doctest)), doc = include_str!("../README.md"))]

use std::{
    env, fs,
    path::{Path, PathBuf},
};

use etcetera::BaseStrategy as _;
use log::warn;
use serde::{Deserialize, Serialize};
use serde_json::Value;
use thiserror::Error;

pub type ConfigResult<T> = Result<T, ConfigError>;

#[derive(Debug, Error)]
pub enum ConfigError {
    #[error("Bad JSON config {0} -- {1}")]
    ConfigRead(String, serde_json::Error),
    #[error(transparent)]
    HomeDir(#[from] etcetera::HomeDirError),
    #[error(transparent)]
    IO(IoError),
    #[error(transparent)]
    Serialization(#[from] serde_json::Error),
}

#[derive(Debug, Error)]
pub struct IoError {
    pub error: std::io::Error,
    pub path: Option<String>,
}

impl IoError {
    fn new(error: std::io::Error, path: Option<&Path>) -> Self {
        Self {
            error,
            path: path.map(|p| p.to_string_lossy().to_string()),
        }
    }
}

impl std::fmt::Display for IoError {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "{}", self.error)?;
        if let Some(ref path) = self.path {
            write!(f, " ({path})")?;
        }
        Ok(())
    }
}

/// Holds the contents of tree-sitter's configuration file.
///
/// The file typically lives at `~/.config/tree-sitter/config.json`, but see the [`Config::load`][]
/// method for the full details on where it might be located.
///
/// This type holds the generic JSON content of the configuration file.  Individual tree-sitter
/// components will use the [`Config::get`][] method to parse that JSON to extract configuration
/// fields that are specific to that component.
#[derive(Debug)]
pub struct Config {
    pub location: PathBuf,
    pub config: Value,
}

impl Config {
    pub fn find_config_file() -> ConfigResult<Option<PathBuf>> {
        if let Ok(path) = env::var("TREE_SITTER_DIR") {
            let mut path = PathBuf::from(path);
            path.push("config.json");
            if !path.exists() {
                return Ok(None);
            }
            if path.is_file() {
                return Ok(Some(path));
            }
        }

        let xdg_path = Self::xdg_config_file()?;
        if xdg_path.is_file() {
            return Ok(Some(xdg_path));
        }

        if cfg!(target_os = "macos") {
            let legacy_apple_path = etcetera::base_strategy::Apple::new()?
                .data_dir() // `$HOME/Library/Application Support/`
                .join("tree-sitter")
                .join("config.json");
            if legacy_apple_path.is_file() {
                let xdg_dir = xdg_path.parent().unwrap();
                fs::create_dir_all(xdg_dir)
                    .map_err(|e| ConfigError::IO(IoError::new(e, Some(xdg_dir))))?;
                fs::rename(&legacy_apple_path, &xdg_path).map_err(|e| {
                    ConfigError::IO(IoError::new(e, Some(legacy_apple_path.as_path())))
                })?;
                warn!(
                    "Your config.json file has been automatically migrated from \"{}\" to \"{}\"",
                    legacy_apple_path.display(),
                    xdg_path.display()
                );
                return Ok(Some(xdg_path));
            }
        }

        let legacy_path = etcetera::home_dir()?
            .join(".tree-sitter")
            .join("config.json");
        if legacy_path.is_file() {
            return Ok(Some(legacy_path));
        }

        Ok(None)
    }

    fn xdg_config_file() -> ConfigResult<PathBuf> {
        let xdg_path = etcetera::choose_base_strategy()?
            .config_dir()
            .join("tree-sitter")
            .join("config.json");
        Ok(xdg_path)
    }

    /// Locates and loads in the user's configuration file.  We search for the configuration file
    /// in the following locations, in order:
    ///
    ///   - Location specified by the path parameter if provided
    ///   - `$TREE_SITTER_DIR/config.json`, if the `TREE_SITTER_DIR` environment variable is set
    ///   - `tree-sitter/config.json` in your default user configuration directory, as determined by
    ///     [`etcetera::choose_base_strategy`](https://docs.rs/etcetera/*/etcetera/#basestrategy)
    ///   - `$HOME/.tree-sitter/config.json` as a fallback from where tree-sitter _used_ to store
    ///     its configuration
    pub fn load(path: Option<PathBuf>) -> ConfigResult<Self> {
        let location = if let Some(path) = path {
            path
        } else if let Some(path) = Self::find_config_file()? {
            path
        } else {
            return Self::initial();
        };

        let content = fs::read_to_string(&location)
            .map_err(|e| ConfigError::IO(IoError::new(e, Some(location.as_path()))))?;
        let config = serde_json::from_str(&content)
            .map_err(|e| ConfigError::ConfigRead(location.to_string_lossy().to_string(), e))?;
        Ok(Self { location, config })
    }

    /// Creates an empty initial configuration file.  You can then use the [`Config::add`][] method
    /// to add the component-specific configuration types for any components that want to add
    /// content to the default file, and then use [`Config::save`][] to write the configuration to
    /// disk.
    ///
    /// (Note that this is typically only done by the `tree-sitter init-config` command.)
    pub fn initial() -> ConfigResult<Self> {
        let location = if let Ok(path) = env::var("TREE_SITTER_DIR") {
            let mut path = PathBuf::from(path);
            path.push("config.json");
            path
        } else {
            Self::xdg_config_file()?
        };
        let config = serde_json::json!({});
        Ok(Self { location, config })
    }

    /// Saves this configuration to the file that it was originally loaded from.
    pub fn save(&self) -> ConfigResult<()> {
        let json = serde_json::to_string_pretty(&self.config)?;
        let config_dir = self.location.parent().unwrap();
        fs::create_dir_all(config_dir)
            .map_err(|e| ConfigError::IO(IoError::new(e, Some(config_dir))))?;
        fs::write(&self.location, json)
            .map_err(|e| ConfigError::IO(IoError::new(e, Some(self.location.as_path()))))?;
        Ok(())
    }

    /// Parses a component-specific configuration from the configuration file.  The type `C` must
    /// be [deserializable](https://docs.rs/serde/*/serde/trait.Deserialize.html) from a JSON
    /// object, and must only include the fields relevant to that component.
    pub fn get<C>(&self) -> ConfigResult<C>
    where
        C: for<'de> Deserialize<'de>,
    {
        let config = serde_json::from_value(self.config.clone())?;
        Ok(config)
    }

    /// Adds a component-specific configuration to the configuration file.  The type `C` must be
    /// [serializable](https://docs.rs/serde/*/serde/trait.Serialize.html) into a JSON object, and
    /// must only include the fields relevant to that component.
    pub fn add<C>(&mut self, config: C) -> ConfigResult<()>
    where
        C: Serialize,
    {
        let mut config = serde_json::to_value(&config)?;
        self.config
            .as_object_mut()
            .unwrap()
            .append(config.as_object_mut().unwrap());
        Ok(())
    }
}
