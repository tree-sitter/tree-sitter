use libloading::{Library, Symbol};
use regex::{Regex, RegexBuilder};
use std::collections::HashMap;
use std::fs;
use std::io;
use std::mem;
use std::path::{Path, PathBuf};
use std::process::Command;
use std::time::SystemTime;
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

    pub fn find_all_languages(&mut self, parser_src_paths: &Vec<PathBuf>) -> io::Result<()> {
        for parser_container_dir in parser_src_paths.iter() {
            for entry in fs::read_dir(parser_container_dir)? {
                let entry = entry?;
                if let Some(parser_dir_name) = entry.file_name().to_str() {
                    if parser_dir_name.starts_with("tree-sitter-") {
                        if self
                            .find_language_at_path(&parser_container_dir.join(parser_dir_name))
                            .is_err()
                        {
                            eprintln!("Error loading {}", parser_dir_name);
                        }
                    }
                }
            }
        }
        Ok(())
    }

    pub fn language_at_path(&mut self, path: &Path) -> io::Result<Option<Language>> {
        if let Ok(id) = self.find_language_at_path(path) {
            Ok(Some(self.language_configuration_for_id(id)?.0))
        } else {
            Ok(None)
        }
    }

    pub fn language_configuration_for_file_name(
        &mut self,
        path: &Path,
    ) -> io::Result<Option<(Language, &LanguageConfiguration)>> {
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

    fn language_configuration_for_id(
        &mut self,
        id: usize,
    ) -> io::Result<(Language, &Vec<LanguageConfiguration>)> {
        let repo = &self.language_repos[id];
        let language = if let Some(language) = repo.language {
            language
        } else {
            let language = self.load_language_at_path(&repo.name, &repo.path)?;
            self.language_repos[id].language = Some(language);
            language
        };
        Ok((language, &self.language_repos[id].configurations))
    }

    fn load_language_at_path(&self, name: &str, language_path: &Path) -> io::Result<Language> {
        let src_path = language_path.join("src");
        let parser_c_path = src_path.join("parser.c");

        let scanner_path;
        let scanner_c_path = src_path.join("scanner.c");
        if scanner_c_path.exists() {
            scanner_path = Some(scanner_c_path);
        } else {
            let scanner_cc_path = src_path.join("scanner.cc");
            if scanner_cc_path.exists() {
                scanner_path = Some(scanner_cc_path);
            } else {
                scanner_path = None;
            }
        }

        self.load_language_from_sources(name, &src_path, &parser_c_path, &scanner_path)
    }

    pub fn load_language_from_sources(
        &self,
        name: &str,
        header_path: &Path,
        parser_path: &Path,
        scanner_path: &Option<PathBuf>,
    ) -> io::Result<Language> {
        let mut library_path = self.parser_lib_path.join(name);
        library_path.set_extension(DYLIB_EXTENSION);

        if needs_recompile(&library_path, &parser_path, &scanner_path)? {
            let mut config = cc::Build::new();
            config
                .opt_level(2)
                .cargo_metadata(false)
                .target(env!("BUILD_TARGET"))
                .host(env!("BUILD_TARGET"));
            let compiler = config.get_compiler();
            let compiler_path = compiler.path();
            let mut command = Command::new(compiler_path);

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
                    .arg("-I")
                    .arg(header_path)
                    .arg("-o")
                    .arg(&library_path)
                    .arg("-xc")
                    .arg(parser_path);
                if let Some(scanner_path) = scanner_path.as_ref() {
                    if scanner_path.extension() == Some("c".as_ref()) {
                        command.arg(scanner_path);
                    } else {
                        command.arg("-xc++").arg(scanner_path);
                    }
                }
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

    fn find_language_at_path<'a>(&'a mut self, parser_path: &Path) -> io::Result<usize> {
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
                self.language_configuration_ids_by_file_type
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

fn needs_recompile(
    lib_path: &Path,
    parser_c_path: &Path,
    scanner_path: &Option<PathBuf>,
) -> io::Result<bool> {
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

fn mtime(path: &Path) -> io::Result<SystemTime> {
    Ok(fs::metadata(path)?.modified()?)
}
