use super::highlight::Theme;
use serde_derive::{Deserialize, Serialize};
use std::path::{Path, PathBuf};
use std::{env, fs, io};

#[derive(Default, Deserialize, Serialize)]
pub struct Config {
    #[serde(skip)]
    pub binary_directory: PathBuf,

    #[serde(default)]
    #[serde(rename = "parser-directories")]
    pub parser_directories: Vec<PathBuf>,

    #[serde(default)]
    pub theme: Theme,
}

impl Config {
    pub fn get_path(home_dir: &Path) -> PathBuf {
        env::var("TREE_SITTER_DIR")
            .map(|p| p.into())
            .unwrap_or_else(|_| home_dir.join(".tree-sitter"))
    }

    pub fn load(home_dir: &Path) -> Self {
        let tree_sitter_dir = Self::get_path(home_dir);
        let config_path = tree_sitter_dir.join("config.json");
        let mut result = fs::read_to_string(&config_path)
            .map_err(drop)
            .and_then(|json| serde_json::from_str(&json).map_err(drop))
            .unwrap_or_else(|_| Self::default());
        result.init(home_dir, &tree_sitter_dir);
        result
    }

    pub fn save(&self, home_dir: &Path) -> io::Result<()> {
        let tree_sitter_dir = Self::get_path(home_dir);
        let config_path = tree_sitter_dir.join("config.json");
        let json = serde_json::to_string_pretty(self).expect("Failed to serialize config");
        fs::write(config_path, json)
    }

    pub fn new(home_dir: &Path) -> Self {
        let tree_sitter_dir = Self::get_path(home_dir);
        let mut result = Self::default();
        result.init(home_dir, &tree_sitter_dir);
        result
    }

    fn init(&mut self, home_dir: &Path, tree_sitter_dir: &Path) {
        if self.parser_directories.is_empty() {
            self.parser_directories = vec![
                home_dir.join("github"),
                home_dir.join("src"),
                home_dir.join("source"),
            ]
        }

        let binary_path = tree_sitter_dir.join("bin");
        self.binary_directory = binary_path;
        fs::create_dir_all(&self.binary_directory).unwrap_or_else(|error| {
            panic!(
                "Could not find or create parser binary directory {:?}. Error: {}",
                self.binary_directory, error
            )
        });
    }
}
