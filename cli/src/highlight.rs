use crate::error::Result;
use crate::loader::Loader;
use ansi_term::Color;
use lazy_static::lazy_static;
use serde::ser::SerializeMap;
use serde::{Deserialize, Deserializer, Serialize, Serializer};
use serde_json::{json, Value};
use std::collections::HashMap;
use std::sync::atomic::{AtomicUsize, Ordering};
use std::sync::Arc;
use std::time::Instant;
use std::{fs, io, path, str, thread, usize};
use tree_sitter_highlight::{
    HighlightConfiguration, HighlightContext, HighlightEvent, Highlighter, HtmlRenderer,
};

pub const HTML_HEADER: &'static str = "
<!doctype HTML>
<head>
  <title>Tree-sitter Highlighting</title>
  <style>
    body {
      font-family: monospace
    }
    .line-number {
      user-select: none;
      text-align: right;
      color: rgba(27,31,35,.3);
      padding: 0 10px;
    }
    .line {
      white-space: pre;
    }
  </style>
</head>
<body>
";

pub const HTML_FOOTER: &'static str = "
</body>
";

lazy_static! {
    static ref CSS_STYLES_BY_COLOR_ID: Vec<String> =
        serde_json::from_str(include_str!("../vendor/xterm-colors.json")).unwrap();
}

#[derive(Debug, Default)]
pub struct Style {
    pub ansi: ansi_term::Style,
    pub css: Option<String>,
}

#[derive(Debug)]
pub struct Theme {
    pub highlighter: Highlighter,
    styles: Vec<Style>,
}

impl Theme {
    pub fn load(path: &path::Path) -> io::Result<Self> {
        let json = fs::read_to_string(path)?;
        Ok(serde_json::from_str(&json).unwrap_or_default())
    }

    pub fn default_style(&self) -> Style {
        Style::default()
    }
}

impl<'de> Deserialize<'de> for Theme {
    fn deserialize<D>(deserializer: D) -> std::result::Result<Theme, D::Error>
    where
        D: Deserializer<'de>,
    {
        let mut names = Vec::new();
        let mut styles = Vec::new();
        if let Ok(colors) = HashMap::<String, Value>::deserialize(deserializer) {
            names.reserve(colors.len());
            styles.reserve(colors.len());
            for (name, style_value) in colors {
                let mut style = Style::default();
                parse_style(&mut style, style_value);
                names.push(name);
                styles.push(style);
            }
        }
        Ok(Self {
            highlighter: Highlighter::new(names),
            styles,
        })
    }
}

impl Serialize for Theme {
    fn serialize<S>(&self, serializer: S) -> std::result::Result<S::Ok, S::Error>
    where
        S: Serializer,
    {
        let mut map = serializer.serialize_map(Some(self.styles.len()))?;
        for (name, style) in self.highlighter.names().iter().zip(&self.styles) {
            let style = &style.ansi;
            let color = style.foreground.map(|color| match color {
                Color::Black => json!("black"),
                Color::Blue => json!("blue"),
                Color::Cyan => json!("cyan"),
                Color::Green => json!("green"),
                Color::Purple => json!("purple"),
                Color::Red => json!("red"),
                Color::White => json!("white"),
                Color::Yellow => json!("yellow"),
                Color::RGB(r, g, b) => json!(format!("#{:x?}{:x?}{:x?}", r, g, b)),
                Color::Fixed(n) => json!(n),
            });
            if style.is_bold || style.is_italic || style.is_underline {
                let mut style_json = HashMap::new();
                if let Some(color) = color {
                    style_json.insert("color", color);
                }
                if style.is_bold {
                    style_json.insert("bold", Value::Bool(true));
                }
                if style.is_italic {
                    style_json.insert("italic", Value::Bool(true));
                }
                if style.is_underline {
                    style_json.insert("underline", Value::Bool(true));
                }
                map.serialize_entry(&name, &style_json)?;
            } else if let Some(color) = color {
                map.serialize_entry(&name, &color)?;
            } else {
                map.serialize_entry(&name, &Value::Null)?;
            }
        }
        map.end()
    }
}

impl Default for Theme {
    fn default() -> Self {
        serde_json::from_str(
            r#"
            {
              "attribute": {"color": 124, "italic": true},
              "comment": {"color": 245, "italic": true},
              "constant.builtin": {"color": 94, "bold": true},
              "constant": 94,
              "constructor": 136,
              "embedded": null,
              "function.builtin": {"color": 26, "bold": true},
              "function": 26,
              "keyword": 56,
              "number": {"color": 94, "bold": true},
              "property": 124,
              "operator": {"color": 239, "bold": true},
              "punctuation.bracket": 239,
              "punctuation.delimiter": 239,
              "string.special": 30,
              "string": 28,
              "tag": 18,
              "type": 23,
              "type.builtin": {"color": 23, "bold": true},
              "variable.builtin": {"bold": true},
              "variable.parameter": {"underline": true}
            }
            "#,
        )
        .unwrap()
    }
}

fn parse_style(style: &mut Style, json: Value) {
    if let Value::Object(entries) = json {
        for (property_name, value) in entries {
            match property_name.as_str() {
                "bold" => style.ansi = style.ansi.bold(),
                "italic" => style.ansi = style.ansi.italic(),
                "underline" => style.ansi = style.ansi.underline(),
                "color" => {
                    if let Some(color) = parse_color(value) {
                        style.ansi = style.ansi.fg(color);
                    }
                }
                _ => {}
            }
        }
        style.css = Some(style_to_css(style.ansi));
    } else if let Some(color) = parse_color(json) {
        style.ansi = style.ansi.fg(color);
        style.css = Some(style_to_css(style.ansi));
    } else {
        style.css = None;
    }
}

fn parse_color(json: Value) -> Option<Color> {
    match json {
        Value::Number(n) => match n.as_u64() {
            Some(n) => Some(Color::Fixed(n as u8)),
            _ => None,
        },
        Value::String(s) => match s.to_lowercase().as_str() {
            "black" => Some(Color::Black),
            "blue" => Some(Color::Blue),
            "cyan" => Some(Color::Cyan),
            "green" => Some(Color::Green),
            "purple" => Some(Color::Purple),
            "red" => Some(Color::Red),
            "white" => Some(Color::White),
            "yellow" => Some(Color::Yellow),
            s => {
                if s.starts_with("#") && s.len() >= 7 {
                    if let (Ok(red), Ok(green), Ok(blue)) = (
                        u8::from_str_radix(&s[1..3], 16),
                        u8::from_str_radix(&s[3..5], 16),
                        u8::from_str_radix(&s[5..7], 16),
                    ) {
                        Some(Color::RGB(red, green, blue))
                    } else {
                        None
                    }
                } else {
                    None
                }
            }
        },
        _ => None,
    }
}

fn style_to_css(style: ansi_term::Style) -> String {
    use std::fmt::Write;
    let mut result = "style='".to_string();
    if style.is_bold {
        write!(&mut result, "font-weight: bold;").unwrap();
    }
    if style.is_italic {
        write!(&mut result, "font-style: italic;").unwrap();
    }
    if let Some(color) = style.foreground {
        write!(&mut result, "color: {};", color_to_css(color)).unwrap();
    }
    result.push('\'');
    result
}

fn color_to_css(color: Color) -> &'static str {
    match color {
        Color::Black => "black",
        Color::Blue => "blue",
        Color::Red => "red",
        Color::Green => "green",
        Color::Yellow => "yellow",
        Color::Cyan => "cyan",
        Color::Purple => "purple",
        Color::White => "white",
        Color::Fixed(n) => CSS_STYLES_BY_COLOR_ID[n as usize].as_str(),
        _ => panic!("Unsupported color type"),
    }
}

fn cancel_on_stdin() -> Arc<AtomicUsize> {
    let result = Arc::new(AtomicUsize::new(0));
    thread::spawn({
        let flag = result.clone();
        move || {
            let mut line = String::new();
            io::stdin().read_line(&mut line).unwrap();
            flag.store(1, Ordering::Relaxed);
        }
    });
    result
}

pub fn ansi(
    loader: &Loader,
    theme: &Theme,
    source: &[u8],
    config: &HighlightConfiguration,
    print_time: bool,
) -> Result<()> {
    let stdout = io::stdout();
    let mut stdout = stdout.lock();
    let time = Instant::now();
    let cancellation_flag = cancel_on_stdin();
    let mut context = HighlightContext::new();

    let events = theme.highlighter.highlight(
        &mut context,
        config,
        source,
        Some(&cancellation_flag),
        |string| language_for_injection_string(loader, theme, string),
    )?;

    let mut style_stack = vec![theme.default_style().ansi];
    for event in events {
        match event? {
            HighlightEvent::HighlightStart(highlight) => {
                style_stack.push(theme.styles[highlight.0].ansi);
            }
            HighlightEvent::HighlightEnd => {
                style_stack.pop();
            }
            HighlightEvent::Source { start, end } => {
                style_stack
                    .last()
                    .unwrap()
                    .paint(&source[start..end])
                    .write_to(&mut stdout)?;
            }
        }
    }

    if print_time {
        eprintln!("Time: {}ms", time.elapsed().as_millis());
    }

    Ok(())
}

pub fn html(
    loader: &Loader,
    theme: &Theme,
    source: &[u8],
    config: &HighlightConfiguration,
    print_time: bool,
) -> Result<()> {
    use std::io::Write;

    let stdout = io::stdout();
    let mut stdout = stdout.lock();
    let time = Instant::now();
    let cancellation_flag = cancel_on_stdin();
    let mut context = HighlightContext::new();

    let events = theme.highlighter.highlight(
        &mut context,
        config,
        source,
        Some(&cancellation_flag),
        |string| language_for_injection_string(loader, theme, string),
    )?;

    let mut renderer = HtmlRenderer::new();
    renderer.render(events, source, &move |highlight| {
        if let Some(css_style) = &theme.styles[highlight.0].css {
            css_style.as_bytes()
        } else {
            "".as_bytes()
        }
    })?;

    write!(&mut stdout, "<table>\n")?;
    for (i, line) in renderer.lines().enumerate() {
        write!(
            &mut stdout,
            "<tr><td class=line-number>{}</td><td class=line>{}</td></tr>\n",
            i + 1,
            line
        )?;
    }

    write!(&mut stdout, "</table>\n")?;

    if print_time {
        eprintln!("Time: {}ms", time.elapsed().as_millis());
    }

    Ok(())
}

fn language_for_injection_string<'a>(
    loader: &'a Loader,
    theme: &Theme,
    string: &str,
) -> Option<&'a HighlightConfiguration> {
    match loader.language_configuration_for_injection_string(string) {
        Err(e) => {
            eprintln!(
                "Failed to load language for injection string '{}': {}",
                string,
                e.message()
            );
            None
        }
        Ok(None) => None,
        Ok(Some((language, configuration))) => {
            match configuration.highlight_config(&theme.highlighter, language) {
                Err(e) => {
                    eprintln!(
                        "Failed to load property sheet for injection string '{}': {}",
                        string,
                        e.message()
                    );
                    None
                }
                Ok(None) => None,
                Ok(Some(config)) => Some(config),
            }
        }
    }
}
