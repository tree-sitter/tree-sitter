use std::{
    collections::{BTreeMap, HashSet},
    fmt::Write,
    fs,
    io::{self, Write as _},
    path::{self, Path, PathBuf},
    str,
    sync::{Arc, atomic::AtomicUsize},
    time::Instant,
};

use ansi_colours::{ansi256_from_rgb, rgb_from_ansi256};
use anstyle::{Ansi256Color, AnsiColor, Color, Effects, RgbColor};
use anyhow::Result;
use clap::ValueEnum;
use log::{info, warn};
use serde::{Deserialize, Deserializer, Serialize, Serializer, ser::SerializeMap};
use serde_json::{Value, json};
use tree_sitter::ffi::{self, TSInputEncoding};
use tree_sitter_highlight::{
    Highlight, HighlightConfiguration, Highlighter, HtmlRenderer, Renderer, TEX_CHAR_ESCAPES,
    TerminalRenderer, TexRenderer,
};
use tree_sitter_loader::Loader;

pub const HTML_HEAD_HEADER: &str = "
<!doctype HTML>
<head>
  <title>Tree-sitter Highlighting</title>
  <style>
    body {
      font-family: monospace
    }";

pub const HTML_LINE_NUMBER_STYLE: &str = "    .line-number {
      user-select: none;
      text-align: right;
      color: rgba(27,31,35,.3);
      padding: 0 10px;
    }
    .line {
      white-space: pre;
    }";

pub const HTML_BODY_HEADER: &str = "
</head>
<body>
";

pub const HTML_FOOTER: &str = "
</body>
";

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
        if let Ok(colors) = BTreeMap::<String, Value>::deserialize(deserializer) {
            styles.reserve(colors.len());
            highlight_names.reserve(colors.len());
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
                let mut style_json = BTreeMap::new();
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
            "constant": 94,
            "constant.builtin": {"color": 94, "bold": true},
            "constructor": 136,
            "embedded": null,
            "function": 26,
            "function.builtin": {"color": 26, "bold": true},
            "keyword": 56,
            "module": 136,
            "number": {"color": 94, "bold": true},
            "operator": {"color": 239, "bold": true},
            "property": 124,
            "property.builtin": {"color": 124, "bold": true},
            "punctuation": 239,
            "punctuation.bracket": 239,
            "punctuation.delimiter": 239,
            "punctuation.special": 239,
            "string": 28,
            "string.special": 30,
            "tag": 18,
            "type": 23,
            "type.builtin": {"color": 23, "bold": true},
            "variable": 252,
            "variable.builtin": {"color": 252, "bold": true},
            "variable.parameter": {"color": 252, "underline": true}
        }))
        .unwrap()
    }
}

fn parse_style(style: &mut Style, json: Value) {
    if let Value::Object(entries) = json {
        for (property_name, value) in entries {
            match property_name.as_str() {
                "bold" if value == Value::Bool(true) => {
                    style.ansi = style.ansi.bold();
                }
                "italic" if value == Value::Bool(true) => {
                    style.ansi = style.ansi.italic();
                }
                "underline" if value == Value::Bool(true) => {
                    style.ansi = style.ansi.underline();
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

    if let Some(Color::Rgb(RgbColor(red, green, blue))) = style.ansi.get_fg_color()
        && !terminal_supports_truecolor()
    {
        let ansi256 = Color::Ansi256(Ansi256Color(ansi256_from_rgb((red, green, blue))));
        style.ansi = style.ansi.fg_color(Some(ansi256));
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
    let mut result = String::new();
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
            let (r, g, b) = rgb_from_ansi256(n);
            write!(buffer, "color: #{r:02x}{g:02x}{b:02x}").unwrap();
        }
        Color::Rgb(RgbColor(r, g, b)) => write!(buffer, "color: #{r:02x}{g:02x}{b:02x}").unwrap(),
    }
}

/// Resolve whether an `anstyle::Style` requests italic, bold, and/or underline.
/// Returns `(italic, bold, underline)`.
fn style_flags(style: anstyle::Style) -> (bool, bool, bool) {
    let effects = style.get_effects();
    (
        effects.contains(anstyle::Effects::ITALIC),
        effects.contains(anstyle::Effects::BOLD),
        effects.contains(anstyle::Effects::UNDERLINE),
    )
}

/// Resolve the foreground RGB (0–255) of an `anstyle::Style`, or `None` if there is no color.
fn style_rgb(style: anstyle::Style) -> Option<(u8, u8, u8)> {
    match style.get_fg_color()? {
        Color::Rgb(RgbColor(r, g, b)) => Some((r, g, b)),
        Color::Ansi256(Ansi256Color(n)) => {
            let (r, g, b) = rgb_from_ansi256(n);
            Some((r, g, b))
        }
        Color::Ansi(color) => Some(match color {
            AnsiColor::Black => (0, 0, 0),
            AnsiColor::Red => (187, 0, 0),
            AnsiColor::Green => (0, 187, 0),
            AnsiColor::Yellow => (187, 187, 0),
            AnsiColor::Blue => (0, 0, 187),
            AnsiColor::Magenta => (187, 0, 187),
            AnsiColor::Cyan => (0, 187, 187),
            AnsiColor::White => (187, 187, 187),
            _ => (0, 0, 0),
        }),
    }
}

/// Emit the shared LaTeX preamble/definitions common to `--layout document` and `--layout line-numbers`.
/// Writes the document header, the `\${prefix}@*` macro block, and (when `style == Classes`) one
/// `\@namedef{...@tok@scope}{...}` color definition per colored scope, then closes with `\makeatother`.
fn write_tex_preamble<W: io::Write>(
    w: &mut W,
    prefix: &str,
    theme: &Theme,
    style: HtmlStyling,
) -> Result<()> {
    w.write_all(b"\\makeatletter\n")?;
    // Character-escaping macros: `\TSZdl` expands to an unescaped `$`, etc.
    // The mapping from character to macro suffix is shared with `TexRenderer::escape_char`
    // via `TEX_CHAR_ESCAPES` so the two stay in sync.
    for (ch, suffix) in TEX_CHAR_ESCAPES {
        w.write_all(
            format!(
                "\\def\\{prefix}{suffix}{{\\char`\\{ch}}}\n",
                prefix = prefix,
                suffix = suffix,
                ch = ch
            )
            .as_bytes(),
        )?;
    }
    w.write_all(
        format!(
            "\\def\\{prefix}@reset{{\\let\\{prefix}@it=\\relax\\let\\{prefix}@bf=\\relax\\let\\{prefix}@ul=\\relax \\let\\{prefix}@tc=\\relax\\let\\{prefix}@bc=\\relax\\let\\{prefix}@ff=\\relax}}\n",
            prefix = prefix
        )
        .as_bytes(),
    )?;
    w.write_all(
        format!(
            "\\def\\{prefix}@tok#1{{\\csname {prefix}@tok@#1\\endcsname}}\n",
            prefix = prefix
        )
        .as_bytes(),
    )?;
    w.write_all(
        format!(
            "\\def\\{prefix}@toks#1+{{\\ifx\\relax#1\\empty\\else\\{prefix}@tok{{#1}}\\expandafter\\{prefix}@toks\\fi}}\n",
            prefix = prefix
        )
        .as_bytes(),
    )?;
    w.write_all(
        format!(
            "\\def\\{prefix}@do#1{{\\{prefix}@bc{{\\{prefix}@tc{{\\{prefix}@ul{{\\{prefix}@it{{\\{prefix}@bf{{\\{prefix}@ff{{#1}}}}}}}}}}}}}}\n",
            prefix = prefix
        )
        .as_bytes(),
    )?;
    w.write_all(
        format!(
            "\\def\\{prefix}#1#2{{\\{prefix}@reset\\{prefix}@toks#1+\\relax+\\{prefix}@do{{#2}}}}\n",
            prefix = prefix
        )
        .as_bytes(),
    )?;
    if style != HtmlStyling::Inline {
        for (name, style) in theme.highlight_names.iter().zip(&theme.styles) {
            let rgb = style_rgb(style.ansi);
            let (italic, bold, underline) = style_flags(style.ansi);
            // Emit a named color/style definition whenever the scope carries a
            // color or any of the supported font styles (italic/bold/underline).
            if rgb.is_some() || italic || bold || underline {
                let mut def = String::new();
                // Style switches are emitted before `\def\TS@tc` so they take
                // effect when `@do` applies the token (see the `\TS@do` macro).
                if italic {
                    def.push_str(&format!("\\let\\{prefix}@it=\\textit"));
                }
                if bold {
                    def.push_str(&format!("\\let\\{prefix}@bf=\\textbf"));
                }
                if underline {
                    def.push_str(&format!("\\let\\{prefix}@ul=\\underline"));
                }
                if let Some((r, g, b)) = rgb {
                    let (r, g, b) = (r as f64 / 255.0, g as f64 / 255.0, b as f64 / 255.0);
                    def.push_str(&format!(
                        "\\def\\{prefix}@tc##1{{\\textcolor[rgb]{{{r:.4},{g:.4},{b:.4}}}{{##1}}}}",
                        prefix = prefix,
                        r = r,
                        g = g,
                        b = b
                    ));
                } else {
                    // No color: reset the text-color slot to a no-op so only the
                    // style switches (if any) apply.
                    def.push_str(&format!("\\let\\{prefix}@tc=\\relax"));
                }
                w.write_all(
                    format!("\\@namedef{{{prefix}@tok@{name}}}{{{def}}}\n", prefix = prefix, name = name, def = def)
                        .as_bytes(),
                )?;
            }
        }
    }
    w.write_all(b"\\makeatother\n")?;
    Ok(())
}

/// Emit a complete, standalone LaTeX document wrapping the rendered `body` in a `Verbatim` block.
fn write_tex_document<W: io::Write>(
    w: &mut W,
    prefix: &str,
    theme: &Theme,
    style: HtmlStyling,
    body: &str,
) -> Result<()> {
    w.write_all(b"\\documentclass{article}\n")?;
    w.write_all(b"\\usepackage{fancyvrb}\n")?;
    w.write_all(b"\\usepackage{color}\n")?;
    w.write_all(b"\\usepackage[utf8]{inputenc}\n")?;
    w.write_all(b"\n")?;
    write_tex_preamble(w, prefix, theme, style)?;
    w.write_all(b"\\begin{document}\n")?;
    w.write_all(b"\n")?;
    w.write_all(
        b"\\begin{Verbatim}[commandchars=\\\\\\{\\},codes={\\catcode`\\$=3\\catcode`\\^=7\\catcode`\\_=8\\relax}]\n",
    )?;
    w.write_all(body.as_bytes())?;
    w.write_all(b"\\end{Verbatim}\n")?;
    w.write_all(b"\n")?;
    w.write_all(b"\\end{document}\n")?;
    Ok(())
}

/// Emit a complete, standalone LaTeX document wrapping each line of `body` in a two-column
/// `longtable` (line number + code), with leading whitespace preserved.
fn write_tex_linenumbers<W: io::Write>(
    w: &mut W,
    prefix: &str,
    theme: &Theme,
    style: HtmlStyling,
    body: &str,
) -> Result<()> {
    w.write_all(b"\\documentclass{article}\n")?;
    w.write_all(b"\\usepackage{fancyvrb}\n")?;
    w.write_all(b"\\usepackage{color}\n")?;
    w.write_all(b"\\usepackage[utf8]{inputenc}\n")?;
    w.write_all(b"\\usepackage{longtable}\n")?;
    w.write_all(b"\n")?;
    write_tex_preamble(w, prefix, theme, style)?;
    w.write_all(b"\\begin{document}\n")?;
    w.write_all(b"\n")?;
    w.write_all(b"\\begin{longtable}{rl}\n")?;
    let lines: Vec<&str> = body.split('\n').collect();
    // `render()` appends a trailing newline, so the final element is an empty string; skip it.
    let count = lines.len().saturating_sub(1);
    for (i, line) in lines.into_iter().take(count).enumerate() {
        w.write_all(format!("{} & \\Verb[commandchars=\\\\\\{{\\}},codes={{\\catcode`\\$=3\\catcode`\\^=7\\catcode`\\_=8\\relax}}]-{line}-\\\\\n", i + 1).as_bytes())?;
    }
    w.write_all(b"\\end{longtable}\n")?;
    w.write_all(b"\n")?;
    w.write_all(b"\\end{document}\n")?;
    Ok(())
}

fn terminal_supports_truecolor() -> bool {
    std::env::var("COLORTERM")
        .is_ok_and(|truecolor| truecolor == "truecolor" || truecolor == "24bit")
}

/// The kind of HTML emitted when highlighting to HTML.
#[derive(Debug, Clone, Copy, PartialEq, Eq, ValueEnum)]
pub enum HtmlOutput {
    /// A complete, self-contained document wrapping a plain
    /// `<div class="highlight"><pre><code>` block.
    Document,
    /// A complete document with a line-number column (a `<table>` layout).
    #[value(name = "line-numbers")]
    NumberedDocument,
    /// Only the code markup, without the surrounding document.
    Fragment,
}

/// How token colors are applied in HTML output.
#[derive(Debug, Clone, Copy, PartialEq, Eq, ValueEnum)]
pub enum HtmlStyling {
    /// `class="..."` spans plus a generated `<style>` carrying the theme's colors.
    Classes,
    /// `style="..."` spans with the colors inlined.
    Inline,
    /// `class="..."` spans with no colors emitted (supply your own stylesheet).
    Minimal,
}

/// The output format for highlighting.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum Formatter {
    /// ANSI-colored terminal output (the default).
    Terminal,
    /// HTML output, reusing `--layout`/`--style` for structure and styling.
    Html(HtmlOutput, HtmlStyling),
    /// TeX/LaTeX output, reusing `--layout`/`--style` for structure and styling.
    Latex(HtmlOutput, HtmlStyling),
}

pub struct HighlightOptions {
    pub theme: Theme,
    pub check: bool,
    pub captures_path: Option<PathBuf>,
    /// The output format, default `Formatter::Terminal`.
    pub formatter: Formatter,
    /// Command prefix for generated LaTeX macros (without a leading backslash), default "TS".
    pub prefix: String,
    /// Indices (into `theme.highlight_names`) of scopes whose contents use
    /// LaTeX math-mode escaping. Empty when `--math-escape` is not given.
    pub math_escape_indices: HashSet<usize>,
    pub quiet: bool,
    pub print_time: bool,
    pub cancellation_flag: Arc<AtomicUsize>,
    pub encoding: Option<TSInputEncoding>,
}

pub fn highlight(
    loader: &Loader,
    path: &Path,
    name: &str,
    config: &HighlightConfiguration,
    print_name: bool,
    opts: &HighlightOptions,
) -> Result<()> {
    if opts.check {
        let names = if let Some(path) = opts.captures_path.as_deref() {
            let file = fs::read_to_string(path)?;
            let capture_names = file
                .lines()
                .filter_map(|line| {
                    if line.trim().is_empty() || line.trim().starts_with(';') {
                        return None;
                    }
                    line.split(';').next().map(|s| s.trim().trim_matches('"'))
                })
                .collect::<HashSet<_>>();
            config.nonconformant_capture_names(&capture_names)
        } else {
            config.nonconformant_capture_names(&HashSet::new())
        };
        if names.is_empty() {
            info!("All highlight captures conform to standards.");
        } else {
            warn!(
                "Non-standard highlight {} detected:\n* {}",
                if names.len() > 1 {
                    "captures"
                } else {
                    "capture"
                },
                names.join("\n* ")
            );
        }
    }

    let source = fs::read(path)?;

    fn is_utf16_le_bom(bom_bytes: &[u8]) -> bool {
        bom_bytes == [0xFF, 0xFE]
    }

    fn is_utf16_be_bom(bom_bytes: &[u8]) -> bool {
        bom_bytes == [0xFE, 0xFF]
    }

    let encoding = match opts.encoding {
        None if source.len() >= 2 => {
            if is_utf16_le_bom(&source[0..2]) {
                Some(ffi::TSInputEncodingUTF16LE)
            } else if is_utf16_be_bom(&source[0..2]) {
                Some(ffi::TSInputEncodingUTF16BE)
            } else {
                None
            }
        }
        _ => opts.encoding,
    };

    let stdout = io::stdout();
    let mut stdout = stdout.lock();
    let time = Instant::now();
    let mut highlighter = Highlighter::new();
    let events = highlighter.highlight(
        config,
        &source,
        encoding,
        Some(&opts.cancellation_flag),
        |string| loader.highlight_config_for_injection_string(string),
    )?;
    let theme = &opts.theme;

    // A fragment is pure code markup, so it must not be prefixed with the filename.
    let html_fragment = matches!(
        opts.formatter,
        Formatter::Html(layout, _) if layout == HtmlOutput::Fragment
    );
    if !opts.quiet && print_name && !html_fragment {
        writeln!(&mut stdout, "{name}")?;
    }

    match &opts.formatter {
        Formatter::Html(layout, style) => {
            if !opts.quiet && *layout != HtmlOutput::Fragment {
                writeln!(&mut stdout, "{HTML_HEAD_HEADER}")?;
                if *layout == HtmlOutput::NumberedDocument {
                    writeln!(&mut stdout, "{HTML_LINE_NUMBER_STYLE}")?;
                }
                if *style == HtmlStyling::Classes {
                    for (name, style) in theme.highlight_names.iter().zip(&theme.styles) {
                        if let Some(css) = &style.css {
                            writeln!(&mut stdout, "    .{name} {{ {css}; }}")?;
                        }
                    }
                }
                writeln!(&mut stdout, "  </style>")?;
                writeln!(&mut stdout, "{HTML_BODY_HEADER}")?;
            }

            let mut renderer = HtmlRenderer::new();
            renderer.render(events, &source, &move |highlight, output| {
                if *style == HtmlStyling::Inline {
                    output.extend(b"style='");
                    output.extend(
                        theme.styles[highlight.0]
                            .css
                            .as_ref()
                            .map_or_else(|| "".as_bytes(), |css_style| css_style.as_bytes()),
                    );
                } else {
                    output.extend(b"class='");
                    let mut parts = theme.highlight_names[highlight.0].split('.').peekable();
                    while let Some(part) = parts.next() {
                        output.extend(part.as_bytes());
                        if parts.peek().is_some() {
                            output.extend(b" ");
                        }
                    }
                }
                output.extend(b"'");
            })?;

            if !opts.quiet {
                if *layout == HtmlOutput::NumberedDocument {
                    writeln!(&mut stdout, "<table>")?;
                    for (i, line) in renderer.lines().enumerate() {
                        writeln!(
                            &mut stdout,
                            "<tr><td class=line-number>{}</td><td class=line>{line}</td></tr>",
                            i + 1,
                        )?;
                    }
                    writeln!(&mut stdout, "</table>")?;
                } else {
                    let mut body = renderer.lines().collect::<String>();
                    if body.ends_with('\n') {
                        body.pop();
                    }
                    writeln!(
                        &mut stdout,
                        "<div class=\"highlight\">\n<pre><code>{body}</code></pre>\n</div>",
                    )?;
                }
                if *layout != HtmlOutput::Fragment {
                    writeln!(&mut stdout, "{HTML_FOOTER}")?;
                }
            }
        }

        Formatter::Latex(layout, style) => {
            let prefix = &opts.prefix; // already trimmed of leading backslash in main.rs
            let mut renderer = TexRenderer::new(prefix.clone(), opts.math_escape_indices.clone());
            let attribute_callback = |highlight: Highlight, output: &mut Vec<u8>| {
                let name = theme.highlight_names[highlight.0].as_bytes();
                match style {
                    HtmlStyling::Inline => {
                        // Open a single group; within it emit font switches
                        // (`\bf`/`\it`) and a color command (no extra group of
                        // its own). `end_highlight` closes the group with a
                        // single `}`, keeping the brace balance automatic.
                        output.push(b'{');
                        let (italic, bold, _underline) =
                            style_flags(theme.styles[highlight.0].ansi);
                        if bold {
                            output.extend(b"\\bf");
                        }
                        if italic {
                            output.extend(b"\\it");
                        }
                        if let Some((r, g, b)) = style_rgb(theme.styles[highlight.0].ansi) {
                            let (r, g, b) = (r as f64 / 255.0, g as f64 / 255.0, b as f64 / 255.0);
                            write!(output, "\\color[rgb]{{{r:.4},{g:.4},{b:.4}}}").unwrap();
                        }
                    }
                    HtmlStyling::Classes | HtmlStyling::Minimal => {
                        output.extend(b"\\");
                        output.extend(prefix.as_bytes());
                        output.extend(b"{");
                        output.extend(name);
                        output.extend(b"}{");
                    }
                }
            };
            renderer.render(events, &source, &attribute_callback)?;

            let body = String::from_utf8(renderer.content().clone()).unwrap();
            match layout {
                HtmlOutput::Fragment => {
                    write!(&mut stdout, "{body}")?;
                }
                HtmlOutput::Document => {
                    write_tex_document(&mut stdout, &opts.prefix, theme, *style, &body)?;
                }
                HtmlOutput::NumberedDocument => {
                    write_tex_linenumbers(&mut stdout, &opts.prefix, theme, *style, &body)?;
                }
            }
        }

        Formatter::Terminal => {
            let styles: Vec<anstyle::Style> = theme.styles.iter().map(|style| style.ansi).collect();
            let mut renderer = TerminalRenderer::new(&styles, theme.default_style().ansi);
            renderer.render(events, &source, &|_highlight, _output| {})?;
            stdout.write_all(renderer.content())?;
        }
    }

    if opts.print_time {
        info!("Time: {}ms", time.elapsed().as_millis());
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
        unsafe { env::set_var("COLORTERM", "") };
        parse_style(&mut style, Value::String(DARK_CYAN.to_string()));
        assert_eq!(
            style.ansi.get_fg_color(),
            Some(Color::Ansi256(Ansi256Color(36)))
        );
        assert_eq!(style.css, Some("color: #00af87".to_string()));

        // junglegreen is not an ANSI color and is preserved when the terminal supports it
        unsafe { env::set_var("COLORTERM", "truecolor") };
        parse_style(&mut style, Value::String(JUNGLE_GREEN.to_string()));
        assert_eq!(
            style.ansi.get_fg_color(),
            Some(Color::Rgb(RgbColor(38, 166, 154)))
        );
        assert_eq!(style.css, Some("color: #26a69a".to_string()));

        // junglegreen gets approximated as cadetblue when the terminal does not support it
        unsafe { env::set_var("COLORTERM", "") };
        parse_style(&mut style, Value::String(JUNGLE_GREEN.to_string()));
        assert_eq!(
            style.ansi.get_fg_color(),
            Some(Color::Ansi256(Ansi256Color(72)))
        );
        assert_eq!(style.css, Some("color: #26a69a".to_string()));

        if let Ok(environment_variable) = original_environment_variable {
            unsafe { env::set_var("COLORTERM", environment_variable) };
        } else {
            unsafe { env::remove_var("COLORTERM") };
        }
    }

    /// Build a one-scope theme (color is optional) with the given flags,
    /// returning the parsed inner `anstyle::Style`.
    fn style_with(
        name: &str,
        color: Option<&str>,
        bold: bool,
        italic: bool,
        underline: bool,
    ) -> anstyle::Style {
        let mut json = serde_json::Map::new();
        if let Some(c) = color {
            json.insert("color".into(), Value::String(c.to_string()));
        }
        if bold {
            json.insert("bold".into(), Value::Bool(true));
        }
        if italic {
            json.insert("italic".into(), Value::Bool(true));
        }
        if underline {
            json.insert("underline".into(), Value::Bool(true));
        }
        let theme: Theme =
            serde_json::from_value(json!({ name: Value::Object(json) })).unwrap();
        theme.styles[0].ansi
    }

    #[test]
    fn test_latex_classes_style_switches() {
        // keyword: color + italic; parameter: color + underline;
        // constant: color + bold; comment: italic only (no color).
        let theme = Theme {
            highlight_names: vec![
                "keyword".into(),
                "variable.parameter".into(),
                "constant.builtin".into(),
                "comment".into(),
            ],
            styles: vec![
                Style { ansi: style_with("keyword", Some("#3d7a7a"), false, true, false), css: None },
                Style { ansi: style_with("variable.parameter", Some("#fcfcfc"), false, false, true), css: None },
                Style { ansi: style_with("constant.builtin", Some("#5f00af"), true, false, false), css: None },
                Style { ansi: style_with("comment", None, false, true, false), css: None },
            ],
        };
        let mut buf = Vec::new();
        write_tex_preamble(&mut buf, "TS", &theme, HtmlStyling::Classes).unwrap();
        let out = String::from_utf8(buf).unwrap();

        // italic emits \let\TS@it=\textit before the color definition.
        assert!(
            out.contains("\\@namedef{TS@tok@keyword}{\\let\\TS@it=\\textit\\def\\TS@tc##1{\\textcolor[rgb]{0.2392,0.4784,0.4784}{##1}}}"),
            "keyword namedef missing italic switch:\n{out}"
        );
        // underline emits \let\TS@ul=\underline.
        assert!(
            out.contains("\\@namedef{TS@tok@variable.parameter}{\\let\\TS@ul=\\underline\\def\\TS@tc##1{\\textcolor[rgb]{0.9882,0.9882,0.9882}{##1}}}"),
            "parameter namedef missing underline switch:\n{out}"
        );
        // bold emits \let\TS@bf=\textbf.
        assert!(
            out.contains("\\@namedef{TS@tok@constant.builtin}{\\let\\TS@bf=\\textbf\\def\\TS@tc##1{\\textcolor[rgb]{0.3725,0.0000,0.6863}{##1}}}"),
            "constant namedef missing bold switch:\n{out}"
        );
        // No color: only the italic switch, with @tc reset to \relax.
        assert!(
            out.contains("\\@namedef{TS@tok@comment}{\\let\\TS@it=\\textit\\let\\TS@tc=\\relax}"),
            "comment namedef (no color) wrong:\n{out}"
        );
    }

    #[test]
    fn test_latex_inline_style_switches() {
        // Replicate the inline attribute_callback for a bold+italic+color scope.
        let style = style_with("kw", Some("#3d7a7a"), true, true, false);
        let (italic, bold, _underline) = style_flags(style);

        let mut output: Vec<u8> = Vec::new();
        output.push(b'{');
        if bold {
            output.extend(b"\\bf");
        }
        if italic {
            output.extend(b"\\it");
        }
        if let Some((r, g, b)) = style_rgb(style) {
            let (r, g, b) = (r as f64 / 255.0, g as f64 / 255.0, b as f64 / 255.0);
            write!(
                output,
                "\\color[rgb]{{{r:.4},{g:.4},{b:.4}}}"
            )
            .unwrap();
        }
        // The renderer closes the single group with one `}`.
        output.extend(b"}");

        let out = String::from_utf8(output).unwrap();
        assert_eq!(
            out,
            "{\\bf\\it\\color[rgb]{0.2392,0.4784,0.4784}}",
            "inline markup mismatch: {out}"
        );
    }

    #[test]
    fn test_latex_inline_no_style_opens_single_group() {
        let style = style_with("plain", Some("#abcdef"), false, false, false);
        let (italic, bold, _underline) = style_flags(style);

        let mut output: Vec<u8> = Vec::new();
        output.push(b'{');
        if bold {
            output.extend(b"\\bf");
        }
        if italic {
            output.extend(b"\\it");
        }
        if let Some((r, g, b)) = style_rgb(style) {
            let (r, g, b) = (r as f64 / 255.0, g as f64 / 255.0, b as f64 / 255.0);
            write!(output, "\\color[rgb]{{{r:.4},{g:.4},{b:.4}}}").unwrap();
        }
        output.extend(b"}");

        assert_eq!(
            String::from_utf8(output).unwrap(),
            "{\\color[rgb]{0.6706,0.8039,0.9373}}"
        );
    }
}
