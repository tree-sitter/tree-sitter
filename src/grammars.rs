use crate::rules::{Associativity, Alias, Rule, Symbol};

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
pub(crate) struct LexicalGrammar {
    pub variables: Vec<Variable>,
    pub separators: Vec<Rule>,
}

// Extracted syntax grammar

#[derive(Clone, Debug, PartialEq, Eq)]
pub(crate) struct ProductionStep {
  pub symbol: Symbol,
  pub precedence: i32,
  pub associativity: Option<Associativity>,
  pub alias: Option<Alias>,
  pub is_excluded: bool,
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
    pub word_token: Symbol,
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
