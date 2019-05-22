#[macro_use]
extern crate criterion;

use criterion::{Criterion, Benchmark, Throughput};
use lazy_static::lazy_static;
use std::collections::BTreeMap;
use std::path::PathBuf;
use std::{env, fs};
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

fn get_language(name: &str) -> Language {
    let src_dir = GRAMMARS_DIR.join(name).join("src");
    TEST_LOADER
        .load_language_at_path(&src_dir, &src_dir)
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
        normal_inputs.push((example_file_str, fs::read(example_path).unwrap()));
    }
    normal_inputs
}

fn get_error_inputs(language_name: &String) -> Vec<(&str, Vec<u8>)> {
    let mut error_inputs = Vec::new();
    for (other_language_name, example_paths) in EXAMPLE_PATHS_BY_LANGUAGE_NAME.iter() {
        if other_language_name != language_name {
            for example_path in example_paths {
                let example_path_str = example_path.to_str().unwrap();
                let example_file_str = example_path.file_name().unwrap().to_str().unwrap();
                if let Some(filter) = EXAMPLE_FILTER.as_ref() {
                    if !example_path_str.contains(filter.as_str()) {
                        continue;
                    }
                }
                error_inputs.push((example_file_str, fs::read(example_path).unwrap()));
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
    for (language_name, example_paths) in EXAMPLE_PATHS_BY_LANGUAGE_NAME.iter() {
        if let Some(filter) = LANGUAGE_FILTER.as_ref() {
            if language_name != filter.as_str() {
                continue;
            }
        }
        let normal_inputs = get_normal_inputs(example_paths);
        for normal_input in normal_inputs {
            let mut parser = Parser::new();
            parser.set_language(get_language(language_name)).unwrap();
            let file_name = normal_input.0;
            let source_code = normal_input.1;
            let source_code_size = source_code.len();
            c.bench(&format!("language: {}", language_name),
                    Benchmark::new(format!("parse normal: {}", file_name),
                                   move |b| b.iter(|| parse(&mut parser, &source_code)),
                    ).throughput(Throughput::Bytes(source_code_size as u32))
            );
        }
        let error_inputs = get_error_inputs(language_name);
        for error_input in error_inputs {
            let mut parser = Parser::new();
            parser.set_language(get_language(language_name)).unwrap();
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

criterion_group!(benches, benchmark);
criterion_main!(benches);
