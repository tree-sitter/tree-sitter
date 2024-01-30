use super::util;
use anyhow::{anyhow, Result};
use std::io::{self, Write};
use std::path::Path;
use std::time::Instant;
use std::{fs, str};
use tree_sitter_loader::Loader;
use tree_sitter_tags::TagsContext;

pub fn generate_tags(
    loader: &Loader,
    scope: Option<&str>,
    paths: &[String],
    quiet: bool,
    time: bool,
) -> Result<()> {
    let mut lang = None;
    if let Some(scope) = scope {
        lang = loader.language_configuration_for_scope(scope)?;
        if lang.is_none() {
            return Err(anyhow!("Unknown scope '{}'", scope));
        }
    }

    let mut context = TagsContext::new();
    let cancellation_flag = util::cancel_on_signal();
    let stdout = io::stdout();
    let mut stdout = stdout.lock();

    for path in paths {
        let path = Path::new(&path);
        let (language, language_config) = match lang.clone() {
            Some(v) => v,
            None => match loader.language_configuration_for_file_name(path)? {
                Some(v) => v,
                None => {
                    eprintln!("No language found for path {:?}", path);
                    continue;
                }
            },
        };

        if let Some(tags_config) = language_config.tags_config(language)? {
            let indent;
            if paths.len() > 1 {
                if !quiet {
                    writeln!(&mut stdout, "{}", path.to_string_lossy())?;
                }
                indent = "\t"
            } else {
                indent = "";
            };

            let source = fs::read(path)?;
            let t0 = Instant::now();
            for tag in context
                .generate_tags(tags_config, &source, Some(&cancellation_flag))?
                .0
            {
                let tag = tag?;
                if !quiet {
                    write!(
                        &mut stdout,
                        "{}{:<10}\t | {:<8}\t{} {} - {} `{}`",
                        indent,
                        str::from_utf8(&source[tag.name_range]).unwrap_or(""),
                        &tags_config.syntax_type_name(tag.syntax_type_id),
                        if tag.is_definition { "def" } else { "ref" },
                        tag.span.start,
                        tag.span.end,
                        str::from_utf8(&source[tag.line_range]).unwrap_or(""),
                    )?;
                    if let Some(docs) = tag.docs {
                        if docs.len() > 120 {
                            write!(&mut stdout, "\t{:?}...", docs.get(0..120).unwrap_or(""))?;
                        } else {
                            write!(&mut stdout, "\t{:?}", &docs)?;
                        }
                    }
                    writeln!(&mut stdout, "")?;
                }
            }

            if time {
                writeln!(
                    &mut stdout,
                    "{}time: {}ms",
                    indent,
                    t0.elapsed().as_millis(),
                )?;
            }
        } else {
            eprintln!("No tags config found for path {:?}", path);
        }
    }

    Ok(())
}
