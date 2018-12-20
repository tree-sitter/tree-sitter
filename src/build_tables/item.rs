use super::inline_variables::InlinedProductionMap;
use crate::grammars::{LexicalGrammar, Production, ProductionStep, SyntaxGrammar};
use crate::rules::{Associativity, Symbol, SymbolType};
use smallbitvec::SmallBitVec;
use std::collections::{HashMap, BTreeMap};
use std::fmt;
use std::hash::{Hash, Hasher};

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

#[derive(Clone, Copy, Debug, PartialEq, Eq, Hash, PartialOrd, Ord)]
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
    pub entries: BTreeMap<ParseItem, LookaheadSet>,
}

pub(crate) struct ParseItemDisplay<'a>(
    &'a ParseItem,
    &'a SyntaxGrammar,
    &'a LexicalGrammar,
    &'a InlinedProductionMap,
);

pub(crate) struct LookaheadSetDisplay<'a>(&'a LookaheadSet, &'a SyntaxGrammar, &'a LexicalGrammar);

pub(crate) struct ParseItemSetDisplay<'a>(
    &'a ParseItemSet,
    &'a SyntaxGrammar,
    &'a LexicalGrammar,
    &'a InlinedProductionMap,
);

struct ParseItemSetMapEntry(ParseItemSet, u64);
pub(crate) struct ParseItemSetMap<T> {
    map: HashMap<ParseItemSetMapEntry, T>
}

impl LookaheadSet {
    pub fn new() -> Self {
        Self {
            terminal_bits: SmallBitVec::new(),
            external_bits: SmallBitVec::new(),
            eof: false,
        }
    }

    pub fn iter<'a>(&'a self) -> impl Iterator<Item = Symbol> + 'a {
        self.terminal_bits
            .iter()
            .enumerate()
            .filter_map(|(i, value)| {
                if value {
                    Some(Symbol::terminal(i))
                } else {
                    None
                }
            })
            .chain(
                self.external_bits
                    .iter()
                    .enumerate()
                    .filter_map(|(i, value)| {
                        if value {
                            Some(Symbol::external(i))
                        } else {
                            None
                        }
                    }),
            )
            .chain(if self.eof { Some(Symbol::end()) } else { None })
    }

    pub fn with<'a>(symbols: impl IntoIterator<Item = &'a Symbol>) -> Self {
        let mut result = Self::new();
        for symbol in symbols {
            result.insert(*symbol);
        }
        result
    }

    pub fn contains(&self, symbol: &Symbol) -> bool {
        match symbol.kind {
            SymbolType::NonTerminal => panic!("Cannot store non-terminals in a LookaheadSet"),
            SymbolType::Terminal => self.terminal_bits.get(symbol.index).unwrap_or(false),
            SymbolType::External => self.external_bits.get(symbol.index).unwrap_or(false),
            SymbolType::End => self.eof,
        }
    }

    pub fn insert(&mut self, other: Symbol) {
        let vec = match other.kind {
            SymbolType::NonTerminal => panic!("Cannot store non-terminals in a LookaheadSet"),
            SymbolType::Terminal => &mut self.terminal_bits,
            SymbolType::External => &mut self.external_bits,
            SymbolType::End => {
                self.eof = true;
                return;
            }
        };
        vec.resize(other.index + 1, false);
        vec.set(other.index, true);
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

    pub fn display_with<'a>(
        &'a self,
        syntax_grammar: &'a SyntaxGrammar,
        lexical_grammar: &'a LexicalGrammar,
    ) -> LookaheadSetDisplay<'a> {
        LookaheadSetDisplay(self, syntax_grammar, lexical_grammar)
    }
}

impl ParseItem {
    pub fn start() -> Self {
        ParseItem::Start { step_index: 0 }
    }

    pub fn is_kernel(&self) -> bool {
        match self {
            ParseItem::Start { .. } => true,
            ParseItem::Normal { step_index, .. } | ParseItem::Inlined { step_index, .. } => {
                *step_index > 0
            }
        }
    }

    pub fn production<'a>(
        &self,
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
                production_index, ..
            } => &inlined_productions.inlined_productions[*production_index as usize],
        }
    }

    pub fn symbol(
        &self,
        grammar: &SyntaxGrammar,
        inlined_productions: &InlinedProductionMap,
    ) -> Option<Symbol> {
        self.step(grammar, inlined_productions).map(|s| s.symbol)
    }

    pub fn step<'a>(
        &self,
        grammar: &'a SyntaxGrammar,
        inlined_productions: &'a InlinedProductionMap,
    ) -> Option<&'a ProductionStep> {
        self.production(grammar, inlined_productions)
            .steps
            .get(self.step_index())
    }

    pub fn precedence<'a>(
        &self,
        grammar: &'a SyntaxGrammar,
        inlines: &'a InlinedProductionMap,
    ) -> i32 {
        self.production(grammar, inlines)
            .steps
            .get(self.step_index() - 1)
            .map(|s| s.precedence)
            .unwrap_or(0)
    }

    pub fn associativity<'a>(
        &self,
        grammar: &'a SyntaxGrammar,
        inlines: &'a InlinedProductionMap,
    ) -> Option<Associativity> {
        let production = self.production(grammar, inlines);
        let step_index = self.step_index();
        if step_index == production.steps.len() {
            production.steps.last().and_then(|s| s.associativity)
        } else {
            None
        }
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

    pub fn is_final(&self) -> bool {
        if let ParseItem::Start { step_index: 1 } = self {
            true
        } else {
            false
        }
    }

    fn step_index_mut(&mut self) -> &mut u32 {
        match self {
            ParseItem::Start { step_index }
            | ParseItem::Normal { step_index, .. }
            | ParseItem::Inlined { step_index, .. } => step_index,
        }
    }

    pub fn display_with<'a>(
        &'a self,
        syntax_grammar: &'a SyntaxGrammar,
        lexical_grammar: &'a LexicalGrammar,
        inlines: &'a InlinedProductionMap,
    ) -> ParseItemDisplay<'a> {
        ParseItemDisplay(self, syntax_grammar, lexical_grammar, inlines)
    }

    pub fn successor(&self) -> ParseItem {
        let mut result = self.clone();
        *result.step_index_mut() += 1;
        result
    }
}

impl ParseItemSet {
    pub fn with<'a>(elements: impl IntoIterator<Item = &'a (ParseItem, LookaheadSet)>) -> Self {
        let mut result = Self::default();
        for (item, lookaheads) in elements {
            result.entries.insert(*item, lookaheads.clone());
        }
        result
    }

    pub fn display_with<'a>(
        &'a self,
        syntax_grammar: &'a SyntaxGrammar,
        lexical_grammar: &'a LexicalGrammar,
        inlines: &'a InlinedProductionMap,
    ) -> ParseItemSetDisplay<'a> {
        ParseItemSetDisplay(self, syntax_grammar, lexical_grammar, inlines)
    }
}

impl Default for ParseItemSet {
    fn default() -> Self {
        Self {
            entries: BTreeMap::new(),
        }
    }
}

impl<'a> fmt::Display for ParseItemDisplay<'a> {
    fn fmt(&self, f: &mut fmt::Formatter) -> Result<(), fmt::Error> {
        if let ParseItem::Start { .. } = &self.0 {
            write!(f, "START →")?;
        } else {
            write!(
                f,
                "{} →",
                &self.1.variables[self.0.variable_index() as usize].name
            )?;
        }

        let step_index = self.0.step_index();
        let production = self.0.production(self.1, self.3);
        for (i, step) in production.steps.iter().enumerate() {
            if i == step_index {
                write!(f, " •")?;
            }

            write!(f, " ")?;
            if step.symbol.is_terminal() {
                if let Some(variable) = self.2.variables.get(step.symbol.index) {
                    write!(f, "{}", &variable.name)?;
                } else {
                    write!(f, "{}-{}", "terminal", step.symbol.index)?;
                }
            } else if step.symbol.is_external() {
                write!(f, "{}", &self.1.external_tokens[step.symbol.index].name)?;
            } else {
                write!(f, "{}", &self.1.variables[step.symbol.index].name)?;
            }
        }

        if production.steps.len() == step_index {
            write!(f, " •")?;
        }

        Ok(())
    }
}

impl<'a> fmt::Display for LookaheadSetDisplay<'a> {
    fn fmt(&self, f: &mut fmt::Formatter) -> Result<(), fmt::Error> {
        write!(f, "[")?;
        for (i, symbol) in self.0.iter().enumerate() {
            if i > 0 {
                write!(f, ", ")?;
            }

            if symbol.is_terminal() {
                if let Some(variable) = self.2.variables.get(symbol.index) {
                    write!(f, "{}", &variable.name)?;
                } else {
                    write!(f, "{}-{}", "terminal", symbol.index)?;
                }
            } else if symbol.is_external() {
                write!(f, "{}", &self.1.external_tokens[symbol.index].name)?;
            } else {
                write!(f, "{}", &self.1.variables[symbol.index].name)?;
            }
        }
        write!(f, "]")?;
        Ok(())
    }
}

impl<'a> fmt::Display for ParseItemSetDisplay<'a> {
    fn fmt(&self, f: &mut fmt::Formatter) -> Result<(), fmt::Error> {
        for (item, lookaheads) in self.0.entries.iter() {
            writeln!(
                f,
                "{}\t{}",
                item.display_with(self.1, self.2, self.3),
                lookaheads.display_with(self.1, self.2)
            )?;
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
