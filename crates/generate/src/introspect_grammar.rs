use std::collections::{BTreeMap, HashMap};

use crate::{
    build_tables::{build_tables, Tables},
    grammars::{InputGrammar, LexicalGrammar, SyntaxGrammar},
    node_types::{self, ChildType, VariableInfo},
    prepare_grammar::prepare_grammar,
    render::generate_symbol_ids,
    rules::{Alias, Symbol},
    GenerateError, OptLevel,
};

pub struct GrammarIntrospection {
    pub syntax_grammar: SyntaxGrammar,
    pub lexical_grammar: LexicalGrammar,
    pub simple_aliases: BTreeMap<Symbol, Alias>,
    pub variable_info: Vec<VariableInfo>,
    pub supertype_symbol_map: BTreeMap<Symbol, Vec<ChildType>>,
    pub tables: Tables,
    pub symbol_ids: HashMap<Symbol, (String, u16)>,
    pub alias_ids: HashMap<Alias, String>,
    pub unique_aliases: Vec<Alias>,
}

pub fn introspect_grammar(
    input_grammar: &InputGrammar,
    report_symbol_name: Option<&str>,
    optimizations: OptLevel,
) -> Result<GrammarIntrospection, GenerateError> {
    let (syntax_grammar, lexical_grammar, inlines, simple_aliases) =
        prepare_grammar(input_grammar)?;
    let variable_info =
        node_types::get_variable_info(&syntax_grammar, &lexical_grammar, &simple_aliases)?;

    let supertype_symbol_map =
        node_types::get_supertype_symbol_map(&syntax_grammar, &simple_aliases, &variable_info);
    let tables = build_tables(
        &syntax_grammar,
        &lexical_grammar,
        &simple_aliases,
        &variable_info,
        &inlines,
        report_symbol_name,
        optimizations,
    )?;

    // Generate symbol IDs (both string and numeric) before rendering C code
    let (symbol_ids, alias_ids, unique_aliases) = generate_symbol_ids(
        &tables.parse_table,
        &syntax_grammar,
        &lexical_grammar,
        &simple_aliases,
    );

    Ok(GrammarIntrospection {
        syntax_grammar,
        lexical_grammar,
        simple_aliases,
        variable_info,
        supertype_symbol_map,
        tables,
        symbol_ids,
        alias_ids,
        unique_aliases,
    })
}
