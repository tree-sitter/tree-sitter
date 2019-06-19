use std::str;

pub struct LossyUtf8<'a> {
    bytes: &'a [u8],
    in_replacement: bool,
}

impl<'a> LossyUtf8<'a> {
    pub fn new(bytes: &'a [u8]) -> Self {
        LossyUtf8 {
            bytes,
            in_replacement: false,
        }
    }
}

impl<'a> Iterator for LossyUtf8<'a> {
    type Item = &'a str;

    fn next(&mut self) -> Option<&'a str> {
        if self.bytes.is_empty() {
            return None;
        }
        if self.in_replacement {
            self.in_replacement = false;
            return Some("\u{fffd}");
        }
        match str::from_utf8(self.bytes) {
            Ok(valid) => {
                self.bytes = &[];
                Some(valid)
            }
            Err(error) => {
                if let Some(error_len) = error.error_len() {
                    let error_start = error.valid_up_to();
                    if error_start > 0 {
                        let result =
                            unsafe { str::from_utf8_unchecked(&self.bytes[..error_start]) };
                        self.bytes = &self.bytes[(error_start + error_len)..];
                        self.in_replacement = true;
                        Some(result)
                    } else {
                        self.bytes = &self.bytes[error_len..];
                        Some("\u{fffd}")
                    }
                } else {
                    None
                }
            }
        }
    }
}

pub fn html_escape(c: u8) -> Option<&'static [u8]> {
    match c as char {
        '>' => Some(b"&gt;"),
        '<' => Some(b"&lt;"),
        '&' => Some(b"&amp;"),
        '\'' => Some(b"&#39;"),
        '"' => Some(b"&quot;"),
        _ => None,
    }
}
