use std::{collections::BTreeSet, fmt::Write as _, path::Path, process::Command};

use anyhow::{Context, Result, anyhow, bail};
use serde_json::Value;

use crate::bail_on_err;

/// The rustdoc JSON schema this reader was written against.
const FORMAT_VERSION: u64 = 61;

/// The toolchain that emits [`FORMAT_VERSION`].
const TOOLCHAIN: &str = "nightly-2026-09-03";

/// The enums [`RegexErrorKind`] mirrors, by their public path upstream.
const UPSTREAM_ENUMS: [&[&str]; 2] = [
    &["regex_syntax", "ast", "ErrorKind"],
    &["regex_syntax", "hir", "ErrorKind"],
];

pub fn run() -> Result<()> {
    let target_dir = target_directory()?;

    let upstream_doc = rustdoc_json(&target_dir, "regex-syntax", "regex_syntax")?;
    let mut upstream = BTreeSet::new();
    for path in UPSTREAM_ENUMS {
        let id = find_enum(&upstream_doc, |p| p == path)
            .with_context(|| format!("no enum `{}` upstream", path.join("::")))?;
        upstream.extend(variant_names(&upstream_doc, &id)?);
    }

    let our_doc = rustdoc_json(&target_dir, "tree-sitter-generate", "tree_sitter_generate")?;
    let id = find_enum(&our_doc, |p| p.last() == Some(&"RegexErrorKind"))
        .context("no enum `RegexErrorKind` in `tree-sitter-generate`")?;
    let mut ours = variant_names(&our_doc, &id)?;

    if !ours.remove("Other") {
        bail!("`RegexErrorKind::Other` is gone, so unmirrored kinds no longer degrade");
    }

    // A reader that matches nothing would otherwise report two empty sets as
    // being in sync.
    if upstream.is_empty() || ours.is_empty() {
        bail!("read no variants, the rustdoc JSON reader is broken");
    }

    let missing = upstream.difference(&ours).copied().collect::<Vec<_>>();
    let extra = ours.difference(&upstream).copied().collect::<Vec<_>>();
    if missing.is_empty() && extra.is_empty() {
        return Ok(());
    }

    let mut message = String::from("`RegexErrorKind` no longer mirrors `regex_syntax`:\n");
    if !missing.is_empty() {
        write!(
            message,
            "\n  upstream kinds that degrade to `Other`, add them to the macro table:\n    {}\n",
            missing.join("\n    ")
        )?;
    }
    if !extra.is_empty() {
        write!(
            message,
            "\n  mirrored kinds upstream no longer has, drop them:\n    {}\n",
            extra.join("\n    ")
        )?;
    }
    Err(anyhow!(message))
}

/// The workspace's target directory, which is where `cargo rustdoc` writes.
fn target_directory() -> Result<String> {
    let output = Command::new("cargo")
        .args(["metadata", "--no-deps", "--format-version", "1"])
        .output()
        .context("Failed to run cargo metadata")?;
    bail_on_err(&output, "Failed to run cargo metadata")?;

    let metadata = serde_json::from_slice::<Value>(&output.stdout)?;
    metadata["target_directory"]
        .as_str()
        .map(ToOwned::to_owned)
        .context("cargo metadata reported no target directory")
}

/// Document `package` and read the rustdoc JSON it produces for `crate_name`.
fn rustdoc_json(target_dir: &str, package: &str, crate_name: &str) -> Result<Value> {
    let output = Command::new("cargo")
        .arg(format!("+{TOOLCHAIN}"))
        .args(["rustdoc", "--package", package, "--lib", "--"])
        .args(["-Zunstable-options", "--output-format", "json"])
        .output()
        .with_context(|| format!("Failed to run cargo rustdoc for `{package}`"))?;
    bail_on_err(&output, &format!("Failed to document `{package}`"))?;

    let path = Path::new(target_dir)
        .join("doc")
        .join(format!("{crate_name}.json"));
    let doc = serde_json::from_slice::<Value>(
        &std::fs::read(&path).with_context(|| format!("Failed to read {}", path.display()))?,
    )?;

    let version = doc["format_version"].as_u64();
    if version != Some(FORMAT_VERSION) {
        bail!(
            "rustdoc JSON is format version {}, this reader expects {FORMAT_VERSION}",
            version.map_or_else(|| "absent".to_owned(), |v| v.to_string())
        );
    }

    Ok(doc)
}

/// The id of an enum whose path satisfies `matches`.
///
/// Paths are where an item is defined rather than where it is re-exported from,
/// so matching on the trailing segment survives a move between modules.
fn find_enum(doc: &Value, matches: impl Fn(&[&str]) -> bool) -> Option<String> {
    doc["paths"].as_object()?.iter().find_map(|(id, item)| {
        let path = item["path"]
            .as_array()?
            .iter()
            .map(Value::as_str)
            .collect::<Option<Vec<_>>>()?;
        (item["kind"] == "enum" && matches(&path)).then(|| id.clone())
    })
}

fn variant_names<'a>(doc: &'a Value, id: &str) -> Result<BTreeSet<&'a str>> {
    let index = doc["index"]
        .as_object()
        .context("rustdoc JSON has no item index")?;
    // Items from other crates are listed in `paths` but carry no `index` entry.
    let variants = index
        .get(id)
        .map(|item| &item["inner"]["enum"]["variants"])
        .and_then(Value::as_array)
        .with_context(|| format!("item {id} is not a local enum"))?;

    variants
        .iter()
        .map(|variant| {
            // Variants are referenced by number but indexed by string.
            let key = match variant {
                Value::Number(id) => id.to_string(),
                Value::String(id) => id.clone(),
                _ => bail!("variant id {variant} is neither a number nor a string"),
            };
            index
                .get(&key)
                .and_then(|variant| variant["name"].as_str())
                .with_context(|| format!("no name for variant {key}"))
        })
        .collect()
}
