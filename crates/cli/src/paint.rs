use anstyle::{AnsiColor, Color, Style};

pub const RED: Style = Style::new().fg_color(Some(Color::Ansi(AnsiColor::Red)));
pub const YELLOW: Style = Style::new().fg_color(Some(Color::Ansi(AnsiColor::Yellow)));

/// Wraps a `Display` value with a style; emits ANSI codes only when
/// [`color_enabled`] is true.
pub struct Paint<T>(pub Style, pub T);

pub fn color_enabled() -> bool {
    static ENABLED: std::sync::OnceLock<bool> = std::sync::OnceLock::new();
    *ENABLED.get_or_init(|| std::env::var_os("NO_COLOR").is_none_or(|v| v.is_empty()))
}

pub fn paint_opt<T>(color: Option<impl Into<Color>>, text: T) -> Paint<T> {
    Paint(Style::new().fg_color(color.map(Into::into)), text)
}

impl<T: std::fmt::Display> std::fmt::Display for Paint<T> {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        if color_enabled() {
            write!(f, "{}{}{:#}", self.0, self.1, self.0)
        } else {
            self.1.fmt(f)
        }
    }
}
