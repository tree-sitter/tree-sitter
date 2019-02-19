use super::error::{Error, Result};
use libloading::{Library, Symbol};
use once_cell::unsync::OnceCell;
use regex::{Regex, RegexBuilder};
use serde_derive::Deserialize;
use std::collections::HashMap;
use std::io::BufReader;
use std::path::{Path, PathBuf};
use std::process::Command;
use std::time::SystemTime;
use std::{fs, mem};
use tree_sitter::{Language, PropertySheet};
use tree_sitter_highlight::{load_property_sheet, LanguageRegistry, Properties};

#[cfg(unix)]
const DYLIB_EXTENSION: &'static str = "so";

#[cfg(windows)]
const DYLIB_EXTENSION: &'static str = "dll";

const BUILD_TARGET: &'static str = env!("BUILD_TARGET");

struct LanguageRepo {
    path: PathBuf,
    language: OnceCell<Language>,
    configurations: Vec<LanguageConfiguration>,
}

pub struct LanguageConfiguration {
    pub name: String,
    _content_regex: Option<Regex>,
    _first_line_regex: Option<Regex>,
    injection_regex: Option<Regex>,
    file_types: Vec<String>,
    highlight_property_sheet_path: Option<PathBuf>,
    highlight_property_sheet: OnceCell<Option<PropertySheet<Properties>>>,
}

pub struct Loader {
    parser_lib_path: PathBuf,
    language_repos: Vec<LanguageRepo>,
    language_configuration_ids_by_file_type: HashMap<String, Vec<(usize, usize)>>,
}

unsafe impl Send for Loader {}
unsafe impl Sync for Loader {}

impl Loader {
    pub fn new(parser_lib_path: PathBuf) -> Self {
        Loader {
            parser_lib_path,
            language_repos: Vec::new(),
            language_configuration_ids_by_file_type: HashMap::new(),
        }
    }

    pub fn find_all_languages(&mut self, parser_src_paths: &Vec<PathBuf>) -> Result<()> {
        for parser_container_dir in parser_src_paths.iter() {
            if let Ok(entries) = fs::read_dir(parser_container_dir) {
                for entry in entries {
                    let entry = entry?;
                    if let Some(parser_dir_name) = entry.file_name().to_str() {
                        if parser_dir_name.starts_with("tree-sitter-") {
                            self.find_language_at_path(&parser_container_dir.join(parser_dir_name))
                                .ok();
                        }
                    }
                }
            }
        }
        Ok(())
    }

    pub fn language_at_path(&mut self, path: &Path) -> Result<Option<Language>> {
        if let Ok(id) = self.find_language_at_path(path) {
            Ok(Some(self.language_configuration_for_id(id)?.0))
        } else {
            Ok(None)
        }
    }

    pub fn language_configuration_for_file_name(
        &self,
        path: &Path,
    ) -> Result<Option<(Language, &LanguageConfiguration)>> {
        let ids = path
            .file_name()
            .and_then(|n| n.to_str())
            .and_then(|file_name| self.language_configuration_ids_by_file_type.get(file_name))
            .or_else(|| {
                path.extension()
                    .and_then(|extension| extension.to_str())
                    .and_then(|extension| {
                        self.language_configuration_ids_by_file_type.get(extension)
                    })
            });
        if let Some(ids) = ids {
            // TODO use `content-regex` to pick one
            for (repo_id, configuration_id) in ids.iter().cloned() {
                let (language, configurations) = self.language_configuration_for_id(repo_id)?;
                return Ok(Some((language, &configurations[configuration_id])));
            }
        }
        Ok(None)
    }

    pub fn language_configuration_for_injection_string(
        &self,
        string: &str,
    ) -> Result<Option<(Language, &LanguageConfiguration)>> {
        let mut best_match_length = 0;
        let mut best_match_position = None;
        for (i, repo) in self.language_repos.iter().enumerate() {
            for (j, configuration) in repo.configurations.iter().enumerate() {
                if let Some(injection_regex) = &configuration.injection_regex {
                    if let Some(mat) = injection_regex.find(string) {
                        let length = mat.end() - mat.start();
                        if length > best_match_length {
                            best_match_position = Some((i, j));
                            best_match_length = length;
                        }
                    }
                }
            }
        }
        if let Some((i, j)) = best_match_position {
            let (language, configurations) = self.language_configuration_for_id(i)?;
            Ok(Some((language, &configurations[j])))
        } else {
            Ok(None)
        }
    }

    fn language_configuration_for_id(
        &self,
        id: usize,
    ) -> Result<(Language, &Vec<LanguageConfiguration>)> {
        let repo = &self.language_repos[id];
        let language = repo.language.get_or_try_init(|| {
            let src_path = repo.path.join("src");
            self.load_language_at_path(&src_path, &src_path)
        })?;
        Ok((*language, &self.language_repos[id].configurations))
    }

    pub fn load_language_at_path(&self, src_path: &Path, header_path: &Path) -> Result<Language> {
        let grammar_path = src_path.join("grammar.json");
        let parser_path = src_path.join("parser.c");
        let mut scanner_path = src_path.join("scanner.c");

        #[derive(Deserialize)]
        struct GrammarJSON {
            name: String,
        }
        let mut grammar_file = fs::File::open(grammar_path)?;
        let grammar_json: GrammarJSON = serde_json::from_reader(BufReader::new(&mut grammar_file))?;

        let scanner_path = if scanner_path.exists() {
            Some(scanner_path)
        } else {
            scanner_path.set_extension("cc");
            if scanner_path.exists() {
                Some(scanner_path)
            } else {
                None
            }
        };

        self.load_language_from_sources(
            &grammar_json.name,
            &header_path,
            &parser_path,
            &scanner_path,
        )
    }

    pub fn load_language_from_sources(
        &self,
        name: &str,
        header_path: &Path,
        parser_path: &Path,
        scanner_path: &Option<PathBuf>,
    ) -> Result<Language> {
        let mut library_path = self.parser_lib_path.join(name);
        library_path.set_extension(DYLIB_EXTENSION);

        if needs_recompile(&library_path, &parser_path, &scanner_path)? {
            let mut config = cc::Build::new();
            config
                .cpp(true)
                .opt_level(2)
                .cargo_metadata(false)
                .target(BUILD_TARGET)
                .host(BUILD_TARGET);
            let compiler = config.get_compiler();
            let mut command = Command::new(compiler.path());
            for (key, value) in compiler.env() {
                command.env(key, value);
            }

            if cfg!(windows) {
                command
                    .args(&["/nologo", "/LD", "/I"])
                    .arg(header_path)
                    .arg("/Od")
                    .arg(parser_path);
                if let Some(scanner_path) = scanner_path.as_ref() {
                    command.arg(scanner_path);
                }
                command
                    .arg("/link")
                    .arg(format!("/out:{}", library_path.to_str().unwrap()));
            } else {
                command
                    .arg("-shared")
                    .arg("-fPIC")
                    .arg("-fno-exceptions")
                    .arg("-I")
                    .arg(header_path)
                    .arg("-o")
                    .arg(&library_path);
                if let Some(scanner_path) = scanner_path.as_ref() {
                    if scanner_path.extension() == Some("c".as_ref()) {
                        command.arg("-xc").arg("-std=c99").arg(scanner_path);
                    } else {
                        command.arg(scanner_path);
                    }
                }
                command.arg("-xc").arg(parser_path);
            }

            let output = command.output()?;
            if !output.status.success() {
                return Err(Error(format!(
                    "Parser compilation failed.\nStdout: {}\nStderr: {}",
                    String::from_utf8_lossy(&output.stdout),
                    String::from_utf8_lossy(&output.stderr)
                )));
            }
        }

        let library = Library::new(&library_path).map_err(|e| {
            Error(format!(
                "Error opening dynamic library {:?}: {}",
                &library_path, e
            ))
        })?;
        let language_fn_name = format!("tree_sitter_{}", replace_dashes_with_underscores(name));
        let language = unsafe {
            let language_fn: Symbol<unsafe extern "C" fn() -> Language> =
                library.get(language_fn_name.as_bytes())?;
            language_fn()
        };
        mem::forget(library);
        Ok(language)
    }

    fn find_language_at_path<'a>(&'a mut self, parser_path: &Path) -> Result<usize> {
        #[derive(Deserialize)]
        struct LanguageConfigurationJSON {
            name: String,
            #[serde(rename = "file-types")]
            file_types: Option<Vec<String>>,
            #[serde(rename = "content-regex")]
            content_regex: Option<String>,
            #[serde(rename = "first-line-regex")]
            first_line_regex: Option<String>,
            #[serde(rename = "injection-regex")]
            injection_regex: Option<String>,
            highlights: Option<String>,
        }

        #[derive(Deserialize)]
        struct PackageJSON {
            #[serde(rename = "tree-sitter")]
            tree_sitter: Option<Vec<LanguageConfigurationJSON>>,
        }

        let package_json_contents = fs::read_to_string(&parser_path.join("package.json"))?;
        let package_json: PackageJSON = serde_json::from_str(&package_json_contents)?;
        let configurations = package_json
            .tree_sitter
            .map_or(Vec::new(), |configurations| {
                configurations
                    .into_iter()
                    .map(|conf| LanguageConfiguration {
                        name: conf.name,
                        file_types: conf.file_types.unwrap_or(Vec::new()),
                        _content_regex: conf
                            .content_regex
                            .and_then(|r| RegexBuilder::new(&r).multi_line(true).build().ok()),
                        _first_line_regex: conf
                            .first_line_regex
                            .and_then(|r| RegexBuilder::new(&r).multi_line(true).build().ok()),
                        injection_regex: conf
                            .injection_regex
                            .and_then(|r| RegexBuilder::new(&r).multi_line(true).build().ok()),
                        highlight_property_sheet_path: conf.highlights.map(|h| parser_path.join(h)),
                        highlight_property_sheet: OnceCell::new(),
                    })
                    .collect()
            });

        for (i, configuration) in configurations.iter().enumerate() {
            for file_type in &configuration.file_types {
                self.language_configuration_ids_by_file_type
                    .entry(file_type.to_string())
                    .or_insert(Vec::new())
                    .push((self.language_repos.len(), i));
            }
        }

        self.language_repos.push(LanguageRepo {
            path: parser_path.to_owned(),
            language: OnceCell::new(),
            configurations,
        });

        Ok(self.language_repos.len() - 1)
    }
}

impl LanguageRegistry for Loader {
    fn language_for_injection_string<'a>(
        &'a self,
        string: &str,
    ) -> Option<(Language, &'a PropertySheet<Properties>)> {
        match self.language_configuration_for_injection_string(string) {
            Err(message) => {
                eprintln!(
                    "Failed to load language for injection string '{}': {}",
                    string, message.0
                );
                None
            }
            Ok(None) => None,
            Ok(Some((language, configuration))) => {
                match configuration.highlight_property_sheet(language) {
                    Err(message) => {
                        eprintln!(
                            "Failed to load property sheet for injection string '{}': {}",
                            string, message.0
                        );
                        None
                    }
                    Ok(None) => None,
                    Ok(Some(sheet)) => Some((language, sheet)),
                }
            }
        }
    }
}

impl LanguageConfiguration {
    pub fn highlight_property_sheet(
        &self,
        language: Language,
    ) -> Result<Option<&PropertySheet<Properties>>> {
        self.highlight_property_sheet
            .get_or_try_init(|| {
                if let Some(path) = &self.highlight_property_sheet_path {
                    let sheet_json = fs::read_to_string(path)?;
                    let sheet = load_property_sheet(language, &sheet_json)?;
                    Ok(Some(sheet))
                } else {
                    Ok(None)
                }
            })
            .map(Option::as_ref)
    }
}

fn needs_recompile(
    lib_path: &Path,
    parser_c_path: &Path,
    scanner_path: &Option<PathBuf>,
) -> Result<bool> {
    if !lib_path.exists() {
        return Ok(true);
    }
    let lib_mtime = mtime(lib_path)?;
    if mtime(parser_c_path)? > lib_mtime {
        return Ok(true);
    }
    if let Some(scanner_path) = scanner_path {
        if mtime(scanner_path)? > lib_mtime {
            return Ok(true);
        }
    }
    Ok(false)
}

fn mtime(path: &Path) -> Result<SystemTime> {
    Ok(fs::metadata(path)?.modified()?)
}

fn replace_dashes_with_underscores(name: &str) -> String {
    let mut result = String::with_capacity(name.len());
    for c in name.chars() {
        if c == '-' {
            result.push('_');
        } else {
            result.push(c);
        }
    }
    result
}
