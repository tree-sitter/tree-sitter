use super::error::{Error, Result};
use super::generate::parse_grammar::GrammarJSON;
use std::fs;
use std::path::Path;
use std::process::Command;

pub fn compile_language_to_wasm(language_dir: &Path) -> Result<()> {
    let src_dir = language_dir.join("src");
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

    let mut command = Command::new("emcc");
    command.args(&[
        "-o",
        &format!("tree-sitter-{}.wasm", grammar.name),
        "-Os",
        "-s",
        "WASM=1",
        "-s",
        "SIDE_MODULE=1",
        "-s",
        &format!("EXPORTED_FUNCTIONS=[\"_tree_sitter_{}\"]", grammar.name),
    ]);
    command.arg("-I").arg(&src_dir);

    // Find source files to compile
    let entries = fs::read_dir(&src_dir)
        .map_err(|e| format!("Failed to read source directory {:?} - {}", src_dir, e))?;

    for entry in entries {
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
                command.arg(entry.path());
            }
        }
    }

    let output = command
        .output()
        .map_err(|e| format!("Failed to run emcc command - {}", e))?;
    if output.status.success() {
        Ok(())
    } else {
        Err(Error::from(format!(
            "emcc command failed - {}",
            String::from_utf8_lossy(&output.stderr)
        )))
    }
}
