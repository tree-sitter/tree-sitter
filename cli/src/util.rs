use anyhow::Result;
use std::io;
use std::sync::atomic::{AtomicUsize, Ordering};
use std::sync::Arc;
use std::thread;
use tree_sitter::{Parser, Tree};

#[cfg(unix)]
use anyhow::{anyhow, Context};
#[cfg(unix)]
use std::path::PathBuf;
#[cfg(unix)]
use std::process::{Child, ChildStdin, Command, Stdio};

#[cfg(unix)]
const HTML_HEADER: &[u8] = b"
<!DOCTYPE html>

<style>
svg { width: 100%; }
</style>

";

pub fn cancel_on_stdin() -> Arc<AtomicUsize> {
    let result = Arc::new(AtomicUsize::new(0));
    if atty::is(atty::Stream::Stdin) {
        thread::spawn({
            let flag = result.clone();
            move || {
                let mut line = String::new();
                io::stdin().read_line(&mut line).unwrap();
                flag.store(1, Ordering::Relaxed);
            }
        });
    }
    result
}

#[cfg(windows)]
pub struct LogSession;

#[cfg(unix)]
pub struct LogSession {
    path: PathBuf,
    dot_process: Option<Child>,
    dot_process_stdin: Option<ChildStdin>,
}

#[cfg(windows)]
pub fn print_tree_graph(_tree: &Tree, _path: &str) -> Result<()> {
    Ok(())
}

#[cfg(windows)]
pub fn log_graphs(_parser: &mut Parser, _path: &str) -> Result<LogSession> {
    Ok(LogSession)
}

#[cfg(unix)]
pub fn print_tree_graph(tree: &Tree, path: &str) -> Result<()> {
    let session = LogSession::new(path)?;
    tree.print_dot_graph(session.dot_process_stdin.as_ref().unwrap());
    Ok(())
}

#[cfg(unix)]
pub fn log_graphs(parser: &mut Parser, path: &str) -> Result<LogSession> {
    let session = LogSession::new(path)?;
    parser.print_dot_graphs(session.dot_process_stdin.as_ref().unwrap());
    Ok(session)
}

#[cfg(unix)]
impl LogSession {
    fn new(path: &str) -> Result<Self> {
        use std::io::Write;

        let mut dot_file = std::fs::File::create(path)?;
        dot_file.write(HTML_HEADER)?;
        let mut dot_process = Command::new("dot")
            .arg("-Tsvg")
            .stdin(Stdio::piped())
            .stdout(dot_file)
            .spawn()
            .with_context(|| {
                "Failed to run the `dot` command. Check that graphviz is installed."
            })?;
        let dot_stdin = dot_process
            .stdin
            .take()
            .ok_or_else(|| anyhow!("Failed to open stdin for `dot` process."))?;
        Ok(Self {
            path: PathBuf::from(path),
            dot_process: Some(dot_process),
            dot_process_stdin: Some(dot_stdin),
        })
    }
}

#[cfg(unix)]
impl Drop for LogSession {
    fn drop(&mut self) {
        use std::fs;

        drop(self.dot_process_stdin.take().unwrap());
        let output = self.dot_process.take().unwrap().wait_with_output().unwrap();
        if output.status.success() {
            if cfg!(target_os = "macos")
                && fs::metadata(&self.path).unwrap().len() > HTML_HEADER.len() as u64
            {
                Command::new("open").arg(&self.path).output().unwrap();
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
