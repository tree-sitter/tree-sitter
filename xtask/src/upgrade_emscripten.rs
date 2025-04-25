use std::{fs, path::Path};

use anyhow::{anyhow, Result};
use git2::Repository;
use http_req::uri::Uri;
use serde_json::Value;

use crate::create_commit;

pub fn run() -> Result<()> {
    let uri = Uri::try_from("https://api.github.com/repos/emscripten-core/emsdk/tags")?;

    let mut body = Vec::new();
    let response = http_req::request::Request::new(&uri)
        .method(http_req::request::Method::GET)
        .header("User-Agent", "tree-sitter")
        .send(&mut body)?;

    if !response.status_code().is_success() {
        return Err(anyhow!("Failed to fetch emscripten tags"));
    }

    let response = String::from_utf8(body)?;
    let json = serde_json::from_str::<Value>(&response)?;
    let version = json
        .as_array()
        .and_then(|arr| arr.first())
        .and_then(|tag| tag["name"].as_str())
        .ok_or(anyhow!("No tags found"))?;

    let version_file = Path::new(env!("CARGO_MANIFEST_DIR"))
        .parent()
        .unwrap()
        .join("cli")
        .join("loader")
        .join("emscripten-version");

    fs::write(version_file, version)?;

    println!("Upgraded emscripten version to {version}");

    let repo = Repository::open(".")?;
    create_commit(
        &repo,
        &format!("build(deps): bump emscripten to {version}"),
        &["cli/loader/emscripten-version"],
    )?;

    Ok(())
}
