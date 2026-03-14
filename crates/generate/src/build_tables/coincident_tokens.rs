use std::fmt;

use crate::{
    grammars::LexicalGrammar,
    rules::Symbol,
    tables::{ParseStateId, ParseTable},
};

pub struct CoincidentTokenIndex<'a> {
    entries: Vec<Vec<ParseStateId>>,
    /// Flat bitset for fast `contains()` checks. Indexed as `a * n + b`
    /// (both `(a,b)` and `(b,a)` bits are set, so no min/max normalization needed).
    contains_bits: Vec<u64>,
    /// Word-aligned per-row bitsets for vectorized intersection checks.
    /// Row `a` spans `[a * row_words .. (a+1) * row_words]`.
    /// Bit `b` is set iff tokens `a` and `b` are coincident in some parse state.
    pub row_bits: Vec<u64>,
    grammar: &'a LexicalGrammar,
    n: usize,
}

impl<'a> CoincidentTokenIndex<'a> {
    pub fn new(table: &ParseTable, lexical_grammar: &'a LexicalGrammar) -> Self {
        let n = lexical_grammar.variables.len();
        let row_words = n.div_ceil(64);
        let mut result = Self {
            n,
            grammar: lexical_grammar,
            entries: vec![Vec::new(); n * n],
            contains_bits: vec![0u64; (n * n).div_ceil(64)],
            row_bits: vec![0u64; n * row_words],
        };
        // Pre-collect terminal indices up front rather than continuously recomputing within the
        // loop below.
        let mut terminal_indices = Vec::new();
        for (i, state) in table.states.iter().enumerate() {
            terminal_indices.clear();
            terminal_indices.extend(
                state
                    .terminal_entries
                    .keys()
                    .filter(|s| s.is_terminal())
                    .map(|s| s.index),
            );
            for (j, &a) in terminal_indices.iter().enumerate() {
                for &b in &terminal_indices[j..] {
                    let index = result.index(a, b);
                    if result.entries[index].last().copied() != Some(i) {
                        result.entries[index].push(i);
                    }
                    // Set both (a,b) and (b,a) bits so `contains()` needs
                    // no min/max normalization.
                    let ab = a * n + b;
                    result.contains_bits[ab / 64] |= 1u64 << (ab % 64);
                    let ba = b * n + a;
                    result.contains_bits[ba / 64] |= 1u64 << (ba % 64);
                    // Also populate the word-aligned row bitsets.
                    result.row_bits[a * row_words + b / 64] |= 1u64 << (b % 64);
                    result.row_bits[b * row_words + a / 64] |= 1u64 << (a % 64);
                }
            }
        }
        result
    }

    pub fn states_with(&self, a: Symbol, b: Symbol) -> &[ParseStateId] {
        &self.entries[self.index(a.index, b.index)]
    }

    pub fn contains(&self, a: Symbol, b: Symbol) -> bool {
        let bit_index = a.index * self.n + b.index;
        self.contains_bits[bit_index / 64] & (1u64 << (bit_index % 64)) != 0
    }

    #[must_use]
    const fn index(&self, a: usize, b: usize) -> usize {
        if a < b {
            a * self.n + b
        } else {
            b * self.n + a
        }
    }
}

impl fmt::Debug for CoincidentTokenIndex<'_> {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        writeln!(f, "CoincidentTokenIndex {{")?;
        for i in 0..self.n {
            let mut coincident = Vec::new();
            for j in 0..self.n {
                if self.contains(Symbol::terminal(i), Symbol::terminal(j)) {
                    coincident.push(&self.grammar.variables[j].name);
                }
            }
            if !coincident.is_empty() {
                writeln!(f, "  {}: {:?},", self.grammar.variables[i].name, coincident)?;
            }
        }
        write!(f, "}}")?;
        Ok(())
    }
}
