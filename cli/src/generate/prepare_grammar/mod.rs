mod expand_repeats;
mod expand_tokens;
mod extract_simple_aliases;
mod extract_tokens;
mod flatten_grammar;
mod intern_symbols;
mod process_inlines;

use self::expand_repeats::expand_repeats;
pub(crate) use self::expand_tokens::expand_tokens;
use self::extract_simple_aliases::extract_simple_aliases;
use self::extract_tokens::extract_tokens;
use self::flatten_grammar::flatten_grammar;
use self::intern_symbols::intern_symbols;
use self::process_inlines::process_inlines;
use crate::error::Result;
use crate::generate::grammars::{
    ExternalToken, InlinedProductionMap, InputGrammar, LexicalGrammar, SyntaxGrammar, Variable,
};
use crate::generate::rules::{AliasMap, Rule, Symbol};

pub(crate) struct IntermediateGrammar<T, U> {
    variables: Vec<Variable>,
    extra_symbols: Vec<T>,
    expected_conflicts: Vec<Vec<Symbol>>,
    external_tokens: Vec<U>,
    variables_to_inline: Vec<Symbol>,
    supertype_symbols: Vec<Symbol>,
    word_token: Option<Symbol>,
}

pub(crate) type InternedGrammar = IntermediateGrammar<Rule, Variable>;

pub(crate) type ExtractedSyntaxGrammar = IntermediateGrammar<Symbol, ExternalToken>;

#[derive(Debug, PartialEq, Eq)]
pub(crate) struct ExtractedLexicalGrammar {
    pub variables: Vec<Variable>,
    pub separators: Vec<Rule>,
}

pub(crate) fn prepare_grammar(
    input_grammar: &InputGrammar,
) -> Result<(
    SyntaxGrammar,
    LexicalGrammar,
    InlinedProductionMap,
    AliasMap,
)> {
    let interned_grammar = intern_symbols(input_grammar)?;
    let (syntax_grammar, lexical_grammar) = extract_tokens(interned_grammar)?;
    let syntax_grammar = expand_repeats(syntax_grammar);
    let mut syntax_grammar = flatten_grammar(syntax_grammar)?;
    let lexical_grammar = expand_tokens(lexical_grammar)?;
    let simple_aliases = extract_simple_aliases(&mut syntax_grammar, &lexical_grammar);
    let inlines = process_inlines(&syntax_grammar);
    Ok((syntax_grammar, lexical_grammar, inlines, simple_aliases))
}
