#[derive(Debug)]
pub struct Error(pub String);

pub type Result<T> = std::result::Result<T, Error>;

impl Error {
    pub fn grammar(message: &str) -> Self {
        Error(format!("Grammar error: {}", message))
    }

    pub fn regex(message: &str) -> Self {
        Error(format!("Regex error: {}", message))
    }

    pub fn undefined_symbol(name: &str) -> Self {
        Error(format!("Undefined symbol `{}`", name))
    }
}

impl From<serde_json::Error> for Error {
    fn from(error: serde_json::Error) -> Self {
        Error(error.to_string())
    }
}
