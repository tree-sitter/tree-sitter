use std::{collections::HashMap, fmt};

use smallbitvec::SmallBitVec;

use super::grammars::VariableType;

#[derive(Clone, Copy, Debug, PartialEq, Eq, Hash, PartialOrd, Ord)]
pub enum SymbolType {
    External,
    End,
    EndOfNonTerminalExtra,
    Terminal,
    NonTerminal,
}

#[derive(Clone, Copy, Debug, PartialEq, Eq, Hash, PartialOrd, Ord)]
pub enum Associativity {
    Left,
    Right,
}

#[derive(Clone, Debug, PartialEq, Eq, Hash, PartialOrd, Ord)]
pub struct Alias {
    pub value: String,
    pub is_named: bool,
}

#[derive(Clone, Debug, PartialEq, Eq, Hash, PartialOrd, Ord, Default)]
pub enum Precedence {
    #[default]
    None,
    Integer(i32),
    Name(String),
}

pub type AliasMap = HashMap<Symbol, Alias>;

#[derive(Clone, Debug, Default, PartialEq, Eq, Hash)]
pub struct MetadataParams {
    pub precedence: Precedence,
    pub dynamic_precedence: i32,
    pub associativity: Option<Associativity>,
    pub is_token: bool,
    pub is_main_token: bool,
    pub alias: Option<Alias>,
    pub field_name: Option<String>,
}

#[derive(Clone, Copy, Debug, PartialEq, Eq, Hash, PartialOrd, Ord)]
pub struct Symbol {
    pub kind: SymbolType,
    pub index: usize,
}

#[derive(Clone, Debug, PartialEq, Eq, Hash)]
pub enum Rule {
    Blank,
    String(String),
    Pattern(String, String),
    NamedSymbol(String),
    Symbol(Symbol),
    Choice(Vec<Rule>),
    Metadata {
        params: MetadataParams,
        rule: Box<Rule>,
    },
    Repeat(Box<Rule>),
    Seq(Vec<Rule>),
}

impl fmt::Display for Rule {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        match self {
            Rule::Blank => write!(f, ""),
            Rule::String(s) => write!(f, "'{s}'"),
            Rule::Pattern(s, fl) => write!(f, "/{s}/{fl}"),
            Rule::NamedSymbol(s) => write!(f, "$.{s}"),
            Rule::Symbol(s) => write!(f, "Symbol({})", s.index),
            Rule::Choice(v) => {
                // if v is length two with a Blank and a Repeat, transform the repeat1 into repeat,
                // as that is the representation under the hood
                if v.len() == 2 && matches!(v[0], Rule::Repeat(_)) && matches!(v[1], Rule::Blank) {
                    return write!(f, "{}", v[0].to_string().replacen("repeat1", "repeat", 1));
                }

                write!(f, "choice(")?;
                for (i, rule) in v.iter().enumerate() {
                    if i == v.len() - 1 {
                        write!(f, "{rule}")?;
                    } else {
                        write!(f, "{rule}, ")?;
                    }
                }
                write!(f, ")")
            }
            Rule::Metadata { rule, params } => {
                let mut s = rule.to_string();
                match (&params.precedence, params.associativity) {
                    (Precedence::Integer(i), None) => s = format!("prec({i}, {s})"),
                    (Precedence::Name(n), None) => s = format!("prec('{n}', {s})"),
                    (Precedence::None, Some(Associativity::Left)) => {
                        s = format!("prec.left({s})");
                    }
                    (Precedence::None, Some(Associativity::Right)) => {
                        s = format!("prec.right({s})");
                    }
                    (Precedence::Integer(i), Some(Associativity::Left)) => {
                        s = format!("prec.left({i}, {s})");
                    }
                    (Precedence::Integer(i), Some(Associativity::Right)) => {
                        s = format!("prec.right({i}, {s})");
                    }
                    (Precedence::Name(n), Some(Associativity::Left)) => {
                        s = format!("prec.left('{n}', {s})");
                    }
                    (Precedence::Name(n), Some(Associativity::Right)) => {
                        s = format!("prec.right('{n}', {s})");
                    }
                    (Precedence::None, None) => {}
                }

                if params.dynamic_precedence != 0 {
                    s = format!("prec.dynamic({}, {s})", params.dynamic_precedence);
                }

                if let Some(alias) = &params.alias {
                    s = format!(
                        "alias({s}, {})",
                        if alias.is_named {
                            format!("$.{}", alias.value)
                        } else {
                            format!("'{}'", alias.value)
                        }
                    );
                }

                if let Some(field_name) = &params.field_name {
                    s = format!("field('{field_name}', {s})");
                }

                if params.is_token {
                    s = format!("token({s})");
                }

                write!(f, "{s}")
            }
            Rule::Repeat(r) => write!(f, "repeat1({r})"),
            Rule::Seq(v) => {
                write!(f, "seq(")?;
                for (i, rule) in v.iter().enumerate() {
                    if i == v.len() - 1 {
                        write!(f, "{rule}")?;
                    } else {
                        write!(f, "{rule}, ")?;
                    }
                }
                write!(f, ")")
            }
        }
    }
}

// Because tokens are represented as small (~400 max) unsigned integers,
// sets of tokens can be efficiently represented as bit vectors with each
// index corresponding to a token, and each value representing whether or not
// the token is present in the set.
#[derive(Debug, Clone, PartialEq, Eq, Hash)]
pub struct TokenSet {
    terminal_bits: SmallBitVec,
    external_bits: SmallBitVec,
    eof: bool,
    end_of_nonterminal_extra: bool,
}

impl Rule {
    pub fn field(name: String, content: Self) -> Self {
        add_metadata(content, move |params| {
            params.field_name = Some(name);
        })
    }

    pub fn alias(content: Self, value: String, is_named: bool) -> Self {
        add_metadata(content, move |params| {
            params.alias = Some(Alias { value, is_named });
        })
    }

    pub fn token(content: Self) -> Self {
        add_metadata(content, |params| {
            params.is_token = true;
        })
    }

    pub fn immediate_token(content: Self) -> Self {
        add_metadata(content, |params| {
            params.is_token = true;
            params.is_main_token = true;
        })
    }

    pub fn prec(value: Precedence, content: Self) -> Self {
        add_metadata(content, |params| {
            params.precedence = value;
        })
    }

    pub fn prec_left(value: Precedence, content: Self) -> Self {
        add_metadata(content, |params| {
            params.associativity = Some(Associativity::Left);
            params.precedence = value;
        })
    }

    pub fn prec_right(value: Precedence, content: Self) -> Self {
        add_metadata(content, |params| {
            params.associativity = Some(Associativity::Right);
            params.precedence = value;
        })
    }

    pub fn prec_dynamic(value: i32, content: Self) -> Self {
        add_metadata(content, |params| {
            params.dynamic_precedence = value;
        })
    }

    pub fn repeat(rule: Self) -> Self {
        Self::Repeat(Box::new(rule))
    }

    pub fn choice(rules: Vec<Self>) -> Self {
        let mut elements = Vec::with_capacity(rules.len());
        for rule in rules {
            choice_helper(&mut elements, rule);
        }
        Self::Choice(elements)
    }

    pub fn seq(rules: Vec<Self>) -> Self {
        Self::Seq(rules)
    }
}

impl Alias {
    #[must_use]
    pub const fn kind(&self) -> VariableType {
        if self.is_named {
            VariableType::Named
        } else {
            VariableType::Anonymous
        }
    }
}

impl Precedence {
    #[must_use]
    pub const fn is_none(&self) -> bool {
        matches!(self, Self::None)
    }
}

#[cfg(test)]
impl Rule {
    #[must_use]
    pub const fn terminal(index: usize) -> Self {
        Self::Symbol(Symbol::terminal(index))
    }

    #[must_use]
    pub const fn non_terminal(index: usize) -> Self {
        Self::Symbol(Symbol::non_terminal(index))
    }

    #[must_use]
    pub const fn external(index: usize) -> Self {
        Self::Symbol(Symbol::external(index))
    }

    #[must_use]
    pub fn named(name: &'static str) -> Self {
        Self::NamedSymbol(name.to_string())
    }

    #[must_use]
    pub fn string(value: &'static str) -> Self {
        Self::String(value.to_string())
    }

    #[must_use]
    pub fn pattern(value: &'static str, flags: &'static str) -> Self {
        Self::Pattern(value.to_string(), flags.to_string())
    }
}

impl Symbol {
    #[must_use]
    pub fn is_terminal(&self) -> bool {
        self.kind == SymbolType::Terminal
    }

    #[must_use]
    pub fn is_non_terminal(&self) -> bool {
        self.kind == SymbolType::NonTerminal
    }

    #[must_use]
    pub fn is_external(&self) -> bool {
        self.kind == SymbolType::External
    }

    #[must_use]
    pub fn is_eof(&self) -> bool {
        self.kind == SymbolType::End
    }

    #[must_use]
    pub const fn non_terminal(index: usize) -> Self {
        Self {
            kind: SymbolType::NonTerminal,
            index,
        }
    }

    #[must_use]
    pub const fn terminal(index: usize) -> Self {
        Self {
            kind: SymbolType::Terminal,
            index,
        }
    }

    #[must_use]
    pub const fn external(index: usize) -> Self {
        Self {
            kind: SymbolType::External,
            index,
        }
    }

    #[must_use]
    pub const fn end() -> Self {
        Self {
            kind: SymbolType::End,
            index: 0,
        }
    }

    #[must_use]
    pub const fn end_of_nonterminal_extra() -> Self {
        Self {
            kind: SymbolType::EndOfNonTerminalExtra,
            index: 0,
        }
    }
}

impl From<Symbol> for Rule {
    #[must_use]
    fn from(symbol: Symbol) -> Self {
        Self::Symbol(symbol)
    }
}

impl TokenSet {
    pub fn new() -> Self {
        Self {
            terminal_bits: SmallBitVec::new(),
            external_bits: SmallBitVec::new(),
            eof: false,
            end_of_nonterminal_extra: false,
        }
    }

    pub fn iter(&self) -> impl Iterator<Item = Symbol> + '_ {
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
            .chain(if self.end_of_nonterminal_extra {
                Some(Symbol::end_of_nonterminal_extra())
            } else {
                None
            })
    }

    pub fn terminals(&self) -> impl Iterator<Item = Symbol> + '_ {
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
    }

    pub fn contains(&self, symbol: &Symbol) -> bool {
        match symbol.kind {
            SymbolType::NonTerminal => panic!("Cannot store non-terminals in a TokenSet"),
            SymbolType::Terminal => self.terminal_bits.get(symbol.index).unwrap_or(false),
            SymbolType::External => self.external_bits.get(symbol.index).unwrap_or(false),
            SymbolType::End => self.eof,
            SymbolType::EndOfNonTerminalExtra => self.end_of_nonterminal_extra,
        }
    }

    pub fn contains_terminal(&self, index: usize) -> bool {
        self.terminal_bits.get(index).unwrap_or(false)
    }

    pub fn insert(&mut self, other: Symbol) {
        let vec = match other.kind {
            SymbolType::NonTerminal => panic!("Cannot store non-terminals in a TokenSet"),
            SymbolType::Terminal => &mut self.terminal_bits,
            SymbolType::External => &mut self.external_bits,
            SymbolType::End => {
                self.eof = true;
                return;
            }
            SymbolType::EndOfNonTerminalExtra => {
                self.end_of_nonterminal_extra = true;
                return;
            }
        };
        if other.index >= vec.len() {
            vec.resize(other.index + 1, false);
        }
        vec.set(other.index, true);
    }

    pub fn remove(&mut self, other: &Symbol) -> bool {
        let vec = match other.kind {
            SymbolType::NonTerminal => panic!("Cannot store non-terminals in a TokenSet"),
            SymbolType::Terminal => &mut self.terminal_bits,
            SymbolType::External => &mut self.external_bits,
            SymbolType::End => {
                return if self.eof {
                    self.eof = false;
                    true
                } else {
                    false
                }
            }
            SymbolType::EndOfNonTerminalExtra => {
                return if self.end_of_nonterminal_extra {
                    self.end_of_nonterminal_extra = false;
                    true
                } else {
                    false
                };
            }
        };
        if other.index < vec.len() && vec[other.index] {
            vec.set(other.index, false);
            return true;
        }
        false
    }

    pub fn is_empty(&self) -> bool {
        !self.eof
            && !self.end_of_nonterminal_extra
            && !self.terminal_bits.iter().any(|a| a)
            && !self.external_bits.iter().any(|a| a)
    }

    pub fn insert_all_terminals(&mut self, other: &Self) -> bool {
        let mut result = false;
        if other.terminal_bits.len() > self.terminal_bits.len() {
            self.terminal_bits.resize(other.terminal_bits.len(), false);
        }
        for (i, element) in other.terminal_bits.iter().enumerate() {
            if element {
                result |= !self.terminal_bits[i];
                self.terminal_bits.set(i, element);
            }
        }
        result
    }

    fn insert_all_externals(&mut self, other: &Self) -> bool {
        let mut result = false;
        if other.external_bits.len() > self.external_bits.len() {
            self.external_bits.resize(other.external_bits.len(), false);
        }
        for (i, element) in other.external_bits.iter().enumerate() {
            if element {
                result |= !self.external_bits[i];
                self.external_bits.set(i, element);
            }
        }
        result
    }

    pub fn insert_all(&mut self, other: &Self) -> bool {
        let mut result = false;
        if other.eof {
            result |= !self.eof;
            self.eof = true;
        }
        if other.end_of_nonterminal_extra {
            result |= !self.end_of_nonterminal_extra;
            self.end_of_nonterminal_extra = true;
        }
        result |= self.insert_all_terminals(other);
        result |= self.insert_all_externals(other);
        result
    }
}

impl FromIterator<Symbol> for TokenSet {
    fn from_iter<T: IntoIterator<Item = Symbol>>(iter: T) -> Self {
        let mut result = Self::new();
        for symbol in iter {
            result.insert(symbol);
        }
        result
    }
}

fn add_metadata<T: FnOnce(&mut MetadataParams)>(input: Rule, f: T) -> Rule {
    match input {
        Rule::Metadata { rule, mut params } if !params.is_token => {
            f(&mut params);
            Rule::Metadata { rule, params }
        }
        _ => {
            let mut params = MetadataParams::default();
            f(&mut params);
            Rule::Metadata {
                rule: Box::new(input),
                params,
            }
        }
    }
}

fn choice_helper(result: &mut Vec<Rule>, rule: Rule) {
    match rule {
        Rule::Choice(elements) => {
            for element in elements {
                choice_helper(result, element);
            }
        }
        _ => {
            if !result.contains(&rule) {
                result.push(rule);
            }
        }
    }
}

impl fmt::Display for Precedence {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        match self {
            Self::Integer(i) => write!(f, "{i}"),
            Self::Name(s) => write!(f, "'{s}'"),
            Self::None => write!(f, "none"),
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn test_converting_a_rule_back_to_javascript() {
        struct TestCase {
            rule: Rule,
            expected: &'static str,
        }

        let test_cases = [
            TestCase {
                rule: Rule::Seq(vec![
                    Rule::Pattern("[0-9]".to_string(), "i".to_string()),
                    Rule::Choice(vec![
                        Rule::Metadata {
                            params: MetadataParams {
                                precedence: Precedence::Integer(1),
                                dynamic_precedence: 0,
                                associativity: None,
                                is_token: true,
                                is_main_token: false,
                                alias: None,
                                field_name: None,
                            },
                            rule: Box::new(Rule::String("o".to_string())),
                        },
                        Rule::Metadata {
                            params: MetadataParams {
                                precedence: Precedence::None,
                                dynamic_precedence: 0,
                                associativity: Some(Associativity::Left),
                                is_token: false,
                                is_main_token: false,
                                alias: None,
                                field_name: None,
                            },
                            rule: Box::new(Rule::NamedSymbol("p".to_string())),
                        },
                    ]),
                ]),
                expected: "seq(/[0-9]/i, choice(token(prec(1, 'o')), prec.left($.p)))",
            },
            TestCase {
                rule: Rule::Metadata {
                    params: MetadataParams {
                        precedence: Precedence::None,
                        dynamic_precedence: 5,
                        associativity: None,
                        is_token: false,
                        is_main_token: false,
                        alias: Some(Alias {
                            value: "p".to_string(),
                            is_named: false,
                        }),
                        field_name: Some("q".to_string()),
                    },
                    rule: Box::new(Rule::NamedSymbol("o".to_string())),
                },
                expected: "field('q', alias(prec.dynamic(5, $.o), 'p'))",
            },
            TestCase {
                rule: Rule::Seq(vec![
                    Rule::Repeat(Box::new(Rule::NamedSymbol("o".to_string()))),
                    Rule::Choice(vec![
                        Rule::Repeat(Box::new(Rule::NamedSymbol("p".to_string()))),
                        Rule::Blank,
                    ]),
                ]),
                expected: "seq(repeat1($.o), repeat($.p))",
            },
        ];

        for test in test_cases.iter() {
            assert_eq!(test.rule.to_string(), test.expected);
        }
    }
}
