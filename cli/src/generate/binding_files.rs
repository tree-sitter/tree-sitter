use super::write_file;
use crate::error::{Error, Result};
use std::path::Path;
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

pub fn generate_binding_files(repo_path: &Path, language_name: &str) -> Result<()> {
    let bindings_dir = repo_path.join("bindings");

    let dashed_language_name = language_name.replace("_", "-");
    let dashed_language_name = dashed_language_name.as_str();

    // Generate rust bindings if needed.
    let rust_binding_dir = bindings_dir.join("rust");
    if !rust_binding_dir.exists() {
        create_dir(&rust_binding_dir)?;
        generate_file(
            &rust_binding_dir.join("lib.rs"),
            LIB_RS_TEMPLATE,
            language_name,
        )?;
        generate_file(
            &rust_binding_dir.join("build.rs"),
            BUILD_RS_TEMPLATE,
            language_name,
        )?;
        let cargo_toml_path = repo_path.join("Cargo.toml");
        if !cargo_toml_path.exists() {
            generate_file(&cargo_toml_path, CARGO_TOML_TEMPLATE, dashed_language_name)?;
        }
    }

    // Generate node bindings
    let node_binding_dir = bindings_dir.join("node");
    if !node_binding_dir.exists() {
        create_dir(&node_binding_dir)?;
        generate_file(
            &node_binding_dir.join("index.js"),
            INDEX_JS_TEMPLATE,
            language_name,
        )?;
        generate_file(
            &node_binding_dir.join("binding.cc"),
            BINDING_CC_TEMPLATE,
            language_name,
        )?;

        // Create binding.gyp, or update it with new binding path.
        let binding_gyp_path = repo_path.join("binding.gyp");
        if binding_gyp_path.exists() {
            eprintln!("Updating binding.gyp with new binding path");

            let binding_gyp = fs::read_to_string(&binding_gyp_path)
                .map_err(Error::wrap(|| "Failed to read binding.gyp"))?;
            let binding_gyp = binding_gyp.replace("src/binding.cc", "bindings/node/binding.cc");
            write_file(&binding_gyp_path, binding_gyp)?;
        } else {
            generate_file(&binding_gyp_path, BINDING_GYP_TEMPLATE, language_name)?;
        }

        // Create package.json, or update it with new binding path.
        let package_json_path = repo_path.join("package.json");
        if package_json_path.exists() {
            let package_json_str = fs::read_to_string(&package_json_path)
                .map_err(Error::wrap(|| "Failed to read package.json"))?;
            let mut package_json =
                serde_json::from_str::<serde_json::Map<String, serde_json::Value>>(
                    &package_json_str,
                )
                .map_err(Error::wrap(|| "Failed to parse package.json"))?;
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
                write_file(&package_json_path, package_json_str)?;
            }
        } else {
            generate_file(
                &package_json_path,
                PACKAGE_JSON_TEMPLATE,
                dashed_language_name,
            )?;
        }

        // Remove files from old node binding paths.
        let old_index_js_path = repo_path.join("index.js");
        let old_binding_cc_path = repo_path.join("src").join("binding.cc");
        if old_index_js_path.exists() {
            fs::remove_file(old_index_js_path).ok();
        }
        if old_binding_cc_path.exists() {
            fs::remove_file(old_binding_cc_path).ok();
        }
    }

    Ok(())
}

fn generate_file(path: &Path, template: &str, language_name: &str) -> Result<()> {
    write_file(
        path,
        template
            .replace(PARSER_NAME_PLACEHOLDER, language_name)
            .replace(CLI_VERSION_PLACEHOLDER, CLI_VERSION),
    )
}

fn create_dir(path: &Path) -> Result<()> {
    fs::create_dir_all(&path).map_err(Error::wrap(|| {
        format!("Failed to create {:?}", path.to_string_lossy())
    }))
}
