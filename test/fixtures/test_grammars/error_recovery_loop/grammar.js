// Reduced from https://github.com/tree-sitter/tree-sitter/issues/5967.
module.exports = grammar({
  name: 'error_recovery_loop',
  conflicts: ($) => [
    [$.primary, $.pattern],
    [$.assignment, $.pattern],
  ],
  inline: ($) => [$._lhs],
  rules: {
    program: ($) => repeat($.sequence),
    sequence: ($) => seq($.expression, ','),
    expression: ($) => choice($.primary, seq('<', '<', $.type, '>', choice(':', seq('{', $.sequence))), $.assignment),
    primary: ($) => choice('let', seq('/', token.immediate(repeat1(/[^\]\n\\]/))), seq('[', $.expression, ','), $.non_null),
    _lhs: ($) => choice('let', seq('[', choice($.pattern, seq($.pattern, '=')), ','), $.non_null),
    assignment: ($) => seq(choice(seq('(', choice(seq($.expression, ':'), $.sequence)), $._lhs), '='),
    pattern: ($) => $._lhs,
    non_null: ($) => seq($.expression, '!'),
    type: ($) => choice(seq('(', $.type), /[a-z]/, seq('(', $.pattern, optional(':'), optional('='), ',')),
  },
});
