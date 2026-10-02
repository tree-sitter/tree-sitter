// The word token is an external token. The generator has no lexical rule for it,
// so it can't extract keywords: 'let' must stay in the main lexer.
//
// `label_name` is the first token in the lexical grammar, so its terminal index (0)
// equals the external index of `identifier` (0). Treating the external word token's
// index as a terminal index makes 'let' look like a keyword of `label_name`.

export default grammar({
  name: 'external_word_token',
  externals: $ => [$.identifier],
  word: $ => $.identifier,

  rules: {
    program: $ => repeat($._item),
    label_name: _ => /[a-z]+/,
    _item: $ => choice($.let_statement, $.label),
    let_statement: $ => seq('let', $.identifier, '=', $.identifier, ';'),
    label: $ => seq('@', $.label_name),
  },
});
