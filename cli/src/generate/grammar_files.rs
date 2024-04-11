use super::write_file;
use anyhow::{anyhow, Context, Result};
use heck::{ToKebabCase, ToShoutySnakeCase, ToSnakeCase, ToUpperCamelCase};
use indoc::indoc;
use serde::Deserialize;
use serde_json::{json, Map, Value};
use std::fs::File;
use std::io::BufReader;
use std::path::{Path, PathBuf};
use std::{fs, str};

const CLI_VERSION: &str = env!("CARGO_PKG_VERSION");
const CLI_VERSION_PLACEHOLDER: &str = "CLI_VERSION";

const PARSER_NAME_PLACEHOLDER: &str = "PARSER_NAME";
const CAMEL_PARSER_NAME_PLACEHOLDER: &str = "CAMEL_PARSER_NAME";
const UPPER_PARSER_NAME_PLACEHOLDER: &str = "UPPER_PARSER_NAME";
const LOWER_PARSER_NAME_PLACEHOLDER: &str = "LOWER_PARSER_NAME";

const GRAMMAR_JS_TEMPLATE: &str = include_str!("./templates/grammar.js");
const PACKAGE_JSON_TEMPLATE: &str = include_str!("./templates/package.json");
const GITIGNORE_TEMPLATE: &str = include_str!("./templates/gitignore");
const GITATTRIBUTES_TEMPLATE: &str = include_str!("./templates/gitattributes");
const EDITORCONFIG_TEMPLATE: &str = include_str!("./templates/.editorconfig");

const RUST_BINDING_VERSION: &str = env!("CARGO_PKG_VERSION");
const RUST_BINDING_VERSION_PLACEHOLDER: &str = "RUST_BINDING_VERSION";

const LIB_RS_TEMPLATE: &str = include_str!("./templates/lib.rs");
const BUILD_RS_TEMPLATE: &str = include_str!("./templates/build.rs");
const CARGO_TOML_TEMPLATE: &str = include_str!("./templates/cargo.toml");

const INDEX_JS_TEMPLATE: &str = include_str!("./templates/index.js");
const INDEX_D_TS_TEMPLATE: &str = include_str!("./templates/index.d.ts");
const JS_BINDING_CC_TEMPLATE: &str = include_str!("./templates/js-binding.cc");
const BINDING_GYP_TEMPLATE: &str = include_str!("./templates/binding.gyp");

const MAKEFILE_TEMPLATE: &str = include_str!("./templates/makefile");
const PARSER_NAME_H_TEMPLATE: &str = include_str!("./templates/PARSER_NAME.h");
const PARSER_NAME_PC_IN_TEMPLATE: &str = include_str!("./templates/PARSER_NAME.pc.in");

const GO_MOD_TEMPLATE: &str = include_str!("./templates/go.mod");
const BINDING_GO_TEMPLATE: &str = include_str!("./templates/binding.go");
const BINDING_GO_TEST_TEMPLATE: &str = include_str!("./templates/binding_test.go");

const SETUP_PY_TEMPLATE: &str = include_str!("./templates/setup.py");
const INIT_PY_TEMPLATE: &str = include_str!("./templates/__init__.py");
const INIT_PYI_TEMPLATE: &str = include_str!("./templates/__init__.pyi");
const PYPROJECT_TOML_TEMPLATE: &str = include_str!("./templates/pyproject.toml");
const PY_BINDING_C_TEMPLATE: &str = include_str!("./templates/py-binding.c");

const PACKAGE_SWIFT_TEMPLATE: &str = include_str!("./templates/Package.swift");

#[derive(Deserialize, Debug)]
struct LanguageConfiguration {}

#[derive(Deserialize, Debug)]
struct PackageJSON {
    #[serde(rename = "tree-sitter")]
    tree_sitter: Option<Vec<LanguageConfiguration>>,
}

pub fn path_in_ignore(repo_path: &Path) -> bool {
    [
        "bindings",
        "build",
        "examples",
        "node_modules",
        "queries",
        "script",
        "src",
        "target",
        "test",
        "types",
    ]
    .iter()
    .any(|dir| repo_path.ends_with(dir))
}

fn insert_after(
    map: Map<String, Value>,
    after: &str,
    key: &str,
    value: Value,
) -> Map<String, Value> {
    let mut entries = map.into_iter().collect::<Vec<_>>();
    let after_index = entries
        .iter()
        .position(|(k, _)| k == after)
        .unwrap_or(entries.len() - 1)
        + 1;
    entries.insert(after_index, (key.to_string(), value));
    entries.into_iter().collect()
}

pub fn generate_grammar_files(
    repo_path: &Path,
    language_name: &str,
    generate_bindings: bool,
) -> Result<()> {
    let dashed_language_name = language_name.to_kebab_case();

    // TODO: remove legacy code updates in v0.24.0

    // Create or update package.json
    let package_json_path_state = missing_path_else(
        repo_path.join("package.json"),
        |path| generate_file(path, PACKAGE_JSON_TEMPLATE, dashed_language_name.as_str()),
        |path| {
            let package_json_str =
                fs::read_to_string(path).with_context(|| "Failed to read package.json")?;
            let mut package_json = serde_json::from_str::<Map<String, Value>>(&package_json_str)
                .with_context(|| "Failed to parse package.json")?;
            if generate_bindings {
                let mut updated = false;

                let dependencies = package_json
                    .entry("dependencies".to_string())
                    .or_insert_with(|| Value::Object(Map::new()))
                    .as_object_mut()
                    .unwrap();
                if dependencies.remove("nan").is_some() {
                    eprintln!("Replacing nan dependency with node-addon-api in package.json");
                    dependencies.insert("node-addon-api".to_string(), "^7.1.0".into());
                    updated = true;
                }
                if !dependencies.contains_key("node-gyp-build") {
                    eprintln!("Adding node-gyp-build dependency to package.json");
                    dependencies.insert("node-gyp-build".to_string(), "^4.8.0".into());
                    updated = true;
                }

                let dev_dependencies = package_json
                    .entry("devDependencies".to_string())
                    .or_insert_with(|| Value::Object(Map::new()))
                    .as_object_mut()
                    .unwrap();
                if !dev_dependencies.contains_key("prebuildify") {
                    eprintln!("Adding prebuildify devDependency to package.json");
                    dev_dependencies.insert("prebuildify".to_string(), "^6.0.0".into());
                    updated = true;
                }

                let scripts = package_json
                    .entry("scripts".to_string())
                    .or_insert_with(|| Value::Object(Map::new()))
                    .as_object_mut()
                    .unwrap();
                match scripts.get("install") {
                    None => {
                        eprintln!("Adding an install script to package.json");
                        scripts.insert("install".to_string(), "node-gyp-build".into());
                        updated = true;
                    }
                    Some(Value::String(v)) if v != "node-gyp-build" => {
                        eprintln!("Updating the install script in package.json");
                        scripts.insert("install".to_string(), "node-gyp-build".into());
                        updated = true;
                    }
                    Some(_) => {}
                }
                if !scripts.contains_key("prebuildify") {
                    eprintln!("Adding a prebuildify script to package.json");
                    scripts.insert(
                        "prebuildify".to_string(),
                        "prebuildify --napi --strip".into(),
                    );
                    updated = true;
                }

                // insert `peerDependencies` after `dependencies`
                if !package_json.contains_key("peerDependencies") {
                    eprintln!("Adding peerDependencies to package.json");
                    package_json = insert_after(
                        package_json,
                        "dependencies",
                        "peerDependencies",
                        json!({"tree-sitter": "^0.21.0"}),
                    );

                    package_json = insert_after(
                        package_json,
                        "peerDependencies",
                        "peerDependenciesMeta",
                        json!({"tree_sitter": {"optional": true}}),
                    );
                    updated = true;
                }

                // insert `types` right after `main`
                if !package_json.contains_key("types") {
                    eprintln!("Adding types to package.json");
                    package_json =
                        insert_after(package_json, "main", "types", "bindings/node".into());
                    updated = true;
                }

                // insert `files` right after `keywords`
                if !package_json.contains_key("files") {
                    eprintln!("Adding files to package.json");
                    package_json = insert_after(
                        package_json,
                        "keywords",
                        "files",
                        json!([
                            "grammar.js",
                            "binding.gyp",
                            "prebuilds/**",
                            "bindings/node/*",
                            "queries/*",
                            "src/**",
                        ]),
                    );
                    updated = true;
                }

                // insert `tree-sitter` at the end
                if !package_json.contains_key("tree-sitter") {
                    eprintln!("Adding a `tree-sitter` section to package.json");
                    package_json.insert(
                        "tree-sitter".to_string(),
                        json!([{
                            "scope": format!("source.{language_name}"),
                            "injection-regex": format!("^{language_name}$"),
                        }]),
                    );
                    updated = true;
                }

                if updated {
                    let mut package_json_str = serde_json::to_string_pretty(&package_json)?;
                    package_json_str.push('\n');
                    write_file(path, package_json_str)?;
                }
            }

            Ok(())
        },
    )?;

    let (_, package_json) = lookup_package_json_for_path(package_json_path_state.as_path())?;

    // Do not create a grammar.js file in a repo with multiple language configs
    if !package_json.has_multiple_language_configs() {
        missing_path(repo_path.join("grammar.js"), |path| {
            generate_file(path, GRAMMAR_JS_TEMPLATE, language_name)
        })?;
    }

    if !generate_bindings {
        // our job is done
        return Ok(());
    }

    // Write .gitignore file
    missing_path(repo_path.join(".gitignore"), |path| {
        generate_file(path, GITIGNORE_TEMPLATE, language_name)
    })?;

    // Write .gitattributes file
    missing_path(repo_path.join(".gitattributes"), |path| {
        generate_file(path, GITATTRIBUTES_TEMPLATE, language_name)
    })?;

    // Write .editorconfig file
    missing_path(repo_path.join(".editorconfig"), |path| {
        generate_file(path, EDITORCONFIG_TEMPLATE, language_name)
    })?;

    let bindings_dir = repo_path.join("bindings");

    // Generate Rust bindings
    missing_path(bindings_dir.join("rust"), create_dir)?.apply(|path| {
        missing_path(path.join("lib.rs"), |path| {
            generate_file(path, LIB_RS_TEMPLATE, language_name)
        })?;

        missing_path_else(
            path.join("build.rs"),
            |path| generate_file(path, BUILD_RS_TEMPLATE, language_name),
            |path| {
                let build_rs =
                    fs::read_to_string(path).with_context(|| "Failed to read build.rs")?;
                if !build_rs.contains("/utf-8") {
                    let index = build_rs
                        .find("    let parser_path = src_dir.join(\"parser.c\")")
                        .ok_or_else(|| anyhow!(indoc!{
                            "Failed to auto-update build.rs with the `/utf-8` flag for windows.
                             To fix this, remove `bindings/rust/build.rs` and re-run `tree-sitter generate`"}))?;

                    let build_rs = format!(
                        "{}{}{}\n{}",
                        &build_rs[..index],
                        "    #[cfg(target_env = \"msvc\")]\n",
                        "    c_config.flag(\"-utf-8\");\n",
                        &build_rs[index..]
                    );

                    write_file(path, build_rs)?;
                    eprintln!("Updated build.rs with the /utf-8 flag for Windows compilation");
                }
                Ok(())
            },
        )?;

        missing_path(repo_path.join("Cargo.toml"), |path| {
            generate_file(path, CARGO_TOML_TEMPLATE, dashed_language_name.as_str())
        })?;

        Ok(())
    })?;

    // Generate Node bindings
    missing_path(bindings_dir.join("node"), create_dir)?.apply(|path| {
        missing_path_else(
            path.join("index.js"),
            |path| generate_file(path, INDEX_JS_TEMPLATE, language_name),
            |path| {
                let index_js =
                    fs::read_to_string(path).with_context(|| "Failed to read index.js")?;
                if index_js.contains("../../build/Release") {
                    eprintln!("Replacing index.js with new binding API");
                    generate_file(path, INDEX_JS_TEMPLATE, language_name)?;
                }
                Ok(())
            },
        )?;

        missing_path(path.join("index.d.ts"), |path| {
            generate_file(path, INDEX_D_TS_TEMPLATE, language_name)
        })?;

        missing_path_else(
            path.join("binding.cc"),
            |path| generate_file(path, JS_BINDING_CC_TEMPLATE, language_name),
            |path| {
                let binding_cc =
                    fs::read_to_string(path).with_context(|| "Failed to read binding.cc")?;
                if binding_cc.contains("NAN_METHOD(New) {}") {
                    eprintln!("Replacing binding.cc with new binding API");
                    generate_file(path, JS_BINDING_CC_TEMPLATE, language_name)?;
                }
                Ok(())
            },
        )?;

        // Create binding.gyp, or update it with new binding API.
        missing_path_else(
            repo_path.join("binding.gyp"),
            |path| generate_file(path, BINDING_GYP_TEMPLATE, language_name),
            |path| {
                let binding_gyp =
                    fs::read_to_string(path).with_context(|| "Failed to read binding.gyp")?;
                if binding_gyp.contains("require('nan')") {
                    eprintln!("Replacing binding.gyp with new binding API");
                    generate_file(path, BINDING_GYP_TEMPLATE, language_name)?;
                }
                Ok(())
            },
        )?;

        Ok(())
    })?;

    // Generate C bindings
    missing_path(bindings_dir.join("c"), create_dir)?.apply(|path| {
        missing_path(
            path.join(format!("tree-sitter-{language_name}.h")),
            |path| generate_file(path, PARSER_NAME_H_TEMPLATE, language_name),
        )?;

        missing_path(
            path.join(format!("tree-sitter-{language_name}.pc.in")),
            |path| generate_file(path, PARSER_NAME_PC_IN_TEMPLATE, language_name),
        )?;

        missing_path(repo_path.join("Makefile"), |path| {
            generate_file(path, MAKEFILE_TEMPLATE, language_name)
        })?;

        Ok(())
    })?;

    // Generate Go bindings
    missing_path(bindings_dir.join("go"), create_dir)?.apply(|path| {
        missing_path(path.join("binding.go"), |path| {
            generate_file(path, BINDING_GO_TEMPLATE, language_name)
        })?;

        missing_path(path.join("binding_test.go"), |path| {
            generate_file(path, BINDING_GO_TEST_TEMPLATE, language_name)
        })?;

        missing_path(path.join("go.mod"), |path| {
            generate_file(path, GO_MOD_TEMPLATE, language_name)
        })?;

        Ok(())
    })?;

    // Generate Python bindings
    missing_path(
        bindings_dir
            .join("python")
            .join(format!("tree_sitter_{}", language_name.to_snake_case())),
        create_dir,
    )?
    .apply(|path| {
        missing_path(path.join("binding.c"), |path| {
            generate_file(path, PY_BINDING_C_TEMPLATE, language_name)
        })?;

        missing_path(path.join("__init__.py"), |path| {
            generate_file(path, INIT_PY_TEMPLATE, language_name)
        })?;

        missing_path(path.join("__init__.pyi"), |path| {
            generate_file(path, INIT_PYI_TEMPLATE, language_name)
        })?;

        missing_path(path.join("py.typed"), |path| {
            generate_file(path, "", language_name) // py.typed is empty
        })?;

        missing_path(repo_path.join("setup.py"), |path| {
            generate_file(path, SETUP_PY_TEMPLATE, language_name)
        })?;

        missing_path(repo_path.join("pyproject.toml"), |path| {
            generate_file(path, PYPROJECT_TOML_TEMPLATE, dashed_language_name.as_str())
        })?;

        Ok(())
    })?;

    // Generate Swift bindings
    missing_path(
        bindings_dir
            .join("swift")
            .join(format!("TreeSitter{}", language_name.to_upper_camel_case())),
        create_dir,
    )?
    .apply(|path| {
        missing_path(path.join(format!("{language_name}.h")), |path| {
            generate_file(path, PARSER_NAME_H_TEMPLATE, language_name)
        })?;

        missing_path(repo_path.join("Package.swift"), |path| {
            generate_file(path, PACKAGE_SWIFT_TEMPLATE, language_name)
        })?;

        Ok(())
    })?;

    Ok(())
}

fn lookup_package_json_for_path(path: &Path) -> Result<(PathBuf, PackageJSON)> {
    let mut pathbuf = path.to_owned();
    loop {
        let package_json = pathbuf
            .exists()
            .then(|| -> Result<PackageJSON> {
                let file =
                    File::open(pathbuf.as_path()).with_context(|| "Failed to open package.json")?;
                Ok(serde_json::from_reader(BufReader::new(file))?)
            })
            .transpose()?;
        if let Some(package_json) = package_json {
            if package_json.tree_sitter.is_some() {
                return Ok((pathbuf, package_json));
            }
        }
        pathbuf.pop(); // package.json
        if !pathbuf.pop() {
            return Err(anyhow!(concat!(
                "Failed to locate a package.json file that has a \"tree-sitter\" section,",
                " please ensure you have one, and if you don't then consult the docs",
            )));
        }
        pathbuf.push("package.json");
    }
}

fn generate_file(path: &Path, template: &str, language_name: &str) -> Result<()> {
    write_file(
        path,
        template
            .replace(
                CAMEL_PARSER_NAME_PLACEHOLDER,
                &language_name.to_upper_camel_case(),
            )
            .replace(
                UPPER_PARSER_NAME_PLACEHOLDER,
                &language_name.to_shouty_snake_case(),
            )
            .replace(
                LOWER_PARSER_NAME_PLACEHOLDER,
                &language_name.to_snake_case(),
            )
            .replace(PARSER_NAME_PLACEHOLDER, language_name)
            .replace(CLI_VERSION_PLACEHOLDER, CLI_VERSION)
            .replace(RUST_BINDING_VERSION_PLACEHOLDER, RUST_BINDING_VERSION),
    )
}

fn create_dir(path: &Path) -> Result<()> {
    fs::create_dir_all(path)
        .with_context(|| format!("Failed to create {:?}", path.to_string_lossy()))
}

#[derive(PartialEq, Eq, Debug)]
enum PathState {
    Exists(PathBuf),
    Missing(PathBuf),
}

#[allow(dead_code)]
impl PathState {
    fn exists(&self, mut action: impl FnMut(&Path) -> Result<()>) -> Result<&Self> {
        if let Self::Exists(path) = self {
            action(path.as_path())?;
        }
        Ok(self)
    }

    fn missing(&self, mut action: impl FnMut(&Path) -> Result<()>) -> Result<&Self> {
        if let Self::Missing(path) = self {
            action(path.as_path())?;
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
            Self::Exists(path) | Self::Missing(path) => path.as_path(),
        }
    }
}

fn missing_path<F>(path: PathBuf, mut action: F) -> Result<PathState>
where
    F: FnMut(&Path) -> Result<()>,
{
    if !path.exists() {
        action(path.as_path())?;
        Ok(PathState::Missing(path))
    } else {
        Ok(PathState::Exists(path))
    }
}

fn missing_path_else<T, F>(path: PathBuf, mut action: T, mut else_action: F) -> Result<PathState>
where
    T: FnMut(&Path) -> Result<()>,
    F: FnMut(&Path) -> Result<()>,
{
    if !path.exists() {
        action(path.as_path())?;
        Ok(PathState::Missing(path))
    } else {
        else_action(path.as_path())?;
        Ok(PathState::Exists(path))
    }
}

impl PackageJSON {
    fn has_multiple_language_configs(&self) -> bool {
        self.tree_sitter.as_ref().is_some_and(|c| c.len() > 1)
    }
}
