use lazy_static::lazy_static;
use std::collections::BTreeMap;
use std::path::{Path, PathBuf};
use std::time::Instant;
use std::{env, fs, usize};
use tree_sitter::{Language, Parser};
use tree_sitter_cli::error::Error;
use tree_sitter_cli::loader::Loader;

include!("../src/tests/helpers/dirs.rs");

lazy_static! {
    static ref LANGUAGE_FILTER: Option<String> =
        env::var("TREE_SITTER_BENCHMARK_LANGUAGE_FILTER").ok();
    static ref EXAMPLE_FILTER: Option<String> =
        env::var("TREE_SITTER_BENCHMARK_EXAMPLE_FILTER").ok();
    static ref REPETITION_COUNT: usize = env::var("TREE_SITTER_BENCHMARK_REPETITION_COUNT")
        .map(|s| usize::from_str_radix(&s, 10).unwrap())
        .unwrap_or(5);

    static ref TEST_LOADER: Loader = Loader::new(SCRATCH_DIR.clone());
    static ref EXAMPLE_PATHS_BY_LANGUAGE_DIR: BTreeMap<PathBuf, Vec<PathBuf>> = {
        fn process_dir(result: &mut BTreeMap<PathBuf, Vec<PathBuf>>, dir: &Path) {
            if dir.join("grammar.js").exists() {
                let relative_path = dir.strip_prefix(GRAMMARS_DIR.as_path()).unwrap();
                if let Ok(example_files) = fs::read_dir(&dir.join("examples")) {
                    result.insert(
                        relative_path.to_owned(),
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
                    result.insert(relative_path.to_owned(), Vec::new());
                }
            } else {
                for entry in fs::read_dir(&dir).unwrap() {
                    let entry = entry.unwrap().path();
                    if entry.is_dir() {
                        process_dir(result, &entry);
                    }
                }
            }
        }

        let mut result = BTreeMap::new();
        process_dir(&mut result, &GRAMMARS_DIR);
        result
    };
}

fn main() {
    let mut parser = Parser::new();
    let max_path_length = EXAMPLE_PATHS_BY_LANGUAGE_DIR
        .iter()
        .flat_map(|(_, paths)| paths.iter())
        .map(|p| p.file_name().unwrap().to_str().unwrap().chars().count())
        .max()
        .unwrap();

    let mut all_normal_speeds = Vec::new();
    let mut all_error_speeds = Vec::new();

    eprintln!("Benchmarking with {} repetitions", *REPETITION_COUNT);

    for (language_path, example_paths) in EXAMPLE_PATHS_BY_LANGUAGE_DIR.iter() {
        let language_name = language_path.file_name().unwrap().to_str().unwrap();

        if let Some(filter) = LANGUAGE_FILTER.as_ref() {
            if language_name != filter.as_str() {
                continue;
            }
        }

        eprintln!("\nLanguage: {}", language_name);
        parser.set_language(get_language(language_path)).unwrap();

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
        for (other_language_path, example_paths) in EXAMPLE_PATHS_BY_LANGUAGE_DIR.iter() {
            if other_language_path != language_path {
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

    let source_code = fs::read(example_path)
        .map_err(Error::wrap(|| format!("Failed to read {:?}", example_path)))
        .unwrap();
    let time = Instant::now();
    for _ in 0..*REPETITION_COUNT {
        parser
            .parse(&source_code, None)
            .expect("Incompatible language version");
    }
    let duration = time.elapsed() / (*REPETITION_COUNT as u32);
    let duration_ms =
        duration.as_secs() as f64 * 1000.0 + duration.subsec_nanos() as f64 / 1000000.0;
    let speed = (source_code.len() as f64 / duration_ms) as usize;
    eprintln!("time {} ms\tspeed {} bytes/ms", duration_ms as usize, speed);
    speed
}

fn get_language(path: &Path) -> Language {
    let src_dir = GRAMMARS_DIR.join(path).join("src");
    TEST_LOADER
        .load_language_at_path(&src_dir, &src_dir)
        .map_err(Error::wrap(|| {
            format!("Failed to load language at path {:?}", src_dir)
        }))
        .unwrap()
}
