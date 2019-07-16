use crate::error::Result;
use crate::loader::Loader;
use ansi_term::{Color, Style};
use lazy_static::lazy_static;
use serde::ser::SerializeMap;
use serde::{Deserialize, Deserializer, Serialize, Serializer};
use serde_json::{json, Value};
use std::collections::HashMap;
use std::sync::atomic::{AtomicUsize, Ordering};
use std::sync::Arc;
use std::time::Instant;
use std::{fmt, fs, io, path, thread};
use tree_sitter::{Language, PropertySheet};
use tree_sitter_highlight::{highlight, highlight_html, Highlight, HighlightEvent, Properties};

lazy_static! {
    static ref CSS_STYLES_BY_COLOR_ID: Vec<String> =
        serde_json::from_str(include_str!("../vendor/xterm-colors.json")).unwrap();
}

pub struct Theme {
    ansi_styles: Vec<Option<Style>>,
    css_styles: Vec<Option<String>>,
}

impl Theme {
    pub fn load(path: &path::Path) -> io::Result<Self> {
        let json = fs::read_to_string(path)?;
        Ok(serde_json::from_str(&json).unwrap_or_default())
    }

    fn ansi_style(&self, highlight: Highlight) -> Option<&Style> {
        self.ansi_styles[highlight as usize].as_ref()
    }

    fn css_style(&self, highlight: Highlight) -> Option<&str> {
        self.css_styles[highlight as usize]
            .as_ref()
            .map(|s| s.as_str())
    }
}

impl<'de> Deserialize<'de> for Theme {
    fn deserialize<D>(deserializer: D) -> std::result::Result<Theme, D::Error>
    where
        D: Deserializer<'de>,
    {
        let highlight_count = Highlight::Unknown as usize + 1;
        let mut ansi_styles = vec![None; highlight_count];
        let mut css_styles = vec![None; highlight_count];
        if let Ok(colors) = HashMap::<Highlight, Value>::deserialize(deserializer) {
            for (highlight, style_value) in colors {
                let mut style = Style::default();
                parse_style(&mut style, style_value);
                ansi_styles[highlight as usize] = Some(style);
                css_styles[highlight as usize] = Some(style_to_css(style));
            }
        }
        Ok(Self {
            ansi_styles,
            css_styles,
        })
    }
}

impl Serialize for Theme {
    fn serialize<S>(&self, serializer: S) -> std::result::Result<S::Ok, S::Error>
    where
        S: Serializer,
    {
        let entry_count = self.ansi_styles.iter().filter(|i| i.is_some()).count();
        let mut map = serializer.serialize_map(Some(entry_count))?;
        for (i, style) in self.ansi_styles.iter().enumerate() {
            let highlight = Highlight::from_usize(i).unwrap();
            if highlight == Highlight::Unknown {
                break;
            }
            if let Some(style) = style {
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
                    let mut entry = HashMap::new();
                    if let Some(color) = color {
                        entry.insert("color", color);
                    }
                    if style.is_bold {
                        entry.insert("bold", Value::Bool(true));
                    }
                    if style.is_italic {
                        entry.insert("italic", Value::Bool(true));
                    }
                    if style.is_underline {
                        entry.insert("underline", Value::Bool(true));
                    }
                    map.serialize_entry(&highlight, &entry)?;
                } else if let Some(color) = color {
                    map.serialize_entry(&highlight, &color)?;
                } else {
                    map.serialize_entry(&highlight, &Value::Null)?;
                }
            } else {
                map.serialize_entry(&highlight, &Value::Null)?;
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

impl fmt::Debug for Theme {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "{{")?;
        let mut first = true;
        for (i, style) in self.ansi_styles.iter().enumerate() {
            if let Some(style) = style {
                let highlight = Highlight::from_usize(i).unwrap();
                if !first {
                    write!(f, ", ")?;
                }
                write!(f, "{:?}: {:?}", highlight, style)?;
                first = false;
            }
        }
        write!(f, "}}")?;
        Ok(())
    }
}

fn parse_style(style: &mut Style, json: Value) {
    if let Value::Object(entries) = json {
        for (property_name, value) in entries {
            match property_name.as_str() {
                "bold" => *style = style.bold(),
                "italic" => *style = style.italic(),
                "underline" => *style = style.underline(),
                "color" => {
                    if let Some(color) = parse_color(value) {
                        *style = style.fg(color);
                    }
                }
                _ => {}
            }
        }
    } else if let Some(color) = parse_color(json) {
        *style = style.fg(color);
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

fn style_to_css(style: Style) -> String {
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
    language: Language,
    property_sheet: &PropertySheet<Properties>,
    print_time: bool,
) -> Result<()> {
    use std::io::Write;
    let stdout = io::stdout();
    let mut stdout = stdout.lock();

    let cancellation_flag = cancel_on_stdin();
    let time = Instant::now();
    let mut highlight_stack = Vec::new();
    for event in highlight(
        source,
        language,
        property_sheet,
        Some(cancellation_flag.as_ref()),
        |s| language_for_injection_string(loader, s),
    )
    .map_err(|e| e.to_string())?
    {
        let event = event.map_err(|e| e.to_string())?;
        match event {
            HighlightEvent::Source(s) => {
                if let Some(style) = highlight_stack.last().and_then(|s| theme.ansi_style(*s)) {
                    write!(&mut stdout, "{}", style.paint(s))?;
                } else {
                    write!(&mut stdout, "{}", s)?;
                }
            }
            HighlightEvent::HighlightStart(h) => {
                highlight_stack.push(h);
            }
            HighlightEvent::HighlightEnd => {
                highlight_stack.pop();
            }
        }
    }

    if print_time {
        let duration = time.elapsed();
        let duration_ms = duration.as_secs() * 1000 + duration.subsec_nanos() as u64 / 1000000;
        eprintln!("{} ms", duration_ms);
    }

    Ok(())
}

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

pub fn html(
    loader: &Loader,
    theme: &Theme,
    source: &[u8],
    language: Language,
    property_sheet: &PropertySheet<Properties>,
) -> Result<()> {
    use std::io::Write;
    let stdout = io::stdout();
    let mut stdout = stdout.lock();
    write!(&mut stdout, "<table>\n")?;

    let cancellation_flag = cancel_on_stdin();
    let lines = highlight_html(
        source,
        language,
        property_sheet,
        Some(cancellation_flag.as_ref()),
        |s| language_for_injection_string(loader, s),
        |highlight| {
            if let Some(css_style) = theme.css_style(highlight) {
                css_style
            } else {
                ""
            }
        },
    )
    .map_err(|e| e.to_string())?;
    for (i, line) in lines.into_iter().enumerate() {
        write!(
            &mut stdout,
            "<tr><td class=line-number>{}</td><td class=line>{}</td></tr>\n",
            i + 1,
            line
        )?;
    }
    write!(&mut stdout, "</table>\n")?;
    Ok(())
}

fn language_for_injection_string<'a>(
    loader: &'a Loader,
    string: &str,
) -> Option<(Language, &'a PropertySheet<Properties>)> {
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
            match configuration.highlight_property_sheet(language) {
                Err(e) => {
                    eprintln!(
                        "Failed to load property sheet for injection string '{}': {}",
                        string,
                        e.message()
                    );
                    None
                }
                Ok(None) => None,
                Ok(Some(sheet)) => Some((language, sheet)),
            }
        }
    }
}
