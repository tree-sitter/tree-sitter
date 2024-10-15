// This grammar has an "extra" rule, `comment`, that is a non-terminal.

export default grammar({
  name: "extra_non_terminals",

  extras: $ => [
    /\s/,
    $.comment,
  ],

  rules: {
    module: $ => seq('a', 'b', 'c', 'd'),
    comment: $ => seq('(', repeat(/[a-z]+/), ')'),
  }
})
