module.exports = grammar({
  name: 'terminal_supertype',

  supertypes: $ => [$.A],
  extras: $ => [$.lineComment, $.lineComment2],

  rules: {
    source_file: $ => choice(
      $.B,
      $.A,
    ),
    lineComment: $ => /;;.*/,
    lineComment2: $ => /##.*/,
    A: $ => /xyz/,
    C: $ => "xyz",
    B: $ => seq('abc', $.C),
  }
});
