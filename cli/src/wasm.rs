use super::generate::parse_grammar::GrammarJSON;
use anyhow::{Context, Result};
use std::{fs, path::Path};
use tree_sitter_loader::Loader;

pub fn load_language_wasm_file(language_dir: &Path) -> Result<(String, Vec<u8>)> {
    let grammar_name = get_grammar_name(&language_dir)
        .with_context(|| "Failed to get wasm filename")
        .unwrap();
    let wasm_filename = format!("tree-sitter-{}.wasm", grammar_name);
    let contents = fs::read(language_dir.join(&wasm_filename)).with_context(|| {
        format!(
            "Failed to read {}. Run `tree-sitter build-wasm` first.",
            wasm_filename
        )
    })?;
    Ok((grammar_name, contents))
}

pub fn get_grammar_name(language_dir: &Path) -> Result<String> {
    let src_dir = language_dir.join("src");
    let grammar_json_path = src_dir.join("grammar.json");
    let grammar_json = fs::read_to_string(&grammar_json_path)
        .with_context(|| format!("Failed to read grammar file {:?}", grammar_json_path))?;
    let grammar: GrammarJSON = serde_json::from_str(&grammar_json)
        .with_context(|| format!("Failed to parse grammar file {:?}", grammar_json_path))?;
    Ok(grammar.name)
}

pub fn compile_language_to_wasm(
    loader: &Loader,
    language_dir: &Path,
    output_dir: &Path,
    force_docker: bool,
) -> Result<()> {
    let grammar_name = get_grammar_name(&language_dir)?;
    let output_filename = output_dir.join(&format!("tree-sitter-{}.wasm", grammar_name));
    let src_path = language_dir.join("src");
    let scanner_path = loader.get_scanner_path(&src_path);
    loader.compile_parser_to_wasm(
        &grammar_name,
        &src_path,
        scanner_path
            .as_ref()
            .and_then(|p| Some(Path::new(p.file_name()?))),
        &output_filename,
        force_docker,
    )?;
    Ok(())
}
