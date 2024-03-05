use crate::tests::helpers::fixtures::scratch_dir;

use std::path::Path;
use tree_sitter_loader::Loader;

#[test]
fn detect_language_by_first_line_regex() {
    let strace_dir = tree_sitter_dir(
        r#"{
  "name": "tree-sitter-strace",
  "version": "0.0.1",
  "tree-sitter": [
    {
      "scope": "source.strace",
      "file-types": [
        "strace"
      ],
      "first-line-regex":  "[0-9:.]* *execve"
    }
  ]
}
"#,
        "strace",
    );

    let mut loader = Loader::with_parser_lib_path(scratch_dir().to_path_buf());
    let config = loader
        .find_language_configurations_at_path(strace_dir.path(), false)
        .unwrap();

    // this is just to validate that we can read the package.json correctly
    assert_eq!(config[0].scope.as_ref().unwrap(), "source.strace");

    let file_name = strace_dir.path().join("strace.log");
    std::fs::write(&file_name, "execve\nworld").unwrap();
    assert_eq!(
        get_lang_scope(&loader, &file_name),
        Some("source.strace".into())
    );

    let file_name = strace_dir.path().join("strace.log");
    std::fs::write(&file_name, "447845 execve\nworld").unwrap();
    assert_eq!(
        get_lang_scope(&loader, &file_name),
        Some("source.strace".into())
    );

    let file_name = strace_dir.path().join("strace.log");
    std::fs::write(&file_name, "hello\nexecve").unwrap();
    assert!(get_lang_scope(&loader, &file_name).is_none());

    let file_name = strace_dir.path().join("strace.log");
    std::fs::write(&file_name, "").unwrap();
    assert!(get_lang_scope(&loader, &file_name).is_none());

    let dummy_dir = tree_sitter_dir(
        r#"{
  "name": "tree-sitter-dummy",
  "version": "0.0.1",
  "tree-sitter": [
    {
      "scope": "source.dummy",
      "file-types": [
        "dummy"
      ]
    }
  ]
}
"#,
        "dummy",
    );

    // file-type takes precedence over first-line-regex
    loader
        .find_language_configurations_at_path(dummy_dir.path(), false)
        .unwrap();
    let file_name = dummy_dir.path().join("strace.dummy");
    std::fs::write(&file_name, "execve").unwrap();
    assert_eq!(
        get_lang_scope(&loader, &file_name),
        Some("source.dummy".into())
    );
}

fn tree_sitter_dir(package_json: &str, name: &str) -> tempfile::TempDir {
    let temp_dir = tempfile::tempdir().unwrap();
    std::fs::write(temp_dir.path().join("package.json"), package_json).unwrap();
    std::fs::create_dir(temp_dir.path().join("src")).unwrap();
    std::fs::create_dir(temp_dir.path().join("src/tree_sitter")).unwrap();
    std::fs::write(
        temp_dir.path().join("src/grammar.json"),
        format!(r#"{{"name":"{name}"}}"#),
    )
    .unwrap();
    std::fs::write(
        temp_dir.path().join("src/parser.c"),
        format!(
            r##"
                #include "tree_sitter/parser.h"
                #ifdef _WIN32
                #define TS_PUBLIC __declspec(dllexport)
                #else
                #define TS_PUBLIC __attribute__((visibility("default")))
                #endif
                TS_PUBLIC const TSLanguage *tree_sitter_{name}() {{}}
            "##
        ),
    )
    .unwrap();
    std::fs::write(
        temp_dir.path().join("src/tree_sitter/parser.h"),
        include_str!("../../../lib/src/parser.h"),
    )
    .unwrap();
    temp_dir
}

// if we manage to get the language scope, it means we correctly detected the file-type
fn get_lang_scope(loader: &Loader, file_name: &Path) -> Option<String> {
    loader
        .language_configuration_for_file_name(file_name)
        .ok()
        .and_then(|config| {
            if let Some((_, config)) = config {
                config.scope.clone()
            } else if let Ok(Some((_, config))) =
                loader.language_configuration_for_first_line_regex(file_name)
            {
                config.scope.clone()
            } else {
                None
            }
        })
}
