use libloading::{Library, Symbol};
use regex::{Regex, RegexBuilder};
use std::collections::HashMap;
use std::fs;
use std::io;
use std::mem;
use std::path::{Path, PathBuf};
use std::process::Command;
use tree_sitter::{Language, PropertySheet};

const PACKAGE_JSON_PATH: &'static str = "package.json";
const PARSER_C_PATH: &'static str = "src/parser.c";
const SCANNER_C_PATH: &'static str = "src/scanner.c";
const SCANNER_CC_PATH: &'static str = "src/scanner.cc";

#[cfg(unix)]
const DYLIB_EXTENSION: &'static str = "so";

#[cfg(windows)]
const DYLIB_EXTENSION: &'static str = "dll";

struct LanguageRepo {
    name: String,
    path: PathBuf,
    language: Option<Language>,
    configurations: Vec<LanguageConfiguration>,
}

pub struct LanguageConfiguration {
    name: String,
    content_regex: Option<Regex>,
    first_line_regex: Option<Regex>,
    file_types: Vec<String>,
    highlight_property_sheet: Option<Result<PropertySheet, PathBuf>>,
}

pub struct Loader {
    parser_lib_path: PathBuf,
    language_repos: Vec<LanguageRepo>,
    language_configuration_indices_by_file_type: HashMap<String, Vec<(usize, usize)>>,
}

unsafe impl Send for Loader {}
unsafe impl Sync for Loader {}

impl Loader {
    pub fn new(parser_lib_path: PathBuf) -> Self {
        Loader {
            parser_lib_path,
            language_repos: Vec::new(),
            language_configuration_indices_by_file_type: HashMap::new(),
        }
    }

    pub fn find_parsers(&mut self, parser_src_paths: &Vec<PathBuf>) -> io::Result<()> {
        for parser_container_dir in parser_src_paths.iter() {
            for entry in fs::read_dir(parser_container_dir)? {
                let entry = entry?;
                if let Some(parser_dir_name) = entry.file_name().to_str() {
                    if parser_dir_name.starts_with("tree-sitter-") {
                        if self.load_language_configurations(
                            &parser_container_dir.join(parser_dir_name),
                        ).is_err() {
                            eprintln!("Error loading {}", parser_dir_name);
                        }
                    }
                }
            }
        }
        Ok(())
    }

    pub fn language_configuration_at_path(
        &mut self,
        path: &Path,
    ) -> io::Result<Option<(Language, &LanguageConfiguration)>> {
        let repo_index = self.load_language_configurations(path)?;
        self.load_language_from_repo(repo_index, 0)
    }

    pub fn language_for_file_name(
        &mut self,
        path: &Path,
    ) -> io::Result<Option<(Language, &LanguageConfiguration)>> {
        let indices = path
            .file_name()
            .and_then(|n| n.to_str())
            .and_then(|file_name| {
                self.language_configuration_indices_by_file_type
                    .get(file_name)
            })
            .or_else(|| {
                path.extension()
                    .and_then(|extension| extension.to_str())
                    .and_then(|extension| {
                        self.language_configuration_indices_by_file_type
                            .get(extension)
                    })
            });

        if let Some(indices) = indices {
            // TODO use `content-regex` to pick one
            for (repo_index, conf_index) in indices {
                return self.load_language_from_repo(*repo_index, *conf_index);
            }
        }
        Ok(None)
    }

    fn load_language_from_repo(
        &mut self,
        repo_index: usize,
        conf_index: usize,
    ) -> io::Result<Option<(Language, &LanguageConfiguration)>> {
        let repo = &self.language_repos[repo_index];
        let language = if let Some(language) = repo.language {
            language
        } else {
            let language = self.load_language_at_path(&repo.name, &repo.path)?;
            self.language_repos[repo_index].language = Some(language);
            language
        };
        if let Some(configuration) = self.language_repos[repo_index]
            .configurations
            .get(conf_index)
        {
            Ok(Some((language, configuration)))
        } else {
            Ok(None)
        }
    }

    fn load_language_at_path(&self, name: &str, language_path: &Path) -> io::Result<Language> {
        let parser_c_path = language_path.join(PARSER_C_PATH);
        let mut library_path = self.parser_lib_path.join(name);
        library_path.set_extension(DYLIB_EXTENSION);

        if !library_path.exists() || was_modified_more_recently(&parser_c_path, &library_path)? {
            let compiler_name = std::env::var("CXX").unwrap_or("c++".to_owned());
            let mut command = Command::new(compiler_name);
            command
                .arg("-shared")
                .arg("-fPIC")
                .arg("-I")
                .arg(language_path.join("src"))
                .arg("-o")
                .arg(&library_path)
                .arg("-xc")
                .arg(parser_c_path);
            let scanner_c_path = language_path.join(SCANNER_C_PATH);
            let scanner_cc_path = language_path.join(SCANNER_CC_PATH);
            if scanner_c_path.exists() {
                command.arg("-xc").arg(scanner_c_path);
            } else if scanner_cc_path.exists() {
                command.arg("-xc++").arg(scanner_cc_path);
            }
            command.output()?;
        }

        let library = Library::new(library_path)?;
        let language_fn_name = format!("tree_sitter_{}", name);
        let language = unsafe {
            let language_fn: Symbol<unsafe extern "C" fn() -> Language> =
                library.get(language_fn_name.as_bytes())?;
            language_fn()
        };
        mem::forget(library);
        Ok(language)
    }

    fn load_language_configurations<'a>(&'a mut self, parser_path: &Path) -> io::Result<usize> {
        let name = parser_path
            .file_name()
            .unwrap()
            .to_str()
            .unwrap()
            .split_at("tree-sitter-".len())
            .1;

        #[derive(Deserialize)]
        struct LanguageConfigurationJSON {
            name: String,
            #[serde(rename = "file-types")]
            file_types: Option<Vec<String>>,
            #[serde(rename = "content-regex")]
            content_regex: Option<String>,
            #[serde(rename = "first-line-regex")]
            first_line_regex: Option<String>,
            highlights: Option<String>,
        }

        #[derive(Deserialize)]
        struct PackageJSON {
            #[serde(rename = "tree-sitter")]
            tree_sitter: Option<Vec<LanguageConfigurationJSON>>,
        }

        let package_json_contents = fs::read_to_string(&parser_path.join(PACKAGE_JSON_PATH))?;
        let package_json: PackageJSON = serde_json::from_str(&package_json_contents)?;
        let configurations = package_json
            .tree_sitter
            .map_or(Vec::new(), |configurations| {
                configurations
                    .into_iter()
                    .map(|conf| LanguageConfiguration {
                        name: conf.name,
                        file_types: conf.file_types.unwrap_or(Vec::new()),
                        content_regex: conf
                            .content_regex
                            .and_then(|r| RegexBuilder::new(&r).multi_line(true).build().ok()),
                        first_line_regex: conf
                            .first_line_regex
                            .and_then(|r| RegexBuilder::new(&r).multi_line(true).build().ok()),
                        highlight_property_sheet: conf.highlights.map(|d| Err(d.into())),
                    })
                    .collect()
            });

        for (i, configuration) in configurations.iter().enumerate() {
            for file_type in &configuration.file_types {
                self.language_configuration_indices_by_file_type
                    .entry(file_type.to_string())
                    .or_insert(Vec::new())
                    .push((self.language_repos.len(), i));
            }
        }

        self.language_repos.push(LanguageRepo {
            name: name.to_string(),
            path: parser_path.to_owned(),
            language: None,
            configurations,
        });

        Ok(self.language_repos.len() - 1)
    }
}

fn was_modified_more_recently(a: &Path, b: &Path) -> io::Result<bool> {
    Ok(fs::metadata(a)?.modified()? > fs::metadata(b)?.modified()?)
}
