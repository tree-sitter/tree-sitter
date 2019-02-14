use lazy_static::lazy_static;
use std::collections::BTreeMap;
use std::path::{Path, PathBuf};
use std::time::Instant;
use std::{env, fs, usize};
use tree_sitter::{Language, Parser};
use tree_sitter_cli::loader::Loader;

include!("../src/tests/helpers/dirs.rs");

lazy_static! {
    static ref LANGUAGE_FILTER: Option<String> =
        env::var("TREE_SITTER_BENCHMARK_LANGUAGE_FILTER").ok();
    static ref EXAMPLE_FILTER: Option<String> =
        env::var("TREE_SITTER_BENCHMARK_EXAMPLE_FILTER").ok();
    static ref TEST_LOADER: Loader = Loader::new(SCRATCH_DIR.clone());
    static ref EXAMPLE_PATHS_BY_LANGUAGE_NAME: BTreeMap<String, Vec<PathBuf>> = {
        let mut result = BTreeMap::new();
        let grammar_dirs = fs::read_dir(&(*GRAMMARS_DIR)).unwrap();
        for grammar_dir in grammar_dirs {
            let grammar_dir = grammar_dir.unwrap();
            if !grammar_dir.path().is_dir() {
                continue;
            }

            let language_name = grammar_dir.file_name();
            let language_name = language_name.to_str().unwrap();
            if let Ok(example_files) = fs::read_dir(&grammar_dir.path().join("examples")) {
                result.insert(
                    language_name.to_string(),
                    example_files
                        .filter_map(|p| {
                            let p = p.unwrap().path();
                            if p.is_file() {
                                Some(p)
                            } else {
                                None
                            }
                        })
                        .collect(),
                );
            } else {
                result.insert(language_name.to_string(), Vec::new());
            }
        }

        result
    };
}

fn main() {
    let mut parser = Parser::new();
    let max_path_length = EXAMPLE_PATHS_BY_LANGUAGE_NAME
        .iter()
        .flat_map(|(_, paths)| paths.iter())
        .map(|p| p.file_name().unwrap().to_str().unwrap().chars().count())
        .max()
        .unwrap();

    let mut all_normal_speeds = Vec::new();
    let mut all_error_speeds = Vec::new();

    for (language_name, example_paths) in EXAMPLE_PATHS_BY_LANGUAGE_NAME.iter() {
        // TODO - remove after fixing slow error parsing HTML.
        if language_name == "html" {
            continue;
        }

        if let Some(filter) = LANGUAGE_FILTER.as_ref() {
            if language_name != filter.as_str() {
                continue;
            }
        }

        eprintln!("\nLanguage: {}", language_name);
        parser.set_language(get_language(language_name)).unwrap();

        eprintln!("  Normal examples:");
        let mut normal_speeds = Vec::new();
        for example_path in example_paths {
            if let Some(filter) = EXAMPLE_FILTER.as_ref() {
                if !example_path.to_str().unwrap().contains(filter.as_str()) {
                    continue;
                }
            }

            normal_speeds.push(parse(&mut parser, example_path, max_path_length));
        }

        eprintln!("  Error examples (mismatched languages):");
        let mut error_speeds = Vec::new();
        for (other_language_name, example_paths) in EXAMPLE_PATHS_BY_LANGUAGE_NAME.iter() {
            if other_language_name != language_name {
                for example_path in example_paths {
                    if let Some(filter) = EXAMPLE_FILTER.as_ref() {
                        if !example_path.to_str().unwrap().contains(filter.as_str()) {
                            continue;
                        }
                    }

                    error_speeds.push(parse(&mut parser, example_path, max_path_length));
                }
            }
        }

        if let Some((average_normal, worst_normal)) = aggregate(&normal_speeds) {
            eprintln!("  Average Speed (normal): {} bytes/ms", average_normal);
            eprintln!("  Worst Speed (normal):   {} bytes/ms", worst_normal);
        }

        if let Some((average_error, worst_error)) = aggregate(&error_speeds) {
            eprintln!("  Average Speed (errors): {} bytes/ms", average_error);
            eprintln!("  Worst Speed (errors):   {} bytes/ms", worst_error);
        }

        all_normal_speeds.extend(normal_speeds);
        all_error_speeds.extend(error_speeds);
    }

    eprintln!("\nOverall");
    if let Some((average_normal, worst_normal)) = aggregate(&all_normal_speeds) {
        eprintln!("  Average Speed (normal): {} bytes/ms", average_normal);
        eprintln!("  Worst Speed (normal):   {} bytes/ms", worst_normal);
    }

    if let Some((average_error, worst_error)) = aggregate(&all_error_speeds) {
        eprintln!("  Average Speed (errors): {} bytes/ms", average_error);
        eprintln!("  Worst Speed (errors):   {} bytes/ms", worst_error);
    }
    eprintln!("");
}

fn aggregate(speeds: &Vec<(usize)>) -> Option<(usize, usize)> {
    if speeds.is_empty() {
        return None;
    }
    let mut total = 0;
    let mut max = usize::MAX;
    for speed in speeds.iter().cloned() {
        total += speed;
        if speed < max {
            max = speed;
        }
    }
    Some((total / speeds.len(), max))
}

fn parse(parser: &mut Parser, example_path: &Path, max_path_length: usize) -> usize {
    eprint!(
        "    {:width$}\t",
        example_path.file_name().unwrap().to_str().unwrap(),
        width = max_path_length
    );

    let source_code = fs::read(example_path).unwrap();
    let time = Instant::now();
    let _tree = parser
        .parse(&source_code, None)
        .expect("Incompatible language version");
    let duration = time.elapsed();
    let duration_ms =
        duration.as_secs() as f64 * 1000.0 + duration.subsec_nanos() as f64 / 1000000.0;
    let speed = (source_code.len() as f64 / duration_ms) as usize;
    eprintln!("time {} ms\tspeed {} bytes/ms", duration_ms as usize, speed);
    speed
}

fn get_language(name: &str) -> Language {
    TEST_LOADER
        .load_language_at_path(&GRAMMARS_DIR.join(name).join("src"), &HEADER_DIR)
        .unwrap()
}
