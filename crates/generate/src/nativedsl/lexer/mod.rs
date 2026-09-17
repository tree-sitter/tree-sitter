//! The byte-level tokenizer.
//!
//! Splits into [`token`] (the [`TokenKind`]/[`Token`] vocabulary, shared with
//! the parser), and [`error`] ([`LexErrorKind`]).

mod error;
mod token;

pub use error::{LexErrorKind, LexResult};
pub use token::{Token, TokenKind};

use memchr::{memchr, memchr2};

use crate::nativedsl::{DocumentId, DocumentRef, LexError, ast::Span};

/// Byte classification flags for the lexer's hot loops.
const CLASS_WHITESPACE: u8 = 0b0000_0001;
const CLASS_IDENT_CONTINUE: u8 = 0b0000_0010;
const CLASS_IDENT_START: u8 = 0b0000_0100;

/// Lookup table mapping byte value to classification flags.
const BYTE_CLASS: [u8; 256] = {
    let mut t = [0u8; 256];
    t[b' ' as usize] = CLASS_WHITESPACE;
    t[b'\t' as usize] = CLASS_WHITESPACE;
    t[b'\n' as usize] = CLASS_WHITESPACE;
    t[b'\r' as usize] = CLASS_WHITESPACE;
    t[0x0c] = CLASS_WHITESPACE; // form feed
    let mut i = b'a';
    while i <= b'z' {
        t[i as usize] |= CLASS_IDENT_CONTINUE | CLASS_IDENT_START;
        i += 1;
    }
    i = b'A';
    while i <= b'Z' {
        t[i as usize] |= CLASS_IDENT_CONTINUE | CLASS_IDENT_START;
        i += 1;
    }
    i = b'0';
    while i <= b'9' {
        t[i as usize] |= CLASS_IDENT_CONTINUE;
        i += 1;
    }
    t[b'_' as usize] |= CLASS_IDENT_CONTINUE | CLASS_IDENT_START;
    t
};

#[inline]
const fn byte_is(b: u8, class: u8) -> bool {
    BYTE_CLASS[b as usize] & class != 0
}

/// True iff `s` is shaped like an `Ident` token.
#[must_use]
pub fn is_ident_str(s: &str) -> bool {
    let bytes = s.as_bytes();
    let Some((&first, rest)) = bytes.split_first() else {
        return false;
    };
    byte_is(first, CLASS_IDENT_START) && rest.iter().all(|&b| byte_is(b, CLASS_IDENT_CONTINUE))
}

pub struct Lexer<'src> {
    source: &'src [u8],
    document: DocumentId,
    pos: usize,
    /// Start offsets of comments, in source order. Preserved out of band for tooling.
    pub comment_starts: Vec<u32>,
}

impl<'src> Lexer<'src> {
    #[must_use]
    pub fn new(document: DocumentRef<'src>) -> Self {
        Self {
            source: document.text().as_bytes(),
            document: document.id(),
            pos: 0,
            comment_starts: Vec::new(),
        }
    }

    /// Consume the entire source and return all tokens. The returned vector
    /// always ends with `TokenKind::Eof`. Line comments are recorded in
    /// [`comment_starts`](Self::comment_starts).
    ///
    /// # Errors
    ///
    /// Returns [`LexError`] on unterminated strings or unexpected characters.
    pub fn tokenize(&mut self) -> LexResult<Vec<Token>> {
        self.pos = 0;
        self.comment_starts.clear();
        self.comment_starts.reserve(16);
        let mut tokens = Vec::with_capacity(self.source.len() / 4);
        let source = self.source;
        let len = source.len();

        loop {
            let mut token_start = self.pos;
            let b = loop {
                if token_start >= len {
                    self.pos = token_start;
                    tokens.push(Token {
                        kind: TokenKind::Eof,
                        span: Span::from_usize(token_start, token_start),
                    });
                    return Ok(tokens);
                }

                // SAFETY: `token_start < len` checked above
                let b = unsafe { *source.get_unchecked(token_start) };
                if !byte_is(b, CLASS_WHITESPACE) {
                    break b;
                }
                token_start += 1;
            };
            self.pos = token_start;

            if b == b'/'
                && token_start + 1 < len
                // SAFETY: `token_start + 1 < len` above ensures this is in bounds
                && unsafe { *source.get_unchecked(token_start + 1) == b'/' }
            {
                self.pos += 2;
                match memchr(b'\n', &source[self.pos..]) {
                    Some(offset) => self.pos += offset,
                    None => self.pos = len,
                }
                self.comment_starts.push(token_start as u32);
                continue;
            }

            tokens.push(self.next_token(b)?);
        }
    }

    fn peek(&self) -> Option<u8> {
        self.source.get(self.pos).copied()
    }

    const fn advance(&mut self) -> u8 {
        let b = self.source[self.pos];
        self.pos += 1;
        b
    }

    fn next_token(&mut self, b: u8) -> LexResult<Token> {
        let mut start = self.pos;
        self.pos += 1;
        let kind = match b {
            b'{' => TokenKind::LBrace,
            b'}' => TokenKind::RBrace,
            b'(' => TokenKind::LParen,
            b')' => TokenKind::RParen,
            b'[' => TokenKind::LBracket,
            b']' => TokenKind::RBracket,
            b',' => TokenKind::Comma,
            b':' => {
                if self.peek() == Some(b':') {
                    self.advance();
                    TokenKind::ColonColon
                } else {
                    TokenKind::Colon
                }
            }
            b'.' => TokenKind::Dot,
            b'=' => TokenKind::Eq,
            b'<' => TokenKind::Lt,
            b'>' => TokenKind::Gt,
            b'-' => TokenKind::Minus,
            b'+' => TokenKind::Plus,
            b'#' => TokenKind::Pound,
            b'@' => TokenKind::At,
            b'"' => self.lex_string(start)?,
            b'0'..=b'9' => self.lex_int(),
            b'a'..=b'z' | b'A'..=b'Z' | b'_' => self.lex_ident(&mut start)?,
            _ => {
                // SAFETY: `source` is valid UTF-8, and `start` is a character boundary
                // because the lexer advances only over ASCII bytes or complete characters.
                let rest = unsafe { std::str::from_utf8_unchecked(&self.source[start..]) };
                let ch = rest.chars().next().unwrap();
                self.pos = start + ch.len_utf8();
                return Err(LexError::new(
                    LexErrorKind::UnexpectedChar(ch),
                    self.document,
                    Span::from_usize(start, self.pos),
                ));
            }
        };
        Ok(Token {
            kind,
            span: Span::from_usize(start, self.pos),
        })
    }

    /// Scan a string literal. Token span will cover `"..."` including quotes.
    /// `self.pos` is not advanced on error.
    fn lex_string(&mut self, start: usize) -> LexResult<TokenKind> {
        let source = self.source;
        let mut pos = self.pos;
        loop {
            let quote_or_escape = memchr2(b'"', b'\\', &source[pos..]);
            let chunk_end = quote_or_escape.map_or(source.len(), |offset| pos + offset);

            if let Some(newline) = memchr(b'\n', &source[pos..chunk_end]) {
                return Err(LexError::new(
                    LexErrorKind::NewlineInString,
                    self.document,
                    Span::from_usize(start, pos + newline),
                ));
            }

            let Some(offset) = quote_or_escape else {
                return Err(LexError::new(
                    LexErrorKind::UnterminatedString,
                    self.document,
                    Span::from_usize(start, source.len()),
                ));
            };
            pos += offset;
            // SAFETY: memchr2 found a byte at this position, so pos < source.len().
            match unsafe { *source.get_unchecked(pos) } {
                b'"' => {
                    self.pos = pos + 1;
                    return Ok(TokenKind::StringLit);
                }
                b'\\' => {
                    let esc_pos = pos;
                    pos += 1;
                    if pos >= source.len() {
                        Err(LexError::new(
                            LexErrorKind::UnterminatedEscape,
                            self.document,
                            Span::from_usize(esc_pos, source.len()),
                        ))?;
                    }
                    // SAFETY: `pos < source.len()` checked above.
                    if unsafe { *source.get_unchecked(pos) == b'\n' } {
                        return Err(LexError::new(
                            LexErrorKind::NewlineInString,
                            self.document,
                            Span::from_usize(start, pos),
                        ));
                    }
                    // Escape validity is checked when the parser interprets the
                    // literal. Skip one byte so an escaped quote cannot terminate the
                    // token. Any remaining UTF-8 continuation bytes are ordinary input
                    // to the next byte search.
                    pos += 1;
                }
                // SAFETY: memchr2 only returns positions of b'"' or b'\\'.
                _ => unreachable!(),
            }
        }
    }

    /// Scan a raw string literal: r"...", r#"..."#, r##"..."##, etc.
    /// Called when we've already consumed `r` and peeked `"` or `#`.
    fn lex_raw_string(&mut self, start: usize) -> LexResult<TokenKind> {
        let source = self.source;
        let hash_start = self.pos;
        while self.peek() == Some(b'#') {
            self.advance();
        }
        let hash_count = self.pos - hash_start;
        let Ok(hash_count) = u8::try_from(hash_count) else {
            return Err(LexError::new(
                LexErrorKind::TooManyHashes(hash_count as u32),
                self.document,
                Span::from_usize(start, self.pos),
            ));
        };
        if self.peek() != Some(b'"') {
            Err(LexError::new(
                LexErrorKind::ExpectedRawStringQuote,
                self.document,
                Span::from_usize(start, self.pos),
            ))?;
        }
        self.advance(); // skip opening "

        // Scan for closing " followed by hash_count #'s
        let mut pos = self.pos;
        loop {
            let Some(offset) = memchr(b'"', &source[pos..]) else {
                return Err(LexError::new(
                    LexErrorKind::UnterminatedRawString,
                    self.document,
                    Span::from_usize(start, source.len()),
                ));
            };
            pos += offset + 1; // Advance past the "
            let mut found = 0u8;
            while found < hash_count
                && pos < source.len()
                // SAFETY: pos < source.len() is checked by the prior condition.
                && unsafe { *source.get_unchecked(pos) } == b'#'
            {
                pos += 1;
                found += 1;
            }
            if found == hash_count {
                self.pos = pos;
                return Ok(TokenKind::RawStringLit);
            }
        }
    }

    fn lex_int(&mut self) -> TokenKind {
        let source = self.source;
        let mut pos = self.pos;

        while pos < source.len() {
            // SAFETY: `pos < source.len()` checked above
            let digit = unsafe { *source.get_unchecked(pos) };
            if !digit.is_ascii_digit() {
                break;
            }
            pos += 1;
        }
        self.pos = pos;
        TokenKind::IntLit
    }

    fn lex_ident(&mut self, start: &mut usize) -> LexResult<TokenKind> {
        self.scan_ident_continue();
        // SAFETY: `next_token` consumed an in-bounds ASCII identifier-start
        // byte before calling this function, and `scan_ident_continue` advances
        // only over in-bounds ASCII identifier bytes. Therefore
        // `*start < self.pos <= self.source.len()` and the range is valid UTF-8.
        let text =
            unsafe { std::str::from_utf8_unchecked(self.source.get_unchecked(*start..self.pos)) };
        if text == "r" {
            match (self.peek(), self.source.get(self.pos + 1).copied()) {
                // `r#<ident>` is a raw identifier. Exlclude the `r#` prefix from
                // its token span so reslving the  span yields the bare name.
                (Some(b'#'), Some(c)) if byte_is(c, CLASS_IDENT_START) => {
                    self.pos += 1; // skip '#'
                    *start = self.pos;
                    self.pos += 1; // skip the ident-start char (already validated)
                    self.scan_ident_continue();
                    return Ok(TokenKind::Ident);
                }
                // r"..." or r#"..."# - raw string literal.
                (Some(b'"' | b'#'), _) => return self.lex_raw_string(*start),
                _ => {}
            }
        }
        Ok(TokenKind::from_keyword(text))
    }

    fn scan_ident_continue(&mut self) {
        let source = self.source;
        while self.pos < source.len()
            // SAFETY: pos < source.len() checked by loop condition.
            && byte_is(unsafe { *source.get_unchecked(self.pos) }, CLASS_IDENT_CONTINUE)
        {
            self.pos += 1;
        }
    }
}
