// This grammar has an "extra" rule, `comment`, that is a non-terminal.

export default grammar({
  name: "extra_non_terminals",

  extras: $ => [
    /\s/,
    $.comment,
  ],

  rules: {
    module: _ => seq('a', 'b', 'c', 'd'),

    comment: $ => choice($.paren_comment, $.line_comment),

    paren_comment: _ => token(seq('(', repeat(/[a-z]+/), ')')),

    line_comment: _ => token(seq('//', /.*/)),
  }
})
