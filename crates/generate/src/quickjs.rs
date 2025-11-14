use std::{
    collections::HashMap,
    path::{Path, PathBuf},
    sync::{LazyLock, Mutex},
};

use log::{error, info, warn};
use rquickjs::{
    loader::{FileResolver, ScriptLoader},
    Context, Ctx, Function, Module, Object, Runtime, Type, Value,
};

use super::{IoError, JSError, JSResult};

const DSL: &[u8] = include_bytes!("dsl.js");

trait JSResultExt<T> {
    fn or_js_error(self, ctx: &Ctx) -> JSResult<T>;
}

impl<T> JSResultExt<T> for Result<T, rquickjs::Error> {
    fn or_js_error(self, ctx: &Ctx) -> JSResult<T> {
        match self {
            Ok(v) => Ok(v),
            Err(rquickjs::Error::Exception) => Err(format_js_exception(ctx.catch())),
            Err(e) => Err(JSError::QuickJS(e.to_string())),
        }
    }
}

fn format_js_exception(v: Value) -> JSError {
    let Some(exception) = v.into_exception() else {
        return JSError::QuickJS("Expected a JS exception".to_string());
    };

    let error_obj = exception.as_object();
    let mut parts = Vec::new();

    for (key, label) in [("message", "Message"), ("stack", "Stack"), ("name", "Type")] {
        if let Ok(value) = error_obj.get::<_, String>(key) {
            parts.push(format!("{label}: {value}"));
        }
    }

    if parts.is_empty() {
        JSError::QuickJS(exception.to_string())
    } else {
        JSError::QuickJS(parts.join("\n"))
    }
}

static FILE_CACHE: LazyLock<Mutex<HashMap<String, String>>> =
    LazyLock::new(|| Mutex::new(HashMap::new()));

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
                Type::Symbol
                | Type::Object
                | Type::Array
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
    #[qjs(constructor)]
    pub const fn new() -> Self {
        Console {}
    }

    #[allow(clippy::needless_pass_by_value)]
    pub fn log(&self, args: rquickjs::function::Rest<Value<'_>>) -> rquickjs::Result<()> {
        info!("{}", Self::format_args(&args));
        Ok(())
    }

    #[allow(clippy::needless_pass_by_value)]
    pub fn warn(&self, args: rquickjs::function::Rest<Value<'_>>) -> rquickjs::Result<()> {
        warn!("{}", Self::format_args(&args));
        Ok(())
    }

    #[allow(clippy::needless_pass_by_value)]
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

#[allow(clippy::needless_pass_by_value)]
fn require_from_module<'a>(
    ctx: Ctx<'a>,
    module_path: String,
    from_module: &str,
) -> rquickjs::Result<Value<'a>> {
    let current_module = PathBuf::from(from_module);
    let current_dir = if current_module.is_file() {
        current_module.parent().unwrap_or(Path::new("."))
    } else {
        current_module.as_path()
    };

    let resolved_path = resolve_module_path(current_dir, &module_path)?;

    let contents = load_file(resolved_path.to_string_lossy().to_string())?;

    load_module_from_content(&ctx, &resolved_path, &contents)
}

fn load_module_from_content<'a>(
    ctx: &Ctx<'a>,
    path: &Path,
    contents: &str,
) -> rquickjs::Result<Value<'a>> {
    if path.extension().is_some_and(|ext| ext == "json") {
        return ctx.eval::<Value, _>(format!("JSON.parse({contents:?})"));
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
        move |ctx_inner: Ctx<'a>, target_path: String| -> rquickjs::Result<Value<'a>> {
            require_from_module(ctx_inner, target_path, &module_path)
        },
    )?;

    let wrapper =
        format!("(function(exports, require, module, __filename, __dirname) {{ {contents} }})");

    let module_func = ctx.eval::<Function, _>(wrapper)?;
    module_func.call::<_, Value>((exports, require, module_obj.clone(), filename, dirname))?;

    module_obj.get("exports")
}

pub fn execute_native_runtime(grammar_path: &Path) -> JSResult<String> {
    let runtime = Runtime::new()?;

    runtime.set_memory_limit(64 * 1024 * 1024); // 64MB
    runtime.set_max_stack_size(256 * 1024); // 256KB

    let context = Context::full(&runtime)?;

    let resolver = FileResolver::default()
        .with_path("./node_modules")
        .with_path("./")
        .with_pattern("{}.mjs");
    let loader = ScriptLoader::default().with_extension("mjs");
    runtime.set_loader(resolver, loader);

    let cwd = std::env::current_dir().map_err(|e| JSError::IO(IoError::new(&e, None)))?;
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

        let promise = Module::evaluate(ctx.clone(), "dsl", DSL).or_js_error(&ctx)?;
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
        let _guard = TEST_MUTEX.get_or_init(|| Arc::new(Mutex::new(()))).lock();
        let result = test();
        cleanup_runtime_state();
        result
    }

    fn cleanup_runtime_state() {
        FILE_CACHE.lock().unwrap().clear();
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
                  rules: { source_file: $ => 'hello' }
                });
            ",
            )
            .unwrap();

            let json = execute_native_runtime(&grammar_path).expect("Failed to execute grammar");
            assert!(json.contains("\"name\": \"test\""));
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
