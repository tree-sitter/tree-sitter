#![cfg_attr(not(any(test, doctest)), doc = include_str!("../README.md"))]
#![cfg_attr(docsrs, feature(doc_cfg))]

#[cfg(any(feature = "tree-sitter-highlight", feature = "tree-sitter-tags"))]
use std::ops::Range;
#[cfg(feature = "tree-sitter-highlight")]
use std::sync::Mutex;
use std::{
    collections::HashMap,
    env, fs,
    io::{BufRead, BufReader},
    marker::PhantomData,
    mem,
    path::{Path, PathBuf},
    process::Command,
    sync::LazyLock,
    time::{SystemTime, SystemTimeError},
};

use etcetera::BaseStrategy as _;
use fs4::fs_std::FileExt;
use libloading::{Library, Symbol};
use log::{error, info, warn};
use once_cell::unsync::OnceCell;
use regex::{Regex, RegexBuilder};
use semver::Version;
use serde::{Deserialize, Deserializer, Serialize};
use thiserror::Error;
use tree_sitter::Language;
#[cfg(any(feature = "tree-sitter-highlight", feature = "tree-sitter-tags"))]
use tree_sitter::QueryError;
#[cfg(feature = "tree-sitter-highlight")]
use tree_sitter::QueryErrorKind;
#[cfg(feature = "wasm")]
use tree_sitter::WasmError;
#[cfg(feature = "tree-sitter-highlight")]
use tree_sitter_highlight::HighlightConfiguration;
#[cfg(feature = "tree-sitter-tags")]
use tree_sitter_tags::{Error as TagsError, TagsConfiguration};

static GRAMMAR_NAME_REGEX: LazyLock<Regex> =
    LazyLock::new(|| Regex::new(r#""name":\s*"(.*?)""#).unwrap());

pub type LoaderResult<T> = Result<T, LoaderError>;

#[derive(Debug, Error)]
pub enum LoaderError {
    #[error(transparent)]
    Compiler(CompilerError),
    #[error("Parser compilation failed.\nStdout: {0}\nStderr: {1}")]
    Compilation(String, String),
    #[error("Failed to execute curl for {0} -- {1}")]
    Curl(String, std::io::Error),
    #[error("Failed to load language in current directory:\n{0}")]
    CurrentDirectoryLoad(Box<Self>),
    #[error("External file path {0} is outside of parser directory {1}")]
    ExternalFile(String, String),
    #[error("Failed to extract archive {0} to {1}")]
    Extraction(String, String),
    #[error("Failed to load language for file name {0}:\n{1}")]
    FileNameLoad(String, Box<Self>),
    #[error("Failed to parse the language name from grammar.json at {0}")]
    GrammarJSON(String),
    #[error(transparent)]
    HomeDir(#[from] etcetera::HomeDirError),
    #[error(transparent)]
    IO(IoError),
    #[error(transparent)]
    Library(LibraryError),
    #[error("Failed to compare binary and source timestamps:\n{0}")]
    ModifiedTime(Box<Self>),
    #[error("No language found")]
    NoLanguage,
    #[error(transparent)]
    Query(LoaderQueryError),
    #[error(transparent)]
    ScannerSymbols(ScannerSymbolError),
    #[error("Failed to load language for scope '{0}':\n{1}")]
    ScopeLoad(String, Box<Self>),
    #[error(transparent)]
    Serialization(#[from] serde_json::Error),
    #[error(transparent)]
    Symbol(SymbolError),
    #[error(transparent)]
    Tags(#[from] TagsError),
    #[error("Failed to execute tar for {0} -- {1}")]
    Tar(String, std::io::Error),
    #[error(transparent)]
    Time(#[from] SystemTimeError),
    #[error("Unknown scope '{0}'")]
    UnknownScope(String),
    #[error("Failed to download wasi-sdk from {0}")]
    WasiSDKDownload(String),
    #[error(transparent)]
    WasiSDKClang(#[from] WasiSDKClangError),
    #[error("Unsupported platform for wasi-sdk")]
    WasiSDKPlatform,
    #[cfg(feature = "wasm")]
    #[error(transparent)]
    Wasm(#[from] WasmError),
    #[error("Failed to run wasi-sdk clang -- {0}")]
    WasmCompiler(std::io::Error),
    #[error("wasi-sdk clang command failed: {0}")]
    WasmCompilation(String),
}

#[derive(Debug, Error)]
pub struct CompilerError {
    pub error: std::io::Error,
    pub command: Box<Command>,
}

impl std::fmt::Display for CompilerError {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(
            f,
            "Failed to execute the C compiler with the following command:\n{:?}\nError: {}",
            *self.command, self.error
        )?;
        Ok(())
    }
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

#[derive(Debug, Error)]
pub struct LibraryError {
    pub error: libloading::Error,
    pub path: String,
}

impl std::fmt::Display for LibraryError {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(
            f,
            "Error opening dynamic library {} -- {}",
            self.path, self.error
        )?;
        Ok(())
    }
}

#[derive(Debug, Error)]
pub struct LoaderQueryError {
    pub error: QueryError,
    pub file: Option<String>,
}

impl std::fmt::Display for LoaderQueryError {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        if let Some(ref path) = self.file {
            writeln!(f, "Error in query file {path}:")?;
        }
        write!(f, "{}", self.error)?;
        Ok(())
    }
}

#[derive(Debug, Error)]
pub struct SymbolError {
    pub error: libloading::Error,
    pub symbol_name: String,
    pub path: String,
}

impl std::fmt::Display for SymbolError {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(
            f,
            "Failed to load symbol {} from {} -- {}",
            self.symbol_name, self.path, self.error
        )?;
        Ok(())
    }
}

#[derive(Debug, Error)]
pub struct ScannerSymbolError {
    pub missing: Vec<String>,
}

impl std::fmt::Display for ScannerSymbolError {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        writeln!(
            f,
            "Missing required functions in the external scanner, parsing won't work without these!\n"
        )?;
        for symbol in &self.missing {
            writeln!(f, "  `{symbol}`")?;
        }
        writeln!(
            f,
            "You can read more about this at https://tree-sitter.github.io/tree-sitter/creating-parsers/4-external-scanners\n"
        )?;
        Ok(())
    }
}

#[derive(Debug, Error)]
pub struct WasiSDKClangError {
    pub wasi_sdk_dir: String,
    pub possible_executables: Vec<&'static str>,
    download: bool,
}

impl std::fmt::Display for WasiSDKClangError {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        if self.download {
            write!(
                f,
                "Failed to find clang executable in downloaded wasi-sdk at '{}'.",
                self.wasi_sdk_dir
            )?;
        } else {
            write!(f, "TREE_SITTER_WASI_SDK_PATH is set to '{}', but no clang executable found in 'bin/' directory.", self.wasi_sdk_dir)?;
        }

        let possible_exes = self.possible_executables.join(", ");
        write!(f, " Looked for: {possible_exes}.")?;

        Ok(())
    }
}

pub const DEFAULT_HIGHLIGHTS_QUERY_FILE_NAME: &str = "highlights.scm";

pub const DEFAULT_INJECTIONS_QUERY_FILE_NAME: &str = "injections.scm";

pub const DEFAULT_LOCALS_QUERY_FILE_NAME: &str = "locals.scm";

pub const DEFAULT_TAGS_QUERY_FILE_NAME: &str = "tags.scm";

#[derive(Default, Deserialize, Serialize)]
pub struct Config {
    #[serde(default)]
    #[serde(
        rename = "parser-directories",
        deserialize_with = "deserialize_parser_directories"
    )]
    pub parser_directories: Vec<PathBuf>,
}

#[derive(Serialize, Deserialize, Clone, Default)]
#[serde(untagged)]
pub enum PathsJSON {
    #[default]
    Empty,
    Single(PathBuf),
    Multiple(Vec<PathBuf>),
}

impl PathsJSON {
    fn into_vec(self) -> Option<Vec<PathBuf>> {
        match self {
            Self::Empty => None,
            Self::Single(s) => Some(vec![s]),
            Self::Multiple(s) => Some(s),
        }
    }

    const fn is_empty(&self) -> bool {
        matches!(self, Self::Empty)
    }

    /// Represent this set of paths as a string that can be included in templates
    #[must_use]
    pub fn to_variable_value<'a>(&'a self, default: &'a PathBuf) -> &'a str {
        match self {
            Self::Empty => Some(default),
            Self::Single(path_buf) => Some(path_buf),
            Self::Multiple(paths) => paths.first(),
        }
        .map_or("", |path| path.as_os_str().to_str().unwrap_or(""))
    }
}

#[derive(Serialize, Deserialize, Clone)]
#[serde(untagged)]
pub enum PackageJSONAuthor {
    String(String),
    Object {
        name: String,
        email: Option<String>,
        url: Option<String>,
    },
}

#[derive(Serialize, Deserialize, Clone)]
#[serde(untagged)]
pub enum PackageJSONRepository {
    String(String),
    Object { url: String },
}

#[derive(Serialize, Deserialize)]
pub struct PackageJSON {
    pub name: String,
    pub version: Version,
    pub description: Option<String>,
    pub author: Option<PackageJSONAuthor>,
    pub maintainers: Option<Vec<PackageJSONAuthor>>,
    pub license: Option<String>,
    pub repository: Option<PackageJSONRepository>,
    #[serde(default)]
    #[serde(rename = "tree-sitter", skip_serializing_if = "Option::is_none")]
    pub tree_sitter: Option<Vec<LanguageConfigurationJSON>>,
}

fn default_path() -> PathBuf {
    PathBuf::from(".")
}

#[derive(Serialize, Deserialize, Clone)]
#[serde(rename_all = "kebab-case")]
pub struct LanguageConfigurationJSON {
    #[serde(default = "default_path")]
    pub path: PathBuf,
    pub scope: Option<String>,
    pub file_types: Option<Vec<String>>,
    pub content_regex: Option<String>,
    pub first_line_regex: Option<String>,
    pub injection_regex: Option<String>,
    #[serde(default, skip_serializing_if = "PathsJSON::is_empty")]
    pub highlights: PathsJSON,
    #[serde(default, skip_serializing_if = "PathsJSON::is_empty")]
    pub injections: PathsJSON,
    #[serde(default, skip_serializing_if = "PathsJSON::is_empty")]
    pub locals: PathsJSON,
    #[serde(default, skip_serializing_if = "PathsJSON::is_empty")]
    pub tags: PathsJSON,
    #[serde(default, skip_serializing_if = "PathsJSON::is_empty")]
    pub external_files: PathsJSON,
}

#[derive(Serialize, Deserialize)]
#[serde(rename_all = "kebab-case")]
pub struct TreeSitterJSON {
    #[serde(rename = "$schema")]
    pub schema: Option<String>,
    pub grammars: Vec<Grammar>,
    pub metadata: Metadata,
    #[serde(default)]
    pub bindings: Bindings,
}

impl TreeSitterJSON {
    pub fn from_file(path: &Path) -> LoaderResult<Self> {
        let path = path.join("tree-sitter.json");
        Ok(serde_json::from_str(&fs::read_to_string(&path).map_err(
            |e| LoaderError::IO(IoError::new(e, Some(path.as_path()))),
        )?)?)
    }

    #[must_use]
    pub fn has_multiple_language_configs(&self) -> bool {
        self.grammars.len() > 1
    }
}

#[derive(Serialize, Deserialize)]
#[serde(rename_all = "kebab-case")]
pub struct Grammar {
    pub name: String,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub camelcase: Option<String>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub title: Option<String>,
    pub scope: String,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub path: Option<PathBuf>,
    #[serde(default, skip_serializing_if = "PathsJSON::is_empty")]
    pub external_files: PathsJSON,
    pub file_types: Option<Vec<String>>,
    #[serde(default, skip_serializing_if = "PathsJSON::is_empty")]
    pub highlights: PathsJSON,
    #[serde(default, skip_serializing_if = "PathsJSON::is_empty")]
    pub injections: PathsJSON,
    #[serde(default, skip_serializing_if = "PathsJSON::is_empty")]
    pub locals: PathsJSON,
    #[serde(default, skip_serializing_if = "PathsJSON::is_empty")]
    pub tags: PathsJSON,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub injection_regex: Option<String>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub first_line_regex: Option<String>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub content_regex: Option<String>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub class_name: Option<String>,
}

#[derive(Serialize, Deserialize)]
pub struct Metadata {
    pub version: Version,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub license: Option<String>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub description: Option<String>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub authors: Option<Vec<Author>>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub links: Option<Links>,
    #[serde(skip)]
    pub namespace: Option<String>,
}

#[derive(Serialize, Deserialize)]
pub struct Author {
    pub name: String,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub email: Option<String>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub url: Option<String>,
}

#[derive(Serialize, Deserialize)]
pub struct Links {
    pub repository: String,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub funding: Option<String>,
}

#[derive(Serialize, Deserialize, Clone)]
#[serde(default)]
pub struct Bindings {
    pub c: bool,
    pub go: bool,
    #[serde(skip)]
    pub java: bool,
    #[serde(skip)]
    pub kotlin: bool,
    pub node: bool,
    pub python: bool,
    pub rust: bool,
    pub swift: bool,
    pub zig: bool,
}

impl Bindings {
    /// return available languages and its default enabled state.
    #[must_use]
    pub const fn languages(&self) -> [(&'static str, bool); 7] {
        [
            ("c", true),
            ("go", true),
            // Comment out Java and Kotlin until the bindings are actually available.
            // ("java", false),
            // ("kotlin", false),
            ("node", true),
            ("python", true),
            ("rust", true),
            ("swift", true),
            ("zig", false),
        ]
    }

    /// construct Bindings from a language list. If a language isn't supported, its name will be put on the error part.
    pub fn with_enabled_languages<'a, I>(languages: I) -> Result<Self, &'a str>
    where
        I: Iterator<Item = &'a str>,
    {
        let mut out = Self {
            c: false,
            go: false,
            java: false,
            kotlin: false,
            node: false,
            python: false,
            rust: false,
            swift: false,
            zig: false,
        };

        for v in languages {
            match v {
                "c" => out.c = true,
                "go" => out.go = true,
                // Comment out Java and Kotlin until the bindings are actually available.
                // "java" => out.java = true,
                // "kotlin" => out.kotlin = true,
                "node" => out.node = true,
                "python" => out.python = true,
                "rust" => out.rust = true,
                "swift" => out.swift = true,
                "zig" => out.zig = true,
                unsupported => return Err(unsupported),
            }
        }

        Ok(out)
    }
}

impl Default for Bindings {
    fn default() -> Self {
        Self {
            c: true,
            go: true,
            java: false,
            kotlin: false,
            node: true,
            python: true,
            rust: true,
            swift: true,
            zig: false,
        }
    }
}

// Replace `~` or `$HOME` with home path string.
// (While paths like "~/.tree-sitter/config.json" can be deserialized,
// they're not valid path for I/O modules.)
fn deserialize_parser_directories<'de, D>(deserializer: D) -> Result<Vec<PathBuf>, D::Error>
where
    D: Deserializer<'de>,
{
    let paths = Vec::<PathBuf>::deserialize(deserializer)?;
    let Ok(home) = etcetera::home_dir() else {
        return Ok(paths);
    };
    let standardized = paths
        .into_iter()
        .map(|path| standardize_path(path, &home))
        .collect();
    Ok(standardized)
}

fn standardize_path(path: PathBuf, home: &Path) -> PathBuf {
    if let Ok(p) = path.strip_prefix("~") {
        return home.join(p);
    }
    if let Ok(p) = path.strip_prefix("$HOME") {
        return home.join(p);
    }
    path
}

impl Config {
    #[must_use]
    pub fn initial() -> Self {
        let home_dir = etcetera::home_dir().expect("Cannot determine home directory");
        Self {
            parser_directories: vec![
                home_dir.join("github"),
                home_dir.join("src"),
                home_dir.join("source"),
                home_dir.join("projects"),
                home_dir.join("dev"),
                home_dir.join("git"),
            ],
        }
    }
}

const BUILD_TARGET: &str = env!("BUILD_TARGET");

pub struct LanguageConfiguration<'a> {
    pub scope: Option<String>,
    pub content_regex: Option<Regex>,
    pub first_line_regex: Option<Regex>,
    pub injection_regex: Option<Regex>,
    pub file_types: Vec<String>,
    pub root_path: PathBuf,
    pub highlights_filenames: Option<Vec<PathBuf>>,
    pub injections_filenames: Option<Vec<PathBuf>>,
    pub locals_filenames: Option<Vec<PathBuf>>,
    pub tags_filenames: Option<Vec<PathBuf>>,
    pub language_name: String,
    language_id: usize,
    #[cfg(feature = "tree-sitter-highlight")]
    highlight_config: OnceCell<Option<HighlightConfiguration>>,
    #[cfg(feature = "tree-sitter-tags")]
    tags_config: OnceCell<Option<TagsConfiguration>>,
    #[cfg(feature = "tree-sitter-highlight")]
    highlight_names: &'a Mutex<Vec<String>>,
    #[cfg(feature = "tree-sitter-highlight")]
    use_all_highlight_names: bool,
    _phantom: PhantomData<&'a ()>,
}

pub struct Loader {
    pub parser_lib_path: PathBuf,
    languages_by_id: Vec<(PathBuf, OnceCell<Language>, Option<Vec<PathBuf>>)>,
    language_configurations: Vec<LanguageConfiguration<'static>>,
    language_configuration_ids_by_file_type: HashMap<String, Vec<usize>>,
    language_configuration_in_current_path: Option<usize>,
    language_configuration_ids_by_first_line_regex: HashMap<String, Vec<usize>>,
    #[cfg(feature = "tree-sitter-highlight")]
    highlight_names: Box<Mutex<Vec<String>>>,
    #[cfg(feature = "tree-sitter-highlight")]
    use_all_highlight_names: bool,
    debug_build: bool,
    sanitize_build: bool,
    force_rebuild: bool,

    #[cfg(feature = "wasm")]
    wasm_store: Mutex<Option<tree_sitter::WasmStore>>,
}

pub struct CompileConfig<'a> {
    pub src_path: &'a Path,
    pub header_paths: Vec<&'a Path>,
    pub parser_path: PathBuf,
    pub scanner_path: Option<PathBuf>,
    pub external_files: Option<&'a [PathBuf]>,
    pub output_path: Option<PathBuf>,
    pub flags: &'a [&'a str],
    pub sanitize: bool,
    pub name: String,
}

impl<'a> CompileConfig<'a> {
    #[must_use]
    pub fn new(
        src_path: &'a Path,
        externals: Option<&'a [PathBuf]>,
        output_path: Option<PathBuf>,
    ) -> Self {
        Self {
            src_path,
            header_paths: vec![src_path],
            parser_path: src_path.join("parser.c"),
            scanner_path: None,
            external_files: externals,
            output_path,
            flags: &[],
            sanitize: false,
            name: String::new(),
        }
    }
}

unsafe impl Sync for Loader {}

impl Loader {
    pub fn new() -> LoaderResult<Self> {
        let parser_lib_path = if let Ok(path) = env::var("TREE_SITTER_LIBDIR") {
            PathBuf::from(path)
        } else {
            if cfg!(target_os = "macos") {
                let legacy_apple_path = etcetera::base_strategy::Apple::new()?
                    .cache_dir() // `$HOME/Library/Caches/`
                    .join("tree-sitter");
                if legacy_apple_path.exists() && legacy_apple_path.is_dir() {
                    std::fs::remove_dir_all(&legacy_apple_path).map_err(|e| {
                        LoaderError::IO(IoError::new(e, Some(legacy_apple_path.as_path())))
                    })?;
                }
            }

            etcetera::choose_base_strategy()?
                .cache_dir()
                .join("tree-sitter")
                .join("lib")
        };
        Ok(Self::with_parser_lib_path(parser_lib_path))
    }

    #[must_use]
    pub fn with_parser_lib_path(parser_lib_path: PathBuf) -> Self {
        Self {
            parser_lib_path,
            languages_by_id: Vec::new(),
            language_configurations: Vec::new(),
            language_configuration_ids_by_file_type: HashMap::new(),
            language_configuration_in_current_path: None,
            language_configuration_ids_by_first_line_regex: HashMap::new(),
            #[cfg(feature = "tree-sitter-highlight")]
            highlight_names: Box::new(Mutex::new(Vec::new())),
            #[cfg(feature = "tree-sitter-highlight")]
            use_all_highlight_names: true,
            debug_build: false,
            sanitize_build: false,
            force_rebuild: false,

            #[cfg(feature = "wasm")]
            wasm_store: Mutex::default(),
        }
    }

    #[cfg(feature = "tree-sitter-highlight")]
    #[cfg_attr(docsrs, doc(cfg(feature = "tree-sitter-highlight")))]
    pub fn configure_highlights(&mut self, names: &[String]) {
        self.use_all_highlight_names = false;
        let mut highlights = self.highlight_names.lock().unwrap();
        highlights.clear();
        highlights.extend(names.iter().cloned());
    }

    #[must_use]
    #[cfg(feature = "tree-sitter-highlight")]
    #[cfg_attr(docsrs, doc(cfg(feature = "tree-sitter-highlight")))]
    pub fn highlight_names(&self) -> Vec<String> {
        self.highlight_names.lock().unwrap().clone()
    }

    pub fn find_all_languages(&mut self, config: &Config) -> LoaderResult<()> {
        if config.parser_directories.is_empty() {
            warn!(concat!(
                "You have not configured any parser directories!\n",
                "Please run `tree-sitter init-config` and edit the resulting\n",
                "configuration file to indicate where we should look for\n",
                "language grammars.\n"
            ));
        }
        for parser_container_dir in &config.parser_directories {
            if let Ok(entries) = fs::read_dir(parser_container_dir) {
                for entry in entries {
                    let entry = entry.map_err(|e| LoaderError::IO(IoError::new(e, None)))?;
                    if let Some(parser_dir_name) = entry.file_name().to_str() {
                        if parser_dir_name.starts_with("tree-sitter-") {
                            self.find_language_configurations_at_path(
                                &parser_container_dir.join(parser_dir_name),
                                false,
                            )
                            .ok();
                        }
                    }
                }
            }
        }
        Ok(())
    }

    pub fn languages_at_path(&mut self, path: &Path) -> LoaderResult<Vec<(Language, String)>> {
        if let Ok(configurations) = self.find_language_configurations_at_path(path, true) {
            let mut language_ids = configurations
                .iter()
                .map(|c| (c.language_id, c.language_name.clone()))
                .collect::<Vec<_>>();
            language_ids.sort_unstable();
            language_ids.dedup();
            language_ids
                .into_iter()
                .map(|(id, name)| Ok((self.language_for_id(id)?, name)))
                .collect::<LoaderResult<Vec<_>>>()
        } else {
            Ok(Vec::new())
        }
    }

    #[must_use]
    pub fn get_all_language_configurations(&self) -> Vec<(&LanguageConfiguration, &Path)> {
        self.language_configurations
            .iter()
            .map(|c| (c, self.languages_by_id[c.language_id].0.as_ref()))
            .collect()
    }

    pub fn language_configuration_for_scope(
        &self,
        scope: &str,
    ) -> LoaderResult<Option<(Language, &LanguageConfiguration)>> {
        for configuration in &self.language_configurations {
            if configuration.scope.as_ref().is_some_and(|s| s == scope) {
                let language = self.language_for_id(configuration.language_id)?;
                return Ok(Some((language, configuration)));
            }
        }
        Ok(None)
    }

    pub fn language_configuration_for_first_line_regex(
        &self,
        path: &Path,
    ) -> LoaderResult<Option<(Language, &LanguageConfiguration)>> {
        self.language_configuration_ids_by_first_line_regex
            .iter()
            .try_fold(None, |_, (regex, ids)| {
                if let Some(regex) = Self::regex(Some(regex)) {
                    let file = fs::File::open(path)
                        .map_err(|e| LoaderError::IO(IoError::new(e, Some(path))))?;
                    let reader = BufReader::new(file);
                    let first_line = reader
                        .lines()
                        .next()
                        .transpose()
                        .map_err(|e| LoaderError::IO(IoError::new(e, Some(path))))?;
                    if let Some(first_line) = first_line {
                        if regex.is_match(&first_line) && !ids.is_empty() {
                            let configuration = &self.language_configurations[ids[0]];
                            let language = self.language_for_id(configuration.language_id)?;
                            return Ok(Some((language, configuration)));
                        }
                    }
                }

                Ok(None)
            })
    }

    pub fn language_configuration_for_file_name(
        &self,
        path: &Path,
    ) -> LoaderResult<Option<(Language, &LanguageConfiguration)>> {
        // Find all the language configurations that match this file name
        // or a suffix of the file name.
        let configuration_ids = path
            .file_name()
            .and_then(|n| n.to_str())
            .and_then(|file_name| self.language_configuration_ids_by_file_type.get(file_name))
            .or_else(|| {
                let mut path = path.to_owned();
                let mut extensions = Vec::with_capacity(2);
                while let Some(extension) = path.extension() {
                    extensions.push(extension.to_str()?.to_string());
                    path = PathBuf::from(path.file_stem()?.to_os_string());
                }
                extensions.reverse();
                self.language_configuration_ids_by_file_type
                    .get(&extensions.join("."))
            });

        if let Some(configuration_ids) = configuration_ids {
            if !configuration_ids.is_empty() {
                let configuration = if configuration_ids.len() == 1 {
                    &self.language_configurations[configuration_ids[0]]
                }
                // If multiple language configurations match, then determine which
                // one to use by applying the configurations' content regexes.
                else {
                    let file_contents =
                        fs::read(path).map_err(|e| LoaderError::IO(IoError::new(e, Some(path))))?;
                    let file_contents = String::from_utf8_lossy(&file_contents);
                    let mut best_score = -2isize;
                    let mut best_configuration_id = None;
                    for configuration_id in configuration_ids {
                        let config = &self.language_configurations[*configuration_id];

                        // If the language configuration has a content regex, assign
                        // a score based on the length of the first match.
                        let score;
                        if let Some(content_regex) = &config.content_regex {
                            if let Some(mat) = content_regex.find(&file_contents) {
                                score = (mat.end() - mat.start()) as isize;
                            }
                            // If the content regex does not match, then *penalize* this
                            // language configuration, so that language configurations
                            // without content regexes are preferred over those with
                            // non-matching content regexes.
                            else {
                                score = -1;
                            }
                        } else {
                            score = 0;
                        }
                        if score > best_score {
                            best_configuration_id = Some(*configuration_id);
                            best_score = score;
                        }
                    }

                    &self.language_configurations[best_configuration_id.unwrap()]
                };

                let language = self.language_for_id(configuration.language_id)?;
                return Ok(Some((language, configuration)));
            }
        }

        Ok(None)
    }

    pub fn language_configuration_for_injection_string(
        &self,
        string: &str,
    ) -> LoaderResult<Option<(Language, &LanguageConfiguration)>> {
        let mut best_match_length = 0;
        let mut best_match_position = None;
        for (i, configuration) in self.language_configurations.iter().enumerate() {
            if let Some(injection_regex) = &configuration.injection_regex {
                if let Some(mat) = injection_regex.find(string) {
                    let length = mat.end() - mat.start();
                    if length > best_match_length {
                        best_match_position = Some(i);
                        best_match_length = length;
                    }
                }
            }
        }

        if let Some(i) = best_match_position {
            let configuration = &self.language_configurations[i];
            let language = self.language_for_id(configuration.language_id)?;
            Ok(Some((language, configuration)))
        } else {
            Ok(None)
        }
    }

    pub fn language_for_configuration(
        &self,
        configuration: &LanguageConfiguration,
    ) -> LoaderResult<Language> {
        self.language_for_id(configuration.language_id)
    }

    fn language_for_id(&self, id: usize) -> LoaderResult<Language> {
        let (path, language, externals) = &self.languages_by_id[id];
        language
            .get_or_try_init(|| {
                let src_path = path.join("src");
                self.load_language_at_path(CompileConfig::new(
                    &src_path,
                    externals.as_deref(),
                    None,
                ))
            })
            .cloned()
    }

    pub fn compile_parser_at_path(
        &self,
        grammar_path: &Path,
        output_path: PathBuf,
        flags: &[&str],
    ) -> LoaderResult<()> {
        let src_path = grammar_path.join("src");
        let mut config = CompileConfig::new(&src_path, None, Some(output_path));
        config.flags = flags;
        self.load_language_at_path(config).map(|_| ())
    }

    pub fn load_language_at_path(&self, mut config: CompileConfig) -> LoaderResult<Language> {
        let grammar_path = config.src_path.join("grammar.json");
        config.name = Self::grammar_json_name(&grammar_path)?;
        self.load_language_at_path_with_name(config)
    }

    pub fn load_language_at_path_with_name(
        &self,
        mut config: CompileConfig,
    ) -> LoaderResult<Language> {
        let mut lib_name = config.name.clone();
        let language_fn_name = format!("tree_sitter_{}", config.name.replace('-', "_"));
        if self.debug_build {
            lib_name.push_str(".debug._");
        }

        if self.sanitize_build {
            lib_name.push_str(".sanitize._");
            config.sanitize = true;
        }

        if config.output_path.is_none() {
            fs::create_dir_all(&self.parser_lib_path).map_err(|e| {
                LoaderError::IO(IoError::new(e, Some(self.parser_lib_path.as_path())))
            })?;
        }

        let mut recompile = self.force_rebuild || config.output_path.is_some(); // if specified, always recompile

        let output_path = config.output_path.unwrap_or_else(|| {
            let mut path = self.parser_lib_path.join(lib_name);
            path.set_extension(env::consts::DLL_EXTENSION);
            #[cfg(feature = "wasm")]
            if self.wasm_store.lock().unwrap().is_some() {
                path.set_extension("wasm");
            }
            path
        });
        config.output_path = Some(output_path.clone());

        let parser_path = config.src_path.join("parser.c");
        config.scanner_path = self.get_scanner_path(config.src_path);

        let mut paths_to_check = vec![parser_path];

        if let Some(scanner_path) = config.scanner_path.as_ref() {
            paths_to_check.push(scanner_path.clone());
        }

        paths_to_check.extend(
            config
                .external_files
                .unwrap_or_default()
                .iter()
                .map(|p| config.src_path.join(p)),
        );

        if !recompile {
            recompile = needs_recompile(&output_path, &paths_to_check)?;
        }

        #[cfg(feature = "wasm")]
        if let Some(wasm_store) = self.wasm_store.lock().unwrap().as_mut() {
            if recompile {
                self.compile_parser_to_wasm(
                    &config.name,
                    config.src_path,
                    config
                        .scanner_path
                        .as_ref()
                        .and_then(|p| p.strip_prefix(config.src_path).ok()),
                    &output_path,
                )?;
            }

            let wasm_bytes = fs::read(&output_path)
                .map_err(|e| LoaderError::IO(IoError::new(e, Some(output_path.as_path()))))?;
            return Ok(wasm_store.load_language(&config.name, &wasm_bytes)?);
        }

        let lock_path = if env::var("CROSS_RUNNER").is_ok() {
            tempfile::tempdir()
                .unwrap()
                .path()
                .join("tree-sitter")
                .join("lock")
                .join(format!("{}.lock", config.name))
        } else {
            etcetera::choose_base_strategy()?
                .cache_dir()
                .join("tree-sitter")
                .join("lock")
                .join(format!("{}.lock", config.name))
        };

        if let Ok(lock_file) = fs::OpenOptions::new().write(true).open(&lock_path) {
            recompile = false;
            if lock_file.try_lock_exclusive().is_err() {
                // if we can't acquire the lock, another process is compiling the parser, wait for
                // it and don't recompile
                lock_file
                    .lock_exclusive()
                    .map_err(|e| LoaderError::IO(IoError::new(e, Some(lock_path.as_path()))))?;
                recompile = false;
            } else {
                // if we can acquire the lock, check if the lock file is older than 30 seconds, a
                // run that was interrupted and left the lock file behind should not block
                // subsequent runs
                let time = lock_file
                    .metadata()
                    .map_err(|e| LoaderError::IO(IoError::new(e, Some(lock_path.as_path()))))?
                    .modified()
                    .map_err(|e| LoaderError::IO(IoError::new(e, Some(lock_path.as_path()))))?
                    .elapsed()?
                    .as_secs();
                if time > 30 {
                    fs::remove_file(&lock_path)
                        .map_err(|e| LoaderError::IO(IoError::new(e, Some(lock_path.as_path()))))?;
                    recompile = true;
                }
            }
        }

        if recompile {
            let parent_path = lock_path.parent().unwrap();
            fs::create_dir_all(parent_path)
                .map_err(|e| LoaderError::IO(IoError::new(e, Some(parent_path))))?;
            let lock_file = fs::OpenOptions::new()
                .create(true)
                .truncate(true)
                .write(true)
                .open(&lock_path)
                .map_err(|e| LoaderError::IO(IoError::new(e, Some(lock_path.as_path()))))?;
            lock_file
                .lock_exclusive()
                .map_err(|e| LoaderError::IO(IoError::new(e, Some(lock_path.as_path()))))?;

            self.compile_parser_to_dylib(&config, &lock_file, &lock_path)?;

            if config.scanner_path.is_some() {
                self.check_external_scanner(&config.name, &output_path)?;
            }
        }

        Self::load_language(&output_path, &language_fn_name)
    }

    pub fn load_language(path: &Path, function_name: &str) -> LoaderResult<Language> {
        let library = unsafe { Library::new(path) }.map_err(|e| {
            LoaderError::Library(LibraryError {
                error: e,
                path: path.to_string_lossy().to_string(),
            })
        })?;
        let language = unsafe {
            let language_fn = library
                .get::<Symbol<unsafe extern "C" fn() -> Language>>(function_name.as_bytes())
                .map_err(|e| {
                    LoaderError::Symbol(SymbolError {
                        error: e,
                        symbol_name: function_name.to_string(),
                        path: path.to_string_lossy().to_string(),
                    })
                })?;
            language_fn()
        };
        mem::forget(library);
        Ok(language)
    }

    fn compile_parser_to_dylib(
        &self,
        config: &CompileConfig,
        lock_file: &fs::File,
        lock_path: &Path,
    ) -> LoaderResult<()> {
        let mut cc_config = cc::Build::new();
        cc_config
            .cargo_metadata(false)
            .cargo_warnings(false)
            .target(BUILD_TARGET)
            // BUILD_TARGET from the build environment becomes a runtime host for cc.
            // Otherwise, when cross compiled, cc will keep looking for a cross-compiler
            // on the target system instead of the native compiler.
            .host(BUILD_TARGET)
            .debug(self.debug_build)
            .file(&config.parser_path)
            .includes(&config.header_paths)
            .std("c11");

        if let Some(scanner_path) = config.scanner_path.as_ref() {
            cc_config.file(scanner_path);
        }

        if self.debug_build {
            cc_config.opt_level(0).extra_warnings(true);
        } else {
            cc_config.opt_level(2).extra_warnings(false);
        }

        for flag in config.flags {
            cc_config.define(flag, None);
        }

        let compiler = cc_config.get_compiler();
        let mut command = Command::new(compiler.path());
        command.args(compiler.args());
        for (key, value) in compiler.env() {
            command.env(key, value);
        }

        let output_path = config.output_path.as_ref().unwrap();

        let temp_dir = if compiler.is_like_msvc() {
            let out = format!("-out:{}", output_path.to_str().unwrap());
            command.arg(if self.debug_build { "-LDd" } else { "-LD" });
            command.arg("-utf-8");

            // Windows creates intermediate files when compiling (.exp, .lib, .obj), which causes
            // issues when multiple processes are compiling in the same directory. This creates a
            // temporary directory for those files to go into, which is deleted after compilation.
            let temp_dir = output_path.parent().unwrap().join(format!(
                "tmp_{}_{:?}",
                std::process::id(),
                std::thread::current().id()
            ));
            std::fs::create_dir_all(&temp_dir).unwrap();

            command.arg(format!("/Fo{}\\", temp_dir.display()));
            command.args(cc_config.get_files());
            command.arg("-link").arg(out);
            command.arg(format!("/IMPLIB:{}.lib", temp_dir.join("temp").display()));

            Some(temp_dir)
        } else {
            command.arg("-Werror=implicit-function-declaration");
            if cfg!(any(target_os = "macos", target_os = "ios")) {
                command.arg("-dynamiclib");
                // TODO: remove when supported
                command.arg("-UTREE_SITTER_REUSE_ALLOCATOR");
            } else {
                command.arg("-shared");
            }
            command.args(cc_config.get_files());
            command.arg("-o").arg(output_path);

            None
        };

        let output = command.output().map_err(|e| {
            LoaderError::Compiler(CompilerError {
                error: e,
                command: Box::new(command),
            })
        })?;

        if let Some(temp_dir) = temp_dir {
            let _ = fs::remove_dir_all(temp_dir);
        }

        FileExt::unlock(lock_file)
            .map_err(|e| LoaderError::IO(IoError::new(e, Some(lock_path))))?;
        fs::remove_file(lock_path)
            .map_err(|e| LoaderError::IO(IoError::new(e, Some(lock_path))))?;

        if output.status.success() {
            Ok(())
        } else {
            Err(LoaderError::Compilation(
                String::from_utf8_lossy(&output.stdout).to_string(),
                String::from_utf8_lossy(&output.stderr).to_string(),
            ))
        }
    }

    #[cfg(unix)]
    fn check_external_scanner(&self, name: &str, library_path: &Path) -> LoaderResult<()> {
        let prefix = if cfg!(any(target_os = "macos", target_os = "ios")) {
            "_"
        } else {
            ""
        };
        let section = if cfg!(all(target_arch = "powerpc64", target_os = "linux")) {
            " D "
        } else {
            " T "
        };
        let mut must_have = vec![
            format!("{prefix}tree_sitter_{name}_external_scanner_create"),
            format!("{prefix}tree_sitter_{name}_external_scanner_destroy"),
            format!("{prefix}tree_sitter_{name}_external_scanner_serialize"),
            format!("{prefix}tree_sitter_{name}_external_scanner_deserialize"),
            format!("{prefix}tree_sitter_{name}_external_scanner_scan"),
        ];

        let nm_cmd = env::var("NM").unwrap_or_else(|_| "nm".to_owned());
        let command = Command::new(nm_cmd)
            .arg("--defined-only")
            .arg(library_path)
            .output();
        if let Ok(output) = command {
            if output.status.success() {
                let mut found_non_static = false;
                for line in String::from_utf8_lossy(&output.stdout).lines() {
                    if line.contains(section) {
                        if let Some(function_name) =
                            line.split_whitespace().collect::<Vec<_>>().get(2)
                        {
                            if !line.contains("tree_sitter_") {
                                if !found_non_static {
                                    found_non_static = true;
                                    warn!("Found non-static non-tree-sitter functions in the external scanner");
                                }
                                warn!("  `{function_name}`");
                            } else {
                                must_have.retain(|f| f != function_name);
                            }
                        }
                    }
                }
                if found_non_static {
                    warn!(concat!(
                        "Consider making these functions static, they can cause conflicts ",
                        "when another tree-sitter project uses the same function name."
                    ));
                }

                if !must_have.is_empty() {
                    return Err(LoaderError::ScannerSymbols(ScannerSymbolError {
                        missing: must_have,
                    }));
                }
            }
        }

        Ok(())
    }

    #[cfg(windows)]
    fn check_external_scanner(&self, _name: &str, _library_path: &Path) -> LoaderResult<()> {
        // TODO: there's no nm command on windows, whoever wants to implement this can and should :)

        // let mut must_have = vec![
        //     format!("tree_sitter_{name}_external_scanner_create"),
        //     format!("tree_sitter_{name}_external_scanner_destroy"),
        //     format!("tree_sitter_{name}_external_scanner_serialize"),
        //     format!("tree_sitter_{name}_external_scanner_deserialize"),
        //     format!("tree_sitter_{name}_external_scanner_scan"),
        // ];

        Ok(())
    }

    pub fn compile_parser_to_wasm(
        &self,
        language_name: &str,
        src_path: &Path,
        scanner_filename: Option<&Path>,
        output_path: &Path,
    ) -> LoaderResult<()> {
        let clang_executable = self.ensure_wasi_sdk_exists()?;

        let mut command = Command::new(&clang_executable);
        command.current_dir(src_path).args([
            "-o",
            output_path.to_str().unwrap(),
            "-fPIC",
            "-shared",
            if self.debug_build { "-g" } else { "-Os" },
            format!("-Wl,--export=tree_sitter_{language_name}").as_str(),
            "-Wl,--allow-undefined",
            "-Wl,--no-entry",
            "-nostdlib",
            "-fno-exceptions",
            "-fvisibility=hidden",
            "-I",
            ".",
            "parser.c",
        ]);

        if let Some(scanner_filename) = scanner_filename {
            command.arg(scanner_filename);
        }

        let output = command.output().map_err(LoaderError::WasmCompiler)?;

        if !output.status.success() {
            return Err(LoaderError::WasmCompilation(
                String::from_utf8_lossy(&output.stderr).to_string(),
            ));
        }

        Ok(())
    }

    /// Extracts a tar.gz archive with `tar`, stripping the first path component.
    fn extract_tar_gz_with_strip(
        &self,
        archive_path: &Path,
        destination: &Path,
    ) -> LoaderResult<()> {
        let status = Command::new("tar")
            .arg("-xzf")
            .arg(archive_path)
            .arg("--strip-components=1")
            .arg("-C")
            .arg(destination)
            .status()
            .map_err(|e| LoaderError::Tar(archive_path.to_string_lossy().to_string(), e))?;

        if !status.success() {
            return Err(LoaderError::Extraction(
                archive_path.to_string_lossy().to_string(),
                destination.to_string_lossy().to_string(),
            ));
        }

        Ok(())
    }

    /// This ensures that the wasi-sdk is available, downloading and extracting it if necessary,
    /// and returns the path to the `clang` executable.
    ///
    /// If `TREE_SITTER_WASI_SDK_PATH` is set, it will use that path to look for the clang executable.
    fn ensure_wasi_sdk_exists(&self) -> LoaderResult<PathBuf> {
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

            return Err(LoaderError::WasiSDKClang(WasiSDKClangError {
                wasi_sdk_dir: wasi_sdk_dir.to_string_lossy().to_string(),
                possible_executables,
                download: false,
            }));
        }

        let cache_dir = etcetera::choose_base_strategy()?
            .cache_dir()
            .join("tree-sitter");
        fs::create_dir_all(&cache_dir)
            .map_err(|e| LoaderError::IO(IoError::new(e, Some(cache_dir.as_path()))))?;

        let wasi_sdk_dir = cache_dir.join("wasi-sdk");

        for exe in &possible_executables {
            let clang_exe = wasi_sdk_dir.join("bin").join(exe);
            if clang_exe.exists() {
                return Ok(clang_exe);
            }
        }

        fs::create_dir_all(&wasi_sdk_dir)
            .map_err(|e| LoaderError::IO(IoError::new(e, Some(wasi_sdk_dir.as_path()))))?;

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
            return Err(LoaderError::WasiSDKPlatform);
        };

        let sdk_filename = format!("wasi-sdk-29.0-{arch_os}.tar.gz");
        let sdk_url = format!(
            "https://github.com/WebAssembly/wasi-sdk/releases/download/wasi-sdk-29/{sdk_filename}",
        );

        info!("Downloading wasi-sdk from {sdk_url}...");
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
            return Err(LoaderError::WasiSDKDownload(sdk_url));
        }

        info!("Extracting wasi-sdk to {}...", wasi_sdk_dir.display());
        self.extract_tar_gz_with_strip(&temp_tar_path, &wasi_sdk_dir)?;

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
        }))
    }

    #[must_use]
    #[cfg(feature = "tree-sitter-highlight")]
    pub fn highlight_config_for_injection_string<'a>(
        &'a self,
        string: &str,
    ) -> Option<&'a HighlightConfiguration> {
        match self.language_configuration_for_injection_string(string) {
            Err(e) => {
                error!("Failed to load language for injection string '{string}': {e}",);
                None
            }
            Ok(None) => None,
            Ok(Some((language, configuration))) => {
                match configuration.highlight_config(language, None) {
                    Err(e) => {
                        error!(
                            "Failed to load higlight config for injection string '{string}': {e}"
                        );
                        None
                    }
                    Ok(None) => None,
                    Ok(Some(config)) => Some(config),
                }
            }
        }
    }

    #[must_use]
    pub fn get_language_configuration_in_current_path(&self) -> Option<&LanguageConfiguration> {
        self.language_configuration_in_current_path
            .map(|i| &self.language_configurations[i])
    }

    pub fn find_language_configurations_at_path(
        &mut self,
        parser_path: &Path,
        set_current_path_config: bool,
    ) -> LoaderResult<&[LanguageConfiguration]> {
        let initial_language_configuration_count = self.language_configurations.len();

        match TreeSitterJSON::from_file(parser_path) {
            Ok(config) => {
                let language_count = self.languages_by_id.len();
                for grammar in config.grammars {
                    // Determine the path to the parser directory. This can be specified in
                    // the tree-sitter.json, but defaults to the directory containing the
                    // tree-sitter.json.
                    let language_path =
                        parser_path.join(grammar.path.unwrap_or(PathBuf::from(".")));

                    // Determine if a previous language configuration in this package.json file
                    // already uses the same language.
                    let mut language_id = None;
                    for (id, (path, _, _)) in
                        self.languages_by_id.iter().enumerate().skip(language_count)
                    {
                        if language_path == *path {
                            language_id = Some(id);
                        }
                    }

                    // If not, add a new language path to the list.
                    let language_id = if let Some(language_id) = language_id {
                        language_id
                    } else {
                        self.languages_by_id.push((
                            language_path,
                            OnceCell::new(),
                            grammar
                                .external_files
                                .clone()
                                .into_vec()
                                .map(|files| {
                                    files
                                        .into_iter()
                                        .map(|path| {
                                            let path = parser_path.join(path);
                                            // prevent p being above/outside of parser_path
                                            if path.starts_with(parser_path) {
                                                Ok(path)
                                            } else {
                                                Err(LoaderError::ExternalFile(
                                                    path.to_string_lossy().to_string(),
                                                    parser_path.to_string_lossy().to_string(),
                                                ))
                                            }
                                        })
                                        .collect::<LoaderResult<Vec<_>>>()
                                })
                                .transpose()?,
                        ));
                        self.languages_by_id.len() - 1
                    };

                    let configuration = LanguageConfiguration {
                        root_path: parser_path.to_path_buf(),
                        language_name: grammar.name,
                        scope: Some(grammar.scope),
                        language_id,
                        file_types: grammar.file_types.unwrap_or_default(),
                        content_regex: Self::regex(grammar.content_regex.as_deref()),
                        first_line_regex: Self::regex(grammar.first_line_regex.as_deref()),
                        injection_regex: Self::regex(grammar.injection_regex.as_deref()),
                        injections_filenames: grammar.injections.into_vec(),
                        locals_filenames: grammar.locals.into_vec(),
                        tags_filenames: grammar.tags.into_vec(),
                        highlights_filenames: grammar.highlights.into_vec(),
                        #[cfg(feature = "tree-sitter-highlight")]
                        highlight_config: OnceCell::new(),
                        #[cfg(feature = "tree-sitter-tags")]
                        tags_config: OnceCell::new(),
                        #[cfg(feature = "tree-sitter-highlight")]
                        highlight_names: &self.highlight_names,
                        #[cfg(feature = "tree-sitter-highlight")]
                        use_all_highlight_names: self.use_all_highlight_names,
                        _phantom: PhantomData,
                    };

                    for file_type in &configuration.file_types {
                        self.language_configuration_ids_by_file_type
                            .entry(file_type.clone())
                            .or_default()
                            .push(self.language_configurations.len());
                    }
                    if let Some(first_line_regex) = &configuration.first_line_regex {
                        self.language_configuration_ids_by_first_line_regex
                            .entry(first_line_regex.to_string())
                            .or_default()
                            .push(self.language_configurations.len());
                    }

                    self.language_configurations.push(unsafe {
                        mem::transmute::<LanguageConfiguration<'_>, LanguageConfiguration<'static>>(
                            configuration,
                        )
                    });

                    if set_current_path_config
                        && self.language_configuration_in_current_path.is_none()
                    {
                        self.language_configuration_in_current_path =
                            Some(self.language_configurations.len() - 1);
                    }
                }
            }
            Err(LoaderError::Serialization(e)) => {
                warn!(
                    "Failed to parse {} -- {e}",
                    parser_path.join("tree-sitter.json").display()
                );
            }
            _ => {}
        }

        // If we didn't find any language configurations in the tree-sitter.json file,
        // but there is a grammar.json file, then use the grammar file to form a simple
        // language configuration.
        if self.language_configurations.len() == initial_language_configuration_count
            && parser_path.join("src").join("grammar.json").exists()
        {
            let grammar_path = parser_path.join("src").join("grammar.json");
            let language_name = Self::grammar_json_name(&grammar_path)?;
            let configuration = LanguageConfiguration {
                root_path: parser_path.to_owned(),
                language_name,
                language_id: self.languages_by_id.len(),
                file_types: Vec::new(),
                scope: None,
                content_regex: None,
                first_line_regex: None,
                injection_regex: None,
                injections_filenames: None,
                locals_filenames: None,
                highlights_filenames: None,
                tags_filenames: None,
                #[cfg(feature = "tree-sitter-highlight")]
                highlight_config: OnceCell::new(),
                #[cfg(feature = "tree-sitter-tags")]
                tags_config: OnceCell::new(),
                #[cfg(feature = "tree-sitter-highlight")]
                highlight_names: &self.highlight_names,
                #[cfg(feature = "tree-sitter-highlight")]
                use_all_highlight_names: self.use_all_highlight_names,
                _phantom: PhantomData,
            };
            self.language_configurations.push(unsafe {
                mem::transmute::<LanguageConfiguration<'_>, LanguageConfiguration<'static>>(
                    configuration,
                )
            });
            self.languages_by_id
                .push((parser_path.to_owned(), OnceCell::new(), None));
        }

        Ok(&self.language_configurations[initial_language_configuration_count..])
    }

    fn regex(pattern: Option<&str>) -> Option<Regex> {
        pattern.and_then(|r| RegexBuilder::new(r).multi_line(true).build().ok())
    }

    fn grammar_json_name(grammar_path: &Path) -> LoaderResult<String> {
        let file = fs::File::open(grammar_path)
            .map_err(|e| LoaderError::IO(IoError::new(e, Some(grammar_path))))?;

        let first_three_lines = BufReader::new(file)
            .lines()
            .take(3)
            .collect::<Result<Vec<_>, std::io::Error>>()
            .map_err(|_| LoaderError::GrammarJSON(grammar_path.to_string_lossy().to_string()))?
            .join("\n");

        let name = GRAMMAR_NAME_REGEX
            .captures(&first_three_lines)
            .and_then(|c| c.get(1))
            .ok_or_else(|| LoaderError::GrammarJSON(grammar_path.to_string_lossy().to_string()))?;

        Ok(name.as_str().to_string())
    }

    pub fn select_language(
        &mut self,
        path: &Path,
        current_dir: &Path,
        scope: Option<&str>,
        // path to dynamic library, name of language
        lib_info: Option<&(PathBuf, &str)>,
    ) -> LoaderResult<Language> {
        if let Some((ref lib_path, language_name)) = lib_info {
            let language_fn_name = format!("tree_sitter_{}", language_name.replace('-', "_"));
            Self::load_language(lib_path, &language_fn_name)
        } else if let Some(scope) = scope {
            if let Some(config) = self
                .language_configuration_for_scope(scope)
                .map_err(|e| LoaderError::ScopeLoad(scope.to_string(), Box::new(e)))?
            {
                Ok(config.0)
            } else {
                Err(LoaderError::UnknownScope(scope.to_string()))
            }
        } else if let Some((lang, _)) =
            self.language_configuration_for_file_name(path)
                .map_err(|e| {
                    LoaderError::FileNameLoad(
                        path.file_name().unwrap().to_string_lossy().to_string(),
                        Box::new(e),
                    )
                })?
        {
            Ok(lang)
        } else if let Some(id) = self.language_configuration_in_current_path {
            Ok(self.language_for_id(self.language_configurations[id].language_id)?)
        } else if let Some(lang) = self
            .languages_at_path(current_dir)
            .map_err(|e| LoaderError::CurrentDirectoryLoad(Box::new(e)))?
            .first()
            .cloned()
        {
            Ok(lang.0)
        } else if let Some(lang) = self.language_configuration_for_first_line_regex(path)? {
            Ok(lang.0)
        } else {
            Err(LoaderError::NoLanguage)
        }
    }

    pub const fn debug_build(&mut self, flag: bool) {
        self.debug_build = flag;
    }

    pub const fn sanitize_build(&mut self, flag: bool) {
        self.sanitize_build = flag;
    }

    pub const fn force_rebuild(&mut self, rebuild: bool) {
        self.force_rebuild = rebuild;
    }

    #[cfg(feature = "wasm")]
    #[cfg_attr(docsrs, doc(cfg(feature = "wasm")))]
    pub fn use_wasm(&mut self, engine: &tree_sitter::wasmtime::Engine) {
        *self.wasm_store.lock().unwrap() = Some(tree_sitter::WasmStore::new(engine).unwrap());
    }

    #[must_use]
    pub fn get_scanner_path(&self, src_path: &Path) -> Option<PathBuf> {
        let path = src_path.join("scanner.c");
        path.exists().then_some(path)
    }
}

impl LanguageConfiguration<'_> {
    #[cfg(feature = "tree-sitter-highlight")]
    pub fn highlight_config(
        &self,
        language: Language,
        paths: Option<&[PathBuf]>,
    ) -> LoaderResult<Option<&HighlightConfiguration>> {
        let (highlights_filenames, injections_filenames, locals_filenames) = match paths {
            Some(paths) => (
                Some(
                    paths
                        .iter()
                        .filter(|p| p.ends_with(DEFAULT_HIGHLIGHTS_QUERY_FILE_NAME))
                        .cloned()
                        .collect::<Vec<_>>(),
                ),
                Some(
                    paths
                        .iter()
                        .filter(|p| p.ends_with(DEFAULT_TAGS_QUERY_FILE_NAME))
                        .cloned()
                        .collect::<Vec<_>>(),
                ),
                Some(
                    paths
                        .iter()
                        .filter(|p| p.ends_with(DEFAULT_LOCALS_QUERY_FILE_NAME))
                        .cloned()
                        .collect::<Vec<_>>(),
                ),
            ),
            None => (None, None, None),
        };
        self.highlight_config
            .get_or_try_init(|| {
                let (highlights_query, highlight_ranges) = self.read_queries(
                    if highlights_filenames.is_some() {
                        highlights_filenames.as_deref()
                    } else {
                        self.highlights_filenames.as_deref()
                    },
                    DEFAULT_HIGHLIGHTS_QUERY_FILE_NAME,
                )?;
                let (injections_query, injection_ranges) = self.read_queries(
                    if injections_filenames.is_some() {
                        injections_filenames.as_deref()
                    } else {
                        self.injections_filenames.as_deref()
                    },
                    DEFAULT_INJECTIONS_QUERY_FILE_NAME,
                )?;
                let (locals_query, locals_ranges) = self.read_queries(
                    if locals_filenames.is_some() {
                        locals_filenames.as_deref()
                    } else {
                        self.locals_filenames.as_deref()
                    },
                    DEFAULT_LOCALS_QUERY_FILE_NAME,
                )?;

                if highlights_query.is_empty() {
                    Ok(None)
                } else {
                    let mut result = HighlightConfiguration::new(
                        language,
                        &self.language_name,
                        &highlights_query,
                        &injections_query,
                        &locals_query,
                    )
                    .map_err(|error| match error.kind {
                        QueryErrorKind::Language => {
                            LoaderError::Query(LoaderQueryError { error, file: None })
                        }
                        _ => {
                            if error.offset < injections_query.len() {
                                Self::include_path_in_query_error(
                                    error,
                                    &injection_ranges,
                                    &injections_query,
                                    0,
                                )
                            } else if error.offset < injections_query.len() + locals_query.len() {
                                Self::include_path_in_query_error(
                                    error,
                                    &locals_ranges,
                                    &locals_query,
                                    injections_query.len(),
                                )
                            } else {
                                Self::include_path_in_query_error(
                                    error,
                                    &highlight_ranges,
                                    &highlights_query,
                                    injections_query.len() + locals_query.len(),
                                )
                            }
                        }
                    })?;
                    let mut all_highlight_names = self.highlight_names.lock().unwrap();
                    if self.use_all_highlight_names {
                        for capture_name in result.query.capture_names() {
                            if !all_highlight_names.iter().any(|x| x == capture_name) {
                                all_highlight_names.push((*capture_name).to_string());
                            }
                        }
                    }
                    result.configure(all_highlight_names.as_slice());
                    drop(all_highlight_names);
                    Ok(Some(result))
                }
            })
            .map(Option::as_ref)
    }

    #[cfg(feature = "tree-sitter-tags")]
    pub fn tags_config(&self, language: Language) -> LoaderResult<Option<&TagsConfiguration>> {
        self.tags_config
            .get_or_try_init(|| {
                let (tags_query, tags_ranges) = self
                    .read_queries(self.tags_filenames.as_deref(), DEFAULT_TAGS_QUERY_FILE_NAME)?;
                let (locals_query, locals_ranges) = self.read_queries(
                    self.locals_filenames.as_deref(),
                    DEFAULT_LOCALS_QUERY_FILE_NAME,
                )?;
                if tags_query.is_empty() {
                    Ok(None)
                } else {
                    TagsConfiguration::new(language, &tags_query, &locals_query)
                        .map(Some)
                        .map_err(|error| {
                            if let TagsError::Query(error) = error {
                                if error.offset < locals_query.len() {
                                    Self::include_path_in_query_error(
                                        error,
                                        &locals_ranges,
                                        &locals_query,
                                        0,
                                    )
                                } else {
                                    Self::include_path_in_query_error(
                                        error,
                                        &tags_ranges,
                                        &tags_query,
                                        locals_query.len(),
                                    )
                                }
                            } else {
                                error.into()
                            }
                        })
                }
            })
            .map(Option::as_ref)
    }

    #[cfg(any(feature = "tree-sitter-highlight", feature = "tree-sitter-tags"))]
    fn include_path_in_query_error(
        mut error: QueryError,
        ranges: &[(PathBuf, Range<usize>)],
        source: &str,
        start_offset: usize,
    ) -> LoaderError {
        let offset_within_section = error.offset - start_offset;
        let (path, range) = ranges
            .iter()
            .find(|(_, range)| range.contains(&offset_within_section))
            .unwrap_or_else(|| ranges.last().unwrap());
        error.offset = offset_within_section - range.start;
        error.row = source[range.start..offset_within_section]
            .matches('\n')
            .count();
        LoaderError::Query(LoaderQueryError {
            error,
            file: Some(path.to_string_lossy().to_string()),
        })
    }

    #[allow(clippy::type_complexity)]
    #[cfg(any(feature = "tree-sitter-highlight", feature = "tree-sitter-tags"))]
    fn read_queries(
        &self,
        paths: Option<&[PathBuf]>,
        default_path: &str,
    ) -> LoaderResult<(String, Vec<(PathBuf, Range<usize>)>)> {
        let mut query = String::new();
        let mut path_ranges = Vec::new();
        if let Some(paths) = paths {
            for path in paths {
                let abs_path = self.root_path.join(path);
                let prev_query_len = query.len();
                query += &fs::read_to_string(&abs_path)
                    .map_err(|e| LoaderError::IO(IoError::new(e, Some(abs_path.as_path()))))?;
                path_ranges.push((path.clone(), prev_query_len..query.len()));
            }
        } else {
            // highlights.scm is needed to test highlights, and tags.scm to test tags
            if default_path == DEFAULT_HIGHLIGHTS_QUERY_FILE_NAME
                || default_path == DEFAULT_TAGS_QUERY_FILE_NAME
            {
                warn!(
                    concat!(
                        "You should add a `{}` entry pointing to the {} path in the `tree-sitter` ",
                        "object in the grammar's tree-sitter.json file. See more here: ",
                        "https://tree-sitter.github.io/tree-sitter/3-syntax-highlighting#query-paths"
                    ),
                    default_path.replace(".scm", ""),
                    default_path
                );
            }
            let queries_path = self.root_path.join("queries");
            let path = queries_path.join(default_path);
            if path.exists() {
                query = fs::read_to_string(&path)
                    .map_err(|e| LoaderError::IO(IoError::new(e, Some(path.as_path()))))?;
                path_ranges.push((PathBuf::from(default_path), 0..query.len()));
            }
        }

        Ok((query, path_ranges))
    }
}

fn needs_recompile(lib_path: &Path, paths_to_check: &[PathBuf]) -> LoaderResult<bool> {
    if !lib_path.exists() {
        return Ok(true);
    }
    let lib_mtime = mtime(lib_path).map_err(|e| LoaderError::ModifiedTime(Box::new(e)))?;
    for path in paths_to_check {
        if mtime(path).map_err(|e| LoaderError::ModifiedTime(Box::new(e)))? > lib_mtime {
            return Ok(true);
        }
    }
    Ok(false)
}

fn mtime(path: &Path) -> LoaderResult<SystemTime> {
    fs::metadata(path)
        .map_err(|e| LoaderError::IO(IoError::new(e, Some(path))))?
        .modified()
        .map_err(|e| LoaderError::IO(IoError::new(e, Some(path))))
}
