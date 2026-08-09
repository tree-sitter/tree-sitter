use std::collections::BTreeMap;

use crate::{
    grammars::{InputGrammar, ProductionStore},
    prepare_grammar::extract_tokens::ExtractedGrammarMeta,
    rules::{Alias, AliasMap, Symbol, SymbolType},
};

#[derive(Clone, Default)]
struct SymbolStatus {
    aliases: Vec<(Alias, usize)>,
    appears_unaliased: bool,
}

// Update the grammar by finding symbols that always are aliased, and for each such symbol,
// promoting one of its aliases to a "default alias", which is applied globally instead
// of in a context-specific way.
//
// This has two benefits:
// * It reduces the overhead of storing production-specific alias info in the parse table.
// * Within an `ERROR` node, no context-specific aliases will be applied. This transformation
//   ensures that the children of an `ERROR` node have symbols that are consistent with the way that
//   they would appear in a valid syntax tree.
pub(super) fn extract_default_aliases(
    g: &InputGrammar,
    meta: &ExtractedGrammarMeta,
    out: &mut ProductionStore,
) -> AliasMap {
    let mut terminal_status_list = vec![SymbolStatus::default(); meta.lexical_variables.len()];
    let mut non_terminal_status_list = vec![SymbolStatus::default(); g.variables.len()];
    let mut external_status_list = vec![SymbolStatus::default(); meta.external_tokens.len()];

    // For each grammar symbol, find all of the aliases under which the symbol appears,
    // and determine whether or not the symbol ever appears *unaliased*.
    for prod in &out.productions {
        for step in &out.steps[prod.step_range()] {
            let symbol = step.symbol();
            let symbol_index = symbol.index as usize;
            let status = match symbol.kind {
                SymbolType::External => &mut external_status_list[symbol_index],
                SymbolType::NonTerminal => &mut non_terminal_status_list[symbol_index],
                SymbolType::Terminal => &mut terminal_status_list[symbol_index],
                SymbolType::End | SymbolType::EndOfNonTerminalExtra => {
                    panic!("Unexpected end token")
                }
            };

            // Default aliases don't work for inlined variables.
            if meta.inline.contains(&symbol) {
                continue;
            }

            if let Some(alias) = step.alias() {
                if let Some(count_for_alias) = status
                    .aliases
                    .iter_mut()
                    .find_map(|(a, count)| (*a == alias).then_some(count))
                {
                    *count_for_alias += 1;
                } else {
                    status.aliases.push((alias, 1));
                }
            } else {
                status.appears_unaliased = true;
            }
        }
    }

    for symbol in &meta.extra_symbols {
        let symbol_index = symbol.index as usize;
        let status = match symbol.kind {
            SymbolType::External => &mut external_status_list[symbol_index],
            SymbolType::NonTerminal => &mut non_terminal_status_list[symbol_index],
            SymbolType::Terminal => &mut terminal_status_list[symbol_index],
            SymbolType::End | SymbolType::EndOfNonTerminalExtra => panic!("Unexpected end token"),
        };
        status.appears_unaliased = true;
    }

    let symbols_with_statuses = terminal_status_list
        .iter_mut()
        .enumerate()
        .map(|(i, status)| (Symbol::terminal(i), status))
        .chain(
            non_terminal_status_list
                .iter_mut()
                .enumerate()
                .map(|(i, status)| (Symbol::non_terminal(i), status)),
        )
        .chain(
            external_status_list
                .iter_mut()
                .enumerate()
                .map(|(i, status)| (Symbol::external(i), status)),
        );

    // For each symbol that always appears aliased, find the alias that occurs most often,
    // and designate that alias as the symbol's "default alias". Store all of these
    // default aliases in a map that will be returned.
    let mut result = BTreeMap::new();
    for (symbol, status) in symbols_with_statuses {
        if status.appears_unaliased {
            status.aliases.clear();
        } else if let Some(default_entry) = status
            .aliases
            .iter()
            .enumerate()
            .max_by_key(|(i, (_, count))| (count, -(*i as i64)))
            .map(|(_, entry)| *entry)
        {
            status.aliases.clear();
            status.aliases.push(default_entry);
            result.insert(symbol, default_entry.0);
        }
    }

    // Wherever a symbol is aliased as its default alias, remove the usage of the alias,
    // because it will now be redundant.
    let mut alias_positions_to_clear = Vec::new();
    for &(p_start, p_end) in &out.var_prods {
        alias_positions_to_clear.clear();

        let productions = &out.productions[p_start as usize..p_end as usize];
        for (i, prod) in productions.iter().enumerate() {
            for (j, step) in out.steps[prod.step_range()].iter().enumerate() {
                let symbol = step.symbol();
                let symbol_index = symbol.index as usize;
                let status = match symbol.kind {
                    SymbolType::External => &external_status_list[symbol_index],
                    SymbolType::Terminal => &terminal_status_list[symbol_index],
                    SymbolType::NonTerminal => &non_terminal_status_list[symbol_index],
                    SymbolType::End | SymbolType::EndOfNonTerminalExtra => {
                        panic!("Unexpected end token")
                    }
                };

                // If this step is aliased as the symbol's default alias, then remove that alias.
                if step.alias().is_some() && step.alias() == status.aliases.first().map(|t| t.0) {
                    let mut other_productions_must_use_this_alias_at_this_index = false;
                    for (other_i, other_prod) in productions.iter().enumerate() {
                        let other_steps = &out.steps[other_prod.step_range()];
                        if other_i != i
                            && other_steps.len() > j
                            && other_steps[j].alias() == step.alias()
                            && result.get(&other_steps[j].symbol()) != step.alias().as_ref()
                        {
                            other_productions_must_use_this_alias_at_this_index = true;
                            break;
                        }
                    }

                    if !other_productions_must_use_this_alias_at_this_index {
                        alias_positions_to_clear.push(prod.steps_start as usize + j);
                    }
                }
            }
        }

        for &step_index in &alias_positions_to_clear {
            out.steps[step_index].set_alias(None);
        }
    }

    result
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::{
        grammars::{Production, ProductionStep, Variable, VariableType},
        prepare_grammar::extract_tokens::LexicalToken,
        rules::{Precedence, RulePool},
    };

    #[test]
    fn test_extract_simple_aliases() {
        let mut pool = RulePool::default();
        let dummy = pool.intern("_");
        let root = pool.blank();

        // v1: every token aliased.
        let v1 = vec![
            aliased(&mut pool, Symbol::terminal(0), "a1"),
            aliased(&mut pool, Symbol::terminal(1), "a2"),
            aliased(&mut pool, Symbol::terminal(2), "a3"),
            aliased(&mut pool, Symbol::terminal(3), "a4"),
        ];
        // v2: t0 same alias, t1 unaliased, t2 aliased differently, t3 aliased twice as a6
        let v2 = vec![
            aliased(&mut pool, Symbol::terminal(0), "a1"),
            plain(Symbol::terminal(1)),
            aliased(&mut pool, Symbol::terminal(2), "a5"),
            aliased(&mut pool, Symbol::terminal(3), "a6"),
            aliased(&mut pool, Symbol::terminal(3), "a6"),
        ];

        let mut out = ProductionStore::default();
        for steps in [v1, v2] {
            let ps = out.productions.len() as u32;
            let steps_start = out.steps.len() as u32;
            out.steps.extend_from_slice(&steps);
            out.productions.push(Production {
                steps_start,
                steps_len: steps.len() as u32,
                dynamic_precedence: 0,
            });
            out.var_prods.push((ps, out.productions.len() as u32));
        }

        let g = InputGrammar {
            variables: (0..2).map(|_| Variable { name: dummy, root }).collect(),
            pool,
            ..Default::default()
        };
        let meta = ExtractedGrammarMeta {
            lexical_variables: (0..4)
                .map(|_| LexicalToken {
                    name: dummy,
                    kind: VariableType::Anonymous,
                    root,
                })
                .collect(),
            ..Default::default()
        };

        let pool_map = extract_default_aliases(&g, &meta, &mut out);

        // t0 -> a1, t2 -> a3 (v1 wins the tie from appearing first), t3 -> a6 (used twice)
        // t1 -> none (appears unaliased in v2).
        let default = |s| {
            pool_map
                .get(&s)
                .map(|a| (g.pool.resolve(a.value), a.is_named))
        };
        assert_eq!(pool_map.len(), 3);
        assert_eq!(default(Symbol::terminal(0)), Some(("a1", true)));
        assert_eq!(default(Symbol::terminal(2)), Some(("a3", true)));
        assert_eq!(default(Symbol::terminal(3)), Some(("a6", true)));
        assert_eq!(default(Symbol::terminal(1)), None);

        // Steps carrying their symbol's default are cleared. The rest keep their alias.
        let step_alias = |i: usize| {
            out.steps[i]
                .alias()
                .map(|a| (g.pool.resolve(a.value), a.is_named))
        };
        assert_eq!(step_alias(0), None); //               v1 t0(a1) = default
        assert_eq!(step_alias(1), Some(("a2", true))); // v1 t1(a2), no default
        assert_eq!(step_alias(2), None); //               v1 t2(a3) = default
        assert_eq!(step_alias(3), Some(("a4", true))); // v1 t3(a4) != a6
        assert_eq!(step_alias(4), None); //               v2 t0(a1) = default
        assert_eq!(step_alias(5), None); //               v2 t1 unaliased
        assert_eq!(step_alias(6), Some(("a5", true))); // v2 t2(a5) != a3
        assert_eq!(step_alias(7), None); //               v2 t3(a6) = default
        assert_eq!(step_alias(8), None); //               v2 t3(a6) = default
    }

    fn aliased(pool: &mut RulePool, symbol: Symbol, name: &str) -> ProductionStep {
        let value = pool.intern(name);
        ProductionStep::pack(
            symbol,
            Precedence::None,
            None,
            Some(Alias {
                value,
                is_named: true,
            }),
            None,
            0,
        )
    }
    fn plain(symbol: Symbol) -> ProductionStep {
        ProductionStep::pack(symbol, Precedence::None, None, None, None, 0)
    }
}
