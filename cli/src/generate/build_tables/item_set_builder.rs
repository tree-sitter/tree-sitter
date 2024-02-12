use super::item::{ParseItem, ParseItemDisplay, ParseItemSet, TokenSetDisplay};
use crate::generate::grammars::{InlinedProductionMap, LexicalGrammar, SyntaxGrammar};
use crate::generate::rules::{Symbol, SymbolType, TokenSet};
use std::collections::{HashMap, HashSet};
use std::fmt;

#[derive(Clone, Debug, PartialEq, Eq)]
struct TransitiveClosureAddition<'a> {
    item: ParseItem<'a>,
    info: FollowSetInfo,
}

#[derive(Clone, Debug, PartialEq, Eq)]
struct FollowSetInfo {
    lookaheads: TokenSet,
    propagates_lookaheads: bool,
}

pub struct ParseItemSetBuilder<'a> {
    syntax_grammar: &'a SyntaxGrammar,
    lexical_grammar: &'a LexicalGrammar,
    first_sets: HashMap<Symbol, TokenSet>,
    last_sets: HashMap<Symbol, TokenSet>,
    inlines: &'a InlinedProductionMap,
    transitive_closure_additions: Vec<Vec<TransitiveClosureAddition<'a>>>,
}

fn find_or_push<T: Eq>(vector: &mut Vec<T>, value: T) {
    if !vector.contains(&value) {
        vector.push(value);
    }
}

impl<'a> ParseItemSetBuilder<'a> {
    pub fn new(
        syntax_grammar: &'a SyntaxGrammar,
        lexical_grammar: &'a LexicalGrammar,
        inlines: &'a InlinedProductionMap,
    ) -> Self {
        let mut result = Self {
            syntax_grammar,
            lexical_grammar,
            first_sets: HashMap::new(),
            last_sets: HashMap::new(),
            inlines,
            transitive_closure_additions: vec![Vec::new(); syntax_grammar.variables.len()],
        };

        // For each grammar symbol, populate the FIRST and LAST sets: the set of
        // terminals that appear at the beginning and end that symbol's productions,
        // respectively.
        //
        // For a terminal symbol, the FIRST and LAST set just consists of the
        // terminal itself.
        for i in 0..lexical_grammar.variables.len() {
            let symbol = Symbol::terminal(i);
            let mut set = TokenSet::new();
            set.insert(symbol);
            result.first_sets.insert(symbol, set.clone());
            result.last_sets.insert(symbol, set);
        }

        for i in 0..syntax_grammar.external_tokens.len() {
            let symbol = Symbol::external(i);
            let mut set = TokenSet::new();
            set.insert(symbol);
            result.first_sets.insert(symbol, set.clone());
            result.last_sets.insert(symbol, set);
        }

        // The FIRST set of a non-terminal `i` is the union of the following sets:
        // * the set of all terminals that appear at the beginnings of i's productions
        // * the FIRST sets of all the non-terminals that appear at the beginnings
        //   of i's productions
        //
        // Rather than computing these sets using recursion, we use an explicit stack
        // called `symbols_to_process`.
        let mut symbols_to_process = Vec::new();
        let mut processed_non_terminals = HashSet::new();
        for i in 0..syntax_grammar.variables.len() {
            let symbol = Symbol::non_terminal(i);

            let first_set = result
                .first_sets
                .entry(symbol)
                .or_insert_with(TokenSet::new);
            processed_non_terminals.clear();
            symbols_to_process.clear();
            symbols_to_process.push(symbol);
            while let Some(current_symbol) = symbols_to_process.pop() {
                if current_symbol.is_terminal() || current_symbol.is_external() {
                    first_set.insert(current_symbol);
                } else if processed_non_terminals.insert(current_symbol) {
                    for production in &syntax_grammar.variables[current_symbol.index].productions {
                        if let Some(step) = production.steps.first() {
                            symbols_to_process.push(step.symbol);
                        }
                    }
                }
            }

            // The LAST set is defined in a similar way to the FIRST set.
            let last_set = result.last_sets.entry(symbol).or_insert_with(TokenSet::new);
            processed_non_terminals.clear();
            symbols_to_process.clear();
            symbols_to_process.push(symbol);
            while let Some(current_symbol) = symbols_to_process.pop() {
                if current_symbol.is_terminal() || current_symbol.is_external() {
                    last_set.insert(current_symbol);
                } else if processed_non_terminals.insert(current_symbol) {
                    for production in &syntax_grammar.variables[current_symbol.index].productions {
                        if let Some(step) = production.steps.last() {
                            symbols_to_process.push(step.symbol);
                        }
                    }
                }
            }
        }

        // To compute an item set's transitive closure, we find each item in the set
        // whose next symbol is a non-terminal, and we add new items to the set for
        // each of that symbols' productions. These productions might themselves begin
        // with non-terminals, so the process continues recursively. In this process,
        // the total set of entries that get added depends only on two things:
        //   * the set of non-terminal symbols that occur at each item's current position
        //   * the set of terminals that occurs after each of these non-terminal symbols
        //
        // So we can avoid a lot of duplicated recursive work by precomputing, for each
        // non-terminal symbol `i`, a final list of *additions* that must be made to an
        // item set when `i` occurs as the next symbol in one if its core items. The
        // structure of an *addition* is as follows:
        //   * `item` - the new item that must be added as part of the expansion of `i`
        //   * `lookaheads` - lookahead tokens that can always come after that item in
        //      the expansion of `i`
        //   * `propagates_lookaheads` - a boolean indicating whether or not `item` can
        //      occur at the *end* of the expansion of `i`, so that i's own current
        //      lookahead tokens can occur after `item`.
        //
        // Again, rather than computing these additions recursively, we use an explicit
        // stack called `entries_to_process`.
        for i in 0..syntax_grammar.variables.len() {
            let empty_lookaheads = TokenSet::new();
            let mut entries_to_process = vec![(i, &empty_lookaheads, true)];

            // First, build up a map whose keys are all of the non-terminals that can
            // appear at the beginning of non-terminal `i`, and whose values store
            // information about the tokens that can follow each non-terminal.
            let mut follow_set_info_by_non_terminal = HashMap::new();
            while let Some(entry) = entries_to_process.pop() {
                let (variable_index, lookaheads, propagates_lookaheads) = entry;
                let existing_info = follow_set_info_by_non_terminal
                    .entry(variable_index)
                    .or_insert_with(|| FollowSetInfo {
                        lookaheads: TokenSet::new(),
                        propagates_lookaheads: false,
                    });

                let did_add_follow_set_info;
                if propagates_lookaheads {
                    did_add_follow_set_info = !existing_info.propagates_lookaheads;
                    existing_info.propagates_lookaheads = true;
                } else {
                    did_add_follow_set_info = existing_info.lookaheads.insert_all(lookaheads);
                }

                if did_add_follow_set_info {
                    for production in &syntax_grammar.variables[variable_index].productions {
                        if let Some(symbol) = production.first_symbol() {
                            if symbol.is_non_terminal() {
                                if production.steps.len() == 1 {
                                    entries_to_process.push((
                                        symbol.index,
                                        lookaheads,
                                        propagates_lookaheads,
                                    ));
                                } else {
                                    entries_to_process.push((
                                        symbol.index,
                                        &result.first_sets[&production.steps[1].symbol],
                                        false,
                                    ));
                                }
                            }
                        }
                    }
                }
            }

            // Store all of those non-terminals' productions, along with their associated
            // lookahead info, as *additions* associated with non-terminal `i`.
            let additions_for_non_terminal = &mut result.transitive_closure_additions[i];
            for (variable_index, follow_set_info) in follow_set_info_by_non_terminal {
                let variable = &syntax_grammar.variables[variable_index];
                let non_terminal = Symbol::non_terminal(variable_index);
                let variable_index = variable_index as u32;
                if syntax_grammar.variables_to_inline.contains(&non_terminal) {
                    continue;
                }
                for production in &variable.productions {
                    let item = ParseItem {
                        variable_index,
                        production,
                        step_index: 0,
                        has_preceding_inherited_fields: false,
                    };

                    if let Some(inlined_productions) =
                        inlines.inlined_productions(item.production, item.step_index)
                    {
                        for production in inlined_productions {
                            find_or_push(
                                additions_for_non_terminal,
                                TransitiveClosureAddition {
                                    item: item.substitute_production(production),
                                    info: follow_set_info.clone(),
                                },
                            );
                        }
                    } else {
                        find_or_push(
                            additions_for_non_terminal,
                            TransitiveClosureAddition {
                                item,
                                info: follow_set_info.clone(),
                            },
                        );
                    }
                }
            }
        }

        result
    }

    pub fn transitive_closure(&mut self, item_set: &ParseItemSet<'a>) -> ParseItemSet<'a> {
        let mut result = ParseItemSet::default();
        for (item, lookaheads) in &item_set.entries {
            if let Some(productions) = self
                .inlines
                .inlined_productions(item.production, item.step_index)
            {
                for production in productions {
                    self.add_item(
                        &mut result,
                        item.substitute_production(production),
                        lookaheads,
                    );
                }
            } else {
                self.add_item(&mut result, *item, lookaheads);
            }
        }
        result
    }

    pub fn first_set(&self, symbol: &Symbol) -> &TokenSet {
        &self.first_sets[symbol]
    }

    pub fn last_set(&self, symbol: &Symbol) -> &TokenSet {
        &self.last_sets[symbol]
    }

    fn add_item(&self, set: &mut ParseItemSet<'a>, item: ParseItem<'a>, lookaheads: &TokenSet) {
        if let Some(step) = item.step() {
            if step.symbol.is_non_terminal() {
                let next_step = item.successor().step();

                // Determine which tokens can follow this non-terminal.
                let following_tokens = next_step.map_or(lookaheads, |next_step| {
                    self.first_sets.get(&next_step.symbol).unwrap()
                });

                // Use the pre-computed *additions* to expand the non-terminal.
                for addition in &self.transitive_closure_additions[step.symbol.index] {
                    let lookaheads = set.insert(addition.item, &addition.info.lookaheads);
                    if addition.info.propagates_lookaheads {
                        lookaheads.insert_all(following_tokens);
                    }
                }
            }
        }
        set.insert(item, lookaheads);
    }
}

impl<'a> fmt::Debug for ParseItemSetBuilder<'a> {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        writeln!(f, "ParseItemSetBuilder {{")?;

        writeln!(f, "  first_sets: {{")?;
        for (symbol, first_set) in &self.first_sets {
            let name = match symbol.kind {
                SymbolType::NonTerminal => &self.syntax_grammar.variables[symbol.index].name,
                SymbolType::External => &self.syntax_grammar.external_tokens[symbol.index].name,
                SymbolType::Terminal => &self.lexical_grammar.variables[symbol.index].name,
                SymbolType::End | SymbolType::EndOfNonTerminalExtra => "END",
            };
            writeln!(
                f,
                "    first({name:?}): {}",
                TokenSetDisplay(first_set, self.syntax_grammar, self.lexical_grammar)
            )?;
        }
        writeln!(f, "  }}")?;

        writeln!(f, "  last_sets: {{")?;
        for (symbol, last_set) in &self.last_sets {
            let name = match symbol.kind {
                SymbolType::NonTerminal => &self.syntax_grammar.variables[symbol.index].name,
                SymbolType::External => &self.syntax_grammar.external_tokens[symbol.index].name,
                SymbolType::Terminal => &self.lexical_grammar.variables[symbol.index].name,
                SymbolType::End | SymbolType::EndOfNonTerminalExtra => "END",
            };
            writeln!(
                f,
                "    last({name:?}): {}",
                TokenSetDisplay(last_set, self.syntax_grammar, self.lexical_grammar)
            )?;
        }
        writeln!(f, "  }}")?;

        writeln!(f, "  additions: {{")?;
        for (i, variable) in self.syntax_grammar.variables.iter().enumerate() {
            writeln!(f, "    {}: {{", variable.name)?;
            for addition in &self.transitive_closure_additions[i] {
                writeln!(
                    f,
                    "      {}",
                    ParseItemDisplay(&addition.item, self.syntax_grammar, self.lexical_grammar)
                )?;
            }
            writeln!(f, "    }},")?;
        }
        write!(f, "  }},")?;

        write!(f, "}}")?;
        Ok(())
    }
}
