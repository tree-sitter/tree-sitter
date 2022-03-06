use super::write_file;
use anyhow::{Context, Result};
use std::path::{Path, PathBuf};
use std::{fs, str};

const BINDING_CC_TEMPLATE: &'static str = include_str!("./templates/binding.cc");
const BINDING_GYP_TEMPLATE: &'static str = include_str!("./templates/binding.gyp");
const INDEX_JS_TEMPLATE: &'static str = include_str!("./templates/index.js");
const LIB_RS_TEMPLATE: &'static str = include_str!("./templates/lib.rs");
const BUILD_RS_TEMPLATE: &'static str = include_str!("./templates/build.rs");
const CARGO_TOML_TEMPLATE: &'static str = include_str!("./templates/cargo.toml");
const PACKAGE_JSON_TEMPLATE: &'static str = include_str!("./templates/package.json");
const PARSER_NAME_PLACEHOLDER: &'static str = "PARSER_NAME";
const CLI_VERSION_PLACEHOLDER: &'static str = "CLI_VERSION";
const CLI_VERSION: &'static str = env!("CARGO_PKG_VERSION");
const RUST_BINDING_VERSION: &'static str = env!("RUST_BINDING_VERSION");
const RUST_BINDING_VERSION_PLACEHOLDER: &'static str = "RUST_BINDING_VERSION";

pub fn generate_binding_files(repo_path: &Path, language_name: &str) -> Result<()> {
    let bindings_dir = repo_path.join("bindings");

    let dashed_language_name = language_name.replace("_", "-");
    let dashed_language_name = dashed_language_name.as_str();

    // Generate rust bindings if needed.
    let rust_binding_dir = bindings_dir.join("rust");
    create_path(&rust_binding_dir, |path| create_dir(path))?;

    create_path(&rust_binding_dir.join("lib.rs").to_owned(), |path| {
        generate_file(path, LIB_RS_TEMPLATE, language_name)
    })?;

    create_path(&rust_binding_dir.join("build.rs").to_owned(), |path| {
        generate_file(path, BUILD_RS_TEMPLATE, language_name)
    })?;

    create_path(&repo_path.join("Cargo.toml").to_owned(), |path| {
        generate_file(path, CARGO_TOML_TEMPLATE, dashed_language_name)
    })?;

    // Generate node bindings
    let node_binding_dir = bindings_dir.join("node");
    create_path(&node_binding_dir, |path| create_dir(path))?;

    create_path(&node_binding_dir.join("index.js").to_owned(), |path| {
        generate_file(path, INDEX_JS_TEMPLATE, language_name)
    })?;

    create_path(&node_binding_dir.join("binding.cc").to_owned(), |path| {
        generate_file(path, BINDING_CC_TEMPLATE, language_name)
    })?;

    // Create binding.gyp, or update it with new binding path.
    let binding_gyp_path = repo_path.join("binding.gyp");
    create_path_else(
        &binding_gyp_path,
        |path| generate_file(path, BINDING_GYP_TEMPLATE, language_name),
        |path| {
            let binding_gyp =
                fs::read_to_string(path).with_context(|| "Failed to read binding.gyp")?;
            let old_path = "\"src/binding.cc\"";
            if binding_gyp.contains(old_path) {
                eprintln!("Updating binding.gyp with new binding path");
                let binding_gyp = binding_gyp.replace(old_path, "\"bindings/node/binding.cc\"");
                write_file(path, binding_gyp)?;
            }
            Ok(())
        },
    )?;

    // Create package.json, or update it with new binding path.
    let package_json_path = repo_path.join("package.json");
    create_path_else(
        &package_json_path,
        |path| generate_file(path, PACKAGE_JSON_TEMPLATE, dashed_language_name),
        |path| {
            let package_json_str =
                fs::read_to_string(path).with_context(|| "Failed to read package.json")?;
            let mut package_json =
                serde_json::from_str::<serde_json::Map<String, serde_json::Value>>(
                    &package_json_str,
                )
                .with_context(|| "Failed to parse package.json")?;
            let package_json_main = package_json.get("main");
            let package_json_needs_update = package_json_main.map_or(true, |v| {
                let main_string = v.as_str();
                main_string == Some("index.js") || main_string == Some("./index.js")
            });
            if package_json_needs_update {
                eprintln!("Updating package.json with new binding path");
                package_json.insert(
                    "main".to_string(),
                    serde_json::Value::String("bindings/node".to_string()),
                );
                let mut package_json_str = serde_json::to_string_pretty(&package_json)?;
                package_json_str.push('\n');
                write_file(path, package_json_str)?;
            }
            Ok(())
        },
    )?;

    // Remove files from old node binding paths.
    let old_index_js_path = repo_path.join("index.js");
    let old_binding_cc_path = repo_path.join("src").join("binding.cc");
    if old_index_js_path.exists() {
        fs::remove_file(old_index_js_path).ok();
    }
    if old_binding_cc_path.exists() {
        fs::remove_file(old_binding_cc_path).ok();
    }

    Ok(())
}

fn generate_file(path: &Path, template: &str, language_name: &str) -> Result<()> {
    write_file(
        path,
        template
            .replace(PARSER_NAME_PLACEHOLDER, language_name)
            .replace(CLI_VERSION_PLACEHOLDER, CLI_VERSION)
            .replace(RUST_BINDING_VERSION_PLACEHOLDER, RUST_BINDING_VERSION),
    )
}

fn create_dir(path: &Path) -> Result<()> {
    fs::create_dir_all(&path)
        .with_context(|| format!("Failed to create {:?}", path.to_string_lossy()))
}

fn create_path<F>(path: &PathBuf, action: F) -> Result<bool>
where
    F: Fn(&PathBuf) -> Result<()>,
{
    if !path.exists() {
        action(path)?;
        return Ok(true);
    }
    Ok(false)
}

fn create_path_else<T, F>(path: &PathBuf, action: T, else_action: F) -> Result<bool>
where
    T: Fn(&PathBuf) -> Result<()>,
    F: Fn(&PathBuf) -> Result<()>,
{
    if !path.exists() {
        action(path)?;
        return Ok(true);
    } else {
        else_action(path)?;
    }
    Ok(false)
}
