use std::io::Write;

use anstyle::{AnsiColor, Color, Style};
use log::{Level, LevelFilter, Log, Metadata, Record};

pub fn paint(color: Option<impl Into<Color>>, text: &str) -> String {
    let style = Style::new().fg_color(color.map(Into::into));
    format!("{style}{text}{style:#}")
}

struct Logger;

impl Log for Logger {
    fn enabled(&self, _: &Metadata) -> bool {
        true
    }

    fn log(&self, record: &Record) {
        match record.level() {
            Level::Error => eprintln!(
                "{} {}",
                paint(Some(AnsiColor::Red), "Error:"),
                record.args()
            ),
            Level::Warn => eprintln!(
                "{} {}",
                paint(Some(AnsiColor::Yellow), "Warning:"),
                record.args()
            ),
            Level::Info | Level::Debug => eprintln!("{}", record.args()),
            Level::Trace => eprintln!(
                "[{}] {}",
                record
                    .module_path()
                    .unwrap_or_default()
                    .trim_start_matches("rust_tree_sitter_cli::"),
                record.args()
            ),
        }
    }

    fn flush(&self) {
        let mut stderr = std::io::stderr().lock();
        let _ = stderr.flush();
    }
}

pub fn init() {
    log::set_boxed_logger(Box::new(Logger {})).unwrap();
    log::set_max_level(LevelFilter::Info);
}

pub fn enable_debug() {
    log::set_max_level(LevelFilter::Debug);
}
