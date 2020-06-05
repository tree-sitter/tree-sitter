use crate::{util::snwrite, *};

use std::{ffi, os, ptr, ptr::copy_nonoverlapping};

static mut BYTE_ORDER_MARK: i32 = 0xfeff as os::raw::c_int;

static mut DEFAULT_RANGE: TSRange = TSRange {
    start_point: TSPoint {
        row: 0 as os::raw::c_int as u32,
        column: 0 as os::raw::c_int as u32,
    },
    end_point: TSPoint {
        row: 4_294_967_295 as os::raw::c_uint,
        column: 4_294_967_295 as os::raw::c_uint,
    },
    start_byte: 0 as os::raw::c_int as u32,
    end_byte: 4_294_967_295 as os::raw::c_uint,
};

// Check if the lexer has reached EOF. This state is stored
// by setting the lexer's `current_included_range_index` such that
// it has consumed all of its available ranges.
unsafe extern "C" fn ts_lexer__eof(mut _self: *const TSLexer) -> bool {
    let mut self_0: *mut Lexer = _self as *mut Lexer;
    (*self_0).current_included_range_index == (*self_0).included_range_count
}
// Clear the currently stored chunk of source code, because the lexer's
// position has changed.
unsafe extern "C" fn ts_lexer__clear_chunk(mut self_0: *mut Lexer) {
    (*self_0).chunk = ptr::null();
    (*self_0).chunk_size = 0 as os::raw::c_int as u32;
    (*self_0).chunk_start = 0 as os::raw::c_int as u32;
}
// Call the lexer's input callback to obtain a new chunk of source code
// for the current position.
unsafe extern "C" fn ts_lexer__get_chunk(mut self_0: *mut Lexer) {
    (*self_0).chunk_start = (*self_0).current_position.bytes;
    (*self_0).chunk = (*self_0).input.read.expect("non-null function pointer")(
        (*self_0).input.payload,
        (*self_0).current_position.bytes,
        (*self_0).current_position.extent,
        &mut (*self_0).chunk_size,
    );
    if (*self_0).chunk_size == 0 {
        (*self_0).current_included_range_index = (*self_0).included_range_count;
        (*self_0).chunk = ptr::null()
    };
}
// Decode the next unicode character in the current chunk of source code.
// This assumes that the lexer has already retrieved a chunk of source
// code that spans the current position.
unsafe extern "C" fn ts_lexer__get_lookahead(mut self_0: *mut Lexer) {
    let mut position_in_chunk: u32 = (*self_0)
        .current_position
        .bytes
        .wrapping_sub((*self_0).chunk_start);
    let mut chunk: *const u8 = ((*self_0).chunk as *const u8).offset(position_in_chunk as isize);
    let mut size: u32 = (*self_0).chunk_size.wrapping_sub(position_in_chunk);
    if size == 0 as os::raw::c_int as os::raw::c_uint {
        (*self_0).lookahead_size = 1 as os::raw::c_int as u32;
        (*self_0).data.lookahead = '\u{0}' as i32;
        return;
    }
    let mut decode: UnicodeDecodeFunction = if (*self_0).input.encoding as os::raw::c_uint
        == TSInputEncodingUTF8 as os::raw::c_int as os::raw::c_uint
    {
        Some(ts_decode_utf8 as unsafe extern "C" fn(_: *const u8, _: u32, _: *mut i32) -> u32)
    } else {
        Some(ts_decode_utf16 as unsafe extern "C" fn(_: *const u8, _: u32, _: *mut i32) -> u32)
    };
    (*self_0).lookahead_size =
        decode.expect("non-null function pointer")(chunk, size, &mut (*self_0).data.lookahead);
    // If this chunk ended in the middle of a multi-byte character,
    // try again with a fresh chunk.
    if (*self_0).data.lookahead == TS_DECODE_ERROR && size < 4 as os::raw::c_int as os::raw::c_uint
    {
        ts_lexer__get_chunk(self_0);
        chunk = (*self_0).chunk as *const u8;
        size = (*self_0).chunk_size;
        (*self_0).lookahead_size =
            decode.expect("non-null function pointer")(chunk, size, &mut (*self_0).data.lookahead)
    }
    if (*self_0).data.lookahead == TS_DECODE_ERROR {
        (*self_0).lookahead_size = 1 as os::raw::c_int as u32
    };
}
// Advance to the next character in the source code, retrieving a new
// chunk of source code if needed.
unsafe extern "C" fn ts_lexer__advance(mut _self: *mut TSLexer, mut skip: bool) {
    let mut self_0: *mut Lexer = _self as *mut Lexer;
    if (*self_0).chunk.is_null() {
        return;
    }
    if skip {
        if (*self_0).logger.log.is_some() {
            if 32 as os::raw::c_int <= (*self_0).data.lookahead
                && (*self_0).data.lookahead < 127 as os::raw::c_int
            {
                snwrite!(
                    (*self_0).debug_buffer.as_mut_ptr(),
                    1024,
                    "skip character:\'{}\'",
                    (*self_0).data.lookahead as u8 as char,
                )
                .unwrap();
            } else {
                snwrite!(
                    (*self_0).debug_buffer.as_mut_ptr(),
                    1024,
                    "skip character:{}",
                    (*self_0).data.lookahead,
                )
                .unwrap();
            }
            (*self_0).logger.log.expect("non-null function pointer")(
                (*self_0).logger.payload,
                TSLogTypeLex,
                (*self_0).debug_buffer.as_mut_ptr(),
            );
        }
    } else if (*self_0).logger.log.is_some() {
        if 32 as os::raw::c_int <= (*self_0).data.lookahead
            && (*self_0).data.lookahead < 127 as os::raw::c_int
        {
            snwrite!(
                (*self_0).debug_buffer.as_mut_ptr(),
                1024,
                "consume character:\'{}\'",
                (*self_0).data.lookahead as u8 as char,
            )
            .unwrap();
        } else {
            snwrite!(
                (*self_0).debug_buffer.as_mut_ptr(),
                1024,
                "consume character:{}",
                (*self_0).data.lookahead,
            )
            .unwrap();
        }
        (*self_0).logger.log.expect("non-null function pointer")(
            (*self_0).logger.payload,
            TSLogTypeLex,
            (*self_0).debug_buffer.as_mut_ptr(),
        );
    }
    if (*self_0).lookahead_size != 0 {
        (*self_0).current_position.bytes = ((*self_0).current_position.bytes as os::raw::c_uint)
            .wrapping_add((*self_0).lookahead_size)
            as u32 as u32;
        if (*self_0).data.lookahead == '\n' as i32 {
            (*self_0).current_position.extent.row =
                (*self_0).current_position.extent.row.wrapping_add(1);
            (*self_0).current_position.extent.column = 0 as os::raw::c_int as u32
        } else {
            (*self_0).current_position.extent.column =
                ((*self_0).current_position.extent.column as os::raw::c_uint)
                    .wrapping_add((*self_0).lookahead_size) as u32 as u32
        }
    }
    let mut current_range: *const TSRange = std::ptr::null::<TSRange>();
    if (*self_0).current_included_range_index < (*self_0).included_range_count {
        current_range = &mut *(*self_0)
            .included_ranges
            .add((*self_0).current_included_range_index) as *mut TSRange;
        if (*self_0).current_position.bytes == (*current_range).end_byte {
            (*self_0).current_included_range_index =
                (*self_0).current_included_range_index.wrapping_add(1);
            if (*self_0).current_included_range_index < (*self_0).included_range_count {
                current_range = current_range.offset(1);
                (*self_0).current_position = Length {
                    bytes: (*current_range).start_byte,
                    extent: (*current_range).start_point,
                }
            } else {
                current_range = std::ptr::null::<TSRange>()
            }
        }
    }
    if skip {
        (*self_0).token_start_position = (*self_0).current_position
    }
    if !current_range.is_null() {
        if (*self_0).current_position.bytes
            >= (*self_0).chunk_start.wrapping_add((*self_0).chunk_size)
        {
            ts_lexer__get_chunk(self_0);
        }
        ts_lexer__get_lookahead(self_0);
    } else {
        ts_lexer__clear_chunk(self_0);
        (*self_0).data.lookahead = '\u{0}' as i32;
        (*self_0).lookahead_size = 1 as os::raw::c_int as u32
    };
}
// Mark that a token match has completed. This can be called multiple
// times if a longer match is found later.
unsafe extern "C" fn ts_lexer__mark_end(mut _self: *mut TSLexer) {
    let mut self_0: *mut Lexer = _self as *mut Lexer;
    if !ts_lexer__eof(&(*self_0).data) {
        // If the lexer is right at the beginning of included range,
        // then the token should be considered to end at the *end* of the
        // previous included range, rather than here.
        let mut current_included_range: *mut TSRange = &mut *(*self_0)
            .included_ranges
            .add((*self_0).current_included_range_index)
            as *mut TSRange;
        if (*self_0).current_included_range_index > 0
            && (*self_0).current_position.bytes == (*current_included_range).start_byte
        {
            let mut previous_included_range: *mut TSRange =
                current_included_range.offset(-(1 as os::raw::c_int as isize));
            (*self_0).token_end_position = Length {
                bytes: (*previous_included_range).end_byte,
                extent: (*previous_included_range).end_point,
            };
            return;
        }
    }
    (*self_0).token_end_position = (*self_0).current_position;
}
unsafe extern "C" fn ts_lexer__get_column(mut _self: *mut TSLexer) -> u32 {
    let mut self_0: *mut Lexer = _self as *mut Lexer;
    let mut goal_byte: u32 = (*self_0).current_position.bytes;
    (*self_0).current_position.bytes = ((*self_0).current_position.bytes as os::raw::c_uint)
        .wrapping_sub((*self_0).current_position.extent.column)
        as u32 as u32;
    (*self_0).current_position.extent.column = 0 as os::raw::c_int as u32;
    if (*self_0).current_position.bytes < (*self_0).chunk_start {
        ts_lexer__get_chunk(self_0);
    }
    let mut result: u32 = 0 as os::raw::c_int as u32;
    while (*self_0).current_position.bytes < goal_byte {
        ts_lexer__advance(&mut (*self_0).data, false);
        result = result.wrapping_add(1)
    }
    result
}
// Is the lexer at a boundary between two disjoint included ranges of
// source code? This is exposed as an API because some languages' external
// scanners need to perform custom actions at these bounaries.
unsafe extern "C" fn ts_lexer__is_at_included_range_start(mut _self: *const TSLexer) -> bool {
    let mut self_0: *const Lexer = _self as *const Lexer;
    if (*self_0).current_included_range_index < (*self_0).included_range_count {
        let mut current_range: *mut TSRange = &mut *(*self_0)
            .included_ranges
            .add((*self_0).current_included_range_index)
            as *mut TSRange;
        (*self_0).current_position.bytes == (*current_range).start_byte
    } else {
        false
    }
}
#[no_mangle]
pub(crate) unsafe extern "C" fn ts_lexer_init(mut self_0: *mut Lexer) {
    *self_0 = Lexer {
        data: TSLexer {
            lookahead: 0 as os::raw::c_int,
            result_symbol: 0 as os::raw::c_int as TSSymbol,
            advance: Some(
                ts_lexer__advance as unsafe extern "C" fn(_: *mut TSLexer, _: bool) -> (),
            ),
            mark_end: Some(ts_lexer__mark_end as unsafe extern "C" fn(_: *mut TSLexer) -> ()),
            get_column: Some(ts_lexer__get_column as unsafe extern "C" fn(_: *mut TSLexer) -> u32),
            is_at_included_range_start: Some(
                ts_lexer__is_at_included_range_start
                    as unsafe extern "C" fn(_: *const TSLexer) -> bool,
            ),
            eof: Some(ts_lexer__eof as unsafe extern "C" fn(_: *const TSLexer) -> bool),
        },
        current_position: Length {
            bytes: 0 as os::raw::c_int as u32,
            extent: TSPoint {
                row: 0 as os::raw::c_int as u32,
                column: 0 as os::raw::c_int as u32,
            },
        },
        token_start_position: Length {
            bytes: 0,
            extent: TSPoint { row: 0, column: 0 },
        },
        token_end_position: Length {
            bytes: 0,
            extent: TSPoint { row: 0, column: 0 },
        },
        included_ranges: std::ptr::null_mut::<TSRange>(),
        included_range_count: 0 as os::raw::c_int as usize,
        current_included_range_index: 0 as os::raw::c_int as usize,
        chunk: ptr::null(),
        chunk_start: 0 as os::raw::c_int as u32,
        chunk_size: 0 as os::raw::c_int as u32,
        lookahead_size: 0,
        input: TSInput {
            payload: ptr::null_mut(),
            read: None,
            encoding: TSInputEncodingUTF8,
        },
        logger: TSLogger {
            payload: ptr::null_mut(),
            log: None,
        },
        debug_buffer: [0; 1024],
    };
    ts_lexer_set_included_ranges(
        self_0,
        std::ptr::null::<TSRange>(),
        0 as os::raw::c_int as u32,
    );
}
#[no_mangle]
pub(crate) unsafe extern "C" fn ts_lexer_delete(mut self_0: *mut Lexer) {
    ts_free((*self_0).included_ranges as *mut ffi::c_void);
}
unsafe extern "C" fn ts_lexer_goto(mut self_0: *mut Lexer, mut position: Length) {
    (*self_0).current_position = position;
    let mut found_included_range: bool = false;
    // Move to the first valid position at or after the given position.
    let mut i: os::raw::c_uint = 0 as os::raw::c_int as os::raw::c_uint;
    while (i as usize) < (*self_0).included_range_count {
        let mut included_range: *mut TSRange =
            &mut *(*self_0).included_ranges.offset(i as isize) as *mut TSRange;
        if (*included_range).end_byte > position.bytes {
            if (*included_range).start_byte > position.bytes {
                (*self_0).current_position = Length {
                    bytes: (*included_range).start_byte,
                    extent: (*included_range).start_point,
                }
            }
            (*self_0).current_included_range_index = i as usize;
            found_included_range = true;
            break;
        } else {
            i = i.wrapping_add(1)
        }
    }
    if found_included_range {
        // If the current position is outside of the current chunk of text,
        // then clear out the current chunk of text.
        if !(*self_0).chunk.is_null()
            && (position.bytes < (*self_0).chunk_start
                || position.bytes >= (*self_0).chunk_start.wrapping_add((*self_0).chunk_size))
        {
            ts_lexer__clear_chunk(self_0);
        }
        (*self_0).lookahead_size = 0 as os::raw::c_int as u32;
        (*self_0).data.lookahead = '\u{0}' as i32
    } else {
        // If the given position is beyond any of included ranges, move to the EOF
        // state - past the end of the included ranges.
        (*self_0).current_included_range_index = (*self_0).included_range_count;
        let mut last_included_range: *mut TSRange = &mut *(*self_0)
            .included_ranges
            .add((*self_0).included_range_count.wrapping_sub(1))
            as *mut TSRange;
        (*self_0).current_position = Length {
            bytes: (*last_included_range).end_byte,
            extent: (*last_included_range).end_point,
        };
        ts_lexer__clear_chunk(self_0);
        (*self_0).lookahead_size = 1 as os::raw::c_int as u32;
        (*self_0).data.lookahead = '\u{0}' as i32
    };
}
#[no_mangle]
pub(crate) unsafe extern "C" fn ts_lexer_set_input(mut self_0: *mut Lexer, mut input: TSInput) {
    (*self_0).input = input;
    ts_lexer__clear_chunk(self_0);
    ts_lexer_goto(self_0, (*self_0).current_position);
}
// Move the lexer to the given position. This doesn't do any work
// if the parser is already at the given position.
#[no_mangle]
pub(crate) unsafe extern "C" fn ts_lexer_reset(mut self_0: *mut Lexer, mut position: Length) {
    if position.bytes != (*self_0).current_position.bytes {
        ts_lexer_goto(self_0, position);
    };
}
#[no_mangle]
pub(crate) unsafe extern "C" fn ts_lexer_start(mut self_0: *mut Lexer) {
    (*self_0).token_start_position = (*self_0).current_position;
    (*self_0).token_end_position = LENGTH_UNDEFINED;
    (*self_0).data.result_symbol = 0 as os::raw::c_int as TSSymbol;
    if !ts_lexer__eof(&(*self_0).data) {
        if (*self_0).chunk_size == 0 {
            ts_lexer__get_chunk(self_0);
        }
        if (*self_0).lookahead_size == 0 {
            ts_lexer__get_lookahead(self_0);
        }
        if (*self_0).current_position.bytes == 0 as os::raw::c_int as os::raw::c_uint
            && (*self_0).data.lookahead == BYTE_ORDER_MARK
        {
            ts_lexer__advance(&mut (*self_0).data, true);
        }
    };
}
#[no_mangle]
pub(crate) unsafe extern "C" fn ts_lexer_finish(
    mut self_0: *mut Lexer,
    mut lookahead_end_byte: *mut u32,
) {
    if length_is_undefined((*self_0).token_end_position) {
        ts_lexer__mark_end(&mut (*self_0).data);
    }
    let mut current_lookahead_end_byte: u32 = (*self_0).current_position.bytes.wrapping_add(1);
    // In order to determine that a byte sequence is invalid UTF8 or UTF16,
    // the character decoding algorithm may have looked at the following byte.
    // Therefore, the next byte *after* the current (invalid) character
    // affects the interpretation of the current character.
    if (*self_0).data.lookahead == TS_DECODE_ERROR {
        current_lookahead_end_byte = current_lookahead_end_byte.wrapping_add(1)
    }
    if current_lookahead_end_byte > *lookahead_end_byte {
        *lookahead_end_byte = current_lookahead_end_byte
    };
}
#[no_mangle]
pub(crate) unsafe extern "C" fn ts_lexer_advance_to_end(mut self_0: *mut Lexer) {
    while !(*self_0).chunk.is_null() {
        ts_lexer__advance(&mut (*self_0).data, false);
    }
}
#[no_mangle]
pub(crate) unsafe extern "C" fn ts_lexer_mark_end(mut self_0: *mut Lexer) {
    ts_lexer__mark_end(&mut (*self_0).data);
}
#[no_mangle]
pub(crate) unsafe extern "C" fn ts_lexer_set_included_ranges(
    mut self_0: *mut Lexer,
    mut ranges: *const TSRange,
    mut count: u32,
) -> bool {
    if count == 0 as os::raw::c_int as os::raw::c_uint || ranges.is_null() {
        ranges = &DEFAULT_RANGE;
        count = 1 as os::raw::c_int as u32
    } else {
        let mut previous_byte: u32 = 0 as os::raw::c_int as u32;
        let mut i: os::raw::c_uint = 0 as os::raw::c_int as os::raw::c_uint;
        while i < count {
            let mut range: *const TSRange = &*ranges.offset(i as isize) as *const TSRange;
            if (*range).start_byte < previous_byte || (*range).end_byte < (*range).start_byte {
                return false;
            }
            previous_byte = (*range).end_byte;
            i = i.wrapping_add(1)
        }
    }
    let mut size: usize = (count as usize).wrapping_mul(::std::mem::size_of::<TSRange>());
    (*self_0).included_ranges =
        ts_realloc((*self_0).included_ranges as *mut ffi::c_void, size) as *mut TSRange;
    copy_nonoverlapping(ranges, (*self_0).included_ranges, count as usize);
    (*self_0).included_range_count = count as usize;
    ts_lexer_goto(self_0, (*self_0).current_position);
    true
}
#[no_mangle]
pub(crate) unsafe extern "C" fn ts_lexer_included_ranges(
    mut self_0: *const Lexer,
    mut count: *mut u32,
) -> *mut TSRange {
    *count = (*self_0).included_range_count as u32;
    (*self_0).included_ranges
}
