export default grammar({
  name: "depends_on_column_repetition",
  externals: $ => [$.head, $.tail],
  extras: _ => [],
  rules: {
    document: $ => repeat(choice($.head, $.tail, $.word, $.newline)),
    word: _ => /[a-w]+/,
    newline: _ => "\n",
  },
});
