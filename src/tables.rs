use std::collections::HashMap;
use std::ops::Range;
use crate::rules::{Associativity, Symbol, Alias};

pub(crate) type AliasSequenceId = usize;
pub(crate) type ParseStateId = usize;
pub(crate) type LexStateId = usize;

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub(crate) enum ParseAction {
    Accept,
    Shift {
        state: ParseStateId,
        is_repetition: bool,
    },
    ShiftExtra,
    Recover,
    Reduce {
        symbol: Symbol,
        child_count: usize,
        precedence: i32,
        dynamic_precedence: i32,
        associativity: Option<Associativity>,
        alias_sequence_id: AliasSequenceId,
    }
}

#[derive(Clone, Debug, PartialEq, Eq)]
pub(crate) struct ParseTableEntry {
    pub actions: Vec<ParseAction>,
    pub reusable: bool,
}

#[derive(Clone, Debug, PartialEq, Eq)]
pub(crate) struct ParseState {
    pub terminal_entries: HashMap<Symbol, ParseTableEntry>,
    pub nonterminal_entries: HashMap<Symbol, ParseStateId>
}

#[derive(Debug, PartialEq, Eq)]
pub(crate) struct ParseTable {
    pub states: Vec<ParseState>,
    pub symbols: Vec<Symbol>,
    pub alias_sequences: Vec<Vec<Option<Alias>>>,
}

#[derive(Clone, Debug, PartialEq, Eq)]
pub(crate) struct AdvanceAction {
    pub state: LexStateId,
    pub precedence: Range<i32>,
    pub in_main_token: bool,
}

#[derive(Clone, Debug, PartialEq, Eq)]
pub(crate) struct AcceptTokenAction {
    pub symbol: Symbol,
    pub precedence: i32,
    pub implicit_precedence: i32,
}

#[derive(Clone, Debug, PartialEq, Eq)]
pub(crate) struct LexState {
    pub advance_actions: HashMap<Symbol, AdvanceAction>,
    pub accept_action: Option<AcceptTokenAction>,
}

#[derive(Debug, PartialEq, Eq)]
pub(crate) struct LexTable {
    pub states: Vec<LexState>,
}

impl ParseTableEntry {
    pub fn new() -> Self {
        Self {
            reusable: true,
            actions: Vec::new(),
        }
    }
}

impl ParseAction {
    pub fn precedence(&self) -> i32 {
        if let ParseAction::Reduce { precedence, .. } = self {
            *precedence
        } else {
            0
        }
    }
}
