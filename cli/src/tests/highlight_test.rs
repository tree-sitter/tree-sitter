use super::helpers::fixtures::{get_language, get_property_sheet};
use lazy_static::lazy_static;
use tree_sitter::{Language, PropertySheet};
use tree_sitter_highlight::{highlight, highlight_html, HighlightEvent, Properties, Scope};

lazy_static! {
    static ref JS_SHEET: PropertySheet<Properties> =
        get_property_sheet("javascript", "highlights.json");
    static ref HTML_SHEET: PropertySheet<Properties> =
        get_property_sheet("html", "highlights.json");
    static ref SCOPE_CLASS_STRINGS: Vec<String> = {
        let mut result = Vec::new();
        let mut i = 0;
        while let Some(scope) = Scope::from_usize(i) {
            result.push(format!("class={:?}", scope));
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
            ("const", vec![Scope::Keyword]),
            (" ", vec![]),
            ("s", vec![Scope::Variable]),
            (" ", vec![]),
            ("=", vec![Scope::Operator]),
            (" ", vec![]),
            ("html", vec![Scope::Function]),
            (" ", vec![]),
            ("`<", vec![Scope::String]),
            ("div", vec![Scope::String, Scope::Tag]),
            (">", vec![Scope::String]),
            (
                "${",
                vec![Scope::String, Scope::Embedded, Scope::PunctuationSpecial]
            ),
            ("a", vec![Scope::String, Scope::Embedded, Scope::Variable]),
            (" ", vec![Scope::String, Scope::Embedded]),
            ("<", vec![Scope::String, Scope::Embedded, Scope::Operator]),
            (" ", vec![Scope::String, Scope::Embedded]),
            ("b", vec![Scope::String, Scope::Embedded, Scope::Variable]),
            (
                "}",
                vec![Scope::String, Scope::Embedded, Scope::PunctuationSpecial]
            ),
            ("</", vec![Scope::String]),
            ("div", vec![Scope::String, Scope::Tag]),
            (">`", vec![Scope::String]),
            (";", vec![Scope::PunctuationDelimiter]),
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
            vec![("<", vec![]), ("body", vec![Scope::Tag]), (">", vec![]),],
            vec![("  <", vec![]), ("script", vec![Scope::Tag]), (">", vec![]),],
            vec![
                ("    ", vec![]),
                ("const", vec![Scope::Keyword]),
                (" ", vec![]),
                ("x", vec![Scope::Variable]),
                (" ", vec![]),
                ("=", vec![Scope::Operator]),
                (" ", vec![]),
                ("new", vec![Scope::Keyword]),
                (" ", vec![]),
                ("Thing", vec![Scope::Constructor]),
                ("(", vec![Scope::PunctuationBracket]),
                (")", vec![Scope::PunctuationBracket]),
                (";", vec![Scope::PunctuationDelimiter]),
            ],
            vec![
                ("  </", vec![]),
                ("script", vec![Scope::Tag]),
                (">", vec![]),
            ],
            vec![("</", vec![]), ("body", vec![Scope::Tag]), (">", vec![]),],
        ]
    );
}

#[test]
fn test_highlighting_multiline_scopes_to_html() {
    let source = vec![
        "const SOMETHING = `",
        "  one ${",
        "    two()",
        "  } three",
        "`",
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
            "  <span class=Function>b</span><span class=PunctuationBracket>(</span><span class=Variable>c</span><span class=PunctuationBracket>)</span> <span class=PunctuationBracket>{</span>\n".to_string(),
            "\n".to_string(),
            "    <span class=Function>d</span><span class=PunctuationBracket>(</span><span class=Variable>e</span><span class=PunctuationBracket>)</span>\n".to_string(),
            "\n".to_string(),
            "  <span class=PunctuationBracket>}</span>\n".to_string(),
            "\n".to_string(),
            "<span class=PunctuationBracket>}</span>\n".to_string(),
        ]
    );
}

fn test_language_for_injection_string<'a>(
    string: &str,
) -> Option<(Language, &'a PropertySheet<Properties>)> {
    match string {
        "javascript" => Some((get_language("javascript"), &JS_SHEET)),
        "html" => Some((get_language("html"), &HTML_SHEET)),
        _ => None,
    }
}

fn to_html<'a>(
    src: &'a str,
    language: Language,
    property_sheet: &'a PropertySheet<Properties>,
) -> Result<Vec<String>, String> {
    highlight_html(
        src.as_bytes(),
        language,
        property_sheet,
        &test_language_for_injection_string,
        &|scope| SCOPE_CLASS_STRINGS[scope as usize].as_str(),
    )
}

fn to_token_vector<'a>(
    src: &'a str,
    language: Language,
    property_sheet: &'a PropertySheet<Properties>,
) -> Result<Vec<Vec<(&'a str, Vec<Scope>)>>, String> {
    let mut lines = Vec::new();
    let mut scopes = Vec::new();
    let mut line = Vec::new();
    for event in highlight(
        src.as_bytes(),
        language,
        property_sheet,
        &test_language_for_injection_string,
    )? {
        match event {
            HighlightEvent::ScopeStart(s) => scopes.push(s),
            HighlightEvent::ScopeEnd => {
                scopes.pop();
            }
            HighlightEvent::Source(s) => {
                for (i, l) in s.lines().enumerate() {
                    if i > 0 {
                        lines.push(line);
                        line = Vec::new();
                    }
                    if l.len() > 0 {
                        line.push((l, scopes.clone()));
                    }
                }
            }
        }
    }
    lines.push(line);
    Ok(lines)
}
