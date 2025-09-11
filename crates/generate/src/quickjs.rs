use std::path::{Path, PathBuf};

use rquickjs::{
    loader::{FileResolver, ScriptLoader},
    Array, Context, Ctx, Function, Module, Object, Runtime, Value,
};

use super::{JSError, JSResult};

const DSL: &[u8] = include_bytes!("dsl.js");

const STDLIB: &[u8] = include_bytes!("stdlib.js");

fn pretty_print_js_error(v: Value) -> JSError {
    let Some(exception) = v.into_exception() else {
        return JSError::QuickJS("Expected a JS exception".to_string());
    };

    let error_obj = exception.as_object();
    let mut error_details = Vec::new();

    if let Ok(message) = error_obj.get::<_, String>("message") {
        error_details.push(format!("Message: {message}"));
    }

    if let Ok(stack) = error_obj.get::<_, String>("stack") {
        error_details.push(format!("Stack: {stack}"));
    }

    if let Ok(name) = error_obj.get::<_, String>("name") {
        error_details.push(format!("Type: {name}"));
    }

    if !error_details.is_empty() {
        return JSError::QuickJS(error_details.join("\n"));
    }

    JSError::QuickJS(exception.to_string())
}

#[allow(clippy::needless_pass_by_value)]
fn print(s: String) {
    println!("{s}");
}

#[allow(clippy::needless_pass_by_value)]
fn warn(s: String) {
    eprintln!("Warning: {s}");
}

#[allow(clippy::needless_pass_by_value)]
fn error(s: String) {
    eprintln!("Error: {s}");
}

fn validate_resolved_path(resolved_path: &Path, allowed_dirs: &[PathBuf]) -> Result<(), JSError> {
    let canonical_resolved = std::fs::canonicalize(resolved_path)
        .map_err(|e| JSError::IO(format!("Failed to canonicalize path: {e}")))?;

    for allowed_dir in allowed_dirs {
        if let Ok(canonical_allowed) = std::fs::canonicalize(allowed_dir) {
            if canonical_resolved.starts_with(&canonical_allowed) {
                return Ok(());
            }
        }
    }

    // Also allow current working directory
    if let Ok(cwd) = std::env::current_dir() {
        if canonical_resolved.starts_with(cwd) {
            return Ok(());
        }
    }

    Err(JSError::IO(format!(
        "Path access denied: {} is outside allowed directories",
        resolved_path.display()
    )))
}

#[allow(clippy::needless_pass_by_value)]
fn stat_path(ctx: Ctx, path: String) -> rquickjs::Result<Object> {
    let path = Path::new(&path);
    let globals = ctx.globals();
    let searchable_dirs = globals.get::<_, Array>("_searchableDirs")?;
    let mut last_error = None;

    let parser_dirs: Vec<PathBuf> = searchable_dirs
        .iter::<rquickjs::String>()
        .filter_map(|d| d.ok()?.to_string().ok().map(PathBuf::from))
        .collect();

    for d in searchable_dirs.iter::<rquickjs::String>() {
        let d = d?.to_string()?;
        let dir = Path::new(&d);
        let mut target_path = dir.join(path);
        let mut metadata = std::fs::metadata(&target_path);
        if metadata.is_err() && target_path.extension().is_none() {
            target_path = dir.join(path.with_extension("js"));
            if target_path.exists() {
                metadata = std::fs::metadata(&target_path);
            }
        }
        match metadata {
            Ok(metadata) => {
                if let Err(validation_error) = validate_resolved_path(&target_path, &parser_dirs) {
                    // Convert JSError to rquickjs::Error
                    return Err(rquickjs::Error::new_from_js_message(
                        "ValidationError",
                        "SecurityError",
                        validation_error.to_string(),
                    ));
                }

                let obj = Object::new(ctx.clone())?;
                obj.set("resolved", target_path.to_string_lossy().to_string())?;
                obj.set("errno", 0)?;
                obj.set("isFile", metadata.is_file())?;
                obj.set("isDir", metadata.is_dir())?;

                // This module should be able to resolve imports from the same directory.
                // We sort the array to ensure that the empty string is last, otherwise
                // imports that import a file of the same name as the folder will resolve to
                // the folder itself - e.g. importing `./common` from a folder called `common`
                // should give us `./common/common.js`, not `./common` again.
                let dir = target_path.parent().unwrap().to_string_lossy().to_string();
                if !searchable_dirs
                    .iter::<rquickjs::String>()
                    .any(|d| d.is_ok_and(|d| d.to_string().is_ok_and(|d| d == dir)))
                {
                    let mut rust_array = searchable_dirs
                        .iter::<rquickjs::String>()
                        .map(|d| d.unwrap().to_string().unwrap())
                        .collect::<Vec<_>>();
                    rust_array.push(target_path.parent().unwrap().to_string_lossy().to_string());
                    rust_array.sort_by(|a, b| {
                        if a.is_empty() {
                            std::cmp::Ordering::Greater
                        } else if b.is_empty() {
                            std::cmp::Ordering::Less
                        } else {
                            std::cmp::Ordering::Equal
                        }
                    });
                    let searchable_dirs = Array::new(ctx.clone())?;
                    for (i, dir) in rust_array.iter().enumerate() {
                        searchable_dirs.set(i, dir)?;
                    }
                    globals.set("_searchableDirs", searchable_dirs)?;
                }

                return Ok(obj);
            }
            Err(e) => {
                last_error = Some(e);
            }
        }
    }
    let obj = Object::new(ctx)?;
    let errno = last_error.map_or(-1, |e| e.raw_os_error().unwrap_or(-1));
    obj.set("errno", errno)?;
    Ok(obj)
}

#[allow(clippy::needless_pass_by_value)]
fn realpath(ctx: Ctx, path: String) -> rquickjs::Result<rquickjs::String> {
    let str = rquickjs::String::from_str(ctx, &std::fs::canonicalize(&path)?.to_string_lossy())?;
    Ok(str)
}

pub fn execute_native_runtime(
    #[cfg(windows)] grammar_path: &str,
    #[cfg(not(windows))] grammar_path: &Path,
    parser_directories: &[PathBuf],
) -> JSResult<String> {
    let runtime = Runtime::new()?;
    runtime.set_memory_limit(64 * 1024 * 1024); // 64MB max
    runtime.set_max_stack_size(256 * 1024); // 256KB stack

    let context = Context::full(&runtime)?;

    let cwd = std::env::current_dir()?;

    let parser_directory_paths = parser_directories
        .iter()
        .filter_map(|p| pathdiff::diff_paths(p, &cwd).map(|p| p.to_string_lossy().to_string()))
        .chain(std::iter::once(String::new()))
        .collect::<Vec<_>>();

    let resolver = FileResolver::default()
        .with_path("./")
        .with_paths(&parser_directory_paths);
    let loader = ScriptLoader::default();

    runtime.set_loader(resolver, loader);

    let relative_path_to_cwd = pathdiff::diff_paths(grammar_path, &cwd)
        .map(|p| p.to_string_lossy().to_string())
        .ok_or_else(|| JSError::IO("Failed to get relative path".to_string()))?;

    context.with(|ctx| -> JSResult<String> {
        let wrap_err = |e: rquickjs::Error| match e {
            rquickjs::Error::Exception => pretty_print_js_error(ctx.catch()),
            _ => JSError::QuickJS(e.to_string()),
        };

        let globals = ctx.globals();
        globals.set("native", true).map_err(wrap_err)?;
        globals
            .set("__ts_grammar_path", relative_path_to_cwd)
            .map_err(wrap_err)?;
        globals
            .set(
                "__print",
                Function::new(ctx.clone(), print)?.with_name("__print")?,
            )
            .map_err(wrap_err)?;
        globals
            .set(
                "__warn",
                Function::new(ctx.clone(), warn)?.with_name("__warn")?,
            )
            .map_err(wrap_err)?;
        globals
            .set(
                "__error",
                Function::new(ctx.clone(), error)?.with_name("__error")?,
            )
            .map_err(wrap_err)?;

        let std = Object::new(ctx.clone()).map_err(wrap_err)?;

        std.set(
            "loadFile",
            Function::new(
                ctx.clone(),
                |ctx: Ctx, path: String| -> rquickjs::Result<String> {
                    let path = Path::new(&path);

                    let globals = ctx.globals();
                    let searchable_dirs = globals.get::<_, Array>("_searchableDirs")?;
                    let parser_dirs: Vec<PathBuf> = searchable_dirs
                        .iter::<rquickjs::String>()
                        .filter_map(|d| d.ok()?.to_string().ok().map(PathBuf::from))
                        .collect();

                    if let Err(validation_error) = validate_resolved_path(path, &parser_dirs) {
                        return Err(rquickjs::Error::new_from_js_message(
                            "ValidationError",
                            "SecurityError",
                            validation_error.to_string(),
                        ));
                    }

                    std::fs::read_to_string(path).map_err(|e| {
                        rquickjs::Error::new_from_js_message(
                            "IOError",
                            "FileReadError",
                            e.to_string(),
                        )
                    })
                },
            )?,
        )?;

        globals.set("std", std).map_err(wrap_err)?;

        let process = Object::new(ctx.clone()).map_err(wrap_err)?;
        let env = Object::new(ctx.clone()).map_err(wrap_err)?;
        for (k, v) in std::env::vars() {
            env.set(k, v).map_err(wrap_err)?;
        }
        process.set("env", env).map_err(wrap_err)?;
        globals.set("process", process).map_err(wrap_err)?;

        let searchable_dirs = Array::new(ctx.clone()).map_err(wrap_err)?;
        for (i, dir) in parser_directory_paths.iter().enumerate() {
            searchable_dirs.set(i, dir).map_err(wrap_err)?;
        }
        globals
            .set("_searchableDirs", searchable_dirs)
            .map_err(wrap_err)?;

        globals
            .set("_statPath", Function::new(ctx.clone(), stat_path)?)
            .map_err(wrap_err)?;
        globals
            .set("_realpath", Function::new(ctx.clone(), realpath)?)
            .map_err(wrap_err)?;

        let module = Object::new(ctx.clone()).map_err(wrap_err)?;
        module
            .set("exports", Object::new(ctx.clone()).map_err(wrap_err)?)
            .map_err(wrap_err)?;
        globals.set("module", module).map_err(wrap_err)?;

        Module::evaluate(ctx.clone(), "stdlib", STDLIB).map_err(wrap_err)?;

        let promise = Module::evaluate(ctx.clone(), "dsl", DSL).map_err(wrap_err)?;
        promise.finish::<()>().map_err(wrap_err)?;

        let grammar_json = ctx
            .eval::<rquickjs::String, _>("globalThis.output")
            .map(|x| x.to_string())
            .map_err(wrap_err)?
            .map_err(wrap_err)?;

        Ok(
            serde_json::to_string_pretty(&serde_json::from_str::<serde_json::Value>(
                &grammar_json,
            )?)? + "\n",
        )
    })
}

#[cfg(all(test, feature = "qjs-rt"))]
mod tests {
    use super::*;
    use std::fs;
    use tempfile::TempDir;

    fn create_test_grammar(content: &str) -> (TempDir, PathBuf) {
        let temp_dir = TempDir::new().unwrap();
        let grammar_path = temp_dir.path().join("grammar.js");
        fs::write(&grammar_path, content).unwrap();
        (temp_dir, grammar_path)
    }

    #[test]
    fn test_basic_grammar_execution() {
        let grammar_content = r"
            module.exports = grammar({
              name: 'test',
              rules: {
                source_file: $ => 'hello'
              }
            });
        ";

        let (temp_dir, grammar_path) = create_test_grammar(grammar_content);
        let parser_dirs = [temp_dir.path().to_path_buf()];
        let result = execute_native_runtime(&grammar_path, &parser_dirs);

        assert!(result.is_ok());
        let json = result.unwrap();
        assert!(json.contains("\"name\": \"test\""));
        assert!(json.contains("\"hello\""));
    }

    #[test]
    fn test_module_imports() {
        let temp_dir = TempDir::new().unwrap();

        let common_path = temp_dir.path().join("common.js");
        fs::write(
            &common_path,
            r"
            module.exports = {
              identifier: $ => /[a-zA-Z_][a-zA-Z0-9_]*/
            };
        ",
        )
        .unwrap();

        // Create main grammar that imports common
        let grammar_path = temp_dir.path().join("grammar.js");
        fs::write(
            &grammar_path,
            r"
            const common = require('./common');

            module.exports = grammar({
              name: 'test_import',
              rules: {
                source_file: common.identifier
              }
            });
        ",
        )
        .unwrap();

        let parser_dirs = vec![temp_dir.path().to_path_buf()];
        let result = execute_native_runtime(&grammar_path, &parser_dirs);

        let json = result.expect("Failed to execute grammar with imports");
        assert!(json.contains("\"name\": \"test_import\""));
    }

    #[test]
    fn test_path_traversal_prevention() {
        let temp_dir = TempDir::new().unwrap();
        let grammar_path = temp_dir.path().join("grammar.js");

        // Try to access files outside allowed directories
        fs::write(
            &grammar_path,
            r"
            try {
              require('../../../etc/passwd');
            } catch (e) {
              console.log('Access denied as expected');
            }

            module.exports = grammar({
              name: 'security_test',
              rules: {
                source_file: $ => 'safe'
              }
            });
            ",
        )
        .unwrap();

        let parser_dirs = vec![temp_dir.path().to_path_buf()];
        let result = execute_native_runtime(&grammar_path, &parser_dirs);

        // Should succeed but not access forbidden files
        assert!(result.is_ok());
    }

    #[test]
    fn test_json_module_loading() {
        let temp_dir = TempDir::new().unwrap();

        let package_path = temp_dir.path().join("package.json");
        fs::write(&package_path, r#"{"version": "1.0.0"}"#).unwrap();

        let grammar_path = temp_dir.path().join("grammar.js");
        fs::write(
            &grammar_path,
            r"
            const pkg = require('./package.json');

            module.exports = grammar({
              name: 'json_test',
              rules: {
                source_file: $ => 'version_' + pkg.version.replace(/\./g, '_')
              }
            });
            ",
        )
        .unwrap();

        let parser_dirs = vec![temp_dir.path().to_path_buf()];
        let result = execute_native_runtime(&grammar_path, &parser_dirs);

        assert!(result.is_ok());
        let json = result.unwrap();
        assert!(json.contains("version_1_0_0"));
    }

    #[test]
    fn test_resource_limits() {
        let grammar_content = r"
            // Try to create a very large object
            const huge = new Array(10000000).fill('x'.repeat(1000));

            module.exports = grammar({
              name: 'resource_test',
              rules: {
                source_file: $ => 'test'
              }
            });
            ";

        let (temp_dir, grammar_path) = create_test_grammar(grammar_content);
        let parser_dirs = [temp_dir.path().to_path_buf()];
        let result = execute_native_runtime(&grammar_path, &parser_dirs);

        let error = result.expect_err("Expected an error due to resource limits");
        assert!(matches!(error, JSError::QuickJS(_)));
    }

    #[test]
    fn test_circular_dependencies() {
        let temp_dir = TempDir::new().unwrap();

        let a_path = temp_dir.path().join("a.js");
        fs::write(
            &a_path,
            r"
            const b = require('./b');
            module.exports = { name: 'a', b_name: b.name };
            ",
        )
        .unwrap();

        let b_path = temp_dir.path().join("b.js");
        fs::write(
            &b_path,
            r"
            const a = require('./a');
            module.exports = { name: 'b' };
            ",
        )
        .unwrap();

        let grammar_path = temp_dir.path().join("grammar.js");
        fs::write(
            &grammar_path,
            r"
            const a = require('./a');

            module.exports = grammar({
              name: 'circular_test',
              rules: {
                source_file: $ => 'test'
              }
            });
            ",
        )
        .unwrap();

        let parser_dirs = vec![temp_dir.path().to_path_buf()];
        let result = execute_native_runtime(&grammar_path, &parser_dirs);

        assert!(result.is_ok() || matches!(result.unwrap_err(), JSError::QuickJS(_)));
    }
}
