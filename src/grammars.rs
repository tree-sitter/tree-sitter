use crate::rules::{Associativity, Alias, Rule, Symbol};
use crate::nfa::Nfa;

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub(crate) enum VariableType {
    Hidden,
    Auxiliary,
    Anonymous,
    Named
}

// Input grammar

#[derive(Clone, Debug, PartialEq, Eq)]
pub(crate) struct Variable {
    pub name: String,
    pub kind: VariableType,
    pub rule: Rule,
}

#[derive(Debug, PartialEq, Eq)]
pub(crate) struct InputGrammar {
    pub name: String,
    pub variables: Vec<Variable>,
    pub extra_tokens: Vec<Rule>,
    pub expected_conflicts: Vec<Vec<String>>,
    pub external_tokens: Vec<Rule>,
    pub variables_to_inline: Vec<String>,
    pub word_token: Option<String>,
}

// Extracted lexical grammar

#[derive(Debug, PartialEq, Eq)]
pub(crate) struct LexicalVariable {
    pub name: String,
    pub kind: VariableType,
    pub start_state: u32,
}

#[derive(Debug, Default, PartialEq, Eq)]
pub(crate) struct LexicalGrammar {
    pub nfa: Nfa,
    pub variables: Vec<LexicalVariable>,
}

// Extracted syntax grammar

#[derive(Clone, Debug, PartialEq, Eq)]
pub(crate) struct ProductionStep {
  pub symbol: Symbol,
  pub precedence: i32,
  pub associativity: Option<Associativity>,
  pub alias: Option<Alias>,
}

#[derive(Clone, Debug, PartialEq, Eq)]
pub(crate) struct Production {
    pub steps: Vec<ProductionStep>,
    pub dynamic_precedence: i32,
}

#[derive(Clone, Debug, PartialEq, Eq)]
pub(crate) struct SyntaxVariable {
    pub name: String,
    pub kind: VariableType,
    pub productions: Vec<Production>,
}

#[derive(Clone, Debug, PartialEq, Eq)]
pub(crate) struct ExternalToken {
    pub name: String,
    pub kind: VariableType,
    pub corresponding_internal_token: Option<Symbol>,
}

#[derive(Debug)]
pub(crate) struct SyntaxGrammar {
    pub variables: Vec<SyntaxVariable>,
    pub extra_tokens: Vec<Symbol>,
    pub expected_conflicts: Vec<Vec<Symbol>>,
    pub external_tokens: Vec<ExternalToken>,
    pub variables_to_inline: Vec<Symbol>,
    pub word_token: Option<Symbol>,
}

impl ProductionStep {
    pub(crate) fn new(symbol: Symbol) -> Self {
        Self { symbol, precedence: 0, associativity: None, alias: None }
    }

    pub(crate) fn with_prec(self, precedence: i32, associativity: Option<Associativity>) -> Self {
        Self {
            symbol: self.symbol,
            precedence,
            associativity,
            alias: self.alias,
        }
    }

    pub(crate) fn with_alias(self, value: &str, is_named: bool) -> Self {
        Self {
            symbol: self.symbol,
            precedence: self.precedence,
            associativity: self.associativity,
            alias: Some(Alias { value: value.to_string(), is_named }),
        }
    }
}

impl Production {
    pub fn first_symbol(&self) -> Option<Symbol> {
        self.steps.first().map(|s| s.symbol.clone())
    }

    pub fn last_precedence(&self) -> i32 {
        self.steps.last().map(|s| s.precedence).unwrap_or(0)
    }

    pub fn last_associativity(&self) -> Option<Associativity> {
        self.steps.last().map(|s| s.associativity).unwrap_or(None)
    }
}

impl Default for Production {
    fn default() -> Self {
        Production { dynamic_precedence: 0, steps: Vec::new() }
    }
}

impl Variable {
    pub fn named(name: &str, rule: Rule) -> Self {
        Self { name: name.to_string(), kind: VariableType::Named, rule }
    }

    pub fn auxiliary(name: &str, rule: Rule) -> Self {
        Self { name: name.to_string(), kind: VariableType::Auxiliary, rule }
    }

    pub fn hidden(name: &str, rule: Rule) -> Self {
        Self { name: name.to_string(), kind: VariableType::Hidden, rule }
    }

    pub fn anonymous(name: &str, rule: Rule) -> Self {
        Self { name: name.to_string(), kind: VariableType::Anonymous, rule }
    }
}

impl SyntaxVariable {
    pub fn is_auxiliary(&self) -> bool {
        self.kind == VariableType::Auxiliary
    }
}
