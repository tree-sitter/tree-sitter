use super::error::{Error, Result};
use std::fs;
use std::io::{self, Write};
use std::path::Path;
use tree_sitter::{Language, Parser, Query, QueryCursor};

pub fn query_files_at_paths(
    language: Language,
    paths: Vec<&Path>,
    query_path: &Path,
) -> Result<()> {
    let stdout = io::stdout();
    let mut stdout = stdout.lock();

    let query_source = fs::read_to_string(query_path).map_err(Error::wrap(|| {
        format!("Error reading query file {:?}", query_path)
    }))?;
    let query = Query::new(language, &query_source)
        .map_err(|e| Error::new(format!("Query compilation failed: {:?}", e)))?;

    let mut query_cursor = QueryCursor::new();

    let mut parser = Parser::new();
    parser.set_language(language).map_err(|e| e.to_string())?;

    for path in paths {
        writeln!(&mut stdout, "{}", path.to_str().unwrap())?;

        let source_code = fs::read(path).map_err(Error::wrap(|| {
            format!("Error reading source file {:?}", path)
        }))?;

        let tree = parser.parse(&source_code, None).unwrap();

        for mat in query_cursor.exec(&query, tree.root_node()) {
            writeln!(&mut stdout, "  pattern: {}", mat.pattern_index())?;
            for (capture_id, node) in mat.captures() {
                writeln!(
                    &mut stdout,
                    "    {}: {:?}",
                    &query.capture_names()[capture_id],
                    node.utf8_text(&source_code).unwrap_or("")
                )?;
            }
        }
    }

    Ok(())
}
