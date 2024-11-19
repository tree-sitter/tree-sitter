use std::{
    collections::HashMap,
    fmt::Write,
    fs,
    io::{self, Write as _},
    path, str,
    sync::atomic::AtomicUsize,
    time::Instant,
};

use anstyle::{Ansi256Color, AnsiColor, Color, Effects, RgbColor};
use anyhow::Result;
use lazy_static::lazy_static;
use serde::{ser::SerializeMap, Deserialize, Deserializer, Serialize, Serializer};
use serde_json::{json, Value};
use tree_sitter_highlight::{HighlightConfiguration, HighlightEvent, Highlighter, HtmlRenderer};
use tree_sitter_loader::Loader;

pub const HTML_HEADER: &str = "
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

pub const HTML_FOOTER: &str = "
</body>
";

lazy_static! {
    static ref CSS_STYLES_BY_COLOR_ID: Vec<String> =
        serde_json::from_str(include_str!("../vendor/xterm-colors.json")).unwrap();
}

#[derive(Debug, Default)]
pub struct Style {
    pub ansi: anstyle::Style,
    pub css: Option<String>,
}

#[derive(Debug)]
pub struct Theme {
    pub styles: Vec<Style>,
    pub highlight_names: Vec<String>,
}

#[derive(Default, Deserialize, Serialize)]
pub struct ThemeConfig {
    #[serde(default)]
    pub theme: Theme,
}

impl Theme {
    pub fn load(path: &path::Path) -> io::Result<Self> {
        let json = fs::read_to_string(path)?;
        Ok(serde_json::from_str(&json).unwrap_or_default())
    }

    #[must_use]
    pub fn default_style(&self) -> Style {
        Style::default()
    }
}

impl<'de> Deserialize<'de> for Theme {
    fn deserialize<D>(deserializer: D) -> std::result::Result<Self, D::Error>
    where
        D: Deserializer<'de>,
    {
        let mut styles = Vec::new();
        let mut highlight_names = Vec::new();
        if let Ok(colors) = HashMap::<String, Value>::deserialize(deserializer) {
            highlight_names.reserve(colors.len());
            styles.reserve(colors.len());
            for (name, style_value) in colors {
                let mut style = Style::default();
                parse_style(&mut style, style_value);
                highlight_names.push(name);
                styles.push(style);
            }
        }
        Ok(Self {
            styles,
            highlight_names,
        })
    }
}

impl Serialize for Theme {
    fn serialize<S>(&self, serializer: S) -> std::result::Result<S::Ok, S::Error>
    where
        S: Serializer,
    {
        let mut map = serializer.serialize_map(Some(self.styles.len()))?;
        for (name, style) in self.highlight_names.iter().zip(&self.styles) {
            let style = &style.ansi;
            let color = style.get_fg_color().map(|color| match color {
                Color::Ansi(color) => match color {
                    AnsiColor::Black => json!("black"),
                    AnsiColor::Blue => json!("blue"),
                    AnsiColor::Cyan => json!("cyan"),
                    AnsiColor::Green => json!("green"),
                    AnsiColor::Magenta => json!("purple"),
                    AnsiColor::Red => json!("red"),
                    AnsiColor::White => json!("white"),
                    AnsiColor::Yellow => json!("yellow"),
                    _ => unreachable!(),
                },
                Color::Ansi256(Ansi256Color(n)) => json!(n),
                Color::Rgb(RgbColor(r, g, b)) => json!(format!("#{r:x?}{g:x?}{b:x?}")),
            });
            let effects = style.get_effects();
            if effects.contains(Effects::BOLD)
                || effects.contains(Effects::ITALIC)
                || effects.contains(Effects::UNDERLINE)
            {
                let mut style_json = HashMap::new();
                if let Some(color) = color {
                    style_json.insert("color", color);
                }
                if effects.contains(Effects::BOLD) {
                    style_json.insert("bold", Value::Bool(true));
                }
                if effects.contains(Effects::ITALIC) {
                    style_json.insert("italic", Value::Bool(true));
                }
                if effects.contains(Effects::UNDERLINE) {
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
        serde_json::from_value(json!({
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
              "module": 136,
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
        }))
        .unwrap()
    }
}

fn parse_style(style: &mut Style, json: Value) {
    if let Value::Object(entries) = json {
        for (property_name, value) in entries {
            match property_name.as_str() {
                "bold" => {
                    if value == Value::Bool(true) {
                        style.ansi = style.ansi.bold();
                    }
                }
                "italic" => {
                    if value == Value::Bool(true) {
                        style.ansi = style.ansi.italic();
                    }
                }
                "underline" => {
                    if value == Value::Bool(true) {
                        style.ansi = style.ansi.underline();
                    }
                }
                "color" => {
                    if let Some(color) = parse_color(value) {
                        style.ansi = style.ansi.fg_color(Some(color));
                    }
                }
                _ => {}
            }
        }
        style.css = Some(style_to_css(style.ansi));
    } else if let Some(color) = parse_color(json) {
        style.ansi = style.ansi.fg_color(Some(color));
        style.css = Some(style_to_css(style.ansi));
    } else {
        style.css = None;
    }

    if let Some(Color::Rgb(RgbColor(red, green, blue))) = style.ansi.get_fg_color() {
        if !terminal_supports_truecolor() {
            style.ansi = style
                .ansi
                .fg_color(Some(closest_xterm_color(red, green, blue)));
        }
    }
}

fn parse_color(json: Value) -> Option<Color> {
    match json {
        Value::Number(n) => n.as_u64().map(|n| Color::Ansi256(Ansi256Color(n as u8))),
        Value::String(s) => match s.to_lowercase().as_str() {
            "black" => Some(Color::Ansi(AnsiColor::Black)),
            "blue" => Some(Color::Ansi(AnsiColor::Blue)),
            "cyan" => Some(Color::Ansi(AnsiColor::Cyan)),
            "green" => Some(Color::Ansi(AnsiColor::Green)),
            "purple" => Some(Color::Ansi(AnsiColor::Magenta)),
            "red" => Some(Color::Ansi(AnsiColor::Red)),
            "white" => Some(Color::Ansi(AnsiColor::White)),
            "yellow" => Some(Color::Ansi(AnsiColor::Yellow)),
            s => {
                if let Some((red, green, blue)) = hex_string_to_rgb(s) {
                    Some(Color::Rgb(RgbColor(red, green, blue)))
                } else {
                    None
                }
            }
        },
        _ => None,
    }
}

fn hex_string_to_rgb(s: &str) -> Option<(u8, u8, u8)> {
    if s.starts_with('#') && s.len() >= 7 {
        if let (Ok(red), Ok(green), Ok(blue)) = (
            u8::from_str_radix(&s[1..3], 16),
            u8::from_str_radix(&s[3..5], 16),
            u8::from_str_radix(&s[5..7], 16),
        ) {
            Some((red, green, blue))
        } else {
            None
        }
    } else {
        None
    }
}

fn style_to_css(style: anstyle::Style) -> String {
    let mut result = "style='".to_string();
    let effects = style.get_effects();
    if effects.contains(Effects::UNDERLINE) {
        write!(&mut result, "text-decoration: underline;").unwrap();
    }
    if effects.contains(Effects::BOLD) {
        write!(&mut result, "font-weight: bold;").unwrap();
    }
    if effects.contains(Effects::ITALIC) {
        write!(&mut result, "font-style: italic;").unwrap();
    }
    if let Some(color) = style.get_fg_color() {
        write_color(&mut result, color);
    }
    result.push('\'');
    result
}

fn write_color(buffer: &mut String, color: Color) {
    match color {
        Color::Ansi(color) => match color {
            AnsiColor::Black => write!(buffer, "color: black").unwrap(),
            AnsiColor::Red => write!(buffer, "color: red").unwrap(),
            AnsiColor::Green => write!(buffer, "color: green").unwrap(),
            AnsiColor::Yellow => write!(buffer, "color: yellow").unwrap(),
            AnsiColor::Blue => write!(buffer, "color: blue").unwrap(),
            AnsiColor::Magenta => write!(buffer, "color: purple").unwrap(),
            AnsiColor::Cyan => write!(buffer, "color: cyan").unwrap(),
            AnsiColor::White => write!(buffer, "color: white").unwrap(),
            _ => unreachable!(),
        },
        Color::Ansi256(Ansi256Color(n)) => {
            write!(buffer, "color: {}", CSS_STYLES_BY_COLOR_ID[n as usize]).unwrap();
        }
        Color::Rgb(RgbColor(r, g, b)) => write!(buffer, "color: #{r:02x}{g:02x}{b:02x}").unwrap(),
    }
}

fn terminal_supports_truecolor() -> bool {
    std::env::var("COLORTERM")
        .is_ok_and(|truecolor| truecolor == "truecolor" || truecolor == "24bit")
}

fn closest_xterm_color(red: u8, green: u8, blue: u8) -> Color {
    use std::cmp::{max, min};

    let colors = CSS_STYLES_BY_COLOR_ID
        .iter()
        .enumerate()
        .map(|(color_id, hex)| (color_id as u8, hex_string_to_rgb(hex).unwrap()));

    // Get the xterm color with the minimum Euclidean distance to the target color
    // i.e.  distance = √ (r2 - r1)² + (g2 - g1)² + (b2 - b1)²
    let distances = colors.map(|(color_id, (r, g, b))| {
        let r_delta = (max(r, red) - min(r, red)) as u32;
        let g_delta = (max(g, green) - min(g, green)) as u32;
        let b_delta = (max(b, blue) - min(b, blue)) as u32;
        let distance = r_delta.pow(2) + g_delta.pow(2) + b_delta.pow(2);
        // don't need to actually take the square root for the sake of comparison
        (color_id, distance)
    });

    Color::Ansi256(Ansi256Color(
        distances.min_by(|(_, d1), (_, d2)| d1.cmp(d2)).unwrap().0,
    ))
}

pub fn ansi(
    loader: &Loader,
    theme: &Theme,
    source: &[u8],
    config: &HighlightConfiguration,
    print_time: bool,
    cancellation_flag: Option<&AtomicUsize>,
) -> Result<()> {
    let stdout = io::stdout();
    let mut stdout = stdout.lock();
    let time = Instant::now();
    let mut highlighter = Highlighter::new();

    let events = highlighter.highlight(config, source, cancellation_flag, |string| {
        loader.highlight_config_for_injection_string(string)
    })?;

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
                let style = style_stack.last().unwrap();
                write!(&mut stdout, "{style}").unwrap();
                stdout.write_all(&source[start..end])?;
                write!(&mut stdout, "{style:#}").unwrap();
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
    quiet: bool,
    print_time: bool,
    cancellation_flag: Option<&AtomicUsize>,
) -> Result<()> {
    use std::io::Write;

    let stdout = io::stdout();
    let mut stdout = stdout.lock();
    let time = Instant::now();
    let mut highlighter = Highlighter::new();

    let events = highlighter.highlight(config, source, cancellation_flag, |string| {
        loader.highlight_config_for_injection_string(string)
    })?;

    let mut renderer = HtmlRenderer::new();
    renderer.render(events, source, &move |highlight| {
        theme.styles[highlight.0]
            .css
            .as_ref()
            .map_or_else(|| "".as_bytes(), |css_style| css_style.as_bytes())
    })?;

    if !quiet {
        writeln!(&mut stdout, "<table>")?;
        for (i, line) in renderer.lines().enumerate() {
            writeln!(
                &mut stdout,
                "<tr><td class=line-number>{}</td><td class=line>{line}</td></tr>",
                i + 1,
            )?;
        }

        writeln!(&mut stdout, "</table>")?;
    }

    if print_time {
        eprintln!("Time: {}ms", time.elapsed().as_millis());
    }

    Ok(())
}

#[cfg(test)]
mod tests {
    use std::env;

    use super::*;

    const JUNGLE_GREEN: &str = "#26A69A";
    const DARK_CYAN: &str = "#00AF87";

    #[test]
    fn test_parse_style() {
        let original_environment_variable = env::var("COLORTERM");

        let mut style = Style::default();
        assert_eq!(style.ansi.get_fg_color(), None);
        assert_eq!(style.css, None);

        // darkcyan is an ANSI color and is preserved
        env::set_var("COLORTERM", "");
        parse_style(&mut style, Value::String(DARK_CYAN.to_string()));
        assert_eq!(
            style.ansi.get_fg_color(),
            Some(Color::Ansi256(Ansi256Color(36)))
        );
        assert_eq!(style.css, Some("style=\'color: #00af87\'".to_string()));

        // junglegreen is not an ANSI color and is preserved when the terminal supports it
        env::set_var("COLORTERM", "truecolor");
        parse_style(&mut style, Value::String(JUNGLE_GREEN.to_string()));
        assert_eq!(
            style.ansi.get_fg_color(),
            Some(Color::Rgb(RgbColor(38, 166, 154)))
        );
        assert_eq!(style.css, Some("style=\'color: #26a69a\'".to_string()));

        // junglegreen gets approximated as darkcyan when the terminal does not support it
        env::set_var("COLORTERM", "");
        parse_style(&mut style, Value::String(JUNGLE_GREEN.to_string()));
        assert_eq!(
            style.ansi.get_fg_color(),
            Some(Color::Ansi256(Ansi256Color(36)))
        );
        assert_eq!(style.css, Some("style=\'color: #26a69a\'".to_string()));

        if let Ok(environment_variable) = original_environment_variable {
            env::set_var("COLORTERM", environment_variable);
        } else {
            env::remove_var("COLORTERM");
        }
    }
}
