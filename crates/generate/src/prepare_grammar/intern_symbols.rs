use rustc_hash::{FxBuildHasher, FxHashMap};
use serde::{Deserialize, Serialize};
use thiserror::Error;

use crate::{
    Diagnostic,
    grammars::{InputGrammar, VariableType},
    rules::{Rule, RuleId, RulePool, Symbol},
    strpool::StrId,
};

pub type InternSymbolsResult<T> = Result<T, InternSymbolsError>;

#[derive(Debug, Error, Serialize, Deserialize, PartialEq, Eq)]
pub enum InternSymbolsError {
    #[error("A grammar's start rule must be visible.")]
    HiddenStartRule,
    #[error("Undefined symbol `{0}`")]
    Undefined(String),
    #[error("Undefined symbol `{0}` in grammar's supertypes array")]
    UndefinedSupertype(String),
    #[error("Undefined symbol `{0}` in grammar's conflicts array")]
    UndefinedConflict(String),
    #[error("Undefined symbol `{0}` as grammar's word token")]
    UndefinedWordToken(String),
}

/// The non-pool outputs of the intern pass. The rule bodies are rewritten in place
/// (`NamedSymbol`->`Sym`). This carries the derived metadata that travels alongside
/// them.
#[derive(Debug)]
pub(super) struct InternedGrammarMeta {
    pub kinds: Vec<VariableType>,
    /// Per external token: its name (if a named symbol) and kind
    pub external_tokens: Vec<(Option<StrId>, VariableType)>,
    pub supertypes: Vec<Symbol>,
    pub conflicts: Vec<Vec<Symbol>>,
    pub inline: Vec<Symbol>,
    pub word: Option<Symbol>,
}

pub(super) fn intern_symbols(
    grammar: &mut InputGrammar,
    diagnostics: &mut Vec<Diagnostic>,
) -> InternSymbolsResult<InternedGrammarMeta> {
    let InputGrammar {
        pool,
        variables,
        external_roots,
        extra_roots,
        reserved_sets,
        ..
    } = grammar;

    // StrId -> the symbol for a variable or external token name. An external whose name
    // shadows a variable resolves to the variable (variables are inserted first).
    let mut name_of_symbol =
        FxHashMap::with_capacity_and_hasher(variables.len() + external_roots.len(), FxBuildHasher);

    for (i, v) in variables.iter().enumerate() {
        name_of_symbol.insert(v.name, Symbol::non_terminal(i));
    }
    for (i, &root) in external_roots.iter().enumerate() {
        if let Rule::NamedSymbol(sid) = pool.node(root) {
            name_of_symbol
                .entry(sid)
                .or_insert_with(|| Symbol::external(i));
        }
    }
    if variable_type_for_name(pool.resolve(variables[0].name)) == VariableType::Hidden {
        Err(InternSymbolsError::HiddenStartRule)?;
    }

    // External names/kinds read before the in-place rewrite consumes them.
    let external_tokens = external_roots
        .iter()
        .map(|&root| match pool.node(root) {
            Rule::NamedSymbol(sid) => (Some(sid), variable_type_for_name(pool.resolve(sid))),
            _ => (None, VariableType::Anonymous),
        })
        .collect::<Vec<(Option<StrId>, VariableType)>>();

    let mut kinds = variables
        .iter()
        .map(|v| variable_type_for_name(pool.resolve(v.name)))
        .collect::<Vec<VariableType>>();

    let mut stack = Vec::new();
    for v in variables.iter() {
        intern_root(
            pool,
            v.root,
            Some(v.name),
            &name_of_symbol,
            diagnostics,
            &mut stack,
        )?;
    }
    for &root in external_roots.iter().chain(extra_roots.iter()) {
        intern_root(pool, root, None, &name_of_symbol, diagnostics, &mut stack)?;
    }
    for set in reserved_sets.iter() {
        for &root in &set.roots {
            intern_root(pool, root, None, &name_of_symbol, diagnostics, &mut stack)?;
        }
    }

    let lookup = |sid: StrId| name_of_symbol.get(&sid).copied();
    let supertypes = grammar
        .supertype_names
        .iter()
        .map(|&s| {
            lookup(s)
                .ok_or_else(|| InternSymbolsError::UndefinedSupertype(pool.resolve(s).to_string()))
        })
        .collect::<InternSymbolsResult<Vec<_>>>()?;
    let conflicts = grammar
        .conflict_names
        .iter()
        .map(|c| {
            c.iter()
                .map(|&s| {
                    lookup(s).ok_or_else(|| {
                        InternSymbolsError::UndefinedConflict(pool.resolve(s).to_string())
                    })
                })
                .collect::<InternSymbolsResult<Vec<_>>>()
        })
        .collect::<InternSymbolsResult<Vec<_>>>()?;

    // Unkown inline names are silently skipped.
    let inline = grammar
        .inline_names
        .iter()
        .filter_map(|&s| lookup(s))
        .collect::<Vec<Symbol>>();

    // An inlined rule never produces nodes, so a supertype entry for it makes
    // no sense and is dropped.
    let supertypes = grammar
        .supertype_names
        .iter()
        .zip(supertypes)
        .filter_map(|(&name, symbol)| {
            if inline.contains(&symbol) {
                diagnostics.push(Diagnostic::SupertypeInlined {
                    name: pool.resolve(name).to_string(),
                });
                None
            } else {
                Some(symbol)
            }
        })
        .collect::<Vec<_>>();
    let word = grammar
        .word_name
        .map(|s| {
            lookup(s)
                .ok_or_else(|| InternSymbolsError::UndefinedWordToken(pool.resolve(s).to_string()))
        })
        .transpose()?;

    for s in &supertypes {
        if s.is_non_terminal() {
            kinds[s.index as usize] = VariableType::Hidden;
        }
    }

    Ok(InternedGrammarMeta {
        kinds,
        external_tokens,
        supertypes,
        conflicts,
        inline,
        word,
    })
}

// Iterative pre-order walk rewriting `NamedSymbol`->`Sym` in place.
fn intern_root(
    pool: &mut RulePool,
    root: RuleId,
    var_name: Option<StrId>,
    name_of_symbol: &FxHashMap<StrId, Symbol>,
    diagnostics: &mut Vec<Diagnostic>,
    stack: &mut Vec<RuleId>,
) -> InternSymbolsResult<()> {
    stack.clear();
    stack.push(root);

    while let Some(id) = stack.pop() {
        match pool.node(id) {
            Rule::NamedSymbol(sid) => match name_of_symbol.get(&sid).copied() {
                Some(s) => pool.set_node(
                    id,
                    Rule::Sym {
                        kind: s.kind,
                        index: s.index,
                    },
                ),
                None => Err(InternSymbolsError::Undefined(pool.resolve(sid).to_string()))?,
            },
            Rule::Seq(range) | Rule::Choice(range) => {
                let children = pool.child_slice(range);
                // In the case of a seq or choice rule of 1 element in a hidden rule, weird
                // inconsistent behavior with queries can occur. So we should warn the user about it.
                if children.len() == 1
                    && matches!(pool.node(children[0]), Rule::String(_) | Rule::Pattern(..))
                {
                    let name = var_name.map(|s| pool.resolve(s).to_string());
                    diagnostics.push(if matches!(pool.node(id), Rule::Choice(_)) {
                        Diagnostic::UnaryChoice { name }
                    } else {
                        Diagnostic::UnarySeq { name }
                    });
                }
                let base = stack.len();
                stack.extend_from_slice(pool.child_slice(range));
                stack[base..].reverse();
            }
            Rule::Repeat(inner)
            | Rule::Metadata { rule: inner, .. }
            | Rule::Reserved { rule: inner, .. } => stack.push(inner),
            _ => {}
        }
    }

    Ok(())
}

fn variable_type_for_name(name: &str) -> VariableType {
    if name.starts_with('_') {
        VariableType::Hidden
    } else {
        VariableType::Named
    }
}

#[cfg(test)]
mod tests {
    use crate::{grammars::Variable, rules::SymbolType};

    use super::*;

    #[test]
    fn test_basic_interning() {
        let mut grammar = {
            // x: choice(y, _z)
            // y: _z
            // _z: "a"
            let mut pool = RulePool::default();
            let (y_str, z_str) = (pool.intern("y"), pool.intern("_z"));
            let y = pool.named_symbol(y_str);
            let z = pool.named_symbol(z_str);
            let a = pool.intern("a");
            let x_root = pool.choice(&[y, z]);
            let y_root = pool.named_symbol(z_str);
            let z_root = pool.string(a);

            let variables = vec![
                Variable {
                    name: pool.intern("x"),
                    root: x_root,
                },
                Variable {
                    name: pool.intern("y"),
                    root: y_root,
                },
                Variable {
                    name: pool.intern("_z"),
                    root: z_root,
                },
            ];

            pool_grammar(pool, variables)
        };
        let meta = intern_symbols(&mut grammar, &mut Vec::new()).unwrap();

        // x's body was `choice(y, _z)` -> `choice(nt1, nt2)`
        let x_root = grammar.pool.node(grammar.variables[0].root);
        let Rule::Choice(range) = x_root else {
            panic!("Expected choice, got {x_root:#?}");
        };
        let x_children = grammar
            .pool
            .child_slice(range)
            .iter()
            .map(|&c| grammar.pool.node(c))
            .collect::<Vec<_>>();
        assert_eq!(x_children, vec![nt(1), nt(2)]);

        // y's body was _z -> nt2
        assert_eq!(grammar.pool.node(grammar.variables[1].root), nt(2));

        // z's body (a string) is untouched, it remains hidden
        assert!(matches!(
            grammar.pool.node(grammar.variables[2].root),
            Rule::String(_)
        ));
        assert_eq!(
            meta.kinds,
            vec![
                VariableType::Named,
                VariableType::Named,
                VariableType::Hidden
            ]
        );
    }

    #[test]
    fn test_interning_external_token_names() {
        // w: choice(x, y, z)
        // x: "a"
        // y: "b"
        // externals: [y, z]
        let mut grammar = {
            let mut pool = RulePool::default();
            let (x_str, y_str, z_str) = (pool.intern("x"), pool.intern("y"), pool.intern("z"));
            let x_ns = pool.named_symbol(x_str);
            let y_ns = pool.named_symbol(y_str);
            let z_ns = pool.named_symbol(z_str);
            let w_root = pool.choice(&[x_ns, y_ns, z_ns]);
            let (a, b) = (pool.intern("a"), pool.intern("b"));
            let x_root = pool.string(a);
            let y_root = pool.string(b);
            let variables = vec![
                Variable {
                    name: pool.intern("w"),
                    root: w_root,
                },
                Variable {
                    name: pool.intern("x"),
                    root: x_root,
                },
                Variable {
                    name: pool.intern("y"),
                    root: y_root,
                },
            ];
            let mut grammar = pool_grammar(pool, variables);
            let ext_y = grammar.pool.named_symbol(y_str);
            let ext_z = grammar.pool.named_symbol(z_str);
            grammar.external_roots = vec![ext_y, ext_z];
            grammar
        };

        let meta = intern_symbols(&mut grammar, &mut Vec::new()).unwrap();

        // w: x -> nt1, y -> nt2 (var shadows the external), z -> ext1
        let w_root = grammar.pool.node(grammar.variables[0].root);
        let Rule::Choice(range) = w_root else {
            panic!("Expected choice, got {w_root:#?}");
        };
        let w_children = grammar
            .pool
            .child_slice(range)
            .iter()
            .map(|&c| grammar.pool.node(c))
            .collect::<Vec<_>>();
        assert_eq!(w_children, vec![nt(1), nt(2), ext(1)]);

        // x and y bodies (bare strings) are left alone
        assert!(matches!(
            grammar.pool.node(grammar.variables[1].root),
            Rule::String(_)
        ));
        assert!(matches!(
            grammar.pool.node(grammar.variables[2].root),
            Rule::String(_)
        ));

        // The external roots resolve the same way: y -> nt2 (shadow), z -> ext1
        assert_eq!(grammar.pool.node(grammar.external_roots[0]), nt(2));
        assert_eq!(grammar.pool.node(grammar.external_roots[1]), ext(1));

        // external token metadata carries the correct names and kinds
        let externals = meta
            .external_tokens
            .iter()
            .map(|&(sid, kind)| (sid.map(|s| grammar.pool.resolve(s)), kind))
            .collect::<Vec<_>>();
        assert_eq!(
            externals,
            vec![
                (Some("y"), VariableType::Named),
                (Some("z"), VariableType::Named)
            ]
        );
    }

    #[test]
    fn test_grammar_with_undefined_symbols() {
        // x references y, which is undefined
        let mut pool = RulePool::default();
        let y_str = pool.intern("y");
        let x_root = pool.named_symbol(y_str);
        let variables = vec![Variable {
            name: pool.intern("x"),
            root: x_root,
        }];
        let mut grammar = pool_grammar(pool, variables);

        let result = intern_symbols(&mut grammar, &mut Vec::new());
        assert!(result.is_err(), "Expected an error but got none");
        assert_eq!(
            result.unwrap_err(),
            InternSymbolsError::Undefined("y".to_string())
        );
    }

    #[test]
    fn test_supertype_and_inline_conflict() {
        // v1: _v2
        // _v2: choice("a", "b")
        // supertypes: [_v2]
        // inline: [_v2]
        let mut grammar = {
            let mut pool = RulePool::default();
            let v2 = pool.intern("_v2");
            let v1_root = pool.named_symbol(v2);
            let v2_root = {
                let (a, b) = (pool.intern("a"), pool.intern("b"));
                let (sa, sb) = (pool.string(a), pool.string(b));
                pool.choice(&[sa, sb])
            };
            let variables = vec![
                Variable {
                    name: pool.intern("v1"),
                    root: v1_root,
                },
                Variable {
                    name: v2,
                    root: v2_root,
                },
            ];
            let mut grammar = pool_grammar(pool, variables);
            grammar.supertype_names = vec![v2];
            grammar.inline_names = vec![v2];
            grammar
        };

        let mut diagnostics = Vec::new();
        let meta = intern_symbols(&mut grammar, &mut diagnostics).unwrap();

        // The supertype entry is dropped with a warning, and the rule stays inlined.
        assert!(meta.supertypes.is_empty());
        assert_eq!(meta.inline, vec![Symbol::non_terminal(1)]);
        assert_eq!(diagnostics.len(), 1);
        assert_eq!(
            diagnostics[0].to_string(),
            "rule `_v2` is both a supertype and inlined. the supertype is \
             ignored. this will become an error in a future release."
        );
    }

    #[test]
    fn test_meta_paths() {
        // x: "a"
        // y: "b"
        // supertypes: [y]
        // word: y
        // conflicts: [x, y]
        // inline: [x, nonexistent]
        let mut grammar = {
            let mut pool = RulePool::default();
            let (a, b) = (pool.intern("a"), pool.intern("b"));
            let (x, y) = (pool.intern("x"), pool.intern("y"));
            let x_root = pool.string(a);
            let y_root = pool.string(b);
            let variables = vec![
                Variable {
                    name: x,
                    root: x_root,
                },
                Variable {
                    name: y,
                    root: y_root,
                },
            ];
            let mut grammar = pool_grammar(pool, variables);

            let nonexistent = grammar.pool.intern("nonexistent");
            grammar.supertype_names = vec![y];
            grammar.word_name = Some(y);
            grammar.conflict_names = vec![vec![x, y]];
            grammar.inline_names = vec![x, nonexistent];

            grammar
        };

        let meta = intern_symbols(&mut grammar, &mut Vec::new()).unwrap();

        // y is a supertype, so it's reclassified as hidden
        assert_eq!(meta.kinds, vec![VariableType::Named, VariableType::Hidden]);
        assert_eq!(meta.supertypes, vec![Symbol::non_terminal(1)]);
        assert_eq!(meta.word, Some(Symbol::non_terminal(1)));
        assert_eq!(
            meta.conflicts,
            vec![vec![Symbol::non_terminal(0), Symbol::non_terminal(1)]]
        );
        // unknown inline names are silently skipped
        assert_eq!(meta.inline, vec![Symbol::non_terminal(0)]);
    }

    fn pool_grammar(pool: RulePool, variables: Vec<Variable>) -> InputGrammar {
        InputGrammar {
            pool,
            variables,
            ..Default::default()
        }
    }

    fn nt(index: u32) -> Rule {
        Rule::Sym {
            kind: SymbolType::NonTerminal,
            index,
        }
    }

    fn ext(index: u32) -> Rule {
        Rule::Sym {
            kind: SymbolType::External,
            index,
        }
    }
}
