use std::path::PathBuf;

use anyhow::Result;
use serde_json::to_writer_pretty;

use tree_sitter_cli::test::TestSummary;

pub fn run_test_schema() -> Result<()> {
    let schema = schemars::schema_for!(TestSummary);

    let xtask_path: PathBuf = env!("CARGO_MANIFEST_DIR").into();
    let schema_path = xtask_path
        .parent()
        .unwrap()
        .parent()
        .unwrap()
        .join("docs")
        .join("src")
        .join("assets")
        .join("schemas")
        .join("test-summary.schema.json");
    let mut file = std::fs::File::create(schema_path)?;

    Ok(to_writer_pretty(&mut file, &schema)?)
}
