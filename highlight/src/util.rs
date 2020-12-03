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
