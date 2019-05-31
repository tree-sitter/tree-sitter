#[macro_use]
extern crate criterion;

use criterion::{Criterion, Benchmark, Throughput};
use lazy_static::lazy_static;
use std::collections::BTreeMap;
use std::path::{Path, PathBuf};
use std::time::Duration;
use std::{env, fs};
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

fn get_language(path: &Path) -> Language {
    let src_dir = GRAMMARS_DIR.join(path).join("src");
    TEST_LOADER
        .load_language_at_path(&src_dir, &src_dir)
        .map_err(Error::wrap(|| {
            format!("Failed to load language at path {:?}", src_dir)
        }))
        .unwrap()
}

fn get_normal_inputs(example_paths: &Vec<PathBuf>) -> Vec<(&str, Vec<u8>)> {
    let mut normal_inputs = Vec::new();
    for example_path in example_paths {
        let example_path_str = example_path.to_str().unwrap();
        let example_file_str = example_path.file_name().unwrap().to_str().unwrap();
        if let Some(filter) = EXAMPLE_FILTER.as_ref() {
            if !example_path_str.contains(filter.as_str()) {
                continue;
            }
        }
        let source_code = fs::read(example_path)
            .map_err(Error::wrap(|| format!("Failed to read {:?}", example_path)))
            .unwrap();
        normal_inputs.push((example_file_str, source_code));
    }
    normal_inputs
}

fn get_error_inputs(language_path: &Path) -> Vec<(&str, Vec<u8>)> {
    let mut error_inputs = Vec::new();
    for (other_language_path, example_paths) in EXAMPLE_PATHS_BY_LANGUAGE_DIR.iter() {
        if other_language_path != language_path {
            for example_path in example_paths {
                let example_path_str = example_path.to_str().unwrap();
                let example_file_str = example_path.file_name().unwrap().to_str().unwrap();
                if let Some(filter) = EXAMPLE_FILTER.as_ref() {
                    if !example_path_str.contains(filter.as_str()) {
                        continue;
                    }
                }
                let source_code = fs::read(example_path)
                    .map_err(Error::wrap(|| format!("Failed to read {:?}", example_path)))
                    .unwrap();
                error_inputs.push((example_file_str, source_code));
            }
        }
    }
    error_inputs
}

fn parse(parser: &mut Parser, source_code: &Vec<u8>) {
    let _tree = parser
        .parse(&source_code, None)
        .expect("Incompatible language version");
}

fn benchmark(c: &mut Criterion) {
    for (language_path, example_paths) in EXAMPLE_PATHS_BY_LANGUAGE_DIR.iter() {
        let language_name = language_path.file_name().unwrap().to_str().unwrap();

        if let Some(filter) = LANGUAGE_FILTER.as_ref() {
            if language_name != filter.as_str() {
                continue;
            }
        }

        let normal_inputs = get_normal_inputs(example_paths);
        for normal_input in normal_inputs {
            let mut parser = Parser::new();
            parser.set_language(get_language(language_path)).unwrap();
            let file_name = normal_input.0;
            let source_code = normal_input.1;
            let source_code_size = source_code.len();
            c.bench(&format!("language: {}", language_name),
                    Benchmark::new(format!("parse normal: {}", file_name),
                                   move |b| b.iter(|| parse(&mut parser, &source_code)),
                    ).throughput(Throughput::Bytes(source_code_size as u32))
            );
        }

        let error_inputs = get_error_inputs(language_path);
        for error_input in error_inputs {
            let mut parser = Parser::new();
            parser.set_language(get_language(language_path)).unwrap();
            let file_name = error_input.0;
            let source_code = error_input.1;
            let source_code_size = source_code.len();
            c.bench(&format!("language: {}", language_name),
                    Benchmark::new(format!("parse error: {}", file_name),
                                   move |b| b.iter(|| parse(&mut parser, &source_code)),
                    ).throughput(Throughput::Bytes(source_code_size as u32))
            );
        }
    }
}

fn benchmark_config() -> Criterion {
    Criterion::default()
        .warm_up_time(Duration::from_millis(500))
        .measurement_time(Duration::from_millis(1000))
        .sample_size(8)
        .nresamples(1000)
}

criterion_group!{
    name = benches;
    config = benchmark_config();
    targets = benchmark
}
criterion_main!(benches);
