export default grammar({
  name: 'token_with_separator_prefix',

  extras: _ => [/\s/],

  rules: {
    program: $ => choice($.error_statement, $.entry),
    error_statement: $ => seq('error', 'make', optional($.flag), $.record),
    flag: _ => '-f',
    entry: $ => seq(alias(token(seq(/\s*/, ':')), ':'), 'x'),
    record: _ => seq('{', '}'),
  },
});
