#include "spec_helper.h"
#include "table_builder.h"
#include "parse_table.h"
#include "c_code.h"
#include <fstream>

using namespace std;
using namespace tree_sitter::lr;
using namespace tree_sitter;

Describe(code_generation) {
    string test_parser_dir = src_dir() + "/spec/fixtures/parsers";
    
    It(works_for_the_arithmetic_grammar) {
        Grammar grammar = test_grammars::arithmetic();
        pair<ParseTable, LexTable> tables = build_tables(grammar);
        std::ofstream parser_file(test_parser_dir + "/arithmetic.c");
        parser_file << code_gen::c_code(grammar, tables.first, tables.second);
    }
};