//! String escape decoding.

use std::ops::Range;

use memchr::memchr;
use serde::{Deserialize, Serialize};
use thiserror::Error;

use crate::nativedsl::diagnostic::DiagnosticChar;

#[derive(Debug, PartialEq, Eq, Serialize, Deserialize, Error)]
pub enum EscapeErrorKind {
    #[error("invalid escape sequence: \\{}", DiagnosticChar(*.0))]
    Invalid(char),
    #[error("invalid hex escape: expected \\xHH with HH in 00..7F (ASCII range)")]
    InvalidHex,
    #[error(
        "invalid unicode escape: expected \\uHHHH or \\u{{H..H}} (max 0x10FFFF, no surrogates)"
    )]
    InvalidUnicode,
}

#[derive(Debug)]
pub(super) struct EscapeError {
    pub kind: EscapeErrorKind,
    pub range: Range<usize>,
}

/// Decode the escape sequences in a quote-stripped string literal's text into
/// `out`, replacing its previous contents.
///
/// # Errors
///
/// Returns the first malformed escape and its byte range within `raw`.
pub(super) fn unescape_string_into(raw: &str, out: &mut String) -> Result<(), EscapeError> {
    let bytes = raw.as_bytes();
    out.clear();
    out.reserve(raw.len());
    let mut i = 0;

    while let Some(backslash_off) = memchr(b'\\', &bytes[i..]) {
        let escape_start = i + backslash_off;
        out.push_str(&raw[i..escape_start]);

        let escape_code_pos = escape_start + 1;
        let Some(&escape_code) = bytes.get(escape_code_pos) else {
            return Err(EscapeError {
                kind: EscapeErrorKind::Invalid('\\'),
                range: escape_start..raw.len(),
            });
        };

        match escape_code {
            c @ (b'"' | b'\\') => {
                out.push(char::from(c));
                i = escape_code_pos + 1;
            }
            b'n' => {
                out.push('\n');
                i = escape_code_pos + 1;
            }
            b't' => {
                out.push('\t');
                i = escape_code_pos + 1;
            }
            b'r' => {
                out.push('\r');
                i = escape_code_pos + 1;
            }
            b'0' => {
                out.push('\0');
                i = escape_code_pos + 1;
            }
            b'x' => {
                let digits_start = escape_code_pos + 1;
                let value = read_hex_digits(raw, digits_start, 2).map_err(|end| EscapeError {
                    kind: EscapeErrorKind::InvalidHex,
                    range: escape_start..end,
                })?;
                i = digits_start + 2;

                let Some(ch) = char::from_u32(value).filter(char::is_ascii) else {
                    return Err(EscapeError {
                        kind: EscapeErrorKind::InvalidHex,
                        range: escape_start..i,
                    });
                };

                out.push(ch);
            }
            b'u' => {
                // \uHHHH (4 hex) or \u{H..H} (1-6 hex in braces), UTF-8 encoded.
                let after_u = escape_code_pos + 1;
                let (codepoint, end) = if bytes.get(after_u) == Some(&b'{') {
                    let digits_start = escape_code_pos + 2;
                    let mut codepoint = 0;
                    let mut pos = digits_start;

                    for _ in 0..6 {
                        let Some(digit) = bytes
                            .get(pos)
                            .and_then(|&byte| char::from(byte).to_digit(16))
                        else {
                            break;
                        };
                        codepoint = codepoint * 16 + digit;
                        pos += 1;
                    }

                    if pos == digits_start || bytes.get(pos) != Some(&b'}') {
                        return Err(EscapeError {
                            kind: EscapeErrorKind::InvalidUnicode,
                            range: escape_start..past_char(raw, pos),
                        });
                    }

                    (codepoint, pos + 1)
                } else {
                    let codepoint =
                        read_hex_digits(raw, after_u, 4).map_err(|end| EscapeError {
                            kind: EscapeErrorKind::InvalidUnicode,
                            range: escape_start..end,
                        })?;
                    (codepoint, after_u + 4)
                };

                let Some(ch) = char::from_u32(codepoint) else {
                    return Err(EscapeError {
                        kind: EscapeErrorKind::InvalidUnicode,
                        range: escape_start..end,
                    });
                };

                out.push(ch);
                i = end;
            }
            _ => {
                let ch = raw[escape_code_pos..].chars().next().unwrap();
                return Err(EscapeError {
                    kind: EscapeErrorKind::Invalid(ch),
                    range: escape_start..escape_code_pos + ch.len_utf8(),
                });
            }
        }
    }

    out.push_str(&raw[i..]);
    Ok(())
}

/// First char boundary strictly after byte `i` (or `source.len()` if `i` is at
/// or past the end).
const fn past_char(source: &str, i: usize) -> usize {
    if i >= source.len() {
        return source.len();
    }
    let mut j = i + 1;
    while !source.is_char_boundary(j) {
        j += 1;
    }
    j
}

/// Read exactly `digit_count` ASCII hexadecimal digits starting at `start`.
///
/// On failure, returns the first UTF-8 boundary after the invalid character, or
/// `source.len()` at EOF. This allows the caller to include the entire invalid
/// range in its error span.
fn read_hex_digits(source: &str, start: usize, digit_count: usize) -> Result<u32, usize> {
    let bytes = source.as_bytes();
    let mut value = 0u32;

    for i in 0..digit_count {
        let Some(digit) = bytes
            .get(start + i)
            .and_then(|&byte| char::from(byte).to_digit(16))
        else {
            return Err(past_char(source, start + i));
        };
        value = value * 16 + digit;
    }
    Ok(value)
}
