use crate::error::Result;
use crate::grammars::LexicalGrammar;
use super::{InternedGrammar, ExtractedGrammar};

pub(super) fn extract_tokens(grammar: InternedGrammar) -> Result<(ExtractedGrammar, LexicalGrammar)> {
    unimplemented!();
}
