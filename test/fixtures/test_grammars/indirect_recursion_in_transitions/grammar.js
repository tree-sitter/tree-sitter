export default grammar({
  name: 'indirect_recursive_in_single_symbol_transitions',
  rules: {
    source_file: $ => repeat($._statement),

    _statement: $ => seq($.initialization_part, $.type_expression),

    type_expression: $ => choice('int', $._expression),

    initialization_part: $ => seq('=', $._expression),

    _expression: $ => choice($.identifier_expression, $.type_expression),

    identifier_expression: $ => choice(/[a-zA-Z_][a-zA-Z0-9_]*/, $.type_expression),
  }
});
