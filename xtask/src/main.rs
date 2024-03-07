use anstyle::{AnsiColor, Color, Style};
use clap::{crate_authors, CommandFactory, FromArgMatches, Parser, Subcommand};
use semver::Version;

mod benchmark;
mod clippy;
mod fixtures;
mod version;

#[derive(Parser)]
#[command(name = "cargo xtask", about="Run various tasks for tree-sitter", author=crate_authors!("\n"), styles=get_styles())]
struct Args {
    #[command(subcommand)]
    command: CliCommand,
}

#[derive(Subcommand)]
enum CliCommand {
    /// Runs `cargo clippy`.
    Clippy(Clippy),
    /// Bumps the version of the workspace.
    BumpVersion(BumpVersion),
    /// Runs `cargo benchmark` with some optional environment variables set.
    Benchmark(Benchmark),
    /// Fetches the fixtures for testing tree-sitter.
    FetchFixtures,
    GenerateBindings,
}

#[derive(Parser)]
struct Clippy {
    /// Automatically apply lint suggestions (`clippy --fix`).
    #[arg(long)]
    fix: bool,

    /// The package to run Clippy against (`cargo -p <PACKAGE> clippy`).
    #[arg(long, short)]
    package: Option<String>,
}

#[derive(Parser)]
struct BumpVersion {
    /// The version to bump to.
    #[arg(long, short)]
    version: Option<Version>,
}

#[derive(Parser)]
struct Benchmark {
    /// The language to run the benchmarks for.
    #[arg(long, short)]
    language: Option<String>,
    /// The example file to run the benchmarks for.
    #[arg(long, short)]
    example_file_name: Option<String>,
    /// The number of times to parse each sample (default is 5).
    #[arg(long, short, default_value = "5")]
    repetition_count: u32,
    /// Whether to run the benchmarks in debug mode.
    #[arg(short = 'g', long)]
    debug: bool,
}

const BUILD_VERSION: &str = env!("CARGO_PKG_VERSION");
const BUILD_SHA: Option<&'static str> = option_env!("BUILD_SHA");

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let version = BUILD_SHA.map_or_else(
        || BUILD_VERSION.to_string(),
        |build_sha| format!("{BUILD_VERSION} ({build_sha})"),
    );
    let version: &'static str = Box::leak(version.into_boxed_str());

    let app = Args::command()
        .help_template(
            "\
{before-help}{name} {version}
{author-with-newline}{about-with-newline}
{usage-heading} {usage}

{all-args}{after-help}
",
        )
        .version(version)
        .subcommand_required(true)
        .arg_required_else_help(true)
        .disable_help_subcommand(true)
        .disable_colored_help(false);

    let mut matches = app.get_matches();
    let args = Args::from_arg_matches_mut(&mut matches)?;

    match args.command {
        CliCommand::Clippy(clippy_args) => {
            clippy::run(&clippy_args)?;
        }
        CliCommand::BumpVersion(bump_version) => {
            version::bump(bump_version.version)?;
        }
        CliCommand::Benchmark(benchmark_args) => {
            benchmark::run(&benchmark_args)?;
        }
        CliCommand::FetchFixtures => {
            fixtures::fetch()?;
        }
        CliCommand::GenerateBindings => {
            bindings::generate()?;
        }
    }

    Ok(())
}

#[must_use]
const fn get_styles() -> clap::builder::Styles {
    clap::builder::Styles::styled()
        .usage(
            Style::new()
                .bold()
                .fg_color(Some(Color::Ansi(AnsiColor::Yellow))),
        )
        .header(
            Style::new()
                .bold()
                .fg_color(Some(Color::Ansi(AnsiColor::Yellow))),
        )
        .literal(Style::new().fg_color(Some(Color::Ansi(AnsiColor::Green))))
        .invalid(
            Style::new()
                .bold()
                .fg_color(Some(Color::Ansi(AnsiColor::Red))),
        )
        .error(
            Style::new()
                .bold()
                .fg_color(Some(Color::Ansi(AnsiColor::Red))),
        )
        .valid(
            Style::new()
                .bold()
                .fg_color(Some(Color::Ansi(AnsiColor::Green))),
        )
        .placeholder(Style::new().fg_color(Some(Color::Ansi(AnsiColor::White))))
}
