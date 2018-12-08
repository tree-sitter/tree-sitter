use std::rc::Rc;
use std::char;
use std::collections::HashMap;

#[derive(Clone, Copy, Debug, PartialEq, Eq, Hash)]
pub(crate) enum SymbolType {
    External,
    Terminal,
    NonTerminal,
}

#[derive(Clone, Copy, Debug, PartialEq, Eq, Hash)]
pub(crate) enum Associativity {
    Left,
    Right
}

#[derive(Clone, Debug, PartialEq, Eq, Hash)]
pub(crate) struct Alias {
    pub value: String,
    pub is_named: bool,
}

pub(crate) type AliasMap = HashMap<Symbol, Alias>;

#[derive(Clone, Debug, Default, PartialEq, Eq, Hash)]
pub(crate) struct MetadataParams {
    pub precedence: Option<i32>,
    pub dynamic_precedence: i32,
    pub associativity: Option<Associativity>,
    pub is_token: bool,
    pub is_string: bool,
    pub is_active: bool,
    pub is_main_token: bool,
    pub is_excluded: bool,
    pub alias: Option<Alias>,
}

#[derive(Clone, Copy, Debug, PartialEq, Eq, Hash)]
pub(crate) struct Symbol {
    pub kind: SymbolType,
    pub index: usize,
}

#[derive(Clone, Debug, PartialEq, Eq, Hash)]
pub(crate) enum Rule {
    Blank,
    String(String),
    Pattern(String),
    NamedSymbol(String),
    Symbol(Symbol),
    Choice {
        elements: Vec<Rule>,
    },
    Metadata {
        params: MetadataParams,
        rule: Rc<Rule>,
    },
    Repeat(Rc<Rule>),
    Seq {
        left: Rc<Rule>,
        right: Rc<Rule>,
    }
}

impl Rule {
    pub fn token(content: Rule) -> Self {
        add_metadata(content, |params| {
            params.is_token = true;
        })
    }

    pub fn immediate_token(content: Rule) -> Self {
        add_metadata(content, |params| {
            params.is_token = true;
            params.is_main_token = true;
        })
    }

    pub fn prec(value: i32, content: Rule) -> Self {
        add_metadata(content, |params| {
            params.precedence = Some(value);
        })
    }

    pub fn prec_left(value: i32, content: Rule) -> Self {
        add_metadata(content, |params| {
            params.associativity = Some(Associativity::Left);
            params.precedence = Some(value);
        })
    }

    pub fn prec_right(value: i32, content: Rule) -> Self {
        add_metadata(content, |params| {
            params.associativity = Some(Associativity::Right);
            params.precedence = Some(value);
        })
    }

    pub fn repeat(rule: Rule) -> Self {
        Rule::Repeat(Rc::new(rule))
    }

    pub fn choice(rules: Vec<Rule>) -> Self {
        let mut elements = Vec::with_capacity(rules.len());
        for rule in rules {
            choice_helper(&mut elements, rule);
        }
        Rule::Choice { elements }
    }

    pub fn seq(rules: Vec<Rule>) -> Self {
        let mut result = Rule::Blank;
        for rule in rules {
            match rule {
                Rule::Blank => continue,
                Rule::Metadata { rule, params: _ } => {
                    if *rule == Rule::Blank {
                        continue;
                    }
                },
                _ => {
                    if result == Rule::Blank {
                        result = rule;
                    } else {
                        result = Rule::Seq {
                            left: Rc::new(result),
                            right: Rc::new(rule),
                        }
                    }
                }
            }
        }
        result
    }

    pub fn terminal(index: usize) -> Self {
        Rule::Symbol(Symbol::terminal(index))
    }

    pub fn non_terminal(index: usize) -> Self {
        Rule::Symbol(Symbol::non_terminal(index))
    }

    pub fn external(index: usize) -> Self {
        Rule::Symbol(Symbol::external(index))
    }

    pub fn named(name: &'static str) -> Self {
        Rule::NamedSymbol(name.to_string())
    }

    pub fn string(value: &'static str) -> Self {
        Rule::String(value.to_string())
    }

    pub fn pattern(value: &'static str) -> Self {
        Rule::Pattern(value.to_string())
    }
}

impl Symbol {
    pub fn is_non_terminal(&self) -> bool {
        return self.kind == SymbolType::NonTerminal
    }

    pub fn is_external(&self) -> bool {
        return self.kind == SymbolType::External
    }

    pub fn non_terminal(index: usize) -> Self {
        Symbol { kind: SymbolType::NonTerminal, index }
    }

    pub fn terminal(index: usize) -> Self {
        Symbol { kind: SymbolType::Terminal, index }
    }

    pub fn external(index: usize) -> Self {
        Symbol { kind: SymbolType::External, index }
    }
}

impl From<Symbol> for Rule {
    fn from(symbol: Symbol) -> Self {
        Rule::Symbol(symbol)
    }
}

fn add_metadata<T: Fn(&mut MetadataParams)>(input: Rule, f: T) -> Rule {
    match input {
        Rule::Metadata { rule, mut params } => {
            f(&mut params);
            Rule::Metadata { rule, params }
        },
        _ => {
            let mut params = MetadataParams::default();
            f(&mut params);
            Rule::Metadata { rule: Rc::new(input), params }
        }
    }
}

fn choice_helper(result: &mut Vec<Rule>, rule: Rule) {
    match rule {
        Rule::Choice {elements} => {
            for element in elements {
                choice_helper(result, element);
            }
        },
        _ => {
            if !result.contains(&rule) {
                result.push(rule);
            }
        }
    }
}
