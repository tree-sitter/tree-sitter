use std::io;
use std::sync::atomic::{AtomicUsize, Ordering};
use std::sync::Arc;
use std::thread;
use tree_sitter::Parser;

#[cfg(unix)]
use std::path::PathBuf;
#[cfg(unix)]
use std::process::{Child, ChildStdin, Command, Stdio};

#[cfg(unix)]
const HTML_HEADER: &[u8] = b"<!DOCTYPE html>\n<style>svg { width: 100%; }</style>\n\n";

pub fn cancel_on_stdin() -> Arc<AtomicUsize> {
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
#[cfg(windows)]
pub struct LogSession();

#[cfg(unix)]
pub struct LogSession(PathBuf, Option<Child>, Option<ChildStdin>);

#[cfg(windows)]
pub fn log_graphs(_parser: &mut Parser, _path: &str) -> std::io::Result<LogSession> {
    Ok(LogSession())
}

#[cfg(unix)]
pub fn log_graphs(parser: &mut Parser, path: &str) -> std::io::Result<LogSession> {
    use std::io::Write;

    let mut dot_file = std::fs::File::create(path)?;
    dot_file.write(HTML_HEADER)?;
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
    Ok(LogSession(
        PathBuf::from(path),
        Some(dot_process),
        Some(dot_stdin),
    ))
}

#[cfg(unix)]
impl Drop for LogSession {
    fn drop(&mut self) {
        use std::fs;

        drop(self.2.take().unwrap());
        let output = self.1.take().unwrap().wait_with_output().unwrap();
        if output.status.success() {
            if cfg!(target_os = "macos")
                && fs::metadata(&self.0).unwrap().len() > HTML_HEADER.len() as u64
            {
                Command::new("open").arg(&self.0).output().unwrap();
            }
        } else {
            eprintln!(
                "Dot failed: {} {}",
                String::from_utf8_lossy(&output.stdout),
                String::from_utf8_lossy(&output.stderr)
            );
        }
    }
}
