use std::process::Command;

use anyhow::{bail, Context, Result};

use crate::Clippy;

pub fn run(args: &Clippy) -> Result<()> {
    let cargo = std::env::var("CARGO").unwrap_or_else(|_| "cargo".to_string());

    let mut clippy_command = Command::new(&cargo);
    clippy_command.arg("clippy");

    if let Some(package) = args.package.as_ref() {
        clippy_command.args(["--package", package]);
    } else {
        clippy_command.arg("--workspace");
    }

    clippy_command
        .arg("--release")
        .arg("--all-targets")
        .arg("--all-features");

    if args.fix {
        clippy_command.arg("--fix");
    }

    clippy_command.arg("--");

    // Deny all warnings.
    clippy_command.args(["--deny", "warnings"]);

    // Deny `dbg!` and `todo!`s.
    clippy_command
        .args(["--deny", "clippy::dbg_macro"])
        .args(["--deny", "clippy::todo"]);

    // Warn `pedantic` and `nursery`
    clippy_command
        .args(["--warn", "clippy::pedantic"])
        .args(["--warn", "clippy::nursery"]);

    /// These are all of the rules that are currently allowed in the tree-sitter codebase.
    /// These are allowed because they contain false-positives, are unnecessary, or worsen the code.
    const RULES_TO_ALLOW: &[&str] = &[
        "clippy::branches_sharing_code",
        "clippy::cast_lossless",
        "clippy::cast_possible_truncation",
        "clippy::cast_possible_wrap",
        "clippy::cast_precision_loss",
        "clippy::cast_sign_loss",
        "clippy::cognitive_complexity",
        "clippy::collection_is_never_read",
        "clippy::fallible_impl_from",
        "clippy::fn_params_excessive_bools",
        "clippy::inline_always",
        "clippy::if_not_else",
        "clippy::items_after_statements",
        "clippy::match_wildcard_for_single_variants",
        "clippy::missing_errors_doc",
        "clippy::missing_panics_doc",
        "clippy::module_name_repetitions",
        "clippy::option_if_let_else",
        "clippy::range_plus_one",
        "clippy::redundant_clone",
        "clippy::similar_names",
        "clippy::string_lit_as_bytes",
        "clippy::struct_excessive_bools",
        "clippy::struct_field_names",
        "clippy::too_many_lines",
        "clippy::unnecessary_wraps",
        "clippy::unused_self",
    ];

    for rule in RULES_TO_ALLOW {
        clippy_command.args(["--allow", rule]);
    }

    eprintln!(
        "running: {cargo} {}",
        clippy_command
            .get_args()
            .map(|arg| arg.to_str().unwrap())
            .collect::<Vec<_>>()
            .join(" ")
    );

    let exit_status = clippy_command
        .spawn()
        .context("failed to spawn child process")?
        .wait()
        .context("failed to wait for child process")?;

    if !exit_status.success() {
        bail!("clippy failed: {exit_status}");
    }

    Ok(())
}
