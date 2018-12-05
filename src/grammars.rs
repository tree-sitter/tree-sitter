use crate::rules::{Associativity, Alias, Rule, Symbol};

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum VariableType {
    Hidden,
    Auxiliary,
    Anonymous,
    Named
}

// Input grammar

#[derive(Clone, Debug, PartialEq, Eq)]
pub struct InputVariable {
    pub name: String,
    pub kind: VariableType,
    pub rule: Rule,
}

#[derive(PartialEq, Eq)]
pub struct InputGrammar {
    pub name: String,
    pub variables: Vec<InputVariable>,
    pub extra_tokens: Vec<Rule>,
    pub expected_conflicts: Vec<Vec<String>>,
    pub external_tokens: Vec<Rule>,
    pub variables_to_inline: Vec<String>,
    pub word_token: Option<String>,
}

// Extracted lexical grammar

#[derive(PartialEq, Eq)]
pub struct LexicalVariable {
    name: String,
    kind: VariableType,
    rule: Rule,
    is_string: bool,
}

pub struct LexicalGrammar {
    variables: Vec<LexicalVariable>,
    separators: Vec<Rule>,
}

// Extracted syntax grammar

#[derive(Clone, Debug, PartialEq, Eq)]
pub struct ProductionStep {
  symbol: Symbol,
  precedence: i32,
  associativity: Option<Associativity>,
  alias: Option<Alias>,
  is_excluded: bool,
}

#[derive(Clone, Debug, PartialEq, Eq)]
pub struct Production {
    steps: Vec<ProductionStep>,
    dynamic_precedence: i32,
}

#[derive(Clone, PartialEq, Eq)]
pub struct SyntaxVariable {
    name: String,
    kind: VariableType,
}

#[derive(Clone, PartialEq, Eq)]
pub struct ExternalToken {
    name: String,
    kind: VariableType,
    corresponding_internal_token: Symbol,
}

pub struct SyntaxGrammar {
    variables: Vec<SyntaxVariable>,
    extra_tokens: Vec<Symbol>,
    expected_conflicts: Vec<Vec<Symbol>>,
    external_tokens: Vec<ExternalToken>,
    variables_to_inline: Vec<Symbol>,
    word_token: Symbol,
}

#[cfg(test)]
impl InputVariable {
    pub fn named(name: &str, rule: Rule) -> Self {
        Self { name: name.to_string(), kind: VariableType::Named, rule }
    }

    pub fn auxiliary(name: &str, rule: Rule) -> Self {
        Self { name: name.to_string(), kind: VariableType::Auxiliary, rule }
    }

    pub fn hidden(name: &str, rule: Rule) -> Self {
        Self { name: name.to_string(), kind: VariableType::Hidden, rule }
    }
}
