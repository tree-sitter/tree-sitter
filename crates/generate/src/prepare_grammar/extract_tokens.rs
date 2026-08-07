use rustc_hash::FxHashMap;

use serde::{Deserialize, Serialize};
use thiserror::Error;

use crate::{
    grammars::{ExternalToken, InputGrammar, VariableType},
    prepare_grammar::intern_symbols::InternedGrammarMeta,
    rules::{MetadataParams, Rule, RuleId, RulePool, Symbol},
    strpool::StrId,
};

pub type ExtractTokensResult<T> = Result<T, ExtractTokensError>;

#[derive(Debug, Error, Serialize, Deserialize, PartialEq, Eq)]
pub enum ExtractTokensError {
    #[error(
        "The rule `{0}` contains an empty string.

Tree-sitter does not support syntactic rules that contain an empty string
unless they are used only as the grammar's start rule.
"
    )]
    EmptyString(String),
    #[error("Terminal rule '{0}' cannot be used as a supertype")]
    SupertypeTerminal(String),
    #[error("Rule '{0}' cannot be used as both an external token and a non-terminal rule")]
    ExternalTokenNonTerminal(String),
    #[error("Non-symbol rules cannot be used as external tokens")]
    NonSymbolExternalToken,
    #[error(transparent)]
    WordToken(NonTerminalWordTokenError),
    #[error("Reserved word '{0}' must be a token")]
    NonTokenReservedWord(String),
}

#[derive(Debug, Error, Serialize, Deserialize, PartialEq, Eq)]
pub struct NonTerminalWordTokenError {
    pub symbol_name: String,
    pub conflicting_symbol_name: Option<String>,
}

impl std::fmt::Display for NonTerminalWordTokenError {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(
            f,
            "Non-terminal symbol '{}' cannot be used as the word token",
            self.symbol_name
        )?;
        if let Some(conflicting_name) = &self.conflicting_symbol_name {
            writeln!(
                f,
                ", because its rule is duplicated in '{conflicting_name}'",
            )
        } else {
            writeln!(f)
        }
    }
}

/// A single extracted token.
#[derive(Clone, Debug)]
pub struct LexicalToken {
    /// Generated for anon tokens, rule name for absorbed variables
    pub name: StrId,
    pub kind: VariableType,
    /// Pool root defining this token
    pub root: RuleId,
}

/// The extra pass's outputs besides the in-place rewrites.
#[derive(Clone, Debug, Default)]
pub(super) struct ExtractedGrammarMeta {
    pub kinds: Vec<VariableType>,
    pub lexical_variables: Vec<LexicalToken>,
    pub separator_roots: Vec<RuleId>,
    pub extra_symbols: Vec<Symbol>,
    pub external_tokens: Vec<ExternalToken>,
    pub reserved_sets: Vec<(StrId, Vec<Symbol>)>,
    pub supertypes: Vec<Symbol>,
    pub conflicts: Vec<Vec<Symbol>>,
    pub inline: Vec<Symbol>,
    pub word: Option<Symbol>,
}

/// Token de-duper over pool subtrees
#[derive(Default)]
struct TokenExtractor {
    lexical: Vec<LexicalToken>,
    usage_counts: Vec<u32>,
    memo: FxHashMap<u64, Vec<u32>>,
}

impl TokenExtractor {
    /// Find or create the lexical token for `token_root`. Returns the terminal index if found
    fn extract_token(
        &mut self,
        pool: &mut RulePool,
        token_root: RuleId,
        string_name: Option<StrId>,
        var_name: Option<StrId>,
        aux_token_count: &mut u32,
        is_first: bool,
    ) -> ExtractTokensResult<u32> {
        let hash = pool.subtree_hash(token_root);
        if let Some(candidates) = self.memo.get(&hash) {
            for &i in candidates {
                if pool.subtree_eq(self.lexical[i as usize].root, token_root) {
                    self.usage_counts[i as usize] += 1;
                    return Ok(i);
                }
            }
        }
        let (name, kind) = if let Some(sid) = string_name {
            if pool.resolve(sid).is_empty() && !is_first {
                Err(ExtractTokensError::EmptyString(
                    var_name.map_or_else(String::new, |v| pool.resolve(v).to_string()),
                ))?;
            }
            (sid, VariableType::Anonymous)
        } else {
            *aux_token_count += 1;
            let name = format!(
                "{}_token{aux_token_count}",
                var_name.map_or("", |v| pool.resolve(v))
            );
            (pool.intern(&name), VariableType::Auxiliary)
        };
        // Shallow hoist: create a new token id pointing to the same pooled subtree.
        // The original `token_root` slot is overwritten by caller to be a token, but it still
        // points to the subtree. This new node becomes the token's root in the lexical grammar.
        let index = self.lexical.len() as u32;
        let root = pool.push_node(pool.node(token_root));
        self.lexical.push(LexicalToken { name, kind, root });
        self.usage_counts.push(1);
        self.memo.entry(hash).or_default().push(index);
        Ok(index)
    }

    /// In-place token extraction over one root.
    ///  - `String`/`Pattern`: always extracted
    ///  - `token(...)`: metadata extracts the inner child when no other metadata
    ///    params are set, otherwise the whole metadata node
    fn extract_in_root(
        &mut self,
        pool: &mut RulePool,
        root: RuleId,
        var_name: Option<StrId>,
        is_first: bool,
        stack: &mut Vec<RuleId>,
    ) -> ExtractTokensResult<()> {
        let mut aux_token_count = 0;
        stack.clear();
        stack.push(root);
        while let Some(id) = stack.pop() {
            match pool.node(id) {
                Rule::String(sid) => {
                    let i = self.extract_token(
                        pool,
                        id,
                        Some(sid),
                        var_name,
                        &mut aux_token_count,
                        is_first,
                    )?;
                    pool.set_node(id, Rule::from(Symbol::terminal(i as usize)));
                }
                Rule::Pattern(..) => {
                    let i = self.extract_token(
                        pool,
                        id,
                        None,
                        var_name,
                        &mut aux_token_count,
                        is_first,
                    )?;
                    pool.set_node(id, Rule::from(Symbol::terminal(i as usize)));
                }
                Rule::Metadata { params, rule } => {
                    let p = pool.params(params);
                    if p.is_token {
                        let cleaned = MetadataParams {
                            is_token: false,
                            ..p
                        };
                        let string_name = match pool.node(rule) {
                            Rule::String(s) => Some(s),
                            _ => None,
                        };
                        let token_root = if cleaned == MetadataParams::default() {
                            rule // Only a token, drop the wrapper
                        } else {
                            id
                        };
                        let i = self.extract_token(
                            pool,
                            token_root,
                            string_name,
                            var_name,
                            &mut aux_token_count,
                            is_first,
                        )?;
                        pool.set_node(id, Rule::from(Symbol::terminal(i as usize)));
                    } else {
                        stack.push(rule);
                    }
                }
                Rule::Seq(range) | Rule::Choice(range) => {
                    let base = stack.len();
                    stack.extend_from_slice(pool.child_slice(range));
                    stack[base..].reverse();
                }
                Rule::Repeat(inner) | Rule::Reserved { rule: inner, .. } => stack.push(inner),
                _ => {}
            }
        }
        Ok(())
    }

    /// Structural lookup
    fn find(&self, pool: &RulePool, root: RuleId) -> Option<u32> {
        self.memo.get(&pool.subtree_hash(root)).and_then(|cands| {
            cands
                .iter()
                .copied()
                .find(|&i| pool.subtree_eq(self.lexical[i as usize].root, root))
        })
    }
}

pub(super) fn extract_tokens(
    g: &mut InputGrammar,
    interned: &InternedGrammarMeta,
) -> ExtractTokensResult<ExtractedGrammarMeta> {
    let mut extractor = TokenExtractor::default();
    let mut stack = Vec::new();

    for (i, v) in g.variables.iter().enumerate() {
        extractor.extract_in_root(&mut g.pool, v.root, Some(v.name), i == 0, &mut stack)?;
    }
    for (&root, &(name, _)) in g.external_roots.iter().zip(&interned.external_tokens) {
        extractor.extract_in_root(&mut g.pool, root, name, false, &mut stack)?;
    }

    // If a variable's entire rule was extracted as a token and that token didn't
    // appear within any other rule, then remove that variable from the syntax
    // grammar, giving its name to the token in the lexical grammar. Any symbols
    // that pointed to that variable will need to be updated to point to the
    // token in the lexical grammar. Symbols that pointed to later variables
    // will need to have their indices decremented.
    let old_len = g.variables.len();
    let mut replacements: FxHashMap<u32, u32> = FxHashMap::default();
    let mut retained = Vec::with_capacity(old_len);
    let mut kinds = Vec::with_capacity(old_len);

    // The start variable cannot be absorbed
    retained.push(g.variables[0]);
    kinds.push(interned.kinds[0]);
    for (i, v) in g.variables.iter().enumerate().skip(1) {
        if let Some(sym) = g.pool.node(v.root).symbol()
            && sym.is_terminal()
            && extractor.usage_counts[sym.index as usize] == 1
        {
            let lexical = &mut extractor.lexical[sym.index as usize];
            if lexical.kind == VariableType::Auxiliary || interned.kinds[i] != VariableType::Hidden
            {
                lexical.kind = interned.kinds[i];
                lexical.name = v.name;
                replacements.insert(i as u32, sym.index);
                continue;
            }
        }
        retained.push(*v);
        kinds.push(interned.kinds[i]);
    }
    g.variables = retained;

    // Prefix-sum renumbering
    let mut shift = vec![0u32; old_len];
    let mut removed = 0u32;
    for (i, slot) in shift.iter_mut().enumerate() {
        *slot = removed;
        if replacements.contains_key(&(i as u32)) {
            removed += 1;
        }
    }
    let replace_symbol = |s: Symbol| {
        if !s.is_non_terminal() {
            return s;
        }
        replacements.get(&s.index).map_or_else(
            || Symbol::non_terminal(s.index as usize - shift[s.index as usize] as usize),
            |&r| Symbol::terminal(r as usize),
        )
    };

    for v in &g.variables {
        renumber_root(&mut g.pool, v.root, &replace_symbol, &mut stack);
    }
    for &root in &g.external_roots {
        renumber_root(&mut g.pool, root, &replace_symbol, &mut stack);
    }

    // Renumber each conflict through absorption, then canonicalize
    let conflicts = interned
        .conflicts
        .iter()
        .map(|c| {
            let mut result: Vec<Symbol> = c.iter().map(|&s| replace_symbol(s)).collect();
            result.sort_unstable();
            result.dedup();
            result
        })
        .collect();

    let supertypes = interned
        .supertypes
        .iter()
        .map(|&s| {
            let sym = replace_symbol(s);
            // A supertype that got absorbed into a token isn't allowed
            if sym.is_terminal() {
                Err(ExtractTokensError::SupertypeTerminal(
                    g.pool
                        .resolve(extractor.lexical[sym.index as usize].name)
                        .to_string(),
                ))
            } else {
                Ok(sym)
            }
        })
        .collect::<ExtractTokensResult<Vec<_>>>()?;

    let inline = interned.inline.iter().map(|&s| replace_symbol(s)).collect();

    let mut separator_roots = Vec::new();
    let mut extra_symbols = Vec::with_capacity(g.extra_roots.len());
    for &root in &g.extra_roots {
        if let Some(s) = g.pool.node(root).symbol() {
            extra_symbols.push(replace_symbol(s));
        } else if let Some(i) = extractor.find(&g.pool, root) {
            extra_symbols.push(Symbol::terminal(i as usize));
        } else {
            separator_roots.push(root);
        }
    }

    let mut external_tokens = Vec::with_capacity(g.external_roots.len());
    for (&root, &(name, kind)) in g.external_roots.iter().zip(&interned.external_tokens) {
        let Some(s) = g.pool.node(root).symbol() else {
            Err(ExtractTokensError::NonSymbolExternalToken)?
        };
        if s.is_non_terminal() {
            Err(ExtractTokensError::ExternalTokenNonTerminal(
                g.pool
                    .resolve(g.variables[s.index as usize].name)
                    .to_string(),
            ))?;
        }
        external_tokens.push(if s.is_external() {
            let Some(name) = name else {
                Err(ExtractTokensError::NonSymbolExternalToken)?
            };
            ExternalToken {
                name,
                kind,
                corresponding_internal_token: None,
            }
        } else {
            ExternalToken {
                name: extractor.lexical[s.index as usize].name,
                kind,
                corresponding_internal_token: Some(s),
            }
        });
    }

    let word = match interned.word.map(replace_symbol) {
        Some(token) if token.is_non_terminal() => {
            let token_index = token.index as usize;
            let word_root = g.variables[token_index].root;
            let conflicting_symbol_name = g
                .variables
                .iter()
                .enumerate()
                .find(|(i, v)| *i != token_index && g.pool.subtree_eq(v.root, word_root))
                .map(|(_, v)| g.pool.resolve(v.name).to_string());
            Err(ExtractTokensError::WordToken(NonTerminalWordTokenError {
                symbol_name: g.pool.resolve(g.variables[token_index].name).to_string(),
                conflicting_symbol_name,
            }))?
        }
        word => word,
    };

    let mut reserved_sets = Vec::with_capacity(g.reserved_sets.len());
    for set in &g.reserved_sets {
        let mut symbols = Vec::with_capacity(set.roots.len());
        for &root in &set.roots {
            if let Some(s) = g.pool.node(root).symbol() {
                symbols.push(replace_symbol(s));
            } else if let Some(i) = extractor.find(&g.pool, root) {
                symbols.push(Symbol::terminal(i as usize));
            } else {
                let inner = match g.pool.node(root) {
                    Rule::Metadata { rule, .. } => g.pool.node(rule),
                    node => node,
                };
                let token_name = match inner {
                    Rule::String(s) | Rule::Pattern(s, _) => g.pool.resolve(s).to_string(),
                    _ => "unknown".to_string(),
                };
                Err(ExtractTokensError::NonTokenReservedWord(token_name))?;
            }
        }
        reserved_sets.push((set.name, symbols));
    }

    Ok(ExtractedGrammarMeta {
        kinds,
        lexical_variables: extractor.lexical,
        separator_roots,
        extra_symbols,
        external_tokens,
        reserved_sets,
        supertypes,
        conflicts,
        inline,
        word,
    })
}

fn renumber_root(
    pool: &mut RulePool,
    root: RuleId,
    replace: &impl Fn(Symbol) -> Symbol,
    stack: &mut Vec<RuleId>,
) {
    stack.clear();
    stack.push(root);
    while let Some(id) = stack.pop() {
        match pool.node(id) {
            Rule::Sym { kind, index } => {
                let s = Symbol { kind, index };
                let replaced = replace(s);
                pool.set_node(id, Rule::from(replaced));
            }
            Rule::Seq(range) | Rule::Choice(range) => {
                stack.extend_from_slice(pool.child_slice(range));
            }
            Rule::Repeat(inner)
            | Rule::Metadata { rule: inner, .. }
            | Rule::Reserved { rule: inner, .. } => stack.push(inner),
            _ => {}
        }
    }
}

#[cfg(test)]
mod test {
    use crate::{
        grammars::Variable,
        prepare_grammar::{extract_tokens, intern_symbols},
        rules::SymbolType,
    };

    use super::*;

    #[test]
    fn test_extraction() {
        let mut pool = RulePool::default();
        // rule_0: repeat(seq("a", /b/, choice(rule_1, rule_2, token(repeat(choice("c", "d"))))))
        let r0 = {
            let a = str(&mut pool, "a");
            let b = pat(&mut pool, "b");
            let (r1, r2) = (n_sym(&mut pool, "rule_1"), n_sym(&mut pool, "rule_2"));
            let tok = {
                let (c, d) = (str(&mut pool, "c"), str(&mut pool, "d"));
                let cd = pool.choice(&[c, d]);
                let rep = pool.repeat(cd);
                pool.token(rep)
            };
            let ch = pool.choice(&[r1, r2, tok]);
            let sq = pool.seq(&[a, b, ch]);
            pool.repeat(sq)
        };
        let r1 = pat(&mut pool, "e");
        let r2 = pat(&mut pool, "b");
        let r3 = {
            let (r, bl) = (n_sym(&mut pool, "rule_2"), pool.blank());
            pool.seq(&[r, bl])
        };
        #[rustfmt::skip]
        let variables = vec![
            Variable { name: pool.intern("rule_0"), root: r0 },
            Variable { name: pool.intern("rule_1"), root: r1 },
            Variable { name: pool.intern("rule_2"), root: r2 },
            Variable { name: pool.intern("rule_3"), root: r3 },
        ];
        let mut grammar = pool_grammar(pool, variables);
        let ext = extract(&mut grammar).unwrap();

        // rule_1 was absorbed into the lexical grammar, rule_0, rule_2, and rule_3 remain
        let names = grammar
            .variables
            .iter()
            .map(|v| grammar.pool.resolve(v.name))
            .collect::<Vec<_>>();
        assert_eq!(names, ["rule_0", "rule_2", "rule_3"]);
        assert_eq!(ext.kinds, [VariableType::Named; 3]);

        // rule_0: repeat(seq(terminal(0), terminal(1), choice(terminal(3), non_terminal(2), terminal(2))))
        //  - Its leaves became terminals: "a"->t0, "b"->t1, token(...)->t2.
        //  - Its symbol refs changed: rule_1 was absorbed into the lexer (now t3),
        //  rule_2's index dropped to 1 because rule_1 was removed.
        let expected_r0 = {
            let p = &mut grammar.pool;
            let ch = {
                let (a, b, c) = (term(p, 3), non_term(p, 1), term(p, 2));
                p.choice(&[a, b, c])
            };
            let sq = {
                let (a, b) = (term(p, 0), term(p, 1));
                p.seq(&[a, b, ch])
            };
            p.repeat(sq)
        };
        assert!(
            grammar
                .pool
                .subtree_eq(grammar.variables[0].root, expected_r0)
        );

        // rule_2 is `/b/` -> terminal(1). It is *not* absorbed: `/b/` appears in
        // two places (rule_0 and rule_2), so its terminal is used more than once.
        assert_eq!(
            grammar.pool.node(grammar.variables[1].root),
            Rule::Sym {
                kind: SymbolType::Terminal,
                index: 1
            }
        );

        // rule_3: seq(non_terminal(1), blank) -> rule_2 decremented after rule_1's removal
        let expected_r3 = {
            let p = &mut grammar.pool;
            let (nt, bl) = (non_term(p, 1), p.blank());
            p.seq(&[nt, bl])
        };
        assert!(
            grammar
                .pool
                .subtree_eq(grammar.variables[2].root, expected_r3)
        );

        // `/e/` is used in exactly one place (as rule_1's whole body), so rule_1
        // was absorbed into the lexical grammar (and donated its name to the token).
        let lex = ext
            .lexical_variables
            .iter()
            .map(|v| (grammar.pool.resolve(v.name), v.kind))
            .collect::<Vec<_>>();
        assert_eq!(
            lex,
            [
                ("a", VariableType::Anonymous),
                ("rule_0_token1", VariableType::Auxiliary),
                ("rule_0_token2", VariableType::Auxiliary),
                ("rule_1", VariableType::Named),
            ]
        );
        let roots = ext
            .lexical_variables
            .iter()
            .map(|v| v.root)
            .collect::<Vec<_>>();
        let e0 = str(&mut grammar.pool, "a");
        assert!(grammar.pool.subtree_eq(roots[0], e0));
        let e1 = pat(&mut grammar.pool, "b");
        assert!(grammar.pool.subtree_eq(roots[1], e1));
        let e2 = {
            let p = &mut grammar.pool;
            let (c, d) = (str(p, "c"), str(p, "d"));
            let cd = p.choice(&[c, d]);
            p.repeat(cd)
        };
        assert!(grammar.pool.subtree_eq(roots[2], e2));
        let e3 = pat(&mut grammar.pool, "e");
        assert!(grammar.pool.subtree_eq(roots[3], e3));
    }

    #[test]
    fn test_start_rule_is_token() {
        // The start rule is a bare token. The token is extracted, but the start
        // rule is never absorbed. It stays as a reference to terminal 0.
        let mut pool = RulePool::default();
        let r0 = str(&mut pool, "hello");
        let variables = vec![Variable {
            name: pool.intern("rule_0"),
            root: r0,
        }];
        let mut grammar = pool_grammar(pool, variables);
        let ext = extract(&mut grammar).unwrap();

        let names = grammar
            .variables
            .iter()
            .map(|v| grammar.pool.resolve(v.name))
            .collect::<Vec<_>>();
        assert_eq!(names, ["rule_0"]);
        assert_eq!(
            grammar.pool.node(grammar.variables[0].root),
            Rule::Sym {
                kind: SymbolType::Terminal,
                index: 0
            }
        );

        let lex = ext
            .lexical_variables
            .iter()
            .map(|v| (grammar.pool.resolve(v.name), v.kind))
            .collect::<Vec<_>>();
        assert_eq!(lex, [("hello", VariableType::Anonymous)]);
        let e = str(&mut grammar.pool, "hello");
        assert!(grammar.pool.subtree_eq(ext.lexical_variables[0].root, e));
    }

    #[test]
    fn test_extracting_extra_symbols() {
        // extras split two ways:
        //  - the `comment` ref (absorbed into a token) becomes an extra terminal
        //  - the bare " " string becomes a separator
        let mut pool = RulePool::default();
        let r0 = str(&mut pool, "x");
        let comment = pat(&mut pool, "//.*");
        let sep = str(&mut pool, " ");
        let extra_ref = n_sym(&mut pool, "comment");
        let variables = vec![
            Variable {
                name: pool.intern("rule_0"),
                root: r0,
            },
            Variable {
                name: pool.intern("comment"),
                root: comment,
            },
        ];
        let mut grammar = pool_grammar(pool, variables);
        grammar.extra_roots = vec![sep, extra_ref];
        let ext = extract(&mut grammar).unwrap();

        // comment's `//.*` was single use-> absorbed by terminal(1), so the extra ref
        // resolves to it
        assert_eq!(ext.extra_symbols, [Symbol::terminal(1)]);
        // the " " string routes to separators, not a token symbol
        assert_eq!(ext.separator_roots.len(), 1);
        let e = str(&mut grammar.pool, " ");
        assert!(grammar.pool.subtree_eq(ext.separator_roots[0], e));
    }

    #[test]
    fn test_extract_externals() {
        let mut pool = RulePool::default();
        // rule_0: seq(external_0, "a", rule_1, rule_2)
        let r0 = {
            let e = n_sym(&mut pool, "external_0");
            let a = str(&mut pool, "a");
            let (r1, r2) = (n_sym(&mut pool, "rule_1"), n_sym(&mut pool, "rule_2"));
            pool.seq(&[e, a, r1, r2])
        };
        let r1 = str(&mut pool, "b");
        let r2 = str(&mut pool, "c");
        // externals: [external_0, "a", rule_2]
        let e0 = n_sym(&mut pool, "external_0");
        let ea = str(&mut pool, "a");
        let er2 = n_sym(&mut pool, "rule_2");
        let variables = vec![
            Variable {
                name: pool.intern("rule_0"),
                root: r0,
            },
            Variable {
                name: pool.intern("rule_1"),
                root: r1,
            },
            Variable {
                name: pool.intern("rule_2"),
                root: r2,
            },
        ];
        let external_0 = pool.intern("external_0");
        let a = pool.intern("a");
        let rule_2 = pool.intern("rule_2");
        let mut grammar = pool_grammar(pool, variables);
        grammar.external_roots = vec![e0, ea, er2];
        let ext = extract(&mut grammar).unwrap();

        assert_eq!(
            ext.external_tokens,
            [
                // a genuine external, no internal counterpart
                ExternalToken {
                    name: external_0,
                    kind: VariableType::Named,
                    corresponding_internal_token: None,
                },
                // "a" is also extracted internally (terminal 0), so it links to it
                ExternalToken {
                    name: a,
                    kind: VariableType::Anonymous,
                    corresponding_internal_token: Some(Symbol::terminal(0)),
                },
                // rule_2 shadowed a variable that got absorbed to terminal 2
                ExternalToken {
                    name: rule_2,
                    kind: VariableType::Named,
                    corresponding_internal_token: Some(Symbol::terminal(2)),
                },
            ]
        );
    }

    #[test]
    fn test_error_on_external_with_same_name_as_non_terminal() {
        let mut pool = RulePool::default();
        let r0 = {
            let (a, b) = (n_sym(&mut pool, "rule_1"), n_sym(&mut pool, "rule_2"));
            pool.seq(&[a, b])
        };
        let r1 = {
            let (a, b) = (n_sym(&mut pool, "rule_2"), n_sym(&mut pool, "rule_2"));
            pool.seq(&[a, b])
        };
        let r2 = str(&mut pool, "a");
        let ext_ref = n_sym(&mut pool, "rule_1");
        let variables = vec![
            Variable {
                name: pool.intern("rule_0"),
                root: r0,
            },
            Variable {
                name: pool.intern("rule_1"),
                root: r1,
            },
            Variable {
                name: pool.intern("rule_2"),
                root: r2,
            },
        ];
        let mut grammar = pool_grammar(pool, variables);
        grammar.external_roots = vec![ext_ref];

        // rule_1 is a seq (not absorbable), so it stays a non-terminal. A non-terminal
        // non-terminal can't also be an external token.
        let err = extract(&mut grammar).unwrap_err();
        assert_eq!(
            err,
            ExtractTokensError::ExternalTokenNonTerminal("rule_1".to_string())
        );
    }

    #[test]
    fn test_extraction_on_hidden_terminal() {
        // `_rule_1` is hidden and its token "a" is anonymous, so the absorption guard declines.
        // Both variables stay, and the anonymous token keeps its own name.
        let mut pool = RulePool::default();
        let r0 = n_sym(&mut pool, "_rule_1");
        let r1 = str(&mut pool, "a");
        let variables = vec![
            Variable {
                name: pool.intern("rule_0"),
                root: r0,
            },
            Variable {
                name: pool.intern("_rule_1"),
                root: r1,
            },
        ];
        let mut grammar = pool_grammar(pool, variables);
        let ext = extract(&mut grammar).unwrap();

        let names = grammar
            .variables
            .iter()
            .map(|v| grammar.pool.resolve(v.name))
            .collect::<Vec<_>>();
        assert_eq!(names, ["rule_0", "_rule_1"]);
        assert_eq!(ext.kinds, [VariableType::Named, VariableType::Hidden]);
        #[rustfmt::skip]
        assert_eq!(
            grammar.pool.node(grammar.variables[0].root),
            Rule::Sym { kind: SymbolType::NonTerminal, index: 1 }
        );
        #[rustfmt::skip]
        assert_eq!(
            grammar.pool.node(grammar.variables[1].root),
            Rule::Sym { kind: SymbolType::Terminal, index: 0 }
        );

        let lex = ext
            .lexical_variables
            .iter()
            .map(|v| (grammar.pool.resolve(v.name), v.kind))
            .collect::<Vec<_>>();
        assert_eq!(lex, [("a", VariableType::Anonymous)]);
        let e = str(&mut grammar.pool, "a");
        assert!(grammar.pool.subtree_eq(ext.lexical_variables[0].root, e));
    }

    #[test]
    fn test_extraction_with_empty_string() {
        // An empty string outside the start rule is an error.
        let mut pool = RulePool::default();
        let r0 = n_sym(&mut pool, "_rule_1");
        let r1 = str(&mut pool, "");
        #[rustfmt::skip]
        let variables = vec![
            Variable { name: pool.intern("rule_0"), root: r0 },
            Variable { name: pool.intern("_rule_1"), root: r1 },
        ];
        let mut grammar = pool_grammar(pool, variables);
        assert_eq!(
            extract(&mut grammar).unwrap_err(),
            ExtractTokensError::EmptyString("_rule_1".to_string())
        );
    }

    fn str(p: &mut RulePool, t: &str) -> RuleId {
        let id = p.intern(t);
        p.string(id)
    }
    fn pat(p: &mut RulePool, t: &str) -> RuleId {
        let (v, f) = (p.intern(t), p.intern(""));
        p.pattern(v, f)
    }
    fn n_sym(p: &mut RulePool, n: &str) -> RuleId {
        let id = p.intern(n);
        p.named_symbol(id)
    }

    fn term(p: &mut RulePool, i: u32) -> RuleId {
        p.push_node(Rule::Sym {
            kind: SymbolType::Terminal,
            index: i,
        })
    }
    fn non_term(p: &mut RulePool, i: u32) -> RuleId {
        p.push_node(Rule::Sym {
            kind: SymbolType::NonTerminal,
            index: i,
        })
    }

    fn pool_grammar(pool: RulePool, variables: Vec<Variable>) -> InputGrammar {
        InputGrammar {
            pool,
            variables,
            ..Default::default()
        }
    }

    fn extract(g: &mut InputGrammar) -> ExtractTokensResult<ExtractedGrammarMeta> {
        let meta = intern_symbols(g, &mut Vec::new()).unwrap();
        extract_tokens(g, &meta)
    }
}
