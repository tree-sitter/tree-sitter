mod bump;

use bump::bump_versions;

fn print_help() {
    println!(
        "
xtask must specify a task to run.

Usage: `cargo xtask <task>`

Tasks:
    bump-version
"
    );
}

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let Some(task) = std::env::args().nth(1) else {
        print_help();
        std::process::exit(0);
    };

    match task.as_str() {
        "bump-version" => {
            bump_versions()?;
        }
        _ => {
            println!("invalid task: {task}");
            std::process::exit(1);
        }
    }

    Ok(())
}
