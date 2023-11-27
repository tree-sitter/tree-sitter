use anyhow::Context;
use lazy_static::lazy_static;
use std::collections::BTreeMap;
use std::path::{Path, PathBuf};
use std::time::Instant;
use std::{env, fs, str, usize};
use tree_sitter::{Language, Parser, Query};
use tree_sitter_loader::Loader;

include!("../src/tests/helpers/dirs.rs");

lazy_static! {
    static ref LANGUAGE_FILTER: Option<String> =
        env::var("TREE_SITTER_BENCHMARK_LANGUAGE_FILTER").ok();
    static ref EXAMPLE_FILTER: Option<String> =
        env::var("TREE_SITTER_BENCHMARK_EXAMPLE_FILTER").ok();
    static ref REPETITION_COUNT: usize = env::var("TREE_SITTER_BENCHMARK_REPETITION_COUNT")
        .map(|s| usize::from_str_radix(&s, 10).unwrap())
        .unwrap_or(5);
    static ref TEST_LOADER: Loader = Loader::with_parser_lib_path(SCRATCH_DIR.clone());
    static ref EXAMPLE_AND_QUERY_PATHS_BY_LANGUAGE_DIR: BTreeMap<PathBuf, (Vec<PathBuf>, Vec<PathBuf>)> = {
        fn process_dir(result: &mut BTreeMap<PathBuf, (Vec<PathBuf>, Vec<PathBuf>)>, dir: &Path) {
            if dir.join("grammar.js").exists() {
                let relative_path = dir.strip_prefix(GRAMMARS_DIR.as_path()).unwrap();
                let (example_paths, query_paths) =
                    result.entry(relative_path.to_owned()).or_default();

                if let Ok(example_files) = fs::read_dir(&dir.join("examples")) {
                    example_paths.extend(example_files.filter_map(|p| {
                        let p = p.unwrap().path();
                        if p.is_file() {
                            Some(p.to_owned())
                        } else {
                            None
                        }
                    }));
                }

                if let Ok(query_files) = fs::read_dir(&dir.join("queries")) {
                    query_paths.extend(query_files.filter_map(|p| {
                        let p = p.unwrap().path();
                        if p.is_file() {
                            Some(p.to_owned())
                        } else {
                            None
                        }
                    }));
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
    let max_path_length = EXAMPLE_AND_QUERY_PATHS_BY_LANGUAGE_DIR
        .values()
        .flat_map(|(e, q)| {
            e.iter()
                .chain(q.iter())
                .map(|s| s.file_name().unwrap().to_str().unwrap().len())
        })
        .max()
        .unwrap_or(0);

    eprintln!("Benchmarking with {} repetitions", *REPETITION_COUNT);

    let mut parser = Parser::new();
    let mut all_normal_speeds = Vec::new();
    let mut all_error_speeds = Vec::new();

    for (language_path, (example_paths, query_paths)) in
        EXAMPLE_AND_QUERY_PATHS_BY_LANGUAGE_DIR.iter()
    {
        let language_name = language_path.file_name().unwrap().to_str().unwrap();

        if let Some(filter) = LANGUAGE_FILTER.as_ref() {
            if language_name != filter.as_str() {
                continue;
            }
        }

        eprintln!("\nLanguage: {}", language_name);
        let language = get_language(language_path);
        parser.set_language(&language).unwrap();

        eprintln!("  Constructing Queries");
        for path in query_paths {
            if let Some(filter) = EXAMPLE_FILTER.as_ref() {
                if !path.to_str().unwrap().contains(filter.as_str()) {
                    continue;
                }
            }

            parse(&path, max_path_length, |source| {
                Query::new(&language, str::from_utf8(source).unwrap())
                    .with_context(|| format!("Query file path: {path:?}"))
                    .expect("Failed to parse query");
            });
        }

        eprintln!("  Parsing Valid Code:");
        let mut normal_speeds = Vec::new();
        for example_path in example_paths {
            if let Some(filter) = EXAMPLE_FILTER.as_ref() {
                if !example_path.to_str().unwrap().contains(filter.as_str()) {
                    continue;
                }
            }

            normal_speeds.push(parse(example_path, max_path_length, |code| {
                parser.parse(code, None).expect("Failed to parse");
            }));
        }

        eprintln!("  Parsing Invalid Code (mismatched languages):");
        let mut error_speeds = Vec::new();
        for (other_language_path, (example_paths, _)) in
            EXAMPLE_AND_QUERY_PATHS_BY_LANGUAGE_DIR.iter()
        {
            if other_language_path != language_path {
                for example_path in example_paths {
                    if let Some(filter) = EXAMPLE_FILTER.as_ref() {
                        if !example_path.to_str().unwrap().contains(filter.as_str()) {
                            continue;
                        }
                    }

                    error_speeds.push(parse(example_path, max_path_length, |code| {
                        parser.parse(code, None).expect("Failed to parse");
                    }));
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

    eprintln!("\n  Overall");
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

fn aggregate(speeds: &Vec<usize>) -> Option<(usize, usize)> {
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

fn parse(path: &Path, max_path_length: usize, mut action: impl FnMut(&[u8])) -> usize {
    eprint!(
        "    {:width$}\t",
        path.file_name().unwrap().to_str().unwrap(),
        width = max_path_length
    );

    let source_code = fs::read(path)
        .with_context(|| format!("Failed to read {:?}", path))
        .unwrap();
    let time = Instant::now();
    for _ in 0..*REPETITION_COUNT {
        action(&source_code);
    }
    let duration = time.elapsed() / (*REPETITION_COUNT as u32);
    let duration_ms = duration.as_millis();
    let speed = source_code.len() as u128 / (duration_ms + 1);
    eprintln!("time {} ms\tspeed {} bytes/ms", duration_ms as usize, speed);
    speed as usize
}

fn get_language(path: &Path) -> Language {
    let src_dir = GRAMMARS_DIR.join(path).join("src");
    TEST_LOADER
        .load_language_at_path(&src_dir, &src_dir)
        .with_context(|| format!("Failed to load language at path {:?}", src_dir))
        .unwrap()
}
