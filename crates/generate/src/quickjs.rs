use std::{
    path::{Path, PathBuf},
    sync::{LazyLock, Mutex},
};

use log::{error, info, warn};
use rquickjs::{
    Context, Ctx, Function, Module, Object, Runtime, Type, Value,
    context::EvalOptions,
    loader::{FileResolver, ScriptLoader},
};
use rustc_hash::FxHashMap;

use super::{DSL, IoError, JSError, JSResult};

trait JSResultExt<T> {
    fn or_js_error(self, ctx: &Ctx) -> JSResult<T>;
}

impl<T> JSResultExt<T> for Result<T, rquickjs::Error> {
    fn or_js_error(self, ctx: &Ctx) -> JSResult<T> {
        match self {
            Ok(v) => Ok(v),
            Err(rquickjs::Error::Exception) => Err(format_js_exception(ctx.catch())),
            Err(e) => Err(JSError::QuickJS(e.to_string().into())),
        }
    }
}

fn format_js_exception(v: Value) -> JSError {
    let Some(exception) = v.into_exception() else {
        return JSError::QuickJS("Expected a JS exception".to_string().into());
    };

    let error_obj = exception.as_object();
    let name = error_obj
        .get::<_, String>("name")
        .unwrap_or_else(|_| "Error".to_string());
    let heading = match error_obj.get::<_, String>("message") {
        Ok(message) if message.is_empty() => name,
        Ok(message) => format!("{name}: {message}"),
        Err(_) => exception.to_string(),
    };
    let stack = error_obj.get::<_, String>("stack").unwrap_or_default();
    // QuickJS's own stacks contain frames only; the DSL's filtered diagnostics
    // already include a heading. Do not print their message a second time.
    let diagnostic = if stack.is_empty() {
        heading
    } else if stack.starts_with(&heading) {
        stack
    } else {
        format!("{heading}\n{stack}")
    };
    JSError::QuickJS(diagnostic.into())
}

static FILE_CACHE: LazyLock<Mutex<FxHashMap<String, String>>> =
    LazyLock::new(|| Mutex::new(FxHashMap::default()));

#[rquickjs::function]
fn load_file(path: String) -> rquickjs::Result<String> {
    {
        let cache = FILE_CACHE.lock().unwrap();
        if let Some(cached) = cache.get(&path) {
            return Ok(cached.clone());
        }
    }

    let content = std::fs::read_to_string(&path).map_err(|e| {
        rquickjs::Error::new_from_js_message("IOError", "FileReadError", e.to_string())
    })?;

    {
        let mut cache = FILE_CACHE.lock().unwrap();
        cache.insert(path, content.clone());
    }

    Ok(content)
}

#[rquickjs::class]
#[derive(rquickjs::class::Trace, rquickjs::JsLifetime, Default)]
pub struct Console {}

impl Console {
    fn format_args(args: &[Value<'_>]) -> String {
        args.iter()
            .map(|v| match v.type_of() {
                Type::Bool => v.as_bool().unwrap().to_string(),
                Type::Int => v.as_int().unwrap().to_string(),
                Type::Float => v.as_float().unwrap().to_string(),
                Type::String => v
                    .as_string()
                    .unwrap()
                    .to_string()
                    .unwrap_or_else(|_| String::new()),
                Type::Null => "null".to_string(),
                Type::Undefined => "undefined".to_string(),
                Type::Uninitialized => "uninitialized".to_string(),
                Type::Module => "module".to_string(),
                Type::BigInt => v.get::<String>().unwrap_or_else(|_| "BigInt".to_string()),
                Type::Unknown => "unknown".to_string(),
                Type::Array => {
                    let js_vals = v
                        .as_array()
                        .unwrap()
                        .iter::<Value<'_>>()
                        .filter_map(std::result::Result::ok)
                        .map(|x| {
                            if x.is_string() {
                                format!("'{}'", Self::format_args(&[x]))
                            } else {
                                Self::format_args(&[x])
                            }
                        })
                        .collect::<Vec<_>>()
                        .join(", ");

                    format!("[ {js_vals} ]")
                }
                Type::Symbol
                | Type::Object
                | Type::Proxy
                | Type::Function
                | Type::Constructor
                | Type::Promise
                | Type::Exception => "[object Object]".to_string(),
            })
            .collect::<Vec<_>>()
            .join(" ")
    }
}

#[rquickjs::methods]
impl Console {
    #[must_use]
    #[qjs(constructor)]
    pub const fn new() -> Self {
        Console {}
    }

    #[expect(
        clippy::needless_pass_by_value,
        clippy::unused_self,
        clippy::unnecessary_wraps,
        reason = "signature required by rquickjs"
    )]
    pub fn log(&self, args: rquickjs::function::Rest<Value<'_>>) -> rquickjs::Result<()> {
        info!("{}", Self::format_args(&args));
        Ok(())
    }

    #[expect(
        clippy::needless_pass_by_value,
        clippy::unused_self,
        clippy::unnecessary_wraps,
        reason = "signature required by rquickjs"
    )]
    pub fn warn(&self, args: rquickjs::function::Rest<Value<'_>>) -> rquickjs::Result<()> {
        warn!("{}", Self::format_args(&args));
        Ok(())
    }

    #[expect(
        clippy::needless_pass_by_value,
        clippy::unused_self,
        clippy::unnecessary_wraps,
        reason = "signature required by rquickjs"
    )]
    pub fn error(&self, args: rquickjs::function::Rest<Value<'_>>) -> rquickjs::Result<()> {
        error!("Error: {}", Self::format_args(&args));
        Ok(())
    }
}

fn resolve_module_path(base_path: &Path, module_path: &str) -> rquickjs::Result<PathBuf> {
    let candidates = if module_path.starts_with("./") || module_path.starts_with("../") {
        let target = base_path.join(module_path);
        vec![
            target.with_extension("js"),
            target.with_extension("json"),
            target.clone(),
        ]
    } else {
        let local_target = base_path.join(module_path);
        let node_modules_target = Path::new("node_modules").join(module_path);

        vec![
            local_target.with_extension("js"),
            local_target.with_extension("json"),
            local_target.clone(),
            node_modules_target.with_extension("js"),
            node_modules_target.with_extension("json"),
            node_modules_target,
        ]
    };

    for candidate in candidates {
        if let Ok(resolved) = try_resolve_path(&candidate) {
            return Ok(resolved);
        }
    }

    Err(rquickjs::Error::new_from_js_message(
        "Error",
        "ModuleNotFound",
        format!("Module not found: {module_path}"),
    ))
}

fn try_resolve_path(path: &Path) -> rquickjs::Result<PathBuf> {
    let metadata = std::fs::metadata(path).map_err(|_| {
        rquickjs::Error::new_from_js_message(
            "Error",
            "FileNotFound",
            format!("Path not found: {}", path.display()),
        )
    })?;

    if metadata.is_file() {
        return Ok(path.to_path_buf());
    }

    if metadata.is_dir() {
        let index_path = path.join("index.js");
        if index_path.exists() {
            return Ok(index_path);
        }
    }

    Err(rquickjs::Error::new_from_js_message(
        "Error",
        "ResolutionFailed",
        format!("Cannot resolve: {}", path.display()),
    ))
}

#[expect(
    clippy::needless_pass_by_value,
    reason = "signature required by rquickjs"
)]
fn require_from_module<'js>(
    ctx: Ctx<'js>,
    module_path: String,
    from_module: &str,
) -> rquickjs::Result<Value<'js>> {
    let current_module = PathBuf::from(from_module);
    let current_dir = if current_module.is_file() {
        current_module.parent().unwrap_or_else(|| Path::new("."))
    } else {
        current_module.as_path()
    };

    let resolved_path = resolve_module_path(current_dir, &module_path)?;

    let contents = load_file(resolved_path.to_string_lossy().to_string())?;

    load_module_from_content(&ctx, &resolved_path, &contents)
}

fn load_module_from_content<'js>(
    ctx: &Ctx<'js>,
    path: &Path,
    contents: &str,
) -> rquickjs::Result<Value<'js>> {
    if path.extension().is_some_and(|ext| ext == "json") {
        return ctx.eval::<Value<'js>, _>(format!("JSON.parse({contents:?})"));
    }

    let exports = Object::new(ctx.clone())?;
    let module_obj = Object::new(ctx.clone())?;
    module_obj.set("exports", exports.clone())?;

    let filename = path.to_string_lossy().to_string();
    let dirname = path
        .parent()
        .map_or_else(|| ".".to_string(), |p| p.to_string_lossy().to_string());

    // Require function specific to *this* module
    let module_path = filename.clone();
    let require = Function::new(
        ctx.clone(),
        move |ctx_inner: Ctx<'js>, target_path: String| -> rquickjs::Result<Value<'js>> {
            require_from_module(ctx_inner, target_path, &module_path)
        },
    )?;

    let wrapper =
        format!("(function(exports, require, module, __filename, __dirname) {{ {contents} }})");

    // Keep the wrapper on the first source line so module line numbers remain
    // unchanged, and give callbacks loaded by require() their original filename.
    let mut options = EvalOptions::default();
    options.filename = Some(filename.clone());
    let module_func = ctx.eval_with_options::<Function<'js>, _>(wrapper, options)?;
    module_func.call::<_, Value<'js>>((exports, require, module_obj.clone(), filename, dirname))?;

    module_obj.get("exports")
}

pub fn execute_native_runtime(grammar_path: &Path) -> JSResult<String> {
    let runtime = Runtime::new()?;

    runtime.set_memory_limit(64 * 1024 * 1024); // 64MB
    runtime.set_max_stack_size(256 * 1024); // 256KB

    let context = Context::full(&runtime)?;

    // Both defaults include `.js`; these additions also allow `.mjs` and `.cjs`.
    // Always parse imports as modules, regardless of extension. CommonJS
    // grammars use the global module/require shim below, while require() loads
    // dependencies in their own CommonJS wrapper. No source-text format
    // detection is needed, so comments and strings cannot affect loading.
    let resolver = FileResolver::default()
        .with_path("./node_modules")
        .with_path("./")
        .with_pattern("{}.mjs")
        .with_pattern("{}.cjs");
    let loader = ScriptLoader::default()
        .with_extension("mjs")
        .with_extension("cjs");
    runtime.set_loader(resolver, loader);

    let cwd = std::env::current_dir().map_err(|e| JSError::IO(IoError::new(e, None)))?;
    let relative_path = pathdiff::diff_paths(grammar_path, &cwd)
        .map(|p| p.to_string_lossy().to_string())
        .ok_or(JSError::RelativePath)?;

    context.with(|ctx| -> JSResult<String> {
        let globals = ctx.globals();

        globals.set("native", true).or_js_error(&ctx)?;
        globals
            .set("__ts_grammar_path", relative_path)
            .or_js_error(&ctx)?;

        let console = rquickjs::Class::instance(ctx.clone(), Console::new()).or_js_error(&ctx)?;
        globals.set("console", console).or_js_error(&ctx)?;

        let process = Object::new(ctx.clone()).or_js_error(&ctx)?;
        let env = Object::new(ctx.clone()).or_js_error(&ctx)?;
        for (key, value) in std::env::vars() {
            env.set(key, value).or_js_error(&ctx)?;
        }
        process.set("env", env).or_js_error(&ctx)?;
        globals.set("process", process).or_js_error(&ctx)?;

        let module = Object::new(ctx.clone()).or_js_error(&ctx)?;
        module
            .set("exports", Object::new(ctx.clone()).or_js_error(&ctx)?)
            .or_js_error(&ctx)?;
        globals.set("module", module).or_js_error(&ctx)?;

        let grammar_path_string = grammar_path.to_string_lossy().to_string();
        let main_require = Function::new(
            ctx.clone(),
            move |ctx_inner, target_path: String| -> rquickjs::Result<Value> {
                require_from_module(ctx_inner, target_path, &grammar_path_string)
            },
        )?;
        globals.set("require", main_require).or_js_error(&ctx)?;

        let promise =
            Module::evaluate(ctx.clone(), "tree-sitter:grammar-dsl", DSL).or_js_error(&ctx)?;
        promise.finish::<()>().or_js_error(&ctx)?;

        let grammar_json = ctx
            .eval::<rquickjs::String, _>("globalThis.output")
            .map(|s| s.to_string())
            .or_js_error(&ctx)?
            .or_js_error(&ctx)?;

        let parsed = serde_json::from_str::<serde_json::Value>(&grammar_json)?;
        Ok(serde_json::to_string_pretty(&parsed)?)
    })
}

#[cfg(test)]
mod tests {
    use std::{
        fs,
        sync::{Arc, Mutex, OnceLock},
    };
    use tempfile::TempDir;

    use super::*;

    static TEST_MUTEX: OnceLock<Arc<Mutex<()>>> = OnceLock::new();

    fn with_test_lock<F, R>(test: F) -> R
    where
        F: FnOnce() -> R,
    {
        let _guard = TEST_MUTEX
            .get_or_init(|| Arc::new(Mutex::new(())))
            .lock()
            .unwrap_or_else(std::sync::PoisonError::into_inner);
        struct RestoreWorkingDirectory(PathBuf);
        impl Drop for RestoreWorkingDirectory {
            fn drop(&mut self) {
                std::env::set_current_dir(&self.0).unwrap();
                cleanup_runtime_state();
            }
        }
        let _restore = RestoreWorkingDirectory(std::env::current_dir().unwrap());
        test()
    }

    fn cleanup_runtime_state() {
        FILE_CACHE.lock().unwrap().clear();
    }

    fn execute_fixture(files: &[(&str, &str)], entry: &str) -> serde_json::Value {
        let temp_dir = TempDir::new().unwrap();
        for (path, source) in files {
            let path = temp_dir.path().join(path);
            fs::create_dir_all(path.parent().unwrap()).unwrap();
            fs::write(path, source).unwrap();
        }
        let json = super::super::load_grammar_file(&temp_dir.path().join(entry), Some("native"))
            .expect("Failed to execute module grammar");
        serde_json::from_str(&json).unwrap()
    }

    fn fixture_error(files: &[(&str, &str)], entry: &str) -> String {
        let temp_dir = TempDir::new().unwrap();
        for (path, source) in files {
            let path = temp_dir.path().join(path);
            fs::create_dir_all(path.parent().unwrap()).unwrap();
            fs::write(path, source).unwrap();
        }
        let error = execute_native_runtime(&temp_dir.path().join(entry))
            .unwrap_err()
            .to_string();
        assert!(!error.contains("tree-sitter:grammar-dsl"), "{error}");
        error
    }

    #[test]
    fn test_nested_and_circular_error_diagnostics() {
        with_test_lock(|| {
            let error = fixture_error(
                &[(
                    "grammar.mjs",
                    r"
                    export const root = rule(() => {
                      const cause = new Error('original cause');
                      void cause.stack;
                      cause.message = 'changed cause';
                      cause.cause = cause;
                      throw new AggregateError(
                        [new Error('member failure')], 'build failed', {cause}
                      );
                    });
                    export default { name: 'test', start: root };
                    ",
                )],
                "grammar.mjs",
            );
            assert!(error.contains("Rule 'root': build failed"), "{error}");
            assert!(error.contains("changed cause"), "{error}");
            assert!(!error.contains("original cause"), "{error}");
            assert!(error.contains("member failure"), "{error}");
            assert!(error.contains("[Circular error]"), "{error}");
        });
    }

    #[test]
    fn test_unexported_handle_declaration_stack() {
        with_test_lock(|| {
            for helper in ["lib/dsl.js", "lib/dsl.mjs"] {
                let source = format!(
                    "import {{ privateRule }} from './{helper}';\n\
                     export const root = rule(() => privateRule());\n\
                     export default {{ name: 'test', start: root }};"
                );
                let error = fixture_error(
                    &[
                        (
                            helper,
                            "// The handle is not exported, only its accessor is.\n\
                             const hidden = rule(() => 'x');\n\
                             export const privateRule = () => hidden;",
                        ),
                        ("grammar.mjs", &source),
                    ],
                    "grammar.mjs",
                );
                assert!(error.contains("Rule 'root'"), "{error}");
                assert!(error.contains("Unregistered rule handle"), "{error}");
                assert!(error.contains(&format!("{helper}:2")), "{error}");
            }
        });
    }

    #[test]
    fn test_module_callback_error_keeps_user_frames() {
        with_test_lock(|| {
            for helper in ["lib/dsl.js", "lib/dsl.mjs"] {
                let source = format!(
                    "import {{ normalize }} from './{helper}';\n\
                     export const root = rule(() => normalize());\n\
                     export default {{ name: 'test', start: root }};"
                );
                let error = fixture_error(
                    &[
                        (
                            helper,
                            "export function normalize() {\n\
                             throw new Error('helper failure');\n\
                             }",
                        ),
                        ("grammar.mjs", &source),
                    ],
                    "grammar.mjs",
                );
                assert!(error.contains("helper failure"), "{error}");
                assert!(error.contains("normalize"), "{error}");
                assert!(error.contains(&format!("{helper}:2")), "{error}");
                assert!(error.contains("grammar.mjs:2"), "{error}");
            }
        });
    }

    #[test]
    fn test_module_initialization_error_stack() {
        with_test_lock(|| {
            for helper in ["lib/dsl.js", "lib/dsl.mjs"] {
                let source = format!("import './{helper}';");
                let error = fixture_error(
                    &[
                        (
                            helper,
                            "// initialization\nthrow new Error('initialization failure');",
                        ),
                        ("grammar.mjs", &source),
                    ],
                    "grammar.mjs",
                );
                assert!(error.contains("initialization failure"), "{error}");
                assert!(error.contains(&format!("{helper}:2")), "{error}");
            }
        });
    }

    #[test]
    fn test_legacy_callback_error_stack() {
        with_test_lock(|| {
            for (entry, export) in [
                ("grammar.js", "export default"),
                ("grammar.mjs", "export default"),
                ("grammar.cjs", "module.exports ="),
            ] {
                let source = format!(
                    "{export} grammar({{\n\
                     name: 'legacy',\n\
                     rules: {{ root: function normalize() {{ throw new Error('legacy failure'); }} }}\n\
                     }});"
                );
                let error = fixture_error(&[(entry, &source)], entry);
                assert!(error.contains("legacy failure"), "{error}");
                assert!(error.contains("normalize"), "{error}");
                assert!(error.contains(&format!("{entry}:3")), "{error}");
            }
        });
    }

    #[test]
    fn test_commonjs_helper_callback_error_stack() {
        with_test_lock(|| {
            let error = fixture_error(
                &[
                    (
                        "lib/dsl.js",
                        "exports.normalize = function normalize() {\n\
                         throw new Error('commonjs helper failure');\n\
                         };",
                    ),
                    (
                        "grammar.cjs",
                        "const { normalize } = require('./lib/dsl.js');\n\
                         module.exports = grammar({ name: 'test', rules: {\n\
                         root: () => normalize()\n\
                         }});",
                    ),
                ],
                "grammar.cjs",
            );
            assert!(error.contains("commonjs helper failure"), "{error}");
            assert!(error.contains("normalize"), "{error}");
            assert!(error.contains("lib/dsl.js:2"), "{error}");
            assert!(error.contains("grammar.cjs:3"), "{error}");
        });
    }

    #[test]
    fn test_callback_error_without_stack() {
        with_test_lock(|| {
            let error = fixture_error(
                &[(
                    "grammar.mjs",
                    "export const root = rule(() => {\n\
                     const error = new Error('no stack failure');\n\
                     Object.defineProperty(error, 'stack', { value: undefined });\n\
                     throw error;\n\
                     });\n\
                     export default { name: 'test', start: root };",
                )],
                "grammar.mjs",
            );
            assert!(error.contains("no stack failure"), "{error}");
        });
    }

    #[test]
    fn test_module_grammar_generates_parser() {
        with_test_lock(|| {
            let grammar = execute_fixture(
                &[(
                    "grammar.mjs",
                    r"
                    export const
                      identifier = rule(() => /[a-z]+/),
                      type_identifier = rule(),
                      grammar = rule(() => seq(alias(identifier, type_identifier), ';')),
                      source_file = rule(() => repeat(grammar));
                    export default { name: 'module_example', start: source_file };
                    ",
                )],
                "grammar.mjs",
            );
            let (name, parser) = super::super::generate_parser_for_grammar(
                &serde_json::to_string(&grammar).unwrap(),
                None,
                super::super::OptLevel::default(),
                &mut Vec::new(),
            )
            .expect("Module grammar must produce a valid parser");
            assert_eq!(name, "module_example");
            assert!(parser.contains("tree_sitter_module_example"));
        });
    }

    #[test]
    fn test_module_grammar_extensions_and_recursive_start() {
        with_test_lock(|| {
            for entry in ["grammar.js", "grammar.mjs"] {
                let grammar = execute_fixture(
                    &[(
                        entry,
                        r"
                        export const identifier = rule(() => /[a-z]+/);
                        export const expression = rule(() =>
                          choice(identifier, seq('(', source_file, ')')));
                        export const source_file = rule(() => repeat(expression));
                        export default { name: 'recursive', start: source_file };
                        ",
                    )],
                    entry,
                );
                assert_eq!(grammar["name"], "recursive");
                assert_eq!(
                    grammar["rules"].as_object().unwrap().keys().next().unwrap(),
                    "source_file"
                );
                assert_eq!(grammar["rules"]["source_file"]["type"], "REPEAT");
                assert_eq!(
                    grammar["rules"]["source_file"]["content"],
                    serde_json::json!({"type": "SYMBOL", "name": "expression"})
                );
                assert_eq!(
                    grammar["rules"]["expression"]["members"][1]["members"][1],
                    serde_json::json!({"type": "SYMBOL", "name": "source_file"})
                );
            }
        });
    }

    #[test]
    fn test_module_grammar_relative_helpers_and_base_override() {
        with_test_lock(|| {
            let grammar = execute_fixture(
                &[
                    (
                        "lib/helpers.js",
                        "export const commaSep = member => seq(member, repeat(seq(',', member)));",
                    ),
                    (
                        "lib/base.js",
                        r"
                        import { commaSep } from './helpers.js';
                        export const item = rule(() => 'base');
                        export const source_file = rule(() => commaSep(item));
                        export default { name: 'base', start: source_file };
                        ",
                    ),
                    (
                        "grammar.mjs",
                        r"
                        import * as base from './lib/base.js';
                        export const item = override(base.item, () => choice(base.item, 'child'));
                        export default { name: 'child', extends: base, start: base.source_file };
                        ",
                    ),
                ],
                "grammar.mjs",
            );
            assert_eq!(grammar["name"], "child");
            assert_eq!(
                grammar["rules"]["item"],
                serde_json::json!({
                    "type": "CHOICE",
                    "members": [
                        {"type": "SYMBOL", "name": "item"},
                        {"type": "STRING", "value": "child"}
                    ]
                })
            );
            assert_eq!(
                grammar["rules"]["source_file"]["members"][0],
                serde_json::json!({"type": "SYMBOL", "name": "item"})
            );
        });
    }

    #[test]
    fn test_module_grammar_external_handle() {
        with_test_lock(|| {
            let grammar = execute_fixture(
                &[(
                    "grammar.js",
                    r"
                    export const newline = external();
                    export const source_file = rule(() => repeat(newline));
                    export default {
                      name: 'with_external', start: source_file, externals: [newline]
                    };
                    ",
                )],
                "grammar.js",
            );
            assert_eq!(
                grammar["externals"],
                serde_json::json!([{"type": "SYMBOL", "name": "newline"}])
            );
            assert!(grammar["rules"].get("newline").is_none());
            assert_eq!(
                grammar["rules"]["source_file"]["content"],
                serde_json::json!({"type": "SYMBOL", "name": "newline"})
            );
        });
    }

    #[test]
    fn test_module_grammar_errors() {
        with_test_lock(|| {
            for (source, expected) in [
                (
                    "export const root = rule(() => 'x'); export default { name: 'test' };",
                    "Specify a start rule handle",
                ),
                (
                    "export const root = rule(() => {}); export default { name: 'test', start: root };",
                    "Rule 'root': Returned undefined",
                ),
                (
                    "export const root = rule(() => root()); export default { name: 'test', start: root };",
                    "Rule 'root':",
                ),
                (
                    "const privateRule = rule(() => 'x'); export const root = rule(() => privateRule); export default { name: 'test', start: root };",
                    "Rule 'root': Unregistered rule handle",
                ),
                (
                    "const helper = () => 'x'; export const root = rule(() => seq(helper)); export default { name: 'test', start: root };",
                    "Expected a rule handle or expression, not a function",
                ),
                (
                    "export const root = rule(() => optional('a', 'b')); export default { name: 'test', start: root };",
                    "only takes one rule argument",
                ),
                (
                    "export const helper = () => 'x'; export default { name: 'test', start: helper };",
                    "Export 'helper' is not a rule handle",
                ),
                (
                    "export const root = rule(() => 'x'); export { root as other }; export default { name: 'test', start: root };",
                    "Each symbol must have one name",
                ),
                (
                    "export const root = external(); export default { name: 'test', start: root, externals: [root] };",
                    "The start rule must have a body",
                ),
            ] {
                let temp_dir = TempDir::new().unwrap();
                let path = temp_dir.path().join("grammar.mjs");
                fs::write(&path, source).unwrap();
                let error = execute_native_runtime(&path).unwrap_err().to_string();
                assert!(error.contains(expected), "{source}\n{error}");
            }
        });
    }

    #[test]
    fn test_legacy_esm_grammar() {
        with_test_lock(|| {
            for entry in ["grammar.js", "grammar.mjs"] {
                let grammar = execute_fixture(
                    &[(
                        entry,
                        r"
                        export default grammar({
                          name: 'legacy_module',
                          rules: { source_file: $ => 'legacy' }
                        });
                        ",
                    )],
                    entry,
                );
                assert_eq!(grammar["name"], "legacy_module");
                assert_eq!(
                    grammar["rules"]["source_file"],
                    serde_json::json!({"type": "STRING", "value": "legacy"})
                );
            }
        });
    }

    #[test]
    fn test_legacy_cjs_grammar() {
        with_test_lock(|| {
            let grammar = execute_fixture(
                &[
                    (
                        "lib/helper.cjs",
                        "module.exports = require('./value.json').value;",
                    ),
                    ("lib/value.json", r#"{"value":"legacy"}"#),
                    (
                        "grammar.cjs",
                        r"
                        // export default is merely a comment, not format detection.
                        const misleading = 'import rule from somewhere';
                        const value = require('./lib/helper.cjs');
                        module.exports = grammar({
                          name: 'legacy_commonjs',
                          rules: { source_file: $ => value }
                        });
                        ",
                    ),
                ],
                "grammar.cjs",
            );
            assert_eq!(grammar["name"], "legacy_commonjs");
            assert_eq!(
                grammar["rules"]["source_file"],
                serde_json::json!({"type": "STRING", "value": "legacy"})
            );
        });
    }

    #[test]
    fn test_basic_grammar_execution() {
        with_test_lock(|| {
            let temp_dir = TempDir::new().unwrap();
            std::env::set_current_dir(temp_dir.path()).unwrap();

            let grammar_path = temp_dir.path().join("grammar.js");
            fs::write(
                &grammar_path,
                r"
                module.exports = grammar({
                  name: 'test',
                  word: $ => $.identifier,
                  rules: {
                    source_file: $ => $.identifier,
                    identifier: $ => 'hello'
                  }
                });
            ",
            )
            .unwrap();

            let json = execute_native_runtime(&grammar_path).expect("Failed to execute grammar");
            assert!(json.contains("\"name\": \"test\""));
            assert!(json.contains("\"word\": \"identifier\""));
            assert!(json.contains("\"hello\""));
        });
    }

    #[test]
    fn test_module_imports() {
        with_test_lock(|| {
            let temp_dir = TempDir::new().unwrap();
            std::env::set_current_dir(temp_dir.path()).unwrap();

            fs::write(
                temp_dir.path().join("common.js"),
                r"
                module.exports = { identifier: $ => /[a-zA-Z_][a-zA-Z0-9_]*/ };
            ",
            )
            .unwrap();

            fs::write(
                temp_dir.path().join("grammar.js"),
                r"
                const common = require('./common');
                module.exports = grammar({
                  name: 'test_import',
                  rules: { source_file: common.identifier }
                });
            ",
            )
            .unwrap();

            let json = execute_native_runtime(&temp_dir.path().join("grammar.js"))
                .expect("Failed to execute grammar with imports");
            assert!(json.contains("\"name\": \"test_import\""));
        });
    }

    #[test]
    fn test_json_module_loading() {
        with_test_lock(|| {
            let temp_dir = TempDir::new().unwrap();
            std::env::set_current_dir(temp_dir.path()).unwrap();

            fs::write(
                temp_dir.path().join("package.json"),
                r#"{"version": "1.0.0"}"#,
            )
            .unwrap();
            fs::write(
                temp_dir.path().join("grammar.js"),
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

            let json = execute_native_runtime(&temp_dir.path().join("grammar.js"))
                .expect("Failed to execute grammar with JSON import");
            assert!(json.contains("version_1_0_0"));
        });
    }

    #[test]
    fn test_resource_limits() {
        with_test_lock(|| {
            let temp_dir = TempDir::new().unwrap();
            std::env::set_current_dir(temp_dir.path()).unwrap();

            fs::write(
                temp_dir.path().join("grammar.js"),
                r"
                const huge = new Array(10000000).fill('x'.repeat(1000));
                module.exports = grammar({
                  name: 'resource_test',
                  rules: { source_file: $ => 'test' }
                });
            ",
            )
            .unwrap();

            let result = execute_native_runtime(&temp_dir.path().join("grammar.js"));
            assert!(result.is_err());
            assert!(matches!(result.unwrap_err(), JSError::QuickJS(_)));
        });
    }
}
