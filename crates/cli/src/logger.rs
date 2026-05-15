use std::io::Write;

use log::{Level, LevelFilter, Log, Metadata, Record};

use crate::paint::{Paint, RED, YELLOW};

struct Logger;

impl Log for Logger {
    fn enabled(&self, _: &Metadata) -> bool {
        true
    }

    fn log(&self, record: &Record) {
        match record.level() {
            Level::Error => eprintln!("{} {}", Paint(RED, "Error:"), record.args()),
            Level::Warn => eprintln!("{} {}", Paint(YELLOW, "Warning:"), record.args()),
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
