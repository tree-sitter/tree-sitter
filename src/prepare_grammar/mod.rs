mod intern_symbols;
mod extract_tokens;
mod expand_repeats;
mod flatten_grammar;
mod normalize_rules;
mod extract_simple_aliases;

use crate::rules::{AliasMap, Rule, Symbol};
use crate::grammars::{InputGrammar, SyntaxGrammar, LexicalGrammar, InputVariable, ExternalToken};
use crate::error::Result;
use self::intern_symbols::intern_symbols;
use self::extract_tokens::extract_tokens;
use self::expand_repeats::expand_repeats;
use self::flatten_grammar::flatten_grammar;
use self::normalize_rules::normalize_rules;
use self::extract_simple_aliases::extract_simple_aliases;

pub(self) struct IntermediateGrammar<T, U> {
    variables: Vec<InputVariable>,
    extra_tokens: Vec<T>,
    expected_conflicts: Vec<Vec<Symbol>>,
    external_tokens: Vec<U>,
    variables_to_inline: Vec<Symbol>,
    word_token: Option<Symbol>,
}

pub(self) type InternedGrammar = IntermediateGrammar<Rule, InputVariable>;
pub(self) type ExtractedGrammar = IntermediateGrammar<Symbol, ExternalToken>;

pub fn prepare_grammar(
    input_grammar: &InputGrammar
) -> Result<(SyntaxGrammar, LexicalGrammar, AliasMap)> {
    let interned_grammar = intern_symbols(input_grammar)?;
    let (syntax_grammar, lexical_grammar) = extract_tokens(interned_grammar)?;
    let syntax_grammar = expand_repeats(syntax_grammar);
    let mut syntax_grammar = flatten_grammar(syntax_grammar)?;
    let mut lexical_grammar = normalize_rules(lexical_grammar);
    let simple_aliases = extract_simple_aliases(&mut syntax_grammar, &mut lexical_grammar);
    Ok((syntax_grammar, lexical_grammar, simple_aliases))
}
