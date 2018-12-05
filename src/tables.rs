use std::collections::HashMap;
use std::ops::Range;
use crate::rules::{Associativity, Symbol, Alias};

pub type AliasSequenceId = usize;
pub type ParseStateId = usize;
pub type LexStateId = usize;

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum ParseActionType {
    Error,
    Shift,
    Reduce,
    Accept,
    Recover,
}

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum ParseAction {
    Accept,
    Error,
    Shift(ParseStateId),
    ShiftExtra,
    Recover,
    Reduce {
        symbol: Symbol,
        child_count: usize,
        precedence: i32,
        dynamic_precedence: i32,
        associativity: Option<Associativity>,
        alias_sequence_id: Option<AliasSequenceId>,
        is_repetition: bool,
    }
}

#[derive(Clone, Debug, PartialEq, Eq)]
pub struct ParseTableEntry {
    actions: Vec<ParseAction>,
    reusable: bool,
}

#[derive(Clone, Debug, PartialEq, Eq)]
pub struct ParseState {
    terminal_entries: HashMap<Symbol, ParseTableEntry>,
    nonterminal_entries: HashMap<Symbol, ParseStateId>
}

#[derive(Debug, PartialEq, Eq)]
pub struct ParseTable {
    states: Vec<ParseState>,
    alias_sequences: Vec<Vec<Alias>>,
}

#[derive(Clone, Debug, PartialEq, Eq)]
pub struct AdvanceAction {
    state: LexStateId,
    precedence: Range<i32>,
    in_main_token: bool,
}

#[derive(Clone, Debug, PartialEq, Eq)]
pub struct AcceptTokenAction {
    symbol: Symbol,
    precedence: i32,
    implicit_precedence: i32,
}

#[derive(Clone, Debug, PartialEq, Eq)]
pub struct LexState {
    advance_actions: HashMap<Symbol, AdvanceAction>,
    accept_action: Option<AcceptTokenAction>,
}

#[derive(Debug, PartialEq, Eq)]
pub struct LexTable {
    states: Vec<LexState>,
}
