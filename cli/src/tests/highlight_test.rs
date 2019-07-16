use super::helpers::fixtures::{get_language, get_property_sheet, get_property_sheet_json};
use lazy_static::lazy_static;
use std::ffi::CString;

use std::sync::atomic::{AtomicUsize, Ordering};
use std::{ptr, slice, str};
use tree_sitter::{Language, PropertySheet};
use tree_sitter_highlight::{
    c, highlight, highlight_html, Error, Highlight, HighlightEvent, Properties,
};

lazy_static! {
    static ref JS_SHEET: PropertySheet<Properties> =
        get_property_sheet("javascript", "highlights.json");
    static ref HTML_SHEET: PropertySheet<Properties> =
        get_property_sheet("html", "highlights.json");
    static ref EJS_SHEET: PropertySheet<Properties> =
        get_property_sheet("embedded-template", "highlights-ejs.json");
    static ref RUST_SHEET: PropertySheet<Properties> =
        get_property_sheet("rust", "highlights.json");
    static ref SCOPE_CLASS_STRINGS: Vec<String> = {
        let mut result = Vec::new();
        let mut i = 0;
        while let Some(highlight) = Highlight::from_usize(i) {
            result.push(format!("class={:?}", highlight));
            i += 1;
        }
        result
    };
}

#[test]
fn test_highlighting_injected_html_in_javascript() {
    let source = vec!["const s = html `<div>${a < b}</div>`;"].join("\n");

    assert_eq!(
        &to_token_vector(&source, get_language("javascript"), &JS_SHEET).unwrap(),
        &[vec![
            ("const", vec![Highlight::Keyword]),
            (" ", vec![]),
            ("s", vec![Highlight::Variable]),
            (" ", vec![]),
            ("=", vec![Highlight::Operator]),
            (" ", vec![]),
            ("html", vec![Highlight::Function]),
            (" ", vec![]),
            ("`<", vec![Highlight::String]),
            ("div", vec![Highlight::String, Highlight::Tag]),
            (">", vec![Highlight::String]),
            (
                "${",
                vec![
                    Highlight::String,
                    Highlight::Embedded,
                    Highlight::PunctuationSpecial
                ]
            ),
            (
                "a",
                vec![Highlight::String, Highlight::Embedded, Highlight::Variable]
            ),
            (" ", vec![Highlight::String, Highlight::Embedded]),
            (
                "<",
                vec![Highlight::String, Highlight::Embedded, Highlight::Operator]
            ),
            (" ", vec![Highlight::String, Highlight::Embedded]),
            (
                "b",
                vec![Highlight::String, Highlight::Embedded, Highlight::Variable]
            ),
            (
                "}",
                vec![
                    Highlight::String,
                    Highlight::Embedded,
                    Highlight::PunctuationSpecial
                ]
            ),
            ("</", vec![Highlight::String]),
            ("div", vec![Highlight::String, Highlight::Tag]),
            (">`", vec![Highlight::String]),
            (";", vec![Highlight::PunctuationDelimiter]),
        ]]
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
        &to_token_vector(&source, get_language("html"), &HTML_SHEET).unwrap(),
        &[
            vec![("<", vec![]), ("body", vec![Highlight::Tag]), (">", vec![]),],
            vec![
                ("  <", vec![]),
                ("script", vec![Highlight::Tag]),
                (">", vec![]),
            ],
            vec![
                ("    ", vec![]),
                ("const", vec![Highlight::Keyword]),
                (" ", vec![]),
                ("x", vec![Highlight::Variable]),
                (" ", vec![]),
                ("=", vec![Highlight::Operator]),
                (" ", vec![]),
                ("new", vec![Highlight::Keyword]),
                (" ", vec![]),
                ("Thing", vec![Highlight::Constructor]),
                ("(", vec![Highlight::PunctuationBracket]),
                (")", vec![Highlight::PunctuationBracket]),
                (";", vec![Highlight::PunctuationDelimiter]),
            ],
            vec![
                ("  </", vec![]),
                ("script", vec![Highlight::Tag]),
                (">", vec![]),
            ],
            vec![
                ("</", vec![]),
                ("body", vec![Highlight::Tag]),
                (">", vec![]),
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
        &to_html(&source, get_language("javascript"), &JS_SHEET,).unwrap(),
        &[
            "<span class=Keyword>const</span> <span class=Constant>SOMETHING</span> <span class=Operator>=</span> <span class=String>`</span>\n".to_string(),
            "<span class=String>  one <span class=Embedded><span class=PunctuationSpecial>${</span></span></span>\n".to_string(),
            "<span class=String><span class=Embedded>    <span class=Function>two</span><span class=PunctuationBracket>(</span><span class=PunctuationBracket>)</span></span></span>\n".to_string(),
            "<span class=String><span class=Embedded>  <span class=PunctuationSpecial>}</span></span> three</span>\n".to_string(),
            "<span class=String>`</span>\n".to_string(),
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
        &to_token_vector(&source, get_language("javascript"), &JS_SHEET).unwrap(),
        &[
            vec![
                ("module", vec![Highlight::VariableBuiltin]),
                (".", vec![Highlight::PunctuationDelimiter]),
                ("exports", vec![Highlight::Property]),
                (" ", vec![]),
                ("=", vec![Highlight::Operator]),
                (" ", vec![]),
                ("function", vec![Highlight::Keyword]),
                (" ", vec![]),
                ("a", vec![Highlight::Function]),
                ("(", vec![Highlight::PunctuationBracket]),
                ("b", vec![Highlight::VariableParameter]),
                (")", vec![Highlight::PunctuationBracket]),
                (" ", vec![]),
                ("{", vec![Highlight::PunctuationBracket])
            ],
            vec![
                ("  ", vec![]),
                ("const", vec![Highlight::Keyword]),
                (" ", vec![]),
                ("module", vec![Highlight::Variable]),
                (" ", vec![]),
                ("=", vec![Highlight::Operator]),
                (" ", vec![]),
                ("c", vec![Highlight::Variable]),
                (";", vec![Highlight::PunctuationDelimiter])
            ],
            vec![
                ("  ", vec![]),
                ("console", vec![Highlight::VariableBuiltin]),
                (".", vec![Highlight::PunctuationDelimiter]),
                ("log", vec![Highlight::Function]),
                ("(", vec![Highlight::PunctuationBracket]),
                // Not a builtin, because `module` was defined as a variable above.
                ("module", vec![Highlight::Variable]),
                (",", vec![Highlight::PunctuationDelimiter]),
                (" ", vec![]),
                // A parameter, because `b` was defined as a parameter above.
                ("b", vec![Highlight::VariableParameter]),
                (")", vec![Highlight::PunctuationBracket]),
                (";", vec![Highlight::PunctuationDelimiter]),
            ],
            vec![("}", vec![Highlight::PunctuationBracket])]
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
        &to_html(&source, get_language("javascript"), &JS_SHEET,).unwrap(),
        &[
            "<span class=Keyword>class</span> <span class=Constructor>A</span> <span class=PunctuationBracket>{</span>\n".to_string(),
            "\n".to_string(),
            "  <span class=Function>b</span><span class=PunctuationBracket>(</span><span class=VariableParameter>c</span><span class=PunctuationBracket>)</span> <span class=PunctuationBracket>{</span>\n".to_string(),
            "\n".to_string(),
            "    <span class=Function>d</span><span class=PunctuationBracket>(</span><span class=Variable>e</span><span class=PunctuationBracket>)</span>\n".to_string(),
            "\n".to_string(),
            "  <span class=PunctuationBracket>}</span>\n".to_string(),
            "\n".to_string(),
            "<span class=PunctuationBracket>}</span>\n".to_string(),
        ]
    );
}

#[test]
fn test_highlighting_ejs() {
    let source = vec!["<div><% foo() %></div>"].join("\n");

    assert_eq!(
        &to_token_vector(&source, get_language("embedded-template"), &EJS_SHEET).unwrap(),
        &[[
            ("<", vec![]),
            ("div", vec![Highlight::Tag]),
            (">", vec![]),
            ("<%", vec![Highlight::Keyword]),
            (" ", vec![]),
            ("foo", vec![Highlight::Function]),
            ("(", vec![Highlight::PunctuationBracket]),
            (")", vec![Highlight::PunctuationBracket]),
            (" ", vec![]),
            ("%>", vec![Highlight::Keyword]),
            ("</", vec![]),
            ("div", vec![Highlight::Tag]),
            (">", vec![])
        ]],
    );
}

#[test]
fn test_highlighting_with_content_children_included() {
    let source = vec!["assert!(", "    a.b.c() < D::e::<F>()", ");"].join("\n");

    assert_eq!(
        &to_token_vector(&source, get_language("rust"), &RUST_SHEET).unwrap(),
        &[
            vec![
                ("assert", vec![Highlight::Function]),
                ("!", vec![Highlight::Function]),
                ("(", vec![Highlight::PunctuationBracket]),
            ],
            vec![
                ("    a", vec![]),
                (".", vec![Highlight::PunctuationDelimiter]),
                ("b", vec![Highlight::Property]),
                (".", vec![Highlight::PunctuationDelimiter]),
                ("c", vec![Highlight::Function]),
                ("(", vec![Highlight::PunctuationBracket]),
                (")", vec![Highlight::PunctuationBracket]),
                (" < ", vec![]),
                ("D", vec![Highlight::Type]),
                ("::", vec![Highlight::PunctuationDelimiter]),
                ("e", vec![Highlight::Function]),
                ("::", vec![Highlight::PunctuationDelimiter]),
                ("<", vec![Highlight::PunctuationBracket]),
                ("F", vec![Highlight::Type]),
                (">", vec![Highlight::PunctuationBracket]),
                ("(", vec![Highlight::PunctuationBracket]),
                (")", vec![Highlight::PunctuationBracket]),
            ],
            vec![(")", vec![Highlight::PunctuationBracket]), (";", vec![]),]
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

    // Constructing the highlighter, which eagerly parses the outer document,
    // should not fail.
    let highlighter = highlight(
        source.as_bytes(),
        get_language("html"),
        &HTML_SHEET,
        Some(&cancellation_flag),
        injection_callback,
    )
    .unwrap();

    // Iterating the scopes should not panic. It should return an error
    // once the cancellation is detected.
    for event in highlighter {
        if let Err(e) = event {
            assert_eq!(e, Error::Cancelled);
            return;
        }
    }
    panic!("Expected an error while iterating highlighter");
}

#[test]
fn test_highlighting_via_c_api() {
    let js_lang = get_language("javascript");
    let html_lang = get_language("html");
    let js_sheet = get_property_sheet_json("javascript", "highlights.json");
    let js_sheet = c_string(&js_sheet);
    let html_sheet = get_property_sheet_json("html", "highlights.json");
    let html_sheet = c_string(&html_sheet);

    let class_tag = c_string("class=tag");
    let class_function = c_string("class=function");
    let class_string = c_string("class=string");
    let class_keyword = c_string("class=keyword");

    let js_scope_name = c_string("source.js");
    let html_scope_name = c_string("text.html.basic");
    let injection_regex = c_string("^(javascript|js)$");
    let source_code = c_string("<script>\nconst a = b('c');\nc.d();\n</script>");

    let attribute_strings = &mut [ptr::null(); Highlight::Unknown as usize + 1];
    attribute_strings[Highlight::Tag as usize] = class_tag.as_ptr();
    attribute_strings[Highlight::String as usize] = class_string.as_ptr();
    attribute_strings[Highlight::Keyword as usize] = class_keyword.as_ptr();
    attribute_strings[Highlight::Function as usize] = class_function.as_ptr();

    let highlighter = c::ts_highlighter_new(attribute_strings.as_ptr());
    let buffer = c::ts_highlight_buffer_new();

    c::ts_highlighter_add_language(
        highlighter,
        html_scope_name.as_ptr(),
        html_lang,
        html_sheet.as_ptr(),
        ptr::null_mut(),
    );
    c::ts_highlighter_add_language(
        highlighter,
        js_scope_name.as_ptr(),
        js_lang,
        js_sheet.as_ptr(),
        injection_regex.as_ptr(),
    );
    c::ts_highlighter_highlight(
        highlighter,
        html_scope_name.as_ptr(),
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
            "&lt;<span class=tag>script</span>&gt;",
            "<span class=keyword>const</span> <span>a</span> <span>=</span> <span class=function>b</span><span>(</span><span class=string>&#39;c&#39;</span><span>)</span><span>;</span>",
            "<span>c</span><span>.</span><span class=function>d</span><span>(</span><span>)</span><span>;</span>",
            "&lt;/<span class=tag>script</span>&gt;",
        ]
    );

    c::ts_highlighter_delete(highlighter);
    c::ts_highlight_buffer_delete(buffer);
}

fn c_string(s: &str) -> CString {
    CString::new(s.as_bytes().to_vec()).unwrap()
}

fn test_language_for_injection_string<'a>(
    string: &str,
) -> Option<(Language, &'a PropertySheet<Properties>)> {
    match string {
        "javascript" => Some((get_language("javascript"), &JS_SHEET)),
        "html" => Some((get_language("html"), &HTML_SHEET)),
        "rust" => Some((get_language("rust"), &RUST_SHEET)),
        _ => None,
    }
}

fn to_html<'a>(
    src: &'a str,
    language: Language,
    property_sheet: &'a PropertySheet<Properties>,
) -> Result<Vec<String>, Error> {
    highlight_html(
        src.as_bytes(),
        language,
        property_sheet,
        None,
        &test_language_for_injection_string,
        &|highlight| SCOPE_CLASS_STRINGS[highlight as usize].as_str(),
    )
}

fn to_token_vector<'a>(
    src: &'a str,
    language: Language,
    property_sheet: &'a PropertySheet<Properties>,
) -> Result<Vec<Vec<(&'a str, Vec<Highlight>)>>, Error> {
    let mut lines = Vec::new();
    let mut highlights = Vec::new();
    let mut line = Vec::new();
    for event in highlight(
        src.as_bytes(),
        language,
        property_sheet,
        None,
        &test_language_for_injection_string,
    )? {
        match event? {
            HighlightEvent::HighlightStart(s) => highlights.push(s),
            HighlightEvent::HighlightEnd => {
                highlights.pop();
            }
            HighlightEvent::Source(s) => {
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
