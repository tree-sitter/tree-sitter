#[derive(Debug)]
pub enum Error {
    GrammarError(String),
    SymbolError(String),
    RegexError(String),
}

pub type Result<T> = std::result::Result<T, Error>;

impl Error {
    pub fn grammar(message: &str) -> Self {
        Error::GrammarError(message.to_string())
    }

    pub fn regex(message: &str) -> Self {
        Error::RegexError(message.to_string())
    }
}

impl From<serde_json::Error> for Error {
    fn from(error: serde_json::Error) -> Self {
        Error::GrammarError(error.to_string())
    }
}
