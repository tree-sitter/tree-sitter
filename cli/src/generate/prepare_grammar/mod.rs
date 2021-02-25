mod expand_repeats;
mod expand_tokens;
mod extract_default_aliases;
mod extract_tokens;
mod flatten_grammar;
mod intern_symbols;
mod process_inlines;

use super::Error;
use std::{
    cmp::Ordering,
    collections::{hash_map, HashMap},
    mem,
};

use self::expand_repeats::expand_repeats;
pub(crate) use self::expand_tokens::expand_tokens;
use self::extract_default_aliases::extract_default_aliases;
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
    precedence_orderings: Vec<Vec<String>>,
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

/// Transform an input grammar into separate components that are ready
/// for parse table construction.
pub(crate) fn prepare_grammar(
    input_grammar: &InputGrammar,
) -> Result<(
    SyntaxGrammar,
    LexicalGrammar,
    InlinedProductionMap,
    AliasMap,
)> {
    validate_precedence_orderings(&input_grammar.precedence_orderings)?;

    let interned_grammar = intern_symbols(input_grammar)?;
    let (syntax_grammar, lexical_grammar) = extract_tokens(interned_grammar)?;
    let syntax_grammar = expand_repeats(syntax_grammar);
    let mut syntax_grammar = flatten_grammar(syntax_grammar)?;
    let lexical_grammar = expand_tokens(lexical_grammar)?;
    let default_aliases = extract_default_aliases(&mut syntax_grammar, &lexical_grammar);
    let inlines = process_inlines(&syntax_grammar);
    Ok((syntax_grammar, lexical_grammar, inlines, default_aliases))
}

/// Make sure that there are no conflicting orderings. For any two precedence
/// names `a` and `b`, if `a` comes before `b` in some list, then it cannot come
// *after* `b` in any list.
fn validate_precedence_orderings(order_lists: &[Vec<String>]) -> Result<()> {
    let mut pairs = HashMap::new();
    for list in order_lists {
        for (i, mut name1) in list.iter().enumerate() {
            for mut name2 in list.iter().skip(i + 1) {
                if name2 == name1 {
                    continue;
                }
                let mut ordering = Ordering::Greater;
                if name1 > name2 {
                    ordering = Ordering::Less;
                    mem::swap(&mut name1, &mut name2);
                }
                match pairs.entry((name1, name2)) {
                    hash_map::Entry::Vacant(e) => {
                        e.insert(ordering);
                    }
                    hash_map::Entry::Occupied(e) => {
                        if e.get() != &ordering {
                            return Err(Error::new(format!(
                                "Conflicting orderings for precedences '{}' and '{}'",
                                name1, name2
                            )));
                        }
                    }
                }
            }
        }
    }
    Ok(())
}
