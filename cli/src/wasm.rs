use super::error::{Error, Result};
use super::generate::parse_grammar::GrammarJSON;
use std::ffi::{OsStr, OsString};
use std::fs;
use std::path::Path;
use std::process::Command;

pub fn get_grammar_name(src_dir: &Path) -> Result<String> {
    let grammar_json_path = src_dir.join("grammar.json");
    let grammar_json = fs::read_to_string(&grammar_json_path).map_err(Error::wrap(|| {
        format!("Failed to read grammar file {:?}", grammar_json_path)
    }))?;
    let grammar: GrammarJSON = serde_json::from_str(&grammar_json).map_err(Error::wrap(|| {
        format!("Failed to parse grammar file {:?}", grammar_json_path)
    }))?;
    Ok(grammar.name)
}

pub fn compile_language_to_wasm(language_dir: &Path, force_docker: bool) -> Result<()> {
    let src_dir = language_dir.join("src");
    let grammar_name = get_grammar_name(&src_dir)?;
    let output_filename = format!("tree-sitter-{}.wasm", grammar_name);

    let mut command;
    if !force_docker && Command::new("emcc").output().is_ok() {
        command = Command::new("emcc");
        command.current_dir(&language_dir);
    } else if Command::new("docker").output().is_ok() {
        command = Command::new("docker");
        command.args(&["run", "--rm"]);

        // Mount the parser directory as a volume
        let mut volume_string;
        if let (Some(parent), Some(filename)) = (language_dir.parent(), language_dir.file_name()) {
            volume_string = OsString::from(parent);
            volume_string.push(":/src:Z");
            command.arg("--workdir");
            command.arg(&Path::new("/src").join(filename));
        } else {
            volume_string = OsString::from(language_dir);
            volume_string.push(":/src:Z");
            command.args(&["--workdir", "/src"]);
        }

        command.args(&[OsStr::new("--volume"), &volume_string]);

        // Get the current user id so that files created in the docker container will have
        // the same owner.
        if cfg!(unix) {
            let user_id_output = Command::new("id")
                .arg("-u")
                .output()
                .map_err(Error::wrap(|| "Failed to get get current user id"))?;
            let user_id = String::from_utf8_lossy(&user_id_output.stdout);
            let user_id = user_id.trim();
            command.args(&["--user", user_id]);
        }

        // Run `emcc` in a container using the `emscripten-slim` image
        command.args(&["trzeci/emscripten-slim", "emcc"]);
    } else {
        return Error::err("You must have either emcc or docker on your PATH to run this command".to_string());
    }

    command.args(&[
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
        "NODEJS_CATCH_EXIT=0",
        "-s",
        &format!("EXPORTED_FUNCTIONS=[\"_tree_sitter_{}\"]", grammar_name),
        "-fno-exceptions",
        "-I",
        "src",
    ]);

    // Find source files to pass to emscripten
    let src_entries = fs::read_dir(&src_dir).map_err(Error::wrap(|| {
        format!("Failed to read source directory {:?}", src_dir)
    }))?;

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
        .map_err(Error::wrap(|| "Failed to run emcc command"))?;
    if !output.status.success() {
        return Err(Error::from(format!(
            "emcc command failed - {}",
            String::from_utf8_lossy(&output.stderr)
        )));
    }

    // Move the created `.wasm` file into the current working directory.
    fs::rename(&language_dir.join(&output_filename), &output_filename).map_err(Error::wrap(
        || format!("Couldn't find output file {:?}", output_filename),
    ))?;

    Ok(())
}
