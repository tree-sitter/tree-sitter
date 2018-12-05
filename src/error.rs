#[derive(Debug)]
pub enum Error {
    GrammarError(String),
    SymbolError(String),
}

pub type Result<T> = std::result::Result<T, Error>;

impl From<serde_json::Error> for Error {
    fn from(error: serde_json::Error) -> Self {
        Error::GrammarError(error.to_string())
    }
}
