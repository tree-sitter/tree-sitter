
/// The interface through which RenderTarget accesses Generator.

pub trait RenderContext {
    fn get_language_name(&self) -> &str;
    fn get_abi_version(&self) -> usize;
    fn get_state_count(&self) -> usize;
    fn get_large_state_count(&self) -> usize;
    fn get_symbol_count(&self) -> usize;
    fn get_alias_count(&self) -> usize;
    fn get_token_count(&self) -> usize;
    fn get_external_token_count(&self) -> usize;
    fn get_field_count(&self) -> usize;
    fn get_max_alias_sequence_length(&self) -> usize;
    fn get_production_id_count(&self) -> usize;
    fn get_main_lex_table_state_count(&self) -> usize;
    fn get_keyword_capture_token_id(&self) -> Option<String>;
    fn get_external_token_id(&self, index: usize) -> String;
}
