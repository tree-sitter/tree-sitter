use anyhow::Result;
use std::fs;
use std::path::Path;

/// Restores sourcesContent if it was stripped by Binaryen.
///
/// This is a workaround for Binaryen where `wasm-opt -O2` and higher
/// optimization levels strip the `sourcesContent` field from source maps,
/// even when the source map was generated with `--sources` flag.
///
/// This is fixed upstream in Binaryen as of Apr 9, 2025, but there hasn't been a release with the fix yet.
/// See: <https://github.com/WebAssembly/binaryen/issues/6805>
///
/// This reads the original source files and embeds them in the
/// source map's `sourcesContent` field, making debugging possible even
/// with optimized builds.
///
/// TODO: Once Binaryen releases a version with the fix, and emscripten updates to that
/// version, and we update our emscripten version, this function can be removed.
pub fn embed_sources_in_map(map_path: &Path) -> Result<()> {
    let map_content = fs::read_to_string(map_path)?;
    let mut map: serde_json::Value = serde_json::from_str(&map_content)?;

    if let Some(sources_content) = map.get("sourcesContent") {
        if let Some(arr) = sources_content.as_array() {
            if !arr.is_empty() && arr.iter().any(|v| !v.is_null()) {
                return Ok(());
            }
        }
    }

    let sources = map["sources"]
        .as_array()
        .ok_or_else(|| anyhow::anyhow!("No sources array in source map"))?;

    let map_dir = map_path.parent().unwrap_or(Path::new("."));
    let mut sources_content = Vec::new();

    for source in sources {
        let source_path = source.as_str().unwrap_or("");
        let full_path = map_dir.join(source_path);

        let content = if full_path.exists() {
            match fs::read_to_string(&full_path) {
                Ok(content) => serde_json::Value::String(content),
                Err(_) => serde_json::Value::Null,
            }
        } else {
            serde_json::Value::Null
        };

        sources_content.push(content);
    }

    map["sourcesContent"] = serde_json::Value::Array(sources_content);

    let output = serde_json::to_string(&map)?;
    fs::write(map_path, output)?;

    Ok(())
}
