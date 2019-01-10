use std::fs::File;
use std::io::{Result, Write};
use std::process::{Child, ChildStdin, Command, Stdio};
use std::str;
use tree_sitter::Parser;

#[cfg(windows)]
pub(crate) struct LogSession();

#[cfg(windows)]
pub(crate) fn start_logging_graphs(parser: &mut Parser, path: &str) -> Result<LogSession> {
    Ok(LogSession())
}

#[cfg(windows)]
pub(crate) fn stop_logging_graphs(parser: &mut Parser, mut session: LogSession) -> Result<()> {
    Ok(())
}

#[cfg(unix)]
pub(crate) struct LogSession(Child, ChildStdin);

#[cfg(unix)]
pub(crate) fn start_logging_graphs(parser: &mut Parser, path: &str) -> Result<LogSession> {
    let mut dot_file = File::create(path)?;
    dot_file.write(b"<!DOCTYPE html>\n<style>svg { width: 100%; }</style>\n\n")?;
    let mut dot_process = Command::new("dot")
        .arg("-Tsvg")
        .stdin(Stdio::piped())
        .stdout(dot_file)
        .spawn()
        .expect("Failed to run Dot");
    let dot_stdin = dot_process
        .stdin
        .take()
        .expect("Failed to open stdin for Dot");

    parser.print_dot_graphs(&dot_stdin);

    Ok(LogSession(dot_process, dot_stdin))
}

#[cfg(unix)]
pub(crate) fn stop_logging_graphs(parser: &mut Parser, mut session: LogSession) -> Result<()> {
    drop(session.1);

    if cfg!(unix) {
        parser.stop_printing_dot_graphs();
    }

    session.0.wait()?;

    if cfg!(target_os = "macos") {
        Command::new("open").arg("log.html").output()?;
    }

    Ok(())
}
