use super::helpers::fixtures::{get_highlight_config, get_language, get_language_queries_path};
use lazy_static::lazy_static;
use std::ffi::CString;
use std::os::raw::c_char;
use std::sync::atomic::{AtomicUsize, Ordering};
use std::{fs, ptr, slice, str};
use tree_sitter_highlight::{
    c, Error, Highlight, HighlightConfiguration, HighlightEvent, Highlighter, HtmlRenderer,
};

lazy_static! {
    static ref JS_HIGHLIGHT: HighlightConfiguration =
        get_highlight_config("javascript", Some("injections.scm"), &HIGHLIGHT_NAMES);
    static ref JSDOC_HIGHLIGHT: HighlightConfiguration =
        get_highlight_config("jsdoc", None, &HIGHLIGHT_NAMES);
    static ref HTML_HIGHLIGHT: HighlightConfiguration =
        get_highlight_config("html", Some("injections.scm"), &HIGHLIGHT_NAMES);
    static ref EJS_HIGHLIGHT: HighlightConfiguration = get_highlight_config(
        "embedded-template",
        Some("injections-ejs.scm"),
        &HIGHLIGHT_NAMES
    );
    static ref RUST_HIGHLIGHT: HighlightConfiguration =
        get_highlight_config("rust", Some("injections.scm"), &HIGHLIGHT_NAMES);
    static ref HIGHLIGHT_NAMES: Vec<String> = [
        "attribute",
        "carriage-return",
        "comment",
        "constant",
        "constructor",
        "function.builtin",
        "function",
        "embedded",
        "keyword",
        "operator",
        "property.builtin",
        "property",
        "punctuation",
        "punctuation.bracket",
        "punctuation.delimiter",
        "punctuation.special",
        "string",
        "tag",
        "type.builtin",
        "type",
        "variable.builtin",
        "variable.parameter",
        "variable",
    ]
    .iter()
    .cloned()
    .map(String::from)
    .collect();
    static ref HTML_ATTRS: Vec<String> = HIGHLIGHT_NAMES
        .iter()
        .map(|s| format!("class={}", s))
        .collect();
}

#[test]
fn test_highlighting_javascript() {
    let source = "const a = function(b) { return b + c; }";
    assert_eq!(
        &to_token_vector(&source, &JS_HIGHLIGHT).unwrap(),
        &[vec![
            ("const", vec!["keyword"]),
            (" ", vec![]),
            ("a", vec!["function"]),
            (" ", vec![]),
            ("=", vec!["operator"]),
            (" ", vec![]),
            ("function", vec!["keyword"]),
            ("(", vec!["punctuation.bracket"]),
            ("b", vec!["variable.parameter"]),
            (")", vec!["punctuation.bracket"]),
            (" ", vec![]),
            ("{", vec!["punctuation.bracket"]),
            (" ", vec![]),
            ("return", vec!["keyword"]),
            (" ", vec![]),
            ("b", vec!["variable.parameter"]),
            (" ", vec![]),
            ("+", vec!["operator"]),
            (" ", vec![]),
            ("c", vec!["variable"]),
            (";", vec!["punctuation.delimiter"]),
            (" ", vec![]),
            ("}", vec!["punctuation.bracket"]),
        ]]
    );
}

#[test]
fn test_highlighting_injected_html_in_javascript() {
    let source = vec!["const s = html `<div>${a < b}</div>`;"].join("\n");

    assert_eq!(
        &to_token_vector(&source, &JS_HIGHLIGHT).unwrap(),
        &[vec![
            ("const", vec!["keyword"]),
            (" ", vec![]),
            ("s", vec!["variable"]),
            (" ", vec![]),
            ("=", vec!["operator"]),
            (" ", vec![]),
            ("html", vec!["function"]),
            (" ", vec![]),
            ("`", vec!["string"]),
            ("<", vec!["string", "punctuation.bracket"]),
            ("div", vec!["string", "tag"]),
            (">", vec!["string", "punctuation.bracket"]),
            ("${", vec!["string", "embedded", "punctuation.special"]),
            ("a", vec!["string", "embedded", "variable"]),
            (" ", vec!["string", "embedded"]),
            ("<", vec!["string", "embedded", "operator"]),
            (" ", vec!["string", "embedded"]),
            ("b", vec!["string", "embedded", "variable"]),
            ("}", vec!["string", "embedded", "punctuation.special"]),
            ("</", vec!["string", "punctuation.bracket"]),
            ("div", vec!["string", "tag"]),
            (">", vec!["string", "punctuation.bracket"]),
            ("`", vec!["string"]),
            (";", vec!["punctuation.delimiter"]),
        ]]
    );
}

#[test]
fn test_highlighting_injected_javascript_in_html_mini() {
    let source = "<script>const x = new Thing();</script>";

    assert_eq!(
        &to_token_vector(source, &HTML_HIGHLIGHT).unwrap(),
        &[vec![
            ("<", vec!["punctuation.bracket"]),
            ("script", vec!["tag"]),
            (">", vec!["punctuation.bracket"]),
            ("const", vec!["keyword"]),
            (" ", vec![]),
            ("x", vec!["variable"]),
            (" ", vec![]),
            ("=", vec!["operator"]),
            (" ", vec![]),
            ("new", vec!["keyword"]),
            (" ", vec![]),
            ("Thing", vec!["constructor"]),
            ("(", vec!["punctuation.bracket"]),
            (")", vec!["punctuation.bracket"]),
            (";", vec!["punctuation.delimiter"]),
            ("</", vec!["punctuation.bracket"]),
            ("script", vec!["tag"]),
            (">", vec!["punctuation.bracket"]),
        ],]
    );
}

#[test]
fn test_highlighting_injected_javascript_in_html() {
    let source = vec![
        "<body>",
        "  <script>",
        "    const x = new Thing();",
        "  </script>",
        "</body>",
    ]
    .join("\n");

    assert_eq!(
        &to_token_vector(&source, &HTML_HIGHLIGHT).unwrap(),
        &[
            vec![
                ("<", vec!["punctuation.bracket"]),
                ("body", vec!["tag"]),
                (">", vec!["punctuation.bracket"]),
            ],
            vec![
                ("  ", vec![]),
                ("<", vec!["punctuation.bracket"]),
                ("script", vec!["tag"]),
                (">", vec!["punctuation.bracket"]),
            ],
            vec![
                ("    ", vec![]),
                ("const", vec!["keyword"]),
                (" ", vec![]),
                ("x", vec!["variable"]),
                (" ", vec![]),
                ("=", vec!["operator"]),
                (" ", vec![]),
                ("new", vec!["keyword"]),
                (" ", vec![]),
                ("Thing", vec!["constructor"]),
                ("(", vec!["punctuation.bracket"]),
                (")", vec!["punctuation.bracket"]),
                (";", vec!["punctuation.delimiter"]),
            ],
            vec![
                ("  ", vec![]),
                ("</", vec!["punctuation.bracket"]),
                ("script", vec!["tag"]),
                (">", vec!["punctuation.bracket"]),
            ],
            vec![
                ("</", vec!["punctuation.bracket"]),
                ("body", vec!["tag"]),
                (">", vec!["punctuation.bracket"]),
            ],
        ]
    );
}

#[test]
fn test_highlighting_multiline_nodes_to_html() {
    let source = vec![
        "const SOMETHING = `",
        "  one ${",
        "    two()",
        "  } three",
        "`",
        "",
    ]
    .join("\n");

    assert_eq!(
        &to_html(&source, &JS_HIGHLIGHT).unwrap(),
        &[
            "<span class=keyword>const</span> <span class=constant>SOMETHING</span> <span class=operator>=</span> <span class=string>`</span>\n".to_string(),
            "<span class=string>  one <span class=embedded><span class=punctuation.special>${</span></span></span>\n".to_string(),
            "<span class=string><span class=embedded>    <span class=function>two</span><span class=punctuation.bracket>(</span><span class=punctuation.bracket>)</span></span></span>\n".to_string(),
            "<span class=string><span class=embedded>  <span class=punctuation.special>}</span></span> three</span>\n".to_string(),
            "<span class=string>`</span>\n".to_string(),
        ]
    );
}

#[test]
fn test_highlighting_with_local_variable_tracking() {
    let source = vec![
        "module.exports = function a(b) {",
        "  const module = c;",
        "  console.log(module, b);",
        "}",
    ]
    .join("\n");

    assert_eq!(
        &to_token_vector(&source, &JS_HIGHLIGHT).unwrap(),
        &[
            vec![
                ("module", vec!["variable.builtin"]),
                (".", vec!["punctuation.delimiter"]),
                ("exports", vec!["function"]),
                (" ", vec![]),
                ("=", vec!["operator"]),
                (" ", vec![]),
                ("function", vec!["keyword"]),
                (" ", vec![]),
                ("a", vec!["function"]),
                ("(", vec!["punctuation.bracket"]),
                ("b", vec!["variable.parameter"]),
                (")", vec!["punctuation.bracket"]),
                (" ", vec![]),
                ("{", vec!["punctuation.bracket"])
            ],
            vec![
                ("  ", vec![]),
                ("const", vec!["keyword"]),
                (" ", vec![]),
                ("module", vec!["variable"]),
                (" ", vec![]),
                ("=", vec!["operator"]),
                (" ", vec![]),
                ("c", vec!["variable"]),
                (";", vec!["punctuation.delimiter"])
            ],
            vec![
                ("  ", vec![]),
                ("console", vec!["variable.builtin"]),
                (".", vec!["punctuation.delimiter"]),
                ("log", vec!["function"]),
                ("(", vec!["punctuation.bracket"]),
                // Not a builtin, because `module` was defined as a variable above.
                ("module", vec!["variable"]),
                (",", vec!["punctuation.delimiter"]),
                (" ", vec![]),
                // A parameter, because `b` was defined as a parameter above.
                ("b", vec!["variable.parameter"]),
                (")", vec!["punctuation.bracket"]),
                (";", vec!["punctuation.delimiter"]),
            ],
            vec![("}", vec!["punctuation.bracket"])]
        ],
    );
}

#[test]
fn test_highlighting_empty_lines() {
    let source = vec![
        "class A {",
        "",
        "  b(c) {",
        "",
        "    d(e)",
        "",
        "  }",
        "",
        "}",
    ]
    .join("\n");

    assert_eq!(
        &to_html(&source, &JS_HIGHLIGHT,).unwrap(),
        &[
            "<span class=keyword>class</span> <span class=constructor>A</span> <span class=punctuation.bracket>{</span>\n".to_string(),
            "\n".to_string(),
            "  <span class=function>b</span><span class=punctuation.bracket>(</span><span class=variable.parameter>c</span><span class=punctuation.bracket>)</span> <span class=punctuation.bracket>{</span>\n".to_string(),
            "\n".to_string(),
            "    <span class=function>d</span><span class=punctuation.bracket>(</span><span class=variable>e</span><span class=punctuation.bracket>)</span>\n".to_string(),
            "\n".to_string(),
            "  <span class=punctuation.bracket>}</span>\n".to_string(),
            "\n".to_string(),
            "<span class=punctuation.bracket>}</span>\n".to_string(),
        ]
    );
}

#[test]
fn test_highlighting_carriage_returns() {
    let source = "a = \"a\rb\"\r\nb\r";

    assert_eq!(
        &to_html(&source, &JS_HIGHLIGHT).unwrap(),
        &[
            "<span class=variable>a</span> <span class=operator>=</span> <span class=string>&quot;a<span class=carriage-return></span>b&quot;</span>\n",
            "<span class=variable>b</span>\n",
        ],
    );
}

#[test]
fn test_highlighting_ejs_with_html_and_javascript() {
    let source = vec!["<div><% foo() %></div><script> bar() </script>"].join("\n");

    assert_eq!(
        &to_token_vector(&source, &EJS_HIGHLIGHT).unwrap(),
        &[[
            ("<", vec!["punctuation.bracket"]),
            ("div", vec!["tag"]),
            (">", vec!["punctuation.bracket"]),
            ("<%", vec!["keyword"]),
            (" ", vec![]),
            ("foo", vec!["function"]),
            ("(", vec!["punctuation.bracket"]),
            (")", vec!["punctuation.bracket"]),
            (" ", vec![]),
            ("%>", vec!["keyword"]),
            ("</", vec!["punctuation.bracket"]),
            ("div", vec!["tag"]),
            (">", vec!["punctuation.bracket"]),
            ("<", vec!["punctuation.bracket"]),
            ("script", vec!["tag"]),
            (">", vec!["punctuation.bracket"]),
            (" ", vec![]),
            ("bar", vec!["function"]),
            ("(", vec!["punctuation.bracket"]),
            (")", vec!["punctuation.bracket"]),
            (" ", vec![]),
            ("</", vec!["punctuation.bracket"]),
            ("script", vec!["tag"]),
            (">", vec!["punctuation.bracket"]),
        ]],
    );
}

#[test]
fn test_highlighting_javascript_with_jsdoc() {
    // Regression test: the middle comment has no highlights. This should not prevent
    // later injections from highlighting properly.
    let source = vec!["a /* @see a */ b; /* nothing */ c; /* @see b */"].join("\n");

    assert_eq!(
        &to_token_vector(&source, &JS_HIGHLIGHT).unwrap(),
        &[[
            ("a", vec!["variable"]),
            (" ", vec![]),
            ("/* ", vec!["comment"]),
            ("@see", vec!["comment", "keyword"]),
            (" a */", vec!["comment"]),
            (" ", vec![]),
            ("b", vec!["variable"]),
            (";", vec!["punctuation.delimiter"]),
            (" ", vec![]),
            ("/* nothing */", vec!["comment"]),
            (" ", vec![]),
            ("c", vec!["variable"]),
            (";", vec!["punctuation.delimiter"]),
            (" ", vec![]),
            ("/* ", vec!["comment"]),
            ("@see", vec!["comment", "keyword"]),
            (" b */", vec!["comment"])
        ]],
    );
}

#[test]
fn test_highlighting_with_content_children_included() {
    let source = vec!["assert!(", "    a.b.c() < D::e::<F>()", ");"].join("\n");

    assert_eq!(
        &to_token_vector(&source, &RUST_HIGHLIGHT).unwrap(),
        &[
            vec![
                ("assert", vec!["function"]),
                ("!", vec!["function"]),
                ("(", vec!["punctuation.bracket"]),
            ],
            vec![
                ("    a", vec![]),
                (".", vec!["punctuation.delimiter"]),
                ("b", vec!["property"]),
                (".", vec!["punctuation.delimiter"]),
                ("c", vec!["function"]),
                ("(", vec!["punctuation.bracket"]),
                (")", vec!["punctuation.bracket"]),
                (" < ", vec![]),
                ("D", vec!["type"]),
                ("::", vec!["punctuation.delimiter"]),
                ("e", vec!["function"]),
                ("::", vec!["punctuation.delimiter"]),
                ("<", vec!["punctuation.bracket"]),
                ("F", vec!["type"]),
                (">", vec!["punctuation.bracket"]),
                ("(", vec!["punctuation.bracket"]),
                (")", vec!["punctuation.bracket"]),
            ],
            vec![
                (")", vec!["punctuation.bracket"]),
                (";", vec!["punctuation.delimiter"]),
            ]
        ],
    );
}

#[test]
fn test_highlighting_cancellation() {
    // An HTML document with a large injected JavaScript document:
    let mut source = "<script>\n".to_string();
    for _ in 0..500 {
        source += "function a() { console.log('hi'); }\n";
    }
    source += "</script>\n";

    // Cancel the highlighting before parsing the injected document.
    let cancellation_flag = AtomicUsize::new(0);
    let injection_callback = |name: &str| {
        cancellation_flag.store(1, Ordering::SeqCst);
        test_language_for_injection_string(name)
    };

    // The initial `highlight` call, which eagerly parses the outer document, should not fail.
    let mut highlighter = Highlighter::new();
    let events = highlighter
        .highlight(
            &HTML_HIGHLIGHT,
            source.as_bytes(),
            Some(&cancellation_flag),
            injection_callback,
        )
        .unwrap();

    // Iterating the scopes should not panic. It should return an error once the
    // cancellation is detected.
    for event in events {
        if let Err(e) = event {
            assert_eq!(e, Error::Cancelled);
            return;
        }
    }

    panic!("Expected an error while iterating highlighter");
}

#[test]
fn test_highlighting_via_c_api() {
    let highlights = vec![
        "class=tag\0",
        "class=function\0",
        "class=string\0",
        "class=keyword\0",
    ];
    let highlight_names = highlights
        .iter()
        .map(|h| h["class=".len()..].as_ptr() as *const c_char)
        .collect::<Vec<_>>();
    let highlight_attrs = highlights
        .iter()
        .map(|h| h.as_bytes().as_ptr() as *const c_char)
        .collect::<Vec<_>>();
    let highlighter = c::ts_highlighter_new(
        &highlight_names[0] as *const *const c_char,
        &highlight_attrs[0] as *const *const c_char,
        highlights.len() as u32,
    );

    let source_code = c_string("<script>\nconst a = b('c');\nc.d();\n</script>");

    let js_scope = c_string("source.js");
    let js_injection_regex = c_string("^javascript");
    let language = get_language("javascript");
    let queries = get_language_queries_path("javascript");
    let highlights_query = fs::read_to_string(queries.join("highlights.scm")).unwrap();
    let injections_query = fs::read_to_string(queries.join("injections.scm")).unwrap();
    let locals_query = fs::read_to_string(queries.join("locals.scm")).unwrap();
    c::ts_highlighter_add_language(
        highlighter,
        js_scope.as_ptr(),
        js_injection_regex.as_ptr(),
        language,
        highlights_query.as_ptr() as *const c_char,
        injections_query.as_ptr() as *const c_char,
        locals_query.as_ptr() as *const c_char,
        highlights_query.len() as u32,
        injections_query.len() as u32,
        locals_query.len() as u32,
    );

    let html_scope = c_string("text.html.basic");
    let html_injection_regex = c_string("^html");
    let language = get_language("html");
    let queries = get_language_queries_path("html");
    let highlights_query = fs::read_to_string(queries.join("highlights.scm")).unwrap();
    let injections_query = fs::read_to_string(queries.join("injections.scm")).unwrap();
    c::ts_highlighter_add_language(
        highlighter,
        html_scope.as_ptr(),
        html_injection_regex.as_ptr(),
        language,
        highlights_query.as_ptr() as *const c_char,
        injections_query.as_ptr() as *const c_char,
        ptr::null(),
        highlights_query.len() as u32,
        injections_query.len() as u32,
        0,
    );

    let buffer = c::ts_highlight_buffer_new();

    c::ts_highlighter_highlight(
        highlighter,
        html_scope.as_ptr(),
        source_code.as_ptr(),
        source_code.as_bytes().len() as u32,
        buffer,
        ptr::null_mut(),
    );

    let output_bytes = c::ts_highlight_buffer_content(buffer);
    let output_line_offsets = c::ts_highlight_buffer_line_offsets(buffer);
    let output_len = c::ts_highlight_buffer_len(buffer);
    let output_line_count = c::ts_highlight_buffer_line_count(buffer);

    let output_bytes = unsafe { slice::from_raw_parts(output_bytes, output_len as usize) };
    let output_line_offsets =
        unsafe { slice::from_raw_parts(output_line_offsets, output_line_count as usize) };

    let mut lines = Vec::new();
    for i in 0..(output_line_count as usize) {
        let line_start = output_line_offsets[i] as usize;
        let line_end = output_line_offsets
            .get(i + 1)
            .map(|x| *x as usize)
            .unwrap_or(output_bytes.len());
        lines.push(str::from_utf8(&output_bytes[line_start..line_end]).unwrap());
    }

    assert_eq!(
        lines,
        vec![
            "&lt;<span class=tag>script</span>&gt;\n",
            "<span class=keyword>const</span> a = <span class=function>b</span>(<span class=string>&#39;c&#39;</span>);\n",
            "c.<span class=function>d</span>();\n",
            "&lt;/<span class=tag>script</span>&gt;\n",
        ]
    );

    c::ts_highlighter_delete(highlighter);
    c::ts_highlight_buffer_delete(buffer);
}

#[test]
fn test_decode_utf8_lossy() {
    use tree_sitter::LossyUtf8;

    let parts = LossyUtf8::new(b"hi").collect::<Vec<_>>();
    assert_eq!(parts, vec!["hi"]);

    let parts = LossyUtf8::new(b"hi\xc0\xc1bye").collect::<Vec<_>>();
    assert_eq!(parts, vec!["hi", "\u{fffd}", "\u{fffd}", "bye"]);

    let parts = LossyUtf8::new(b"\xc0\xc1bye").collect::<Vec<_>>();
    assert_eq!(parts, vec!["\u{fffd}", "\u{fffd}", "bye"]);

    let parts = LossyUtf8::new(b"hello\xc0\xc1").collect::<Vec<_>>();
    assert_eq!(parts, vec!["hello", "\u{fffd}", "\u{fffd}"]);
}

fn c_string(s: &str) -> CString {
    CString::new(s.as_bytes().to_vec()).unwrap()
}

fn test_language_for_injection_string<'a>(string: &str) -> Option<&'a HighlightConfiguration> {
    match string {
        "javascript" => Some(&JS_HIGHLIGHT),
        "html" => Some(&HTML_HIGHLIGHT),
        "rust" => Some(&RUST_HIGHLIGHT),
        "jsdoc" => Some(&JSDOC_HIGHLIGHT),
        _ => None,
    }
}

fn to_html<'a>(
    src: &'a str,
    language_config: &'a HighlightConfiguration,
) -> Result<Vec<String>, Error> {
    let src = src.as_bytes();
    let mut renderer = HtmlRenderer::new();
    let mut highlighter = Highlighter::new();
    let events = highlighter.highlight(
        language_config,
        src,
        None,
        &test_language_for_injection_string,
    )?;

    renderer.set_carriage_return_highlight(
        HIGHLIGHT_NAMES
            .iter()
            .position(|s| s == "carriage-return")
            .map(Highlight),
    );
    renderer
        .render(events, src, &|highlight| HTML_ATTRS[highlight.0].as_bytes())
        .unwrap();
    Ok(renderer.lines().map(|s| s.to_string()).collect())
}

fn to_token_vector<'a>(
    src: &'a str,
    language_config: &'a HighlightConfiguration,
) -> Result<Vec<Vec<(&'a str, Vec<&'static str>)>>, Error> {
    let src = src.as_bytes();
    let mut highlighter = Highlighter::new();
    let mut lines = Vec::new();
    let mut highlights = Vec::new();
    let mut line = Vec::new();
    let events = highlighter.highlight(
        language_config,
        src,
        None,
        &test_language_for_injection_string,
    )?;
    for event in events {
        match event? {
            HighlightEvent::HighlightStart(s) => highlights.push(HIGHLIGHT_NAMES[s.0].as_str()),
            HighlightEvent::HighlightEnd => {
                highlights.pop();
            }
            HighlightEvent::Source { start, end } => {
                let s = str::from_utf8(&src[start..end]).unwrap();
                for (i, l) in s.split("\n").enumerate() {
                    let l = l.trim_end_matches('\r');
                    if i > 0 {
                        lines.push(line);
                        line = Vec::new();
                    }
                    if l.len() > 0 {
                        line.push((l, highlights.clone()));
                    }
                }
            }
        }
    }
    if line.len() > 0 {
        lines.push(line);
    }
    Ok(lines)
}
