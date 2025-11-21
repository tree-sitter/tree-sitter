use std::{
    fs,
    path::{Path, PathBuf},
    str::{self, FromStr},
};

use anyhow::{anyhow, Context, Result};
use crc32fast::hash as crc32;
use heck::{ToKebabCase, ToShoutySnakeCase, ToSnakeCase, ToUpperCamelCase};
use indoc::{formatdoc, indoc};
use log::warn;
use rand::{thread_rng, Rng};
use semver::Version;
use serde::{Deserialize, Serialize};
use serde_json::{Map, Value};
use tree_sitter_generate::write_file;
use tree_sitter_loader::{
    Author, Bindings, Grammar, Links, Metadata, PathsJSON, TreeSitterJSON,
    DEFAULT_HIGHLIGHTS_QUERY_FILE_NAME, DEFAULT_INJECTIONS_QUERY_FILE_NAME,
    DEFAULT_LOCALS_QUERY_FILE_NAME, DEFAULT_TAGS_QUERY_FILE_NAME,
};

const CLI_VERSION: &str = env!("CARGO_PKG_VERSION");
const CLI_VERSION_PLACEHOLDER: &str = "CLI_VERSION";

const ABI_VERSION_MAX: usize = tree_sitter::LANGUAGE_VERSION;
const ABI_VERSION_MAX_PLACEHOLDER: &str = "ABI_VERSION_MAX";

const PARSER_NAME_PLACEHOLDER: &str = "PARSER_NAME";
const CAMEL_PARSER_NAME_PLACEHOLDER: &str = "CAMEL_PARSER_NAME";
const TITLE_PARSER_NAME_PLACEHOLDER: &str = "TITLE_PARSER_NAME";
const UPPER_PARSER_NAME_PLACEHOLDER: &str = "UPPER_PARSER_NAME";
const LOWER_PARSER_NAME_PLACEHOLDER: &str = "LOWER_PARSER_NAME";
const KEBAB_PARSER_NAME_PLACEHOLDER: &str = "KEBAB_PARSER_NAME";
const PARSER_CLASS_NAME_PLACEHOLDER: &str = "PARSER_CLASS_NAME";

const PARSER_DESCRIPTION_PLACEHOLDER: &str = "PARSER_DESCRIPTION";
const PARSER_LICENSE_PLACEHOLDER: &str = "PARSER_LICENSE";
const PARSER_URL_PLACEHOLDER: &str = "PARSER_URL";
const PARSER_URL_STRIPPED_PLACEHOLDER: &str = "PARSER_URL_STRIPPED";
const PARSER_VERSION_PLACEHOLDER: &str = "PARSER_VERSION";
const PARSER_FINGERPRINT_PLACEHOLDER: &str = "PARSER_FINGERPRINT";

const AUTHOR_NAME_PLACEHOLDER: &str = "PARSER_AUTHOR_NAME";
const AUTHOR_EMAIL_PLACEHOLDER: &str = "PARSER_AUTHOR_EMAIL";
const AUTHOR_URL_PLACEHOLDER: &str = "PARSER_AUTHOR_URL";

const AUTHOR_BLOCK_JS: &str = "\n  \"author\": {";
const AUTHOR_NAME_PLACEHOLDER_JS: &str = "\n    \"name\": \"PARSER_AUTHOR_NAME\",";
const AUTHOR_EMAIL_PLACEHOLDER_JS: &str = ",\n    \"email\": \"PARSER_AUTHOR_EMAIL\"";
const AUTHOR_URL_PLACEHOLDER_JS: &str = ",\n    \"url\": \"PARSER_AUTHOR_URL\"";

const AUTHOR_BLOCK_PY: &str = "\nauthors = [{";
const AUTHOR_NAME_PLACEHOLDER_PY: &str = "name = \"PARSER_AUTHOR_NAME\"";
const AUTHOR_EMAIL_PLACEHOLDER_PY: &str = ", email = \"PARSER_AUTHOR_EMAIL\"";

const AUTHOR_BLOCK_RS: &str = "\nauthors = [";
const AUTHOR_NAME_PLACEHOLDER_RS: &str = "PARSER_AUTHOR_NAME";
const AUTHOR_EMAIL_PLACEHOLDER_RS: &str = " PARSER_AUTHOR_EMAIL";

const AUTHOR_BLOCK_GRAMMAR: &str = "\n * @author ";
const AUTHOR_NAME_PLACEHOLDER_GRAMMAR: &str = "PARSER_AUTHOR_NAME";
const AUTHOR_EMAIL_PLACEHOLDER_GRAMMAR: &str = " PARSER_AUTHOR_EMAIL";

const FUNDING_URL_PLACEHOLDER: &str = "FUNDING_URL";

const HIGHLIGHTS_QUERY_PATH_PLACEHOLDER: &str = "HIGHLIGHTS_QUERY_PATH";
const INJECTIONS_QUERY_PATH_PLACEHOLDER: &str = "INJECTIONS_QUERY_PATH";
const LOCALS_QUERY_PATH_PLACEHOLDER: &str = "LOCALS_QUERY_PATH";
const TAGS_QUERY_PATH_PLACEHOLDER: &str = "TAGS_QUERY_PATH";

const GRAMMAR_JS_TEMPLATE: &str = include_str!("./templates/grammar.js");
const PACKAGE_JSON_TEMPLATE: &str = include_str!("./templates/package.json");
const GITIGNORE_TEMPLATE: &str = include_str!("./templates/gitignore");
const GITATTRIBUTES_TEMPLATE: &str = include_str!("./templates/gitattributes");
const EDITORCONFIG_TEMPLATE: &str = include_str!("./templates/.editorconfig");

const RUST_BINDING_VERSION: &str = env!("CARGO_PKG_VERSION");
const RUST_BINDING_VERSION_PLACEHOLDER: &str = "RUST_BINDING_VERSION";

const LIB_RS_TEMPLATE: &str = include_str!("./templates/lib.rs");
const BUILD_RS_TEMPLATE: &str = include_str!("./templates/build.rs");
const CARGO_TOML_TEMPLATE: &str = include_str!("./templates/_cargo.toml");

const INDEX_JS_TEMPLATE: &str = include_str!("./templates/index.js");
const INDEX_D_TS_TEMPLATE: &str = include_str!("./templates/index.d.ts");
const JS_BINDING_CC_TEMPLATE: &str = include_str!("./templates/js-binding.cc");
const BINDING_GYP_TEMPLATE: &str = include_str!("./templates/binding.gyp");
const BINDING_TEST_JS_TEMPLATE: &str = include_str!("./templates/binding_test.js");

const MAKEFILE_TEMPLATE: &str = include_str!("./templates/makefile");
const CMAKELISTS_TXT_TEMPLATE: &str = include_str!("./templates/cmakelists.cmake");
const PARSER_NAME_H_TEMPLATE: &str = include_str!("./templates/PARSER_NAME.h");
const PARSER_NAME_PC_IN_TEMPLATE: &str = include_str!("./templates/PARSER_NAME.pc.in");

const GO_MOD_TEMPLATE: &str = include_str!("./templates/go.mod");
const BINDING_GO_TEMPLATE: &str = include_str!("./templates/binding.go");
const BINDING_TEST_GO_TEMPLATE: &str = include_str!("./templates/binding_test.go");

const SETUP_PY_TEMPLATE: &str = include_str!("./templates/setup.py");
const INIT_PY_TEMPLATE: &str = include_str!("./templates/__init__.py");
const INIT_PYI_TEMPLATE: &str = include_str!("./templates/__init__.pyi");
const PYPROJECT_TOML_TEMPLATE: &str = include_str!("./templates/pyproject.toml");
const PY_BINDING_C_TEMPLATE: &str = include_str!("./templates/py-binding.c");
const TEST_BINDING_PY_TEMPLATE: &str = include_str!("./templates/test_binding.py");

const PACKAGE_SWIFT_TEMPLATE: &str = include_str!("./templates/package.swift");
const TESTS_SWIFT_TEMPLATE: &str = include_str!("./templates/tests.swift");

const BUILD_ZIG_TEMPLATE: &str = include_str!("./templates/build.zig");
const BUILD_ZIG_ZON_TEMPLATE: &str = include_str!("./templates/build.zig.zon");
const ROOT_ZIG_TEMPLATE: &str = include_str!("./templates/root.zig");
const TEST_ZIG_TEMPLATE: &str = include_str!("./templates/test.zig");

const TREE_SITTER_JSON_SCHEMA: &str =
    "https://tree-sitter.github.io/tree-sitter/assets/schemas/config.schema.json";

#[derive(Serialize, Deserialize, Clone)]
pub struct JsonConfigOpts {
    pub name: String,
    pub camelcase: String,
    pub title: String,
    pub description: String,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub repository: Option<String>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub funding: Option<String>,
    pub scope: String,
    pub file_types: Vec<String>,
    pub version: Version,
    pub license: String,
    pub author: String,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub email: Option<String>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub url: Option<String>,
    pub bindings: Bindings,
}

impl JsonConfigOpts {
    #[must_use]
    pub fn to_tree_sitter_json(self) -> TreeSitterJSON {
        TreeSitterJSON {
            schema: Some(TREE_SITTER_JSON_SCHEMA.to_string()),
            grammars: vec![Grammar {
                name: self.name.clone(),
                camelcase: Some(self.camelcase),
                title: Some(self.title),
                scope: self.scope,
                path: None,
                external_files: PathsJSON::Empty,
                file_types: Some(self.file_types),
                highlights: PathsJSON::Empty,
                injections: PathsJSON::Empty,
                locals: PathsJSON::Empty,
                tags: PathsJSON::Empty,
                injection_regex: Some(format!("^{}$", self.name)),
                first_line_regex: None,
                content_regex: None,
                class_name: Some(format!("TreeSitter{}", self.name.to_upper_camel_case())),
            }],
            metadata: Metadata {
                version: self.version,
                license: Some(self.license),
                description: Some(self.description),
                authors: Some(vec![Author {
                    name: self.author,
                    email: self.email,
                    url: self.url,
                }]),
                links: Some(Links {
                    repository: self.repository.unwrap_or_else(|| {
                        format!("https://github.com/tree-sitter/tree-sitter-{}", self.name)
                    }),
                    funding: self.funding,
                }),
                namespace: None,
            },
            bindings: self.bindings,
        }
    }
}

impl Default for JsonConfigOpts {
    fn default() -> Self {
        Self {
            name: String::new(),
            camelcase: String::new(),
            title: String::new(),
            description: String::new(),
            repository: None,
            funding: None,
            scope: String::new(),
            file_types: vec![],
            version: Version::from_str("0.1.0").unwrap(),
            license: String::new(),
            author: String::new(),
            email: None,
            url: None,
            bindings: Bindings::default(),
        }
    }
}

struct GenerateOpts<'a> {
    author_name: Option<&'a str>,
    author_email: Option<&'a str>,
    author_url: Option<&'a str>,
    license: Option<&'a str>,
    description: Option<&'a str>,
    repository: Option<&'a str>,
    funding: Option<&'a str>,
    version: &'a Version,
    camel_parser_name: &'a str,
    title_parser_name: &'a str,
    class_name: &'a str,
    highlights_query_path: &'a str,
    injections_query_path: &'a str,
    locals_query_path: &'a str,
    tags_query_path: &'a str,
}

pub fn generate_grammar_files(
    repo_path: &Path,
    language_name: &str,
    allow_update: bool,
    opts: Option<&JsonConfigOpts>,
) -> Result<()> {
    let dashed_language_name = language_name.to_kebab_case();

    let tree_sitter_config = missing_path_else(
        repo_path.join("tree-sitter.json"),
        true,
        |path| {
            // invariant: opts is always Some when `tree-sitter.json` doesn't exist
            let Some(opts) = opts else { unreachable!() };

            let tree_sitter_json = opts.clone().to_tree_sitter_json();
            write_file(path, serde_json::to_string_pretty(&tree_sitter_json)?)?;
            Ok(())
        },
        |path| {
            // updating the config, if needed
            if let Some(opts) = opts {
                let tree_sitter_json = opts.clone().to_tree_sitter_json();
                write_file(path, serde_json::to_string_pretty(&tree_sitter_json)?)?;
            }
            Ok(())
        },
    )?;

    let tree_sitter_config = serde_json::from_str::<TreeSitterJSON>(
        &fs::read_to_string(tree_sitter_config.as_path())
            .with_context(|| "Failed to read tree-sitter.json")?,
    )?;

    let authors = tree_sitter_config.metadata.authors.as_ref();
    let camel_name = tree_sitter_config.grammars[0]
        .camelcase
        .clone()
        .unwrap_or_else(|| language_name.to_upper_camel_case());
    let title_name = tree_sitter_config.grammars[0]
        .title
        .clone()
        .unwrap_or_else(|| language_name.to_upper_camel_case());
    let class_name = tree_sitter_config.grammars[0]
        .class_name
        .clone()
        .unwrap_or_else(|| format!("TreeSitter{}", language_name.to_upper_camel_case()));

    let default_highlights_path = Path::new("queries").join(DEFAULT_HIGHLIGHTS_QUERY_FILE_NAME);
    let default_injections_path = Path::new("queries").join(DEFAULT_INJECTIONS_QUERY_FILE_NAME);
    let default_locals_path = Path::new("queries").join(DEFAULT_LOCALS_QUERY_FILE_NAME);
    let default_tags_path = Path::new("queries").join(DEFAULT_TAGS_QUERY_FILE_NAME);

    let generate_opts = GenerateOpts {
        author_name: authors
            .map(|a| a.first().map(|a| a.name.as_str()))
            .unwrap_or_default(),
        author_email: authors
            .map(|a| a.first().and_then(|a| a.email.as_deref()))
            .unwrap_or_default(),
        author_url: authors
            .map(|a| a.first().and_then(|a| a.url.as_deref()))
            .unwrap_or_default(),
        license: tree_sitter_config.metadata.license.as_deref(),
        description: tree_sitter_config.metadata.description.as_deref(),
        repository: tree_sitter_config
            .metadata
            .links
            .as_ref()
            .map(|l| l.repository.as_str()),
        funding: tree_sitter_config
            .metadata
            .links
            .as_ref()
            .and_then(|l| l.funding.as_deref()),
        version: &tree_sitter_config.metadata.version,
        camel_parser_name: &camel_name,
        title_parser_name: &title_name,
        class_name: &class_name,
        highlights_query_path: tree_sitter_config.grammars[0]
            .highlights
            .to_variable_value(&default_highlights_path),
        injections_query_path: tree_sitter_config.grammars[0]
            .injections
            .to_variable_value(&default_injections_path),
        locals_query_path: tree_sitter_config.grammars[0]
            .locals
            .to_variable_value(&default_locals_path),
        tags_query_path: tree_sitter_config.grammars[0]
            .tags
            .to_variable_value(&default_tags_path),
    };

    // Create package.json
    missing_path_else(
        repo_path.join("package.json"),
        allow_update,
        |path| {
            generate_file(
                path,
                PACKAGE_JSON_TEMPLATE,
                dashed_language_name.as_str(),
                &generate_opts,
            )
        },
        |path| {
            let mut contents = fs::read_to_string(path)?
                .replace(
                    r#""node-addon-api": "^8.3.1""#,
                    r#""node-addon-api": "^8.5.0""#,
                )
                .replace(
                    indoc! {r#"
                    "prebuildify": "^6.0.1",
                    "tree-sitter-cli":"#},
                    indoc! {r#"
                    "prebuildify": "^6.0.1",
                    "tree-sitter": "^0.25.0",
                    "tree-sitter-cli":"#},
                );
            if !contents.contains("module") {
                warn!("Updating package.json");
                contents = contents.replace(
                    r#""repository":"#,
                    indoc! {r#"
                    "type": "module",
                      "repository":"#},
                );
            }
            write_file(path, contents)?;
            Ok(())
        },
    )?;

    // Do not create a grammar.js file in a repo with multiple language configs
    if !tree_sitter_config.has_multiple_language_configs() {
        missing_path_else(
            repo_path.join("grammar.js"),
            allow_update,
            |path| generate_file(path, GRAMMAR_JS_TEMPLATE, language_name, &generate_opts),
            |path| {
                let mut contents = fs::read_to_string(path)?;
                if contents.contains("module.exports") {
                    contents = contents.replace("module.exports =", "export default");
                    write_file(path, contents)?;
                }

                Ok(())
            },
        )?;
    }

    // Write .gitignore file
    missing_path_else(
        repo_path.join(".gitignore"),
        allow_update,
        |path| generate_file(path, GITIGNORE_TEMPLATE, language_name, &generate_opts),
        |path| {
            let contents = fs::read_to_string(path)?;
            if !contents.contains("Zig artifacts") {
                warn!("Replacing .gitignore");
                generate_file(path, GITIGNORE_TEMPLATE, language_name, &generate_opts)?;
            }
            Ok(())
        },
    )?;

    // Write .gitattributes file
    missing_path_else(
        repo_path.join(".gitattributes"),
        allow_update,
        |path| generate_file(path, GITATTRIBUTES_TEMPLATE, language_name, &generate_opts),
        |path| {
            let mut contents = fs::read_to_string(path)?;
            contents = contents.replace("bindings/c/* ", "bindings/c/** ");
            if !contents.contains("Zig bindings") {
                contents.push('\n');
                contents.push_str(indoc! {"
                # Zig bindings
                build.zig linguist-generated
                build.zig.zon linguist-generated
                "});
            }
            write_file(path, contents)?;
            Ok(())
        },
    )?;

    // Write .editorconfig file
    missing_path(repo_path.join(".editorconfig"), |path| {
        generate_file(path, EDITORCONFIG_TEMPLATE, language_name, &generate_opts)
    })?;

    let bindings_dir = repo_path.join("bindings");

    // Generate Rust bindings
    if tree_sitter_config.bindings.rust {
        missing_path(bindings_dir.join("rust"), create_dir)?.apply(|path| {
            missing_path_else(path.join("lib.rs"), allow_update, |path| {
                generate_file(path, LIB_RS_TEMPLATE, language_name, &generate_opts)
            }, |path| {
                let mut contents = fs::read_to_string(path)?;
                if !contents.contains("#[cfg(with_highlights_query)]") {
                let replacement = indoc! {r#"
                    #[cfg(with_highlights_query)]
                    /// The syntax highlighting query for this grammar.
                    pub const HIGHLIGHTS_QUERY: &str = include_str!("../../HIGHLIGHTS_QUERY_PATH");

                    #[cfg(with_injections_query)]
                    /// The language injection query for this grammar.
                    pub const INJECTIONS_QUERY: &str = include_str!("../../INJECTIONS_QUERY_PATH");

                    #[cfg(with_locals_query)]
                    /// The local variable query for this grammar.
                    pub const LOCALS_QUERY: &str = include_str!("../../LOCALS_QUERY_PATH");

                    #[cfg(with_tags_query)]
                    /// The symbol tagging query for this grammar.
                    pub const TAGS_QUERY: &str = include_str!("../../TAGS_QUERY_PATH");
                    "#}
                    .replace("HIGHLIGHTS_QUERY_PATH", generate_opts.highlights_query_path)
                    .replace("INJECTIONS_QUERY_PATH", generate_opts.injections_query_path)
                    .replace("LOCALS_QUERY_PATH", generate_opts.locals_query_path)
                    .replace("TAGS_QUERY_PATH", generate_opts.tags_query_path);
                contents = contents
                    .replace(
                        indoc! {r#"
                        // NOTE: uncomment these to include any queries that this grammar contains:

                        // pub const HIGHLIGHTS_QUERY: &str = include_str!("../../queries/highlights.scm");
                        // pub const INJECTIONS_QUERY: &str = include_str!("../../queries/injections.scm");
                        // pub const LOCALS_QUERY: &str = include_str!("../../queries/locals.scm");
                        // pub const TAGS_QUERY: &str = include_str!("../../queries/tags.scm");
                        "#},
                        &replacement,
                    );
                }
                write_file(path, contents)?;
                Ok(())
            })?;

            missing_path_else(
                path.join("build.rs"),
                allow_update,
                |path| generate_file(path, BUILD_RS_TEMPLATE, language_name, &generate_opts),
                |path| {
                    let mut contents = fs::read_to_string(path)?;
                    if !contents.contains("wasm32-unknown-unknown") {
                        let replacement = indoc!{r#"
                            c_config.flag("-utf-8");

                            if std::env::var("TARGET").unwrap() == "wasm32-unknown-unknown" {
                                let Ok(wasm_headers) = std::env::var("DEP_TREE_SITTER_LANGUAGE_WASM_HEADERS") else {
                                    panic!("Environment variable DEP_TREE_SITTER_LANGUAGE_WASM_HEADERS must be set by the language crate");
                                };
                                let Ok(wasm_src) =
                                    std::env::var("DEP_TREE_SITTER_LANGUAGE_WASM_SRC").map(std::path::PathBuf::from)
                                else {
                                    panic!("Environment variable DEP_TREE_SITTER_LANGUAGE_WASM_SRC must be set by the language crate");
                                };

                                c_config.include(&wasm_headers);
                                c_config.files([
                                    wasm_src.join("stdio.c"),
                                    wasm_src.join("stdlib.c"),
                                    wasm_src.join("string.c"),
                                ]);
                            }
                        "#};

                        let indented_replacement = replacement
                            .lines()
                            .map(|line| if line.is_empty() { line.to_string() } else { format!("    {line}") })
                            .collect::<Vec<_>>()
                            .join("\n");

                        contents = contents.replace(r#"    c_config.flag("-utf-8");"#, &indented_replacement);
                    }

                    // Introduce configuration variables for dynamic query inclusion
                    if !contents.contains("with_highlights_query") {
                        let replaced = indoc! {r#"
                                c_config.compile("tree-sitter-KEBAB_PARSER_NAME");
                            }"#}
                            .replace("KEBAB_PARSER_NAME", &language_name.to_kebab_case());

                        let replacement = indoc! {r#"
                                c_config.compile("tree-sitter-KEBAB_PARSER_NAME");

                                println!("cargo:rustc-check-cfg=cfg(with_highlights_query)");
                                if !"HIGHLIGHTS_QUERY_PATH".is_empty() && std::path::Path::new("HIGHLIGHTS_QUERY_PATH").exists() {
                                    println!("cargo:rustc-cfg=with_highlights_query");
                                }
                                println!("cargo:rustc-check-cfg=cfg(with_injections_query)");
                                if !"INJECTIONS_QUERY_PATH".is_empty() && std::path::Path::new("INJECTIONS_QUERY_PATH").exists() {
                                    println!("cargo:rustc-cfg=with_injections_query");
                                }
                                println!("cargo:rustc-check-cfg=cfg(with_locals_query)");
                                if !"LOCALS_QUERY_PATH".is_empty() && std::path::Path::new("LOCALS_QUERY_PATH").exists() {
                                    println!("cargo:rustc-cfg=with_locals_query");
                                }
                                println!("cargo:rustc-check-cfg=cfg(with_tags_query)");
                                if !"TAGS_QUERY_PATH".is_empty() && std::path::Path::new("TAGS_QUERY_PATH").exists() {
                                    println!("cargo:rustc-cfg=with_tags_query");
                                }
                            }"#}
                            .replace("KEBAB_PARSER_NAME", &language_name.to_kebab_case())
                            .replace("HIGHLIGHTS_QUERY_PATH", generate_opts.highlights_query_path)
                            .replace("INJECTIONS_QUERY_PATH", generate_opts.injections_query_path)
                            .replace("LOCALS_QUERY_PATH", generate_opts.locals_query_path)
                            .replace("TAGS_QUERY_PATH", generate_opts.tags_query_path);

                        contents = contents.replace(
                            &replaced,
                            &replacement,
                        );
                    }

                    write_file(path, contents)?;
                    Ok(())
                },
            )?;

            missing_path_else(
                repo_path.join("Cargo.toml"),
                allow_update,
                |path| {
                    generate_file(
                        path,
                        CARGO_TOML_TEMPLATE,
                        dashed_language_name.as_str(),
                        &generate_opts,
                    )
                },
                |path| {
                    let contents = fs::read_to_string(path)?;
                    if contents.contains("\"LICENSE\"") {
                        write_file(path, contents.replace("\"LICENSE\"", "\"/LICENSE\""))?;
                    }
                    Ok(())
                },
            )?;

            Ok(())
        })?;
    }

    // Generate Node bindings
    if tree_sitter_config.bindings.node {
        missing_path(bindings_dir.join("node"), create_dir)?.apply(|path| {
            missing_path_else(
                path.join("index.js"),
                allow_update,
                |path| generate_file(path, INDEX_JS_TEMPLATE, language_name, &generate_opts),
                |path| {
                    let contents = fs::read_to_string(path)?;
                    if !contents.contains("Object.defineProperty") {
                        warn!("Replacing index.js");
                        generate_file(path, INDEX_JS_TEMPLATE, language_name, &generate_opts)?;
                    }
                    Ok(())
                },
            )?;

            missing_path_else(
                path.join("index.d.ts"),
                allow_update,
                |path| generate_file(path, INDEX_D_TS_TEMPLATE, language_name, &generate_opts),
                |path| {
                    let contents = fs::read_to_string(path)?;
                    if !contents.contains("export default binding") {
                        warn!("Replacing index.d.ts");
                        generate_file(path, INDEX_D_TS_TEMPLATE, language_name, &generate_opts)?;
                    }
                    Ok(())
                },
            )?;

            missing_path_else(
                path.join("binding_test.js"),
                allow_update,
                |path| {
                    generate_file(
                        path,
                        BINDING_TEST_JS_TEMPLATE,
                        language_name,
                        &generate_opts,
                    )
                },
                |path| {
                    let contents = fs::read_to_string(path)?;
                    if !contents.contains("import") {
                        warn!("Replacing binding_test.js");
                        generate_file(
                            path,
                            BINDING_TEST_JS_TEMPLATE,
                            language_name,
                            &generate_opts,
                        )?;
                    }
                    Ok(())
                },
            )?;

            missing_path(path.join("binding.cc"), |path| {
                generate_file(path, JS_BINDING_CC_TEMPLATE, language_name, &generate_opts)
            })?;

            missing_path_else(
                repo_path.join("binding.gyp"),
                allow_update,
                |path| generate_file(path, BINDING_GYP_TEMPLATE, language_name, &generate_opts),
                |path| {
                    let contents = fs::read_to_string(path)?;
                    if contents.contains("fs.exists(") {
                        write_file(path, contents.replace("fs.exists(", "fs.existsSync("))?;
                    }
                    Ok(())
                },
            )?;

            Ok(())
        })?;
    }

    // Generate C bindings
    if tree_sitter_config.bindings.c {
        missing_path(bindings_dir.join("c"), create_dir)?.apply(|path| {
            let old_file = &path.join(format!("tree-sitter-{}.h", language_name.to_kebab_case()));
            if allow_update && fs::exists(old_file).unwrap_or(false) {
                fs::remove_file(old_file)?;
            }
            missing_path(path.join("tree_sitter"), create_dir)?.apply(|include_path| {
                missing_path(
                    include_path.join(format!("tree-sitter-{}.h", language_name.to_kebab_case())),
                    |path| {
                        generate_file(path, PARSER_NAME_H_TEMPLATE, language_name, &generate_opts)
                    },
                )?;
                Ok(())
            })?;

            missing_path(
                path.join(format!("tree-sitter-{}.pc.in", language_name.to_kebab_case())),
                |path| {
                    generate_file(
                        path,
                        PARSER_NAME_PC_IN_TEMPLATE,
                        language_name,
                        &generate_opts,
                    )
                },
            )?;

            missing_path_else(
                repo_path.join("Makefile"),
                allow_update,
                |path| {
                    generate_file(path, MAKEFILE_TEMPLATE, language_name, &generate_opts)
                },
                |path| {
                    let mut contents = fs::read_to_string(path)?;
                    if !contents.contains("cd '$(DESTDIR)$(LIBDIR)' && ln -sf") {
                        warn!("Replacing Makefile");
                        generate_file(path, MAKEFILE_TEMPLATE, language_name, &generate_opts)?;
                    } else {
                        contents = contents
                            .replace(
                                indoc! {r"
                                $(PARSER): $(SRC_DIR)/grammar.json
                                        $(TS) generate $^
                                "},
                                indoc! {r"
                                $(SRC_DIR)/grammar.json: grammar.js
                                        $(TS) generate --no-parser $^

                                $(PARSER): $(SRC_DIR)/grammar.json
                                        $(TS) generate $^
                                "}
                            );
                        write_file(path, contents)?;
                    }
                    Ok(())
                },
            )?;

            missing_path_else(
                repo_path.join("CMakeLists.txt"),
                allow_update,
                |path| generate_file(path, CMAKELISTS_TXT_TEMPLATE, language_name, &generate_opts),
                |path| {
                    let mut contents = fs::read_to_string(path)?;
                    contents = contents
                        .replace("add_custom_target(test", "add_custom_target(ts-test")
                        .replace(
                            &formatdoc! {r#"
                            install(FILES bindings/c/tree-sitter-{language_name}.h
                                    DESTINATION "${{CMAKE_INSTALL_INCLUDEDIR}}/tree_sitter")
                            "#},
                            indoc! {r#"
                            install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bindings/c/tree_sitter"
                                    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
                                    FILES_MATCHING PATTERN "*.h")
                            "#}
                        ).replace(
                            &format!("target_include_directories(tree-sitter-{language_name} PRIVATE src)"),
                            &formatdoc! {"
                            target_include_directories(tree-sitter-{language_name}
                                                       PRIVATE src
                                                       INTERFACE $<BUILD_INTERFACE:${{CMAKE_CURRENT_SOURCE_DIR}}/bindings/c>
                                                                 $<INSTALL_INTERFACE:${{CMAKE_INSTALL_INCLUDEDIR}}>)
                            "}
                        ).replace(
                            indoc! {r#"
                            add_custom_command(OUTPUT "${CMAKE_CURRENT_SOURCE_DIR}/src/parser.c"
                                               DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/grammar.json"
                                               COMMAND "${TREE_SITTER_CLI}" generate src/grammar.json
                                                        --abi=${TREE_SITTER_ABI_VERSION}
                                               WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
                                               COMMENT "Generating parser.c")
                            "#},
                            indoc! {r#"
                            add_custom_command(OUTPUT "${CMAKE_CURRENT_SOURCE_DIR}/src/grammar.json"
                                               DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/grammar.js"
                                               COMMAND "${TREE_SITTER_CLI}" generate grammar.js
                                                        --no-parser
                                               WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
                                               COMMENT "Generating grammar.json")

                            add_custom_command(OUTPUT "${CMAKE_CURRENT_SOURCE_DIR}/src/parser.c"
                                               DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/grammar.json"
                                               COMMAND "${TREE_SITTER_CLI}" generate src/grammar.json
                                                        --abi=${TREE_SITTER_ABI_VERSION}
                                               WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
                                               COMMENT "Generating parser.c")
                            "#}
                        );
                    write_file(path, contents)?;
                    Ok(())
                },
            )?;

            Ok(())
        })?;
    }

    // Generate Go bindings
    if tree_sitter_config.bindings.go {
        missing_path(bindings_dir.join("go"), create_dir)?.apply(|path| {
            missing_path(path.join("binding.go"), |path| {
                generate_file(path, BINDING_GO_TEMPLATE, language_name, &generate_opts)
            })?;

            missing_path(path.join("binding_test.go"), |path| {
                generate_file(
                    path,
                    BINDING_TEST_GO_TEMPLATE,
                    language_name,
                    &generate_opts,
                )
            })?;

            missing_path(repo_path.join("go.mod"), |path| {
                generate_file(path, GO_MOD_TEMPLATE, language_name, &generate_opts)
            })?;

            Ok(())
        })?;
    }

    // Generate Python bindings
    if tree_sitter_config.bindings.python {
        missing_path(bindings_dir.join("python"), create_dir)?.apply(|path| {
            let lang_path = path.join(format!("tree_sitter_{}", language_name.to_snake_case()));
            missing_path(&lang_path, create_dir)?;

            missing_path_else(
                lang_path.join("binding.c"),
                allow_update,
                |path| generate_file(path, PY_BINDING_C_TEMPLATE, language_name, &generate_opts),
                |path| {
                    let mut contents = fs::read_to_string(path)?;
                    if !contents.contains("PyModuleDef_Init") {
                        contents = contents
                            .replace("PyModule_Create", "PyModuleDef_Init")
                            .replace(
                                "static PyMethodDef methods[] = {\n",
                                indoc! {"
                                static struct PyModuleDef_Slot slots[] = {
                                #ifdef Py_GIL_DISABLED
                                    {Py_mod_gil, Py_MOD_GIL_NOT_USED},
                                #endif
                                    {0, NULL}
                                };

                                static PyMethodDef methods[] = {
                                "},
                            )
                            .replace(
                                indoc! {"
                                .m_size = -1,
                                    .m_methods = methods
                                "},
                                indoc! {"
                                .m_size = 0,
                                    .m_methods = methods,
                                    .m_slots = slots,
                                "},
                            );
                        write_file(path, contents)?;
                    }
                    Ok(())
                },
            )?;

            missing_path_else(
                lang_path.join("__init__.py"),
                allow_update,
                |path| {
                    generate_file(path, INIT_PY_TEMPLATE, language_name, &generate_opts)
                },
                |path| {
                    let contents = fs::read_to_string(path)?;
                    if !contents.contains("uncomment these to include any queries") {
                        warn!("Replacing __init__.py");
                        generate_file(path, INIT_PY_TEMPLATE, language_name, &generate_opts)?;
                    }
                    Ok(())
                },
            )?;

            missing_path_else(
                lang_path.join("__init__.pyi"),
                allow_update,
                |path| generate_file(path, INIT_PYI_TEMPLATE, language_name, &generate_opts),
                |path| {
                    let mut contents = fs::read_to_string(path)?;
                    if contents.contains("uncomment these to include any queries") {
                        warn!("Replacing __init__.pyi");
                        generate_file(path, INIT_PYI_TEMPLATE, language_name, &generate_opts)?;
                    } else if !contents.contains("CapsuleType") {
                        contents = contents
                            .replace(
                                "from typing import Final",
                                "from typing import Final\nfrom typing_extensions import CapsuleType"
                            )
                            .replace("-> object:", "-> CapsuleType:");
                        write_file(path, contents)?;
                    }
                    Ok(())
                },
            )?;

            missing_path(lang_path.join("py.typed"), |path| {
                generate_file(path, "", language_name, &generate_opts) // py.typed is empty
            })?;

            missing_path(path.join("tests"), create_dir)?.apply(|path| {
                missing_path_else(
                    path.join("test_binding.py"),
                    allow_update,
                    |path| {
                        generate_file(
                            path,
                            TEST_BINDING_PY_TEMPLATE,
                            language_name,
                            &generate_opts,
                        )
                    },
                    |path| {
                        let mut contents = fs::read_to_string(path)?;
                        if !contents.contains("Parser(Language(") {
                            contents = contents
                                .replace("tree_sitter.Language(", "Parser(Language(")
                                .replace(".language())\n", ".language()))\n")
                                .replace(
                                    "import tree_sitter\n",
                                    "from tree_sitter import Language, Parser\n",
                                );
                            write_file(path, contents)?;
                        }
                        Ok(())
                    },
                )?;
                Ok(())
            })?;

            missing_path_else(
                repo_path.join("setup.py"),
                allow_update,
                |path| generate_file(path, SETUP_PY_TEMPLATE, language_name, &generate_opts),
                |path| {
                    let contents = fs::read_to_string(path)?;
                    if !contents.contains("build_ext") {
                        warn!("Replacing setup.py");
                        generate_file(path, SETUP_PY_TEMPLATE, language_name, &generate_opts)?;
                    }
                    Ok(())
                },
            )?;

            missing_path_else(
                repo_path.join("pyproject.toml"),
                allow_update,
                |path| {
                    generate_file(
                        path,
                        PYPROJECT_TOML_TEMPLATE,
                        dashed_language_name.as_str(),
                        &generate_opts,
                    )
                },
                |path| {
                    let mut contents = fs::read_to_string(path)?;
                    if !contents.contains("cp310-*") {
                        contents = contents
                            .replace(r#"build = "cp39-*""#, r#"build = "cp310-*""#)
                            .replace(r#"python = ">=3.9""#, r#"python = ">=3.10""#)
                            .replace("tree-sitter~=0.22", "tree-sitter~=0.24");
                        write_file(path, contents)?;
                    }
                    Ok(())
                },
            )?;

            Ok(())
        })?;
    }

    // Generate Swift bindings
    if tree_sitter_config.bindings.swift {
        missing_path(bindings_dir.join("swift"), create_dir)?.apply(|path| {
            let lang_path = path.join(&class_name);
            missing_path(&lang_path, create_dir)?;

            missing_path(lang_path.join(format!("{language_name}.h")), |path| {
                generate_file(path, PARSER_NAME_H_TEMPLATE, language_name, &generate_opts)
            })?;

            missing_path(path.join(format!("{class_name}Tests")), create_dir)?.apply(|path| {
                missing_path(path.join(format!("{class_name}Tests.swift")), |path| {
                    generate_file(path, TESTS_SWIFT_TEMPLATE, language_name, &generate_opts)
                })?;

                Ok(())
            })?;

            missing_path_else(
                repo_path.join("Package.swift"),
                allow_update,
                |path| generate_file(path, PACKAGE_SWIFT_TEMPLATE, language_name, &generate_opts),
                |path| {
                    let mut contents = fs::read_to_string(path)?;
                    contents = contents
                        .replace(
                            "https://github.com/ChimeHQ/SwiftTreeSitter",
                            "https://github.com/tree-sitter/swift-tree-sitter",
                        )
                        .replace("version: \"0.8.0\")", "version: \"0.9.0\")")
                        .replace("(url:", "(name: \"SwiftTreeSitter\", url:");
                    write_file(path, contents)?;
                    Ok(())
                },
            )?;

            Ok(())
        })?;
    }

    // Generate Zig bindings
    if tree_sitter_config.bindings.zig {
        missing_path_else(
            repo_path.join("build.zig"),
            allow_update,
            |path| generate_file(path, BUILD_ZIG_TEMPLATE, language_name, &generate_opts),
            |path| {
                let contents = fs::read_to_string(path)?;
                if !contents.contains("b.pkg_hash.len") {
                    warn!("Replacing build.zig");
                    generate_file(path, BUILD_ZIG_TEMPLATE, language_name, &generate_opts)
                } else {
                    Ok(())
                }
            },
        )?;

        missing_path_else(
            repo_path.join("build.zig.zon"),
            allow_update,
            |path| generate_file(path, BUILD_ZIG_ZON_TEMPLATE, language_name, &generate_opts),
            |path| {
                let contents = fs::read_to_string(path)?;
                if !contents.contains(".name = .tree_sitter_") {
                    warn!("Replacing build.zig.zon");
                    generate_file(path, BUILD_ZIG_ZON_TEMPLATE, language_name, &generate_opts)
                } else {
                    Ok(())
                }
            },
        )?;

        missing_path(bindings_dir.join("zig"), create_dir)?.apply(|path| {
            missing_path_else(
                path.join("root.zig"),
                allow_update,
                |path| generate_file(path, ROOT_ZIG_TEMPLATE, language_name, &generate_opts),
                |path| {
                    let contents = fs::read_to_string(path)?;
                    if contents.contains("ts.Language") {
                        warn!("Replacing root.zig");
                        generate_file(path, ROOT_ZIG_TEMPLATE, language_name, &generate_opts)
                    } else {
                        Ok(())
                    }
                },
            )?;

            missing_path(path.join("test.zig"), |path| {
                generate_file(path, TEST_ZIG_TEMPLATE, language_name, &generate_opts)
            })?;

            Ok(())
        })?;
    }

    Ok(())
}

pub fn get_root_path(path: &Path) -> Result<PathBuf> {
    let mut pathbuf = path.to_owned();
    let filename = path.file_name().unwrap().to_str().unwrap();
    let is_package_json = filename == "package.json";
    loop {
        let json = pathbuf
            .exists()
            .then(|| {
                let contents = fs::read_to_string(pathbuf.as_path())
                    .with_context(|| format!("Failed to read {filename}"))?;
                if is_package_json {
                    serde_json::from_str::<Map<String, Value>>(&contents)
                        .context(format!("Failed to parse {filename}"))
                        .map(|v| v.contains_key("tree-sitter"))
                } else {
                    serde_json::from_str::<TreeSitterJSON>(&contents)
                        .context(format!("Failed to parse {filename}"))
                        .map(|_| true)
                }
            })
            .transpose()?;
        if json == Some(true) {
            return Ok(pathbuf.parent().unwrap().to_path_buf());
        }
        pathbuf.pop(); // filename
        if !pathbuf.pop() {
            return Err(anyhow!(format!(
                concat!(
                    "Failed to locate a {} file,",
                    " please ensure you have one, and if you don't then consult the docs",
                ),
                filename
            )));
        }
        pathbuf.push(filename);
    }
}

fn generate_file(
    path: &Path,
    template: &str,
    language_name: &str,
    generate_opts: &GenerateOpts,
) -> Result<()> {
    let filename = path.file_name().unwrap().to_str().unwrap();

    let mut replacement = template
        .replace(
            CAMEL_PARSER_NAME_PLACEHOLDER,
            generate_opts.camel_parser_name,
        )
        .replace(
            TITLE_PARSER_NAME_PLACEHOLDER,
            generate_opts.title_parser_name,
        )
        .replace(
            UPPER_PARSER_NAME_PLACEHOLDER,
            &language_name.to_shouty_snake_case(),
        )
        .replace(
            LOWER_PARSER_NAME_PLACEHOLDER,
            &language_name.to_snake_case(),
        )
        .replace(
            KEBAB_PARSER_NAME_PLACEHOLDER,
            &language_name.to_kebab_case(),
        )
        .replace(PARSER_NAME_PLACEHOLDER, language_name)
        .replace(CLI_VERSION_PLACEHOLDER, CLI_VERSION)
        .replace(RUST_BINDING_VERSION_PLACEHOLDER, RUST_BINDING_VERSION)
        .replace(ABI_VERSION_MAX_PLACEHOLDER, &ABI_VERSION_MAX.to_string())
        .replace(
            PARSER_VERSION_PLACEHOLDER,
            &generate_opts.version.to_string(),
        )
        .replace(PARSER_CLASS_NAME_PLACEHOLDER, generate_opts.class_name)
        .replace(
            HIGHLIGHTS_QUERY_PATH_PLACEHOLDER,
            generate_opts.highlights_query_path,
        )
        .replace(
            INJECTIONS_QUERY_PATH_PLACEHOLDER,
            generate_opts.injections_query_path,
        )
        .replace(
            LOCALS_QUERY_PATH_PLACEHOLDER,
            generate_opts.locals_query_path,
        )
        .replace(TAGS_QUERY_PATH_PLACEHOLDER, generate_opts.tags_query_path);

    if let Some(name) = generate_opts.author_name {
        replacement = replacement.replace(AUTHOR_NAME_PLACEHOLDER, name);
    } else {
        match filename {
            "package.json" => {
                replacement = replacement.replace(AUTHOR_NAME_PLACEHOLDER_JS, "");
            }
            "pyproject.toml" => {
                replacement = replacement.replace(AUTHOR_NAME_PLACEHOLDER_PY, "");
            }
            "grammar.js" => {
                replacement = replacement.replace(AUTHOR_NAME_PLACEHOLDER_GRAMMAR, "");
            }
            "Cargo.toml" => {
                replacement = replacement.replace(AUTHOR_NAME_PLACEHOLDER_RS, "");
            }
            _ => {}
        }
    }

    if let Some(email) = generate_opts.author_email {
        replacement = match filename {
            "Cargo.toml" | "grammar.js" => {
                replacement.replace(AUTHOR_EMAIL_PLACEHOLDER, &format!("<{email}>"))
            }
            _ => replacement.replace(AUTHOR_EMAIL_PLACEHOLDER, email),
        }
    } else {
        match filename {
            "package.json" => {
                replacement = replacement.replace(AUTHOR_EMAIL_PLACEHOLDER_JS, "");
            }
            "pyproject.toml" => {
                replacement = replacement.replace(AUTHOR_EMAIL_PLACEHOLDER_PY, "");
            }
            "grammar.js" => {
                replacement = replacement.replace(AUTHOR_EMAIL_PLACEHOLDER_GRAMMAR, "");
            }
            "Cargo.toml" => {
                replacement = replacement.replace(AUTHOR_EMAIL_PLACEHOLDER_RS, "");
            }
            _ => {}
        }
    }

    if filename == "package.json" {
        if let Some(url) = generate_opts.author_url {
            replacement = replacement.replace(AUTHOR_URL_PLACEHOLDER, url);
        } else {
            replacement = replacement.replace(AUTHOR_URL_PLACEHOLDER_JS, "");
        }
    }

    if generate_opts.author_name.is_none()
        && generate_opts.author_email.is_none()
        && generate_opts.author_url.is_none()
        && filename == "package.json"
    {
        if let Some(start_idx) = replacement.find(AUTHOR_BLOCK_JS) {
            if let Some(end_idx) = replacement[start_idx..]
                .find("},")
                .map(|i| i + start_idx + 2)
            {
                replacement.replace_range(start_idx..end_idx, "");
            }
        }
    } else if generate_opts.author_name.is_none() && generate_opts.author_email.is_none() {
        match filename {
            "pyproject.toml" => {
                if let Some(start_idx) = replacement.find(AUTHOR_BLOCK_PY) {
                    if let Some(end_idx) = replacement[start_idx..]
                        .find("}]")
                        .map(|i| i + start_idx + 2)
                    {
                        replacement.replace_range(start_idx..end_idx, "");
                    }
                }
            }
            "grammar.js" => {
                if let Some(start_idx) = replacement.find(AUTHOR_BLOCK_GRAMMAR) {
                    if let Some(end_idx) = replacement[start_idx..]
                        .find(" \n")
                        .map(|i| i + start_idx + 1)
                    {
                        replacement.replace_range(start_idx..end_idx, "");
                    }
                }
            }
            "Cargo.toml" => {
                if let Some(start_idx) = replacement.find(AUTHOR_BLOCK_RS) {
                    if let Some(end_idx) = replacement[start_idx..]
                        .find("\"]")
                        .map(|i| i + start_idx + 2)
                    {
                        replacement.replace_range(start_idx..end_idx, "");
                    }
                }
            }
            _ => {}
        }
    }

    if let Some(license) = generate_opts.license {
        replacement = replacement.replace(PARSER_LICENSE_PLACEHOLDER, license);
    } else {
        replacement = replacement.replace(PARSER_LICENSE_PLACEHOLDER, "MIT");
    }

    if let Some(description) = generate_opts.description {
        replacement = replacement.replace(PARSER_DESCRIPTION_PLACEHOLDER, description);
    } else {
        replacement = replacement.replace(
            PARSER_DESCRIPTION_PLACEHOLDER,
            &format!(
                "{} grammar for tree-sitter",
                generate_opts.camel_parser_name,
            ),
        );
    }

    if let Some(repository) = generate_opts.repository {
        replacement = replacement
            .replace(
                PARSER_URL_STRIPPED_PLACEHOLDER,
                &repository.replace("https://", "").to_lowercase(),
            )
            .replace(PARSER_URL_PLACEHOLDER, &repository.to_lowercase());
    } else {
        replacement = replacement
            .replace(
                PARSER_URL_STRIPPED_PLACEHOLDER,
                &format!(
                    "github.com/tree-sitter/tree-sitter-{}",
                    language_name.to_lowercase()
                ),
            )
            .replace(
                PARSER_URL_PLACEHOLDER,
                &format!(
                    "https://github.com/tree-sitter/tree-sitter-{}",
                    language_name.to_lowercase()
                ),
            );
    }

    if let Some(funding_url) = generate_opts.funding {
        match filename {
            "pyproject.toml" | "package.json" => {
                replacement = replacement.replace(FUNDING_URL_PLACEHOLDER, funding_url);
            }
            _ => {}
        }
    } else {
        match filename {
            "package.json" => {
                replacement = replacement.replace("  \"funding\": \"FUNDING_URL\",\n", "");
            }
            "pyproject.toml" => {
                replacement = replacement.replace("Funding = \"FUNDING_URL\"\n", "");
            }
            _ => {}
        }
    }

    if filename == "build.zig.zon" {
        let id = thread_rng().gen_range(1u32..0xFFFF_FFFFu32);
        let checksum = crc32(format!("tree_sitter_{language_name}").as_bytes());
        replacement = replacement.replace(
            PARSER_FINGERPRINT_PLACEHOLDER,
            #[cfg(target_endian = "little")]
            &format!("0x{checksum:x}{id:x}"),
            #[cfg(target_endian = "big")]
            &format!("0x{id:x}{checksum:x}"),
        );
    }

    write_file(path, replacement)?;
    Ok(())
}

fn create_dir(path: &Path) -> Result<()> {
    fs::create_dir_all(path)
        .with_context(|| format!("Failed to create {:?}", path.to_string_lossy()))
}

#[derive(PartialEq, Eq, Debug)]
enum PathState<P>
where
    P: AsRef<Path>,
{
    Exists(P),
    Missing(P),
}

#[allow(dead_code)]
impl<P> PathState<P>
where
    P: AsRef<Path>,
{
    fn exists(&self, mut action: impl FnMut(&Path) -> Result<()>) -> Result<&Self> {
        if let Self::Exists(path) = self {
            action(path.as_ref())?;
        }
        Ok(self)
    }

    fn missing(&self, mut action: impl FnMut(&Path) -> Result<()>) -> Result<&Self> {
        if let Self::Missing(path) = self {
            action(path.as_ref())?;
        }
        Ok(self)
    }

    fn apply(&self, mut action: impl FnMut(&Path) -> Result<()>) -> Result<&Self> {
        action(self.as_path())?;
        Ok(self)
    }

    fn apply_state(&self, mut action: impl FnMut(&Self) -> Result<()>) -> Result<&Self> {
        action(self)?;
        Ok(self)
    }

    fn as_path(&self) -> &Path {
        match self {
            Self::Exists(path) | Self::Missing(path) => path.as_ref(),
        }
    }
}

fn missing_path<P, F>(path: P, mut action: F) -> Result<PathState<P>>
where
    P: AsRef<Path>,
    F: FnMut(&Path) -> Result<()>,
{
    let path_ref = path.as_ref();
    if !path_ref.exists() {
        action(path_ref)?;
        Ok(PathState::Missing(path))
    } else {
        Ok(PathState::Exists(path))
    }
}

fn missing_path_else<P, T, F>(
    path: P,
    allow_update: bool,
    mut action: T,
    mut else_action: F,
) -> Result<PathState<P>>
where
    P: AsRef<Path>,
    T: FnMut(&Path) -> Result<()>,
    F: FnMut(&Path) -> Result<()>,
{
    let path_ref = path.as_ref();
    if !path_ref.exists() {
        action(path_ref)?;
        Ok(PathState::Missing(path))
    } else {
        if allow_update {
            else_action(path_ref)?;
        }
        Ok(PathState::Exists(path))
    }
}
