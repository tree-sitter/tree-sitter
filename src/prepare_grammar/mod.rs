mod expand_repeats;
mod expand_tokens;
mod extract_simple_aliases;
mod extract_tokens;
mod flatten_grammar;
mod intern_symbols;

use self::expand_repeats::expand_repeats;
use self::expand_tokens::expand_tokens;
use self::extract_simple_aliases::extract_simple_aliases;
use self::extract_tokens::extract_tokens;
use self::flatten_grammar::flatten_grammar;
use self::intern_symbols::intern_symbols;
use crate::error::Result;
use crate::grammars::{ExternalToken, InputGrammar, LexicalGrammar, SyntaxGrammar, Variable};
use crate::rules::{AliasMap, Rule, Symbol};

pub(self) struct IntermediateGrammar<T, U> {
    variables: Vec<Variable>,
    extra_tokens: Vec<T>,
    expected_conflicts: Vec<Vec<Symbol>>,
    external_tokens: Vec<U>,
    variables_to_inline: Vec<Symbol>,
    word_token: Option<Symbol>,
}

pub(self) type InternedGrammar = IntermediateGrammar<Rule, Variable>;

pub(self) type ExtractedSyntaxGrammar = IntermediateGrammar<Symbol, ExternalToken>;

#[derive(Debug, PartialEq, Eq)]
pub(self) struct ExtractedLexicalGrammar {
    variables: Vec<Variable>,
    separators: Vec<Rule>,
}

pub(crate) fn prepare_grammar(
    input_grammar: &InputGrammar,
) -> Result<(SyntaxGrammar, LexicalGrammar, AliasMap)> {
    let interned_grammar = intern_symbols(input_grammar)?;
    let (syntax_grammar, lexical_grammar) = extract_tokens(interned_grammar)?;
    let syntax_grammar = expand_repeats(syntax_grammar);
    let mut syntax_grammar = flatten_grammar(syntax_grammar)?;
    let lexical_grammar = expand_tokens(lexical_grammar)?;
    let simple_aliases = extract_simple_aliases(&mut syntax_grammar, &lexical_grammar);
    Ok((syntax_grammar, lexical_grammar, simple_aliases))
}
