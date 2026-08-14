use std::hash::{Hash as _, Hasher as _};

use rustc_hash::{FxHashMap, FxHasher};
use serde::{Deserialize, Serialize};
use thiserror::Error;

use crate::{
    grammars::{InlinedProductionMap, InputGrammar, Production, ProductionStep, ProductionStore},
    prepare_grammar::extract_tokens::ExtractedGrammarMeta,
    rules::{Precedence, Symbol, SymbolType},
};

struct InlineBuilder<'a> {
    out: &'a mut ProductionStore,
    first_inlined: u32,
    inline: &'a [Symbol],
    map: FxHashMap<(u32, u32), Vec<u32>>,
    memo: FxHashMap<u64, Vec<u32>>,
}

#[derive(Clone, Default)]
struct ScratchProd {
    steps: Vec<ProductionStep>,
    dynamic_precedence: i32,
}

impl InlineBuilder<'_> {
    fn build(mut self) -> InlinedProductionMap {
        let mut worklist = Vec::new();
        for prod_id in 0..self.first_inlined {
            worklist.push((prod_id, 0u32));
            while !worklist.is_empty() {
                let mut i = 0;
                while i < worklist.len() {
                    let (prod_id, step_index) = worklist[i];
                    if let Some(step) = self.production_step_for_id(prod_id, step_index) {
                        if self.inline.contains(&step.symbol()) {
                            let ids = self.inline_production_at_step(prod_id, step_index);
                            worklist.splice(i..=i, ids.into_iter().map(|id| (id, step_index)));
                        } else {
                            worklist[i].1 += 1;
                            i += 1;
                        }
                    } else {
                        worklist.remove(i);
                    }
                }
            }
        }

        InlinedProductionMap { map: self.map }
    }

    /// Expand inlining at one step of one production, dedup, and store the results
    fn inline_production_at_step(&mut self, prod_id: u32, step_index: u32) -> Vec<u32> {
        if let Some(ids) = self.map.get(&(prod_id, step_index)) {
            return ids.clone();
        }

        let si = step_index as usize;
        let src = self.out.productions[prod_id as usize];
        let mut scratch = vec![ScratchProd {
            steps: self.out.steps[src.step_range()].to_vec(),
            dynamic_precedence: src.dynamic_precedence,
        }];
        let mut i = 0;
        while i < scratch.len() {
            let symbol = match scratch[i].steps.get(si) {
                Some(s) if self.inline.contains(&s.symbol()) => s.symbol(),
                _ => {
                    i += 1;
                    continue;
                }
            };

            let removed_prod = std::mem::take(&mut scratch[i]);
            let removed_step = removed_prod.steps[si];
            let (v_start, v_end) = self.out.var_prods[symbol.index as usize];
            let replacements = (v_start..v_end)
                .map(|p_idx| {
                    let p = self.out.productions[p_idx as usize];
                    let mut production = removed_prod.clone();
                    production
                        .steps
                        .splice(si..=si, self.out.steps[p.step_range()].iter().copied());
                    let inserted = &mut production.steps[si..si + p.steps_len as usize];
                    if let Some(removed_alias) = removed_step.alias() {
                        for step in inserted.iter_mut() {
                            step.set_alias(Some(removed_alias));
                        }
                    }
                    if let Some(removed_field) = removed_step.field() {
                        for step in inserted.iter_mut() {
                            step.set_field(Some(removed_field));
                        }
                    }
                    if let Some(last) = inserted.last_mut() {
                        if last.precedence() == Precedence::None {
                            last.set_precedence(removed_step.precedence());
                        }
                        if last.associativity().is_none() {
                            last.set_associativity(removed_step.associativity());
                        }
                    }
                    if p.dynamic_precedence.abs() > production.dynamic_precedence.abs() {
                        production.dynamic_precedence = p.dynamic_precedence;
                    }
                    production
                })
                .collect::<Vec<_>>();
            scratch.splice(i..=i, replacements);
        }

        let mut result = Vec::with_capacity(scratch.len());
        for sp in scratch {
            let mut hasher = FxHasher::default();
            sp.dynamic_precedence.hash(&mut hasher);
            sp.steps.hash(&mut hasher);
            let candidates = self.memo.entry(hasher.finish()).or_default();
            let existing = candidates.iter().copied().find(|&id| {
                let p = self.out.productions[id as usize];
                p.dynamic_precedence == sp.dynamic_precedence
                    && self.out.steps[p.step_range()] == sp.steps
            });
            result.push(existing.unwrap_or_else(|| {
                let steps_start = self.out.steps.len() as u32;
                self.out.steps.extend_from_slice(&sp.steps);
                self.out.productions.push(Production {
                    steps_start,
                    steps_len: sp.steps.len() as u32,
                    dynamic_precedence: sp.dynamic_precedence,
                });
                let id = (self.out.productions.len() - 1) as u32;
                candidates.push(id);
                id
            }));
        }

        self.map.insert((prod_id, step_index), result.clone());
        result
    }

    fn production_step_for_id(&self, prod_id: u32, step: u32) -> Option<ProductionStep> {
        let p = self.out.productions[prod_id as usize];
        (step < p.steps_len).then(|| self.out.steps[(p.steps_start + step) as usize])
    }
}

pub type ProcessInlinesResult<T> = Result<T, ProcessInlinesError>;

#[derive(Debug, Error, Serialize, Deserialize, PartialEq, Eq)]
pub enum ProcessInlinesError {
    #[error("External token `{0}` cannot be inlined")]
    ExternalToken(String),
    #[error("Token `{0}` cannot be inlined")]
    Token(String),
    #[error("Rule `{0}` cannot be inlined because it is the first rule")]
    FirstRule(String),
}

pub(super) fn process_inlines(
    g: &InputGrammar,
    meta: &ExtractedGrammarMeta,
    out: &mut ProductionStore,
) -> ProcessInlinesResult<InlinedProductionMap> {
    if meta.inline.is_empty() {
        return Ok(InlinedProductionMap::default());
    }
    for symbol in &meta.inline {
        match symbol.kind {
            SymbolType::External => Err(ProcessInlinesError::ExternalToken(
                g.pool
                    .resolve(meta.external_tokens[symbol.index as usize].name)
                    .to_string(),
            ))?,
            SymbolType::Terminal => Err(ProcessInlinesError::Token(
                g.pool
                    .resolve(meta.lexical_variables[symbol.index as usize].name)
                    .to_string(),
            ))?,
            SymbolType::NonTerminal if symbol.index == 0 => Err(ProcessInlinesError::FirstRule(
                g.pool.resolve(g.variables[0].name).to_string(),
            ))?,
            _ => {}
        }
    }

    Ok(InlineBuilder {
        first_inlined: out.productions.len() as u32,
        out,
        inline: &meta.inline,
        map: FxHashMap::default(),
        memo: FxHashMap::default(),
    }
    .build())
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::{
        grammars::VariableType,
        prepare_grammar::extract_tokens::LexicalToken,
        rules::{Alias, Associativity, RulePool, Symbol},
    };

    #[test]
    fn test_basic_inlining() {
        // var0: [t10, nt1, t11] (nt1 is inlined)
        // var1: [t12, t13] | [t14]
        let mut out = ProductionStore::default();
        add_variable(
            &mut out,
            &[(
                vec![
                    plain(Symbol::terminal(10)),
                    plain(Symbol::non_terminal(1)),
                    plain(Symbol::terminal(11)),
                ],
                0,
            )],
        );
        add_variable(
            &mut out,
            &[
                (
                    vec![plain(Symbol::terminal(12)), plain(Symbol::terminal(13))],
                    0,
                ),
                (vec![plain(Symbol::terminal(14))], -2),
            ],
        );

        let g = InputGrammar::default();
        let meta = ExtractedGrammarMeta {
            inline: vec![Symbol::non_terminal(1)],
            ..Default::default()
        };
        let map = process_inlines(&g, &meta, &mut out).unwrap();
        let prod0 = out.var_prods[0].0;

        // Nothing to inline at step 0.
        assert!(inlined(&out, &map, prod0, 0).is_none());

        // Inlining variable 1 yields two productions.
        let (_, prods) = inlined(&out, &map, prod0, 1).unwrap();
        assert_eq!(
            prods,
            vec![
                (
                    vec![
                        plain(Symbol::terminal(10)),
                        plain(Symbol::terminal(12)),
                        plain(Symbol::terminal(13)),
                        plain(Symbol::terminal(11)),
                    ],
                    0
                ),
                (
                    vec![
                        plain(Symbol::terminal(10)),
                        plain(Symbol::terminal(14)),
                        plain(Symbol::terminal(11)),
                    ],
                    -2
                ),
            ]
        );
    }

    #[test]
    fn test_nested_inlining() {
        // var0: [t10, nt1, t11, nt2, t12]    (nt1, nt2 inlined)
        // var1: [t13] | [nt3, t14]           (nt3 inlined)
        // var2: [t15]
        // var3: [t16]
        let mut out = ProductionStore::default();
        add_variable(
            &mut out,
            &[(
                vec![
                    plain(Symbol::terminal(10)),
                    plain(Symbol::non_terminal(1)),
                    plain(Symbol::terminal(11)),
                    plain(Symbol::non_terminal(2)),
                    plain(Symbol::terminal(12)),
                ],
                0,
            )],
        );
        add_variable(
            &mut out,
            &[
                (vec![plain(Symbol::terminal(13))], 0),
                (
                    vec![plain(Symbol::non_terminal(3)), plain(Symbol::terminal(14))],
                    0,
                ),
            ],
        );
        add_variable(&mut out, &[(vec![plain(Symbol::terminal(15))], 0)]);
        add_variable(&mut out, &[(vec![plain(Symbol::terminal(16))], 0)]);

        let g = InputGrammar::default();
        let meta = ExtractedGrammarMeta {
            inline: vec![
                Symbol::non_terminal(1),
                Symbol::non_terminal(2),
                Symbol::non_terminal(3),
            ],
            ..Default::default()
        };
        let map = process_inlines(&g, &meta, &mut out).unwrap();
        let prod0 = out.var_prods[0].0;

        let (ids, prods) = inlined(&out, &map, prod0, 1).unwrap();
        assert_eq!(
            prods,
            vec![
                (
                    vec![
                        plain(Symbol::terminal(10)),
                        plain(Symbol::terminal(13)),
                        plain(Symbol::terminal(11)),
                        plain(Symbol::non_terminal(2)),
                        plain(Symbol::terminal(12)),
                    ],
                    0,
                ),
                (
                    vec![
                        plain(Symbol::terminal(10)),
                        plain(Symbol::terminal(16)),
                        plain(Symbol::terminal(14)),
                        plain(Symbol::terminal(11)),
                        plain(Symbol::non_terminal(2)),
                        plain(Symbol::terminal(12)),
                    ],
                    0
                ),
            ]
        );

        // nt2, now at step 3
        let (_, prods) = inlined(&out, &map, ids[0], 3).unwrap();
        assert_eq!(
            prods,
            vec![(
                vec![
                    plain(Symbol::terminal(10)),
                    plain(Symbol::terminal(13)),
                    plain(Symbol::terminal(11)),
                    plain(Symbol::terminal(15)),
                    plain(Symbol::terminal(12)),
                ],
                0,
            )]
        );
    }

    #[test]
    fn test_inlining_with_precedence_and_alias() {
        // var0: [ nt1{prec 1, left}, t10, nt2{alias outer} ]     (nt1, nt2 inlined)
        // var1: [ r11{prec 2, alias inner}, t12 ]
        // var2: [ t13 ]
        let mut pool = RulePool::default();
        let mut out = ProductionStore::default();
        add_variable(
            &mut out,
            &[(
                vec![
                    decorated(
                        &mut pool,
                        Symbol::non_terminal(1),
                        Precedence::Integer(1),
                        Some(Associativity::Left),
                        None,
                    ),
                    plain(Symbol::terminal(10)),
                    decorated(
                        &mut pool,
                        Symbol::non_terminal(2),
                        Precedence::None,
                        None,
                        Some("outer_alias"),
                    ),
                ],
                0,
            )],
        );
        add_variable(
            &mut out,
            &[(
                vec![
                    decorated(
                        &mut pool,
                        Symbol::terminal(11),
                        Precedence::Integer(2),
                        None,
                        Some("inner_alias"),
                    ),
                    plain(Symbol::terminal(12)),
                ],
                0,
            )],
        );
        add_variable(&mut out, &[(vec![plain(Symbol::terminal(13))], 0)]);

        let g = InputGrammar::default();
        let meta = ExtractedGrammarMeta {
            inline: vec![Symbol::non_terminal(1), Symbol::non_terminal(2)],
            ..Default::default()
        };
        let map = process_inlines(&g, &meta, &mut out).unwrap();
        let prod0 = out.var_prods[0].0;

        let (ids, prods) = inlined(&out, &map, prod0, 0).unwrap();
        assert_eq!(
            prods,
            vec![(
                vec![
                    // The first inlined step keeps its own precedence and alias.
                    decorated(
                        &mut pool,
                        Symbol::terminal(11),
                        Precedence::Integer(2),
                        None,
                        Some("inner_alias")
                    ),
                    // The last inlined step inherits the inlined step's precedence.
                    decorated(
                        &mut pool,
                        Symbol::terminal(12),
                        Precedence::Integer(1),
                        Some(Associativity::Left),
                        None,
                    ),
                    plain(Symbol::terminal(10)),
                    decorated(
                        &mut pool,
                        Symbol::non_terminal(2),
                        Precedence::None,
                        None,
                        Some("outer_alias"),
                    ),
                ],
                0,
            )]
        );

        let (_, prods) = inlined(&out, &map, ids[0], 3).unwrap();
        assert_eq!(
            prods,
            vec![(
                vec![
                    decorated(
                        &mut pool,
                        Symbol::terminal(11),
                        Precedence::Integer(2),
                        None,
                        Some("inner_alias"),
                    ),
                    decorated(
                        &mut pool,
                        Symbol::terminal(12),
                        Precedence::Integer(1),
                        Some(Associativity::Left),
                        None,
                    ),
                    plain(Symbol::terminal(10)),
                    // Every inlined step inherits the inlined step's alias
                    decorated(
                        &mut pool,
                        Symbol::terminal(13),
                        Precedence::None,
                        None,
                        Some("outer_alias"),
                    ),
                ],
                0,
            )],
        );
    }

    #[test]
    fn test_error_when_inlining_tokens() {
        let mut pool = RulePool::default();
        let name = pool.intern("something");
        let root = pool.blank();
        let g = InputGrammar {
            pool,
            ..Default::default()
        };
        let meta = ExtractedGrammarMeta {
            inline: vec![Symbol::terminal(0)],
            lexical_variables: vec![LexicalToken {
                name,
                kind: VariableType::Named,
                root,
            }],
            ..Default::default()
        };
        let mut out = ProductionStore::default();

        let result = process_inlines(&g, &meta, &mut out);
        assert!(result.is_err());
        let err = result.unwrap_err();
        assert_eq!(err, ProcessInlinesError::Token("something".to_string()));
    }

    /// Append one variable's productions to `out` and record its production id range.
    fn add_variable(out: &mut ProductionStore, prods: &[(Vec<ProductionStep>, i32)]) {
        let start = out.productions.len() as u32;
        for (steps, dynamic_prc) in prods {
            let steps_start = out.steps.len() as u32;
            out.steps.extend_from_slice(steps);
            out.productions.push(Production {
                steps_start,
                steps_len: steps.len() as u32,
                dynamic_precedence: *dynamic_prc,
            });
        }
        out.var_prods.push((start, out.productions.len() as u32));
    }

    /// One inlined replacement production: its owned steps and dynamic precedence.
    type InlinedProduction = (Vec<ProductionStep>, i32);

    /// Inlining results recorded at `(prod_id, step`: the replacement ids and each
    /// one's steps and dynamic precedence.
    fn inlined(
        out: &ProductionStore,
        map: &InlinedProductionMap,
        prod_id: u32,
        step: u32,
    ) -> Option<(Vec<u32>, Vec<InlinedProduction>)> {
        map.map.get(&(prod_id, step)).map(|ids| {
            let prods = ids
                .iter()
                .map(|&id| {
                    let p = out.productions[id as usize];
                    (out.steps[p.step_range()].to_vec(), p.dynamic_precedence)
                })
                .collect::<Vec<_>>();
            (ids.clone(), prods)
        })
    }

    fn plain(symbol: Symbol) -> ProductionStep {
        ProductionStep::pack(symbol, Precedence::None, None, None, None, 0)
    }

    fn decorated(
        pool: &mut RulePool,
        symbol: Symbol,
        prec: Precedence,
        assoc: Option<Associativity>,
        alias: Option<&str>,
    ) -> ProductionStep {
        let alias = alias.map(|name| Alias {
            value: pool.intern(name),
            is_named: true,
        });
        ProductionStep::pack(symbol, prec, assoc, alias, None, 0)
    }
}
