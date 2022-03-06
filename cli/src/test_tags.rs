use crate::query_testing::{parse_position_comments, Assertion};
use ansi_term::Colour;
use anyhow::{anyhow, Result};
use std::fs;
use std::path::Path;
use tree_sitter::Point;
use tree_sitter_loader::Loader;
use tree_sitter_tags::{TagsConfiguration, TagsContext};

#[derive(Debug)]
pub struct Failure {
    row: usize,
    column: usize,
    expected_tag: String,
    actual_tags: Vec<String>,
}

impl std::error::Error for Failure {}

impl std::fmt::Display for Failure {
    fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
        write!(
            f,
            "Failure - row: {}, column: {}, expected tag: '{}', actual tag: ",
            self.row, self.column, self.expected_tag
        )?;
        if self.actual_tags.is_empty() {
            write!(f, "none.")?;
        } else {
            for (i, actual_tag) in self.actual_tags.iter().enumerate() {
                if i > 0 {
                    write!(f, ", ")?;
                }
                write!(f, "'{}'", actual_tag)?;
            }
        }
        Ok(())
    }
}

pub fn test_tags(loader: &Loader, directory: &Path) -> Result<()> {
    let mut failed = false;
    let mut tags_context = TagsContext::new();

    println!("tags:");
    for tag_test_file in fs::read_dir(directory)? {
        let tag_test_file = tag_test_file?;
        let test_file_path = tag_test_file.path();
        let test_file_name = tag_test_file.file_name();
        let (language, language_config) = loader
            .language_configuration_for_file_name(&test_file_path)?
            .ok_or_else(|| anyhow!("No language found for path {:?}", test_file_path))?;
        let tags_config = language_config
            .tags_config(language)?
            .ok_or_else(|| anyhow!("No tags config found for {:?}", test_file_path))?;
        match test_tag(
            &mut tags_context,
            tags_config,
            fs::read(&test_file_path)?.as_slice(),
        ) {
            Ok(assertion_count) => {
                println!(
                    "  ✓ {} ({} assertions)",
                    Colour::Green.paint(test_file_name.to_string_lossy().as_ref()),
                    assertion_count
                );
            }
            Err(e) => {
                println!(
                    "  ✗ {}",
                    Colour::Red.paint(test_file_name.to_string_lossy().as_ref())
                );
                println!("    {}", e);
                failed = true;
            }
        }
    }

    if failed {
        Err(anyhow!(""))
    } else {
        Ok(())
    }
}

pub fn test_tag(
    tags_context: &mut TagsContext,
    tags_config: &TagsConfiguration,
    source: &[u8],
) -> Result<usize> {
    let tags = get_tag_positions(tags_context, tags_config, source)?;
    let assertions = parse_position_comments(tags_context.parser(), tags_config.language, source)?;

    // Iterate through all of the assertions, checking against the actual tags.
    let mut i = 0;
    let mut actual_tags = Vec::<&String>::new();
    for Assertion {
        position,
        expected_capture_name: expected_tag,
    } in &assertions
    {
        let mut passed = false;

        'tag_loop: loop {
            if let Some(tag) = tags.get(i) {
                if tag.1 <= *position {
                    i += 1;
                    continue;
                }

                // Iterate through all of the tags that start at or before this assertion's
                // position, looking for one that matches the assertion
                let mut j = i;
                while let (false, Some(tag)) = (passed, tags.get(j)) {
                    if tag.0 > *position {
                        break 'tag_loop;
                    }

                    let tag_name = &tag.2;
                    if *tag_name == *expected_tag {
                        passed = true;
                        break 'tag_loop;
                    } else {
                        actual_tags.push(tag_name);
                    }

                    j += 1;
                }
            } else {
                break;
            }
        }

        if !passed {
            return Err(Failure {
                row: position.row,
                column: position.column,
                expected_tag: expected_tag.clone(),
                actual_tags: actual_tags.into_iter().cloned().collect(),
            }
            .into());
        }
    }

    Ok(assertions.len())
}

pub fn get_tag_positions(
    tags_context: &mut TagsContext,
    tags_config: &TagsConfiguration,
    source: &[u8],
) -> Result<Vec<(Point, Point, String)>> {
    let (tags_iter, _has_error) = tags_context.generate_tags(&tags_config, &source, None)?;
    let tag_positions = tags_iter
        .filter_map(|t| t.ok())
        .map(|tag| {
            let tag_postfix = tags_config.syntax_type_name(tag.syntax_type_id).to_string();
            let tag_name = if tag.is_definition {
                format!("definition.{}", tag_postfix)
            } else {
                format!("reference.{}", tag_postfix)
            };
            (tag.span.start, tag.span.end, tag_name)
        })
        .collect();
    Ok(tag_positions)
}
