use rustc_hash::{FxHashMap, FxHashSet};

use regex::Regex;
use serde::{Deserialize, Serialize};
use serde_json::{Map, Value};
use thiserror::Error;

use crate::{
    Diagnostic,
    grammars::{InputGrammar, PrecedenceEntry, ReservedWordContext, Variable},
    rules::{Precedence, Rule, RuleId, RulePool},
    strpool::StrId,
};

#[derive(Deserialize)]
#[serde(tag = "type")]
#[expect(
    non_camel_case_types,
    reason = "variant names match JSON grammar format"
)]
#[expect(
    clippy::upper_case_acronyms,
    reason = "variant names match JSON grammar format"
)]
enum RuleJSON {
    ALIAS {
        content: Box<Self>,
        named: bool,
        value: String,
    },
    BLANK,
    STRING {
        value: String,
    },
    PATTERN {
        value: String,
        flags: Option<String>,
    },
    SYMBOL {
        name: String,
    },
    CHOICE {
        members: Vec<Self>,
    },
    FIELD {
        name: String,
        content: Box<Self>,
    },
    SEQ {
        members: Vec<Self>,
    },
    REPEAT {
        content: Box<Self>,
    },
    REPEAT1 {
        content: Box<Self>,
    },
    PREC_DYNAMIC {
        value: i32,
        content: Box<Self>,
    },
    PREC_LEFT {
        value: PrecedenceValueJSON,
        content: Box<Self>,
    },
    PREC_RIGHT {
        value: PrecedenceValueJSON,
        content: Box<Self>,
    },
    PREC {
        value: PrecedenceValueJSON,
        content: Box<Self>,
    },
    TOKEN {
        content: Box<Self>,
    },
    IMMEDIATE_TOKEN {
        content: Box<Self>,
    },
    RESERVED {
        context_name: String,
        content: Box<Self>,
    },
    EOF,
}

#[derive(Deserialize)]
#[serde(untagged)]
enum PrecedenceValueJSON {
    Integer(i32),
    Name(String),
}

#[derive(Deserialize)]
pub struct GrammarJSON {
    pub name: String,
    rules: Map<String, Value>,
    #[serde(default)]
    precedences: Vec<Vec<RuleJSON>>,
    #[serde(default)]
    conflicts: Vec<Vec<String>>,
    #[serde(default)]
    externals: Vec<RuleJSON>,
    #[serde(default)]
    extras: Vec<RuleJSON>,
    #[serde(default)]
    inline: Vec<String>,
    #[serde(default)]
    supertypes: Vec<String>,
    #[serde(default)]
    word: Option<String>,
    #[serde(default)]
    reserved: Map<String, Value>,
}

pub type ParseGrammarResult<T> = Result<T, ParseGrammarError>;

#[derive(Debug, Error, Serialize, Deserialize)]
pub enum ParseGrammarError {
    #[error("{0}")]
    Serialization(String),
    #[error("Rules in the `extras` array must not contain empty strings")]
    InvalidExtra,
    #[error("Invalid rule in precedences array. Only strings and symbols are allowed")]
    Unexpected,
    #[error("Reserved word sets must be arrays")]
    InvalidReservedWordSet,
    #[error("Grammar Error: Unexpected rule `{0}` in `token()` call")]
    UnexpectedRule(String),
}

impl From<serde_json::Error> for ParseGrammarError {
    fn from(value: serde_json::Error) -> Self {
        Self::Serialization(value.to_string())
    }
}

impl InputGrammar {
    /// Strip unused rules from the grammar and clean up references to them
    /// in the surrounding config. (conflicts, supertypes, inline, extras,
    /// externals, precedences).
    ///
    /// A variable is "used" if it is the start rule, the word token, named in
    /// `extras`/`externals`, or transitively reachable via rule references from
    /// any of the above.
    fn normalize(mut self, diagnostics: &mut Vec<Diagnostic>) -> Self {
        // Compute the used set via forward DFS from the implicit roots
        // (start rule, word_token, refs in extras and externals).
        //
        // Extras count their top-level `NamedSymbol` as a use (so naming
        // a rule directly in `extras` keeps it), but externals do not (the
        // external entry is the rule itself, not a reference to one).
        let used: FxHashSet<StrId> = {
            let by_name: FxHashMap<StrId, RuleId> =
                self.variables.iter().map(|v| (v.name, v.root)).collect();
            let mut visited: FxHashSet<StrId> = FxHashSet::default();
            let mut stack: Vec<StrId> = Vec::new();
            if let Some(first) = self.variables.first() {
                stack.push(first.name);
            }
            if let Some(word) = self.word_name {
                stack.push(word);
            }
            for &root in &self.extra_roots {
                self.pool.collect_referenced_ids(root, false, &mut stack);
            }
            for &root in &self.external_roots {
                self.pool.collect_referenced_ids(root, true, &mut stack);
            }
            for set in &self.reserved_sets {
                for &root in &set.roots {
                    self.pool.collect_referenced_ids(root, false, &mut stack);
                }
            }
            while let Some(name) = stack.pop() {
                if !visited.insert(name) {
                    continue;
                }
                if let Some(&root) = by_name.get(&name) {
                    self.pool.collect_referenced_ids(root, false, &mut stack);
                }
            }
            visited
        };

        for v in &self.variables {
            if !used.contains(&v.name) {
                continue;
            }
            if !self
                .extra_roots
                .iter()
                .any(|&r| self.pool.rule_is_referenced(r, v.name, false))
            {
                continue;
            }
            let inner_root = match self.pool.node(v.root) {
                Rule::Metadata { rule, .. } => rule,
                _ => v.root,
            };
            let matches_empty = match self.pool.node(inner_root) {
                Rule::String(s) => self.pool.resolve(s).is_empty(),
                Rule::Pattern(value, _) => {
                    Regex::new(self.pool.resolve(value)).is_ok_and(|reg| reg.is_match(""))
                }
                _ => false,
            };
            if matches_empty {
                diagnostics.push(Diagnostic::EmptyStringMatch(
                    self.pool.resolve(v.name).to_string(),
                ));
            }
        }

        // Drop unused variables and clean up references to them in the config
        let dropped: Vec<StrId> = self
            .variables
            .iter()
            .filter(|v| !used.contains(&v.name))
            .map(|v| v.name)
            .collect();
        self.variables.retain(|v| used.contains(&v.name));
        for &name in &dropped {
            self.conflict_names.retain(|c| !c.contains(&name));
            self.supertype_names.retain(|&s| s != name);
            self.inline_names.retain(|&s| s != name);
            let pool = &self.pool;
            self.extra_roots
                .retain(|&r| !pool.rule_is_referenced(r, name, true));
            self.external_roots
                .retain(|&r| !pool.rule_is_referenced(r, name, true));
            self.precedence_orderings.retain(|o| {
                !o.iter()
                    .any(|e| matches!(e, PrecedenceEntry::Symbol(s) if *s == name))
            });
            // Prune entries but keep the context: an intentionally-empty
            // reserved-word context is a meaningful marker that rule bodies
            // may reference by name.
            for set in &mut self.reserved_sets {
                set.roots
                    .retain(|&r| !pool.rule_is_referenced(r, name, false));
            }
        }

        self
    }
}

pub(crate) fn parse_grammar(
    input: &str,
    diagnostics: &mut Vec<Diagnostic>,
) -> ParseGrammarResult<InputGrammar> {
    let grammar_json = serde_json::from_str::<GrammarJSON>(input)?;
    let mut pool = RulePool::default();

    let extra_roots =
        grammar_json
            .extras
            .into_iter()
            .try_fold(Vec::<RuleId>::new(), |mut acc, item| {
                let root = pool.parse_rule(item, false, diagnostics)?;
                if let Rule::String(s) = pool.node(root)
                    && pool.resolve(s).is_empty()
                {
                    Err(ParseGrammarError::InvalidExtra)?;
                }
                acc.push(root);
                ParseGrammarResult::Ok(acc)
            })?;

    let external_roots = grammar_json
        .externals
        .into_iter()
        .map(|e| pool.parse_rule(e, false, diagnostics))
        .collect::<ParseGrammarResult<Vec<_>>>()?;

    let mut precedence_orderings = Vec::with_capacity(grammar_json.precedences.len());
    for list in grammar_json.precedences {
        let mut ordering = Vec::with_capacity(list.len());
        for entry in list {
            ordering.push(match entry {
                RuleJSON::STRING { value } => PrecedenceEntry::Name(pool.intern(&value)),
                RuleJSON::SYMBOL { name } => PrecedenceEntry::Symbol(pool.intern(&name)),
                _ => Err(ParseGrammarError::Unexpected)?,
            });
        }
        precedence_orderings.push(ordering);
    }

    let variables = grammar_json
        .rules
        .into_iter()
        .map(|(name, r)| {
            let name = pool.intern(&name);
            Ok(Variable {
                name,
                root: pool.parse_rule(serde_json::from_value(r)?, false, diagnostics)?,
            })
        })
        .collect::<ParseGrammarResult<Vec<_>>>()?;

    let reserved_sets = grammar_json
        .reserved
        .into_iter()
        .map(|(name, rule_values)| {
            let Value::Array(rule_values) = rule_values else {
                Err(ParseGrammarError::InvalidReservedWordSet)?
            };

            let name = pool.intern(&name);
            let mut roots = Vec::with_capacity(rule_values.len());
            for value in rule_values {
                roots.push(pool.parse_rule(serde_json::from_value(value)?, false, diagnostics)?);
            }
            Ok(ReservedWordContext { name, roots })
        })
        .collect::<ParseGrammarResult<Vec<_>>>()?;

    let supertype_names = grammar_json
        .supertypes
        .iter()
        .map(|s| pool.intern(s))
        .collect();
    let conflict_names = grammar_json
        .conflicts
        .iter()
        .map(|c| c.iter().map(|n| pool.intern(n)).collect())
        .collect();
    let inline_names = grammar_json.inline.iter().map(|n| pool.intern(n)).collect();
    let word_name = grammar_json.word.as_deref().map(|w| pool.intern(w));
    let name = pool.intern(&grammar_json.name);

    let grammar = InputGrammar {
        pool,
        name,
        variables,
        external_roots,
        extra_roots,
        reserved_sets,
        supertype_names,
        conflict_names,
        inline_names,
        word_name,
        precedence_orderings,
    }
    .normalize(diagnostics);
    Ok(grammar)
}

impl RulePool {
    fn parse_rule(
        &mut self,
        json: RuleJSON,
        is_token: bool,
        diagnostics: &mut Vec<Diagnostic>,
    ) -> ParseGrammarResult<RuleId> {
        match json {
            RuleJSON::ALIAS {
                content,
                named,
                value,
            } => {
                let content = self.parse_rule(*content, is_token, diagnostics)?;
                let value = self.intern(&value);
                Ok(self.alias(content, value, named))
            }
            RuleJSON::BLANK => Ok(self.blank()),
            RuleJSON::PATTERN { value, flags } => {
                let processed_flags = flags.map_or(String::new(), |f| {
                    f.matches(|c| {
                        if c == 'i' {
                            true
                        } else {
                            // silently ignore unicode flags
                            if c != 'u' && c != 'v' {
                                diagnostics.push(Diagnostic::UnsupportedRegexFlag {
                                    flag: c,
                                    pattern: value.clone(),
                                });
                            }
                            false
                        }
                    })
                    .collect()
                });
                let value = self.intern(&value);
                let flags = self.intern(&processed_flags);
                Ok(self.pattern(value, flags))
            }
            RuleJSON::SYMBOL { name } => {
                if is_token {
                    Err(ParseGrammarError::UnexpectedRule(name))?
                } else {
                    let sid = self.intern(&name);
                    Ok(self.named_symbol(sid))
                }
            }
            RuleJSON::CHOICE { members } => {
                let members = members
                    .into_iter()
                    .map(|m| self.parse_rule(m, is_token, diagnostics))
                    .collect::<ParseGrammarResult<Vec<_>>>()?;
                Ok(self.choice(&members))
            }
            RuleJSON::SEQ { members } => self.try_seq(members.into_iter(), |pool, m| {
                pool.parse_rule(m, is_token, diagnostics)
            }),
            RuleJSON::FIELD { name, content } => {
                let content = self.parse_rule(*content, is_token, diagnostics)?;
                let name = self.intern(&name);
                Ok(self.field(name, content))
            }
            RuleJSON::REPEAT { content } => {
                let content = self.parse_rule(*content, is_token, diagnostics)?;
                let repeat = self.repeat(content);
                let blank = self.blank();
                // Neither element is a `Choice` or equal to one another, so we
                // can skip `self.choice`'s flattening loop.
                let range = self.push_children(&[repeat, blank]);
                Ok(self.push_node(Rule::Choice(range)))
            }
            RuleJSON::REPEAT1 { content } => {
                let content = self.parse_rule(*content, is_token, diagnostics)?;
                Ok(self.repeat(content))
            }
            RuleJSON::PREC { value, content } => {
                let content = self.parse_rule(*content, is_token, diagnostics)?;
                let value = value.intern(self);
                Ok(self.prec(value, content))
            }
            RuleJSON::PREC_LEFT { value, content } => {
                let content = self.parse_rule(*content, is_token, diagnostics)?;
                let value = value.intern(self);
                Ok(self.prec_left(value, content))
            }
            RuleJSON::PREC_RIGHT { value, content } => {
                let content = self.parse_rule(*content, is_token, diagnostics)?;
                let value = value.intern(self);
                Ok(self.prec_right(value, content))
            }
            RuleJSON::PREC_DYNAMIC { value, content } => {
                let content = self.parse_rule(*content, is_token, diagnostics)?;
                Ok(self.prec_dynamic(value, content))
            }
            RuleJSON::RESERVED {
                context_name,
                content,
            } => {
                let content = self.parse_rule(*content, is_token, diagnostics)?;
                let ctx = self.intern(&context_name);
                Ok(self.reserved(content, ctx))
            }
            RuleJSON::TOKEN { content } => {
                let content = self.parse_rule(*content, true, diagnostics)?;
                Ok(self.token(content))
            }
            RuleJSON::IMMEDIATE_TOKEN { content } => {
                let content = self.parse_rule(*content, true, diagnostics)?;
                Ok(self.immediate_token(content))
            }
            RuleJSON::STRING { value } => {
                let sid = self.intern(&value);
                Ok(self.string(sid))
            }
            RuleJSON::EOF => Ok(self.eof()),
        }
    }
}

impl PrecedenceValueJSON {
    fn intern(self, pool: &mut RulePool) -> Precedence {
        match self {
            Self::Integer(i) => Precedence::Integer(i),
            Self::Name(n) => Precedence::Name(pool.intern(&n)),
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_parse_grammar() {
        let grammar = parse_grammar(
            r#"{
            "name": "my_lang",
            "rules": {
                "file": {
                    "type": "REPEAT1",
                    "content": {
                        "type": "SYMBOL",
                        "name": "statement"
                    }
                },
                "statement": {
                    "type": "STRING",
                    "value": "foo"
                }
            }
        }"#,
            &mut Vec::new(),
        )
        .unwrap();

        assert_eq!(grammar.pool.resolve(grammar.name), "my_lang");

        let names = grammar
            .variables
            .iter()
            .map(|v| grammar.pool.resolve(v.name))
            .collect::<Vec<_>>();
        assert_eq!(names, ["file", "statement"]);

        // file = repeat(named_symbol "statement")
        let file_child = grammar.pool.node(grammar.variables[0].root);
        let Rule::Repeat(inner) = file_child else {
            panic!("Expected repeat, got {file_child:#?}");
        };
        let inner_node = grammar.pool.node(inner);
        let Rule::NamedSymbol(name) = inner_node else {
            panic!("Expected named symbol, got {inner_node:#?}");
        };
        assert_eq!(grammar.pool.resolve(name), "statement");

        // statement = string "foo"
        let statement_child = grammar.pool.node(grammar.variables[1].root);
        let Rule::String(value) = statement_child else {
            panic!("Expected string, got {statement_child:#?}");
        };
        assert_eq!(grammar.pool.resolve(value), "foo");
    }
}
