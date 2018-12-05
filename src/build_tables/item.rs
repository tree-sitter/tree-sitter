use crate::grammars::Production;
use std::collections::HashMap;
use bitvec::BitVec;

#[derive(Debug, PartialEq, Eq)]
pub(super) struct LookaheadSet {
    terminal_bits: BitVec,
    external_bits: BitVec,
    eof: bool,
}

#[derive(Clone, Copy, Debug, PartialEq, Eq, Hash)]
pub(super) struct ParseItem {
    variable_index: u32,
    production_index: u32,
    step_index: u32,
}

#[derive(Debug, PartialEq, Eq)]
pub(super) struct ParseItemSet {
    entries: HashMap<ParseItem, LookaheadSet>
}
