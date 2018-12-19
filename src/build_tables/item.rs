use super::inline_variables::InlinedProductionMap;
use crate::grammars::{Production, ProductionStep, SyntaxGrammar};
use crate::rules::{Symbol, SymbolType};
use smallbitvec::SmallBitVec;
use std::collections::HashMap;
use std::hash::{Hash, Hasher};
use std::fmt;

lazy_static! {
    static ref START_PRODUCTION: Production = Production {
        dynamic_precedence: 0,
        steps: vec![ProductionStep {
            symbol: Symbol {
                index: 0,
                kind: SymbolType::NonTerminal,
            },
            precedence: 0,
            associativity: None,
            alias: None,
        }],
    };
}

#[derive(Debug, Clone, PartialEq, Eq, Hash)]
pub(crate) struct LookaheadSet {
    terminal_bits: SmallBitVec,
    external_bits: SmallBitVec,
    eof: bool,
}

#[derive(Clone, Copy, Debug, PartialEq, Eq, Hash)]
pub(crate) enum ParseItem {
    Start {
        step_index: u32,
    },
    Normal {
        variable_index: u32,
        production_index: u32,
        step_index: u32,
    },
    Inlined {
        variable_index: u32,
        production_index: u32,
        step_index: u32,
    },
}

#[derive(Clone, Debug, PartialEq, Eq)]
pub(crate) struct ParseItemSet {
    pub entries: HashMap<ParseItem, LookaheadSet>,
}

impl LookaheadSet {
    pub fn new() -> Self {
        Self {
            terminal_bits: SmallBitVec::new(),
            external_bits: SmallBitVec::new(),
            eof: false,
        }
    }

    pub fn insert(&mut self, other: Symbol) {
        match other.kind {
            SymbolType::NonTerminal => panic!("Cannot store non-terminals in a LookaheadSet"),
            SymbolType::Terminal => self.terminal_bits.set(other.index, true),
            SymbolType::External => self.external_bits.set(other.index, true),
        }
    }

    pub fn insert_all(&mut self, other: &LookaheadSet) -> bool {
        let mut result = false;
        if other.terminal_bits.len() > self.terminal_bits.len() {
            self.terminal_bits.resize(other.terminal_bits.len(), false);
        }
        if other.external_bits.len() > self.external_bits.len() {
            self.external_bits.resize(other.external_bits.len(), false);
        }
        for (i, element) in other.terminal_bits.iter().enumerate() {
            if element {
                result |= !self.terminal_bits[i];
                self.terminal_bits.set(i, element);
            }
        }
        for (i, element) in other.external_bits.iter().enumerate() {
            if element {
                result |= !self.external_bits[i];
                self.external_bits.set(i, element);
            }
        }
        if other.eof {
            result |= !self.eof;
            self.eof = true;
        }
        result
    }
}

impl ParseItem {
    pub fn is_kernel(&self) -> bool {
        match self {
            ParseItem::Start { .. } => true,
            ParseItem::Normal { step_index, .. } | ParseItem::Inlined { step_index, .. } => {
                *step_index > 0
            }
        }
    }

    pub fn production<'a>(
        &'a self,
        grammar: &'a SyntaxGrammar,
        inlined_productions: &'a InlinedProductionMap,
    ) -> &'a Production {
        match self {
            ParseItem::Start { .. } => &START_PRODUCTION,
            ParseItem::Normal {
                variable_index,
                production_index,
                ..
            } => {
                &grammar.variables[*variable_index as usize].productions[*production_index as usize]
            }
            ParseItem::Inlined {
                production_index,
                ..
            } => &inlined_productions.inlined_productions[*production_index as usize],
        }
    }

    pub fn step<'a>(
        &'a self,
        grammar: &'a SyntaxGrammar,
        inlined_productions: &'a InlinedProductionMap,
    ) -> Option<&'a ProductionStep> {
        self.production(grammar, inlined_productions).steps.get(self.step_index())
    }

    pub fn variable_index(&self) -> u32 {
        match self {
            ParseItem::Start { .. } => panic!("Start item doesn't have a variable index"),
            ParseItem::Normal { variable_index, .. }
            | ParseItem::Inlined { variable_index, .. } => *variable_index,
        }
    }

    pub fn step_index(&self) -> usize {
        match self {
            ParseItem::Start { step_index }
            | ParseItem::Normal { step_index, .. }
            | ParseItem::Inlined { step_index, .. } => *step_index as usize,
        }
    }

    fn step_index_mut(&mut self) -> &mut u32 {
        match self {
            ParseItem::Start { step_index }
            | ParseItem::Normal { step_index, .. }
            | ParseItem::Inlined { step_index, .. } => step_index,
        }
    }

    pub fn with<'a>(&'a self, grammar: &'a SyntaxGrammar, inlines: &'a InlinedProductionMap) -> ParseItemDisplay<'a> {
        ParseItemDisplay(self, grammar, inlines)
    }

    pub fn successor(&self) -> ParseItem {
        let mut result = self.clone();
        *result.step_index_mut() += 1;
        result
    }
}

pub struct ParseItemDisplay<'a>(&'a ParseItem, &'a SyntaxGrammar, &'a InlinedProductionMap);

impl<'a> fmt::Display for ParseItemDisplay<'a> {
    fn fmt(&self, f: &mut fmt::Formatter) -> Result<(), fmt::Error> {
        let step_index = self.0.step_index();
        let production = self.0.production(self.1, self.2);
        for (i, step) in production.steps.iter().enumerate() {
            if i > 0 {
                write!(f, " ")?;
            }

            if i == step_index {
                write!(f, "• ")?;
            }

            let name = if step.symbol.is_terminal() {
                "terminal"
            } else if step.symbol.is_external() {
                "external"
            } else {
                "non-terminal"
            };

            write!(f, "{}-{}", name, step.symbol.index)?;
        }
        Ok(())
    }
}

impl Hash for ParseItemSet {
    fn hash<H: Hasher>(&self, hasher: &mut H) {
        hasher.write_usize(self.entries.len());
        for (item, lookaheads) in self.entries.iter() {
            item.hash(hasher);
            lookaheads.hash(hasher);
        }
    }
}
