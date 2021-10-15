use super::nfa::Nfa;
use super::rules::{Alias, Associativity, Precedence, Rule, Symbol};
use std::collections::HashMap;
use std::fmt;

/// Kind of the rule
#[derive(Clone, Copy, Debug, PartialEq, Eq, PartialOrd, Ord)]
pub enum VariableType {
    Hidden,
    Auxiliary,
    /// the rule which start with `_`
    Anonymous,
    /// a named rule
    Named,
}

/// A grammar rule
#[derive(Clone, Debug, PartialEq, Eq)]
pub struct Variable {
    /// name of the rule
    pub name: String,
    /// kind of the rule
    pub kind: VariableType,
    /// Actual syntax tree
    pub rule: Rule,
}

/// Precedence entry
#[derive(Clone, Debug, PartialEq, Eq, PartialOrd, Ord, Hash)]
pub enum PrecedenceEntry {
    Name(String),
    Symbol(String),
}

/// Typed syntax DSL
#[derive(Debug, PartialEq, Eq)]
pub struct InputGrammar {
    /// name of your grammar
    pub name: String,
    /// all of the rules
    pub variables: Vec<Variable>,
    /// an array of tokens that may appear anywhere in the language.
    ///
    /// This is often used for whitespace and comments.
    ///
    /// The default value of extras is to accept whitespace.
    pub extra_symbols: Vec<Rule>,
    /// An array of arrays of rule names.
    ///
    /// Each inner array represents a set of rules that’s involved in an LR(1) conflict that is intended to exist in the grammar.
    ///
    /// When these conflicts occur at runtime, Tree-sitter will use the GLR algorithm to explore all of the possible interpretations.
    ///
    /// If multiple parses end up succeeding, Tree-sitter will pick the subtree whose corresponding rule has the highest total dynamic precedence.
    pub expected_conflicts: Vec<Vec<String>>,
    /// Precedence ordering entries
    pub precedence_orderings: Vec<Vec<PrecedenceEntry>>,
    /// An array of token names which can be returned by an external scanner.
    ///
    /// External scanners allow you to write custom C code which runs during the lexing process in order to handle lexical rules (e.g. Python’s indentation tokens) that cannot be described by regular expressions.
    pub external_tokens: Vec<Rule>,
    /// An array of rule names that should be automatically removed from the grammar by replacing all of their usages with a copy of their definition.
    ///
    /// This is useful for rules that are used in multiple places but for which you don’t want to create syntax tree nodes at runtime.
    pub variables_to_inline: Vec<String>,
    /// On array of hidden rule names which should be considered to be ‘supertypes’ in the generated [node types file](https://tree-sitter.github.io/tree-sitter/using-parsers#static-node-types).
    pub supertype_symbols: Vec<String>,
    /// The name of a token that will match keywords for the purpose of the [keyword extraction](https://tree-sitter.github.io/tree-sitter/creating-parsers#keyword-extraction) optimization.
    pub word_token: Option<String>,
}

/// Extracted lexical grammar
#[derive(Debug, PartialEq, Eq)]
pub struct LexicalVariable {
    pub name: String,
    pub kind: VariableType,
    pub implicit_precedence: i32,
    pub start_state: u32,
}

#[derive(Debug, Default, PartialEq, Eq)]
pub struct LexicalGrammar {
    pub nfa: Nfa,
    pub variables: Vec<LexicalVariable>,
}

/// Extracted syntax grammar
#[derive(Clone, Debug, PartialEq, Eq, Hash, PartialOrd, Ord)]
pub struct ProductionStep {
    pub symbol: Symbol,
    pub precedence: Precedence,
    pub associativity: Option<Associativity>,
    pub alias: Option<Alias>,
    pub field_name: Option<String>,
}

#[derive(Clone, Debug, PartialEq, Eq)]
pub struct Production {
    pub steps: Vec<ProductionStep>,
    pub dynamic_precedence: i32,
}

#[derive(Default)]
pub struct InlinedProductionMap {
    pub productions: Vec<Production>,
    pub production_map: HashMap<(*const Production, u32), Vec<usize>>,
}

#[derive(Clone, Debug, PartialEq, Eq)]
pub struct SyntaxVariable {
    pub name: String,
    pub kind: VariableType,
    pub productions: Vec<Production>,
}

#[derive(Clone, Debug, PartialEq, Eq)]
pub struct ExternalToken {
    pub name: String,
    pub kind: VariableType,
    pub corresponding_internal_token: Option<Symbol>,
}

#[derive(Debug, Default)]
pub struct SyntaxGrammar {
    pub variables: Vec<SyntaxVariable>,
    pub extra_symbols: Vec<Symbol>,
    pub expected_conflicts: Vec<Vec<Symbol>>,
    pub external_tokens: Vec<ExternalToken>,
    pub supertype_symbols: Vec<Symbol>,
    pub variables_to_inline: Vec<Symbol>,
    pub word_token: Option<Symbol>,
    pub precedence_orderings: Vec<Vec<PrecedenceEntry>>,
}

#[cfg(test)]
impl ProductionStep {
    pub(crate) fn new(symbol: Symbol) -> Self {
        Self {
            symbol,
            precedence: Precedence::None,
            associativity: None,
            alias: None,
            field_name: None,
        }
    }

    pub(crate) fn with_prec(
        self,
        precedence: Precedence,
        associativity: Option<Associativity>,
    ) -> Self {
        Self {
            symbol: self.symbol,
            precedence,
            associativity,
            alias: self.alias,
            field_name: self.field_name,
        }
    }

    pub(crate) fn with_alias(self, value: &str, is_named: bool) -> Self {
        Self {
            symbol: self.symbol,
            precedence: self.precedence,
            associativity: self.associativity,
            alias: Some(Alias {
                value: value.to_string(),
                is_named,
            }),
            field_name: self.field_name,
        }
    }
    pub(crate) fn with_field_name(self, name: &str) -> Self {
        Self {
            symbol: self.symbol,
            precedence: self.precedence,
            associativity: self.associativity,
            alias: self.alias,
            field_name: Some(name.to_string()),
        }
    }
}

impl Production {
    pub fn first_symbol(&self) -> Option<Symbol> {
        self.steps.first().map(|s| s.symbol.clone())
    }
}

impl Default for Production {
    fn default() -> Self {
        Production {
            dynamic_precedence: 0,
            steps: Vec::new(),
        }
    }
}

#[cfg(test)]
impl Variable {
    pub fn named(name: &str, rule: Rule) -> Self {
        Self {
            name: name.to_string(),
            kind: VariableType::Named,
            rule,
        }
    }

    pub fn auxiliary(name: &str, rule: Rule) -> Self {
        Self {
            name: name.to_string(),
            kind: VariableType::Auxiliary,
            rule,
        }
    }

    pub fn hidden(name: &str, rule: Rule) -> Self {
        Self {
            name: name.to_string(),
            kind: VariableType::Hidden,
            rule,
        }
    }

    pub fn anonymous(name: &str, rule: Rule) -> Self {
        Self {
            name: name.to_string(),
            kind: VariableType::Anonymous,
            rule,
        }
    }
}

impl VariableType {
    pub fn is_visible(&self) -> bool {
        *self == VariableType::Named || *self == VariableType::Anonymous
    }
}

impl LexicalGrammar {
    pub fn variable_indices_for_nfa_states<'a>(
        &'a self,
        state_ids: &'a Vec<u32>,
    ) -> impl Iterator<Item = usize> + 'a {
        let mut prev = None;
        state_ids.iter().filter_map(move |state_id| {
            let variable_id = self.variable_index_for_nfa_state(*state_id);
            if prev != Some(variable_id) {
                prev = Some(variable_id);
                prev
            } else {
                None
            }
        })
    }

    pub fn variable_index_for_nfa_state(&self, state_id: u32) -> usize {
        self.variables
            .iter()
            .position(|v| v.start_state >= state_id)
            .unwrap()
    }
}

impl SyntaxVariable {
    pub fn is_auxiliary(&self) -> bool {
        self.kind == VariableType::Auxiliary
    }

    pub fn is_hidden(&self) -> bool {
        self.kind == VariableType::Hidden || self.kind == VariableType::Auxiliary
    }
}

impl InlinedProductionMap {
    pub fn inlined_productions<'a>(
        &'a self,
        production: &Production,
        step_index: u32,
    ) -> Option<impl Iterator<Item = &'a Production> + 'a> {
        self.production_map
            .get(&(production as *const Production, step_index))
            .map(|production_indices| {
                production_indices
                    .iter()
                    .cloned()
                    .map(move |index| &self.productions[index])
            })
    }
}

impl fmt::Display for PrecedenceEntry {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        match self {
            PrecedenceEntry::Name(n) => write!(f, "'{}'", n),
            PrecedenceEntry::Symbol(s) => write!(f, "$.{}", s),
        }
    }
}
