use crate::{
    util::{self, snwrite},
    *,
};

use std::{
    ffi::{self, CStr},
    io::Write,
    os, ptr,
    time::{Duration, Instant},
};

#[cfg(all(not(feature = "capi"), unix))]
use std::{fs, io::BufWriter, os::unix::io::FromRawFd};

static mut MAX_VERSION_COUNT: os::raw::c_uint = 6 as os::raw::c_int as os::raw::c_uint;
static mut MAX_VERSION_COUNT_OVERFLOW: os::raw::c_uint = 4 as os::raw::c_int as os::raw::c_uint;
static mut MAX_SUMMARY_DEPTH: os::raw::c_uint = 16 as os::raw::c_int as os::raw::c_uint;
static mut MAX_COST_DIFFERENCE: os::raw::c_uint =
    (16 as os::raw::c_int * 100 as os::raw::c_int) as os::raw::c_uint;
static mut OP_COUNT_PER_TIMEOUT_CHECK: os::raw::c_uint = 100 as os::raw::c_int as os::raw::c_uint;

#[derive(Copy, Clone)]
#[repr(C)]
pub struct TokenCache {
    pub token: Subtree,
    pub last_external_token: Subtree,
    pub byte_index: u32,
}

#[cfg_attr(feature = "capi", derive(Clone, Copy))]
#[repr(C)]
pub struct TSParser {
    pub lexer: Lexer,
    pub stack: *mut Stack,
    pub tree_pool: SubtreePool,
    pub language: *const TSLanguage,
    pub reduce_actions: ReduceActionSet,
    pub finished_tree: Subtree,
    pub scratch_tree_data: SubtreeHeapData,
    pub scratch_tree: MutableSubtree,
    pub token_cache: TokenCache,
    pub reusable_node: ReusableNode,
    pub external_scanner_payload: *mut ffi::c_void,
    pub dot_graph_file: util::File,
    pub end_instant: Option<Instant>,
    pub timeout_duration: Duration,
    pub accept_count: os::raw::c_uint,
    pub operation_count: os::raw::c_uint,
    pub cancellation_flag: *const usize,
    pub old_tree: Subtree,
    pub included_range_differences: TSRangeArray,
    pub included_range_difference_index: os::raw::c_uint,
}

pub const ErrorComparisonTakeRight: ErrorComparison = 4;
pub const ErrorComparisonPreferRight: ErrorComparison = 3;
pub const ErrorComparisonNone: ErrorComparison = 2;
pub const ErrorComparisonPreferLeft: ErrorComparison = 1;
pub const ErrorComparisonTakeLeft: ErrorComparison = 0;
pub type ErrorComparison = os::raw::c_uint;

#[derive(Copy, Clone)]
#[repr(C)]
pub struct ErrorStatus {
    pub cost: os::raw::c_uint,
    pub node_count: os::raw::c_uint,
    pub dynamic_precedence: os::raw::c_int,
    pub is_in_error: bool,
}

#[derive(Copy, Clone)]
#[repr(C)]
pub struct TSStringInput {
    pub string: *const os::raw::c_char,
    pub length: u32,
}

// StringInput
unsafe extern "C" fn ts_string_input_read(
    mut _self: *mut ffi::c_void,
    mut byte: u32,
    mut _id: TSPoint,
    mut length: *mut u32,
) -> *const os::raw::c_char {
    let mut self_0: *mut TSStringInput = _self as *mut TSStringInput;
    if byte >= (*self_0).length {
        *length = 0 as os::raw::c_int as u32;
        b"\x00" as *const u8 as *const os::raw::c_char
    } else {
        *length = (*self_0).length.wrapping_sub(byte);
        (*self_0).string.offset(byte as isize)
    }
}
// Parser - Private
unsafe extern "C" fn ts_parser__log(mut self_0: *mut TSParser) {
    if (*self_0).lexer.logger.log.is_some() {
        (*self_0)
            .lexer
            .logger
            .log
            .expect("non-null function pointer")(
            (*self_0).lexer.logger.payload,
            TSLogTypeParse,
            (*self_0).lexer.debug_buffer.as_mut_ptr(),
        );
    }
    if (*self_0).dot_graph_file.is_valid() {
        let dot_graph_file = &mut (*self_0).dot_graph_file;
        write!(dot_graph_file, "graph {{\nlabel=\"").unwrap();

        let mut c: *mut os::raw::c_char = &mut *(*self_0)
            .lexer
            .debug_buffer
            .as_mut_ptr()
            .offset(0 as os::raw::c_int as isize)
            as *mut os::raw::c_char;
        while *c as os::raw::c_int != 0 as os::raw::c_int {
            if *c as os::raw::c_int == '\"' as i32 {
                write!(dot_graph_file, "\\").unwrap();
            }
            write!(dot_graph_file, "{}", *c as u8 as char).unwrap();
            c = c.offset(1)
        }
        write!(dot_graph_file, "\"\n}}\n\n").unwrap();
    };
}
unsafe extern "C" fn ts_parser__breakdown_top_of_stack(
    mut self_0: *mut TSParser,
    mut version: StackVersion,
) -> bool {
    let mut did_break_down: bool = false;
    let mut pending: bool = false;
    loop {
        let mut pop: StackSliceArray = ts_stack_pop_pending((*self_0).stack, version);
        if pop.size == 0 {
            break;
        }
        did_break_down = true;
        pending = false;
        let mut i: u32 = 0 as os::raw::c_int as u32;
        while i < pop.size {
            let mut slice: StackSlice = *pop.contents.offset(i as isize);
            let mut state: TSStateId = ts_stack_state((*self_0).stack, slice.version);
            assert!((0 as os::raw::c_int as u32) < slice.subtrees.size);
            let mut parent: Subtree =
                *(&mut *slice.subtrees.contents.offset(0 as os::raw::c_int as isize)
                    as *mut Subtree);
            let mut j: u32 = 0 as os::raw::c_int as u32;
            let mut n: u32 = ts_subtree_child_count(parent);
            while j < n {
                let mut child: Subtree = *(*parent.ptr)
                    .c2rust_unnamed
                    .c2rust_unnamed
                    .children
                    .offset(j as isize);
                pending = ts_subtree_child_count(child) > 0 as os::raw::c_int as os::raw::c_uint;
                if ts_subtree_is_error(child) {
                    state = 0 as os::raw::c_int as TSStateId
                } else if !ts_subtree_extra(child) {
                    state =
                        ts_language_next_state((*self_0).language, state, ts_subtree_symbol(child))
                }
                ts_subtree_retain(child);
                ts_stack_push((*self_0).stack, slice.version, child, pending, state);
                j = j.wrapping_add(1)
            }
            let mut j_0: u32 = 1 as os::raw::c_int as u32;
            while j_0 < slice.subtrees.size {
                let mut tree: Subtree = *slice.subtrees.contents.offset(j_0 as isize);
                ts_stack_push((*self_0).stack, slice.version, tree, false, state);
                j_0 = j_0.wrapping_add(1)
            }
            ts_subtree_release(&mut (*self_0).tree_pool, parent);
            array__delete(&mut slice.subtrees as *mut SubtreeArray as *mut VoidArray);
            if (*self_0).lexer.logger.log.is_some() || (*self_0).dot_graph_file.is_valid() {
                snwrite!(
                    (*self_0).lexer.debug_buffer.as_mut_ptr(),
                    1024,
                    "breakdown_top_of_stack tree:{}",
                    CStr::from_ptr(ts_language_symbol_name(
                        (*self_0).language,
                        ts_subtree_symbol(parent)
                    ))
                    .to_string_lossy(),
                )
                .unwrap();
                ts_parser__log(self_0);
            }
            if (*self_0).dot_graph_file.is_valid() {
                let dot_graph_file = &mut (*self_0).dot_graph_file;
                ts_stack_print_dot_graph((*self_0).stack, (*self_0).language, dot_graph_file);
                write!(dot_graph_file, "\n\n",).unwrap();
            }
            i = i.wrapping_add(1)
        }
        if !pending {
            break;
        }
    }
    did_break_down
}
unsafe extern "C" fn ts_parser__breakdown_lookahead(
    mut self_0: *mut TSParser,
    mut lookahead: *mut Subtree,
    mut state: TSStateId,
    mut reusable_node: *mut ReusableNode,
) {
    let mut did_descend: bool = false;
    let mut tree: Subtree = reusable_node_tree(reusable_node);
    while ts_subtree_child_count(tree) > 0 as os::raw::c_int as os::raw::c_uint
        && ts_subtree_parse_state(tree) as os::raw::c_int != state as os::raw::c_int
    {
        if (*self_0).lexer.logger.log.is_some() || (*self_0).dot_graph_file.is_valid() {
            snwrite!(
                (*self_0).lexer.debug_buffer.as_mut_ptr(),
                1024,
                "state_mismatch sym:{}",
                CStr::from_ptr(ts_language_symbol_name(
                    (*self_0).language,
                    ts_subtree_symbol(tree)
                ))
                .to_string_lossy(),
            )
            .unwrap();
            ts_parser__log(self_0);
        }
        reusable_node_descend(reusable_node);
        tree = reusable_node_tree(reusable_node);
        did_descend = true
    }
    if did_descend {
        ts_subtree_release(&mut (*self_0).tree_pool, *lookahead);
        *lookahead = tree;
        ts_subtree_retain(*lookahead);
    };
}
unsafe extern "C" fn ts_parser__compare_versions(
    mut _self_0: *mut TSParser,
    mut a: ErrorStatus,
    mut b: ErrorStatus,
) -> ErrorComparison {
    if !a.is_in_error && b.is_in_error as os::raw::c_int != 0 {
        if a.cost < b.cost {
            return ErrorComparisonTakeLeft;
        } else {
            return ErrorComparisonPreferLeft;
        }
    }
    if a.is_in_error as os::raw::c_int != 0 && !b.is_in_error {
        if b.cost < a.cost {
            return ErrorComparisonTakeRight;
        } else {
            return ErrorComparisonPreferRight;
        }
    }
    if a.cost < b.cost {
        if b.cost
            .wrapping_sub(a.cost)
            .wrapping_mul((1 as os::raw::c_int as os::raw::c_uint).wrapping_add(a.node_count))
            > MAX_COST_DIFFERENCE
        {
            return ErrorComparisonTakeLeft;
        } else {
            return ErrorComparisonPreferLeft;
        }
    }
    if b.cost < a.cost {
        if a.cost
            .wrapping_sub(b.cost)
            .wrapping_mul((1 as os::raw::c_int as os::raw::c_uint).wrapping_add(b.node_count))
            > MAX_COST_DIFFERENCE
        {
            return ErrorComparisonTakeRight;
        } else {
            return ErrorComparisonPreferRight;
        }
    }
    if a.dynamic_precedence > b.dynamic_precedence {
        return ErrorComparisonPreferLeft;
    }
    if b.dynamic_precedence > a.dynamic_precedence {
        return ErrorComparisonPreferRight;
    }
    ErrorComparisonNone
}
unsafe extern "C" fn ts_parser__version_status(
    mut self_0: *mut TSParser,
    mut version: StackVersion,
) -> ErrorStatus {
    let mut cost: os::raw::c_uint = ts_stack_error_cost((*self_0).stack, version);
    let mut is_paused: bool = ts_stack_is_paused((*self_0).stack, version);
    if is_paused {
        cost = cost.wrapping_add(100)
    }
    ErrorStatus {
        cost,
        node_count: ts_stack_node_count_since_error((*self_0).stack, version),
        dynamic_precedence: ts_stack_dynamic_precedence((*self_0).stack, version),
        is_in_error: is_paused as os::raw::c_int != 0
            || ts_stack_state((*self_0).stack, version) as os::raw::c_int == 0 as os::raw::c_int,
    }
}
unsafe extern "C" fn ts_parser__better_version_exists(
    mut self_0: *mut TSParser,
    mut version: StackVersion,
    mut is_in_error: bool,
    mut cost: os::raw::c_uint,
) -> bool {
    if !(*self_0).finished_tree.ptr.is_null()
        && ts_subtree_error_cost((*self_0).finished_tree) <= cost
    {
        return true;
    }
    let mut position: Length = ts_stack_position((*self_0).stack, version);
    let mut status = ErrorStatus {
        cost,
        node_count: ts_stack_node_count_since_error((*self_0).stack, version),
        dynamic_precedence: ts_stack_dynamic_precedence((*self_0).stack, version),
        is_in_error,
    };
    let mut i: StackVersion = 0 as os::raw::c_int as StackVersion;
    let mut n: StackVersion = ts_stack_version_count((*self_0).stack);
    while i < n {
        if !(i == version
            || !ts_stack_is_active((*self_0).stack, i)
            || ts_stack_position((*self_0).stack, i).bytes < position.bytes)
        {
            let mut status_i: ErrorStatus = ts_parser__version_status(self_0, i);
            match ts_parser__compare_versions(self_0, status, status_i) as os::raw::c_uint {
                4 => return true,
                3 => {
                    if ts_stack_can_merge((*self_0).stack, i, version) {
                        return true;
                    }
                }
                _ => {}
            }
        }
        i = i.wrapping_add(1)
    }
    false
}
unsafe extern "C" fn ts_parser__restore_external_scanner(
    mut self_0: *mut TSParser,
    mut external_token: Subtree,
) {
    if !external_token.ptr.is_null() {
        (*(*self_0).language)
            .external_scanner
            .deserialize
            .expect("non-null function pointer")(
            (*self_0).external_scanner_payload,
            ts_external_scanner_state_data(
                &(*external_token.ptr).c2rust_unnamed.external_scanner_state,
            ),
            (*external_token.ptr)
                .c2rust_unnamed
                .external_scanner_state
                .length,
        );
    } else {
        (*(*self_0).language)
            .external_scanner
            .deserialize
            .expect("non-null function pointer")(
            (*self_0).external_scanner_payload,
            ptr::null(),
            0 as os::raw::c_int as os::raw::c_uint,
        );
    };
}
unsafe extern "C" fn ts_parser__can_reuse_first_leaf(
    mut self_0: *mut TSParser,
    mut state: TSStateId,
    mut tree: Subtree,
    mut table_entry: *mut TableEntry,
) -> bool {
    let mut current_lex_mode: TSLexMode = *(*(*self_0).language).lex_modes.offset(state as isize);
    let mut leaf_symbol: TSSymbol = ts_subtree_leaf_symbol(tree);
    let mut leaf_state: TSStateId = ts_subtree_leaf_parse_state(tree);
    let mut leaf_lex_mode: TSLexMode = *(*(*self_0).language).lex_modes.offset(leaf_state as isize);
    // At the end of a non-terminal extra node, the lexer normally returns
    // NULL, which indicates that the parser should look for a reduce action
    // at symbol `0`. Avoid reusing tokens in this situation to ensure that
    // the same thing happens when incrementally reparsing.
    if current_lex_mode.lex_state as os::raw::c_int
        == -(1 as os::raw::c_int) as u16 as os::raw::c_int
    {
        return false;
    }
    // If the token was created in a state with the same set of lookaheads, it is reusable.
    if (*table_entry).action_count > 0 as os::raw::c_int as os::raw::c_uint
        && leaf_lex_mode == current_lex_mode
        && (leaf_symbol as os::raw::c_int
            != (*(*self_0).language).keyword_capture_token as os::raw::c_int
            || !ts_subtree_is_keyword(tree)
                && ts_subtree_parse_state(tree) as os::raw::c_int == state as os::raw::c_int)
    {
        return true;
    }
    // Empty tokens are not reusable in states with different lookaheads.
    if ts_subtree_size(tree).bytes == 0 as os::raw::c_int as os::raw::c_uint
        && leaf_symbol as os::raw::c_int != 0 as os::raw::c_int
    {
        return false;
    }
    // If the current state allows external tokens or other tokens that conflict with this
    // token, this token is not reusable.
    current_lex_mode.external_lex_state as os::raw::c_int == 0 as os::raw::c_int
        && (*table_entry).is_reusable as os::raw::c_int != 0
}
unsafe extern "C" fn ts_parser__lex(
    mut self_0: *mut TSParser,
    mut version: StackVersion,
    mut parse_state: TSStateId,
) -> Subtree {
    let mut start_position: Length = ts_stack_position((*self_0).stack, version);
    let mut external_token: Subtree = ts_stack_last_external_token((*self_0).stack, version);
    let mut lex_mode: TSLexMode = *(*(*self_0).language).lex_modes.offset(parse_state as isize);
    if lex_mode.lex_state as os::raw::c_int == -(1 as os::raw::c_int) as u16 as os::raw::c_int {
        return Subtree {
            ptr: std::ptr::null::<SubtreeHeapData>(),
        };
    }
    let mut valid_external_tokens: *const bool = ts_language_enabled_external_tokens(
        (*self_0).language,
        lex_mode.external_lex_state as os::raw::c_uint,
    );
    let mut found_external_token: bool = false;
    let mut error_mode: bool = parse_state as os::raw::c_int == 0 as os::raw::c_int;
    let mut skipped_error: bool = false;
    let mut first_error_character: i32 = 0 as os::raw::c_int;
    let mut error_start_position: Length = length_zero();
    let mut error_end_position: Length = length_zero();
    let mut lookahead_end_byte: u32 = 0 as os::raw::c_int as u32;
    ts_lexer_reset(&mut (*self_0).lexer, start_position);
    loop {
        let mut current_position: Length = (*self_0).lexer.current_position;
        if !valid_external_tokens.is_null() {
            if (*self_0).lexer.logger.log.is_some() || (*self_0).dot_graph_file.is_valid() {
                snwrite!(
                    (*self_0).lexer.debug_buffer.as_mut_ptr(),
                    1024,
                    "lex_external state:{}, row:{}, column:{}",
                    lex_mode.external_lex_state as os::raw::c_int,
                    current_position.extent.row.wrapping_add(1),
                    current_position.extent.column,
                )
                .unwrap();
                ts_parser__log(self_0);
            }
            ts_lexer_start(&mut (*self_0).lexer);
            ts_parser__restore_external_scanner(self_0, external_token);
            let mut found_token: bool = (*(*self_0).language)
                .external_scanner
                .scan
                .expect("non-null function pointer")(
                (*self_0).external_scanner_payload,
                &mut (*self_0).lexer.data,
                valid_external_tokens,
            );
            ts_lexer_finish(&mut (*self_0).lexer, &mut lookahead_end_byte);
            // Zero-length external tokens are generally allowed, but they're not
            // allowed right after a syntax error. This is for two reasons:
            // 1. After a syntax error, the lexer is looking for any possible token,
            //    as opposed to the specific set of tokens that are valid in some
            //    parse state. In this situation, it's very easy for an external
            //    scanner to produce unwanted zero-length tokens.
            // 2. The parser sometimes inserts *missing* tokens to recover from
            //    errors. These tokens are also zero-length. If we allow more
            //    zero-length tokens to be created after missing tokens, it
            //    can lead to infinite loops. Forbidding zero-length tokens
            //    right at the point of error recovery is a conservative strategy
            //    for preventing this kind of infinite loop.
            if found_token as os::raw::c_int != 0
                && ((*self_0).lexer.token_end_position.bytes > current_position.bytes
                    || !error_mode
                        && ts_stack_has_advanced_since_error((*self_0).stack, version)
                            as os::raw::c_int
                            != 0)
            {
                found_external_token = true;
                break;
            } else {
                ts_lexer_reset(&mut (*self_0).lexer, current_position);
            }
        }
        if (*self_0).lexer.logger.log.is_some() || (*self_0).dot_graph_file.is_valid() {
            snwrite!(
                (*self_0).lexer.debug_buffer.as_mut_ptr(),
                1024,
                "lex_internal state:{}, row:{}, column:{}",
                lex_mode.lex_state as os::raw::c_int,
                current_position.extent.row.wrapping_add(1),
                current_position.extent.column,
            )
            .unwrap();
            ts_parser__log(self_0);
        }
        ts_lexer_start(&mut (*self_0).lexer);
        let mut found_token_0: bool = (*(*self_0).language)
            .lex_fn
            .expect("non-null function pointer")(
            &mut (*self_0).lexer.data, lex_mode.lex_state
        );
        ts_lexer_finish(&mut (*self_0).lexer, &mut lookahead_end_byte);
        if found_token_0 {
            break;
        }
        if !error_mode {
            error_mode = true;
            lex_mode = *(*(*self_0).language)
                .lex_modes
                .offset(0 as os::raw::c_int as isize);
            valid_external_tokens = ts_language_enabled_external_tokens(
                (*self_0).language,
                lex_mode.external_lex_state as os::raw::c_uint,
            );
            ts_lexer_reset(&mut (*self_0).lexer, start_position);
        } else {
            if !skipped_error {
                if (*self_0).lexer.logger.log.is_some() || (*self_0).dot_graph_file.is_valid() {
                    snwrite!(
                        (*self_0).lexer.debug_buffer.as_mut_ptr(),
                        1024,
                        "skip_unrecognized_character",
                    )
                    .unwrap();
                    ts_parser__log(self_0);
                }
                skipped_error = true;
                error_start_position = (*self_0).lexer.token_start_position;
                error_end_position = (*self_0).lexer.token_start_position;
                first_error_character = (*self_0).lexer.data.lookahead
            }
            if (*self_0).lexer.current_position.bytes == error_end_position.bytes {
                if (*self_0).lexer.data.eof.expect("non-null function pointer")(
                    &mut (*self_0).lexer.data,
                ) {
                    (*self_0).lexer.data.result_symbol = -(1 as os::raw::c_int) as TSSymbol;
                    break;
                } else {
                    (*self_0)
                        .lexer
                        .data
                        .advance
                        .expect("non-null function pointer")(
                        &mut (*self_0).lexer.data, false
                    );
                }
            }
            error_end_position = (*self_0).lexer.current_position
        }
    }
    let mut result: Subtree = Subtree {
        data: SubtreeInlineData {
            is_inline_visible_named_extra_has_changes_is_missing_is_keyword: [0; 1],
            symbol: 0,
            padding_bytes: 0,
            size_bytes: 0,
            padding_columns: 0,
            padding_rows_lookahead_bytes: [0; 1],
            parse_state: 0,
        },
    };
    if skipped_error {
        let mut padding: Length = length_sub(error_start_position, start_position);
        let mut size: Length = length_sub(error_end_position, error_start_position);
        let mut lookahead_bytes: u32 = lookahead_end_byte.wrapping_sub(error_end_position.bytes);
        result = ts_subtree_new_error(
            &mut (*self_0).tree_pool,
            first_error_character,
            padding,
            size,
            lookahead_bytes,
            parse_state,
            (*self_0).language,
        );
        if (*self_0).lexer.logger.log.is_some() || (*self_0).dot_graph_file.is_valid() {
            snwrite!(
                (*self_0).lexer.debug_buffer.as_mut_ptr(),
                1024,
                "lexed_lookahead sym:{}, size:{}, character:\'{}\'",
                CStr::from_ptr(ts_language_symbol_name(
                    (*self_0).language,
                    ts_subtree_symbol(result)
                ))
                .to_string_lossy(),
                ts_subtree_total_size(result).bytes,
                first_error_character as u8 as char,
            )
            .unwrap();
            ts_parser__log(self_0);
        }
    } else {
        if (*self_0).lexer.token_end_position.bytes < (*self_0).lexer.token_start_position.bytes {
            (*self_0).lexer.token_start_position = (*self_0).lexer.token_end_position
        }
        let mut is_keyword: bool = false;
        let mut symbol: TSSymbol = (*self_0).lexer.data.result_symbol;
        let mut padding_0: Length =
            length_sub((*self_0).lexer.token_start_position, start_position);
        let mut size_0: Length = length_sub(
            (*self_0).lexer.token_end_position,
            (*self_0).lexer.token_start_position,
        );
        let mut lookahead_bytes_0: u32 =
            lookahead_end_byte.wrapping_sub((*self_0).lexer.token_end_position.bytes);
        if found_external_token {
            symbol = *(*(*self_0).language)
                .external_scanner
                .symbol_map
                .offset(symbol as isize)
        } else if symbol as os::raw::c_int
            == (*(*self_0).language).keyword_capture_token as os::raw::c_int
            && symbol as os::raw::c_int != 0 as os::raw::c_int
        {
            let mut end_byte: u32 = (*self_0).lexer.token_end_position.bytes;
            ts_lexer_reset(&mut (*self_0).lexer, (*self_0).lexer.token_start_position);
            ts_lexer_start(&mut (*self_0).lexer);
            if (*(*self_0).language)
                .keyword_lex_fn
                .expect("non-null function pointer")(
                &mut (*self_0).lexer.data,
                0 as os::raw::c_int as TSStateId,
            ) as os::raw::c_int
                != 0
                && (*self_0).lexer.token_end_position.bytes == end_byte
                && ts_language_has_actions(
                    (*self_0).language,
                    parse_state,
                    (*self_0).lexer.data.result_symbol,
                ) as os::raw::c_int
                    != 0
            {
                is_keyword = true;
                symbol = (*self_0).lexer.data.result_symbol
            }
        }
        result = ts_subtree_new_leaf(
            &mut (*self_0).tree_pool,
            symbol,
            padding_0,
            size_0,
            lookahead_bytes_0,
            parse_state,
            found_external_token,
            is_keyword,
            (*self_0).language,
        );
        if found_external_token {
            let mut length: os::raw::c_uint = (*(*self_0).language)
                .external_scanner
                .serialize
                .expect("non-null function pointer")(
                (*self_0).external_scanner_payload,
                (*self_0).lexer.debug_buffer.as_mut_ptr(),
            );
            ts_external_scanner_state_init(
                &mut (*(result.ptr as *mut SubtreeHeapData))
                    .c2rust_unnamed
                    .external_scanner_state,
                (*self_0).lexer.debug_buffer.as_mut_ptr(),
                length,
            );
        }
        if (*self_0).lexer.logger.log.is_some() || (*self_0).dot_graph_file.is_valid() {
            snwrite!(
                (*self_0).lexer.debug_buffer.as_mut_ptr(),
                1024,
                "lexed_lookahead sym:{}, size:{}",
                CStr::from_ptr(ts_language_symbol_name(
                    (*self_0).language,
                    ts_subtree_symbol(result)
                ))
                .to_string_lossy(),
                ts_subtree_total_size(result).bytes,
            )
            .unwrap();
            ts_parser__log(self_0);
        }
    }
    result
}
unsafe extern "C" fn ts_parser__get_cached_token(
    mut self_0: *mut TSParser,
    mut state: TSStateId,
    mut position: usize,
    mut last_external_token: Subtree,
    mut table_entry: *mut TableEntry,
) -> Subtree {
    let mut cache: *mut TokenCache = &mut (*self_0).token_cache;
    if !(*cache).token.ptr.is_null()
        && (*cache).byte_index as usize == position
        && ts_subtree_external_scanner_state_eq((*cache).last_external_token, last_external_token)
            as os::raw::c_int
            != 0
    {
        ts_language_table_entry(
            (*self_0).language,
            state,
            ts_subtree_symbol((*cache).token),
            table_entry,
        );
        if ts_parser__can_reuse_first_leaf(self_0, state, (*cache).token, table_entry) {
            ts_subtree_retain((*cache).token);
            return (*cache).token;
        }
    }
    Subtree {
        ptr: std::ptr::null::<SubtreeHeapData>(),
    }
}
unsafe extern "C" fn ts_parser__set_cached_token(
    mut self_0: *mut TSParser,
    mut byte_index: usize,
    mut last_external_token: Subtree,
    mut token: Subtree,
) {
    let mut cache: *mut TokenCache = &mut (*self_0).token_cache;
    if !token.ptr.is_null() {
        ts_subtree_retain(token);
    }
    if !last_external_token.ptr.is_null() {
        ts_subtree_retain(last_external_token);
    }
    if !(*cache).token.ptr.is_null() {
        ts_subtree_release(&mut (*self_0).tree_pool, (*cache).token);
    }
    if !(*cache).last_external_token.ptr.is_null() {
        ts_subtree_release(&mut (*self_0).tree_pool, (*cache).last_external_token);
    }
    (*cache).token = token;
    (*cache).byte_index = byte_index as u32;
    (*cache).last_external_token = last_external_token;
}
unsafe extern "C" fn ts_parser__has_included_range_difference(
    mut self_0: *const TSParser,
    mut start_position: u32,
    mut end_position: u32,
) -> bool {
    ts_range_array_intersects(
        &(*self_0).included_range_differences,
        (*self_0).included_range_difference_index,
        start_position,
        end_position,
    )
}
unsafe extern "C" fn ts_parser__reuse_node(
    mut self_0: *mut TSParser,
    mut version: StackVersion,
    mut state: *mut TSStateId,
    mut position: u32,
    mut last_external_token: Subtree,
    mut table_entry: *mut TableEntry,
) -> Subtree {
    let mut result: Subtree = Subtree {
        data: SubtreeInlineData {
            is_inline_visible_named_extra_has_changes_is_missing_is_keyword: [0; 1],
            symbol: 0,
            padding_bytes: 0,
            size_bytes: 0,
            padding_columns: 0,
            padding_rows_lookahead_bytes: [0; 1],
            parse_state: 0,
        },
    };
    loop {
        result = reusable_node_tree(&mut (*self_0).reusable_node);
        if result.ptr.is_null() {
            break;
        }
        let mut byte_offset: u32 = reusable_node_byte_offset(&mut (*self_0).reusable_node);
        let mut end_byte_offset: u32 = byte_offset.wrapping_add(ts_subtree_total_bytes(result));
        // Do not reuse an EOF node if the included ranges array has changes
        // later on in the file.
        if ts_subtree_is_eof(result) {
            end_byte_offset = 4_294_967_295 as os::raw::c_uint
        }
        if byte_offset > position {
            if (*self_0).lexer.logger.log.is_some() || (*self_0).dot_graph_file.is_valid() {
                snwrite!(
                    (*self_0).lexer.debug_buffer.as_mut_ptr(),
                    1024,
                    "before_reusable_node symbol:{}",
                    CStr::from_ptr(ts_language_symbol_name(
                        (*self_0).language,
                        ts_subtree_symbol(result)
                    ))
                    .to_string_lossy(),
                )
                .unwrap();
                ts_parser__log(self_0);
            }
            break;
        } else if byte_offset < position {
            if (*self_0).lexer.logger.log.is_some() || (*self_0).dot_graph_file.is_valid() {
                snwrite!(
                    (*self_0).lexer.debug_buffer.as_mut_ptr(),
                    1024,
                    "past_reusable_node symbol:{}",
                    CStr::from_ptr(ts_language_symbol_name(
                        (*self_0).language,
                        ts_subtree_symbol(result)
                    ))
                    .to_string_lossy(),
                )
                .unwrap();
                ts_parser__log(self_0);
            }
            if end_byte_offset <= position || !reusable_node_descend(&mut (*self_0).reusable_node) {
                reusable_node_advance(&mut (*self_0).reusable_node);
            }
        } else if !ts_subtree_external_scanner_state_eq(
            (*self_0).reusable_node.last_external_token,
            last_external_token,
        ) {
            if (*self_0).lexer.logger.log.is_some() || (*self_0).dot_graph_file.is_valid() {
                snwrite!(
                    (*self_0).lexer.debug_buffer.as_mut_ptr(),
                    1024,
                    "reusable_node_has_different_external_scanner_state symbol:{}",
                    CStr::from_ptr(ts_language_symbol_name(
                        (*self_0).language,
                        ts_subtree_symbol(result)
                    ))
                    .to_string_lossy(),
                )
                .unwrap();
                ts_parser__log(self_0);
            }
            reusable_node_advance(&mut (*self_0).reusable_node);
        } else {
            let mut reason: *const os::raw::c_char = ptr::null();
            if ts_subtree_has_changes(result) {
                reason = b"has_changes\x00" as *const u8 as *const os::raw::c_char
            } else if ts_subtree_is_error(result) {
                reason = b"is_error\x00" as *const u8 as *const os::raw::c_char
            } else if ts_subtree_missing(result) {
                reason = b"is_missing\x00" as *const u8 as *const os::raw::c_char
            } else if ts_subtree_is_fragile(result) {
                reason = b"is_fragile\x00" as *const u8 as *const os::raw::c_char
            } else if ts_parser__has_included_range_difference(self_0, byte_offset, end_byte_offset)
            {
                reason =
                    b"contains_different_included_range\x00" as *const u8 as *const os::raw::c_char
            }
            if !reason.is_null() {
                if (*self_0).lexer.logger.log.is_some() || (*self_0).dot_graph_file.is_valid() {
                    snwrite!(
                        (*self_0).lexer.debug_buffer.as_mut_ptr(),
                        1024,
                        "cant_reuse_node_{} tree:{}",
                        CStr::from_ptr(reason).to_string_lossy(),
                        CStr::from_ptr(ts_language_symbol_name(
                            (*self_0).language,
                            ts_subtree_symbol(result)
                        ))
                        .to_string_lossy(),
                    )
                    .unwrap();
                    ts_parser__log(self_0);
                }
                if !reusable_node_descend(&mut (*self_0).reusable_node) {
                    reusable_node_advance(&mut (*self_0).reusable_node);
                    ts_parser__breakdown_top_of_stack(self_0, version);
                    *state = ts_stack_state((*self_0).stack, version)
                }
            } else {
                let mut leaf_symbol: TSSymbol = ts_subtree_leaf_symbol(result);
                ts_language_table_entry((*self_0).language, *state, leaf_symbol, table_entry);
                if !ts_parser__can_reuse_first_leaf(self_0, *state, result, table_entry) {
                    if (*self_0).lexer.logger.log.is_some() || (*self_0).dot_graph_file.is_valid() {
                        snwrite!(
                            (*self_0).lexer.debug_buffer.as_mut_ptr(),
                            1024,
                            "cant_reuse_node symbol:{}, first_leaf_symbol:{}",
                            CStr::from_ptr(ts_language_symbol_name(
                                (*self_0).language,
                                ts_subtree_symbol(result)
                            ))
                            .to_string_lossy(),
                            CStr::from_ptr(ts_language_symbol_name(
                                (*self_0).language,
                                leaf_symbol
                            ))
                            .to_string_lossy(),
                        )
                        .unwrap();
                        ts_parser__log(self_0);
                    }
                    reusable_node_advance_past_leaf(&mut (*self_0).reusable_node);
                    break;
                } else {
                    if (*self_0).lexer.logger.log.is_some() || (*self_0).dot_graph_file.is_valid() {
                        snwrite!(
                            (*self_0).lexer.debug_buffer.as_mut_ptr(),
                            1024,
                            "reuse_node symbol:{}",
                            CStr::from_ptr(ts_language_symbol_name(
                                (*self_0).language,
                                ts_subtree_symbol(result)
                            ))
                            .to_string_lossy(),
                        )
                        .unwrap();
                        ts_parser__log(self_0);
                    }
                    ts_subtree_retain(result);
                    return result;
                }
            }
        }
    }
    Subtree {
        ptr: std::ptr::null::<SubtreeHeapData>(),
    }
}
unsafe extern "C" fn ts_parser__select_tree(
    mut self_0: *mut TSParser,
    mut left: Subtree,
    mut right: Subtree,
) -> bool {
    if left.ptr.is_null() {
        return true;
    }
    if right.ptr.is_null() {
        return false;
    }
    if ts_subtree_error_cost(right) < ts_subtree_error_cost(left) {
        if (*self_0).lexer.logger.log.is_some() || (*self_0).dot_graph_file.is_valid() {
            snwrite!(
                (*self_0).lexer.debug_buffer.as_mut_ptr(),
                1024,
                "select_smaller_error symbol:{}, over_symbol:{}",
                CStr::from_ptr(ts_language_symbol_name(
                    (*self_0).language,
                    ts_subtree_symbol(right)
                ))
                .to_string_lossy(),
                CStr::from_ptr(ts_language_symbol_name(
                    (*self_0).language,
                    ts_subtree_symbol(left)
                ))
                .to_string_lossy(),
            )
            .unwrap();
            ts_parser__log(self_0);
        }
        return true;
    }
    if ts_subtree_error_cost(left) < ts_subtree_error_cost(right) {
        if (*self_0).lexer.logger.log.is_some() || (*self_0).dot_graph_file.is_valid() {
            snwrite!(
                (*self_0).lexer.debug_buffer.as_mut_ptr(),
                1024,
                "select_smaller_error symbol:{}, over_symbol:{}",
                CStr::from_ptr(ts_language_symbol_name(
                    (*self_0).language,
                    ts_subtree_symbol(left)
                ))
                .to_string_lossy(),
                CStr::from_ptr(ts_language_symbol_name(
                    (*self_0).language,
                    ts_subtree_symbol(right)
                ))
                .to_string_lossy(),
            )
            .unwrap();
            ts_parser__log(self_0);
        }
        return false;
    }
    if ts_subtree_dynamic_precedence(right) > ts_subtree_dynamic_precedence(left) {
        if (*self_0).lexer.logger.log.is_some() || (*self_0).dot_graph_file.is_valid() {
            snwrite!(
                (*self_0).lexer.debug_buffer.as_mut_ptr(),
                1024,
                "select_higher_precedence symbol:{}, prec:{}, over_symbol:{}, other_prec:{}",
                CStr::from_ptr(ts_language_symbol_name(
                    (*self_0).language,
                    ts_subtree_symbol(right)
                ))
                .to_string_lossy(),
                ts_subtree_dynamic_precedence(right),
                CStr::from_ptr(ts_language_symbol_name(
                    (*self_0).language,
                    ts_subtree_symbol(left)
                ))
                .to_string_lossy(),
                ts_subtree_dynamic_precedence(left),
            )
            .unwrap();
            ts_parser__log(self_0);
        }
        return true;
    }
    if ts_subtree_dynamic_precedence(left) > ts_subtree_dynamic_precedence(right) {
        if (*self_0).lexer.logger.log.is_some() || (*self_0).dot_graph_file.is_valid() {
            snwrite!(
                (*self_0).lexer.debug_buffer.as_mut_ptr(),
                1024,
                "select_higher_precedence symbol:{}, prec:{}, over_symbol:{}, other_prec:{}",
                CStr::from_ptr(ts_language_symbol_name(
                    (*self_0).language,
                    ts_subtree_symbol(left)
                ))
                .to_string_lossy(),
                ts_subtree_dynamic_precedence(left),
                CStr::from_ptr(ts_language_symbol_name(
                    (*self_0).language,
                    ts_subtree_symbol(right)
                ))
                .to_string_lossy(),
                ts_subtree_dynamic_precedence(right),
            )
            .unwrap();
            ts_parser__log(self_0);
        }
        return false;
    }
    if ts_subtree_error_cost(left) > 0 as os::raw::c_int as os::raw::c_uint {
        return true;
    }
    let mut comparison: os::raw::c_int = ts_subtree_compare(left, right);
    match comparison {
        -1 => {
            if (*self_0).lexer.logger.log.is_some() || (*self_0).dot_graph_file.is_valid() {
                snwrite!(
                    (*self_0).lexer.debug_buffer.as_mut_ptr(),
                    1024,
                    "select_earlier symbol:{}, over_symbol:{}",
                    CStr::from_ptr(ts_language_symbol_name(
                        (*self_0).language,
                        ts_subtree_symbol(left)
                    ))
                    .to_string_lossy(),
                    CStr::from_ptr(ts_language_symbol_name(
                        (*self_0).language,
                        ts_subtree_symbol(right)
                    ))
                    .to_string_lossy(),
                )
                .unwrap();
                ts_parser__log(self_0);
            }
            false
        }
        1 => {
            if (*self_0).lexer.logger.log.is_some() || (*self_0).dot_graph_file.is_valid() {
                snwrite!(
                    (*self_0).lexer.debug_buffer.as_mut_ptr(),
                    1024,
                    "select_earlier symbol:{}, over_symbol:{}",
                    CStr::from_ptr(ts_language_symbol_name(
                        (*self_0).language,
                        ts_subtree_symbol(right)
                    ))
                    .to_string_lossy(),
                    CStr::from_ptr(ts_language_symbol_name(
                        (*self_0).language,
                        ts_subtree_symbol(left)
                    ))
                    .to_string_lossy(),
                )
                .unwrap();
                ts_parser__log(self_0);
            }
            true
        }
        _ => {
            if (*self_0).lexer.logger.log.is_some() || (*self_0).dot_graph_file.is_valid() {
                snwrite!(
                    (*self_0).lexer.debug_buffer.as_mut_ptr(),
                    1024,
                    "select_existing symbol:{}, over_symbol:{}",
                    CStr::from_ptr(ts_language_symbol_name(
                        (*self_0).language,
                        ts_subtree_symbol(left)
                    ))
                    .to_string_lossy(),
                    CStr::from_ptr(ts_language_symbol_name(
                        (*self_0).language,
                        ts_subtree_symbol(right)
                    ))
                    .to_string_lossy(),
                )
                .unwrap();
                ts_parser__log(self_0);
            }
            false
        }
    }
}
unsafe extern "C" fn ts_parser__shift(
    mut self_0: *mut TSParser,
    mut version: StackVersion,
    mut state: TSStateId,
    mut lookahead: Subtree,
    mut extra: bool,
) {
    let mut subtree_to_push: Subtree = Subtree {
        data: SubtreeInlineData {
            is_inline_visible_named_extra_has_changes_is_missing_is_keyword: [0; 1],
            symbol: 0,
            padding_bytes: 0,
            size_bytes: 0,
            padding_columns: 0,
            padding_rows_lookahead_bytes: [0; 1],
            parse_state: 0,
        },
    };
    if extra as os::raw::c_int != ts_subtree_extra(lookahead) as os::raw::c_int {
        let mut result: MutableSubtree = ts_subtree_make_mut(&mut (*self_0).tree_pool, lookahead);
        ts_subtree_set_extra(&mut result);
        subtree_to_push = ts_subtree_from_mut(result)
    } else {
        subtree_to_push = lookahead
    }
    let mut is_pending: bool =
        ts_subtree_child_count(subtree_to_push) > 0 as os::raw::c_int as os::raw::c_uint;
    ts_stack_push((*self_0).stack, version, subtree_to_push, is_pending, state);
    if ts_subtree_has_external_tokens(subtree_to_push) {
        ts_stack_set_last_external_token(
            (*self_0).stack,
            version,
            ts_subtree_last_external_token(subtree_to_push),
        );
    };
}
unsafe extern "C" fn ts_parser__replace_children(
    mut self_0: *mut TSParser,
    mut tree: *mut MutableSubtree,
    mut children: *mut SubtreeArray,
) -> bool {
    *(*self_0).scratch_tree.ptr = *(*tree).ptr;
    (*(*self_0).scratch_tree.ptr).child_count = 0 as os::raw::c_int as u32;
    ts_subtree_set_children(
        (*self_0).scratch_tree,
        (*children).contents,
        (*children).size,
        (*self_0).language,
    );
    if ts_parser__select_tree(
        self_0,
        ts_subtree_from_mut(*tree),
        ts_subtree_from_mut((*self_0).scratch_tree),
    ) {
        *(*tree).ptr = *(*self_0).scratch_tree.ptr;
        true
    } else {
        false
    }
}
unsafe extern "C" fn ts_parser__reduce(
    mut self_0: *mut TSParser,
    mut version: StackVersion,
    mut symbol: TSSymbol,
    mut count: u32,
    mut dynamic_precedence: os::raw::c_int,
    mut production_id: u16,
    mut is_fragile: bool,
    mut is_extra: bool,
) -> StackVersion {
    let mut initial_version_count: u32 = ts_stack_version_count((*self_0).stack);
    let mut removed_version_count: u32 = 0 as os::raw::c_int as u32;
    let mut pop: StackSliceArray = ts_stack_pop_count((*self_0).stack, version, count);
    let mut i: u32 = 0 as os::raw::c_int as u32;
    while i < pop.size {
        let mut slice: StackSlice = *pop.contents.offset(i as isize);
        let mut slice_version: StackVersion = slice.version.wrapping_sub(removed_version_count);
        // Error recovery can sometimes cause lots of stack versions to merge,
        // such that a single pop operation can produce a lots of slices.
        // Avoid creating too many stack versions in that situation.
        if i > 0 as os::raw::c_int as os::raw::c_uint
            && slice_version > MAX_VERSION_COUNT.wrapping_add(MAX_VERSION_COUNT_OVERFLOW)
        {
            ts_stack_remove_version((*self_0).stack, slice_version);
            ts_subtree_array_delete(&mut (*self_0).tree_pool, &mut slice.subtrees);
            removed_version_count = removed_version_count.wrapping_add(1);
            while i.wrapping_add(1) < pop.size {
                let mut next_slice: StackSlice = *pop.contents.offset(i.wrapping_add(1) as isize);
                if next_slice.version != slice.version {
                    break;
                }
                ts_subtree_array_delete(&mut (*self_0).tree_pool, &mut next_slice.subtrees);
                i = i.wrapping_add(1)
            }
        } else {
            // Extra tokens on top of the stack should not be included in this new parent
            // node. They will be re-pushed onto the stack after the parent node is
            // created and pushed.
            let mut children: SubtreeArray = slice.subtrees;
            while children.size > 0 as os::raw::c_int as os::raw::c_uint
                && ts_subtree_extra(
                    *children
                        .contents
                        .offset(children.size.wrapping_sub(1) as isize),
                ) as os::raw::c_int
                    != 0
            {
                children.size = children.size.wrapping_sub(1)
            }
            let mut parent: MutableSubtree = ts_subtree_new_node(
                &mut (*self_0).tree_pool,
                symbol,
                &mut children,
                production_id as os::raw::c_uint,
                (*self_0).language,
            );
            // This pop operation may have caused multiple stack versions to collapse
            // into one, because they all diverged from a common state. In that case,
            // choose one of the arrays of trees to be the parent node's children, and
            // delete the rest of the tree arrays.
            while i.wrapping_add(1) < pop.size {
                let mut next_slice_0: StackSlice = *pop.contents.offset(i.wrapping_add(1) as isize);
                if next_slice_0.version != slice.version {
                    break;
                }
                i = i.wrapping_add(1);
                let mut children_0: SubtreeArray = next_slice_0.subtrees;
                while children_0.size > 0 as os::raw::c_int as os::raw::c_uint
                    && ts_subtree_extra(
                        *children_0
                            .contents
                            .offset(children_0.size.wrapping_sub(1) as isize),
                    ) as os::raw::c_int
                        != 0
                {
                    children_0.size = children_0.size.wrapping_sub(1)
                }
                if ts_parser__replace_children(self_0, &mut parent, &mut children_0) {
                    ts_subtree_array_delete(&mut (*self_0).tree_pool, &mut slice.subtrees);
                    slice = next_slice_0
                } else {
                    ts_subtree_array_delete(&mut (*self_0).tree_pool, &mut next_slice_0.subtrees);
                }
            }
            (*parent.ptr)
                .c2rust_unnamed
                .c2rust_unnamed
                .dynamic_precedence += dynamic_precedence;
            (*parent.ptr).c2rust_unnamed.c2rust_unnamed.production_id = production_id;
            let mut state: TSStateId = ts_stack_state((*self_0).stack, slice_version);
            let mut next_state: TSStateId =
                ts_language_next_state((*self_0).language, state, symbol);
            if is_extra {
                (*parent.ptr).set_extra(true)
            }
            if is_fragile as os::raw::c_int != 0
                || pop.size > 1 as os::raw::c_int as os::raw::c_uint
                || initial_version_count > 1 as os::raw::c_int as os::raw::c_uint
            {
                (*parent.ptr).set_fragile_left(true);
                (*parent.ptr).set_fragile_right(true);
                (*parent.ptr).parse_state = TS_TREE_STATE_NONE
            } else {
                (*parent.ptr).parse_state = state
            }
            // Push the parent node onto the stack, along with any extra tokens that
            // were previously on top of the stack.
            ts_stack_push(
                (*self_0).stack,
                slice_version,
                ts_subtree_from_mut(parent),
                false,
                next_state,
            );
            let mut j: u32 = (*parent.ptr).child_count;
            while j < slice.subtrees.size {
                ts_stack_push(
                    (*self_0).stack,
                    slice_version,
                    *slice.subtrees.contents.offset(j as isize),
                    false,
                    next_state,
                );
                j = j.wrapping_add(1)
            }
            let mut j_0: StackVersion = 0 as os::raw::c_int as StackVersion;
            while j_0 < slice_version {
                if j_0 != version && ts_stack_merge((*self_0).stack, j_0, slice_version) {
                    removed_version_count = removed_version_count.wrapping_add(1);
                    break;
                }
                j_0 = j_0.wrapping_add(1)
            }
        }
        i = i.wrapping_add(1)
    }
    // Return the first new stack version that was created.
    if ts_stack_version_count((*self_0).stack) > initial_version_count {
        initial_version_count
    } else {
        -(1 as os::raw::c_int) as StackVersion
    }
}
unsafe extern "C" fn ts_parser__accept(
    mut self_0: *mut TSParser,
    mut version: StackVersion,
    mut lookahead: Subtree,
) {
    assert!(ts_subtree_is_eof(lookahead));
    ts_stack_push(
        (*self_0).stack,
        version,
        lookahead,
        false,
        1 as os::raw::c_int as TSStateId,
    );
    let mut pop: StackSliceArray = ts_stack_pop_all((*self_0).stack, version);
    let mut i: u32 = 0 as os::raw::c_int as u32;
    while i < pop.size {
        let mut trees: SubtreeArray = (*pop.contents.offset(i as isize)).subtrees;
        let mut root: Subtree = Subtree {
            ptr: std::ptr::null::<SubtreeHeapData>(),
        };
        let mut j: u32 = trees.size.wrapping_sub(1);
        while j.wrapping_add(1) > 0 as os::raw::c_int as os::raw::c_uint {
            let mut child: Subtree = *trees.contents.offset(j as isize);
            if !ts_subtree_extra(child) {
                assert!(!child.data.is_inline());
                let mut child_count: u32 = ts_subtree_child_count(child);
                let mut k: u32 = 0 as os::raw::c_int as u32;
                while k < child_count {
                    ts_subtree_retain(
                        *(*child.ptr)
                            .c2rust_unnamed
                            .c2rust_unnamed
                            .children
                            .offset(k as isize),
                    );
                    k = k.wrapping_add(1)
                }
                array__splice(
                    &mut trees as *mut SubtreeArray as *mut VoidArray,
                    ::std::mem::size_of::<Subtree>(),
                    j,
                    1 as os::raw::c_int as u32,
                    child_count,
                    (*child.ptr).c2rust_unnamed.c2rust_unnamed.children as *const ffi::c_void,
                );
                root = ts_subtree_from_mut(ts_subtree_new_node(
                    &mut (*self_0).tree_pool,
                    ts_subtree_symbol(child),
                    &mut trees,
                    (*child.ptr).c2rust_unnamed.c2rust_unnamed.production_id as os::raw::c_uint,
                    (*self_0).language,
                ));
                ts_subtree_release(&mut (*self_0).tree_pool, child);
                break;
            } else {
                j = j.wrapping_sub(1)
            }
        }
        assert!(!root.ptr.is_null());
        (*self_0).accept_count = (*self_0).accept_count.wrapping_add(1);
        if !(*self_0).finished_tree.ptr.is_null() {
            if ts_parser__select_tree(self_0, (*self_0).finished_tree, root) {
                ts_subtree_release(&mut (*self_0).tree_pool, (*self_0).finished_tree);
                (*self_0).finished_tree = root
            } else {
                ts_subtree_release(&mut (*self_0).tree_pool, root);
            }
        } else {
            (*self_0).finished_tree = root
        }
        i = i.wrapping_add(1)
    }
    ts_stack_remove_version(
        (*self_0).stack,
        (*pop.contents.offset(0 as os::raw::c_int as isize)).version,
    );
    ts_stack_halt((*self_0).stack, version);
}
unsafe extern "C" fn ts_parser__do_all_potential_reductions(
    mut self_0: *mut TSParser,
    mut starting_version: StackVersion,
    mut lookahead_symbol: TSSymbol,
) -> bool {
    let mut initial_version_count: u32 = ts_stack_version_count((*self_0).stack);
    let mut can_shift_lookahead_symbol: bool = false;
    let mut version: StackVersion = starting_version;
    let mut current_block_33: u64;
    let mut i: os::raw::c_uint = 0 as os::raw::c_int as os::raw::c_uint;
    loop {
        let mut version_count: u32 = ts_stack_version_count((*self_0).stack);
        if version >= version_count {
            break;
        }
        let mut merged: bool = false;
        let mut i_0: StackVersion = initial_version_count;
        while i_0 < version {
            if ts_stack_merge((*self_0).stack, i_0, version) {
                merged = true;
                break;
            } else {
                i_0 = i_0.wrapping_add(1)
            }
        }
        if !merged {
            let mut state: TSStateId = ts_stack_state((*self_0).stack, version);
            let mut has_shift_action: bool = false;
            (*self_0).reduce_actions.size = 0 as os::raw::c_int as u32;
            let mut first_symbol: TSSymbol = 0;
            let mut end_symbol: TSSymbol = 0;
            if lookahead_symbol as os::raw::c_int != 0 as os::raw::c_int {
                first_symbol = lookahead_symbol;
                end_symbol = (lookahead_symbol as os::raw::c_int + 1 as os::raw::c_int) as TSSymbol
            } else {
                first_symbol = 1 as os::raw::c_int as TSSymbol;
                end_symbol = (*(*self_0).language).token_count as TSSymbol
            }
            let mut symbol: TSSymbol = first_symbol;
            while (symbol as os::raw::c_int) < end_symbol as os::raw::c_int {
                let mut entry: TableEntry = TableEntry {
                    actions: std::ptr::null::<TSParseAction>(),
                    action_count: 0,
                    is_reusable: false,
                };
                ts_language_table_entry((*self_0).language, state, symbol, &mut entry);
                let mut i_1: u32 = 0 as os::raw::c_int as u32;
                while i_1 < entry.action_count {
                    let mut action: TSParseAction = *entry.actions.offset(i_1 as isize);
                    match action.type_0() as os::raw::c_int {
                        0 | 3 => {
                            if !action.params.shift.extra() && !action.params.shift.repetition() {
                                has_shift_action = true
                            }
                        }
                        1 => {
                            if action.params.reduce.child_count as os::raw::c_int
                                > 0 as os::raw::c_int
                            {
                                ts_reduce_action_set_add(
                                    &mut (*self_0).reduce_actions,
                                    ReduceAction {
                                        count: action.params.reduce.child_count as u32,
                                        symbol: action.params.reduce.symbol,
                                        dynamic_precedence: action.params.reduce.dynamic_precedence
                                            as os::raw::c_int,
                                        production_id: action.params.reduce.production_id
                                            as os::raw::c_ushort,
                                    },
                                );
                            }
                        }
                        _ => {}
                    }
                    i_1 = i_1.wrapping_add(1)
                }
                symbol = symbol.wrapping_add(1)
            }
            let mut reduction_version: StackVersion = -(1 as os::raw::c_int) as StackVersion;
            let mut i_2: u32 = 0 as os::raw::c_int as u32;
            while i_2 < (*self_0).reduce_actions.size {
                let mut action_0: ReduceAction =
                    *(*self_0).reduce_actions.contents.offset(i_2 as isize);
                reduction_version = ts_parser__reduce(
                    self_0,
                    version,
                    action_0.symbol,
                    action_0.count,
                    action_0.dynamic_precedence,
                    action_0.production_id,
                    true,
                    false,
                );
                i_2 = i_2.wrapping_add(1)
            }
            if has_shift_action {
                can_shift_lookahead_symbol = true;
                current_block_33 = 13_619_784_596_304_402_172;
            } else if reduction_version != -(1 as os::raw::c_int) as StackVersion
                && i < MAX_VERSION_COUNT
            {
                ts_stack_renumber_version((*self_0).stack, reduction_version, version);
                current_block_33 = 14_916_268_686_031_723_178;
            } else {
                if lookahead_symbol as os::raw::c_int != 0 as os::raw::c_int {
                    ts_stack_remove_version((*self_0).stack, version);
                }
                current_block_33 = 13_619_784_596_304_402_172;
            }
            match current_block_33 {
                14_916_268_686_031_723_178 => {}
                _ => {
                    if version == starting_version {
                        version = version_count
                    } else {
                        version = version.wrapping_add(1)
                    }
                }
            }
        }
        i = i.wrapping_add(1)
    }
    can_shift_lookahead_symbol
}
unsafe extern "C" fn ts_parser__handle_error(
    mut self_0: *mut TSParser,
    mut version: StackVersion,
    mut lookahead_symbol: TSSymbol,
) {
    let mut previous_version_count: u32 = ts_stack_version_count((*self_0).stack);
    // Perform any reductions that can happen in this state, regardless of the lookahead. After
    // skipping one or more invalid tokens, the parser might find a token that would have allowed
    // a reduction to take place.
    ts_parser__do_all_potential_reductions(self_0, version, 0 as os::raw::c_int as TSSymbol);
    let mut version_count: u32 = ts_stack_version_count((*self_0).stack);
    let mut position: Length = ts_stack_position((*self_0).stack, version);
    // Push a discontinuity onto the stack. Merge all of the stack versions that
    // were created in the previous step.
    let mut did_insert_missing_token: bool = false;
    let mut v: StackVersion = version;
    while v < version_count {
        if !did_insert_missing_token {
            let mut state: TSStateId = ts_stack_state((*self_0).stack, v);
            let mut missing_symbol: TSSymbol = 1 as os::raw::c_int as TSSymbol;
            while (missing_symbol as os::raw::c_uint) < (*(*self_0).language).token_count {
                let mut state_after_missing_symbol: TSStateId =
                    ts_language_next_state((*self_0).language, state, missing_symbol);
                if !(state_after_missing_symbol as os::raw::c_int == 0 as os::raw::c_int
                    || state_after_missing_symbol as os::raw::c_int == state as os::raw::c_int)
                    && ts_language_has_reduce_action(
                        (*self_0).language,
                        state_after_missing_symbol,
                        lookahead_symbol,
                    )
                {
                    // In case the parser is currently outside of any included range, the lexer will
                    // snap to the beginning of the next included range. The missing token's padding
                    // must be assigned to position it within the next included range.
                    ts_lexer_reset(&mut (*self_0).lexer, position);
                    ts_lexer_mark_end(&mut (*self_0).lexer);
                    let mut padding: Length =
                        length_sub((*self_0).lexer.token_end_position, position);
                    let mut version_with_missing_tree: StackVersion =
                        ts_stack_copy_version((*self_0).stack, v);
                    let mut missing_tree: Subtree = ts_subtree_new_missing_leaf(
                        &mut (*self_0).tree_pool,
                        missing_symbol,
                        padding,
                        (*self_0).language,
                    );
                    ts_stack_push(
                        (*self_0).stack,
                        version_with_missing_tree,
                        missing_tree,
                        false,
                        state_after_missing_symbol,
                    );
                    if ts_parser__do_all_potential_reductions(
                        self_0,
                        version_with_missing_tree,
                        lookahead_symbol,
                    ) {
                        if (*self_0).lexer.logger.log.is_some()
                            || (*self_0).dot_graph_file.is_valid()
                        {
                            snwrite!(
                                (*self_0).lexer.debug_buffer.as_mut_ptr(),
                                1024,
                                "recover_with_missing symbol:{}, state:{}",
                                CStr::from_ptr(ts_language_symbol_name(
                                    (*self_0).language,
                                    missing_symbol
                                ))
                                .to_string_lossy(),
                                ts_stack_state((*self_0).stack, version_with_missing_tree)
                                    as os::raw::c_int,
                            )
                            .unwrap();
                            ts_parser__log(self_0);
                        }
                        did_insert_missing_token = true;
                        break;
                    }
                }
                missing_symbol = missing_symbol.wrapping_add(1)
            }
        }
        ts_stack_push(
            (*self_0).stack,
            v,
            Subtree {
                ptr: std::ptr::null::<SubtreeHeapData>(),
            },
            false,
            0 as os::raw::c_int as TSStateId,
        );
        v = if v == version {
            previous_version_count
        } else {
            v.wrapping_add(1)
        }
    }
    let mut i: os::raw::c_uint = previous_version_count;
    while i < version_count {
        let mut did_merge: bool = ts_stack_merge((*self_0).stack, version, previous_version_count);
        assert!(did_merge);
        i = i.wrapping_add(1)
    }
    ts_stack_record_summary((*self_0).stack, version, MAX_SUMMARY_DEPTH);
    if (*self_0).dot_graph_file.is_valid() {
        let dot_graph_file = &mut (*self_0).dot_graph_file;
        ts_stack_print_dot_graph((*self_0).stack, (*self_0).language, dot_graph_file);
        write!(dot_graph_file, "\n\n",).unwrap();
    };
}
unsafe extern "C" fn ts_parser__recover_to_state(
    mut self_0: *mut TSParser,
    mut version: StackVersion,
    mut depth: os::raw::c_uint,
    mut goal_state: TSStateId,
) -> bool {
    let mut pop: StackSliceArray = ts_stack_pop_count((*self_0).stack, version, depth);
    let mut previous_version: StackVersion = -(1 as os::raw::c_int) as StackVersion;
    let mut i: os::raw::c_uint = 0 as os::raw::c_int as os::raw::c_uint;
    while i < pop.size {
        let mut slice: StackSlice = *pop.contents.offset(i as isize);
        if slice.version == previous_version {
            ts_subtree_array_delete(&mut (*self_0).tree_pool, &mut slice.subtrees);
            let fresh8 = i;
            i = i.wrapping_sub(1);
            array__erase(
                &mut pop as *mut StackSliceArray as *mut VoidArray,
                ::std::mem::size_of::<StackSlice>(),
                fresh8,
            );
        } else if ts_stack_state((*self_0).stack, slice.version) as os::raw::c_int
            != goal_state as os::raw::c_int
        {
            ts_stack_halt((*self_0).stack, slice.version);
            ts_subtree_array_delete(&mut (*self_0).tree_pool, &mut slice.subtrees);
            let fresh9 = i;
            i = i.wrapping_sub(1);
            array__erase(
                &mut pop as *mut StackSliceArray as *mut VoidArray,
                ::std::mem::size_of::<StackSlice>(),
                fresh9,
            );
        } else {
            let mut error_trees: SubtreeArray = ts_stack_pop_error((*self_0).stack, slice.version);
            if error_trees.size > 0 as os::raw::c_int as os::raw::c_uint {
                assert!(error_trees.size == 1 as os::raw::c_int as os::raw::c_uint);
                let mut error_tree: Subtree =
                    *error_trees.contents.offset(0 as os::raw::c_int as isize);
                let mut error_child_count: u32 = ts_subtree_child_count(error_tree);
                if error_child_count > 0 as os::raw::c_int as os::raw::c_uint {
                    array__splice(
                        &mut slice.subtrees as *mut SubtreeArray as *mut VoidArray,
                        ::std::mem::size_of::<Subtree>(),
                        0 as os::raw::c_int as u32,
                        0 as os::raw::c_int as u32,
                        error_child_count,
                        (*error_tree.ptr).c2rust_unnamed.c2rust_unnamed.children
                            as *const ffi::c_void,
                    );
                    let mut j: os::raw::c_uint = 0 as os::raw::c_int as os::raw::c_uint;
                    while j < error_child_count {
                        ts_subtree_retain(*slice.subtrees.contents.offset(j as isize));
                        j = j.wrapping_add(1)
                    }
                }
                ts_subtree_array_delete(&mut (*self_0).tree_pool, &mut error_trees);
            }
            let mut trailing_extras: SubtreeArray =
                ts_subtree_array_remove_trailing_extras(&mut slice.subtrees);
            if slice.subtrees.size > 0 as os::raw::c_int as os::raw::c_uint {
                let mut error: Subtree = ts_subtree_new_error_node(
                    &mut (*self_0).tree_pool,
                    &mut slice.subtrees,
                    true,
                    (*self_0).language,
                );
                ts_stack_push((*self_0).stack, slice.version, error, false, goal_state);
            } else {
                array__delete(&mut slice.subtrees as *mut SubtreeArray as *mut VoidArray);
            }
            let mut j_0: os::raw::c_uint = 0 as os::raw::c_int as os::raw::c_uint;
            while j_0 < trailing_extras.size {
                let mut tree: Subtree = *trailing_extras.contents.offset(j_0 as isize);
                ts_stack_push((*self_0).stack, slice.version, tree, false, goal_state);
                j_0 = j_0.wrapping_add(1)
            }
            previous_version = slice.version;
            array__delete(&mut trailing_extras as *mut SubtreeArray as *mut VoidArray);
        }
        i = i.wrapping_add(1)
    }
    previous_version != -(1 as os::raw::c_int) as StackVersion
}
unsafe extern "C" fn ts_parser__recover(
    mut self_0: *mut TSParser,
    mut version: StackVersion,
    mut lookahead: Subtree,
) {
    let mut did_recover: bool = false;
    let mut previous_version_count: os::raw::c_uint = ts_stack_version_count((*self_0).stack);
    let mut position: Length = ts_stack_position((*self_0).stack, version);
    let mut summary: *mut StackSummary = ts_stack_get_summary((*self_0).stack, version);
    let mut node_count_since_error: os::raw::c_uint =
        ts_stack_node_count_since_error((*self_0).stack, version);
    let mut current_error_cost: os::raw::c_uint = ts_stack_error_cost((*self_0).stack, version);
    // When the parser is in the error state, there are two strategies for recovering with a
    // given lookahead token:
    // 1. Find a previous state on the stack in which that lookahead token would be valid. Then,
    //    create a new stack version that is in that state again. This entails popping all of the
    //    subtrees that have been pushed onto the stack since that previous state, and wrapping
    //    them in an ERROR node.
    // 2. Wrap the lookahead token in an ERROR node, push that ERROR node onto the stack, and
    //    move on to the next lookahead token, remaining in the error state.
    //
    // First, try the strategy 1. Upon entering the error state, the parser recorded a summary
    // of the previous parse states and their depths. Look at each state in the summary, to see
    // if the current lookahead token would be valid in that state.
    if !summary.is_null() && !ts_subtree_is_error(lookahead) {
        let mut i: os::raw::c_uint = 0 as os::raw::c_int as os::raw::c_uint;
        while i < (*summary).size {
            let mut entry: StackSummaryEntry = *(*summary).contents.offset(i as isize);
            if entry.state as os::raw::c_int != 0 as os::raw::c_int
                && entry.position.bytes != position.bytes
            {
                let mut depth: os::raw::c_uint = entry.depth;
                if node_count_since_error > 0 as os::raw::c_int as os::raw::c_uint {
                    depth = depth.wrapping_add(1)
                }
                // Do not recover in ways that create redundant stack versions.
                let mut would_merge: bool = false;
                let mut j: os::raw::c_uint = 0 as os::raw::c_int as os::raw::c_uint;
                while j < previous_version_count {
                    if ts_stack_state((*self_0).stack, j) as os::raw::c_int
                        == entry.state as os::raw::c_int
                        && ts_stack_position((*self_0).stack, j).bytes == position.bytes
                    {
                        would_merge = true;
                        break;
                    } else {
                        j = j.wrapping_add(1)
                    }
                }
                if !would_merge {
                    // Do not recover if the result would clearly be worse than some existing stack version.
                    let mut new_cost: os::raw::c_uint = current_error_cost
                        .wrapping_add(entry.depth.wrapping_mul(100))
                        .wrapping_add(
                            position
                                .bytes
                                .wrapping_sub(entry.position.bytes)
                                .wrapping_mul(1),
                        )
                        .wrapping_add(
                            position
                                .extent
                                .row
                                .wrapping_sub(entry.position.extent.row)
                                .wrapping_mul(30),
                        );
                    if ts_parser__better_version_exists(self_0, version, false, new_cost) {
                        break;
                    }
                    // If the current lookahead token is valid in some previous state, recover to that state.
                    // Then stop looking for further recoveries.
                    if ts_language_has_actions(
                        (*self_0).language,
                        entry.state,
                        ts_subtree_symbol(lookahead),
                    ) && ts_parser__recover_to_state(self_0, version, depth, entry.state)
                    {
                        did_recover = true;
                        if (*self_0).lexer.logger.log.is_some()
                            || (*self_0).dot_graph_file.is_valid()
                        {
                            snwrite!(
                                (*self_0).lexer.debug_buffer.as_mut_ptr(),
                                1024,
                                "recover_to_previous state:{}, depth:{}",
                                entry.state as os::raw::c_int,
                                depth,
                            )
                            .unwrap();
                            ts_parser__log(self_0);
                        }
                        if (*self_0).dot_graph_file.is_valid() {
                            let dot_graph_file = &mut (*self_0).dot_graph_file;
                            ts_stack_print_dot_graph(
                                (*self_0).stack,
                                (*self_0).language,
                                dot_graph_file,
                            );
                            write!(dot_graph_file, "\n\n").unwrap();
                        }
                        break;
                    }
                }
            }
            i = i.wrapping_add(1)
        }
    }
    // In the process of attemping to recover, some stack versions may have been created
    // and subsequently halted. Remove those versions.
    let mut i_0: os::raw::c_uint = previous_version_count;
    while i_0 < ts_stack_version_count((*self_0).stack) {
        if !ts_stack_is_active((*self_0).stack, i_0) {
            let fresh10 = i_0;
            i_0 = i_0.wrapping_sub(1);
            ts_stack_remove_version((*self_0).stack, fresh10);
        }
        i_0 = i_0.wrapping_add(1)
    }
    // If strategy 1 succeeded, a new stack version will have been created which is able to handle
    // the current lookahead token. Now, in addition, try strategy 2 described above: skip the
    // current lookahead token by wrapping it in an ERROR node.
    // Don't pursue this additional strategy if there are already too many stack versions.
    if did_recover as os::raw::c_int != 0
        && ts_stack_version_count((*self_0).stack) > MAX_VERSION_COUNT
    {
        ts_stack_halt((*self_0).stack, version);
        ts_subtree_release(&mut (*self_0).tree_pool, lookahead);
        return;
    }
    // If the parser is still in the error state at the end of the file, just wrap everything
    // in an ERROR node and terminate.
    if ts_subtree_is_eof(lookahead) {
        if (*self_0).lexer.logger.log.is_some() || (*self_0).dot_graph_file.is_valid() {
            snwrite!(
                (*self_0).lexer.debug_buffer.as_mut_ptr(),
                1024,
                "recover_eof",
            )
            .unwrap();
            ts_parser__log(self_0);
        }
        let mut children = SubtreeArray {
            contents: std::ptr::null_mut::<Subtree>(),
            size: 0 as os::raw::c_int as u32,
            capacity: 0 as os::raw::c_int as u32,
        };
        let mut parent: Subtree = ts_subtree_new_error_node(
            &mut (*self_0).tree_pool,
            &mut children,
            false,
            (*self_0).language,
        );
        ts_stack_push(
            (*self_0).stack,
            version,
            parent,
            false,
            1 as os::raw::c_int as TSStateId,
        );
        ts_parser__accept(self_0, version, lookahead);
        return;
    }
    // Do not recover if the result would clearly be worse than some existing stack version.
    let mut new_cost_0: os::raw::c_uint = current_error_cost
        .wrapping_add(100)
        .wrapping_add(ts_subtree_total_bytes(lookahead).wrapping_mul(1))
        .wrapping_add(ts_subtree_total_size(lookahead).extent.row.wrapping_mul(30));
    if ts_parser__better_version_exists(self_0, version, false, new_cost_0) {
        ts_stack_halt((*self_0).stack, version);
        ts_subtree_release(&mut (*self_0).tree_pool, lookahead);
        return;
    }
    // If the current lookahead token is an extra token, mark it as extra. This means it won't
    // be counted in error cost calculations.
    let mut n: os::raw::c_uint = 0;
    let mut actions: *const TSParseAction = ts_language_actions(
        (*self_0).language,
        1 as os::raw::c_int as TSStateId,
        ts_subtree_symbol(lookahead),
        &mut n,
    );
    if n > 0 as os::raw::c_int as os::raw::c_uint
        && (*actions.offset(n.wrapping_sub(1) as isize)).type_0() as os::raw::c_int
            == TSParseActionTypeShift as os::raw::c_int
        && (*actions.offset(n.wrapping_sub(1) as isize))
            .params
            .shift
            .extra() as os::raw::c_int
            != 0
    {
        let mut mutable_lookahead: MutableSubtree =
            ts_subtree_make_mut(&mut (*self_0).tree_pool, lookahead);
        ts_subtree_set_extra(&mut mutable_lookahead);
        lookahead = ts_subtree_from_mut(mutable_lookahead)
    }
    // Wrap the lookahead token in an ERROR.
    if (*self_0).lexer.logger.log.is_some() || (*self_0).dot_graph_file.is_valid() {
        snwrite!(
            (*self_0).lexer.debug_buffer.as_mut_ptr(),
            1024,
            "skip_token symbol:{}",
            CStr::from_ptr(ts_language_symbol_name(
                (*self_0).language,
                ts_subtree_symbol(lookahead)
            ))
            .to_string_lossy(),
        )
        .unwrap();
        ts_parser__log(self_0);
    }
    let mut children_0 = SubtreeArray {
        contents: std::ptr::null_mut::<Subtree>(),
        size: 0 as os::raw::c_int as u32,
        capacity: 0 as os::raw::c_int as u32,
    };
    array__reserve(
        &mut children_0 as *mut SubtreeArray as *mut VoidArray,
        ::std::mem::size_of::<Subtree>(),
        1 as os::raw::c_int as u32,
    );
    array__grow(
        &mut children_0 as *mut SubtreeArray as *mut VoidArray,
        1 as os::raw::c_int as usize,
        ::std::mem::size_of::<Subtree>(),
    );
    let fresh11 = children_0.size;
    children_0.size = children_0.size.wrapping_add(1);
    *children_0.contents.offset(fresh11 as isize) = lookahead;
    let mut error_repeat: MutableSubtree = ts_subtree_new_node(
        &mut (*self_0).tree_pool,
        (-(1 as os::raw::c_int) as TSSymbol as os::raw::c_int - 1 as os::raw::c_int) as TSSymbol,
        &mut children_0,
        0 as os::raw::c_int as os::raw::c_uint,
        (*self_0).language,
    );
    // If other tokens have already been skipped, so there is already an ERROR at the top of the
    // stack, then pop that ERROR off the stack and wrap the two ERRORs together into one larger
    // ERROR.
    if node_count_since_error > 0 as os::raw::c_int as os::raw::c_uint {
        let mut pop: StackSliceArray =
            ts_stack_pop_count((*self_0).stack, version, 1 as os::raw::c_int as u32);
        // TODO: Figure out how to make this condition occur.
        // See https://github.com/atom/atom/issues/18450#issuecomment-439579778
        // If multiple stack versions have merged at this point, just pick one of the errors
        // arbitrarily and discard the rest.
        if pop.size > 1 as os::raw::c_int as os::raw::c_uint {
            let mut i_1: os::raw::c_uint = 1 as os::raw::c_int as os::raw::c_uint;
            while i_1 < pop.size {
                ts_subtree_array_delete(
                    &mut (*self_0).tree_pool,
                    &mut (*pop.contents.offset(i_1 as isize)).subtrees,
                );
                i_1 = i_1.wrapping_add(1)
            }
            while ts_stack_version_count((*self_0).stack)
                > (*pop.contents.offset(0 as os::raw::c_int as isize))
                    .version
                    .wrapping_add(1)
            {
                ts_stack_remove_version(
                    (*self_0).stack,
                    (*pop.contents.offset(0 as os::raw::c_int as isize))
                        .version
                        .wrapping_add(1),
                );
            }
        }
        ts_stack_renumber_version(
            (*self_0).stack,
            (*pop.contents.offset(0 as os::raw::c_int as isize)).version,
            version,
        );
        array__grow(
            &mut (*pop.contents.offset(0 as os::raw::c_int as isize)).subtrees as *mut SubtreeArray
                as *mut VoidArray,
            1 as os::raw::c_int as usize,
            ::std::mem::size_of::<Subtree>(),
        );
        let fresh12 = &mut (*pop.contents.offset(0 as os::raw::c_int as isize))
            .subtrees
            .size;
        let fresh13 = *fresh12;
        *fresh12 = (*fresh12).wrapping_add(1);
        *(*pop.contents.offset(0 as os::raw::c_int as isize))
            .subtrees
            .contents
            .offset(fresh13 as isize) = ts_subtree_from_mut(error_repeat);
        error_repeat = ts_subtree_new_node(
            &mut (*self_0).tree_pool,
            (-(1 as os::raw::c_int) as TSSymbol as os::raw::c_int - 1 as os::raw::c_int)
                as TSSymbol,
            &mut (*pop.contents.offset(0 as os::raw::c_int as isize)).subtrees,
            0 as os::raw::c_int as os::raw::c_uint,
            (*self_0).language,
        )
    }
    // Push the new ERROR onto the stack.
    ts_stack_push(
        (*self_0).stack,
        version,
        ts_subtree_from_mut(error_repeat),
        false,
        0 as os::raw::c_int as TSStateId,
    );
    if ts_subtree_has_external_tokens(lookahead) {
        ts_stack_set_last_external_token(
            (*self_0).stack,
            version,
            ts_subtree_last_external_token(lookahead),
        );
    };
}

unsafe extern "C" fn ts_parser__advance(
    mut self_0: *mut TSParser,
    mut version: StackVersion,
    mut allow_node_reuse: bool,
) -> bool {
    let mut last_reduction_version: StackVersion = 0;
    let mut state: TSStateId = ts_stack_state((*self_0).stack, version);
    let mut position: u32 = ts_stack_position((*self_0).stack, version).bytes;
    let mut last_external_token: Subtree = ts_stack_last_external_token((*self_0).stack, version);
    let mut did_reuse: bool = 1 as os::raw::c_int != 0;
    let mut lookahead: Subtree = Subtree {
        ptr: 0 as *const SubtreeHeapData,
    };
    let mut table_entry: TableEntry = {
        let mut init = TableEntry {
            actions: 0 as *const TSParseAction,
            action_count: 0 as os::raw::c_int as u32,
            is_reusable: false,
        };
        init
    };
    // If possible, reuse a node from the previous syntax tree.
    if allow_node_reuse {
        lookahead = ts_parser__reuse_node(
            self_0,
            version,
            &mut state,
            position,
            last_external_token,
            &mut table_entry,
        )
    }
    // If no node from the previous syntax tree could be reused, then try to
    // reuse the token previously returned by the lexer.
    if lookahead.ptr.is_null() {
        did_reuse = 0 as os::raw::c_int != 0;
        lookahead = ts_parser__get_cached_token(
            self_0,
            state,
            position as usize,
            last_external_token,
            &mut table_entry,
        )
    }
    loop {
        // Otherwise, re-run the lexer.
        if lookahead.ptr.is_null() {
            lookahead = ts_parser__lex(self_0, version, state);
            if !lookahead.ptr.is_null() {
                ts_parser__set_cached_token(
                    self_0,
                    position as usize,
                    last_external_token,
                    lookahead,
                );
                ts_language_table_entry(
                    (*self_0).language,
                    state,
                    ts_subtree_symbol(lookahead),
                    &mut table_entry,
                );
            } else {
                // When parsing a non-terminal extra, a null lookahead indicates the
                // end of the rule. The reduction is stored in the EOF table entry.
                // After the reduction, the lexer needs to be run again.
                ts_language_table_entry(
                    (*self_0).language,
                    state,
                    0 as os::raw::c_int as TSSymbol,
                    &mut table_entry,
                );
            }
        }
        loop {
            // If a cancellation flag or a timeout was provided, then check every
            // time a fixed number of parse actions has been processed.
            (*self_0).operation_count = (*self_0).operation_count.wrapping_add(1);
            if (*self_0).operation_count == OP_COUNT_PER_TIMEOUT_CHECK {
                (*self_0).operation_count = 0 as os::raw::c_int as os::raw::c_uint
            }
            if (*self_0).operation_count == 0 as os::raw::c_int as os::raw::c_uint
                && (!(*self_0).cancellation_flag.is_null()
                    && atomic_load((*self_0).cancellation_flag) != 0
                    || (*self_0).end_instant.is_some()
                        && Instant::now() > (*self_0).end_instant.unwrap())
            {
                ts_subtree_release(&mut (*self_0).tree_pool, lookahead);
                return 0 as os::raw::c_int != 0;
            }
            // Process each parse action for the current lookahead token in
            // the current state. If there are multiple actions, then this is
            // an ambiguous state. REDUCE actions always create a new stack
            // version, whereas SHIFT actions update the existing stack version
            // and terminate this loop.
            last_reduction_version = -(1 as os::raw::c_int) as StackVersion;
            let mut current_block_67: u64;
            let mut i: u32 = 0;
            while i < table_entry.action_count {
                let mut action: TSParseAction = *table_entry.actions.offset(i as isize);
                match action.type_0() as os::raw::c_int {
                    0 => {
                        if !action.params.shift.repetition() {
                            let mut next_state: TSStateId = 0;
                            if action.params.shift.extra() {
                                // TODO: remove when TREE_SITTER_LANGUAGE_VERSION 9 is out.
                                if state as os::raw::c_int == 0 as os::raw::c_int {
                                    current_block_67 = 14763689060501151050;
                                } else {
                                    next_state = state;
                                    if (*self_0).lexer.logger.log.is_some()
                                        || (*self_0).dot_graph_file.is_valid()
                                    {
                                        snwrite!(
                                            (*self_0).lexer.debug_buffer.as_mut_ptr(),
                                            1024,
                                            "shift_extra",
                                        )
                                        .unwrap();
                                        ts_parser__log(self_0);
                                    }
                                    current_block_67 = 12381812505308290051;
                                }
                            } else {
                                next_state = action.params.shift.state;
                                if (*self_0).lexer.logger.log.is_some()
                                    || (*self_0).dot_graph_file.is_valid()
                                {
                                    snwrite!(
                                        (*self_0).lexer.debug_buffer.as_mut_ptr(),
                                        1024,
                                        "shift state: {}",
                                        next_state as os::raw::c_int,
                                    )
                                    .unwrap();
                                    ts_parser__log(self_0);
                                }
                                current_block_67 = 12381812505308290051;
                            }
                            match current_block_67 {
                                14763689060501151050 => {}
                                _ => {
                                    if ts_subtree_child_count(lookahead)
                                        > 0 as os::raw::c_int as os::raw::c_uint
                                    {
                                        ts_parser__breakdown_lookahead(
                                            self_0,
                                            &mut lookahead,
                                            state,
                                            &mut (*self_0).reusable_node,
                                        );
                                        next_state = ts_language_next_state(
                                            (*self_0).language,
                                            state,
                                            ts_subtree_symbol(lookahead),
                                        )
                                    }
                                    ts_parser__shift(
                                        self_0,
                                        version,
                                        next_state,
                                        lookahead,
                                        action.params.shift.extra(),
                                    );
                                    if did_reuse {
                                        reusable_node_advance(&mut (*self_0).reusable_node);
                                    }
                                    return 1 as os::raw::c_int != 0;
                                }
                            }
                        }
                    }
                    1 => {
                        let mut is_fragile: bool =
                            table_entry.action_count > 1 as os::raw::c_int as os::raw::c_uint;
                        let mut is_extra: bool = lookahead.ptr.is_null();
                        if (*self_0).lexer.logger.log.is_some()
                            || (*self_0).dot_graph_file.is_valid()
                        {
                            snwrite!(
                                (*self_0).lexer.debug_buffer.as_mut_ptr(),
                                1024,
                                "reduce sym: {}, child_count: {}",
                                CStr::from_ptr(ts_language_symbol_name(
                                    (*self_0).language,
                                    action.params.reduce.symbol,
                                ))
                                .to_string_lossy(),
                                action.params.reduce.child_count as os::raw::c_int,
                            )
                            .unwrap();
                            ts_parser__log(self_0);
                        }
                        let mut reduction_version: StackVersion = ts_parser__reduce(
                            self_0,
                            version,
                            action.params.reduce.symbol,
                            action.params.reduce.child_count as u32,
                            action.params.reduce.dynamic_precedence as os::raw::c_int,
                            action.params.reduce.production_id as u16,
                            is_fragile,
                            is_extra,
                        );
                        if reduction_version != -(1 as os::raw::c_int) as StackVersion {
                            last_reduction_version = reduction_version
                        }
                    }
                    2 => {
                        if (*self_0).lexer.logger.log.is_some()
                            || (*self_0).dot_graph_file.is_valid()
                        {
                            snwrite!((*self_0).lexer.debug_buffer.as_mut_ptr(), 1024, "accept",)
                                .unwrap();
                            ts_parser__log(self_0);
                        }
                        ts_parser__accept(self_0, version, lookahead);
                        return 1 as os::raw::c_int != 0;
                    }
                    3 => {
                        if ts_subtree_child_count(lookahead)
                            > 0 as os::raw::c_int as os::raw::c_uint
                        {
                            ts_parser__breakdown_lookahead(
                                self_0,
                                &mut lookahead,
                                0 as os::raw::c_int as TSStateId,
                                &mut (*self_0).reusable_node,
                            );
                        }
                        ts_parser__recover(self_0, version, lookahead);
                        if did_reuse {
                            reusable_node_advance(&mut (*self_0).reusable_node);
                        }
                        return 1 as os::raw::c_int != 0;
                    }
                    _ => {}
                }
                i = i.wrapping_add(1)
            }
            // If a reduction was performed, then replace the current stack version
            // with one of the stack versions created by a reduction, and continue
            // processing this version of the stack with the same lookahead symbol.
            if last_reduction_version != -(1 as os::raw::c_int) as StackVersion {
                ts_stack_renumber_version((*self_0).stack, last_reduction_version, version);
                if (*self_0).dot_graph_file.is_valid() {
                    let dot_graph_file = &mut (*self_0).dot_graph_file;
                    ts_stack_print_dot_graph((*self_0).stack, (*self_0).language, dot_graph_file);
                    write!(dot_graph_file, "\n\n").unwrap();
                }
                state = ts_stack_state((*self_0).stack, version);
                // At the end of a non-terminal extra rule, the lexer will return a
                // null subtree, because the parser needs to perform a fixed reduction
                // regardless of the lookahead node. After performing that reduction,
                // (and completing the non-terminal extra rule) run the lexer again based
                // on the current parse state.
                if lookahead.ptr.is_null() {
                    lookahead = ts_parser__lex(self_0, version, state)
                }
                ts_language_table_entry(
                    (*self_0).language,
                    state,
                    ts_subtree_leaf_symbol(lookahead),
                    &mut table_entry,
                );
            } else {
                // If there were no parse actions for the current lookahead token, then
                // it is not valid in this state. If the current lookahead token is a
                // keyword, then switch to treating it as the normal word token if that
                // token is valid in this state.
                if !(ts_subtree_is_keyword(lookahead) as os::raw::c_int != 0
                    && ts_subtree_symbol(lookahead) as os::raw::c_int
                        != (*(*self_0).language).keyword_capture_token as os::raw::c_int)
                {
                    break;
                }
                ts_language_table_entry(
                    (*self_0).language,
                    state,
                    (*(*self_0).language).keyword_capture_token,
                    &mut table_entry,
                );
                if !(table_entry.action_count > 0 as os::raw::c_int as os::raw::c_uint) {
                    break;
                }
                if (*self_0).lexer.logger.log.is_some() || (*self_0).dot_graph_file.is_valid() {
                    snwrite!(
                        (*self_0).lexer.debug_buffer.as_mut_ptr(),
                        1024,
                        "switch from_keyword: {}, to_word_token: {}",
                        CStr::from_ptr(ts_language_symbol_name(
                            (*self_0).language,
                            ts_subtree_symbol(lookahead),
                        ))
                        .to_string_lossy(),
                        CStr::from_ptr(ts_language_symbol_name(
                            (*self_0).language,
                            (*(*self_0).language).keyword_capture_token,
                        ))
                        .to_string_lossy(),
                    )
                    .unwrap();
                    ts_parser__log(self_0);
                }
                let mut mutable_lookahead: MutableSubtree =
                    ts_subtree_make_mut(&mut (*self_0).tree_pool, lookahead);
                ts_subtree_set_symbol(
                    &mut mutable_lookahead,
                    (*(*self_0).language).keyword_capture_token,
                    (*self_0).language,
                );
                lookahead = ts_subtree_from_mut(mutable_lookahead)
            }
        }
        // If the current lookahead token is not valid and the parser is
        // already in the error state, restart the error recovery process.
        // TODO - can this be unified with the other `RECOVER` case above?
        if state as os::raw::c_int == 0 as os::raw::c_int {
            ts_parser__recover(self_0, version, lookahead);
            return 1 as os::raw::c_int != 0;
        }
        // If the current lookahead token is not valid and the previous
        // subtree on the stack was reused from an old tree, it isn't actually
        // valid to reuse it. Remove it from the stack, and in its place,
        // push each of its children. Then try again to process the current
        // lookahead.
        if !ts_parser__breakdown_top_of_stack(self_0, version) {
            break;
        }
        state = ts_stack_state((*self_0).stack, version);
        ts_subtree_release(&mut (*self_0).tree_pool, lookahead);
        lookahead = Subtree {
            ptr: 0 as *const SubtreeHeapData,
        }
    }
    // At this point, the current lookahead token is definitely not valid
    // for this parse stack version. Mark this version as paused and continue
    // processing any other stack versions that might exist. If some other
    // version advances successfully, then this version can simply be removed.
    // But if all versions end up paused, then error recovery is needed.
    if (*self_0).lexer.logger.log.is_some() || (*self_0).dot_graph_file.is_valid() {
        snwrite!(
            (*self_0).lexer.debug_buffer.as_mut_ptr(),
            1024,
            "detect_error",
        )
        .unwrap();
        ts_parser__log(self_0);
    }
    ts_stack_pause((*self_0).stack, version, ts_subtree_leaf_symbol(lookahead));
    ts_subtree_release(&mut (*self_0).tree_pool, lookahead);
    return 1 as os::raw::c_int != 0;
}

unsafe extern "C" fn ts_parser__condense_stack(mut self_0: *mut TSParser) -> os::raw::c_uint {
    let mut made_changes: bool = false;
    let mut min_error_cost: os::raw::c_uint = (2_147_483_647 as os::raw::c_int as os::raw::c_uint)
        .wrapping_mul(2)
        .wrapping_add(1);
    let mut i: StackVersion = 0 as os::raw::c_int as StackVersion;
    while i < ts_stack_version_count((*self_0).stack) {
        // Prune any versions that have been marked for removal.
        if ts_stack_is_halted((*self_0).stack, i) {
            ts_stack_remove_version((*self_0).stack, i);
            i = i.wrapping_sub(1)
        } else {
            // Keep track of the minimum error cost of any stack version so
            // that it can be returned.
            let mut status_i: ErrorStatus = ts_parser__version_status(self_0, i);
            if !status_i.is_in_error && status_i.cost < min_error_cost {
                min_error_cost = status_i.cost
            }
            // Examine each pair of stack versions, removing any versions that
            // are clearly worse than another version. Ensure that the versions
            // are ordered from most promising to least promising.
            let mut j: StackVersion = 0 as os::raw::c_int as StackVersion;
            while j < i {
                let mut status_j: ErrorStatus = ts_parser__version_status(self_0, j);
                match ts_parser__compare_versions(self_0, status_j, status_i) as os::raw::c_uint {
                    0 => {
                        made_changes = true;
                        ts_stack_remove_version((*self_0).stack, i);
                        i = i.wrapping_sub(1);
                        j = i
                    }
                    1 | 2 => {
                        if ts_stack_merge((*self_0).stack, j, i) {
                            made_changes = true;
                            i = i.wrapping_sub(1);
                            j = i
                        }
                    }
                    3 => {
                        made_changes = true;
                        if ts_stack_merge((*self_0).stack, j, i) {
                            i = i.wrapping_sub(1);
                            j = i
                        } else {
                            ts_stack_swap_versions((*self_0).stack, i, j);
                        }
                    }
                    4 => {
                        made_changes = true;
                        ts_stack_remove_version((*self_0).stack, j);
                        i = i.wrapping_sub(1);
                        j = j.wrapping_sub(1)
                    }
                    _ => {}
                }
                j = j.wrapping_add(1)
            }
        }
        i = i.wrapping_add(1)
    }
    // Enfore a hard upper bound on the number of stack versions by
    // discarding the least promising versions.
    while ts_stack_version_count((*self_0).stack) > MAX_VERSION_COUNT {
        ts_stack_remove_version((*self_0).stack, MAX_VERSION_COUNT);
        made_changes = true
    }
    // If the best-performing stack version is currently paused, or all
    // versions are paused, then resume the best paused version and begin
    // the error recovery process. Otherwise, remove the paused versions.
    if ts_stack_version_count((*self_0).stack) > 0 as os::raw::c_int as os::raw::c_uint {
        let mut has_unpaused_version: bool = false;
        let mut i_0: StackVersion = 0 as os::raw::c_int as StackVersion;
        let mut n: StackVersion = ts_stack_version_count((*self_0).stack);
        while i_0 < n {
            if ts_stack_is_paused((*self_0).stack, i_0) {
                if !has_unpaused_version && (*self_0).accept_count < MAX_VERSION_COUNT {
                    if (*self_0).lexer.logger.log.is_some() || (*self_0).dot_graph_file.is_valid() {
                        snwrite!(
                            (*self_0).lexer.debug_buffer.as_mut_ptr(),
                            1024,
                            "resume version:{}",
                            i_0,
                        )
                        .unwrap();
                        ts_parser__log(self_0);
                    }
                    min_error_cost = ts_stack_error_cost((*self_0).stack, i_0);
                    let mut lookahead_symbol: TSSymbol = ts_stack_resume((*self_0).stack, i_0);
                    ts_parser__handle_error(self_0, i_0, lookahead_symbol);
                    has_unpaused_version = true
                } else {
                    ts_stack_remove_version((*self_0).stack, i_0);
                    i_0 = i_0.wrapping_sub(1);
                    n = n.wrapping_sub(1)
                }
            } else {
                has_unpaused_version = true
            }
            i_0 = i_0.wrapping_add(1)
        }
    }
    if made_changes {
        if (*self_0).lexer.logger.log.is_some() || (*self_0).dot_graph_file.is_valid() {
            snwrite!((*self_0).lexer.debug_buffer.as_mut_ptr(), 1024, "condense",).unwrap();
            ts_parser__log(self_0);
        }
        if (*self_0).dot_graph_file.is_valid() {
            let dot_graph_file = &mut (*self_0).dot_graph_file;
            ts_stack_print_dot_graph((*self_0).stack, (*self_0).language, dot_graph_file);
            write!(dot_graph_file, "\n\n").unwrap();
        }
    }
    min_error_cost
}
unsafe extern "C" fn ts_parser_has_outstanding_parse(mut self_0: *mut TSParser) -> bool {
    ts_stack_state((*self_0).stack, 0 as os::raw::c_int as StackVersion) as os::raw::c_int
        != 1 as os::raw::c_int
        || ts_stack_node_count_since_error((*self_0).stack, 0 as os::raw::c_int as StackVersion)
            != 0 as os::raw::c_int as os::raw::c_uint
}

/// Create a new parser.
#[no_mangle]
pub unsafe extern "C" fn ts_parser_new() -> *mut TSParser {
    let mut self_0: *mut TSParser = ts_calloc(
        1 as os::raw::c_int as usize,
        ::std::mem::size_of::<TSParser>(),
    ) as *mut TSParser;
    ts_lexer_init(&mut (*self_0).lexer);
    (*self_0).reduce_actions.size = 0 as os::raw::c_int as u32;
    (*self_0).reduce_actions.capacity = 0 as os::raw::c_int as u32;
    (*self_0).reduce_actions.contents = ptr::null_mut();
    array__reserve(
        &mut (*self_0).reduce_actions as *mut ReduceActionSet as *mut VoidArray,
        ::std::mem::size_of::<ReduceAction>(),
        4 as os::raw::c_int as u32,
    );
    (*self_0).tree_pool = ts_subtree_pool_new(32 as os::raw::c_int as u32);
    (*self_0).stack = ts_stack_new(&mut (*self_0).tree_pool);
    (*self_0).finished_tree = Subtree {
        ptr: std::ptr::null::<SubtreeHeapData>(),
    };
    (*self_0).reusable_node = reusable_node_new();
    (*self_0).dot_graph_file = util::File::empty();
    (*self_0).cancellation_flag = ptr::null();
    (*self_0).timeout_duration = Default::default();
    (*self_0).end_instant = None;
    (*self_0).operation_count = 0 as os::raw::c_int as os::raw::c_uint;
    (*self_0).old_tree = Subtree {
        ptr: std::ptr::null::<SubtreeHeapData>(),
    };
    (*self_0).scratch_tree.ptr = &mut (*self_0).scratch_tree_data;
    (*self_0).included_range_differences = TSRangeArray {
        contents: std::ptr::null_mut::<TSRange>(),
        size: 0 as os::raw::c_int as u32,
        capacity: 0 as os::raw::c_int as u32,
    };
    (*self_0).included_range_difference_index = 0 as os::raw::c_int as os::raw::c_uint;
    ts_parser__set_cached_token(
        self_0,
        0 as os::raw::c_int as usize,
        Subtree {
            ptr: std::ptr::null::<SubtreeHeapData>(),
        },
        Subtree {
            ptr: std::ptr::null::<SubtreeHeapData>(),
        },
    );
    self_0
}

/// Delete the parser, freeing all of the memory that it used.
#[no_mangle]
pub unsafe extern "C" fn ts_parser_delete(mut self_0: *mut TSParser) {
    if self_0.is_null() {
        return;
    }
    ts_parser_set_language(self_0, std::ptr::null::<TSLanguage>());
    ts_stack_delete((*self_0).stack);
    if !(*self_0).reduce_actions.contents.is_null() {
        array__delete(&mut (*self_0).reduce_actions as *mut ReduceActionSet as *mut VoidArray);
    }
    if !(*self_0).included_range_differences.contents.is_null() {
        array__delete(
            &mut (*self_0).included_range_differences as *mut TSRangeArray as *mut VoidArray,
        );
    }
    if !(*self_0).old_tree.ptr.is_null() {
        ts_subtree_release(&mut (*self_0).tree_pool, (*self_0).old_tree);
        (*self_0).old_tree = Subtree {
            ptr: std::ptr::null::<SubtreeHeapData>(),
        }
    }
    ts_lexer_delete(&mut (*self_0).lexer);
    ts_parser__set_cached_token(
        self_0,
        0 as os::raw::c_int as usize,
        Subtree {
            ptr: std::ptr::null::<SubtreeHeapData>(),
        },
        Subtree {
            ptr: std::ptr::null::<SubtreeHeapData>(),
        },
    );
    ts_subtree_pool_delete(&mut (*self_0).tree_pool);
    reusable_node_delete(&mut (*self_0).reusable_node);
    ts_free(self_0 as *mut ffi::c_void);
}

/// Get the parser's current language.
#[no_mangle]
pub unsafe extern "C" fn ts_parser_language(mut self_0: *const TSParser) -> *const TSLanguage {
    (*self_0).language
}

/// Set the language that the parser should use for parsing.
///
/// Returns a boolean indicating whether or not the language was successfully
/// assigned. True means assignment succeeded. False means there was a version
/// mismatch: the language was generated with an incompatible version of the
/// Tree-sitter CLI. Check the language's version using `ts_language_version`
/// and compare it to this library's `TREE_SITTER_LANGUAGE_VERSION` and
/// `TREE_SITTER_MIN_COMPATIBLE_LANGUAGE_VERSION` constants.
#[no_mangle]
pub unsafe extern "C" fn ts_parser_set_language(
    mut self_0: *mut TSParser,
    mut language: *const TSLanguage,
) -> bool {
    if !language.is_null() {
        if (*language).version > 11 as os::raw::c_int as os::raw::c_uint {
            return false;
        }
        if (*language).version < 9 as os::raw::c_int as os::raw::c_uint {
            return false;
        }
    }
    if !(*self_0).external_scanner_payload.is_null()
        && (*(*self_0).language).external_scanner.destroy.is_some()
    {
        (*(*self_0).language)
            .external_scanner
            .destroy
            .expect("non-null function pointer")((*self_0).external_scanner_payload);
    }
    if !language.is_null() && (*language).external_scanner.create.is_some() {
        (*self_0).external_scanner_payload = (*language)
            .external_scanner
            .create
            .expect("non-null function pointer")()
    } else {
        (*self_0).external_scanner_payload = ptr::null_mut()
    }
    (*self_0).language = language;
    ts_parser_reset(self_0);
    true
}

/// Get the parser's current logger.
#[no_mangle]
pub unsafe extern "C" fn ts_parser_logger(mut self_0: *const TSParser) -> TSLogger {
    (*self_0).lexer.logger
}

/// Set the logger that a parser should use during parsing.
///
/// The parser does not take ownership over the logger payload. If a logger was
/// previously assigned, the caller is responsible for releasing any memory
/// owned by the previous logger.
#[no_mangle]
pub unsafe extern "C" fn ts_parser_set_logger(mut self_0: *mut TSParser, mut logger: TSLogger) {
    (*self_0).lexer.logger = logger;
}

/// Set the file descriptor to which the parser should write debugging graphs
/// during parsing. The graphs are formatted in the DOT language. You may want
/// to pipe these graphs directly to a `dot(1)` process in order to generate
/// SVG output. You can turn off this logging by passing a negative number.
#[no_mangle]
pub unsafe extern "C" fn ts_parser_print_dot_graphs(
    mut self_0: *mut TSParser,
    mut fd: os::raw::c_int,
) {
    if (*self_0).dot_graph_file.is_valid() {
        (*self_0).dot_graph_file.close();
    }
    if fd >= 0 as os::raw::c_int {
        #[cfg(feature = "capi")]
        {
            (*self_0).dot_graph_file =
                os::raw::fdopen(fd, b"a\0" as *const u8 as *const os::raw::c_char).into();
        }

        #[cfg(all(not(feature = "capi"), not(windows)))]
        {
            (*self_0).dot_graph_file = BufWriter::new(fs::File::from_raw_fd(fd)).into();
        }

        #[cfg(all(not(feature = "capi"), windows))]
        {
            panic!("raw file descriptor on windows are not supported");
        }
    } else {
        (*self_0).dot_graph_file = util::File::empty();
    };
}

/// Get the parser's current cancellation flag pointer.
#[no_mangle]
pub unsafe extern "C" fn ts_parser_cancellation_flag(mut self_0: *const TSParser) -> *const usize {
    (*self_0).cancellation_flag as *const usize
}

/// Set the parser's current cancellation flag pointer.
///
/// If a non-null pointer is assigned, then the parser will periodically read
/// from this pointer during parsing. If it reads a non-zero value, it will
/// halt early, returning NULL. See `ts_parser_parse` for more information.
#[no_mangle]
pub unsafe extern "C" fn ts_parser_set_cancellation_flag(
    mut self_0: *mut TSParser,
    mut flag: *const usize,
) {
    (*self_0).cancellation_flag = flag as *const usize;
}

/// Get the duration in microseconds that parsing is allowed to take.
#[no_mangle]
pub unsafe extern "C" fn ts_parser_timeout_micros(mut self_0: *const TSParser) -> u64 {
    (*self_0).timeout_duration.as_micros() as u64
}

/// Set the maximum duration in microseconds that parsing should be allowed to
/// take before halting.
///
/// If parsing takes longer than this, it will halt early, returning NULL.
/// See `ts_parser_parse` for more information.
#[no_mangle]
pub unsafe extern "C" fn ts_parser_set_timeout_micros(
    mut self_0: *mut TSParser,
    mut timeout_micros: u64,
) {
    (*self_0).timeout_duration = Duration::from_micros(timeout_micros);
}

/// Set the ranges of text that the parser should include when parsing.
///
/// By default, the parser will always include entire documents. This function
/// allows you to parse only a *portion* of a document but still return a syntax
/// tree whose ranges match up with the document as a whole. You can also pass
/// multiple disjoint ranges.
///
/// The second and third parameters specify the location and length of an array
/// of ranges. The parser does *not* take ownership of these ranges; it copies
/// the data, so it doesn't matter how these ranges are allocated.
///
/// If `length` is zero, then the entire document will be parsed. Otherwise,
/// the given ranges must be ordered from earliest to latest in the document,
/// and they must not overlap. That is, the following must hold for all
/// `i` < `length - 1`:
///
///   ranges[i].end_byte <= ranges[i + 1].start_byte
///
/// If this requirement is not satisfied, the operation will fail, the ranges
/// will not be assigned, and this function will return `false`. On success,
/// this function returns `true`
#[no_mangle]
pub unsafe extern "C" fn ts_parser_set_included_ranges(
    mut self_0: *mut TSParser,
    mut ranges: *const TSRange,
    mut count: u32,
) -> bool {
    ts_lexer_set_included_ranges(&mut (*self_0).lexer, ranges, count)
}

/// Get the ranges of text that the parser will include when parsing.
///
/// The returned pointer is owned by the parser. The caller should not free it
/// or write to it. The length of the array will be written to the given
/// `length` pointer.
#[no_mangle]
pub(crate) unsafe extern "C" fn ts_parser_included_ranges(
    mut self_0: *const TSParser,
    mut count: *mut u32,
) -> *const TSRange {
    ts_lexer_included_ranges(&(*self_0).lexer, count)
}

/// Instruct the parser to start the next parse from the beginning.
///
/// If the parser previously failed because of a timeout or a cancellation, then
/// by default, it will resume where it left off on the next call to
/// `ts_parser_parse` or other parsing functions. If you don't want to resume,
/// and instead intend to use this parser to parse some other document, you must
/// call `ts_parser_reset` first.
#[no_mangle]
pub unsafe extern "C" fn ts_parser_reset(mut self_0: *mut TSParser) {
    if !(*self_0).language.is_null() && (*(*self_0).language).external_scanner.deserialize.is_some()
    {
        (*(*self_0).language)
            .external_scanner
            .deserialize
            .expect("non-null function pointer")(
            (*self_0).external_scanner_payload,
            ptr::null(),
            0 as os::raw::c_int as os::raw::c_uint,
        );
    }
    if !(*self_0).old_tree.ptr.is_null() {
        ts_subtree_release(&mut (*self_0).tree_pool, (*self_0).old_tree);
        (*self_0).old_tree = Subtree {
            ptr: std::ptr::null::<SubtreeHeapData>(),
        }
    }
    reusable_node_clear(&mut (*self_0).reusable_node);
    ts_lexer_reset(&mut (*self_0).lexer, length_zero());
    ts_stack_clear((*self_0).stack);
    ts_parser__set_cached_token(
        self_0,
        0 as os::raw::c_int as usize,
        Subtree {
            ptr: std::ptr::null::<SubtreeHeapData>(),
        },
        Subtree {
            ptr: std::ptr::null::<SubtreeHeapData>(),
        },
    );
    if !(*self_0).finished_tree.ptr.is_null() {
        ts_subtree_release(&mut (*self_0).tree_pool, (*self_0).finished_tree);
        (*self_0).finished_tree = Subtree {
            ptr: std::ptr::null::<SubtreeHeapData>(),
        }
    }
    (*self_0).accept_count = 0 as os::raw::c_int as os::raw::c_uint;
}

/// Use the parser to parse some source code and create a syntax tree.
///
/// If you are parsing this document for the first time, pass `NULL` for the
/// `old_tree` parameter. Otherwise, if you have already parsed an earlier
/// version of this document and the document has since been edited, pass the
/// previous syntax tree so that the unchanged parts of it can be reused.
/// This will save time and memory. For this to work correctly, you must have
/// already edited the old syntax tree using the `ts_tree_edit` function in a
/// way that exactly matches the source code changes.
///
/// The `TSInput` parameter lets you specify how to read the text. It has the
/// following three fields:
/// 1. `read`: A function to retrieve a chunk of text at a given byte offset
///    and (row, column) position. The function should return a pointer to the
///    text and write its length to the the `bytes_read` pointer. The parser
///    does not take ownership of this buffer; it just borrows it until it has
///    finished reading it. The function should write a zero value to the
///    `bytes_read` pointer to indicate the end of the document.
/// 2. `payload`: An arbitrary pointer that will be passed to each invocation
///    of the `read` function.
/// 3. `encoding`: An indication of how the text is encoded. Either
///    `TSInputEncodingUTF8` or `TSInputEncodingUTF16`.
///
/// This function returns a syntax tree on success, and `NULL` on failure. There
/// are three possible reasons for failure:
/// 1. The parser does not have a language assigned. Check for this using the
///    `ts_parser_language` function.
/// 2. Parsing was cancelled due to a timeout that was set by an earlier call to
///    the `ts_parser_set_timeout_micros` function. You can resume parsing from
///    where the parser left out by calling `ts_parser_parse` again with the
///    same arguments. Or you can start parsing from scratch by first calling
///    `ts_parser_reset`.
/// 3. Parsing was cancelled using a cancellation flag that was set by an
///    earlier call to `ts_parser_set_cancellation_flag`. You can resume parsing
///    from where the parser left out by calling `ts_parser_parse` again with
///    the same arguments.
#[no_mangle]
pub unsafe extern "C" fn ts_parser_parse(
    mut self_0: *mut TSParser,
    mut old_tree: *const TSTree,
    mut input: TSInput,
) -> *mut TSTree {
    if (*self_0).language.is_null() || input.read.is_none() {
        return std::ptr::null_mut::<TSTree>();
    }
    ts_lexer_set_input(&mut (*self_0).lexer, input);
    (*self_0).included_range_differences.size = 0 as os::raw::c_int as u32;
    (*self_0).included_range_difference_index = 0 as os::raw::c_int as os::raw::c_uint;
    if ts_parser_has_outstanding_parse(self_0) {
        if (*self_0).lexer.logger.log.is_some() || (*self_0).dot_graph_file.is_valid() {
            snwrite!(
                (*self_0).lexer.debug_buffer.as_mut_ptr(),
                1024,
                "resume_parsing",
            )
            .unwrap();
            ts_parser__log(self_0);
        }
    } else if !old_tree.is_null() {
        ts_subtree_retain((*old_tree).root);
        (*self_0).old_tree = (*old_tree).root;
        ts_range_array_get_changed_ranges(
            (*old_tree).included_ranges,
            (*old_tree).included_range_count,
            (*self_0).lexer.included_ranges,
            (*self_0).lexer.included_range_count as os::raw::c_uint,
            &mut (*self_0).included_range_differences,
        );
        reusable_node_reset(&mut (*self_0).reusable_node, (*old_tree).root);
        if (*self_0).lexer.logger.log.is_some() || (*self_0).dot_graph_file.is_valid() {
            snwrite!(
                (*self_0).lexer.debug_buffer.as_mut_ptr(),
                1024,
                "parse_after_edit",
            )
            .unwrap();
            ts_parser__log(self_0);
        }
        if (*self_0).dot_graph_file.is_valid() {
            let dot_graph_file = &mut (*self_0).dot_graph_file;
            ts_subtree_print_dot_graph((*self_0).old_tree, (*self_0).language, dot_graph_file);
            writeln!(dot_graph_file).unwrap();
        }
        let mut i: os::raw::c_uint = 0 as os::raw::c_int as os::raw::c_uint;
        while i < (*self_0).included_range_differences.size {
            let mut range: *mut TSRange = &mut *(*self_0)
                .included_range_differences
                .contents
                .offset(i as isize) as *mut TSRange;
            if (*self_0).lexer.logger.log.is_some() || (*self_0).dot_graph_file.is_valid() {
                snwrite!(
                    (*self_0).lexer.debug_buffer.as_mut_ptr(),
                    1024,
                    "different_included_range {} - {}",
                    (*range).start_byte,
                    (*range).end_byte,
                )
                .unwrap();
                ts_parser__log(self_0);
            }
            i = i.wrapping_add(1)
        }
    } else {
        reusable_node_clear(&mut (*self_0).reusable_node);
        if (*self_0).lexer.logger.log.is_some() || (*self_0).dot_graph_file.is_valid() {
            snwrite!((*self_0).lexer.debug_buffer.as_mut_ptr(), 1024, "new_parse").unwrap();
            ts_parser__log(self_0);
        }
    }
    let mut position: u32 = 0 as os::raw::c_int as u32;
    let mut last_position: u32 = 0 as os::raw::c_int as u32;
    let mut version_count: u32 = 0 as os::raw::c_int as u32;
    (*self_0).operation_count = 0 as os::raw::c_int as os::raw::c_uint;
    if (*self_0).timeout_duration.as_micros() != 0 {
        (*self_0).end_instant = Some(Instant::now() + (*self_0).timeout_duration);
    } else {
        (*self_0).end_instant = None;
    }
    loop {
        let mut version: StackVersion = 0 as os::raw::c_int as StackVersion;
        loop {
            version_count = ts_stack_version_count((*self_0).stack);
            if version >= version_count {
                break;
            }
            let mut allow_node_reuse: bool =
                version_count == 1 as os::raw::c_int as os::raw::c_uint;
            while ts_stack_is_active((*self_0).stack, version) {
                if (*self_0).lexer.logger.log.is_some() || (*self_0).dot_graph_file.is_valid() {
                    snwrite!(
                        (*self_0).lexer.debug_buffer.as_mut_ptr(),
                        1024 as usize,
                        "process version:{}, version_count:{}, state:{}, row:{}, col:{}",
                        version,
                        ts_stack_version_count((*self_0).stack),
                        ts_stack_state((*self_0).stack, version) as os::raw::c_int,
                        ts_stack_position((*self_0).stack, version)
                            .extent
                            .row
                            .wrapping_add(1),
                        ts_stack_position((*self_0).stack, version).extent.column,
                    )
                    .unwrap();
                    ts_parser__log(self_0);
                }
                if !ts_parser__advance(self_0, version, allow_node_reuse) {
                    return std::ptr::null_mut::<TSTree>();
                }
                if (*self_0).dot_graph_file.is_valid() {
                    let dot_graph_file = &mut (*self_0).dot_graph_file;
                    ts_stack_print_dot_graph((*self_0).stack, (*self_0).language, dot_graph_file);
                    write!(dot_graph_file, "\n\n").unwrap();
                }
                position = ts_stack_position((*self_0).stack, version).bytes;
                if !(position > last_position
                    || version > 0 as os::raw::c_int as os::raw::c_uint
                        && position == last_position)
                {
                    continue;
                }
                last_position = position;
                break;
            }
            version = version.wrapping_add(1)
        }
        let mut min_error_cost: os::raw::c_uint = ts_parser__condense_stack(self_0);
        if !(*self_0).finished_tree.ptr.is_null()
            && ts_subtree_error_cost((*self_0).finished_tree) < min_error_cost
        {
            break;
        }
        while (*self_0).included_range_difference_index < (*self_0).included_range_differences.size
        {
            let mut range_0: *mut TSRange = &mut *(*self_0)
                .included_range_differences
                .contents
                .offset((*self_0).included_range_difference_index as isize)
                as *mut TSRange;
            if (*range_0).end_byte > position {
                break;
            }
            (*self_0).included_range_difference_index =
                (*self_0).included_range_difference_index.wrapping_add(1)
        }
        if version_count == 0 as os::raw::c_int as os::raw::c_uint {
            break;
        }
    }
    ts_subtree_balance(
        (*self_0).finished_tree,
        &mut (*self_0).tree_pool,
        (*self_0).language,
    );
    if (*self_0).lexer.logger.log.is_some() || (*self_0).dot_graph_file.is_valid() {
        snwrite!((*self_0).lexer.debug_buffer.as_mut_ptr(), 1024, "done",).unwrap();
        ts_parser__log(self_0);
    }
    if (*self_0).dot_graph_file.is_valid() {
        let dot_graph_file = &mut (*self_0).dot_graph_file;
        ts_subtree_print_dot_graph((*self_0).finished_tree, (*self_0).language, dot_graph_file);
        writeln!(dot_graph_file).unwrap();
    }
    let mut result: *mut TSTree = ts_tree_new(
        (*self_0).finished_tree,
        (*self_0).language,
        (*self_0).lexer.included_ranges,
        (*self_0).lexer.included_range_count as os::raw::c_uint,
    );
    (*self_0).finished_tree = Subtree {
        ptr: std::ptr::null::<SubtreeHeapData>(),
    };
    ts_parser_reset(self_0);
    result
}

/// Use the parser to parse some source code stored in one contiguous buffer.
/// The first two parameters are the same as in the `ts_parser_parse` function
/// above. The second two parameters indicate the location of the buffer and its
/// length in bytes.
#[no_mangle]
pub(crate) unsafe extern "C" fn ts_parser_parse_string(
    mut self_0: *mut TSParser,
    mut old_tree: *const TSTree,
    mut string: *const os::raw::c_char,
    mut length: u32,
) -> *mut TSTree {
    ts_parser_parse_string_encoding(self_0, old_tree, string, length, TSInputEncodingUTF8)
}

/// Use the parser to parse some source code stored in one contiguous buffer with
/// a given encoding. The first four parameters work the same as in the
/// `ts_parser_parse_string` method above. The final parameter indicates whether
/// the text is encoded as UTF8 or UTF16.
#[no_mangle]
pub(crate) unsafe extern "C" fn ts_parser_parse_string_encoding(
    mut self_0: *mut TSParser,
    mut old_tree: *const TSTree,
    mut string: *const os::raw::c_char,
    mut length: u32,
    mut encoding: TSInputEncoding,
) -> *mut TSTree {
    let mut input = TSStringInput { string, length };
    ts_parser_parse(self_0, old_tree, {
        TSInput {
            payload: &mut input as *mut TSStringInput as *mut ffi::c_void,
            read: Some(
                ts_string_input_read
                    as unsafe extern "C" fn(
                        _: *mut ffi::c_void,
                        _: u32,
                        _: TSPoint,
                        _: *mut u32,
                    ) -> *const os::raw::c_char,
            ),
            encoding,
        }
    })
}
