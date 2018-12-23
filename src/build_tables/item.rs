use crate::grammars::{LexicalGrammar, Production, ProductionStep, SyntaxGrammar};
use crate::rules::Associativity;
use crate::rules::{Symbol, SymbolType};
use smallbitvec::SmallBitVec;
use std::collections::BTreeMap;
use std::fmt;
use std::hash::{Hash, Hasher};
use std::u32;
use std::cmp::Ordering;

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

#[derive(Clone, Copy, Debug)]
pub(crate) struct ParseItem<'a> {
    pub variable_index: u32,
    pub step_index: u32,
    pub production: &'a Production,
}

#[derive(Clone, Debug, PartialEq, Eq)]
pub(crate) struct ParseItemSet<'a> {
    pub entries: BTreeMap<ParseItem<'a>, LookaheadSet>,
}

pub(crate) struct ParseItemDisplay<'a>(&'a ParseItem<'a>, &'a SyntaxGrammar, &'a LexicalGrammar);
pub(crate) struct LookaheadSetDisplay<'a>(&'a LookaheadSet, &'a SyntaxGrammar, &'a LexicalGrammar);
pub(crate) struct ParseItemSetDisplay<'a>(
    &'a ParseItemSet<'a>,
    &'a SyntaxGrammar,
    &'a LexicalGrammar,
);

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

impl<'a> ParseItem<'a> {
    pub fn start() -> Self {
        ParseItem {
            variable_index: u32::MAX,
            production: &START_PRODUCTION,
            step_index: 0,
        }
    }

    pub fn step(&self) -> Option<&'a ProductionStep> {
        self.production.steps.get(self.step_index as usize)
    }

    pub fn symbol(&self) -> Option<Symbol> {
        self.step().map(|step| step.symbol)
    }

    pub fn associativity(&self) -> Option<Associativity> {
        self.prev_step().and_then(|step| step.associativity)
    }

    pub fn precedence(&self) -> i32 {
        self.prev_step().map_or(0, |step| step.precedence)
    }

    pub fn prev_step(&self) -> Option<&'a ProductionStep> {
        if self.step_index > 0 {
            Some(&self.production.steps[self.step_index as usize - 1])
        } else {
            None
        }
    }

    pub fn is_done(&self) -> bool {
        self.step_index as usize == self.production.steps.len()
    }

    pub fn is_augmented(&self) -> bool {
        self.variable_index == u32::MAX
    }

    pub fn successor(&self) -> ParseItem<'a> {
        ParseItem {
            variable_index: self.variable_index,
            production: self.production,
            step_index: self.step_index + 1,
        }
    }

    pub fn display_with(
        &'a self,
        syntax_grammar: &'a SyntaxGrammar,
        lexical_grammar: &'a LexicalGrammar,
    ) -> ParseItemDisplay<'a> {
        ParseItemDisplay(self, syntax_grammar, lexical_grammar)
    }
}

impl<'a> ParseItemSet<'a> {
    pub fn with(elements: impl IntoIterator<Item = (ParseItem<'a>, LookaheadSet)>) -> Self {
        let mut result = Self::default();
        for (item, lookaheads) in elements {
            result.entries.insert(item, lookaheads);
        }
        result
    }

    pub fn display_with(
        &'a self,
        syntax_grammar: &'a SyntaxGrammar,
        lexical_grammar: &'a LexicalGrammar,
    ) -> ParseItemSetDisplay<'a> {
        ParseItemSetDisplay(self, syntax_grammar, lexical_grammar)
    }
}

impl<'a> Default for ParseItemSet<'a> {
    fn default() -> Self {
        Self {
            entries: BTreeMap::new(),
        }
    }
}

impl<'a> fmt::Display for ParseItemDisplay<'a> {
    fn fmt(&self, f: &mut fmt::Formatter) -> Result<(), fmt::Error> {
        if self.0.is_augmented() {
            write!(f, "START →")?;
        } else {
            write!(
                f,
                "{} →",
                &self.1.variables[self.0.variable_index as usize].name
            )?;
        }

        for (i, step) in self.0.production.steps.iter().enumerate() {
            if i == self.0.step_index as usize {
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

        if self.0.is_done() {
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
                item.display_with(self.1, self.2),
                lookaheads.display_with(self.1, self.2)
            )?;
        }
        Ok(())
    }
}

impl<'a> Hash for ParseItem<'a> {
    fn hash<H: Hasher>(&self, hasher: &mut H) {
        hasher.write_u32(self.variable_index);
        hasher.write_u32(self.step_index);
        hasher.write_i32(self.production.dynamic_precedence);
        hasher.write_usize(self.production.steps.len());
        hasher.write_i32(self.precedence());
        self.associativity().hash(hasher);
        for step in &self.production.steps[0..self.step_index as usize] {
            step.alias.hash(hasher);
        }
        for step in &self.production.steps[self.step_index as usize..] {
            step.hash(hasher);
        }
    }
}

impl<'a> PartialEq for ParseItem<'a> {
    fn eq(&self, other: &Self) -> bool {
        if self.variable_index != other.variable_index
            || self.step_index != other.step_index
            || self.production.dynamic_precedence != other.production.dynamic_precedence
            || self.production.steps.len() != other.production.steps.len()
            || self.precedence() != other.precedence()
            || self.associativity() != other.associativity()
        {
            return false;
        }

        for (i, step) in self.production.steps.iter().enumerate() {
            if i < self.step_index as usize {
                if step.alias != other.production.steps[i].alias {
                    return false;
                }
            } else {
                if *step != other.production.steps[i] {
                    return false;
                }
            }
        }

        return true;
    }
}

impl<'a> Ord for ParseItem<'a> {
    fn cmp(&self, other: &Self) -> Ordering {
        let o = self.variable_index.cmp(&other.variable_index);
        if o != Ordering::Equal {
            return o;
        }
        let o = self.step_index.cmp(&other.step_index);
        if o != Ordering::Equal {
            return o;
        }
        let o = self.production.dynamic_precedence.cmp(&other.production.dynamic_precedence);
        if o != Ordering::Equal {
            return o;
        }
        let o = self.production.steps.len().cmp(&other.production.steps.len());
        if o != Ordering::Equal {
            return o;
        }
        let o = self.precedence().cmp(&other.precedence());
        if o != Ordering::Equal {
            return o;
        }
        let o = self.associativity().cmp(&other.associativity());
        if o != Ordering::Equal {
            return o;
        }
        for (i, step) in self.production.steps.iter().enumerate() {
            let o = if i < self.step_index as usize {
                step.alias.cmp(&other.production.steps[i].alias)
            } else {
                step.cmp(&other.production.steps[i])
            };
            if o != Ordering::Equal {
                return o;
            }
        }
        return Ordering::Equal;
    }
}

impl<'a> PartialOrd for ParseItem<'a> {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}

impl<'a> Eq for ParseItem<'a> {}

impl<'a> Hash for ParseItemSet<'a> {
    fn hash<H: Hasher>(&self, hasher: &mut H) {
        hasher.write_usize(self.entries.len());
        for (item, lookaheads) in self.entries.iter() {
            item.hash(hasher);
            lookaheads.hash(hasher);
        }
    }
}
