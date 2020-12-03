use super::nfa::Nfa;
use super::rules::{Alias, Associativity, Rule, Symbol};
use std::collections::HashMap;

#[derive(Clone, Copy, Debug, PartialEq, Eq, PartialOrd, Ord)]
pub(crate) enum VariableType {
    Hidden,
    Auxiliary,
    Anonymous,
    Named,
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
    pub extra_symbols: Vec<Rule>,
    pub expected_conflicts: Vec<Vec<String>>,
    pub external_tokens: Vec<Rule>,
    pub variables_to_inline: Vec<String>,
    pub supertype_symbols: Vec<String>,
    pub word_token: Option<String>,
}

// Extracted lexical grammar

#[derive(Debug, PartialEq, Eq)]
pub(crate) struct LexicalVariable {
    pub name: String,
    pub kind: VariableType,
    pub implicit_precedence: i32,
    pub start_state: u32,
}

#[derive(Debug, Default, PartialEq, Eq)]
pub(crate) struct LexicalGrammar {
    pub nfa: Nfa,
    pub variables: Vec<LexicalVariable>,
}

// Extracted syntax grammar

#[derive(Clone, Debug, PartialEq, Eq, Hash, PartialOrd, Ord)]
pub(crate) struct ProductionStep {
    pub symbol: Symbol,
    pub precedence: i32,
    pub associativity: Option<Associativity>,
    pub alias: Option<Alias>,
    pub field_name: Option<String>,
}

#[derive(Clone, Debug, PartialEq, Eq)]
pub(crate) struct Production {
    pub steps: Vec<ProductionStep>,
    pub dynamic_precedence: i32,
}

#[derive(Default)]
pub(crate) struct InlinedProductionMap {
    pub productions: Vec<Production>,
    pub production_map: HashMap<(*const Production, u32), Vec<usize>>,
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

#[derive(Debug, Default)]
pub(crate) struct SyntaxGrammar {
    pub variables: Vec<SyntaxVariable>,
    pub extra_symbols: Vec<Symbol>,
    pub expected_conflicts: Vec<Vec<Symbol>>,
    pub external_tokens: Vec<ExternalToken>,
    pub supertype_symbols: Vec<Symbol>,
    pub variables_to_inline: Vec<Symbol>,
    pub word_token: Option<Symbol>,
}

#[cfg(test)]
impl ProductionStep {
    pub(crate) fn new(symbol: Symbol) -> Self {
        Self {
            symbol,
            precedence: 0,
            associativity: None,
            alias: None,
            field_name: None,
        }
    }

    pub(crate) fn with_prec(self, precedence: i32, associativity: Option<Associativity>) -> Self {
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
