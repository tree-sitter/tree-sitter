use super::loader::Loader;
use super::util;
use crate::error::{Error, Result};
use std::io::{self, Write};
use std::path::Path;
use std::{fs, str};
use tree_sitter_tags::TagsContext;

pub fn generate_tags(loader: &Loader, scope: Option<&str>, paths: &[String]) -> Result<()> {
    let mut lang = None;
    if let Some(scope) = scope {
        lang = loader.language_configuration_for_scope(scope)?;
        if lang.is_none() {
            return Error::err(format!("Unknown scope '{}'", scope));
        }
    }

    let mut context = TagsContext::new();
    let cancellation_flag = util::cancel_on_stdin();
    let stdout = io::stdout();
    let mut stdout = stdout.lock();

    for path in paths {
        let path = Path::new(&path);
        let (language, language_config) = match lang {
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
            let path_str = format!("{:?}", path);
            writeln!(&mut stdout, "{}", &path_str[1..path_str.len() - 1])?;

            let source = fs::read(path)?;
            for tag in context.generate_tags(tags_config, &source, Some(&cancellation_flag))? {
                let tag = tag?;
                write!(
                    &mut stdout,
                    "  {:<8} {:<40}\t{:>9}-{:<9}",
                    tag.kind,
                    str::from_utf8(&source[tag.name_range]).unwrap_or(""),
                    tag.span.start,
                    tag.span.end,
                )?;
                if let Some(docs) = tag.docs {
                    if docs.len() > 120 {
                        write!(&mut stdout, "\t{:?}...", &docs[0..120])?;
                    } else {
                        write!(&mut stdout, "\t{:?}", &docs)?;
                    }
                }
                writeln!(&mut stdout, "")?;
            }
        } else {
            eprintln!("No tags config found for path {:?}", path);
        }
    }

    Ok(())
}
