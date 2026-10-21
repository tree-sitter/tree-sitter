use std::{
    fs,
    path::{Path, PathBuf},
};

use anyhow::{Context, Result, anyhow, bail};
use tree_sitter::wasm_stdlib_symbols;
use tree_sitter_generate::{load_grammar_file, parse_grammar::GrammarJSON};
use tree_sitter_loader::Loader;

pub fn load_language_wasm_file(language_dir: &Path) -> Result<(String, Vec<u8>)> {
    let grammar_name = get_grammar_name(language_dir)
        .with_context(|| "Failed to get Wasm filename")
        .unwrap();
    let wasm_filename = format!("tree-sitter-{grammar_name}.wasm");
    let contents = fs::read(language_dir.join(&wasm_filename)).with_context(|| {
        format!("Failed to read {wasm_filename}. Run `tree-sitter build --wasm` first.")
    })?;
    Ok((grammar_name, contents))
}

pub fn get_grammar_name(language_dir: &Path) -> Result<String> {
    let src_dir = language_dir.join("src");
    let grammar_json_path = src_dir.join("grammar.json");
    let grammar_json = fs::read_to_string(&grammar_json_path).with_context(|| {
        format!(
            "Failed to read grammar file {}",
            grammar_json_path.display()
        )
    })?;
    let grammar: GrammarJSON = serde_json::from_str(&grammar_json).with_context(|| {
        format!(
            "Failed to parse grammar file {}",
            grammar_json_path.display()
        )
    })?;
    Ok(grammar.name)
}

pub fn compile_language_to_wasm(
    loader: &Loader,
    language_dir: &Path,
    output_dir: &Path,
    output_file: Option<PathBuf>,
) -> Result<()> {
    let grammar_name = get_grammar_name(language_dir)
        .or_else(|_| load_grammar_file(&language_dir.join("grammar.js"), None))?;
    let output_filename =
        output_file.unwrap_or_else(|| output_dir.join(format!("tree-sitter-{grammar_name}.wasm")));
    let src_path = language_dir.join("src");
    let scanner_path = loader.get_scanner_path(&src_path);
    loader.compile_parser_to_wasm(
        &grammar_name,
        &src_path,
        scanner_path
            .as_ref()
            .and_then(|p| Some(Path::new(p.file_name()?))),
        &output_filename,
    )?;

    // Exit with an error if the external scanner uses symbols from the
    // C or C++ standard libraries that aren't available to Wasm parsers.
    let stdlib_symbols = wasm_stdlib_symbols().collect::<Vec<_>>();
    let dylink_symbols = [
        "__indirect_function_table",
        "__memory_base",
        "__stack_pointer",
        "__table_base",
        "__table_base",
        "memory",
    ];
    let builtin_symbols = [
        "__assert_fail",
        "__cxa_atexit",
        "abort",
        "emscripten_notify_memory_growth",
        "tree_sitter_debug_message",
        "proc_exit",
    ];

    let wasm_bytes = fs::read(&output_filename)?;
    let missing_symbols = wasm_import_names(&wasm_bytes)
        .with_context(|| format!("Failed to read imports of {}", output_filename.display()))?
        .into_iter()
        .filter(|name| {
            !builtin_symbols.contains(name)
                && !stdlib_symbols.contains(name)
                && !dylink_symbols.contains(name)
        })
        .collect::<Vec<_>>();

    if !missing_symbols.is_empty() {
        Err(anyhow!(
            concat!(
                "This external scanner uses a symbol that isn't available to Wasm parsers.\n",
                "\n",
                "Missing symbols:\n",
                "    {}\n",
                "\n",
                "Available symbols:\n",
                "    {}",
            ),
            missing_symbols.join("\n    "),
            stdlib_symbols.join("\n    ")
        ))?;
    }

    Ok(())
}

fn wasm_import_names(mut bytes: &[u8]) -> Result<Vec<&str>> {
    const IMPORT_SECTION_ID: u8 = 2;

    fn take<'wasm>(bytes: &mut &'wasm [u8], len: usize) -> Result<&'wasm [u8]> {
        let Some((head, tail)) = bytes.split_at_checked(len) else {
            bail!("unexpected end of Wasm module");
        };
        *bytes = tail;
        Ok(head)
    }

    fn leb128(bytes: &mut &[u8]) -> Result<u64> {
        let mut value = 0;
        for shift in (0..64).step_by(7) {
            let byte = take(bytes, 1)?[0];
            value |= u64::from(byte & 0x7f) << shift;
            if byte & 0x80 == 0 {
                return Ok(value);
            }
        }
        bail!("malformed LEB128 integer in Wasm module")
    }

    fn skip_limits(bytes: &mut &[u8]) -> Result<()> {
        let flags = take(bytes, 1)?[0];
        leb128(bytes)?;
        if flags & 0x01 != 0 {
            leb128(bytes)?;
        }
        if flags & 0x08 != 0 {
            leb128(bytes)?;
        }
        Ok(())
    }

    if take(&mut bytes, 8)? != b"\0asm\x01\0\0\0" {
        bail!("not a Wasm module");
    }

    while !bytes.is_empty() {
        let section_id = take(&mut bytes, 1)?[0];
        let section_len = leb128(&mut bytes)? as usize;
        let mut section = take(&mut bytes, section_len)?;
        if section_id != IMPORT_SECTION_ID {
            continue;
        }

        let mut names = Vec::new();
        for _ in 0..leb128(&mut section)? {
            let module_len = leb128(&mut section)? as usize;
            take(&mut section, module_len)?;
            let name_len = leb128(&mut section)? as usize;
            names.push(str::from_utf8(take(&mut section, name_len)?)?);

            match take(&mut section, 1)?[0] {
                0x00 => {
                    leb128(&mut section)?;
                }
                0x01 => {
                    take(&mut section, 1)?;
                    skip_limits(&mut section)?;
                }
                0x02 => skip_limits(&mut section)?,
                0x03 => {
                    take(&mut section, 2)?;
                }
                0x04 => {
                    take(&mut section, 1)?;
                    leb128(&mut section)?;
                }
                kind => bail!("unsupported Wasm import kind {kind:#04x}"),
            }
        }
        return Ok(names);
    }

    Ok(Vec::new())
}
