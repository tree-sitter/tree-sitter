use crate::error::Result;
use std::io;
use tree_sitter_tags::{TagsConfiguration, TagsContext};

pub fn generate_tags(config: &TagsConfiguration, source: &[u8]) -> Result<()> {
    let mut context = TagsContext::new();

    let stdout = io::stdout();
    let mut stdout = stdout.lock();

    for tag in context.generate_tags(config, source) {
        serde_json::to_writer(&mut stdout, &tag)?;
    }

    Ok(())
}
