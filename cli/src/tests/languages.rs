use tree_sitter::Language;

extern "C" {
    fn tree_sitter_c() -> Language;
    fn tree_sitter_cpp() -> Language;
    fn tree_sitter_embedded_template() -> Language;
    fn tree_sitter_go() -> Language;
    fn tree_sitter_html() -> Language;
    fn tree_sitter_javascript() -> Language;
    fn tree_sitter_rust() -> Language;
}

pub fn c() -> Language { unsafe { tree_sitter_c() } }
pub fn cpp() -> Language { unsafe { tree_sitter_cpp() } }
pub fn embedded_template() -> Language { unsafe { tree_sitter_embedded_template() } }
pub fn go() -> Language { unsafe { tree_sitter_go() } }
pub fn html() -> Language { unsafe { tree_sitter_html() } }
pub fn javascript() -> Language { unsafe { tree_sitter_javascript() } }
pub fn rust() -> Language { unsafe { tree_sitter_rust() } }
