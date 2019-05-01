use super::error::{Error, Result};
use super::generate::parse_grammar::GrammarJSON;
use std::ffi::{OsStr, OsString};
use std::fs;
use std::path::Path;
use std::process::Command;

pub fn compile_language_to_wasm(language_dir: &Path) -> Result<()> {
    let src_dir = language_dir.join("src");

    // Parse the grammar.json to find out the language name.
    let grammar_json_path = src_dir.join("grammar.json");
    let grammar_json = fs::read_to_string(&grammar_json_path).map_err(|e| {
        format!(
            "Failed to read grammar file {:?} - {}",
            grammar_json_path, e
        )
    })?;
    let grammar: GrammarJSON = serde_json::from_str(&grammar_json).map_err(|e| {
        format!(
            "Failed to parse grammar file {:?} - {}",
            grammar_json_path, e
        )
    })?;
    let output_filename = format!("tree-sitter-{}.wasm", grammar.name);

    // Get the current user id so that files created in the docker container will have
    // the same owner.
    let user_id_output = Command::new("id")
        .arg("-u")
        .output()
        .map_err(|e| format!("Failed to get get current user id {}", e))?;
    let user_id = String::from_utf8_lossy(&user_id_output.stdout);
    let user_id = user_id.trim();

    // Use `emscripten-slim` docker image with the parser directory mounted as a volume.
    let mut command = Command::new("docker");
    let mut volume_string = OsString::from(language_dir);
    volume_string.push(":/src");
    command.args(&["run", "--rm"]);
    command.args(&[OsStr::new("--volume"), &volume_string]);
    command.args(&["--user", user_id, "trzeci/emscripten-slim"]);

    // Run emscripten in the container
    command.args(&[
        "emcc",
        "-o",
        &output_filename,
        "-Os",
        "-s",
        "WASM=1",
        "-s",
        "SIDE_MODULE=1",
        "-s",
        "TOTAL_MEMORY=33554432",
        "-s",
        &format!("EXPORTED_FUNCTIONS=[\"_tree_sitter_{}\"]", grammar.name),
        "-fno-exceptions",
        "-I",
        "src",
    ]);

    // Find source files to pass to emscripten
    let src_entries = fs::read_dir(&src_dir)
        .map_err(|e| format!("Failed to read source directory {:?} - {}", src_dir, e))?;

    for entry in src_entries {
        let entry = entry?;
        let file_name = entry.file_name();

        // Do not compile the node.js binding file.
        if file_name
            .to_str()
            .map_or(false, |s| s.starts_with("binding"))
        {
            continue;
        }

        // Compile any .c, .cc, or .cpp files
        if let Some(extension) = Path::new(&file_name).extension().and_then(|s| s.to_str()) {
            if extension == "c" || extension == "cc" || extension == "cpp" {
                command.arg(Path::new("src").join(entry.file_name()));
            }
        }
    }

    let output = command
        .output()
        .map_err(|e| format!("Failed to run docker emcc command - {}", e))?;
    if !output.status.success() {
        return Err(Error::from(format!(
            "emcc command failed - {}",
            String::from_utf8_lossy(&output.stderr)
        )));
    }

    // Move the created `.wasm` file into the current working directory.
    fs::rename(&language_dir.join(&output_filename), &output_filename)
        .map_err(|e| format!("Couldn't find output file {:?} - {}", output_filename, e))?;

    Ok(())
}
